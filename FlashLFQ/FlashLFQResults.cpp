#include <iostream>
#include <fstream>

#include "FlashLFQResults.h"
#include "SpectraFileInfo.h"
#include "Peptide.h"
#include "ProteinGroup.h"
#include "ChromatographicPeak.h"
#include "DetectionType.h"


namespace FlashLFQ
{

    FlashLfqResults::FlashLfqResults(std::vector<SpectraFileInfo*> &spectraFiles) : SpectraFiles(spectraFiles), PeptideModifiedSequences(std::unordered_map<std::string, Peptide*>()), ProteinGroups(std::unordered_map<std::string, ProteinGroup*>()), Peaks(std::unordered_map<SpectraFileInfo*, std::vector<ChromatographicPeak*>>())
    {
    }

    void FlashLfqResults::MergeResultsWith(FlashLfqResults *mergeFrom)
    {
        this->SpectraFiles.insert(this->SpectraFiles.end(), mergeFrom->SpectraFiles.begin(), mergeFrom->SpectraFiles.end());

        for (auto pep : mergeFrom->PeptideModifiedSequences)
        {
            std::unordered_map<std::string, Peptide*>::const_iterator PeptideModifiedSequences_iterator = this->PeptideModifiedSequences.find(std::get<0>(pep));
            if (PeptideModifiedSequences_iterator != this->PeptideModifiedSequences.end())
            {
                auto peptide = PeptideModifiedSequences_iterator->second;
                Peptide *mergeFromPep = std::get<1>(pep);
                Peptide *mergeToPep = peptide;

                for (auto file : mergeFrom->SpectraFiles)
                {
                    mergeToPep->SetIntensity(file, mergeFromPep->GetIntensity(file));
                    mergeToPep->SetDetectionType(file, mergeFromPep->GetDetectionType(file));
                }
            }
            else
            {
                //auto peptide = this->PeptideModifiedSequences_iterator->second;
                this->PeptideModifiedSequences.emplace(std::get<0>(pep), std::get<1>(pep));
            }
        }

        for (auto pg : mergeFrom->ProteinGroups)
        {
            //TValue proteinGroup;
            std::unordered_map<std::string, ProteinGroup*>::const_iterator ProteinGroups_iterator = this->ProteinGroups.find(std::get<0>(pg));
            if ( ProteinGroups_iterator != this->ProteinGroups.end())
            {
                auto proteinGroup = ProteinGroups_iterator->second;
                ProteinGroup *mergeFromPg = std::get<1>(pg);
                ProteinGroup *mergeToPg = proteinGroup;

                for (auto file : mergeFrom->SpectraFiles)
                {
                    mergeToPg->SetIntensity(file, mergeFromPg->GetIntensity(file));
                }
            }
            else
            {
                //proteinGroup = this->ProteinGroups_iterator->second;
                this->ProteinGroups.emplace(std::get<0>(pg), std::get<1>(pg));
            }
        }

        for (auto fromPeaks : mergeFrom->Peaks)
        {
            //TValue toPeaks;
            std::unordered_map<SpectraFileInfo*, std::vector<ChromatographicPeak*>>::const_iterator Peaks_iterator = this->Peaks.find(std::get<0>(fromPeaks));
            if ( Peaks_iterator != this->Peaks.end())
            {
                std::vector<ChromatographicPeak*>toPeaks = Peaks_iterator->second;
                //toPeaks->AddRange(std::get<1>(fromPeaks));
                for ( auto p: std::get<1>(fromPeaks) ) {
                    toPeaks.push_back(p);
                }
            }
            else
            {
                //toPeaks = this->Peaks_iterator->second;
                this->Peaks.emplace(std::get<0>(fromPeaks), std::get<1>(fromPeaks));
            }
        }
    }

    void FlashLfqResults::CalculatePeptideResults()
    {
        for (auto file : Peaks)
        {

#ifdef ORIG
            auto groupedPeaks = file.Value->Where([&] (std::any p)
            {
                return p->NumIdentificationsByFullSeq == 1;
            }).GroupBy([&] (std::any p)
            {
                p::Identifications::First().ModifiedSequence;
            }).ToList();
#endif
            std::vector<std::vector<ChromatographicPeak*>> groupedPeaks;
            for ( ChromatographicPeak* p : std::get<1>(file) ) {
                if ( p->getNumIdentificationsByFullSeq() == 1 ) {
                    bool found = false;
                    for (auto v: groupedPeaks ) {
                        if ( !v.empty() &&
                             v[0]->getIdentifications()[0]->ModifiedSequence ==
                             p->getIdentifications()[0]->ModifiedSequence ) {
                            found = true;
                            v.push_back(p);
                        }
                        if ( !found ) {
                            std::vector<ChromatographicPeak*> *t = new std::vector<ChromatographicPeak*>;
                            t->push_back(p);
                            groupedPeaks.push_back(*t);                            
                        }
                    }
                }
            }
            
            for (auto sequenceWithPeaks : groupedPeaks)
            {
                std::string sequence = sequenceWithPeaks[0]->getIdentifications()[0]->ModifiedSequence;
#ifdef ORIG
                double intensity = sequenceWithPeaks.Sum([&] (std::any p)
                {
                    p::Intensity;
                });
#endif
                double intensity = 0.0;
                for ( auto p: sequenceWithPeaks ) {
                    intensity += p->Intensity;
                    
                }
                DetectionType detectionType;
#ifdef ORIG
                auto pgs = std::unordered_set<ProteinGroup*>(sequenceWithPeaks.SelectMany([&] (std::any p)
                {
                    p::Identifications;
                }).SelectMany([&] (std::any v)
                {
                    v::proteinGroups;
                }));
#endif
                std::unordered_set<ProteinGroup*> pgs;
                std::vector<Identification *> ivec;
                for ( auto p : sequenceWithPeaks ) {
                    for ( auto v: p->getIdentifications() ) {
                        ivec.push_back (v);
                    }
                }
                for ( auto p: ivec ) {
                    for ( auto v : p->proteinGroups ) {
                        pgs.insert (v);
                    }
                }

                if (sequenceWithPeaks.front()->IsMbrPeak && intensity > 0)
                {
                    detectionType = DetectionType::MBR;
                }
                else if (!sequenceWithPeaks.front()->IsMbrPeak && intensity > 0)
                {
                    detectionType = DetectionType::MSMS;
                }
                else if (!sequenceWithPeaks.front()->IsMbrPeak && intensity == 0)
                {
                    detectionType = DetectionType::MSMSIdentifiedButNotQuantified;
                }
                else
                {
                    detectionType = DetectionType::NotDetected;
                }

                if (PeptideModifiedSequences.find(sequence) == PeptideModifiedSequences.end())
                {
                    bool useForProteinQuant = sequenceWithPeaks.front()->getIdentifications()[0]->UseForProteinQuant;
                    Peptide tempVar(sequence, useForProteinQuant);
                    PeptideModifiedSequences.emplace(sequence, &tempVar);
                }

                PeptideModifiedSequences[sequence]->SetIntensity(std::get<0>(file), intensity);
                PeptideModifiedSequences[sequence]->SetDetectionType(std::get<0>(file), detectionType);
                PeptideModifiedSequences[sequence]->proteinGroups = pgs;
            }

            // report ambiguous quantification
#ifdef ORIG
            auto ambiguousPeaks = file.Value->Where([&] (std::any p)
            {
                return p::NumIdentificationsByFullSeq > 1;
            }).ToList();
#endif
            std::vector<ChromatographicPeak*> ambiguousPeaks;
            for ( auto p: std::get<1>(file) ) {
                if ( p->getNumIdentificationsByFullSeq() > 1 ) {
                    ambiguousPeaks.push_back ( p);
                }
            }

            for (auto ambiguousPeak : ambiguousPeaks)
            {
                for (auto id : ambiguousPeak->getIdentifications())
                {
                    std::string sequence = id->ModifiedSequence;

                    if (PeptideModifiedSequences.find(sequence) == PeptideModifiedSequences.end())
                    {
                        bool useForProteinQuant = id->UseForProteinQuant;
                        Peptide tempVar2(sequence, useForProteinQuant);
                        PeptideModifiedSequences.emplace(sequence, &tempVar2);
                    }

                    double alreadyRecordedIntensity = PeptideModifiedSequences[sequence]->GetIntensity(std::get<0>(file));
                    double fractionAmbiguous = (ambiguousPeak->Intensity + alreadyRecordedIntensity) /
                        alreadyRecordedIntensity;

                    if (fractionAmbiguous > 0.3)
                    {
                        PeptideModifiedSequences[sequence]->SetIntensity(std::get<0>(file), 0);
                        PeptideModifiedSequences[sequence]->SetDetectionType(std::get<0>(file),
                                                                             DetectionType::MSMSAmbiguousPeakfinding);
                        PeptideModifiedSequences[sequence]->proteinGroups = id->proteinGroups;
                    }
                }
            }
        }
    }

    void FlashLfqResults::CalculateProteinResultsTop3()
    {
        int topNPeaks = 3;

#ifdef ORIG
        std::vector<ProteinGroup*> allProteinGroups = Peaks.Values->SelectMany([&] (std::any p)
        {
            return p;
        }).SelectMany([&] (std::any p)
        {
            p::Identifications;
        }).SelectMany([&] (std::any p)
        {
            p::proteinGroups;
        }).Distinct().ToList();
#endif
        //1st SelectMany: flatmap the Chromatographic Peaks
        std::vector<ChromatographicPeak*> tPeaks;
        for ( auto p : Peaks ) {
            for ( auto v : std::get<1>(p) ) {
                tPeaks.push_back (v);
            }
        }
        // 2nd SelectMany: extract Identifications.
        std::vector<Identification *> ivec;
        for ( auto p: tPeaks ) {
            for ( auto v: p->getIdentifications() ) {
                ivec.push_back(v);
            }
        }
        // 3rd SelectMany: extract proteinGroups;
        std::vector<ProteinGroup*> allProteinGroups;
        for ( auto p : ivec ) {
            for ( auto v: p->proteinGroups ) {
                allProteinGroups.push_back(v );
            }
        }
        //Distinct.
        std::sort(allProteinGroups.begin(), allProteinGroups.end() );
        auto ip = std::unique (allProteinGroups.begin(), allProteinGroups.end() );
        allProteinGroups.erase(ip, allProteinGroups.end());
        
        for (auto pg : allProteinGroups)
        {
            ProteinGroups.emplace(pg->ProteinGroupName, pg);
        }

#ifdef ORIG
        std::vector<ChromatographicPeak*> unambiguousPeaks = Peaks.Values->SelectMany([&] (std::any p)
        {
            return p;
        }).Where([&] (std::any p)
        {
            return p->NumIdentificationsByFullSeq == 1 && p::Intensity > 0;
        }).ToList();
#endif
        std::vector<ChromatographicPeak*> unambiguousPeaks;
        for ( auto p : Peaks) {
            for ( ChromatographicPeak* v: std::get<1>(p) ) {
                if ( v->getNumIdentificationsByFullSeq() == 1 && v->Intensity > 0 ) {
                    unambiguousPeaks.push_back(v);
                }
            }
        }

        std::unordered_map<ProteinGroup*, std::vector<ChromatographicPeak*>> proteinGroupToPeaks;
        for (auto peak : unambiguousPeaks)
        {
            auto id = peak->getIdentifications().front();
            if (!id->UseForProteinQuant)
            {
                continue;
            }

            for (ProteinGroup *pg : id->proteinGroups)
            {
                //TValue peaks;
                std::unordered_map<ProteinGroup*, std::vector<ChromatographicPeak*>>::const_iterator proteinGroupToPeaks_iterator = proteinGroupToPeaks.find(pg);
                if (proteinGroupToPeaks_iterator != proteinGroupToPeaks.end())
                {
                    auto peaks = proteinGroupToPeaks_iterator->second;
                    //peaks->Add(peak);
                    peaks.push_back(peak);
                }
                else
                {
                    //peaks = proteinGroupToPeaks_iterator->second;
                    proteinGroupToPeaks.emplace(pg, std::vector<ChromatographicPeak*> {peak});
                }
            }
        }

        for (auto pg : ProteinGroups)
        {
            //TValue proteinGroupPeaks;
            std::unordered_map<ProteinGroup*, std::vector<ChromatographicPeak*>>::const_iterator proteinGroupToPeaks_iterator = proteinGroupToPeaks.find(std::get<1>(pg));
            if (proteinGroupToPeaks_iterator != proteinGroupToPeaks.end())
            {
                auto proteinGroupPeaks = proteinGroupToPeaks_iterator->second;
                auto peaksGroupedByFile = proteinGroupPeaks::GroupBy([&] (std::any p)
                {
                    p::SpectraFileInfo;
                }).ToList();

#ifdef NEW_BUT_NOT_READY
                std::vector<std::unordered_map<ProteinGroup*, std::vector<ChromatographicPeak*>>> peaksGroupedByFile;
                std::unordered_map<ProteinGroup*, std::vector<ChromatographicPeak*>> proteinGroupToPeaks;
                std::sort(proteinGroupPeaks.begin(), proteinGroupPeaks.end(), [&]
                          ( ChromatographicPeak* l, ChromatographicPeak* r ) {
                              return l->spectralFileInfo < r->spectralFileInfo;
                          });
                for ( auto p : proteinGroupPeaks ) {
                    if ( peaksGroupedByFile.empty() ) {
                        std::unordered_map<ProteinGroup*, std::vector<ChromatographicPeak*>> *v = new std::unordered_map<ProteinGroup*, std::vector<ChromatographicPeak*>>;
                        v->insert(p);
                        peaksGroupedByFile.push_back(*v);
                        continue;
                    }
                }
#endif
                
                for (auto peaksForThisPgAndFile : peaksGroupedByFile)
                {
                    SpectraFileInfo *file = peaksForThisPgAndFile.begin()->spectraFileInfo;

                    // top N peaks, prioritizing protein-uniqueness and then intensity
                    double proteinIntensity = peaksForThisPgAndFile.OrderBy([&] (std::any p)
                    {
                        p::Identifications::SelectMany([&] (std::any v)
                        {
                            v::proteinGroups;
                        }).Distinct()->Count();
                    }).ThenByDescending([&] (std::any p)
                    {
                        p::Intensity;
                    }).Take(topNPeaks).Sum([&] (std::any p)
                    {
                        p::Intensity;
                    });

                    pg->Value->SetIntensity(file, proteinIntensity);
                }
            }
            //else
            //{
                //proteinGroupPeaks = proteinGroupToPeaks_iterator->second;
            //}
        }
    }

    void FlashLfqResults::WriteResults(const std::string &peaksOutputPath,
                                       const std::string &modPeptideOutputPath,
                                       const std::string &proteinOutputPath)
    {
        if (peaksOutputPath != "")
        {
#ifdef ORIG
            StreamWriter output = StreamWriter(peaksOutputPath);
            output.WriteLine(ChromatographicPeak::getTabSeparatedHeader());
#endif
            std::ofstream output (peaksOutputPath);
            output << ChromatographicPeak::getTabSeparatedHeader() << std::endl;

#ifdef ORIG
            for (auto peak : Peaks.SelectMany([&] (std::any p)         {
                        p->Value;
                    }))    {
                output.WriteLine(peak.ToString());
            }
#endif
            std::vector<ChromatographicPeak*> tPeaks;
            for ( auto p : Peaks ) {
                for ( auto v : std::get<1>(p) ){
                    tPeaks.push_back(v);
                }
            }
            for ( auto peak : tPeaks ) {
                output << peak->ToString() << std::endl;
            }
            output.close();
        }
        

        if (modPeptideOutputPath != "")
        {
#ifdef ORIG
            StreamWriter output = StreamWriter(modPeptideOutputPath);
            output.WriteLine(Peptide::TabSeparatedHeader(SpectraFiles));
#endif
            std::ofstream output (modPeptideOutputPath);
            output  << Peptide::TabSeparatedHeader(SpectraFiles) << std::endl;
#ifdef ORIG
            for (auto peptide : PeptideModifiedSequences.OrderBy([&] (std::any p)    {
                        p::Key;
                    }))     {
                output.WriteLine(peptide->Value->ToString(SpectraFiles));
            }
#endif
            std::map<std::string, Peptide*> tpS ( PeptideModifiedSequences.begin(), PeptideModifiedSequences.end());
            for ( auto peptide :tpS ) {
                output << std::get<1>(peptide)->ToString(SpectraFiles) << std::endl;
            }
            output.close();
        }

        if (proteinOutputPath != "")
        {
#ifdef ORIG
            StreamWriter output = StreamWriter(proteinOutputPath);
            output.WriteLine(ProteinGroup::TabSeparatedHeader(SpectraFiles));
#endif     
            std::ofstream output (modPeptideOutputPath);
            output << ProteinGroup::TabSeparatedHeader(SpectraFiles) << std::endl;
                
#ifdef ORIG
            for (auto protein : ProteinGroups.OrderBy([&] (std::any p)  {
                        p::Key;
                    }))  {
                output.WriteLine(protein->Value->ToString(SpectraFiles));
            }
#endif
            std::map<std::string, ProteinGroup*> tP (ProteinGroups.begin(), ProteinGroups.end());
            for ( auto protein : tP ) {
                output << std::get<1>(protein)->ToString(SpectraFiles) << std::endl;
            }
            output.close();
        }
    }
}
