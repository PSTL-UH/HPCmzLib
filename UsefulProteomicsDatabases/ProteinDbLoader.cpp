#include "ProteinDbLoader.h"
#include "FastaHeaderFieldRegex.h"
#include "../Proteomics/Modifications/Modification.h"
#include "../Proteomics/Protein/Protein.h"
#include "ProteinXmlEntry.h"
#include "DecoyProteinGenerator.h"
#include "PtmListLoader.h"
#include "../Proteomics/Protein/ProteolysisProduct.h"
#include "../Proteomics/Protein/SequenceVariation.h"
#include "../Proteomics/Protein/DatabaseReference.h"
#include "../Proteomics/Protein/DisulfideBond.h"
#include "../Proteomics/Protein/SpliceSite.h"

using namespace Proteomics;

namespace UsefulProteomicsDatabases
{

FastaHeaderFieldRegex *const ProteinDbLoader::UniprotAccessionRegex = new FastaHeaderFieldRegex("accession", R"(([A-Z0-9_.]+))", 0, 1);
FastaHeaderFieldRegex *const ProteinDbLoader::UniprotFullNameRegex = new FastaHeaderFieldRegex("fullName", R"(\s(.*?)\sOS=)", 0, 1);
FastaHeaderFieldRegex *const ProteinDbLoader::UniprotNameRegex = new FastaHeaderFieldRegex("name", R"(\|([^\|][A-Z0-9_]+))", 1, 1);
FastaHeaderFieldRegex *const ProteinDbLoader::UniprotGeneNameRegex = new FastaHeaderFieldRegex("geneName", R"(GN=([^ ]+))", 0, 1);
FastaHeaderFieldRegex *const ProteinDbLoader::UniprotOrganismRegex = new FastaHeaderFieldRegex("organism", R"(OS=(.*?)\sGN=)", 0, 1);
FastaHeaderFieldRegex *const ProteinDbLoader::EnsemblAccessionRegex = new FastaHeaderFieldRegex("accession", R"(([A-Z0-9_.]+))", 0, 1);
FastaHeaderFieldRegex *const ProteinDbLoader::EnsemblFullNameRegex = new FastaHeaderFieldRegex("fullName", R"((pep:.*))", 0, 1);
FastaHeaderFieldRegex *const ProteinDbLoader::EnsemblGeneNameRegex = new FastaHeaderFieldRegex("geneName", R"(gene:([^ ]+))", 0, 1);
std::unordered_map<std::string, std::vector<Modification*>> ProteinDbLoader::IdToPossibleMods;
std::unordered_map<std::string, Modification*> ProteinDbLoader::IdWithMotifToMod;
std::string ProteinDbLoader::last_database_location;
std::vector<Modification*> ProteinDbLoader::protein_xml_modlist_general;

    std::vector<Protein*> ProteinDbLoader::LoadProteinXML(const std::string &proteinDbLocation, bool generateTargets, DecoyType decoyType, std::vector<Modification*> &allKnownModifications, bool isContaminant, std::vector<std::string> &modTypesToExclude, std::unordered_map<std::string, Modification*> &unknownModifications, int maxThreads, int maxHeterozygousVariants, int minAlleleDepth)
    {
        std::vector<Modification*> prespecified = GetPtmListFromProteinXml(proteinDbLocation);
        allKnownModifications = allKnownModifications ? allKnownModifications : std::vector<Modification*>();
        modTypesToExclude = modTypesToExclude ? modTypesToExclude : std::vector<std::string>();

        //Dictionary<string, IList<Modification>> modsDictionary = new Dictionary<string, IList<Modification>>();
        if (prespecified.size() > 0 || allKnownModifications.size()() > 0)
        {
            //modsDictionary = GetModificationDict(new HashSet<Modification>(prespecified.Concat(allKnownModifications)));
            IdToPossibleMods = GetModificationDict(std::unordered_set<Modification*>(prespecified.Concat(allKnownModifications)));
            IdWithMotifToMod = GetModificationDictWithMotifs(std::unordered_set<Modification*>(prespecified.Concat(allKnownModifications)));
        }

        std::vector<Protein*> targets;
        unknownModifications = std::unordered_map<std::string, Modification*>();
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (var stream = new FileStream(proteinDbLocation, FileMode.Open, FileAccess.Read, FileShare.Read))
        {
            auto stream = FileStream(proteinDbLocation, FileMode::Open, FileAccess::Read, FileShare::Read);
            Regex *substituteWhitespace = new Regex(R"(\s+)");

            GZipStream tempVar(stream, CompressionMode::Decompress);
            Stream *uniprotXmlFileStream = StringHelper::endsWith(proteinDbLocation, "gz") ? static_cast<Stream*>(&tempVar): stream;

            ProteinXmlEntry *block = new ProteinXmlEntry();

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (XmlReader xml = XmlReader.Create(uniprotXmlFileStream))
            {
                XmlReader xml = XmlReader::Create(uniprotXmlFileStream);
                while (xml.Read())
                {
                    if (xml.NodeType == XmlNodeType::Element)
                    {
                        block->ParseElement(xml.Name, xml);
                    }
                    if (xml.NodeType == XmlNodeType::EndElement || xml.IsEmptyElement)
                    {
                        Protein *newProtein = block->ParseEndElement(xml, modTypesToExclude, unknownModifications, isContaminant, proteinDbLocation);
                        if (newProtein != nullptr)
                        {
                            targets.push_back(newProtein);
                        }
                    }
                }
            }

            delete block;
            delete substituteWhitespace;
        }

        std::vector<Protein*> decoys = DecoyProteinGenerator::GenerateDecoys(targets, decoyType, maxThreads);
        std::vector<Protein*> proteinsToExpand = generateTargets ? targets.Concat(decoys) : decoys;
        return proteinsToExpand.SelectMany([&] (std::any p)
        {
            p::GetVariantProteins(maxHeterozygousVariants, minAlleleDepth);
        }).ToList();
    }

    std::vector<Modification*> ProteinDbLoader::GetPtmListFromProteinXml(const std::string &proteinDbLocation)
    {
        if (proteinDbLocation == last_database_location)
        {
            return protein_xml_modlist_general;
        }
        else
        {
            last_database_location = proteinDbLocation;
            StringBuilder *storedKnownModificationsBuilder = new StringBuilder();
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (var stream = new FileStream(proteinDbLocation, FileMode.Open, FileAccess.Read, FileShare.Read))
            {
                auto stream = FileStream(proteinDbLocation, FileMode::Open, FileAccess::Read, FileShare::Read);
                Regex *startingWhitespace = new Regex(R"(/^\s+/gm)");
                GZipStream tempVar(stream, CompressionMode::Decompress);
                Stream *uniprotXmlFileStream = StringHelper::endsWith(proteinDbLocation, ".gz") ? static_cast<Stream*>(&tempVar): stream;

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (XmlReader xml = XmlReader.Create(uniprotXmlFileStream))
                {
                    XmlReader xml = XmlReader::Create(uniprotXmlFileStream);
                    while (xml.Read())
                    {
                        if (xml.NodeType == XmlNodeType::Element)
                        {
                            if (xml.Name == "modification")
                            {
                                std::string modification = startingWhitespace->Replace(xml.ReadElementString(), "");
                                storedKnownModificationsBuilder->appendLine(modification);
                            }
                            else if (xml.Name == "entry")
                            {
                                //if we are up to entry fields in the protein database, then there no more prespecified modifications to read and we
                                //can begin processing all the lines we have read.
                                //This block of code does not process information in any of the entries.
                                std::vector<(Modification, string)> errors;
                                protein_xml_modlist_general = storedKnownModificationsBuilder->length() <= 0 ? std::vector<Modification*>() : PtmListLoader::ReadModsFromString(storedKnownModificationsBuilder->toString(), errors).ToList();
                                break;
                            }
                        }
                    }
                }

                delete startingWhitespace;
                delete storedKnownModificationsBuilder;
                return protein_xml_modlist_general;
            }

            delete storedKnownModificationsBuilder;
        }
    }

    std::vector<Protein*> ProteinDbLoader::LoadProteinFasta(const std::string &proteinDbLocation, bool generateTargets, DecoyType decoyType, bool isContaminant, FastaHeaderFieldRegex *accessionRegex, FastaHeaderFieldRegex *fullNameRegex, FastaHeaderFieldRegex *nameRegex, FastaHeaderFieldRegex *geneNameRegex, FastaHeaderFieldRegex *organismRegex, std::vector<std::string> &errors, int maxThreads)
    {
        std::unordered_set<std::string> unique_accessions;
        int unique_identifier = 1;
        std::string accession = "";
        std::string name = "";
        std::string fullName = "";
        std::string organism = "";
        std::vector<std::tuple<std::string, std::string>> geneName;
        errors = std::vector<std::string>();
        Regex *substituteWhitespace = new Regex(R"(\s+)");

        std::vector<Protein*> targets;

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (var stream = new FileStream(proteinDbLocation, FileMode.Open, FileAccess.Read, FileShare.Read))
        {
            auto stream = FileStream(proteinDbLocation, FileMode::Open, FileAccess::Read, FileShare::Read);
            GZipStream tempVar(stream, CompressionMode::Decompress);
            Stream *fastaFileStream = StringHelper::endsWith(proteinDbLocation, "gz") ? static_cast<Stream*>(&tempVar): stream;

            StringBuilder *sb = nullptr;
            StreamReader *fasta = new StreamReader(fastaFileStream);

            while (true)
            {
                std::string line = "";
                line = fasta->ReadLine();
                if (line == "")
                {
                    break;
                }

                if (StringHelper::startsWith(line, ">"))
                {
                    accession = ApplyRegex(accessionRegex, line);
                    fullName = ApplyRegex(fullNameRegex, line);
                    name = ApplyRegex(nameRegex, line);
                    organism = ApplyRegex(organismRegex, line);
                    std::string geneNameString = ApplyRegex(geneNameRegex, line);
                    if (geneNameString != "")
                    {
                        geneName.push_back(std::tuple<std::string, std::string>("primary", geneNameString));
                    }

                    if (accession == "" || accession == "")
                    {
                        accession = StringHelper::trimEnd(line.substr(1));
                    }

                    sb = new StringBuilder();
                }
                else if (sb != nullptr)
                {
                    sb->append(StringHelper::trim(line));
                }

                if ((fasta->Peek() == '>' || fasta->Peek() == -1) && accession != "" && sb != nullptr)
                {
                    std::string sequence = substituteWhitespace->Replace(sb->toString(), "");
                    while (std::find(unique_accessions.begin(), unique_accessions.end(), accession) != unique_accessions.end())
                    {
                        accession += "_" + std::to_string(unique_identifier);
                        unique_identifier++;
                    }
                    unique_accessions.insert(accession);
                    Protein *protein = new Protein(sequence, accession, organism, geneName, std::unordered_map<int, std::vector<Modification>>(), std::vector<ProteolysisProduct>(), name, fullName, false, isContaminant, std::vector<DatabaseReference>(), std::vector<SequenceVariation>(), std::vector<SequenceVariation>(), "", std::vector<DisulfideBond>(), std::vector<SpliceSite>(), proteinDbLocation);
                    if (protein->getLength() == 0)
                    {
                        errors.push_back("Line" + line + ", Protein Length of 0: " + protein->getName() + " was skipped from database: " + proteinDbLocation);
                    }
                    else
                    {
                        targets.push_back(protein);
                    }

                    accession = "";
                    name = "";
                    fullName = "";
                    organism = "";
                    geneName = std::vector<std::tuple<std::string, std::string>>();

//C# TO C++ CONVERTER TODO TASK: A 'delete protein' statement was not added since protein was passed to a method or constructor. Handle memory management manually.
                }

                // no input left
                if (fasta->Peek() == -1)
                {
                    break;
                }
            }

            delete fasta;
//C# TO C++ CONVERTER TODO TASK: A 'delete sb' statement was not added since sb was passed to a method or constructor. Handle memory management manually.
        }
        if (!targets.Any())
        {
            errors.push_back("Error: No proteins could be read from the database: " + proteinDbLocation);
        }
        std::vector<Protein*> decoys = DecoyProteinGenerator::GenerateDecoys(targets, decoyType, maxThreads);

        delete substituteWhitespace;
        return generateTargets ? targets.Concat(decoys)->ToList() : decoys;
    }

    std::vector<Protein*> ProteinDbLoader::MergeProteins(std::vector<Protein*> &mergeThese)
    {
        std::unordered_map<std::tuple<std::string, std::string, bool, bool>, std::vector<Protein*>> proteinsByAccessionSequenceContaminant;
        for (auto p : mergeThese)
        {
            std::tuple<std::string, std::string, bool, bool> key = std::tuple<std::string, std::string, bool, bool>(p->getAccession(), p->getBaseSequence(), p->getIsContaminant(), p->getIsDecoy());
            List<Protein*> bundled;
            std::unordered_map<std::tuple<std::string, std::string, bool, bool>, std::vector<Protein*>>::const_iterator proteinsByAccessionSequenceContaminant_iterator = proteinsByAccessionSequenceContaminant.find(key);
            if (proteinsByAccessionSequenceContaminant_iterator == proteinsByAccessionSequenceContaminant.end())
            {
                bundled = proteinsByAccessionSequenceContaminant_iterator->second;
                proteinsByAccessionSequenceContaminant.emplace(key, std::vector<Protein*> {p});
            }
            else
            {
                bundled = proteinsByAccessionSequenceContaminant_iterator->second;
                bundled->Add(p);
            }
        }

        for (auto proteins : proteinsByAccessionSequenceContaminant)
        {
            std::unordered_set<std::string> names = std::unordered_set<std::string>(proteins.second->Select([&] (std::any p)
            {
                p->Name;
            }));
            std::unordered_set<std::string> fullnames = std::unordered_set<std::string>(proteins.second->Select([&] (std::any p)
            {
                p->FullName;
            }));
            std::unordered_set<std::string> descriptions = std::unordered_set<std::string>(proteins.second->Select([&] (std::any p)
            {
                p::FullDescription;
            }));
            std::unordered_set<std::tuple<std::string, std::string>> genenames = std::unordered_set<std::tuple<std::string, std::string>>(proteins.second::SelectMany([&] (std::any p)
            {
                p::GeneNames;
            }));
            std::unordered_set<ProteolysisProduct*> proteolysis = std::unordered_set<ProteolysisProduct*>(proteins.second::SelectMany([&] (std::any p)
            {
                p::ProteolysisProducts;
            }));
            std::unordered_set<SequenceVariation*> variants = std::unordered_set<SequenceVariation*>(proteins.second::SelectMany([&] (std::any p)
            {
                p::SequenceVariations;
            }));
            std::unordered_set<DatabaseReference*> references = std::unordered_set<DatabaseReference*>(proteins.second::SelectMany([&] (std::any p)
            {
                p::DatabaseReferences;
            }));
            std::unordered_set<DisulfideBond*> bonds = std::unordered_set<DisulfideBond*>(proteins.second::SelectMany([&] (std::any p)
            {
                p::DisulfideBonds;
            }));
            std::unordered_set<SpliceSite*> splices = std::unordered_set<SpliceSite*>(proteins.second::SelectMany([&] (std::any p)
            {
                p::SpliceSites;
            }));

            std::unordered_map<int, std::unordered_set<Modification*>> mod_dict;
            for (auto nice : proteins.Value.SelectMany([&] (std::any p)
            {
                p::OneBasedPossibleLocalizedModifications;
            }).ToList())
            {
                HashSet<Modification*> val;
                std::unordered_map<int, std::unordered_set<Modification*>>::const_iterator mod_dict_iterator = mod_dict.find(nice.Key);
                if (mod_dict_iterator == mod_dict.end())
                {
                    val = mod_dict_iterator->second;
                    mod_dict.emplace(nice::Key, std::unordered_set<Modification*>(nice->Value));
                }
                else
                {
                    val = mod_dict_iterator->second;
                    for (Modification *mod : nice->Value)
                    {
                        val->Add(mod);
                    }
                }
            }
            std::unordered_map<int, std::vector<Modification*>> mod_dict2 = mod_dict.ToDictionary([&] (std::any kv)
            {
                kv::Key;
            }, [&] (std::any kv)
            {
                kv->Value->ToList();
            });

//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
            yield return new Protein(std::get<1>(proteins.first), std::get<0>(proteins.first), isContaminant: std::get<2>(proteins.first), isDecoy: std::get<3>(proteins.first), geneNames: genenames.ToList(), oneBasedModifications: mod_dict2, proteolysisProducts: proteolysis.ToList(), name: names.FirstOrDefault(), fullName: fullnames.FirstOrDefault(), databaseReferences: references.ToList(), disulfideBonds: bonds.ToList(), sequenceVariations: variants.ToList(), spliceSites: splices.ToList());
        }
    }

    std::string ProteinDbLoader::ApplyRegex(FastaHeaderFieldRegex *regex, const std::string &line)
    {
        std::string result = "";
        if (regex != nullptr)
        {
            auto matches = regex->getRegex()->Matches(line);
            if (matches->Count > regex->getMatch() && matches[regex->getMatch()].Groups->Count > regex->getGroup())
            {
                result = matches[regex->getMatch()].Groups[regex->getGroup()]->Value;
            }
        }
        return result;
    }

    std::unordered_map<std::string, std::vector<Modification*>> ProteinDbLoader::GetModificationDict(std::vector<Modification*> &mods)
    {
        auto mod_dict = std::unordered_map<std::string, std::vector<Modification*>>();

        for (Modification *mod : mods.Where([&] (std::any m)
        {
            m::ValidModification;
        }))
        {
            std::string modIdWithoutMotif = mod::OriginalId->Split({" on "}, StringSplitOptions::None)->First();
            IList<Modification*> val;
            std::unordered_map<std::string, std::vector<Modification*>>::const_iterator mod_dict_iterator = mod_dict.find(modIdWithoutMotif);
            if (mod_dict_iterator != mod_dict.end())
            {
                val = mod_dict_iterator->second;
                val->Add(mod);
            }
            else
            {
                val = mod_dict_iterator->second;
                mod_dict.emplace(modIdWithoutMotif, std::vector<Modification*> {mod});
            }
        }

        return mod_dict;
    }

    std::unordered_map<std::string, Modification*> ProteinDbLoader::GetModificationDictWithMotifs(std::vector<Modification*> &mods)
    {
        auto mod_dict = std::unordered_map<std::string, Modification*>();

        for (Modification *mod : mods.Where([&] (std::any m)
        {
            m::ValidModification;
        }))
        {
            if (mod_dict.find(mod::IdWithMotif) == mod_dict.end())
            {
                mod_dict.emplace(mod::IdWithMotif, mod);
            }
        }

        return mod_dict;
    }
}
