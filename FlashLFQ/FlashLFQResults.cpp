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
            TValue peptide;
            std::unordered_map<std::string, Peptide*>::const_iterator this.PeptideModifiedSequences_iterator = this.PeptideModifiedSequences.find(pep.Key);
            if (this->PeptideModifiedSequences_iterator != this->PeptideModifiedSequences.end())
            {
                peptide = this->PeptideModifiedSequences_iterator->second;
                Peptide *mergeFromPep = pep->Value;
                Peptide *mergeToPep = peptide;

                for (auto file : mergeFrom->SpectraFiles)
                {
                    mergeToPep->SetIntensity(file, mergeFromPep->GetIntensity(file));
                    mergeToPep->SetDetectionType(file, mergeFromPep->GetDetectionType(file));
                }
            }
            else
            {
                peptide = this->PeptideModifiedSequences_iterator->second;
                this->PeptideModifiedSequences.emplace(pep->Key, pep->Value);
            }
        }

        for (auto pg : mergeFrom->ProteinGroups)
        {
            TValue proteinGroup;
            std::unordered_map<std::string, ProteinGroup*>::const_iterator this.ProteinGroups_iterator = this.ProteinGroups.find(pg.Key);
            if (this->ProteinGroups_iterator != this->ProteinGroups.end())
            {
                proteinGroup = this->ProteinGroups_iterator->second;
                ProteinGroup *mergeFromPg = pg->Value;
                ProteinGroup *mergeToPg = proteinGroup;

                for (auto file : mergeFrom->SpectraFiles)
                {
                    mergeToPg->SetIntensity(file, mergeFromPg->GetIntensity(file));
                }
            }
            else
            {
                proteinGroup = this->ProteinGroups_iterator->second;
                this->ProteinGroups.emplace(pg->Key, pg->Value);
            }
        }

        for (auto fromPeaks : mergeFrom->Peaks)
        {
            TValue toPeaks;
            std::unordered_map<SpectraFileInfo*, std::vector<ChromatographicPeak*>>::const_iterator this.Peaks_iterator = this.Peaks.find(fromPeaks.Key);
            if (this->Peaks_iterator != this->Peaks.end())
            {
                toPeaks = this->Peaks_iterator->second;
                toPeaks->AddRange(fromPeaks.Value);
            }
            else
            {
                toPeaks = this->Peaks_iterator->second;
                this->Peaks.emplace(fromPeaks.Key, fromPeaks.Value);
            }
        }
    }

    void FlashLfqResults::CalculatePeptideResults()
    {
        for (auto file : Peaks)
        {
            auto groupedPeaks = file.Value->Where([&] (std::any p)
            {
                return p->NumIdentificationsByFullSeq == 1;
            }).GroupBy([&] (std::any p)
            {
                p::Identifications::First().ModifiedSequence;
            }).ToList();

            for (auto sequenceWithPeaks : groupedPeaks)
            {
                std::string sequence = sequenceWithPeaks.Key;
                double intensity = sequenceWithPeaks.Sum([&] (std::any p)
                {
                    p::Intensity;
                });
                DetectionType detectionType;
                auto pgs = std::unordered_set<ProteinGroup*>(sequenceWithPeaks.SelectMany([&] (std::any p)
                {
                    p::Identifications;
                }).SelectMany([&] (std::any v)
                {
                    v::proteinGroups;
                }));

                if (sequenceWithPeaks.First().IsMbrPeak && intensity > 0)
                {
                    detectionType = DetectionType::MBR;
                }
                else if (!sequenceWithPeaks.First().IsMbrPeak && intensity > 0)
                {
                    detectionType = DetectionType::MSMS;
                }
                else if (!sequenceWithPeaks.First().IsMbrPeak && intensity == 0)
                {
                    detectionType = DetectionType::MSMSIdentifiedButNotQuantified;
                }
                else
                {
                    detectionType = DetectionType::NotDetected;
                }

                if (PeptideModifiedSequences.find(sequence) == PeptideModifiedSequences.end())
                {
                    bool useForProteinQuant = sequenceWithPeaks.First().Identifications::First().UseForProteinQuant;
                    Peptide tempVar(sequence, useForProteinQuant);
                    PeptideModifiedSequences.emplace(sequence, &tempVar);
                }

                PeptideModifiedSequences[sequence]->SetIntensity(file.Key, intensity);
                PeptideModifiedSequences[sequence]->SetDetectionType(file.Key, detectionType);
                PeptideModifiedSequences[sequence]->proteinGroups = pgs;
            }

            // report ambiguous quantification
            auto ambiguousPeaks = file.Value->Where([&] (std::any p)
            {
                return p::NumIdentificationsByFullSeq > 1;
            }).ToList();
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

                    double alreadyRecordedIntensity = PeptideModifiedSequences[sequence]->GetIntensity(file.Key);
                    double fractionAmbiguous = (ambiguousPeak->Intensity + alreadyRecordedIntensity) / alreadyRecordedIntensity;

                    if (fractionAmbiguous > 0.3)
                    {
                        PeptideModifiedSequences[sequence]->SetIntensity(file.Key, 0);
                        PeptideModifiedSequences[sequence]->SetDetectionType(file.Key, DetectionType::MSMSAmbiguousPeakfinding);
                        PeptideModifiedSequences[sequence]->proteinGroups = id->proteinGroups;
                    }
                }
            }
        }
    }

    void FlashLfqResults::CalculateProteinResultsTop3()
    {
        int topNPeaks = 3;

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

        for (auto pg : allProteinGroups)
        {
            ProteinGroups.emplace(pg->ProteinGroupName, pg);
        }

        std::vector<ChromatographicPeak*> unambiguousPeaks = Peaks.Values->SelectMany([&] (std::any p)
        {
            return p;
        }).Where([&] (std::any p)
        {
            return p->NumIdentificationsByFullSeq == 1 && p::Intensity > 0;
        }).ToList();
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
                TValue peaks;
                std::unordered_map<ProteinGroup*, std::vector<ChromatographicPeak*>>::const_iterator proteinGroupToPeaks_iterator = proteinGroupToPeaks.find(pg);
                if (proteinGroupToPeaks_iterator != proteinGroupToPeaks.end())
                {
                    peaks = proteinGroupToPeaks_iterator->second;
                    peaks->Add(peak);
                }
                else
                {
                    peaks = proteinGroupToPeaks_iterator->second;
                    proteinGroupToPeaks.emplace(pg, std::vector<ChromatographicPeak*> {peak});
                }
            }
        }

        for (auto pg : ProteinGroups)
        {
            TValue proteinGroupPeaks;
            std::unordered_map<ProteinGroup*, std::vector<ChromatographicPeak*>>::const_iterator proteinGroupToPeaks_iterator = proteinGroupToPeaks.find(pg.Value);
            if (proteinGroupToPeaks_iterator != proteinGroupToPeaks.end())
            {
                proteinGroupPeaks = proteinGroupToPeaks_iterator->second;
                auto peaksGroupedByFile = proteinGroupPeaks::GroupBy([&] (std::any p)
                {
                    p::SpectraFileInfo;
                }).ToList();

                for (auto peaksForThisPgAndFile : peaksGroupedByFile)
                {
                    SpectraFileInfo *file = peaksForThisPgAndFile.First().SpectraFileInfo;

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
            else
            {
                proteinGroupPeaks = proteinGroupToPeaks_iterator->second;
            }
        }
    }

    void FlashLfqResults::WriteResults(const std::string &peaksOutputPath, const std::string &modPeptideOutputPath, const std::string &proteinOutputPath)
    {
        if (peaksOutputPath != "")
        {
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (StreamWriter output = new StreamWriter(peaksOutputPath))
            {
                StreamWriter output = StreamWriter(peaksOutputPath);
                output.WriteLine(ChromatographicPeak::getTabSeparatedHeader());

                for (auto peak : Peaks.SelectMany([&] (std::any p)
                {
                    p->Value;
                }))
                {
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
                    output.WriteLine(peak.ToString());
                }
            }
        }

        if (modPeptideOutputPath != "")
        {
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (StreamWriter output = new StreamWriter(modPeptideOutputPath))
            {
                StreamWriter output = StreamWriter(modPeptideOutputPath);
                output.WriteLine(Peptide::TabSeparatedHeader(SpectraFiles));

                for (auto peptide : PeptideModifiedSequences.OrderBy([&] (std::any p)
                {
                    p::Key;
                }))
                {
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
                    output.WriteLine(peptide->Value->ToString(SpectraFiles));
                }
            }
        }

        if (proteinOutputPath != "")
        {
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (StreamWriter output = new StreamWriter(proteinOutputPath))
            {
                StreamWriter output = StreamWriter(proteinOutputPath);
                output.WriteLine(ProteinGroup::TabSeparatedHeader(SpectraFiles));

                for (auto protein : ProteinGroups.OrderBy([&] (std::any p)
                {
                    p::Key;
                }))
                {
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
                    output.WriteLine(protein->Value->ToString(SpectraFiles));
                }
            }
        }
    }
}
