#include "ProteinDbWriter.h"
#include "../Proteomics/Modification.h"
#include "../Proteomics/Protein.h"

using namespace Proteomics;

namespace UsefulProteomicsDatabases {

    std::unordered_map<std::string, int> ProteinDbWriter::WriteXmlDatabase(std::unordered_map<std::string, std::unordered_set<std::tuple<int, Modification*>>> &AdditionalModsToAddToProteins, std::vector<Protein*> &proteinList, const std::string &outputFileName) {
        auto xmlWriterSettings = new XmlWriterSettings();
        xmlWriterSettings->Indent = true;
        xmlWriterSettings->IndentChars = "  ";

        std::unordered_map<std::string, int> newModResEntries;

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (XmlWriter writer = XmlWriter.Create(outputFileName, xmlWriterSettings))
        {
            XmlWriter writer = XmlWriter::Create(outputFileName, xmlWriterSettings);
            writer.WriteStartDocument();
            writer.WriteStartElement("mzLibProteinDb");

            std::unordered_set<Modification*> all_relevant_modifications = std::unordered_set<Modification*>(proteinList.SelectMany([&] (std::any p) {
                p::OneBasedPossibleLocalizedModifications->Values->SelectMany([&] (std::any list) {
//C# TO C++ CONVERTER TODO TASK: A 'delete xmlWriterSettings' statement was not added since xmlWriterSettings was passed to a method or constructor. Handle memory management manually.
                    return list;
                });
            }).Concat(AdditionalModsToAddToProteins.Where([&] (std::any kv) {
                proteinList.Select([&] (std::any p) {
                    p::Accession;
                })->Contains(kv::Key);
            }).SelectMany([&] (std::any kv) {
                kv->Value->Select([&] (std::any v) {
                    v::Item2;
                });
            })));

            for (Modification *mod : all_relevant_modifications.OrderBy([&] (std::any m) {
                m::id;
            })) {
                writer.WriteStartElement("modification");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                writer.WriteString(mod.ToString() + "\r\n" + "//");
                writer.WriteEndElement();
            }
            for (auto protein : proteinList) {
                writer.WriteStartElement("entry");
                writer.WriteStartElement("accession");
                writer.WriteString(protein->getAccession());
                writer.WriteEndElement();

                if (protein->getName() != "") {
                    writer.WriteStartElement("name");
                    writer.WriteString(protein->getName());
                    writer.WriteEndElement();
                }

                if (protein->getFullName() != "") {
                    writer.WriteStartElement("protein");
                    writer.WriteStartElement("recommendedName");
                    writer.WriteStartElement("fullName");
                    writer.WriteString(protein->getFullName());
                    writer.WriteEndElement();
                    writer.WriteEndElement();
                    writer.WriteEndElement();
                }

                writer.WriteStartElement("gene");
                for (auto gene_name : protein->getGeneNames()) {
                    writer.WriteStartElement("name");
                    writer.WriteAttributeString("type", gene_name.Item1);
                    writer.WriteString(gene_name.Item2);
                    writer.WriteEndElement();
                }
                writer.WriteEndElement();

                for (auto dbRef : protein->getDatabaseReferences()) {
                    writer.WriteStartElement("dbReference");
                    writer.WriteAttributeString("type", dbRef->getType());
                    writer.WriteAttributeString("id", dbRef->getId());
                    for (auto property_Renamed : dbRef->getProperties()) {
                        writer.WriteStartElement("property");
                        writer.WriteAttributeString("type", property_Renamed.Item1);
                        writer.WriteAttributeString("value", property_Renamed.Item2);
                        writer.WriteEndElement();
                    }
                    writer.WriteEndElement();
                }
                for (auto proteolysisProduct : protein->getProteolysisProducts()) {
                    writer.WriteStartElement("feature");
                    writer.WriteAttributeString("type", proteolysisProduct->getType());
                    writer.WriteStartElement("location");
                    writer.WriteStartElement("begin");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                    writer.WriteAttributeString("position", proteolysisProduct->getOneBasedBeginPosition().ToString());
                    writer.WriteEndElement();
                    writer.WriteStartElement("end");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                    writer.WriteAttributeString("position", proteolysisProduct->getOneBasedEndPosition().ToString());
                    writer.WriteEndElement();
                    writer.WriteEndElement();
                    writer.WriteEndElement();
                }

                std::unordered_map<int, std::unordered_set<std::string>> modsToWriteForThisSpecificProtein;

                for (auto ye : protein->getOneBasedPossibleLocalizedModifications()) {
                    for (auto nice : ye.Value) {
                        HashSet<std::string> val;
                        std::unordered_map<int, std::unordered_set<std::string>>::const_iterator modsToWriteForThisSpecificProtein_iterator = modsToWriteForThisSpecificProtein.find(ye.Key);
                        if (modsToWriteForThisSpecificProtein_iterator != modsToWriteForThisSpecificProtein.end()) {
                            val = modsToWriteForThisSpecificProtein_iterator->second;
                            val->Add(nice->id);
                        }
                        else {
                            val = modsToWriteForThisSpecificProtein_iterator->second;
                            modsToWriteForThisSpecificProtein.emplace(ye.Key, std::unordered_set<std::string> {nice->id});
                        }
                    }
                }

                if (AdditionalModsToAddToProteins.find(protein->getAccession()) != AdditionalModsToAddToProteins.end()) {
                    for (auto ye : AdditionalModsToAddToProteins[protein->getAccession()]) {
                        int additionalModResidueIndex = ye.Item1;
                        std::string additionalModId = ye.Item2->id;
                        bool modAdded = false;

                        // If we already have modifications that need to be written to the specific residue, get the hash set of those mods
                        HashSet<std::string> val;
                        std::unordered_map<int, std::unordered_set<std::string>>::const_iterator modsToWriteForThisSpecificProtein_iterator = modsToWriteForThisSpecificProtein.find(additionalModResidueIndex);
                        if (modsToWriteForThisSpecificProtein_iterator != modsToWriteForThisSpecificProtein.end()) {
                            val = modsToWriteForThisSpecificProtein_iterator->second;
                            // Try to add the new mod to that hash set. If it's not there, modAdded=true, and it is added.
                            modAdded = val->Add(additionalModId);
                        }

                        // Otherwise, no modifications currently need to be written to the residue at residueIndex, so need to create new hash set for that residue
                        else {
                            val = modsToWriteForThisSpecificProtein_iterator->second;
                            modsToWriteForThisSpecificProtein.emplace(additionalModResidueIndex, std::unordered_set<std::string> {additionalModId});
                            modAdded = true;
                        }

                        // Finally, if a new modification has in fact been deemed worthy of being added to the database, mark that in the output dictionary
                        if (modAdded) {
                            if (newModResEntries.find(additionalModId) != newModResEntries.end()) {
                                newModResEntries[additionalModId]++;
                            }
                            else {
                                newModResEntries.emplace(additionalModId, 1);
                            }
                        }
                    }
                }

                for (auto hm : modsToWriteForThisSpecificProtein.OrderBy([&] (std::any b) {
                    b::Key;
                })) {
                    for (auto modId : hm->Value) {
                        writer.WriteStartElement("feature");
                        writer.WriteAttributeString("type", "modified residue");
                        writer.WriteAttributeString("description", modId);
                        writer.WriteStartElement("location");
                        writer.WriteStartElement("position");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                        writer.WriteAttributeString("position", hm::Key->ToString(CultureInfo::InvariantCulture));
                        writer.WriteEndElement();
                        writer.WriteEndElement();
                        writer.WriteEndElement();
                    }
                }

                for (auto hm : protein->getSequenceVariations()) {
                    writer.WriteStartElement("feature");
                    writer.WriteAttributeString("type", "sequence variant");
                    writer.WriteAttributeString("description", hm->getDescription());
                    writer.WriteStartElement("original");
                    writer.WriteString(hm->getOriginalSequence());
                    writer.WriteEndElement(); // original
                    writer.WriteStartElement("variation");
                    writer.WriteString(hm->getVariantSequence());
                    writer.WriteEndElement(); // variation
                    writer.WriteStartElement("location");
                    if (hm->getOneBasedBeginPosition() == hm->getOneBasedEndPosition()) {
                        writer.WriteStartElement("position");
                        writer.WriteAttributeString("position", std::to_string(hm->getOneBasedBeginPosition()));
                        writer.WriteEndElement();
                    }
                    else {
                        writer.WriteStartElement("begin");
                        writer.WriteAttributeString("position", std::to_string(hm->getOneBasedBeginPosition()));
                        writer.WriteEndElement();
                        writer.WriteStartElement("end");
                        writer.WriteAttributeString("position", std::to_string(hm->getOneBasedEndPosition()));
                        writer.WriteEndElement();
                    }
                    writer.WriteEndElement(); // location
                    writer.WriteEndElement(); // feature
                }

                for (auto hm : protein->getDisulfideBonds()) {
                    writer.WriteStartElement("feature");
                    writer.WriteAttributeString("type", "disulfide bond");
                    writer.WriteAttributeString("description", hm->getDescription());
                    writer.WriteStartElement("location");
                    if (hm->getOneBasedBeginPosition() == hm->getOneBasedEndPosition()) {
                        writer.WriteStartElement("position");
                        writer.WriteAttributeString("position", std::to_string(hm->getOneBasedBeginPosition()));
                        writer.WriteEndElement();
                    }
                    else {
                        writer.WriteStartElement("begin");
                        writer.WriteAttributeString("position", std::to_string(hm->getOneBasedBeginPosition()));
                        writer.WriteEndElement();
                        writer.WriteStartElement("end");
                        writer.WriteAttributeString("position", std::to_string(hm->getOneBasedEndPosition()));
                        writer.WriteEndElement();
                    }
                    writer.WriteEndElement(); // location
                    writer.WriteEndElement(); // feature
                }

                writer.WriteStartElement("sequence");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                writer.WriteAttributeString("length", protein->getLength().ToString(CultureInfo::InvariantCulture));
                writer.WriteString(protein->getBaseSequence());
                writer.WriteEndElement(); // sequence
                writer.WriteEndElement(); // entry
            }

            writer.WriteEndElement();
            writer.WriteEndDocument();
        }

//C# TO C++ CONVERTER TODO TASK: A 'delete xmlWriterSettings' statement was not added since xmlWriterSettings was passed to a method or constructor. Handle memory management manually.
        return newModResEntries;
    }

    void ProteinDbWriter::WriteFastaDatabase(std::vector<Protein*> &proteinList, const std::string &outputFileName, const std::string &delimeter) {
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (StreamWriter writer = new StreamWriter(outputFileName))
    {
            StreamWriter writer = StreamWriter(outputFileName);
            for (auto protein : proteinList) {
                std::string header = protein->getFullName() != protein->getAccession() ? protein->getAccession() + delimeter + protein->getFullName() : protein->getAccession(); // we read in full name and accession to be the same string if the format isn't recognized
                writer.WriteLine(">" + header);
                writer.WriteLine(protein->getBaseSequence());
            }
    }
    }
}
