#include "ProteinDbWriter.h"
#include "../Proteomics/Modifications/Modification.h"
#include "../Proteomics/Protein/Protein.h"
#include "../Proteomics/Protein/SequenceVariation.h"
#include "../Proteomics/Protein/VariantApplication.h"
#include "XmlWriter.h"

#include <iostream>
#include <fstream>

using namespace Proteomics;

namespace UsefulProteomicsDatabases
{
    std::unordered_map<std::string, int> ProteinDbWriter::WriteXmlDatabase(std::unordered_map<std::string, ModDbTuple_set> &additionalModsToAddToProteins,
                                                                           std::vector<Protein*> &proteinList,
                                                                           const std::string &outputFileName)
    {
        //additionalModsToAddToProteins = additionalModsToAddToProteins ? additionalModsToAddToProteins :
        //                                std::unordered_map<std::string, ModDbTuple_set>>();

        // write nonvariant proteins (for cases where variants aren't applied, this just gets the protein itself)
#ifdef ORIG
        std::vector<Protein*> nonVariantProteins = proteinList.Select([&] (std::any p){
                p::NonVariantProtein;
            }).Distinct().ToList();
#endif
        std::vector<Protein*> nonVariantProteins;
        for ( auto p : proteinList ) {
            bool found = false;
            for ( auto q: nonVariantProteins ) {
                if ( p->getNonVariantProtein() == q ) {
                    found = true;
                    break;
                }
            }
            if ( !found ) {
                nonVariantProteins.push_back( p->getNonVariantProtein() );
            }
        }
        
#ifdef ORIG
        auto xmlWriterSettings = new XmlWriterSettings();
        xmlWriterSettings->Indent = true;
        xmlWriterSettings->IndentChars = "  ";
#endif
        std::unordered_map<std::string, int> newModResEntries;
        
        //XmlWriter writer = XmlWriter::Create(outputFileName, xmlWriterSettings);
        XmlWriter writer(outputFileName);
        writer.WriteStartDocument();
        writer.WriteStartElement("mzLibProteinDb");
        
        std::vector<Modification*> myModificationList;
        for (auto p : nonVariantProteins)
        {
            for (auto entry : p->getOneBasedPossibleLocalizedModifications())
            {
                myModificationList.insert(myModificationList.end(), std::get<1>(entry).begin(), std::get<1>(entry).end());
            }
        }
        
#ifdef ORIG
        std::unordered_set<Modification*> allRelevantModifications = std::unordered_set<Modification*>(nonVariantProteins.SelectMany([&] (std::any p)
        {
            p::SequenceVariations::SelectMany([&] (std::any sv)  {
                    sv::OneBasedModifications;
                }).Concat(p::OneBasedPossibleLocalizedModifications)->SelectMany([&] (std::any kv) {
                        kv->Value;
                    });
        }).Concat(additionalModsToAddToProteins.Where([&] (std::any kv)  {
                    nonVariantProteins.SelectMany([&] (std::any p)  {
                            p::SequenceVariations->Select([&] (std::any sv) {
                                    VariantApplication::GetAccession(p, std::vector<std::any> {sv});
                                }).Concat(std::vector<std::any> {p::Accession});
                        })->Contains(kv::Key);
                }).SelectMany([&] (std::any kv)  {
                        kv->Value->Select([&] (std::any v)   {
                                v::Item2;
                            });
                    }) ) );
#endif
        // This part is equivalent to lines 1-7
        std::set<Modification*> allRelevantModifications;
        for ( auto p: nonVariantProteins ) {
            for ( auto sv : p->getSequenceVariations() ) {
                for ( auto q: sv->getOneBasedModifications() ) {
                    allRelevantModifications.insert(q.second.begin(), q.second.end());
                }
            }
            for ( auto kv : p->getOneBasedPossibleLocalizedModifications() ) {
                allRelevantModifications.insert(kv.second.begin(), kv.second.end());
            }
        }
        //This is equivalent to lines 8-18
        for ( auto kv: additionalModsToAddToProteins ) { // unordered_map<string, unordered_set<tuple<int, Modification *>>>
            for ( auto p: nonVariantProteins ) {         // vector<Protein*>
                for ( auto sv: p->getSequenceVariations() ) { // std::vector<SequenceVariation*>
                    std::vector<SequenceVariation *> t = {sv};
                    std::string s =VariantApplication::GetAccession(p, t);
                    if ( s == kv.first ) {
                        for ( auto k = std::get<1>(kv).begin(); k  != std::get<1>(kv).end() ; k++ ) {
                            allRelevantModifications.insert ( std::get<1>(*k));
                        }
                    }
                }
                if (kv.first == p->getAccession() ){
                    for ( auto k = std::get<1>(kv).begin(); k  != std::get<1>(kv).end() ; k++ ) {
                        allRelevantModifications.insert ( std::get<1>(*k));
                    }
                }
            }
        }
        
#ifdef ORIG
        //for (Modification *mod : allRelevantModifications.OrderBy([&] (std::any m)       {
        //            m::IdWithMotif;
        //        }))
#endif
        std::vector<Modification*> allRelevantModificationsVec(allRelevantModifications.begin(), allRelevantModifications.end());
        std::sort(allRelevantModificationsVec.begin(), allRelevantModificationsVec.end(), [&](auto *l, auto *r ) {
                return l->getIdWithMotif() < r->getIdWithMotif();
            } );

        for ( Modification *mod : allRelevantModificationsVec )
        {
            writer.WriteStartElement("modification");
            writer.WriteString(mod->ToString() + "\r\n" + "//");
            writer.WriteEndElement();
        }
        
        for (auto protein : nonVariantProteins)
        {
            writer.WriteStartElement("entry");
            writer.WriteStartElement("accession");
            writer.WriteString(protein->getAccession());
            writer.WriteEndElement();
            
            if (protein->getName() != "")
            {
                writer.WriteStartElement("name");
                writer.WriteString(protein->getName());
                writer.WriteEndElement();
            }
            
            if (protein->getFullName() != "")
            {
                writer.WriteStartElement("protein");
                writer.WriteStartElement("recommendedName");
                writer.WriteStartElement("fullName");
                writer.WriteString(protein->getFullName());
                writer.WriteEndElement();
                writer.WriteEndElement();
                writer.WriteEndElement();
            }
            
            writer.WriteStartElement("gene");
            for (auto gene_name : protein->getGeneNames())
            {
                writer.WriteStartElement("name");
                writer.WriteAttributeString("type", std::get<0>(gene_name));
                writer.WriteString(std::get<1>(gene_name));
                writer.WriteEndElement();
            }
            writer.WriteEndElement();
            
            if (protein->getOrganism() != "")
            {
                writer.WriteStartElement("organism");
                writer.WriteStartElement("name");
                writer.WriteAttributeString("type", "scientific");
                writer.WriteString(protein->getOrganism());
                writer.WriteEndElement();
                writer.WriteEndElement();
            }
            
            for (auto dbRef : protein->getDatabaseReferences())
            {
                writer.WriteStartElement("dbReference");
                writer.WriteAttributeString("type", dbRef->getType());
                writer.WriteAttributeString("id", dbRef->getId());
                writer.WriteStartElement("property");
                writer.WriteEndElement();
                writer.WriteEndElement();
            }
            for (auto proteolysisProduct : protein->getProteolysisProducts())
            {
                writer.WriteStartElement("feature");
                writer.WriteAttributeString("type", proteolysisProduct->getType());
                writer.WriteStartElement("location");
                writer.WriteStartElement("begin");
                writer.WriteAttributeString("position", std::to_string(proteolysisProduct->getOneBasedBeginPosition().value()));
                writer.WriteEndElement();
                writer.WriteStartElement("end");
                writer.WriteAttributeString("position", std::to_string(proteolysisProduct->getOneBasedEndPosition().value()));
                writer.WriteEndElement();
                writer.WriteEndElement();
                writer.WriteEndElement();
            }
            
            
#ifdef ORIG
            //for (auto hm : GetModsForThisProtein(protein, nullptr, additionalModsToAddToProteins, newModResEntries).OrderBy([&] (std::any b) {
            //            b::Key;
            //        }) {
#endif
            auto tmpvar = GetModsForThisProtein(protein, nullptr, additionalModsToAddToProteins, newModResEntries);
            std::map<int, std::unordered_set<std::string>> tmpvarOrdered ( tmpvar.begin(),  tmpvar.end() );
            
            for ( auto hm : tmpvarOrdered )
            {
                for (auto modId : hm.second)  {
                    writer.WriteStartElement("feature");
                    writer.WriteAttributeString("type", "modified residue");
                    writer.WriteAttributeString("description", modId);
                    writer.WriteStartElement("location");
                    writer.WriteStartElement("position");
                    writer.WriteAttributeString("position", std::to_string(hm.first));
                    writer.WriteEndElement();
                    writer.WriteEndElement();
                    writer.WriteEndElement();
                }
            }
            
            for (auto hm : protein->getSequenceVariations())
            {
                writer.WriteStartElement("feature");
                writer.WriteAttributeString("type", "sequence variant");
                writer.WriteAttributeString("description", hm->getDescription()->ToString());
                writer.WriteStartElement("original");
                writer.WriteString(hm->getOriginalSequence());
                writer.WriteEndElement(); // original
                writer.WriteStartElement("variation");
                writer.WriteString(hm->getVariantSequence());
                writer.WriteEndElement(); // variation
                writer.WriteStartElement("location");
                if (hm->getOneBasedBeginPosition() == hm->getOneBasedEndPosition())
                {
                    writer.WriteStartElement("position");
                    writer.WriteAttributeString("position", std::to_string(hm->getOneBasedBeginPosition()));
                    writer.WriteEndElement();
                }
                else
                {
                    writer.WriteStartElement("begin");
                    writer.WriteAttributeString("position", std::to_string(hm->getOneBasedBeginPosition()));
                    writer.WriteEndElement();
                    writer.WriteStartElement("end");
                    writer.WriteAttributeString("position", std::to_string(hm->getOneBasedEndPosition()));
                    writer.WriteEndElement();
                }
#ifdef ORIG
                //for (auto hmm : GetModsForThisProtein(protein, hm, additionalModsToAddToProteins, newModResEntries).OrderBy([&] (std::any b)
                // {
                //    b::Key;
                //}))
#endif
                auto tmp = GetModsForThisProtein(protein, hm, additionalModsToAddToProteins, newModResEntries);
                std::map<int, std::unordered_set<std::string>> tmpvarOrdered2 ( tmp.begin(),  tmp.end() );

                for ( auto hmm: tmpvarOrdered2 )
                {
                    for (auto modId : hmm.second)
                    {
                        writer.WriteStartElement("subfeature");
                        writer.WriteAttributeString("type", "modified residue");
                        writer.WriteAttributeString("description", modId);
                        writer.WriteStartElement("location");
                        writer.WriteStartElement("subposition");
                        writer.WriteAttributeString("subposition", std::to_string(hmm.first));
                        writer.WriteEndElement();
                        writer.WriteEndElement();
                        writer.WriteEndElement();
                    }
                }
                writer.WriteEndElement(); // location
                writer.WriteEndElement(); // feature
            }
            
            for (auto hm : protein->getDisulfideBonds())
            {
                writer.WriteStartElement("feature");
                writer.WriteAttributeString("type", "disulfide bond");
                writer.WriteAttributeString("description", hm->getDescription());
                writer.WriteStartElement("location");
                if (hm->getOneBasedBeginPosition() == hm->getOneBasedEndPosition())
                {
                    writer.WriteStartElement("position");
                    writer.WriteAttributeString("position", std::to_string(hm->getOneBasedBeginPosition()));
                    writer.WriteEndElement();
                }
                else
                {
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
            
            for (auto hm : protein->getSpliceSites())
            {
                writer.WriteStartElement("feature");
                writer.WriteAttributeString("type", "splice site");
                writer.WriteAttributeString("description", hm->getDescription());
                writer.WriteStartElement("location");
                if (hm->getOneBasedBeginPosition() == hm->getOneBasedEndPosition())
                {
                    writer.WriteStartElement("position");
                    writer.WriteAttributeString("position", std::to_string(hm->getOneBasedBeginPosition()));
                    writer.WriteEndElement();
                }
                else
                {
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
            writer.WriteAttributeString("length", std::to_string(protein->getLength()));
            writer.WriteString(protein->getBaseSequence());
            writer.WriteEndElement(); // sequence
            writer.WriteEndElement(); // entry
        }
        
        writer.WriteEndElement(); // mzLibProteinDb
        writer.WriteEndDocument();
        writer.Close();
        
        //C# TO C++ CONVERTER TODO TASK: A 'delete xmlWriterSettings' statement was not added since
        //xmlWriterSettings was passed to a method or constructor. Handle memory management manually.
        return newModResEntries;
    }
    
    
    void ProteinDbWriter::WriteFastaDatabase(std::vector<Protein*> &proteinList, const std::string &outputFileName,
                                             const std::string &delimeter)
    {
        std::ofstream writer(outputFileName);
        for (auto protein : proteinList)
        {
            std::string header = delimeter == " " ? protein->GetEnsemblFastaHeader() : protein->GetUniProtFastaHeader();
            writer << ">" << header << std::endl;
            writer << protein->getBaseSequence() << std::endl;
        }        
    }  
    
    std::unordered_map<int, std::unordered_set<std::string>> ProteinDbWriter::GetModsForThisProtein(
        Protein *protein,
        SequenceVariation *seqvar,
        std::unordered_map<std::string, std::unordered_set<ModDbTuple, ModDbTuple_hash, ModDbTuple_equal>> &additionalModsToAddToProteins,
        std::unordered_map<std::string, int> &newModResEntries)
    {
        auto modsToWriteForThisSpecificProtein = std::unordered_map<int, std::unordered_set<std::string>>();
        
        auto primaryModDict = seqvar == nullptr ? protein->getOneBasedPossibleLocalizedModifications() : seqvar->getOneBasedModifications();
        for (auto mods : primaryModDict)
        {
            for (auto mod : mods.second)
            {
                std::unordered_set<std::string> val;
                std::unordered_map<int, std::unordered_set<std::string>>::const_iterator modsToWriteForThisSpecificProtein_iterator = modsToWriteForThisSpecificProtein.find(mods.first);
                if (modsToWriteForThisSpecificProtein_iterator != modsToWriteForThisSpecificProtein.end())
                {
                    val = modsToWriteForThisSpecificProtein_iterator->second;
                    val.emplace(mod->getIdWithMotif());
                }
                else
                {
                    //val = modsToWriteForThisSpecificProtein_iterator->second;
                    std::unordered_set<std::string> tmp = {mod->getIdWithMotif()};
                    modsToWriteForThisSpecificProtein.emplace(mods.first, tmp);
                }
            }
        }

        std::vector<Proteomics::SequenceVariation*> tmp2 = {seqvar};
        std::string accession = seqvar == nullptr ? protein->getAccession() : VariantApplication::GetAccession(protein, tmp2);
        if (additionalModsToAddToProteins.find(accession) != additionalModsToAddToProteins.end())
        {
            for (auto ye : additionalModsToAddToProteins[accession])
            {
                int additionalModResidueIndex = std::get<0>(ye);
                std::string additionalModId = std::get<1>(ye)->getIdWithMotif();
                bool modAdded = false;

                // If we already have modifications that need to be written to the specific residue, get the hash set of those mods
                std::unordered_set<std::string> val;
                std::unordered_map<int, std::unordered_set<std::string>>::const_iterator modsToWriteForThisSpecificProtein_iterator = modsToWriteForThisSpecificProtein.find(additionalModResidueIndex);
                if (modsToWriteForThisSpecificProtein_iterator != modsToWriteForThisSpecificProtein.end())
                {
                    val = modsToWriteForThisSpecificProtein_iterator->second;
                    // Try to add the new mod to that hash set. If it's not there, modAdded=true, and it is added.
                    auto tmp4 = val.insert(additionalModId);
                    modAdded = std::get<1>(tmp4);
                }

                // Otherwise, no modifications currently need to be written to the residue at residueIndex,
                // so need to create new hash set for that residue
                else
                {
                    val = modsToWriteForThisSpecificProtein_iterator->second;
                    std::unordered_set<std::string> tmp3 = {additionalModId};
                    modsToWriteForThisSpecificProtein.emplace(additionalModResidueIndex, tmp3 );
                    modAdded = true;
                }

                // Finally, if a new modification has in fact been deemed worthy of being added to the database,
                // mark that in the output dictionary
                if (modAdded)
                {
                    if (newModResEntries.find(additionalModId) != newModResEntries.end())
                    {
                        newModResEntries[additionalModId]++;
                    }
                    else
                    {
                        newModResEntries.emplace(additionalModId, 1);
                    }
                }
            }
        }
        return modsToWriteForThisSpecificProtein;
    }
}
