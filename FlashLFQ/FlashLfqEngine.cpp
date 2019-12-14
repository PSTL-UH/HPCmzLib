#include "FlashLfqEngine.h"
#include "SpectraFileInfo.h"
#include "Identification.h"
#include "FlashLFQResults.h"
#include "Ms1ScanInfo.h"
#include "PeakIndexingEngine.h"
#include "../UsefulProteomicsDatabases/Loaders.h"
#include "IntensityNormalizationEngine.h"
#include "../MzLibUtil/MzLibException.h"
#include "ProteinQuantificationEngine.h"
#include "../Proteomics/AminoAcidPolymer/Peptide.h"
#include "../Chemistry/IsotopicDistribution.h"
#include "../MzLibUtil/Tolerance.h"
#include "ChromatographicPeak.h"
#include "ProteinGroup.h"
#include "RetentionTimeCalibDataPoint.h"
#include "IndexedMassSpectralPeak.h"
#include "IsotopicEnvelope.h"
#include "../Chemistry/ClassExtensions.h"
#include "../Chemistry/Constants.h"

using namespace Chemistry;
using namespace MathNet::Numerics::Statistics;
using namespace MzLibUtil;
using namespace UsefulProteomicsDatabases;

namespace FlashLFQ
{

    FlashLfqEngine::FlashLfqEngine(std::vector<Identification*> &allIdentifications, bool normalize, bool advancedProteinQuant, bool matchBetweenRuns, double ppmTolerance, double isotopeTolerancePpm, double matchBetweenRunsPpmTolerance, bool integrate, int numIsotopesRequired, bool idSpecificChargeState, bool requireMonoisotopicMass, bool silent, const std::string &optionalPeriodicTablePath, double maxMbrWindow, int maxThreads) : Silent(silent), MaxThreads(maxThreads), PeakfindingPpmTolerance(20.0), PpmTolerance(ppmTolerance), RtTol(5.0), IsotopePpmTolerance(isotopeTolerancePpm), Integrate(integrate), MissedScansAllowed(1), NumIsotopesRequired(numIsotopesRequired), MbrRtWindow(maxMbrWindow), MbrPpmTolerance(matchBetweenRunsPpmTolerance), ErrorCheckAmbiguousMatches(true), MatchBetweenRuns(matchBetweenRuns), IdSpecificChargeState(idSpecificChargeState), RequireMonoisotopicMass(requireMonoisotopicMass), Normalize(normalize), MinDiscFactorToCutAt(0.6), AdvancedProteinQuant(advancedProteinQuant)
    {
        if (optionalPeriodicTablePath == "")
        {
            optionalPeriodicTablePath = FileSystem::combine(AppDomain::CurrentDomain->BaseDirectory, R"(elements.dat)");
        }

        Loaders::LoadElements(optionalPeriodicTablePath);

        _globalStopwatch = new Stopwatch();
        _chargeStates = std::vector<int>();
        _peakIndexingEngine = new PeakIndexingEngine();

        _spectraFileInfo = allIdentifications.Select([&] (std::any p)
        {
            p::fileInfo;
        }).Distinct().OrderBy([&] (std::any p)
        {
            p::Condition;
        }).ThenBy([&] (std::any p)
        {
            p::BiologicalReplicate;
        }).ThenBy([&] (std::any p)
        {
            p::Fraction;
        }).ThenBy([&] (std::any p)
        {
            p::TechnicalReplicate;
        }).ToList();

        _allIdentifications = allIdentifications;

        if (MaxThreads == -1 || MaxThreads >= Environment::ProcessorCount)
        {
            MaxThreads = Environment::ProcessorCount - 1;
        }

        if (MaxThreads <= 0)
        {
            MaxThreads = 1;
        }

    }

    FlashLfqResults *FlashLfqEngine::Run()
    {
        _globalStopwatch->Start();
        _ms1Scans = std::unordered_map<SpectraFileInfo*, std::vector<Ms1ScanInfo*>>();

        _results = new FlashLfqResults(_spectraFileInfo);

        // build m/z index keys
        CalculateTheoreticalIsotopeDistributions();

        // quantify each file
        for (auto spectraFile : _spectraFileInfo)
        {
            // fill lookup-table with peaks from the spectra file
            if (!_peakIndexingEngine->IndexMassSpectralPeaks(spectraFile, Silent, _ms1Scans))
            {
                // something went wrong finding/opening/indexing the file...
                continue;
            }

            // quantify peaks using this file's IDs first
            QuantifyMs2IdentifiedPeptides(spectraFile);

            // write the indexed peaks for MBR later
            if (MatchBetweenRuns)
            {
                _peakIndexingEngine->SerializeIndex(spectraFile);
            }

            // error checking function
            // handles features with multiple identifying scans and scans that are associated with more than one feature
            RunErrorChecking(spectraFile);

            if (!Silent)
            {
                std::cout << "Finished " << spectraFile->FilenameWithoutExtension << std::endl;
            }

            // some memory-saving stuff
            _peakIndexingEngine->ClearIndex();
        }

        // do MBR
        if (MatchBetweenRuns)
        {
            for (auto spectraFile : _spectraFileInfo)
            {
                if (!Silent)
                {
                    std::cout << "Doing match-between-runs for " << spectraFile->FilenameWithoutExtension << std::endl;
                }

                QuantifyMatchBetweenRunsPeaks(spectraFile);

                _peakIndexingEngine->ClearIndex();

                if (!Silent)
                {
                    std::cout << "Finished MBR for " << spectraFile->FilenameWithoutExtension << std::endl;
                }
            }
        }

        // normalize
        if (Normalize)
        {
            try
            {
                IntensityNormalizationEngine tempVar(_results, Integrate, Silent, MaxThreads);
                (&tempVar)->NormalizeResults();
            }
            catch (const std::runtime_error &e)
            {
                throw MzLibException("A crash occured in FlashLFQ during the intensity normalization process:\n" + e.what());
            }
        }

        // calculate intensities for proteins/peptides
        _results->CalculatePeptideResults();

        if (AdvancedProteinQuant)
        {
            ProteinQuantificationEngine tempVar2(_results, MaxThreads);
            (&tempVar2)->Run();
        }
        else
        {
            _results->CalculateProteinResultsTop3();
        }

        // done
        if (!Silent)
        {
            std::cout << "Done quantifying" << std::endl;
        }

        if (!Silent)
        {
            std::cout << "Analysis time: " << _globalStopwatch->Elapsed.Hours << "h " << _globalStopwatch->Elapsed.Minutes << "m " << _globalStopwatch->Elapsed.Seconds << "s" << std::endl;
        }

        return _results;
    }

    void FlashLfqEngine::CalculateTheoreticalIsotopeDistributions()
    {
        _baseSequenceToIsotopicDistribution = std::unordered_map<std::string, std::vector<KeyValuePair<double, double>*>>();

        // calculate monoisotopic masses and isotopic envelope
        for (auto id : _allIdentifications)
        {
            if (_baseSequenceToIsotopicDistribution.find(id->BaseSequence) != _baseSequenceToIsotopicDistribution.end())
            {
                continue;
            }

            auto formula = id->OptionalChemicalFormula;

            auto isotopicMassesAndNormalizedAbundances = std::vector<KeyValuePair<double, double>*>();

            Proteomics::AminoAcidPolymer::Peptide *p = new Proteomics::AminoAcidPolymer::Peptide(id->BaseSequence);

            if (formula == nullptr)
            {
                formula = p->GetChemicalFormula();
            }

            auto isotopicDistribution = IsotopicDistribution::GetDistribution(formula, 0.125, 1e-8);

            std::vector<double> masses = isotopicDistribution->getMasses().ToArray();
            std::vector<double> abundances = isotopicDistribution->getIntensities().ToArray();

            double unmodifiedMonoisotopicMass = p->getMonoisotopicMass();
            double highestAbundance = abundances.Max();

            for (int i = 0; i < masses.size(); i++)
            {
                // expected isotopic mass shifts for this peptide
                masses[i] -= unmodifiedMonoisotopicMass;

                // normalized abundance of each isotope
                abundances[i] /= highestAbundance;

                // look for these isotopes
                if (isotopicMassesAndNormalizedAbundances.size() < NumIsotopesRequired || abundances[i] > 0.1)
                {
                    isotopicMassesAndNormalizedAbundances.push_back(KeyValuePair<double, double>(masses[i], abundances[i]));
                }
            }

            _baseSequenceToIsotopicDistribution.emplace(id->BaseSequence, isotopicMassesAndNormalizedAbundances);

            delete p;
        }

        auto minChargeState = _allIdentifications.Min([&] (std::any p)
        {
            p::precursorChargeState;
        });
        auto maxChargeState = _allIdentifications.Max([&] (std::any p)
        {
            p::precursorChargeState;
        });
        _chargeStates = Enumerable::Range(minChargeState, (maxChargeState - minChargeState) + 1);

        auto peptideModifiedSequences = _allIdentifications.GroupBy([&] (std::any p)
        {
            p::ModifiedSequence;
        });
        for (auto identifications : peptideModifiedSequences)
        {
            // isotope where normalized abundance is 1
            double mostAbundantIsotopeShift = _baseSequenceToIsotopicDistribution[identifications->First().BaseSequence].First([&] (std::any p)
            {
                return p->Value == 1.0;
            }).Key;

            double thisPeptidesMostAbundantMass = identifications->First().monoisotopicMass + mostAbundantIsotopeShift;

            for (auto identification : identifications)
            {
                identification->massToLookFor = RequireMonoisotopicMass ? identification->monoisotopicMass : thisPeptidesMostAbundantMass;
            }
        }
    }

    void FlashLfqEngine::QuantifyMs2IdentifiedPeptides(SpectraFileInfo *fileInfo)
    {
        if (!Silent)
        {
            std::cout << "Quantifying peptides for " << fileInfo->FilenameWithoutExtension << std::endl;
        }

        auto ms2IdsForThisFile = _allIdentifications.Where([&] (std::any p)
        {
            p::fileInfo->Equals(fileInfo);
        }).ToList();

        if (!ms2IdsForThisFile.Any())
        {
            return;
        }

        Tolerance *peakfindingTol = new PpmTolerance(PeakfindingPpmTolerance);
        Tolerance *ppmTolerance = new PpmTolerance(PpmTolerance);

        auto chromatographicPeaks = std::vector<ChromatographicPeak*>(ms2IdsForThisFile.size());

        ParallelOptions *tempVar = new ParallelOptions();
        tempVar->MaxDegreeOfParallelism = MaxThreads;
        Parallel::ForEach(Partitioner::Create(0, ms2IdsForThisFile.size()), tempVar, [&] (range, loopState)
        {
                for (int i = range::Item1; i < range::Item2; i++)
                {
                    //// Stop loop if canceled
                    //if (GlobalVariables.StopLoops)
                    //{
                    //    loopState.Stop();
                    //    return;
                    //}
    
                    auto identification = ms2IdsForThisFile[i];
                    ChromatographicPeak *msmsFeature = new ChromatographicPeak(identification, false, fileInfo);
                    chromatographicPeaks[i] = msmsFeature;
    
                    for (auto chargeState : _chargeStates)
                    {
                        if (IdSpecificChargeState && chargeState != identification.precursorChargeState)
                        {
                            continue;
                        }
    
                        // get XIC (peakfinding)
                        std::vector<IndexedMassSpectralPeak*> xic = Peakfind(identification.ms2RetentionTimeInMinutes, identification.massToLookFor, chargeState, identification.fileInfo, peakfindingTol).OrderBy([&] (std::any p)
                        {
                p::RetentionTime;
                        }).ToList();
    
                        // filter by smaller mass tolerance
                        xic.RemoveAll([&] (std::any p)
                        {
                !ppmTolerance->Within(p::Mz::ToMass(chargeState), identification.massToLookFor);
                        });
    
                        // filter by isotopic distribution
                        std::vector<IsotopicEnvelope*> isotopicEnvelopes = GetIsotopicEnvelopes(xic, identification, chargeState, true);
    
                        // add isotopic envelopes to the chromatographic peak
                        msmsFeature->IsotopicEnvelopes.insert(msmsFeature->IsotopicEnvelopes.end(), isotopicEnvelopes.begin(), isotopicEnvelopes.end());
                    }
    
                    msmsFeature->CalculateIntensityForThisFeature(Integrate);
                    CutPeak(msmsFeature, identification.ms2RetentionTimeInMinutes);
    
                    if (!msmsFeature->IsotopicEnvelopes.Any())
                    {
//C# TO C++ CONVERTER TODO TASK: A 'delete msmsFeature' statement was not added since msmsFeature was passed to a method or constructor. Handle memory management manually.
                        continue;
                    }
    
                    auto precursorXic = msmsFeature->IsotopicEnvelopes.Where([&] (std::any p)
                    {
//C# TO C++ CONVERTER TODO TASK: A 'delete msmsFeature' statement was not added since msmsFeature was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete tempVar' statement was not added since tempVar was passed to a method or constructor. Handle memory management manually.
        delete ppmTolerance;
//C# TO C++ CONVERTER TODO TASK: A 'delete peakfindingTol' statement was not added since peakfindingTol was passed to a method or constructor. Handle memory management manually.
                return p->ChargeState == identification.precursorChargeState;
                    }).ToList();
    
                    if (!precursorXic.Any())
                    {
                        msmsFeature->IsotopicEnvelopes.clear();

//C# TO C++ CONVERTER TODO TASK: A 'delete msmsFeature' statement was not added since msmsFeature was passed to a method or constructor. Handle memory management manually.
                        continue;
                    }
    
                    int min = precursorXic.Min([&] (std::any p)
                    {
                p::IndexedPeak::ZeroBasedMs1ScanIndex;
                    });
                    int max = precursorXic.Max([&] (std::any p)
                    {
                p::IndexedPeak::ZeroBasedMs1ScanIndex;
                    });
                    msmsFeature->IsotopicEnvelopes.RemoveAll([&] (std::any p)
                    {
//C# TO C++ CONVERTER TODO TASK: A 'delete msmsFeature' statement was not added since msmsFeature was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete tempVar' statement was not added since tempVar was passed to a method or constructor. Handle memory management manually.
        delete ppmTolerance;
//C# TO C++ CONVERTER TODO TASK: A 'delete peakfindingTol' statement was not added since peakfindingTol was passed to a method or constructor. Handle memory management manually.
                return p::IndexedPeak::ZeroBasedMs1ScanIndex < min;
                    });
                    msmsFeature->IsotopicEnvelopes.RemoveAll([&] (std::any p)
                    {
//C# TO C++ CONVERTER TODO TASK: A 'delete msmsFeature' statement was not added since msmsFeature was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete tempVar' statement was not added since tempVar was passed to a method or constructor. Handle memory management manually.
        delete ppmTolerance;
//C# TO C++ CONVERTER TODO TASK: A 'delete peakfindingTol' statement was not added since peakfindingTol was passed to a method or constructor. Handle memory management manually.
                return p::IndexedPeak::ZeroBasedMs1ScanIndex > max;
                    });
                    msmsFeature->CalculateIntensityForThisFeature(Integrate);

//C# TO C++ CONVERTER TODO TASK: A 'delete msmsFeature' statement was not added since msmsFeature was passed to a method or constructor. Handle memory management manually.
                }
        });

        _results->Peaks.emplace(fileInfo, chromatographicPeaks.ToList());

//C# TO C++ CONVERTER TODO TASK: A 'delete tempVar' statement was not added since tempVar was passed to a method or constructor. Handle memory management manually.
        delete ppmTolerance;
//C# TO C++ CONVERTER TODO TASK: A 'delete peakfindingTol' statement was not added since peakfindingTol was passed to a method or constructor. Handle memory management manually.
    }

    void FlashLfqEngine::QuantifyMatchBetweenRunsPeaks(SpectraFileInfo *idAcceptorFile)
    {
        auto acceptorFileIdentifiedPeaks = _results->Peaks[idAcceptorFile];

        if (!acceptorFileIdentifiedPeaks.Any())
        {
            return;
        }

        _peakIndexingEngine->DeserializeIndex(idAcceptorFile);

        auto thisFilesIds = std::unordered_set<std::string>(acceptorFileIdentifiedPeaks.Where([&] (std::any p)
        {
            p::IsotopicEnvelopes::Any();
        }).SelectMany([&] (std::any p)
        {
            p::Identifications->Select([&] (std::any d)
            {
                d::ModifiedSequence;
            });
        }));
        auto thisFilesMsmsIdentifiedProteins = std::unordered_set<ProteinGroup*>();

        // only match peptides from proteins that have at least one MS/MS identified peptide in the condition
        for (SpectraFileInfo *conditionFile : _spectraFileInfo.Where([&] (std::any p)
        {
            return p->Condition == idAcceptorFile->Condition;
        }))
        {
            for (ProteinGroup *proteinGroup : _results->Peaks[conditionFile].Where([&] (std::any p)
            {
                !p::IsMbrPeak;
            }).SelectMany([&] (std::any p)
            {
                p::Identifications::SelectMany([&] (std::any v)
                {
                    v::proteinGroups;
                });
            }))
            {
            }
            }
    }

    private *FlashLfqEngine::foreach(SpectraFileInfo idDonorFile in *_spectraFileInfo)
    {
        if (idAcceptorFile->Equals(idDonorFile))
        {
            continue;
        }

        // these peaks have no IDs in the acceptor file
        // match their IDs to this file
        auto donorPeaksToMatch = _results->Peaks[idDonorFile].Where([&] (std::any p)
        {
            return p->NumIdentificationsByFullSeq == 1 && p::IsotopicEnvelopes::Any() && !p::Identifications::Any([&] (std::any v)
            {
                    thisFilesIds->Contains(v::ModifiedSequence);
            }) && p::Identifications::Any([&] (std::any v)
            {
                    v::proteinGroups::Any([&] (std::any g)
                    {
                    thisFilesMsmsIdentifiedProteins->Contains(g);
                    });
                });
        }).ToList();

        if (!donorPeaksToMatch.Any())
        {
            continue;
        }

        std::vector<RetentionTimeCalibDataPoint*> rtCalibrationCurve = GetRtCalSpline(idDonorFile, idAcceptorFile);

        std::vector<ChromatographicPeak*> matchedPeaks(donorPeaksToMatch.size());
        std::vector<double> donorRts = rtCalibrationCurve.Select([&] (std::any p)
        {
            p::DonorFilePeak::Apex::IndexedPeak::RetentionTime;
        })->ToArray();

        ParallelOptions *tempVar = new ParallelOptions();
        tempVar->MaxDegreeOfParallelism = MaxThreads;
        Parallel::ForEach(Partitioner::Create(0, donorPeaksToMatch.size()), tempVar, [&] (range, loopState)
        {
                for (int i = range::Item1; i < range::Item2; i++)
                {
                    ChromatographicPeak *donorPeak = donorPeaksToMatch[i];
                    Identification *identification = donorPeak->getIdentifications().front();
    
                    auto acceptorPeak = new ChromatographicPeak(identification, true, idAcceptorFile);
                    matchedPeaks[i] = acceptorPeak;
    
                    int rtHypothesisIndex = Array::BinarySearch(donorRts, donorPeak->getApex()->IndexedPeak->RetentionTime);
                    if (rtHypothesisIndex < 0)
                    {
                        rtHypothesisIndex = ~rtHypothesisIndex;
                    }
                    if (rtHypothesisIndex >= donorRts.size() && rtHypothesisIndex >= 1)
                    {
                        rtHypothesisIndex = donorRts.size() - 1;
                    }
    
                    std::vector<RetentionTimeCalibDataPoint*> nearbyDataPoints;
    
                    // calculate accepted range of RTs
                    for (int r = rtHypothesisIndex; r < rtCalibrationCurve.size(); r++)
                    {
                        RetentionTimeCalibDataPoint *rightDataPoint = rtCalibrationCurve[r];
                        if (std::abs(rightDataPoint->DonorFilePeak->getApex()->IndexedPeak->RetentionTime - donorPeak->getApex()->IndexedPeak->RetentionTime) < 0.5)
                        {
                            nearbyDataPoints.push_back(rtCalibrationCurve[r]);
                        }
                        else
                        {
                            break;
                        }
                    }
    
                    for (int l = rtHypothesisIndex - 1; l >= 0; l--)
                    {
                        RetentionTimeCalibDataPoint *leftDataPoint = rtCalibrationCurve[l];
                        if (std::abs(leftDataPoint->DonorFilePeak->getApex()->IndexedPeak->RetentionTime - donorPeak->getApex()->IndexedPeak->RetentionTime) < 0.5)
                        {
                            nearbyDataPoints.push_back(rtCalibrationCurve[l]);
                        }
                        else
                        {
                            break;
                        }
                    }
    
                    double acceptorFileRtHypothesis;
                    double lowerRange;
                    double upperRange;
    
                    if (nearbyDataPoints.size() >= 4)
                    {
                        std::vector<double> nearbyRts = nearbyDataPoints.Select([&] (std::any p)
                        {
                    p::RtDiff;
                        }).ToList();
    
                        acceptorFileRtHypothesis = donorPeak->getApex()->IndexedPeak->RetentionTime + Statistics::Median(nearbyRts);
                        double firstQuartile = Statistics::LowerQuartile(nearbyRts);
                        double thirdQuartile = Statistics::UpperQuartile(nearbyRts);
                        double iqr = Statistics::InterquartileRange(nearbyRts);
    
                        lowerRange = firstQuartile - 1.5 * iqr;
                        upperRange = thirdQuartile + 1.5 * iqr;
                    }
                    else
                    {
        delete acceptorPeak;
                        continue;
                    }
    
                    double lowerBoundRt = acceptorFileRtHypothesis + lowerRange;
                    double upperBoundRt = acceptorFileRtHypothesis + upperRange;
    
                    if (upperBoundRt - acceptorFileRtHypothesis > MbrRtWindow)
                    {
                        upperBoundRt = acceptorFileRtHypothesis + MbrRtWindow;
                    }
    
                    if (acceptorFileRtHypothesis - lowerBoundRt > MbrRtWindow)
                    {
                        lowerBoundRt = acceptorFileRtHypothesis - MbrRtWindow;
                    }
    
                    std::vector<Ms1ScanInfo*> ms1ScanInfos = _ms1Scans[idAcceptorFile];
                    Ms1ScanInfo *start = ms1ScanInfos[0];
                    Ms1ScanInfo *end = ms1ScanInfos[0];
                    for (int j = 0; i < ms1ScanInfos.size(); j++)
                    {
                        Ms1ScanInfo *scan = ms1ScanInfos[j];
                        if (scan->RetentionTime <= lowerBoundRt)
                        {
                            start = scan;
                        }
    
                        if (scan->RetentionTime >= upperBoundRt)
                        {
                            end = scan;
                            break;
                        }
                    }
    
                    IsotopicEnvelope *bestEnv = nullptr;
                    std::vector<IsotopicEnvelope*> allEnvs;
                    for (int chargeState : donorPeak->IsotopicEnvelopes.Select([&] (std::any p)
                    {
                    p::ChargeState;
                    }).Distinct())
                    {
                        std::vector<IndexedMassSpectralPeak*> binPeaks;
    
                        for (int j = start->ZeroBasedMs1ScanIndex; j <= end->ZeroBasedMs1ScanIndex; j++)
                        {
                            IndexedMassSpectralPeak *peak = _peakIndexingEngine->GetIndexedPeak(identification->massToLookFor, j, mbrTol, chargeState);
    
                            if (peak != nullptr)
                            {
                                binPeaks.push_back(peak);
                            }
                        }
    
                        std::vector<IsotopicEnvelope*> envsForThisCharge = GetIsotopicEnvelopes(binPeaks, identification, chargeState, true);
    
                        if (envsForThisCharge.Any())
                        {
                            allEnvs.insert(allEnvs.end(), envsForThisCharge.begin(), envsForThisCharge.end());
                        }
                    }
    
                    if (!allEnvs.Any())
                    {
        delete acceptorPeak;
                        continue;
                    }
    
                    double maxIntensity = allEnvs.Max([&] (std::any p)
                    {
                    p::Intensity;
                    });
                    bestEnv = allEnvs.First([&] (std::any p)
                    {
        delete acceptorPeak;
//C# TO C++ CONVERTER TODO TASK: A 'delete tempVar' statement was not added since tempVar was passed to a method or constructor. Handle memory management manually.
                    return p->Intensity == maxIntensity;
                    });
    
                    auto bestChargeXic = Peakfind(bestEnv->IndexedPeak->RetentionTime, identification->massToLookFor, bestEnv->ChargeState, idAcceptorFile, mbrTol);
                    std::vector<IsotopicEnvelope*> envs2 = GetIsotopicEnvelopes(bestChargeXic, identification, bestEnv->ChargeState, true);
                    double maxRt = envs2.Max([&] (std::any p)
                    {
                    p::IndexedPeak::RetentionTime;
                    });
                    double minRt = envs2.Min([&] (std::any p)
                    {
                    p::IndexedPeak::RetentionTime;
                    });
                    acceptorPeak->IsotopicEnvelopes.insert(acceptorPeak->IsotopicEnvelopes.end(), envs2.begin(), envs2.end());
                    acceptorPeak->IsotopicEnvelopes.AddRange(allEnvs.Where([&] (std::any p)
                    {
        delete acceptorPeak;
//C# TO C++ CONVERTER TODO TASK: A 'delete tempVar' statement was not added since tempVar was passed to a method or constructor. Handle memory management manually.
                    return p::ChargeState != bestEnv->ChargeState && p::IndexedPeak::RetentionTime < maxRt && p::IndexedPeak::RetentionTime > minRt;
                    }));
                    acceptorPeak->CalculateIntensityForThisFeature(Integrate);
                    CutPeak(acceptorPeak, bestEnv->IndexedPeak->RetentionTime);

//C# TO C++ CONVERTER TODO TASK: A 'delete acceptorPeak' statement was not added since acceptorPeak was passed to a method or constructor. Handle memory management manually.
                }
        });

        // save MBR results
        for (auto peak : matchedPeaks.Where([&] (std::any p)
        {
//C# TO C++ CONVERTER TODO TASK: A 'delete tempVar' statement was not added since tempVar was passed to a method or constructor. Handle memory management manually.
            return p != nullptr && p::IsotopicEnvelopes::Any();
        }))
        {
            std::any oldPeak;
            if (bestMbrHits::TryGetValue(peak::Identifications::First().ModifiedSequence, oldPeak))
            {
                if (peak::Intensity > oldPeak::Intensity)
                {
                    bestMbrHits[peak::Identifications::First().ModifiedSequence] = peak;
                }
            }
            else
            {
                bestMbrHits->Add(peak::Identifications::First().ModifiedSequence, peak);
            }
        }

//C# TO C++ CONVERTER TODO TASK: A 'delete tempVar' statement was not added since tempVar was passed to a method or constructor. Handle memory management manually.
    }

    private *FlashLfqEngine::foreach(var peak in *bestMbrHits)
    {
        _results->Peaks[idAcceptorFile].push_back(peak->Value);
    }

    private std::vector<RetentionTimeCalibDataPoint*> <missing_class_definition>::GetRtCalSpline(SpectraFileInfo *donor, SpectraFileInfo *acceptor)
    {
        auto donorFileBestMsmsPeaks = std::unordered_map<std::string, ChromatographicPeak*>();
        auto acceptorFileBestMsmsPeaks = std::unordered_map<std::string, ChromatographicPeak*>();
        auto rtCalibrationCurve = std::vector<RetentionTimeCalibDataPoint*>();

        // get all peaks, not counting ambiguous peaks
        std::vector<ChromatographicPeak*> donorPeaks = _results::Peaks[donor].Where([&] (std::any p)
        {
            return p::Apex != nullptr && !p::IsMbrPeak && p->NumIdentificationsByFullSeq == 1;
        });
        std::vector<ChromatographicPeak*> acceptorPeaks = _results::Peaks[acceptor].Where([&] (std::any p)
        {
            return p::Apex != nullptr && !p::IsMbrPeak && p->NumIdentificationsByFullSeq == 1;
        });

        // get the best (most intense) peak for each peptide in the acceptor file
        for (auto acceptorPeak : acceptorPeaks)
        {
            ChromatographicPeak currentBestPeak;
            std::unordered_map<std::string, ChromatographicPeak*>::const_iterator acceptorFileBestMsmsPeaks_iterator = acceptorFileBestMsmsPeaks.find(acceptorPeak.Identifications.First().ModifiedSequence);
            if (acceptorFileBestMsmsPeaks_iterator != acceptorFileBestMsmsPeaks.end())
            {
                currentBestPeak = acceptorFileBestMsmsPeaks_iterator->second;
                if (currentBestPeak::Intensity > acceptorPeak->Intensity)
                {
                    acceptorFileBestMsmsPeaks[acceptorPeak->getIdentifications().front().ModifiedSequence] = acceptorPeak;
                }
            }
            else
            {
                currentBestPeak = acceptorFileBestMsmsPeaks_iterator->second;
                acceptorFileBestMsmsPeaks.emplace(acceptorPeak->getIdentifications().front().ModifiedSequence, acceptorPeak);
            }
        }

        // get the best (most intense) peak for each peptide in the donor file
        for (auto donorPeak : donorPeaks)
        {
            ChromatographicPeak currentBestPeak;
            std::unordered_map<std::string, ChromatographicPeak*>::const_iterator donorFileBestMsmsPeaks_iterator = donorFileBestMsmsPeaks.find(donorPeak.Identifications.First().ModifiedSequence);
            if (donorFileBestMsmsPeaks_iterator != donorFileBestMsmsPeaks.end())
            {
                currentBestPeak = donorFileBestMsmsPeaks_iterator->second;
                if (currentBestPeak::Intensity > donorPeak->Intensity)
                {
                    donorFileBestMsmsPeaks[donorPeak->getIdentifications().front().ModifiedSequence] = donorPeak;
                }
            }
            else
            {
                currentBestPeak = donorFileBestMsmsPeaks_iterator->second;
                donorFileBestMsmsPeaks.emplace(donorPeak->getIdentifications().front().ModifiedSequence, donorPeak);
            }
        }

        // create RT calibration curve
        for (auto peak : acceptorFileBestMsmsPeaks)
        {
            ChromatographicPeak *acceptorFilePeak = peak->Value;

            ChromatographicPeak donorFilePeak;
            std::unordered_map<std::string, ChromatographicPeak*>::const_iterator donorFileBestMsmsPeaks_iterator = donorFileBestMsmsPeaks.find(peak.Key);
            if (donorFileBestMsmsPeaks_iterator != donorFileBestMsmsPeaks.end())
            {
                donorFilePeak = donorFileBestMsmsPeaks_iterator->second;
                RetentionTimeCalibDataPoint tempVar(donorFilePeak, acceptorFilePeak);
                rtCalibrationCurve.push_back(&tempVar);
            }
            else
            {
                donorFilePeak = donorFileBestMsmsPeaks_iterator->second;
            }
        }

        return rtCalibrationCurve.OrderBy([&] (std::any p)
        {
            p::DonorFilePeak::Apex::IndexedPeak::RetentionTime;
        })->ToArray();
    }

    private void <missing_class_definition>::RunErrorChecking(SpectraFileInfo *spectraFile)
    {
        if (!Silent)
        {
            std::cout << "Checking errors" << std::endl;
        }

        _results::Peaks[spectraFile].RemoveAll([&] (std::any p)
        {
            return p == nullptr || p::IsMbrPeak && !p::IsotopicEnvelopes::Any();
        });

        // merge duplicate peaks and handle MBR/MSMS peakfinding conflicts
        auto peaksGroupedByApex = std::unordered_map<IndexedMassSpectralPeak*, ChromatographicPeak*>();
        auto peaks = std::vector<ChromatographicPeak*>();
        for (ChromatographicPeak *tryPeak : _results::Peaks[spectraFile].OrderBy([&] (std::any p)
        {
            p::IsMbrPeak;
        }))
        {
            tryPeak::CalculateIntensityForThisFeature(Integrate);
            tryPeak::ResolveIdentifications();

            if (tryPeak->Apex == nullptr)
            {
                if (tryPeak::IsMbrPeak)
                {
                    continue;
                }

                peaks.push_back(tryPeak);
                continue;
            }

            IndexedMassSpectralPeak *apexPeak = tryPeak::Apex::IndexedPeak;
            ChromatographicPeak storedPeak;
            std::unordered_map<IndexedMassSpectralPeak*, ChromatographicPeak*>::const_iterator peaksGroupedByApex_iterator = peaksGroupedByApex.find(apexPeak);
            if (peaksGroupedByApex_iterator != peaksGroupedByApex.end())
            {
                storedPeak = peaksGroupedByApex_iterator->second;
                if (tryPeak::IsMbrPeak && storedPeak == nullptr)
                {
                    continue;
                }

                if (!tryPeak::IsMbrPeak && !storedPeak::IsMbrPeak)
                {
                    storedPeak::MergeFeatureWith(tryPeak, Integrate);
                }
                else if (tryPeak::IsMbrPeak && !storedPeak::IsMbrPeak)
                {
                    continue;
                }
                else if (tryPeak::IsMbrPeak && storedPeak::IsMbrPeak)
                {
                    if (tryPeak::Identifications::First()->ModifiedSequence == storedPeak::Identifications::First().ModifiedSequence)
                    {
                        storedPeak::MergeFeatureWith(tryPeak, Integrate);
                    }
                    else
                    {
                        peaksGroupedByApex[tryPeak::Apex::IndexedPeak] = nullptr;
                    }
                }
            }
            else
            {
                storedPeak = peaksGroupedByApex_iterator->second;
                peaksGroupedByApex.emplace(apexPeak, tryPeak);
            }
        }

        peaks.AddRange(peaksGroupedByApex.Values->Where([&] (std::any p)
        {
            return p != nullptr;
        }));
        _results::Peaks[spectraFile] = peaks;

        // merge multiple peaks for the same peptide within a time window
        peaks = _results::Peaks[spectraFile].Where([&] (std::any p)
        {
            return p::NumIdentificationsByFullSeq > 1;
        }).ToList();
        auto temp = _results::Peaks[spectraFile].Where([&] (std::any p)
        {
            return p->NumIdentificationsByFullSeq == 1;
        }).GroupBy([&] (std::any p)
        {
            p::Identifications::First().ModifiedSequence;
        }).ToList();

        for (auto sequence : temp)
        {
            if (sequence.Count() == 1)
            {
                peaks.push_back(sequence.First());
                continue;
            }

            auto temp2 = sequence.Where([&] (std::any p)
            {
                return p::Apex != nullptr;
            }).ToList();
            auto merged = std::unordered_set<ChromatographicPeak*>();
            for (auto peak : temp2)
            {
                if (std::find(merged.begin(), merged.end(), peak) != merged.end())
                {
                    continue;
                }

                auto toMerge = temp2.Where([&] (std::any p)
                {
                    return std::abs(p::Apex::IndexedPeak::RetentionTime - peak->getApex()->IndexedPeak->RetentionTime) < RtTol && !std::find(merged.begin(), merged.end(), p) != merged.end() && p != peak;
                });
                for (auto peakToMerge : toMerge)
                {
                    peak->MergeFeatureWith(peakToMerge, Integrate);
                    merged.insert(peakToMerge);
                }

                peaks.push_back(peak);
            }
        }

        _results::Peaks[spectraFile] = peaks;
    }

    private std::vector<IsotopicEnvelope*> <missing_class_definition>::GetIsotopicEnvelopes(std::vector<IndexedMassSpectralPeak*> &peaks, Identification *identification, int chargeState, bool matchBetweenRuns)
    {
        auto isotopicEnvelopes = std::vector<IsotopicEnvelope*>();
        auto isotopeMassShifts = _baseSequenceToIsotopicDistribution[identification->BaseSequence];

        if (isotopeMassShifts->Count < NumIsotopesRequired)
        {
            return isotopicEnvelopes;
        }

        PpmTolerance *isotopeTolerance = new PpmTolerance(IsotopePpmTolerance);

        auto theorIsotopeMasses = std::vector<double>(isotopeMassShifts->Count);
        auto expIsotopeMasses = std::vector<double>(isotopeMassShifts->Count);
        auto experimentalIsotopeAbundances = std::vector<double>(isotopeMassShifts->Count);
        auto theoreticalIsotopeAbundances = isotopeMassShifts->Select([&] (std::any p)
        {
            p->Value;
        })->ToArray();

        for (auto peak : peaks)
        {
            // calculate theoretical isotopes relative to observed peak
            Array::Clear(theorIsotopeMasses, 0, theorIsotopeMasses.size());
            Array::Clear(expIsotopeMasses, 0, expIsotopeMasses.size());
            Array::Clear(experimentalIsotopeAbundances, 0, experimentalIsotopeAbundances.size());

            double observedMass = Chemistry::ClassExtensions::ToMass(peak->Mz, chargeState);
            double theorMass = identification->massToLookFor;
            double mainPeakError = observedMass - theorMass;
            for (int i = 0; i < theorIsotopeMasses.size(); i++)
            {
                theorIsotopeMasses[i] = mainPeakError + identification->massToLookFor + isotopeMassShifts[i].Key;
            }

            if (matchBetweenRuns)
            {
                double unexpectedIsotopeMass = observedMass - Constants::C13MinusC12;
                auto unexpectedPeak = _peakIndexingEngine::GetIndexedPeak(unexpectedIsotopeMass, peak->ZeroBasedMs1ScanIndex, isotopeTolerance, chargeState);
                bool unexpectedIsotopePeakObserved = unexpectedPeak != nullptr && unexpectedPeak->Intensity / peak->Intensity > 0.3;

                if (unexpectedIsotopePeakObserved)
                {
                    continue;
                }
            }

            for (int t = 0; t < theorIsotopeMasses.size(); t++)
            {
                auto isotopePeak = _peakIndexingEngine::GetIndexedPeak(theorIsotopeMasses[t], peak->ZeroBasedMs1ScanIndex, isotopeTolerance, chargeState);

                if (isotopePeak == nullptr)
                {
                    continue;
                }

                expIsotopeMasses[t] = isotopePeak->Mz.ToMass(chargeState);
                experimentalIsotopeAbundances[t] = isotopePeak->Intensity;
            }

            if (expIsotopeMasses[0] == 0 && RequireMonoisotopicMass)
            {
                continue;
            }

            int numIsotopePeaksObserved = 0;
            int mainPeakIndex = static_cast<int>(std::round(observedMass - identification->monoisotopicMass * std::pow(10, 0))) / std::pow(10, 0);
            for (int i = mainPeakIndex; i < expIsotopeMasses.size(); i++)
            {
                if (expIsotopeMasses[i] > 0)
                {
                    numIsotopePeaksObserved++;
                }
                else
                {
                    break;
                }
            }
            for (int i = mainPeakIndex - 1; i >= 0; i--)
            {
                if (expIsotopeMasses[i] > 0)
                {
                    numIsotopePeaksObserved++;
                }
                else
                {
                    break;
                }
            }

            if (numIsotopePeaksObserved >= NumIsotopesRequired)
            {
                double corr = Correlation::Pearson(experimentalIsotopeAbundances, theoreticalIsotopeAbundances);

                //TODO: include isotope imputation, more tolerance, etc
                if (corr > 0.7)
                {
                    IsotopicEnvelope tempVar(peak, chargeState, experimentalIsotopeAbundances.Sum());
                    isotopicEnvelopes.push_back(&tempVar);
                }
                //else
                //{
                //    for (int i = theoreticalIsotopeAbundances.Length - 1; i >= NumIsotopesRequired - 1 && i >= 0; i--)
                //    {
                //        if (experimentalIsotopeAbundances[i] > 0)
                //        {
                //            double relIsotopeAbundance = experimentalIsotopeAbundances[i] / experimentalIsotopeAbundances[0];
                //            double theorIsotopeAbundance = isotopeMassShifts[i].Value / isotopeMassShifts[0].Value;

                //            // impute isotope intensity if it is much higher than expected
                //            if (relIsotopeAbundance / theorIsotopeAbundance < 2.0)
                //            {
                //                experimentalIsotopeAbundances[i] = experimentalIsotopeAbundances[i];
                //            }
                //            else
                //            {
                //                experimentalIsotopeAbundances[i] = theorIsotopeAbundance * experimentalIsotopeAbundances[0] * 2.0;
                //            }
                //        }
                //        else
                //        {
                //            experimentalIsotopeAbundances[i] = (isotopeMassShifts[i].Value / isotopeMassShifts[0].Value) * experimentalIsotopeAbundances[0];
                //        }
                //    }

                //    corr = Correlation.Pearson(experimentalIsotopeAbundances, theoreticalIsotopeAbundances);

                //    if (corr > 0.7)
                //    {
                //        isotopicEnvelopes.Add(new IsotopicEnvelope(peak, chargeState, experimentalIsotopeAbundances.Sum()));
                //    }
                //}
            }
        }

//C# TO C++ CONVERTER TODO TASK: A 'delete isotopeTolerance' statement was not added since isotopeTolerance was passed to a method or constructor. Handle memory management manually.
        return isotopicEnvelopes;
    }

    private std::vector<IndexedMassSpectralPeak*> <missing_class_definition>::Peakfind(double idRetentionTime, double mass, int charge, SpectraFileInfo *spectraFileInfo, Tolerance *tolerance)
    {
        auto xic = std::vector<IndexedMassSpectralPeak*>();

        // get precursor scan to start at
        std::vector<Ms1ScanInfo*> ms1Scans = _ms1Scans[spectraFileInfo];
        int precursorScanIndex = -1;
        for (auto ms1Scan : ms1Scans)
        {
            if (ms1Scan->RetentionTime < idRetentionTime)
            {
                precursorScanIndex = ms1Scan->ZeroBasedMs1ScanIndex;
            }
            else
            {
                break;
            }
        }

        // go right
        int missedScans = 0;
        for (int t = precursorScanIndex; t < ms1Scans.size(); t++)
        {
            auto peak = _peakIndexingEngine::GetIndexedPeak(mass, t, tolerance, charge);

            if (peak == nullptr && t != precursorScanIndex)
            {
                missedScans++;
            }
            else if (peak != nullptr)
            {
                missedScans = 0;
                xic.push_back(peak);
            }

            if (missedScans > MissedScansAllowed)
            {
                break;
            }
        }

        // go left
        missedScans = 0;
        for (int t = precursorScanIndex - 1; t >= 0; t--)
        {
            auto peak = _peakIndexingEngine::GetIndexedPeak(mass, t, tolerance, charge);

            if (peak == nullptr && t != precursorScanIndex)
            {
                missedScans++;
            }
            else if (peak != nullptr)
            {
                missedScans = 0;
                xic.push_back(peak);
            }

            if (missedScans > MissedScansAllowed)
            {
                break;
            }
        }

        // sort by RT
//C# TO C++ CONVERTER TODO TASK: The 'Compare' parameter of std::sort produces a boolean value, while the .NET Comparison parameter produces a tri-state result:
//ORIGINAL LINE: xic.Sort((x, y) => x.RetentionTime.CompareTo(y.RetentionTime));
        std::sort(xic.begin(), xic.end(), [&] (x, y)
        {
            x::RetentionTime->CompareTo(y::RetentionTime);
        });

        return xic;
    }

    private void <missing_class_definition>::CutPeak(ChromatographicPeak *peak, double identificationTime)
    {
        // find out if we need to split this peak by using the discrimination factor
        // this method assumes that the isotope envelopes in a chromatographic peak are already sorted by MS1 scan number
        bool cutThisPeak = false;

        if (peak->IsotopicEnvelopes.size() < 5)
        {
            return;
        }

        auto timePointsForApexZ = peak->IsotopicEnvelopes.Where([&] (std::any p)
        {
            return p->ChargeState == peak->getApex()->ChargeState;
        }).ToList();
        std::unordered_set<int> scanNumbers = std::unordered_set<int>(timePointsForApexZ.Select([&] (std::any p)
        {
            p::IndexedPeak::ZeroBasedMs1ScanIndex;
        }));
        int apexIndex = timePointsForApexZ.find(peak->getApex());
        IsotopicEnvelope *valleyTimePoint = nullptr;

        // -1 checks the left side, +1 checks the right side
        std::vector<int> iters = {1, -1};

        for (auto iter : iters)
        {
            valleyTimePoint = nullptr;
            int indexOfValley = 0;

            for (int i = apexIndex + iter; i < timePointsForApexZ.size() && i >= 0; i += iter)
            {
                IsotopicEnvelope *timepoint = timePointsForApexZ[i];

                if (valleyTimePoint == nullptr || timepoint->getIntensity() < valleyTimePoint->getIntensity())
                {
                    valleyTimePoint = timepoint;
                    indexOfValley = timePointsForApexZ.find(valleyTimePoint);
                }

                double discriminationFactor = (timepoint->getIntensity() - valleyTimePoint->getIntensity()) / timepoint->getIntensity();

                if (discriminationFactor > MinDiscFactorToCutAt && (indexOfValley + iter < timePointsForApexZ.size() && indexOfValley + iter >= 0))
                {
                    IsotopicEnvelope *secondValleyTimepoint = timePointsForApexZ[indexOfValley + iter];

                    discriminationFactor = (timepoint->getIntensity() - secondValleyTimepoint->getIntensity()) / timepoint->getIntensity();

                    if (discriminationFactor > MinDiscFactorToCutAt)
                    {
                        cutThisPeak = true;
                        break;
                    }

                    int nextMs1ScanNum = -1;
                    for (int j = valleyTimePoint->IndexedPeak->ZeroBasedMs1ScanIndex - 1; j < _ms1Scans[peak->SpectraFileInfo]->Length && j >= 0; j += iter)
                    {
                        if (_ms1Scans[peak->SpectraFileInfo][j].OneBasedScanNumber >= 0 && _ms1Scans[peak->SpectraFileInfo][j].OneBasedScanNumber != valleyTimePoint->IndexedPeak->ZeroBasedMs1ScanIndex)
                        {
                            nextMs1ScanNum = j + 1;
                            break;
                        }
                    }

                    if (!std::find(scanNumbers.begin(), scanNumbers.end(), nextMs1ScanNum) != scanNumbers.end())
                    {
                        cutThisPeak = true;
                        break;
                    }
                }
            }

            if (cutThisPeak)
            {
                break;
            }
        }

        // cut
        if (cutThisPeak)
        {
            if (identificationTime > valleyTimePoint->IndexedPeak->RetentionTime)
            {
                // MS2 identification is to the right of the valley; remove all peaks left of the valley
                peak->IsotopicEnvelopes.RemoveAll([&] (std::any p)
                {
                    return p::IndexedPeak::RetentionTime <= valleyTimePoint->IndexedPeak->RetentionTime;
                });
            }
            else
            {
                // MS2 identification is to the left of the valley; remove all peaks right of the valley
                peak->IsotopicEnvelopes.RemoveAll([&] (std::any p)
                {
                    return p::IndexedPeak::RetentionTime >= valleyTimePoint->IndexedPeak->RetentionTime;
                });
            }

            // recalculate intensity for the peak
            peak->CalculateIntensityForThisFeature(Integrate);
            peak->SplitRT = valleyTimePoint->IndexedPeak->RetentionTime;

            // recursively cut
            CutPeak(peak, identificationTime);
        }
    }
}
