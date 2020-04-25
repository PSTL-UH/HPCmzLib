#include "ProteinDbLoader.h"
#include "FastaHeaderFieldRegex.h"
#include "../Proteomics/Modifications/Modification.h"
#include "../Proteomics/Protein/Protein.h"
//#include "ProteinXmlEntry.h"
#include "DecoyProteinGenerator.h"
#include "PtmListLoader.h"
#include "../Proteomics/Protein/ProteolysisProduct.h"
#include "../Proteomics/Protein/SequenceVariation.h"
#include "../Proteomics/Protein/DatabaseReference.h"
#include "../Proteomics/Protein/DisulfideBond.h"
#include "../Proteomics/Protein/SpliceSite.h"

#include <iostream>
#include <fstream>
#include <regex>

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
    
    std::vector<Protein*> ProteinDbLoader::LoadProteinXML(const std::string &proteinDbLocation,
                                                          bool generateTargets,
                                                          DecoyType decoyType,
                                                          std::vector<Modification*> &allKnownModifications,
                                                          bool isContaminant,
                                                          std::vector<std::string> &modTypesToExclude,
                                                          std::unordered_map<std::string, Modification*> &unknownModifications,
                                                          int maxThreads,
                                                          int maxHeterozygousVariants,
                                                          int minAlleleDepth)
    {

#ifdef ORIG
        // EDGAR: NOT dealing with XML databases right now.
        //        only fasta supported
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

        auto stream = FileStream(proteinDbLocation, FileMode::Open, FileAccess::Read, FileShare::Read);
        Regex *substituteWhitespace = new Regex(R"(\s+)");
        
        GZipStream tempVar(stream, CompressionMode::Decompress);
        Stream *uniprotXmlFileStream = StringHelper::endsWith(proteinDbLocation, "gz") ? static_cast<Stream*>(&tempVar): stream;
        
        ProteinXmlEntry *block = new ProteinXmlEntry();
        
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
        

        delete block;
        delete substituteWhitespace;
    
        std::vector<Protein*> decoys = DecoyProteinGenerator::GenerateDecoys(targets, decoyType, maxThreads);
        std::vector<Protein*> proteinsToExpand = generateTargets ? targets.Concat(decoys) : decoys;
        return proteinsToExpand.SelectMany([&] (std::any p)  {
                p::GetVariantProteins(maxHeterozygousVariants, minAlleleDepth);
            }).ToList();
#endif
        std::cout << "ProteinDbLoader::LoadProteinXML not supported right now. Use fasta files. "<< std::endl;
        std::vector<Protein*> tmp;
        return tmp;
    }

    std::vector<Modification*> ProteinDbLoader::GetPtmListFromProteinXml(const std::string &proteinDbLocation)
    {
#ifdef ORIG
        // EDGAR: NOT dealing with XML databases right now.
        //        only fasta supported
        
        if (proteinDbLocation == last_database_location)
        {
            return protein_xml_modlist_general;
        }
        else
        {
            last_database_location = proteinDbLocation;
            StringBuilder *storedKnownModificationsBuilder = new StringBuilder();
            auto stream = FileStream(proteinDbLocation, FileMode::Open, FileAccess::Read, FileShare::Read);
            Regex *startingWhitespace = new Regex(R"(/^\s+/gm)");
            GZipStream tempVar(stream, CompressionMode::Decompress);
            Stream *uniprotXmlFileStream = StringHelper::endsWith(proteinDbLocation, ".gz") ? static_cast<Stream*>(&tempVar): stream;
            
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
                        //if we are up to entry fields in the protein database, then there no more prespecified modifications to read
                        //and we can begin processing all the lines we have read.
                        //This block of code does not process information in any of the entries.
                        std::vector<(Modification, string)> errors;
                        protein_xml_modlist_general = storedKnownModificationsBuilder->length() <= 0 ? std::vector<Modification*>() : PtmListLoader::ReadModsFromString(storedKnownModificationsBuilder->toString(), errors).ToList();
                        break;
                    }
                }
            }
            
            delete startingWhitespace;
            delete storedKnownModificationsBuilder;
            return protein_xml_modlist_general;
            delete storedKnownModificationsBuilder;
        }
#endif
        std::cout << "ProteinDbLoader:: GetPtmListFromProteinXml not supported right now. Use fasta files. "<< std::endl;
        std::vector<Modification*> tmp;
        return tmp;
    }
    
    std::vector<Protein*> ProteinDbLoader::LoadProteinFasta(const std::string &proteinDbLocation,
                                                            bool generateTargets,
                                                            DecoyType decoyType,
                                                            bool isContaminant,
                                                            FastaHeaderFieldRegex *accessionRegex,
                                                            FastaHeaderFieldRegex *fullNameRegex,
                                                            FastaHeaderFieldRegex *nameRegex,
                                                            FastaHeaderFieldRegex *geneNameRegex,
                                                            FastaHeaderFieldRegex *organismRegex,
                                                            std::vector<std::string> &errors,
                                                            int maxThreads)
    {
        std::unordered_set<std::string> unique_accessions;
        int unique_identifier = 1;
        std::string accession = "";
        std::string name = "";
        std::string fullName = "";
        std::string organism = "";
        std::vector<std::tuple<std::string, std::string>> geneName;
        errors = std::vector<std::string>();
        std::regex *substituteWhitespace = new std::regex(R"(\s+)");

        std::vector<Protein*> targets;

        //auto stream = FileStream(proteinDbLocation, FileMode::Open, FileAccess::Read, FileShare::Read);
        //GZipStream tempVar(stream, CompressionMode::Decompress);
        //Stream *fastaFileStream = StringHelper::endsWith(proteinDbLocation, "gz") ? static_cast<Stream*>(&tempVar): stream;
        
        StringBuilder *sb = nullptr;
        std::ifstream fasta(proteinDbLocation);
        
        while (true)
        {
            std::string line;
            getline(fasta, line);
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
                    geneName.push_back(std::make_tuple("primary", geneNameString));
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
            
            if ((fasta.peek() == '>' || fasta.peek() == -1) &&
                 accession != ""                            &&
                 sb != nullptr)
            {
                //std::string sequence = substituteWhitespace->Replace(sb->toString(), "");
                std::string sequence = std::regex_replace(sb->toString(), *substituteWhitespace, "");
                while (std::find(unique_accessions.begin(), unique_accessions.end(), accession) != unique_accessions.end())
                {
                    accession += "_" + std::to_string(unique_identifier);
                    unique_identifier++;
                }
                unique_accessions.insert(accession);
                Protein *protein = new Protein(sequence, accession, organism, geneName,
                                               std::unordered_map<int, std::vector<Modification*>>(),
                                               std::vector<ProteolysisProduct*>(), name, fullName,
                                               false, isContaminant,
                                               std::vector<DatabaseReference*>(),
                                               std::vector<SequenceVariation*>(),
                                               std::vector<SequenceVariation*>(), "",
                                               std::vector<DisulfideBond*>(),
                                               std::vector<SpliceSite*>(),
                                               proteinDbLocation);
                if (protein->getLength() == 0)
                {
                    errors.push_back("Line" + line + ", Protein Length of 0: " + protein->getName() +
                                     " was skipped from database: " + proteinDbLocation);
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
                
                //C# TO C++ CONVERTER TODO TASK: A 'delete protein' statement was not added since protein was
                //passed to a method or constructor. Handle memory management manually.
            }
            
            // no input left
            if (fasta.peek() == -1)
            {
                break;
            }
        }
        
        fasta.close();
        //C# TO C++ CONVERTER TODO TASK: A 'delete sb' statement was not added since sb
        //was passed to a method or constructor. Handle memory management manually.
        
        if (targets.empty())
        {
            errors.push_back("Error: No proteins could be read from the database: " + proteinDbLocation);
        }
        std::vector<Protein*> decoys = DecoyProteinGenerator::GenerateDecoys(targets, decoyType, maxThreads);
        
        delete substituteWhitespace;
        //return generateTargets ? targets.Concat(decoys)->ToList() : decoys;
        if ( generateTargets ) {
            for ( auto p: decoys ) {
                targets.push_back(p);
            }
        }
        return generateTargets ? targets : decoys;        
    }
    
    std::vector<Protein*> ProteinDbLoader::MergeProteins(std::vector<Protein*> &mergeThese)
    {
        std::vector<Protein*> retvec;
        
        std::unordered_map<ProteinDbTuple, std::vector<Protein*>, ProteinDbTuple_hash, ProteinDbTuple_equal> proteinsByAccessionSequenceContaminant;
        for (auto p : mergeThese)
        {
            ProteinDbTuple key = std::make_tuple(p->getAccession(), p->getBaseSequence(), p->getIsContaminant(), p->getIsDecoy());
            std::vector<Protein*> bundled;
            std::unordered_map<ProteinDbTuple, std::vector<Protein*>, ProteinDbTuple_hash, ProteinDbTuple_equal >::const_iterator proteinsByAccessionSequenceContaminant_iterator = proteinsByAccessionSequenceContaminant.find(key);
            if (proteinsByAccessionSequenceContaminant_iterator == proteinsByAccessionSequenceContaminant.end())
            {
                //bundled = proteinsByAccessionSequenceContaminant_iterator->second;
                proteinsByAccessionSequenceContaminant.emplace(key, std::vector<Protein*> {p});
            }
            else
            {
                bundled = proteinsByAccessionSequenceContaminant_iterator->second;
                bundled.push_back(p);
            }
        }
        
        for (auto proteins : proteinsByAccessionSequenceContaminant)
        {
#ifdef ORIG
            std::unordered_set<std::string> names = std::unordered_set<std::string>(proteins.second->Select([&] (std::any p)
            {
                p->Name;
            }));
#endif
            std::unordered_set<std::string> names;
            for ( auto p : proteins.second ) {
                names.insert(p->getName() );
            }
#ifdef ORIG
            std::unordered_set<std::string> fullnames = std::unordered_set<std::string>(proteins.second->Select([&] (std::any p)
            {
                p->FullName;
            }));
#endif
            std::unordered_set<std::string> fullnames;
            for ( auto p : proteins.second ) {
                fullnames.insert(p->getFullName() );
            }
            
#ifdef ORIG
            std::unordered_set<std::string> descriptions = std::unordered_set<std::string>(proteins.second->Select([&] (std::any p)
            {
                p::FullDescription;
            }));
#endif
            std::unordered_set<std::string> descriptions;
            for ( auto p : proteins.second ) {
                descriptions.insert(p->getFullDescription() );
            }
            
#ifdef ORIG
            std::unordered_set<std::tuple<std::string, std::string>> genenames = std::unordered_set<std::tuple<std::string, std::string>>(proteins.second::SelectMany([&] (std::any p)
            {
                p::GeneNames;
            }));
#endif
            // Changing to std::vector, since this is required to construct the Protein structure and
            // genenames is not used anywhere
            std::vector<std::tuple<std::string, std::string>> genenames;
            for ( Proteomics::Protein* p: proteins.second ) {
                for ( auto q: p->getGeneNames() ) {
                    genenames.push_back( q );
                }
            }

#ifdef ORIG
            std::unordered_set<ProteolysisProduct*> proteolysis = std::unordered_set<ProteolysisProduct*>(proteins.second::SelectMany([&] (std::any p)
            {
                p::ProteolysisProducts;
            }));
#endif
            // Changing to std::vector, since this is required to construct the Protein structure and
            // proteolysis is not used anywhere
            std::vector<ProteolysisProduct*> proteolysis;
            for ( auto p: proteins.second) {
                for ( auto q: p->getProteolysisProducts() ) {
                    proteolysis.push_back(q );
                }
            }
            
#ifdef ORIG
            std::unordered_set<SequenceVariation*> variants = std::unordered_set<SequenceVariation*>(proteins.second::SelectMany([&] (std::any p)
            {
                p::SequenceVariations;
            }));
#endif
            // Changing to std::vector, since this is required to construct the Protein structure and
            // variants is not used anywhere
            std::vector<SequenceVariation*> variants;
            for ( auto p: proteins.second) {
                for ( auto q: p->getSequenceVariations() ) {
                    variants.push_back(q );
                }
            }

#ifdef ORIG            
            std::unordered_set<DatabaseReference*> references = std::unordered_set<DatabaseReference*>(proteins.second::SelectMany([&] (std::any p)
            {
                p::DatabaseReferences;
            }));
#endif
            // Changing to std::vector, since this is required to construct the Protein structure and
            // references is not used anywhere
            std::vector<DatabaseReference*> references;
            for ( auto p: proteins.second) {
                for ( auto q: p->getDatabaseReferences() ) {
                    references.push_back(q );
                }
            }

#ifdef ORIG
            std::unordered_set<DisulfideBond*> bonds = std::unordered_set<DisulfideBond*>(proteins.second::SelectMany([&] (std::any p)
            {
                p::DisulfideBonds;
            }));
#endif
            // Changing to std::vector, since this is required to construct the Protein structure and
            // bonds is not used anywhere
            std::vector<DisulfideBond*> bonds;
            for ( auto p: proteins.second) {
                for ( auto q: p->getDisulfideBonds() ) {
                    bonds.push_back(q );
                }
            }
            
#ifdef ORIG
            std::unordered_set<SpliceSite*> splices = std::unordered_set<SpliceSite*>(proteins.second::SelectMany([&] (std::any p)
            {
                p::SpliceSites;
            }));
#endif
            // Changing to std::vector, since this is required to construct the Protein structure and
            // splices is not used anywhere
            std::vector<SpliceSite*> splices;
            for ( auto p: proteins.second) {
                for ( auto q: p->getSpliceSites() ) {
                    splices.push_back(q );
                }
            }
            
            std::unordered_map<int, std::unordered_set<Modification*>> mod_dict;
#ifdef ORIG
            //for (auto nice : proteins.Value.SelectMany([&] (std::any p)    {
            //            p::OneBasedPossibleLocalizedModifications;
            //        }).ToList())            
#endif
            std::unordered_map<int, std::unordered_set<Modification*>> tmp_dict;
            for ( auto p: proteins.second ) {
                for ( auto q: p->getOneBasedPossibleLocalizedModifications() ) {
                    auto v = new std::unordered_set<Modification*>();
                    for ( auto w: q.second) {
                        v->emplace(w);
                    }
                    tmp_dict[q.first] = *v;
                }
            }
            
            for ( auto nice : tmp_dict)   {
                std::unordered_set<Modification*> val;
                std::unordered_map<int, std::unordered_set<Modification*>>::const_iterator mod_dict_iterator = mod_dict.find(nice.first);
                if (mod_dict_iterator == mod_dict.end())
                {
                    //val = mod_dict_iterator->second;
                    mod_dict.emplace(nice.first, nice.second);
                }
                else
                {
                    val = mod_dict_iterator->second;
                    for (Modification *mod : nice.second)
                    {
                        val.emplace(mod);
                    }
                }
            }
        
#ifdef ORIG
            std::unordered_map<int, std::vector<Modification*>> mod_dict2 = mod_dict.ToDictionary([&] (std::any kv)   {
                    kv::Key;
                }, [&] (std::any kv) {
                    kv->Value->ToList();
                });
#endif
            std::unordered_map<int, std::vector<Modification*>> mod_dict2;
            for ( auto kv : mod_dict ) {
                auto v = new std::vector<Modification*>();
                for ( auto w: kv.second ) {
                    v->push_back(w);
                }
                mod_dict2.emplace(kv.first, *v);
            }
            
#ifdef ORIG
            //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
            yield return new Protein(std::get<1>(proteins.first), std::get<0>(proteins.first),
                                     isContaminant: std::get<2>(proteins.first),
                                     isDecoy: std::get<3>(proteins.first),
                                     geneNames: genenames.ToList(),
                                     oneBasedModifications: mod_dict2,
                                     proteolysisProducts: proteolysis.ToList(),
                                     name: names.FirstOrDefault(),
                                     fullName: fullnames.FirstOrDefault(),
                                     databaseReferences: references.ToList(),
                                     disulfideBonds: bonds.ToList(),
                                     sequenceVariations: variants.ToList(),
                                     spliceSites: splices.ToList());
#endif
            auto appliedSequenceVariations = new std::vector<SequenceVariation*>();
            Protein *prot =  new Protein(std::get<1>(proteins.first), //Sequence
                                         std::get<0>(proteins.first), //Accession
                                         "",                          //organism
                                         genenames,                   //geneNames
                                         mod_dict2,                   //oneBasedModifications
                                         proteolysis,                 //proteolysisProducts
                                         *(names.begin()),            //name
                                         *(fullnames.begin()),        //fullname
                                         std::get<3>(proteins.first), //isDecoy
                                         std::get<2>(proteins.first), //isContaminant
                                         references,                  //databaseReferences
                                         variants,                    //sequenceVariations
                                         *appliedSequenceVariations,   //appliedSequenceVariations
                                         "",                          //sampleNameForVariants
                                         bonds,                       //disulfideBonds
                                         splices );                   //spliceSites
            retvec.push_back(prot);
        }
        
        return retvec;
    }

    std::string ProteinDbLoader::ApplyRegex(FastaHeaderFieldRegex *regex, const std::string &line)
    {
        std::string result;
        if (regex != nullptr)
        {
#ifdef ORIG
            auto matches = regex->getRegex()->Matches(line);
            if (matches->Count > regex->getMatch()                           &&
                matches[regex->getMatch()].Groups->Count > regex->getGroup())
            {
                result = matches[regex->getMatch()].Groups[regex->getGroup()].str();
            }

#endif
            int matchno=0;
            std::sregex_iterator it(line.begin(), line.end(), *(regex->getRegex()) );
            std::sregex_iterator reg_end;

            int match = regex->getMatch();
            int group = regex->getGroup();
            
            int i=0;
            for ( ; it!= reg_end; ++it, ++matchno ) {
                std::smatch res;
                std::string sgroup = it->str();
                if ( std::regex_search(sgroup, res, *(regex->getRegex()) ) )  {
                    for ( auto groupno=0; groupno<res.size() ; groupno++ ) {
                        if ( matchno == match && groupno == group ) {
                            result =  res[groupno];
                            break;
                        }
                    }
                }
            }
            
        }
        return result;
    }

    std::unordered_map<std::string, std::vector<Modification*>> ProteinDbLoader::GetModificationDict(std::vector<Modification*> &mods)
    {
        auto mod_dict = std::unordered_map<std::string, std::vector<Modification*>>();

#ifdef ORIG
        //for (Modification *mod : mods.Where([&] (std::any m)
        // {
        //    m::ValidModification;
        //}))
#endif
        for (Modification *mod : mods ) 
        {
            if ( !mod->getValidModification() ) {
                continue;
            }

            //std::string modIdWithoutMotif = mod::OriginalId->Split({" on "}, StringSplitOptions::None)->First();
            std::string modIdWithoutMotif = mod->getOriginalId().substr(0, mod->getOriginalId().find(" on "));
            std::vector<Modification*> val;
            std::unordered_map<std::string, std::vector<Modification*>>::const_iterator mod_dict_iterator = mod_dict.find(modIdWithoutMotif);
            if (mod_dict_iterator != mod_dict.end())
            {
                val = mod_dict_iterator->second;
                val.push_back(mod);
            }
            else
            {
                //val = mod_dict_iterator->second;
                std::vector<Modification*> vtemp = {mod};
                mod_dict.emplace(modIdWithoutMotif, vtemp );
            }
        }

        return mod_dict;
    }

    std::unordered_map<std::string, Modification*> ProteinDbLoader::GetModificationDictWithMotifs(std::vector<Modification*> &mods)
    {
        auto mod_dict = std::unordered_map<std::string, Modification*>();

#ifdef ORIG
        //for (Modification *mod : mods.Where([&] (std::any m)
        //{
        //    m::ValidModification;
        //}))
#endif
        for (Modification *mod : mods ) 
        {
            if ( !mod->getValidModification() ) {
                continue;
            }
            if (mod_dict.find(mod->getIdWithMotif() ) == mod_dict.end())
            {
                mod_dict.emplace(mod->getIdWithMotif(), mod);
            }
        }

        return mod_dict;
    }
}
