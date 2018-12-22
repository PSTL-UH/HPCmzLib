#include "ProteinDbWriter.h"
#include "../Proteomics/Modification.h"
#include "../Proteomics/Protein.h"

using namespace Proteomics;

namespace UsefulProteomicsDatabases {

    std::unordered_map<std::wstring, int> ProteinDbWriter::WriteXmlDatabase(std::unordered_map<std::wstring, std::unordered_set<std::tuple<int, Modification*>>> &AdditionalModsToAddToProteins, std::vector<Protein*> &proteinList, const std::wstring &outputFileName) {
        auto xmlWriterSettings = new XmlWriterSettings();
        xmlWriterSettings->Indent = true;
        xmlWriterSettings->IndentChars = L"  ";

        std::unordered_map<std::wstring, int> newModResEntries;

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (XmlWriter writer = XmlWriter.Create(outputFileName, xmlWriterSettings))
        {
            XmlWriter writer = XmlWriter::Create(outputFileName, xmlWriterSettings);
            writer.WriteStartDocument();
            writer.WriteStartElement(L"mzLibProteinDb");

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
                writer.WriteStartElement(L"modification");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                writer.WriteString(mod.ToString() + L"\r\n" + L"//");
                writer.WriteEndElement();
            }
            for (auto protein : proteinList) {
                writer.WriteStartElement(L"entry");
                writer.WriteStartElement(L"accession");
                writer.WriteString(protein->getAccession());
                writer.WriteEndElement();

                if (protein->getName() != L"") {
                    writer.WriteStartElement(L"name");
                    writer.WriteString(protein->getName());
                    writer.WriteEndElement();
                }

                if (protein->getFullName() != L"") {
                    writer.WriteStartElement(L"protein");
                    writer.WriteStartElement(L"recommendedName");
                    writer.WriteStartElement(L"fullName");
                    writer.WriteString(protein->getFullName());
                    writer.WriteEndElement();
                    writer.WriteEndElement();
                    writer.WriteEndElement();
                }

                writer.WriteStartElement(L"gene");
                for (auto gene_name : protein->getGeneNames()) {
                    writer.WriteStartElement(L"name");
                    writer.WriteAttributeString(L"type", gene_name.Item1);
                    writer.WriteString(gene_name.Item2);
                    writer.WriteEndElement();
                }
                writer.WriteEndElement();

                for (auto dbRef : protein->getDatabaseReferences()) {
                    writer.WriteStartElement(L"dbReference");
                    writer.WriteAttributeString(L"type", dbRef->getType());
                    writer.WriteAttributeString(L"id", dbRef->getId());
                    for (auto property_Renamed : dbRef->getProperties()) {
                        writer.WriteStartElement(L"property");
                        writer.WriteAttributeString(L"type", property_Renamed.Item1);
                        writer.WriteAttributeString(L"value", property_Renamed.Item2);
                        writer.WriteEndElement();
                    }
                    writer.WriteEndElement();
                }
                for (auto proteolysisProduct : protein->getProteolysisProducts()) {
                    writer.WriteStartElement(L"feature");
                    writer.WriteAttributeString(L"type", proteolysisProduct->getType());
                    writer.WriteStartElement(L"location");
                    writer.WriteStartElement(L"begin");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                    writer.WriteAttributeString(L"position", proteolysisProduct->getOneBasedBeginPosition().ToString());
                    writer.WriteEndElement();
                    writer.WriteStartElement(L"end");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                    writer.WriteAttributeString(L"position", proteolysisProduct->getOneBasedEndPosition().ToString());
                    writer.WriteEndElement();
                    writer.WriteEndElement();
                    writer.WriteEndElement();
                }

                std::unordered_map<int, std::unordered_set<std::wstring>> modsToWriteForThisSpecificProtein;

                for (auto ye : protein->getOneBasedPossibleLocalizedModifications()) {
                    for (auto nice : ye.Value) {
                        HashSet<std::wstring> val;
                        std::unordered_map<int, std::unordered_set<std::wstring>>::const_iterator modsToWriteForThisSpecificProtein_iterator = modsToWriteForThisSpecificProtein.find(ye.Key);
                        if (modsToWriteForThisSpecificProtein_iterator != modsToWriteForThisSpecificProtein.end()) {
                            val = modsToWriteForThisSpecificProtein_iterator->second;
                            val->Add(nice->id);
                        }
                        else {
                            val = modsToWriteForThisSpecificProtein_iterator->second;
                            modsToWriteForThisSpecificProtein.emplace(ye.Key, std::unordered_set<std::wstring> {nice->id});
                        }
                    }
                }

                if (AdditionalModsToAddToProteins.find(protein->getAccession()) != AdditionalModsToAddToProteins.end()) {
                    for (auto ye : AdditionalModsToAddToProteins[protein->getAccession()]) {
                        int additionalModResidueIndex = ye.Item1;
                        std::wstring additionalModId = ye.Item2->id;
                        bool modAdded = false;

                        // If we already have modifications that need to be written to the specific residue, get the hash set of those mods
                        HashSet<std::wstring> val;
                        std::unordered_map<int, std::unordered_set<std::wstring>>::const_iterator modsToWriteForThisSpecificProtein_iterator = modsToWriteForThisSpecificProtein.find(additionalModResidueIndex);
                        if (modsToWriteForThisSpecificProtein_iterator != modsToWriteForThisSpecificProtein.end()) {
                            val = modsToWriteForThisSpecificProtein_iterator->second;
                            // Try to add the new mod to that hash set. If it's not there, modAdded=true, and it is added.
                            modAdded = val->Add(additionalModId);
                        }

                        // Otherwise, no modifications currently need to be written to the residue at residueIndex, so need to create new hash set for that residue
                        else {
                            val = modsToWriteForThisSpecificProtein_iterator->second;
                            modsToWriteForThisSpecificProtein.emplace(additionalModResidueIndex, std::unordered_set<std::wstring> {additionalModId});
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
                        writer.WriteStartElement(L"feature");
                        writer.WriteAttributeString(L"type", L"modified residue");
                        writer.WriteAttributeString(L"description", modId);
                        writer.WriteStartElement(L"location");
                        writer.WriteStartElement(L"position");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                        writer.WriteAttributeString(L"position", hm::Key->ToString(CultureInfo::InvariantCulture));
                        writer.WriteEndElement();
                        writer.WriteEndElement();
                        writer.WriteEndElement();
                    }
                }

                for (auto hm : protein->getSequenceVariations()) {
                    writer.WriteStartElement(L"feature");
                    writer.WriteAttributeString(L"type", L"sequence variant");
                    writer.WriteAttributeString(L"description", hm->getDescription());
                    writer.WriteStartElement(L"original");
                    writer.WriteString(hm->getOriginalSequence());
                    writer.WriteEndElement(); // original
                    writer.WriteStartElement(L"variation");
                    writer.WriteString(hm->getVariantSequence());
                    writer.WriteEndElement(); // variation
                    writer.WriteStartElement(L"location");
                    if (hm->getOneBasedBeginPosition() == hm->getOneBasedEndPosition()) {
                        writer.WriteStartElement(L"position");
                        writer.WriteAttributeString(L"position", std::to_wstring(hm->getOneBasedBeginPosition()));
                        writer.WriteEndElement();
                    }
                    else {
                        writer.WriteStartElement(L"begin");
                        writer.WriteAttributeString(L"position", std::to_wstring(hm->getOneBasedBeginPosition()));
                        writer.WriteEndElement();
                        writer.WriteStartElement(L"end");
                        writer.WriteAttributeString(L"position", std::to_wstring(hm->getOneBasedEndPosition()));
                        writer.WriteEndElement();
                    }
                    writer.WriteEndElement(); // location
                    writer.WriteEndElement(); // feature
                }

                for (auto hm : protein->getDisulfideBonds()) {
                    writer.WriteStartElement(L"feature");
                    writer.WriteAttributeString(L"type", L"disulfide bond");
                    writer.WriteAttributeString(L"description", hm->getDescription());
                    writer.WriteStartElement(L"location");
                    if (hm->getOneBasedBeginPosition() == hm->getOneBasedEndPosition()) {
                        writer.WriteStartElement(L"position");
                        writer.WriteAttributeString(L"position", std::to_wstring(hm->getOneBasedBeginPosition()));
                        writer.WriteEndElement();
                    }
                    else {
                        writer.WriteStartElement(L"begin");
                        writer.WriteAttributeString(L"position", std::to_wstring(hm->getOneBasedBeginPosition()));
                        writer.WriteEndElement();
                        writer.WriteStartElement(L"end");
                        writer.WriteAttributeString(L"position", std::to_wstring(hm->getOneBasedEndPosition()));
                        writer.WriteEndElement();
                    }
                    writer.WriteEndElement(); // location
                    writer.WriteEndElement(); // feature
                }

                writer.WriteStartElement(L"sequence");
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                writer.WriteAttributeString(L"length", protein->getLength().ToString(CultureInfo::InvariantCulture));
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

    void ProteinDbWriter::WriteFastaDatabase(std::vector<Protein*> &proteinList, const std::wstring &outputFileName, const std::wstring &delimeter) {
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (StreamWriter writer = new StreamWriter(outputFileName))
    {
            StreamWriter writer = StreamWriter(outputFileName);
            for (auto protein : proteinList) {
                std::wstring header = protein->getFullName() != protein->getAccession() ? protein->getAccession() + delimeter + protein->getFullName() : protein->getAccession(); // we read in full name and accession to be the same string if the format isn't recognized
                writer.WriteLine(L">" + header);
                writer.WriteLine(protein->getBaseSequence());
            }
    }
    }
}
