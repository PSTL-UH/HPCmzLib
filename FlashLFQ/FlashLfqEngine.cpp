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
#include "PpmTolerance.h"
#include "Tolerance.h"
#include "ChromatographicPeak.h"
#include "ProteinGroup.h"
#include "RetentionTimeCalibDataPoint.h"
#include "IndexedMassSpectralPeak.h"
#include "IsotopicEnvelope.h"
#include "../Chemistry/ClassExtensions.h"
#include "../Chemistry/Constants.h"

#include "Math.h"
#include "Group.h"
#include "Search.h"

#include <string>

using namespace Chemistry;
using namespace MzLibUtil;
using namespace UsefulProteomicsDatabases;

namespace FlashLFQ
{

    FlashLfqEngine::FlashLfqEngine(std::vector<Identification*> &allIdentifications,
                                   bool normalize, bool advancedProteinQuant,
                                   bool matchBetweenRuns, double ppmTolerance,
                                   double isotopeTolerancePpm,
                                   double matchBetweenRunsPpmTolerance,
                                   bool integrate, int numIsotopesRequired,
                                   bool idSpecificChargeState,
                                   bool requireMonoisotopicMass, bool silent,
                                   std::string optionalPeriodicTablePath,
                                   double maxMbrWindow, int maxThreads) :
        Silent(silent), MaxThreads(maxThreads), PeakfindingPpmTolerance(20.0),
        PpmTolerance(ppmTolerance), RtTol(5.0), IsotopePpmTolerance(isotopeTolerancePpm),
        Integrate(integrate), MissedScansAllowed(1), NumIsotopesRequired(numIsotopesRequired),
        MbrRtWindow(maxMbrWindow), MbrPpmTolerance(matchBetweenRunsPpmTolerance),
        ErrorCheckAmbiguousMatches(true), MatchBetweenRuns(matchBetweenRuns),
        IdSpecificChargeState(idSpecificChargeState),
        RequireMonoisotopicMass(requireMonoisotopicMass),
        Normalize(normalize), MinDiscFactorToCutAt(0.6),
        AdvancedProteinQuant(advancedProteinQuant)
    {
        if (optionalPeriodicTablePath == "")
        {
            //optionalPeriodicTablePath = FileSystem::combine(AppDomain::CurrentDomain->BaseDirectory, R"(elements.dat)");
            optionalPeriodicTablePath = "elements.dat";
        }

        Loaders::LoadElements(optionalPeriodicTablePath);

        _chargeStates = std::vector<int>();
        _peakIndexingEngine = new PeakIndexingEngine();

 #ifdef ORIG       
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
#endif
        // This does the Select and Distinct part
        for ( auto p =allIdentifications.begin(); p != allIdentifications.end(); p++ ) {
            bool found = false;
            if ( p == allIdentifications.begin() ) {
                _spectraFileInfo.push_back ( (*p)->fileInfo );
                continue;
            }
            for ( auto t : _spectraFileInfo ) {
                if ( (*p)->fileInfo == t ) {
                    found = true;
                    break;
                }
            }
            if ( !found ) {
                _spectraFileInfo.push_back ( (*p)->fileInfo );
            }
        }
        // Now to the ordering.
        std::sort ( _spectraFileInfo.begin(),  _spectraFileInfo.end(), [&]
                    (SpectraFileInfo *l, SpectraFileInfo *r) {
                        if (l->Condition < r->Condition ) return true;
                        if (l->Condition > r->Condition ) return false;
                        if (l->BiologicalReplicate < r->BiologicalReplicate ) return true;
                        if (l->BiologicalReplicate > r->BiologicalReplicate ) return false;
                        if (l->Fraction < r->Fraction ) return true;
                        if (l->Fraction > r->Fraction ) return false;
                        if (l->TechnicalReplicate < r->TechnicalReplicate ) return true;
                        return false;       
                    } );
        
        _allIdentifications = allIdentifications;

#ifdef ORIG
        if (MaxThreads == -1 || MaxThreads >= Environment::ProcessorCount)
        {
            MaxThreads = Environment::ProcessorCount - 1;
        }

        if (MaxThreads <= 0)
        {
            MaxThreads = 1;
        }
#endif

    }

    FlashLfqResults *FlashLfqEngine::Run()
    {
        //_globalStopwatch->Start();
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
                throw MzLibException("A crash occured in FlashLFQ during the intensity normalization process:\n" );
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

        return _results;
    }

    void FlashLfqEngine::CalculateTheoreticalIsotopeDistributions()
    {
        _baseSequenceToIsotopicDistribution = std::unordered_map<std::string, std::vector<std::tuple<double, double>*>>();

        // calculate monoisotopic masses and isotopic envelope
        for (auto id : _allIdentifications)
        {
            if (_baseSequenceToIsotopicDistribution.find(id->BaseSequence) != _baseSequenceToIsotopicDistribution.end())
            {
                continue;
            }

            auto formula = id->OptionalChemicalFormula;

            auto isotopicMassesAndNormalizedAbundances = std::vector<std::tuple<double, double>>();

            Proteomics::AminoAcidPolymer::Peptide *p = new Proteomics::AminoAcidPolymer::Peptide(id->BaseSequence);

            if (formula == nullptr)
            {
                formula = p->GetChemicalFormula();
            }

            auto isotopicDistribution = IsotopicDistribution::GetDistribution(formula, 0.125, 1e-8);

            std::vector<double> masses = isotopicDistribution->getMasses(); //.ToArray();
            std::vector<double> abundances = isotopicDistribution->getIntensities(); //.ToArray();

            double unmodifiedMonoisotopicMass = p->getMonoisotopicMass();
            //double highestAbundance = abundances.Max();
            double highestAbundance = *std::max(abundances.begin(), abundances.end());

            for (int i = 0; i < (int) masses.size(); i++)
            {
                // expected isotopic mass shifts for this peptide
                masses[i] -= unmodifiedMonoisotopicMass;

                // normalized abundance of each isotope
                abundances[i] /= highestAbundance;

                // look for these isotopes
                if ((int)isotopicMassesAndNormalizedAbundances.size() < NumIsotopesRequired ||
                    abundances[i] > 0.1)
                {
                    isotopicMassesAndNormalizedAbundances.push_back(std::make_tuple(masses[i], abundances[i]));
                }
            }

            _baseSequenceToIsotopicDistribution.emplace(id->BaseSequence, isotopicMassesAndNormalizedAbundances);

            delete p;
        }

#ifdef ORIG
        auto minChargeState = _allIdentifications.Min([&] (std::any p)
        {
            p::precursorChargeState;
        });
#endif
        auto  minChargeState = (*std::min(_allIdentifications.begin(), _allIdentifications.end(),
                                          [&] ( auto l, auto r ) {
                                              return (*l)->precursorChargeState < (*r)->precursorChargeState;
                                          }))->precursorChargeState;
        
#ifdef ORIG
        auto maxChargeState = _allIdentifications.Max([&] (std::any p)
        {
            p::precursorChargeState;
        });
        _chargeStates = Enumerable::Range(minChargeState, (maxChargeState - minChargeState) + 1);

#endif
        auto maxChargeState = (*std::max(_allIdentifications.begin(), _allIdentifications.end(),
                                         [&] ( auto l,  auto r ) {
                                             return (*l)->precursorChargeState < (*r)->precursorChargeState;
                }))->precursorChargeState;

        for (int p = minChargeState; p< ((maxChargeState - minChargeState) + 1); p++ ) {
            _chargeStates.push_back(p);
        }
        
#ifdef ORIG
        auto peptideModifiedSequences = _allIdentifications.GroupBy([&] (std::any p)
        {
            p::ModifiedSequence;
        });
#endif
        std::function<bool(Identification*, Identification*)> f1 = [&] (Identification*l, Identification* r) {
            return l->ModifiedSequence < r->ModifiedSequence; };
        std::function<bool(Identification*, Identification*)> f2 = [&] (Identification*l, Identification* r) {
            return l->ModifiedSequence != r->ModifiedSequence; };
        std::vector<std::vector<Identification*>> peptideModifiedSequences = Group::GroupBy (_allIdentifications, f1, f2);
        
        for (auto identifications : peptideModifiedSequences)
        {
            // isotope where normalized abundance is 1
#ifdef ORIG
            double mostAbundantIsotopeShift = _baseSequenceToIsotopicDistribution[identifications->First().BaseSequence].First([&] (std::any p)
            {
                return p->Value == 1.0;
            }).Key;
#endif
            auto t =identifications.front()->BaseSequence;
            double mostAbundantIsotopeShift;
            for ( auto p: _baseSequenceToIsotopicDistribution[t] ) {
                if ( std::get<1>(*p) == 1.0 ) {
                    mostAbundantIsotopeShift = std::get<0>(*p);
                    break;
                }
            }
            
            double thisPeptidesMostAbundantMass = identifications.front()->monoisotopicMass + mostAbundantIsotopeShift;

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

#ifdef ORIG
        auto ms2IdsForThisFile = _allIdentifications.Where([&] (std::any p)
        {
            p::fileInfo->Equals(fileInfo);
        }).ToList();
#endif
        std::vector<Identification*> ms2IdsForThisFile;
        for ( auto p: _allIdentifications ) {
            if ( p->fileInfo->Equals(fileInfo)) {
                ms2IdsForThisFile.push_back(p);
            }
        }

        if (!ms2IdsForThisFile.empty())
        {
            return;
        }

        Tolerance *peakfindingTol = new PpmTolerance(PeakfindingPpmTolerance);
        Tolerance *ppmTolerance = new PpmTolerance(PpmTolerance);

        auto chromatographicPeaks = std::vector<ChromatographicPeak*>(ms2IdsForThisFile.size());

        //ParallelOptions *tempVar = new ParallelOptions();
        //tempVar->MaxDegreeOfParallelism = MaxThreads;
        //Parallel::ForEach(Partitioner::Create(0, ms2IdsForThisFile.size()), tempVar, [&] (range, loopState)
        //{
        //      for (int i = range::Item1; i < range::Item2; i++)
        for (int i= 0; i < (int) ms2IdsForThisFile.size(); i++ ) 
        {
            auto identification = ms2IdsForThisFile[i];
            ChromatographicPeak *msmsFeature = new ChromatographicPeak(identification, false, fileInfo);
            chromatographicPeaks[i] = msmsFeature;
            
            for (auto chargeState : _chargeStates)
            {
                if (IdSpecificChargeState && chargeState != identification->precursorChargeState)
                {
                    continue;
                }
                
                // get XIC (peakfinding)
#ifdef ORIG
                std::vector<IndexedMassSpectralPeak*> xic = Peakfind(identification->ms2RetentionTimeInMinutes, identification->massToLookFor, chargeState, identification->fileInfo, peakfindingTol).OrderBy([&] (std::any p) {
                        p::RetentionTime;
                    }).ToList();
#endif
    
                std::vector<IndexedMassSpectralPeak*> xic = Peakfind(identification->ms2RetentionTimeInMinutes,
                                                                     identification->massToLookFor,
                                                                     chargeState, identification->fileInfo,
                                                                     peakfindingTol);
                std::sort(xic.begin(), xic.end(), [&] (IndexedMassSpectralPeak* l, IndexedMassSpectralPeak* r) {
                        return l->RetentionTime < r->RetentionTime;
                    });


#ifdef ORIG
                // filter by smaller mass tolerance
                xic.RemoveAll([&] (std::any p)   {
                        !ppmTolerance->Within(p::Mz::ToMass(chargeState), identification->massToLookFor);
                    });
#endif
                for ( auto p = xic.begin(); p!= xic.end(); p++ ) {
                    if ( !ppmTolerance->Within(Chemistry::ClassExtensions::ToMass((*p)->Mz, chargeState),
                                               identification->massToLookFor ) ) {
                        xic.erase(p);
                    }
                }
                
                // filter by isotopic distribution
                std::vector<IsotopicEnvelope*> isotopicEnvelopes = GetIsotopicEnvelopes(xic,
                                                          identification, chargeState, true);
                
                // add isotopic envelopes to the chromatographic peak
                msmsFeature->IsotopicEnvelopes.insert(msmsFeature->IsotopicEnvelopes.end(),
                                        isotopicEnvelopes.begin(), isotopicEnvelopes.end());
            }
            
            msmsFeature->CalculateIntensityForThisFeature(Integrate);
            CutPeak(msmsFeature, identification->ms2RetentionTimeInMinutes);
            
            if (!msmsFeature->IsotopicEnvelopes.empty())
            {
                continue;
            }

#ifdef ORIG           
            auto precursorXic = msmsFeature->IsotopicEnvelopes.Where([&] (std::any p)  {
                    delete ppmTolerance;
                    return p->ChargeState == identification.precursorChargeState;
                }).ToList();
#endif
            std::vector<IsotopicEnvelope *> precursorXic;
            for ( auto p:  msmsFeature->IsotopicEnvelopes ) {
                if ( p->ChargeState == identification->precursorChargeState ) {
                    precursorXic.push_back(p);
                }
            }
    
            if (!precursorXic.empty())
            {
                msmsFeature->IsotopicEnvelopes.clear();
                continue;
            }
#ifdef ORIG    
            int min = precursorXic.Min([&] (std::any p)  {
                    p::IndexedPeak::ZeroBasedMs1ScanIndex;
                });
#endif
            int min = (*std::min(precursorXic.begin(), precursorXic.end(),
                                 [&] ( auto l,  auto r) {
                                     return (*l)->IndexedPeak->ZeroBasedMs1ScanIndex <
                                     (*r)->IndexedPeak->ZeroBasedMs1ScanIndex;
                                 }))->IndexedPeak->ZeroBasedMs1ScanIndex;
#ifdef ORIG            
            int max = precursorXic.Max([&] (std::any p) {
                p::IndexedPeak::ZeroBasedMs1ScanIndex;
                });
#endif
            int max = (*std::max(precursorXic.begin(), precursorXic.end(),
                                 [&] ( auto l,  auto r) {
                                     return (*l)->IndexedPeak->ZeroBasedMs1ScanIndex <
                                     (*r)->IndexedPeak->ZeroBasedMs1ScanIndex;
                                 }))->IndexedPeak->ZeroBasedMs1ScanIndex;
#ifdef ORIG
            msmsFeature->IsotopicEnvelopes.RemoveAll([&] (std::any p)   {
                    delete ppmTolerance;
                    return p::IndexedPeak::ZeroBasedMs1ScanIndex < min;
                });

            msmsFeature->IsotopicEnvelopes.RemoveAll([&] (std::any p) {
                    delete ppmTolerance;
                    return p::IndexedPeak::ZeroBasedMs1ScanIndex > max;
                });

#endif
            for ( auto p = msmsFeature->IsotopicEnvelopes.begin(); p != msmsFeature->IsotopicEnvelopes.end(); p++ ){
                if ( (*p)->IndexedPeak->ZeroBasedMs1ScanIndex < min  ||
                     (*p)->IndexedPeak->ZeroBasedMs1ScanIndex > max ) {
                    msmsFeature->IsotopicEnvelopes.erase(p);
                }
            }

            
            msmsFeature->CalculateIntensityForThisFeature(Integrate);

            //C# TO C++ CONVERTER TODO TASK: A 'delete msmsFeature' statement was not added since msmsFeature was
            // passed to a method or constructor. Handle memory management manually.
        }

        _results->Peaks.emplace(fileInfo, chromatographicPeaks);

        // C# TO C++ CONVERTER TODO TASK: A 'delete tempVar' statement was not added
        // since tempVar was passed to a method or constructor. Handle memory management manually.
        delete ppmTolerance;
        // C# TO C++ CONVERTER TODO TASK: A 'delete peakfindingTol' statement was not added since
        // peakfindingTol was passed to a method or constructor. Handle memory management manually.
    }

    void FlashLfqEngine::QuantifyMatchBetweenRunsPeaks(SpectraFileInfo *idAcceptorFile)
    {
        auto acceptorFileIdentifiedPeaks = _results->Peaks[idAcceptorFile];

        if (!acceptorFileIdentifiedPeaks.empty())
        {
            return;
        }

        _peakIndexingEngine->DeserializeIndex(idAcceptorFile);

#ifdef ORIG
        auto thisFilesIds = std::unordered_set<std::string>(acceptorFileIdentifiedPeaks.Where([&] (std::any p){
            p::IsotopicEnvelopes::Any();
        }).SelectMany([&] (std::any p) {
                p::Identifications->Select([&] (std::any d) {
                        d::ModifiedSequence;
                    });
            }));
#endif
        std::unordered_set<std::string> thisFilesIds;
        for ( auto p: acceptorFileIdentifiedPeaks ) {
            if ( !p->IsotopicEnvelopes.empty() ) {
                for ( auto d: p->getIdentifications() ) {
                    thisFilesIds.insert(d->ModifiedSequence);
                }
            }
        }
        std::unordered_set<ProteinGroup*> thisFilesMsmsIdentifiedProteins;

        // only match peptides from proteins that have at least one MS/MS identified peptide in the condition
#ifdef ORIG
        // The converted C++ by the tool was useless, replaced it by the original C# code.
        foreach (SpectraFileInfo conditionFile in _spectraFileInfo.Where(p => p.Condition ==
                                                                         idAcceptorFile.Condition))
        {
            foreach (ProteinGroup proteinGroup in _results.Peaks[conditionFile].Where(p => !p.IsMbrPeak).
                     SelectMany(p => p.Identifications.SelectMany(v => v.proteinGroups)))
            {
                thisFilesMsmsIdentifiedProteins.Add(proteinGroup);
            }
        }
#endif
        for ( SpectraFileInfo *conditionFile : _spectraFileInfo ) {
            if (conditionFile->Condition  == idAcceptorFile->Condition ) {
                for (auto p : _results->Peaks[conditionFile] ) {
                    if ( !p->IsMbrPeak ) {
                        for ( auto t:  p->getIdentifications() ) {
                            for ( auto proteinGroup : t->proteinGroups ) {
                                thisFilesMsmsIdentifiedProteins.insert(proteinGroup);                            
                            }
                        }
                    }
                }
            }
        }
        
    

        //foreach(SpectraFileInfo idDonorFile in *_spectraFileInfo)
        for ( SpectraFileInfo* idDonorFile : _spectraFileInfo )
        {
            if (idAcceptorFile->Equals(idDonorFile))
            {
                continue;
            }
            
            // these peaks have no IDs in the acceptor file
            // match their IDs to this file
#ifdef ORIG
            auto donorPeaksToMatch = _results->Peaks[idDonorFile].Where([&] (std::any p)   {
                    return p->NumIdentificationsByFullSeq == 1 && p::IsotopicEnvelopes::Any() &&
                    !p::Identifications::Any([&] (std::any v)  {
                            thisFilesIds->Contains(v::ModifiedSequence);
                        })                                                                    &&
                    p::Identifications::Any([&] (std::any v) {
                            v::proteinGroups::Any([&] (std::any g)  {
                                    thisFilesMsmsIdentifiedProteins->Contains(g);
                                });
                        });
                }).ToList();
#endif
            std::vector<ChromatographicPeak*> donorPeaksToMatch;
            for ( auto p: _results->Peaks[idDonorFile] ) {
                bool empty1=true, empty2=true;
                for ( auto v : p->getIdentifications() ) {
                    if (thisFilesIds.find(v->ModifiedSequence) != thisFilesIds.end()) {
                        empty1=false;
                        break;
                    }
                    for ( auto g: v->proteinGroups ) {
                        if ( thisFilesMsmsIdentifiedProteins.find(g) !=  thisFilesMsmsIdentifiedProteins.end() ) {
                            empty2 = false;
                            break;
                        }                        
                    }
                    if (  p->getNumIdentificationsByFullSeq() == 1 &&
                          !p->IsotopicEnvelopes.empty()       &&
                          empty1                              &&
                          empty2                                ) {
                        donorPeaksToMatch.push_back(p);
                    }
                }

                
            }
            if (!donorPeaksToMatch.empty())
            {
                continue;
            }
            
            std::vector<RetentionTimeCalibDataPoint*> rtCalibrationCurve = GetRtCalSpline(idDonorFile, idAcceptorFile);
            
            std::vector<ChromatographicPeak*> matchedPeaks(donorPeaksToMatch.size());
#ifdef ORIG
            std::vector<double> donorRts = rtCalibrationCurve.Select([&] (std::any p) {
                    p::DonorFilePeak::Apex::IndexedPeak::RetentionTime;
                })->ToArray();
#endif
            std::vector<double> donorRts;
            for ( auto p :  rtCalibrationCurve ) {
                donorRts.push_back( p->DonorFilePeak->getApex()->IndexedPeak->RetentionTime );
            }
            //ParallelOptions *tempVar = new ParallelOptions();
            //tempVar->MaxDegreeOfParallelism = MaxThreads;
            //Parallel::ForEach(Partitioner::Create(0, donorPeaksToMatch.size()), tempVar, [&] (range, loopState)
            //{
            //        for (int i = range::Item1; i < range::Item2; i++)
            for ( int i = 0; i < (int)donorPeaksToMatch.size(); i++ ) {
                ChromatographicPeak *donorPeak = donorPeaksToMatch[i];
                Identification *identification = donorPeak->getIdentifications().front();
                
                auto acceptorPeak = new ChromatographicPeak(identification, true, idAcceptorFile);
                matchedPeaks[i] = acceptorPeak;
                
                int rtHypothesisIndex = BinarySearch(donorRts, donorPeak->getApex()->IndexedPeak->RetentionTime);
                if (rtHypothesisIndex < 0)
                {
                    rtHypothesisIndex = ~rtHypothesisIndex;
                }
                if (rtHypothesisIndex >= (int)donorRts.size() && rtHypothesisIndex >= 1)
                {
                    rtHypothesisIndex = donorRts.size() - 1;
                }
                
                std::vector<RetentionTimeCalibDataPoint*> nearbyDataPoints;
                
                // calculate accepted range of RTs
                for (int r = rtHypothesisIndex; r < (int)rtCalibrationCurve.size(); r++)
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
                    if (std::abs(leftDataPoint->DonorFilePeak->getApex()->IndexedPeak->RetentionTime -
                                 donorPeak->getApex()->IndexedPeak->RetentionTime) < 0.5)
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
#ifdef ORIG
                    std::vector<double> nearbyRts = nearbyDataPoints.Select([&] (std::any p) {
                            p::RtDiff;
                        }).ToList();
#endif
                    std::vector<double> nearbyRts;
                    for ( auto p : nearbyDataPoints ) {
                        nearbyRts.push_back(p->RtDiff);
                    }
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
                for (int j = 0; i < (int)ms1ScanInfos.size(); j++)
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
#ifdef ORIT
                //for (int chargeState : donorPeak->IsotopicEnvelopes.Select([&] (std::any p){
                //            p::ChargeState;
                //        }).Distinct())                
#endif
                std::vector<int> tempvec;
                for ( auto p : donorPeak->IsotopicEnvelopes ) {
                    bool found = false;
                    for ( auto v: tempvec ) {
                        if (p->ChargeState == v ) {
                            found = true;
                            break;
                        }
                    }
                    if ( !found ) {
                        tempvec.push_back(p->ChargeState);
                    }
                }
                for ( int chargeState : tempvec ) 
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
                    
                    if (!envsForThisCharge.empty())
                    {
                        allEnvs.insert(allEnvs.end(), envsForThisCharge.begin(), envsForThisCharge.end());
                    }
                }
                
                if (!allEnvs.empty())
                {
                    delete acceptorPeak;
                    continue;
                }
                
#ifdef ORIG
                double maxIntensity = allEnvs.Max([&] (std::any p) {
                        p::Intensity;
                    });
#endif
                double maxIntensity = (*std::max(allEnvs.begin(), allEnvs.end(),
                                                 [&] ( auto l, auto r ) {
                                                     return (*l)->getIntensity() < (*r)->getIntensity();
                                                 }) )->getIntensity();
                
#ifdef ORIG
                bestEnv = allEnvs.First([&] (std::any p) {
                        delete acceptorPeak;
                        return p->Intensity == maxIntensity;
                    });
#endif
                for ( auto p : allEnvs ) {
                    if ( p->getIntensity() == maxIntensity ) {
                        bestEnv = p;
                        break;
                    }
                }
                
                auto bestChargeXic = Peakfind(bestEnv->IndexedPeak->RetentionTime, identification->massToLookFor,
                                              bestEnv->ChargeState, idAcceptorFile, mbrTol);
                std::vector<IsotopicEnvelope*> envs2 = GetIsotopicEnvelopes(bestChargeXic, identification,
                                                                            bestEnv->ChargeState, true);

#ifdef ORIG
                double maxRt = envs2.Max([&] (std::any p) {
                        p::IndexedPeak::RetentionTime;
                    });
                double minRt = envs2.Min([&] (std::any p) {
                        p::IndexedPeak::RetentionTime;
                    });
#endif
                double maxRt = (*std::max(envs2.begin(), envs2.end(),
                                                 [&] ( auto l, auto r ) {
                                              return (*l)->IndexedPeak->RetentionTime < (*r)->IndexedPeak->RetentionTime;
                                                 }) )->IndexedPeak->RetentionTime;
                double minRt = (*std::min(envs2.begin(), envs2.end(),
                                                 [&] ( auto l, auto r ) {
                                              return (*l)->IndexedPeak->RetentionTime < (*r)->IndexedPeak->RetentionTime;
                                                 }) )->IndexedPeak->RetentionTime;

                acceptorPeak->IsotopicEnvelopes.insert(acceptorPeak->IsotopicEnvelopes.end(), envs2.begin(), envs2.end());
#ifdef ORIG
                acceptorPeak->IsotopicEnvelopes.AddRange(allEnvs.Where([&] (std::any p) {
                            return p::ChargeState != bestEnv->ChargeState &&
                                   p::IndexedPeak::RetentionTime < maxRt  &&
                                   p::IndexedPeak::RetentionTime > minRt;
                        }));
#endif
                for ( auto p : allEnvs ) {
                    if (p->ChargeState != bestEnv->ChargeState &&
                        p->IndexedPeak->RetentionTime < maxRt  &&
                        p->IndexedPeak->RetentionTime > minRt    ) {
                        acceptorPeak->IsotopicEnvelopes.push_back(p);
                    }
                }

                
                acceptorPeak->CalculateIntensityForThisFeature(Integrate);
                CutPeak(acceptorPeak, bestEnv->IndexedPeak->RetentionTime);
                
                //C# TO C++ CONVERTER TODO TASK: A 'delete acceptorPeak' statement was not added since
                // acceptorPeak was passed to a method or constructor. Handle memory management manually.
            }
            
            // save MBR results
#ifdef ORIG
            //for (auto peak : matchedPeaks.Where([&] (std::any p) {
            //            return p != nullptr && p::IsotopicEnvelopes::Any();
            //        }))
#endif
            for ( auto peak : matchedPeaks ) {
                if ( peak != nullptr && !peak->IsotopicEnvelopes.empty() ) {
                    ChromatographicPeak *oldPeak;
                    if (bestMbrHits.TryGetValue(peak->getIdentifications().front()->ModifiedSequence, oldPeak))
                    {
                        if (peak->Intensity > oldPeak->Intensity)
                        {
                            bestMbrHits[peak->getIdentifications().front()->ModifiedSequence] = peak;
                        }
                    }
                    else
                    {
                        bestMbrHits[peak->getIdentifications().front()->ModifiedSequence]= peak;
                    }
                }
            }
        }
        
        //foreach(var peak in *bestMbrHits)
        for ( auto peak : bestMbrHits )
        {
            _results->Peaks[idAcceptorFile].push_back(std::get<1>(peak));
        }
        RunErrorChecking (idAcceptorFile);
    }
        
    std::vector<RetentionTimeCalibDataPoint*> FlashLfqEngine::GetRtCalSpline(SpectraFileInfo *donor, SpectraFileInfo *acceptor)
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
            std::unordered_map<std::string, ChromatographicPeak*>::const_iterator acceptorFileBestMsmsPeaks_iterator = acceptorFileBestMsmsPeaks.find(acceptorPeak.Identifications.front()->ModifiedSequence);
            if (acceptorFileBestMsmsPeaks_iterator != acceptorFileBestMsmsPeaks.end())
            {
                currentBestPeak = acceptorFileBestMsmsPeaks_iterator->second;
                if (currentBestPeak::Intensity > acceptorPeak->Intensity)
                {
                    acceptorFileBestMsmsPeaks[acceptorPeak->getIdentifications().front()->ModifiedSequence] = acceptorPeak;
                }
            }
            else
            {
                currentBestPeak = acceptorFileBestMsmsPeaks_iterator->second;
                acceptorFileBestMsmsPeaks.emplace(acceptorPeak->getIdentifications().front()->ModifiedSequence, acceptorPeak);
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
                    donorFileBestMsmsPeaks[donorPeak->getIdentifications().front()->ModifiedSequence] = donorPeak;
                }
            }
            else
            {
                currentBestPeak = donorFileBestMsmsPeaks_iterator->second;
                donorFileBestMsmsPeaks.emplace(donorPeak->getIdentifications().front()->ModifiedSequence,
                                               donorPeak);
            }
        }

        // create RT calibration curve
        for (auto peak : acceptorFileBestMsmsPeaks)
        {
            ChromatographicPeak *acceptorFilePeak = std::get<1>(peak);

            ChromatographicPeak donorFilePeak;
            std::unordered_map<std::string, ChromatographicPeak*>::const_iterator donorFileBestMsmsPeaks_iterator = donorFileBestMsmsPeaks.find(std::get<0>(peak));
            if (donorFileBestMsmsPeaks_iterator != donorFileBestMsmsPeaks.end())
            {
                donorFilePeak = donorFileBestMsmsPeaks_iterator->second;
                RetentionTimeCalibDataPoint tempVar(&donorFilePeak, acceptorFilePeak);
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

    void FlashLfqEngine::RunErrorChecking(SpectraFileInfo *spectraFile)
    {
        if (!Silent)
        {
            std::cout << "Checking errors" << std::endl;
        }

#ifdef ORIG
        _results::Peaks[spectraFile].RemoveAll([&] (std::any p)
        {
            return p == nullptr || p::IsMbrPeak && !p::IsotopicEnvelopes::Any();
        });
#endif
        for ( auto p = _results->Peaks[spectraFile].begin() ; p != _results->Peaks[spectraFile].end(); p++ ) {
            if ( (*p)  == nullptr || ( (*p)->IsMbrPeak && !(*p)->IsotopicEnvelopes.empty()) ) {
                _results->Peaks[spectraFile].erase(p);
            }

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

#ifdef ORIG
        peaks.AddRange(peaksGroupedByApex.Values->Where([&] (std::any p)
        {
            return p != nullptr;
        }));
#endif
        for ( auto p = peaksGroupedByApex.begin(); p!= peaksGroupedByApex.end(); p++ ) {
            if ( std::get<1>(*p) != nullptr ) {
                peaks.push_back(std::get<1>(*p));
            }
        }
        _results->Peaks[spectraFile] = peaks;

        // merge multiple peaks for the same peptide within a time window
#ifdef ORIG
        peaks = _results::Peaks[spectraFile].Where([&] (std::any p)
        {
            return p::NumIdentificationsByFullSeq > 1;
        }).ToList();
#endif
        peaks.clear();
        for ( auto p :  _results->Peaks[spectraFile] ) {
            if ( p->getNumIdentificationsByFullSeq() > 1 ) {
                peaks.push_back(p);
            }
        }

#ifdef ORIG
        auto temp = _results::Peaks[spectraFile].Where([&] (std::any p)
        {
            return p->NumIdentificationsByFullSeq == 1;
        }).GroupBy([&] (std::any p)
        {
            p::Identifications::First().ModifiedSequence;
        }).ToList();
#endif
        std::vector<ChromatographicPeak *> temp1;
        for ( auto p : _results->Peaks[spectraFile] ) {
            if ( p->getNumIdentificationsByFullSeq() == 1 ) {
                temp1.push_back(p);
            }
        }
        std::function<bool(ChromatographicPeak*, ChromatographicPeak*)> f1 = [&] (ChromatographicPeak* l, ChromatographicPeak* r) {
            return l->getIdentifications().front()->ModifiedSequence < r->getIdentifications().front()->ModifiedSequence; };
        std::function<bool(ChromatographicPeak*, ChromatographicPeak*)> f2 = [&] (ChromatographicPeak* l, ChromatographicPeak* r) {
            return l->getIdentifications().front()->ModifiedSequence != r->getIdentifications().front()->ModifiedSequence; };
        std::vector<std::vector<ChromatographicPeak *>> temp = Group::GroupBy (temp1, f1, f2);

        
        for (auto sequence : temp)
        {
            if (sequence.size() == 1)
            {
                peaks.push_back(sequence.front());
                continue;
            }

            auto temp2 = sequence.Where([&] (std::any p)
            {
                return p::Apex != nullptr;
            }).ToList();

            std::unordered_set<ChromatographicPeak*> merged;
            for (auto peak : temp2)
            {
                if (std::find(merged.begin(), merged.end(), peak) != merged.end())
                {
                    continue;
                }

                auto toMerge = temp2.Where([&] (std::any p)
                {
                    return
                    std::abs(p::Apex::IndexedPeak::RetentionTime-peak->getApex()->IndexedPeak->RetentionTime)<RtTol &&
                    std::find(merged.begin(), merged.end(), p) == merged.end() &&
                    p != peak;
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
    }

    std::vector<IsotopicEnvelope*> FlashLfqEngine::GetIsotopicEnvelopes(std::vector<IndexedMassSpectralPeak*> &peaks,
                                                                        Identification *identification,
                                                                        int chargeState, bool matchBetweenRuns)
    {
        auto isotopicEnvelopes = std::vector<IsotopicEnvelope*>();
        auto isotopeMassShifts = _baseSequenceToIsotopicDistribution[identification->BaseSequence];

        if (isotopeMassShifts.size() < NumIsotopesRequired)
        {
            return isotopicEnvelopes;
        }

        PpmTolerance *isotopeTolerance = new PpmTolerance(IsotopePpmTolerance);

        auto theorIsotopeMasses = std::vector<double>(isotopeMassShifts.size());
        auto expIsotopeMasses = std::vector<double>(isotopeMassShifts.size());
        auto experimentalIsotopeAbundances = std::vector<double>(isotopeMassShifts.size());
#ifdef ORIG
        auto theoreticalIsotopeAbundances = isotopeMassShifts->Select([&] (std::any p)
        {
            p->Value;
        })->ToArray();
#endif
        std::vector<double> theoreticalIsotopeAbundances;
        for ( auto p : isotopeMassShifts ) {
            theoreticalIsotopeAbundances.push_back(std::get<1>(*p));
        }

        for (auto peak : peaks)
        {
            // calculate theoretical isotopes relative to observed peak
            Math::Clear(theorIsotopeMasses, 0, theorIsotopeMasses.size());
            Math::Clear(expIsotopeMasses, 0, expIsotopeMasses.size());
            Math::Clear(experimentalIsotopeAbundances, 0, experimentalIsotopeAbundances.size());

            double observedMass = Chemistry::ClassExtensions::ToMass(peak->Mz, chargeState);
            double theorMass = identification->massToLookFor;
            double mainPeakError = observedMass - theorMass;
            for (int i = 0; i < (int)theorIsotopeMasses.size(); i++)
            {
                theorIsotopeMasses[i] = mainPeakError + identification->massToLookFor +
                    std::get<0>(*isotopeMassShifts[i]);
            }

            if (matchBetweenRuns)
            {
                double unexpectedIsotopeMass = observedMass - Constants::C13MinusC12;
                auto unexpectedPeak = _peakIndexingEngine->GetIndexedPeak(unexpectedIsotopeMass,
                                                                          peak->ZeroBasedMs1ScanIndex,
                                                                          isotopeTolerance, chargeState);
                bool unexpectedIsotopePeakObserved = unexpectedPeak != nullptr &&
                    unexpectedPeak->Intensity / peak->Intensity > 0.3;

                if (unexpectedIsotopePeakObserved)
                {
                    continue;
                }
            }

            for (int t = 0; t < theorIsotopeMasses.size(); t++)
            {
                auto isotopePeak = _peakIndexingEngine->GetIndexedPeak(theorIsotopeMasses[t],
                                                                       peak->ZeroBasedMs1ScanIndex,
                                                                       isotopeTolerance, chargeState);

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

        //C# TO C++ CONVERTER TODO TASK: A 'delete isotopeTolerance' statement was not added since
        // isotopeTolerance was passed to a method or constructor. Handle memory management manually.
        return isotopicEnvelopes;
    }

    std::vector<IndexedMassSpectralPeak*> FlashLfqEngine::Peakfind(double idRetentionTime, double mass,
                                                                   int charge,
                                                                   SpectraFileInfo *spectraFileInfo,
                                                                   Tolerance *tolerance)
    {
        std::vector<IndexedMassSpectralPeak*> xic;

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
            auto peak = _peakIndexingEngine->GetIndexedPeak(mass, t, tolerance, charge);

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
            auto peak = _peakIndexingEngine->GetIndexedPeak(mass, t, tolerance, charge);

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
        //C# TO C++ CONVERTER TODO TASK: The 'Compare' parameter of std::sort produces a boolean value,
        // while the .NET Comparison parameter produces a tri-state result:
        //ORIGINAL LINE: xic.Sort((x, y) => x.RetentionTime.CompareTo(y.RetentionTime));
        std::sort(xic.begin(), xic.end(), [&] (IndexedMassSpectralPeak* x, IndexedMassSpectralPeak* y){
            return x->RetentionTime < y->RetentionTime;
        });

        return xic;
    }

    void FlashLfqEngine::CutPeak(ChromatographicPeak *peak, double identificationTime)
    {
        // find out if we need to split this peak by using the discrimination factor
        // this method assumes that the isotope envelopes in a chromatographic peak are
        // already sorted by MS1 scan number
        bool cutThisPeak = false;
        
        if (peak->IsotopicEnvelopes.size() < 5)
        {
            return;
        }
        
        auto timePointsForApexZ = peak->IsotopicEnvelopes.Where([&] (std::any p)  {
                return p->ChargeState == peak->getApex()->ChargeState;
            }).ToList();
        std::unordered_set<int> scanNumbers = std::unordered_set<int>(timePointsForApexZ.Select([&] (std::any p) {
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
            
            for (int i = apexIndex + iter; i < (int)timePointsForApexZ.size() && i >= 0; i += iter)
            {
                IsotopicEnvelope *timepoint = timePointsForApexZ[i];
                
                if ( valleyTimePoint == nullptr ||
                     timepoint->getIntensity() < valleyTimePoint->getIntensity())
                {
                    valleyTimePoint = timepoint;
                    indexOfValley = timePointsForApexZ.find(valleyTimePoint);
                }
                
                double discriminationFactor = (timepoint->getIntensity() - valleyTimePoint->getIntensity()) /
                    timepoint->getIntensity();
                
                if (discriminationFactor > MinDiscFactorToCutAt &&
                    (indexOfValley + iter < timePointsForApexZ.size() && indexOfValley + iter >= 0))
                {
                    IsotopicEnvelope *secondValleyTimepoint = timePointsForApexZ[indexOfValley + iter];
                    
                    discriminationFactor = (timepoint->getIntensity() - secondValleyTimepoint->getIntensity()) /
                        timepoint->getIntensity();
                    
                    if (discriminationFactor > MinDiscFactorToCutAt)
                    {
                        cutThisPeak = true;
                        break;
                    }
                    
                    int nextMs1ScanNum = -1;
                    for (int j = valleyTimePoint->IndexedPeak->ZeroBasedMs1ScanIndex - 1;
                         j < (int)_ms1Scans[peak->spectraFileInfo].size() && j >= 0; j += iter)
                    {
                        if (_ms1Scans[peak->spectraFileInfo][j]->OneBasedScanNumber >= 0 &&
                            _ms1Scans[peak->spectraFileInfo][j]->OneBasedScanNumber != valleyTimePoint->IndexedPeak->ZeroBasedMs1ScanIndex)
                        {
                            nextMs1ScanNum = j + 1;
                            break;
                        }
                    }
                    
                    if (std::find(scanNumbers.begin(), scanNumbers.end(), nextMs1ScanNum) == scanNumbers.end() )
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
#ifdef ORIG
                peak->IsotopicEnvelopes.RemoveAll([&] (std::any p) {
                        return p::IndexedPeak::RetentionTime <= valleyTimePoint->IndexedPeak->RetentionTime;
                    });
#endif
                for ( auto p = peak->IsotopicEnvelopes.begin(); p != peak->IsotopicEnvelopes.end(); p++ ) {
                    if ( (*p)->IndexedPeak->RetentionTime <= valleyTimePoint->IndexedPeak->RetentionTime ) {
                        peak->IsotopicEnvelopes.erase(p);
                    }
                }
            }
            else
            {
                // MS2 identification is to the left of the valley; remove all peaks right of the valley
#ifdef ORIG
                peak->IsotopicEnvelopes.RemoveAll([&] (std::any p) {
                        return p::IndexedPeak::RetentionTime >= valleyTimePoint->IndexedPeak->RetentionTime;
                    });
#endif
                for ( auto p = peak->IsotopicEnvelopes.begin(); p != peak->IsotopicEnvelopes.end(); p++ ) {
                    if ( (*p)->IndexedPeak->RetentionTime >= valleyTimePoint->IndexedPeak->RetentionTime ) {
                        peak->IsotopicEnvelopes.erase(p);
                    }
                }
            }
            
            // recalculate intensity for the peak
            peak->CalculateIntensityForThisFeature(Integrate);
            peak->SplitRT = valleyTimePoint->IndexedPeak->RetentionTime;
            
            // recursively cut
            CutPeak(peak, identificationTime);
        }
    }
}
