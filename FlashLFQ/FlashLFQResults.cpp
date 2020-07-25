#include <iostream>
#include <fstream>
#include <iomanip>

#include "FlashLFQResults.h"
#include "SpectraFileInfo.h"
#include "Peptide.h"
#include "ProteinGroup.h"
#include "ChromatographicPeak.h"
#include "DetectionType.h"

#include "Group.h"

namespace FlashLFQ
{

    FlashLfqResults::FlashLfqResults(std::vector<SpectraFileInfo*> &spectraFiles) :
        SpectraFiles(spectraFiles),
        PeptideModifiedSequences(std::unordered_map<std::string, Peptide*>()),
        ProteinGroups(std::unordered_map<std::string, ProteinGroup*>()),
        Peaks(std::unordered_map<SpectraFileInfo*, std::vector<ChromatographicPeak*>>())
    {
    }

    void FlashLfqResults::MergeResultsWith(FlashLfqResults *mergeFrom)
    {
        this->SpectraFiles.insert(this->SpectraFiles.end(),
                                  mergeFrom->SpectraFiles.begin(), mergeFrom->SpectraFiles.end());

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
            std::vector<ChromatographicPeak*> tmpPeaks;
            for ( ChromatographicPeak* p : std::get<1>(file) ) {
                if ( p->getNumIdentificationsByFullSeq() == 1 ) {
                    tmpPeaks.push_back(p);
                }
            }

            std::function<bool(ChromatographicPeak*,ChromatographicPeak*)> f1 = [&]
                ( ChromatographicPeak* l, ChromatographicPeak* r ) {
                return l->getIdentifications()[0]->ModifiedSequence < r->getIdentifications()[0]->ModifiedSequence; };
            std::function<bool(ChromatographicPeak*,ChromatographicPeak*)> f2 = [&]
                ( ChromatographicPeak* l, ChromatographicPeak* r ) {
                return l->getIdentifications()[0]->ModifiedSequence != r->getIdentifications()[0]->ModifiedSequence; };
            std::vector< std::vector<ChromatographicPeak*>> groupedPeaks = Group::GroupBy ( tmpPeaks, f1, f2);                        
            
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
                    auto  tempVar = new Peptide(sequence, useForProteinQuant);
                    PeptideModifiedSequences.emplace(sequence, tempVar);
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
                        auto  tempVar2 = new Peptide(sequence, useForProteinQuant);
                        PeptideModifiedSequences.emplace(sequence, tempVar2);
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
                bool found = false;
                for ( auto q: allProteinGroups ) {
                    if ( v->Equals(q) ){
                        found = true;
                        break;
                    }
                }
                if ( !found ) {
                    allProteinGroups.push_back(v );
                }
            }
        }
        //Distinct.
        //Edgar: Done already in the step above now.
        //std::sort(allProteinGroups.begin(), allProteinGroups.end(), [&](auto l, auto r ) {
        //        return l->ProteinGroupName < r->ProteinGroupName; });

        // auto ip = std::unique (allProteinGroups.begin(), allProteinGroups.end() );
        //allProteinGroups.erase(ip, allProteinGroups.end());
        
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
                std::unordered_map<ProteinGroup*, std::vector<ChromatographicPeak*>>::iterator proteinGroupToPeaks_iterator = proteinGroupToPeaks.find(pg);
                if (proteinGroupToPeaks_iterator != proteinGroupToPeaks.end())
                {
                    std::vector<ChromatographicPeak*> &peaks = proteinGroupToPeaks_iterator->second;
                    //peaks->Add(peak);
                    peaks.push_back(peak);
                }
                else
                {
                    proteinGroupToPeaks.emplace(pg, std::vector<ChromatographicPeak*> {peak});
                }
            }
        }

        for (auto pg : ProteinGroups)
        {
            //TValue proteinGroupPeaks;
            std::unordered_map<ProteinGroup*, std::vector<ChromatographicPeak*>>::iterator proteinGroupToPeaks_iterator = proteinGroupToPeaks.find(std::get<1>(pg));
            if (proteinGroupToPeaks_iterator != proteinGroupToPeaks.end())
            {
                std::vector<ChromatographicPeak*> &proteinGroupPeaks = proteinGroupToPeaks_iterator->second;
#ifdef ORIG
                auto peaksGroupedByFile = proteinGroupPeaks::GroupBy([&] (std::any p)
                {
                    p::SpectraFileInfo;
                }).ToList();
#endif

                std::function<bool(ChromatographicPeak*,ChromatographicPeak*)> f1 = [&]
                          ( ChromatographicPeak* l, ChromatographicPeak* r ) {
                    return l->spectraFileInfo < r->spectraFileInfo; };
                std::function<bool(ChromatographicPeak*,ChromatographicPeak*)> f2 = [&]
                          ( ChromatographicPeak* l, ChromatographicPeak* r ) {
                    return l->spectraFileInfo != r->spectraFileInfo; };
                std::vector< std::vector<ChromatographicPeak*>> peaksGroupedByFile = Group::GroupBy ( proteinGroupPeaks, f1, f2);
                
                for (auto peaksForThisPgAndFile : peaksGroupedByFile)
                {
                    SpectraFileInfo *file = peaksForThisPgAndFile.front()->spectraFileInfo;

#ifdef ORIG
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
#endif
                    // Step 1: Order by the number of entries having the same v->proteinGroups
                    // and then by p->Intenisity descending order
                    std::vector<std::tuple<ChromatographicPeak*, int, double>> peaksVec;
                    for ( auto p : peaksForThisPgAndFile ) {
                        std::vector<Identification*> idVec;
                        for ( auto v: p->getIdentifications() ) {
                            bool found = false;
                            for ( auto w: idVec ) {
                                if ( w->proteinGroups.size() != v->proteinGroups.size() ) break;
                                for ( auto pp:  w->proteinGroups ) {
                                    bool equal = false;
                                    for ( auto qq: v->proteinGroups ) {
                                        if ( pp->Equals(qq) ){
                                            equal = true;
                                            break;
                                        }
                                    }
                                    if ( !equal ) {
                                        //Could not find this element, proteinGroups can not be identical
                                        break;
                                    }
                                }
                            }
                            if ( !found ) {
                                idVec.push_back(v);
                            }
                        }
                        peaksVec.push_back( std::make_tuple(p, (int)idVec.size(), p->Intensity) );
                    }
                    std::sort(peaksVec.begin(), peaksVec.end(), [&]
                              ( std::tuple<ChromatographicPeak*, int, double> l,
                                std::tuple<ChromatographicPeak*, int, double> r ) {
                                  if ( std::get<1>(l) < std::get<1>(r) ) return true;
                                  if ( std::get<1>(l) > std::get<1>(r) ) return false;
                                  return std::get<2>(l) > std::get<2>(r);
                              }
                        );
                    // Step 2: take topNPeaks and determine sum;
                    double proteinIntensity =0.0;
                    for ( int i=0; i<topNPeaks; i++  ) {
                        proteinIntensity += std::get<2>(peaksVec[i]);
                    }
                    std::get<1>(pg)->SetIntensity(file, proteinIntensity);
                }
            }
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
