#include "IntensityNormalizationEngine.h"
#include "FlashLFQResults.h"
#include "Peptide.h"
#include "SpectraFileInfo.h"
#include "RectangularVectors.h"

#include "Group.h"
#include "Math.h"

namespace FlashLFQ
{

    IntensityNormalizationEngine::IntensityNormalizationEngine(FlashLfqResults *results, bool integrate, bool silent, int maxThreads) : results(results), integrate(integrate), silent(silent), maxThreads(maxThreads)
    {
    }

    void IntensityNormalizationEngine::NormalizeResults()
    {
        results->CalculatePeptideResults();

        // run normalization functions, recalculating intensity between each function
        if (!silent)
        {
            std::cout << "Normalizing fractions" << std::endl;
        }
        NormalizeFractions();
        results->CalculatePeptideResults();

        if (!silent)
        {
            std::cout << "Normalizing bioreps and conditions" << std::endl;
        }
        NormalizeBioreps();
        results->CalculatePeptideResults();

        if (!silent)
        {
            std::cout << "Normalizing techreps" << std::endl;
        }
        NormalizeTechreps();
        results->CalculatePeptideResults();
    }

    void IntensityNormalizationEngine::NormalizeTechreps()
    {
#ifdef ORIG
        auto peptides = results->PeptideModifiedSequences.Select([&] (std::any v)
        {
            v->Value;
        }).ToList();
#endif
        std::vector<Peptide*> peptides;
        for ( auto v: results->PeptideModifiedSequences ) {
            peptides.push_back(std::get<1>(v));
        }

#ifdef ORIG
        auto conditions = results->SpectraFiles.GroupBy([&] (std::any v)
        {
            v::Condition;
        });
#endif

        std::function<bool(SpectraFileInfo*,SpectraFileInfo*)> f1 = [&](SpectraFileInfo *l, SpectraFileInfo *r) {return l->Condition > r->Condition; } ;
        std::function<bool(SpectraFileInfo*,SpectraFileInfo*)> f2 = [&](SpectraFileInfo *l, SpectraFileInfo *r) {return l->Condition != r->Condition; } ;
        std::vector<std::vector<SpectraFileInfo*>> conditions = Group::GroupBy ( results->SpectraFiles, f1, f2); 
        
        for (auto condition : conditions)
        {
#ifdef ORIG
            auto bioreps = condition->GroupBy([&] (std::any v)
            {
                v::BiologicalReplicate;
            });
#endif
            std::function<bool(SpectraFileInfo*,SpectraFileInfo*)> f1 = [&](SpectraFileInfo *l, SpectraFileInfo *r) {return l->BiologicalReplicate > r->BiologicalReplicate; } ;
            std::function<bool(SpectraFileInfo*,SpectraFileInfo*)> f2 = [&](SpectraFileInfo *l, SpectraFileInfo *r) {return l->BiologicalReplicate != r->BiologicalReplicate; } ;
            std::vector<std::vector<SpectraFileInfo*>> bioreps = Group::GroupBy ( condition, f1, f2); 

            for (auto biorep : bioreps)
            {
#ifdef ORIG
                auto fractions = biorep->GroupBy([&] (std::any v)
                {
                    v::Fraction;
                });
#endif
                std::function<bool(SpectraFileInfo*,SpectraFileInfo*)> f1 = [&](SpectraFileInfo *l, SpectraFileInfo *r) {return l->Fraction> r->Fraction; } ;
                std::function<bool(SpectraFileInfo*,SpectraFileInfo*)> f2 = [&](SpectraFileInfo *l, SpectraFileInfo *r) {return l->Fraction != r->Fraction; } ;
                std::vector<std::vector<SpectraFileInfo*>> fractions = Group::GroupBy ( biorep, f1, f2); 

                for (auto fraction : fractions)
                {
                    std::vector<SpectraFileInfo*> techreps;
                    techreps.insert(techreps.end(), fraction.begin(), fraction.end());

                    for (int t = 1; t < (int)techreps.size(); t++)
                    {
                        std::vector<double> foldChanges;

                        for (int p = 0; p < (int)peptides.size(); p++)
                        {
                            double techrep1Intensity = peptides[p]->GetIntensity(techreps[0]);
                            double techrepTIntensity = peptides[p]->GetIntensity(techreps[t]);

                            if (techrep1Intensity > 0 && techrepTIntensity > 0)
                            {
                                foldChanges.push_back(techrepTIntensity / techrep1Intensity);
                            }
                        }

                        if (!foldChanges.empty())
                        {
                            // TODO: throw an exception?
                            return;
                        }

                        //double medianFoldChange = foldChanges.Median();
                        double medianFoldChange = Math::Median(foldChanges);
                        double normalizationFactor = 1.0 / medianFoldChange;

                        // normalize to median fold-change
                        for (auto peak : results->Peaks[techreps[t]])
                        {
                            for (auto isotopeEnvelope : peak->IsotopicEnvelopes)
                            {
                                isotopeEnvelope->Normalize(normalizationFactor);
                            }

                            // recalculate intensity after normalization
                            peak->CalculateIntensityForThisFeature(integrate);
                        }
                    }
                }
            }
        }
    }

    void IntensityNormalizationEngine::NormalizeFractions()
    {
#ifdef ORIG
        if (results->SpectraFiles.Max([&] (std::any p)
        {
            p::Fraction;
        }) == 0);
#endif
        bool all_are_zero = true;
        for ( auto p: results->SpectraFiles ) {
            if ( p->Fraction != 0 ) {
                all_are_zero = false;
            }
        }
        if ( all_are_zero )
        {
            return;
        }

#ifdef ORIG
        auto peptides = results->PeptideModifiedSequences.Select([&] (std::any v)
        {
            v->Value;
        }).ToList();
#endif
        std::vector<Peptide*> peptides;
        for ( auto v: results->PeptideModifiedSequences ) {
            peptides.push_back(std::get<1>(v));
        }
        
#ifdef ORIG
        auto conditions = results->SpectraFiles.Select([&] (std::any p)
        {
            p::Condition;
        }).Distinct().OrderBy([&] (std::any p)
        {
            return p;
        }).ToList();
#endif
        std::vector<std::string> conditions;
        for ( auto p : results->SpectraFiles ) {
            bool found = false;
            for ( auto v: conditions ) {
                if ( v == p->Condition ) {
                    found = true;
                    break;
                }
            }
            if ( !found ) {
                conditions.push_back (p->Condition);
            }            
        }
        std::sort ( conditions.begin(), conditions.end() );
        
#ifdef ORIG
        auto filesForCond1Biorep1 = results->SpectraFiles.Where([&] (std::any p)
        {
            return p->Condition == conditions[0] && p->BiologicalReplicate == 0 && p->TechnicalReplicate == 0;
        }).ToList();
#endif
        std::vector<SpectraFileInfo*> filesForCond1Biorep1;
        for ( auto p: results->SpectraFiles ) {
            if ( p->Condition == conditions[0] && p->BiologicalReplicate == 0 &&
                 p->TechnicalReplicate == 0 ) {
                filesForCond1Biorep1.push_back (p);
            }
        }

        
        for (auto condition : conditions)
        {
#ifdef ORIG
            auto filesForThisCondition = results->SpectraFiles.Where([&] (std::any p)
            {
                p::Condition->Equals(condition);
            }).ToList();
#endif
            std::vector<SpectraFileInfo*> filesForThisCondition;
            for ( auto p: results->SpectraFiles ) {
                if ( p->Condition == condition ) {
                    filesForThisCondition.push_back (p);
                }
            }
            
#ifdef ORIG
            int numB = filesForThisCondition.Select([&] (std::any p)
            {
                p::BiologicalReplicate;
            }).Distinct()->Count();
#endif
            std::vector<int> tempvec;
            for ( auto p : filesForThisCondition ) {
                bool found = false;
                for ( auto v: tempvec ) {
                    if ( v == p->BiologicalReplicate ) {
                        found = true;
                        break;
                    }
                }
                if ( !found ) {
                    tempvec.push_back (p->BiologicalReplicate);
                }            
            }
            int numB = tempvec.size();
            
            
            for (int b = 0; b < numB; b++)
            {
                // condition 1 biorep 1 is the reference, don't normalize it
                // if (b == 0 && conditions.find(condition) == 0)
                bool cond_found = false;
                for ( auto c: conditions ) {
                    if ( c == condition ) {
                        cond_found = true;
                        break;
                    }
                }
                if (b == 0 && !cond_found )
                {
                    continue;
                }

                // run the normalization function
                if (!silent)
                {
                    std::cout << "Normalizing condition \"" << condition << "\" biorep " << (b + 1) << std::endl;
                }

#ifdef ORIG
                auto filesForThisBiorep = filesForThisCondition.Where([&] (std::any p)
                {
                    return p->BiologicalReplicate == b && p->TechnicalReplicate == 0;
                });
#endif

                std::vector<SpectraFileInfo*> filesForThisBiorep;
                for ( auto p: filesForThisCondition ) {
                    if ( p->BiologicalReplicate == b && p->TechnicalReplicate == 0 ) {
                        filesForThisBiorep.push_back ( p);
                    }
                }
                
#ifdef ORIG
                int numF = std::max(filesForCond1Biorep1.Max([&] (std::any p)
                {
                    p::Fraction;
                }), filesForThisBiorep->Max([&] (std::any p)
                {
                    p::Fraction;
                })) + 1;
#endif
                int max1 = filesForCond1Biorep1.front()->Fraction;
                for ( auto p: filesForCond1Biorep1 ) {
                    if ( p->Fraction > max1 ) {
                        max1 = p->Fraction;
                    }
                }
                int max2 = filesForThisBiorep.front()->Fraction;
                for ( auto p: filesForThisBiorep ) {
                    if ( p->Fraction > max2 ) {
                        max2 = p->Fraction;
                    }
                }
                int numF = std::max(max1, max2);
                
                // only normalize on peptides seen in both bioreps
                std::vector<Peptide*> seenInBothBioreps;
                for (int p = 0; p < (int)peptides.size(); p++)
                {
                    bool seenInBiorep1 = false;
                    bool seenInBiorep2 = false;

                    for (auto file : filesForCond1Biorep1)
                    {
                        if (peptides[p]->GetIntensity(file) > 0)
                        {
                            seenInBiorep1 = true;
                        }
                    }

                    for (auto file : filesForThisBiorep)
                    {
                        if (peptides[p]->GetIntensity(file) > 0)
                        {
                            seenInBiorep2 = true;
                        }
                    }

                    if (seenInBiorep1 && seenInBiorep2)
                    {
                        seenInBothBioreps.push_back(peptides[p]);
                    }
                }

                // we're only normalizing on a subset of data here because it might take too long to do the whole set
                std::vector<SpectraFileInfo *> allfiles;
                allfiles.insert(allfiles.end(), filesForThisBiorep.begin(), filesForThisBiorep.end() );
                allfiles.insert(allfiles.end(), filesForCond1Biorep1.begin(), filesForCond1Biorep1.end() );   
                seenInBothBioreps = SubsetData(seenInBothBioreps, allfiles );                                     

                // add the data to the array to set up for the normalization function
                int numP = seenInBothBioreps.size();
                //C# TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class
                // reproduces the rectangular array initialization that is automatic in C#:
                //ORIGINAL LINE: double[,,] myIntensityArray = new double[numP, 2, numF];
                std::vector<std::vector<std::vector<double>>> myIntensityArray = RectangularVectors::RectangularDoubleVector(numP, 2, numF);

                for (int p = 0; p < numP; p++)
                {
                    auto peptide = seenInBothBioreps[p];

                    for (auto file : filesForCond1Biorep1)
                    {
                        myIntensityArray[p][0][file->Fraction] = peptide->GetIntensity(file);
                    }

                    for (auto file : filesForThisBiorep)
                    {
                        myIntensityArray[p][1][file->Fraction] = peptide->GetIntensity(file);
                    }
                }

                // solve for normalization factors
                auto normFactors = GetNormalizationFactors(myIntensityArray, numP, 2, numF, maxThreads);

#ifdef ORIG
                if (normFactors.All([&] (std::any p)
                {
                    return p == 1.0;
                }) && !silent);
#endif
                bool all_are_one = true;
                for ( auto p: normFactors ) {
                    if (p != 1.0) {
                        all_are_one = false;
                        break;
                    }
                }
                if ( all_are_one && !silent) 
                {
                    std::cout << "Warning: Could not solve for optimal normalization factors for condition \"" << condition << "\" biorep " << (b + 1) << std::endl;
                }

                // multiply each peak's isotope envelopes by its file's normalization factor
                for (auto spectraFile : filesForThisBiorep)
                {
                    for (auto peak : results->Peaks[spectraFile])
                    {
                        for (auto isotopeEnvelope : peak->IsotopicEnvelopes)
                        {
                            isotopeEnvelope->Normalize(normFactors[spectraFile->Fraction]);
                        }

                        // recalculate intensity after normalization
                        peak->CalculateIntensityForThisFeature(integrate);
                    }
                }
            }
        }
    }

    void IntensityNormalizationEngine::NormalizeBioreps()
    {
#ifdef ORIG
        auto peptides = results->PeptideModifiedSequences.Select([&] (std::any v)
        {
            v->Value;
        }).ToList();
#endif
        std::vector<Peptide*> peptides;
        for ( auto v: results->PeptideModifiedSequences ) {
            peptides.push_back(std::get<1>(v));
        }

#ifdef ORIG
        auto conditions = results->SpectraFiles.GroupBy([&] (std::any v)
        {
            v::Condition;
        }).ToList();
#endif
        std::function<bool(SpectraFileInfo*,SpectraFileInfo*)> f1 = [&](SpectraFileInfo *l, SpectraFileInfo *r) {return l->Condition > r->Condition; } ;
        std::function<bool(SpectraFileInfo*,SpectraFileInfo*)> f2 = [&](SpectraFileInfo *l, SpectraFileInfo *r) {return l->Condition != r->Condition; } ;
        std::vector<std::vector<SpectraFileInfo*>> conditions = Group::GroupBy ( results->SpectraFiles, f1, f2); 

        
        //C# TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class
        // reproduces the rectangular
        // array initialization that is automatic in C#:
        // ORIGINAL LINE: double[,] biorepIntensityPair = new double[peptides.Count, 2];
        std::vector<std::vector<double>> biorepIntensityPair = RectangularVectors::RectangularDoubleVector(peptides.size(), 2);

#ifdef ORIG
        auto firstConditionFirstBiorep = conditions.front().Where([&] (std::any v)
        {
            return v->BiologicalReplicate == 0 && v->TechnicalReplicate == 0;
        });
#endif
        std::vector<SpectraFileInfo*> firstConditionFirstBiorep;
        for ( auto v: conditions.front() ) {
            if ( v->BiologicalReplicate == 0 && v->TechnicalReplicate == 0 ) {
                firstConditionFirstBiorep.push_back (v);
            }
        }

        for (auto file : firstConditionFirstBiorep)
        {
            for (int p = 0; p < (int) peptides.size(); p++)
            {
                biorepIntensityPair[p][0] += peptides[p]->GetIntensity(file);
            }
        }

        for (auto condition : conditions)
        {
#ifdef ORIG
            auto bioreps = condition.GroupBy([&] (std::any v)
            {
                v::BiologicalReplicate;
            });
#endif
            std::function<bool(SpectraFileInfo*,SpectraFileInfo*)> f1 = [&](SpectraFileInfo *l, SpectraFileInfo *r) {return l->BiologicalReplicate > r->BiologicalReplicate; } ;
            std::function<bool(SpectraFileInfo*,SpectraFileInfo*)> f2 = [&](SpectraFileInfo *l, SpectraFileInfo *r) {return l->BiologicalReplicate != r->BiologicalReplicate; } ;
            std::vector<std::vector<SpectraFileInfo*>> bioreps = Group::GroupBy ( condition, f1, f2); 


            for (auto biorep : bioreps)
            {
                for (int p = 0; p < (int) peptides.size(); p++)
                {
                    biorepIntensityPair[p][1] = 0;
                }

#ifdef ORIG
                auto fractions = biorep->GroupBy([&] (std::any v)
                {
                    v::Fraction;
                });
#endif
                std::function<bool(SpectraFileInfo*,SpectraFileInfo*)> f1 = [&](SpectraFileInfo *l, SpectraFileInfo *r) {return l->Fraction> r->Fraction; } ;
                std::function<bool(SpectraFileInfo*,SpectraFileInfo*)> f2 = [&](SpectraFileInfo *l, SpectraFileInfo *r) {return l->Fraction != r->Fraction; } ;
                std::vector<std::vector<SpectraFileInfo*>> fractions = Group::GroupBy ( biorep, f1, f2); 

                for (auto fraction : fractions)
                {
#ifdef ORIG
                    auto firstTechrep = fraction->Where([&] (std::any v)
                    {
                        return v->TechnicalReplicate == 0;
                    }).First();
#endif
                    std::vector<SpectraFileInfo *> tempv;
                    for ( auto v: fraction ) {
                        if ( v->TechnicalReplicate == 0 ) {
                            tempv.push_back(v);
                        }
                    }
                    auto firstTechrep = tempv.front();
                    
                    for (int p = 0; p < (int) peptides.size(); p++)
                    {
                        biorepIntensityPair[p][1] += peptides[p]->GetIntensity(firstTechrep);
                    }
                }

                std::vector<double> foldChanges;

                for (int p = 0; p < (int)peptides.size(); p++)
                {
                    if (biorepIntensityPair[p][0] > 0 && biorepIntensityPair[p][1] > 0)
                    {
                        foldChanges.push_back(biorepIntensityPair[p][1] / biorepIntensityPair[p][0]);
                    }
                }

                if (!foldChanges.empty())
                {
                    // TODO: throw an exception?
                    return;
                }

                //double medianFoldChange = foldChanges.Median();
                double medianFoldChange = Math::Median(foldChanges);
                double normalizationFactor = 1.0 / medianFoldChange;

                // normalize to median fold-change
                for (auto file : biorep)
                {
                    for (auto peak : results->Peaks[file])
                    {
                        for (auto isotopeEnvelope : peak->IsotopicEnvelopes)
                        {
                            isotopeEnvelope->Normalize(normalizationFactor);
                        }

                        // recalculate intensity after normalization
                        peak->CalculateIntensityForThisFeature(integrate);
                    }
                }
            }
        }
    }

    std::vector<Peptide*> IntensityNormalizationEngine::SubsetData(std::vector<Peptide*> &initialList,
                                                                   std::vector<SpectraFileInfo*> &spectraFiles)
    {
        std::vector<std::vector<SpectraFileInfo*>> bothBioreps(2);
#ifdef ORIG
        auto temp1 = spectraFiles.GroupBy([&] (std::any p)
        {
            p::Condition;
        }).ToList();
#endif
        std::function<bool(SpectraFileInfo*,SpectraFileInfo*)> f1 = [&](SpectraFileInfo *l, SpectraFileInfo *r) {return l->Condition> r->Condition; } ;
        std::function<bool(SpectraFileInfo*,SpectraFileInfo*)> f2 = [&](SpectraFileInfo *l, SpectraFileInfo *r) {return l->Condition != r->Condition; } ;
        std::vector<std::vector<SpectraFileInfo*>> temp1 = Group::GroupBy ( spectraFiles, f1, f2); 
        
        if (temp1.size() == 1)
        {
            // normalizing bioreps within a condition
#ifdef ORIG
            auto temp2 = spectraFiles.GroupBy([&] (std::any p)
            {
                p::BiologicalReplicate;
            }).ToList();
#endif
            std::function<bool(SpectraFileInfo*,SpectraFileInfo*)> f1 = [&](SpectraFileInfo *l, SpectraFileInfo *r) {return l->BiologicalReplicate> r->BiologicalReplicate; } ;
            std::function<bool(SpectraFileInfo*,SpectraFileInfo*)> f2 = [&](SpectraFileInfo *l, SpectraFileInfo *r) {return l->BiologicalReplicate != r->BiologicalReplicate; } ;
            std::vector<std::vector<SpectraFileInfo*>> temp2 = Group::GroupBy (spectraFiles, f1, f2); 

            bothBioreps[0] = temp2[0]; //.ToList();
            bothBioreps[1] = temp2[1]; //.ToList();
        }
        else
        {
            // normalizing bioreps between conditions
            bothBioreps[0] = temp1[0];//.ToList();
            bothBioreps[1] = temp1[1];//.ToList();
        }

        std::unordered_set<Peptide*> subsetList;
#ifdef ORIG
        int maxFractionIndex = bothBioreps.SelectMany([&] (std::any p)
        {
            return p;
        }).Max([&] (std::any v)
        {
            v::Fraction;
        });
#endif
        int maxFractionIndex=0;
        for ( auto p: bothBioreps ) {
            for ( auto v: p ) {
                if (v->Fraction > maxFractionIndex) {
                    maxFractionIndex = v->Fraction;
                }
            }
        }
        
        for (auto biorep : bothBioreps)
        {
#ifdef ORIG
            std::vector<int> fractions = biorep.Select([&] (std::any p)
            {
                p::Fraction;
            }).Distinct().ToList();
#endif
            std::vector<int> fractions;
            for ( auto p: biorep ) {
                bool found = false;
                for ( auto f: fractions ) {
                    if ( f == p->Fraction ) {
                        found = true;
                        break;
                    }
                }
                if (!found ) {
                    fractions.push_back (p->Fraction);
                }
            }

            int numToAddPerFraction = numPeptidesDesiredInMatrix / fractions.size();
            if (numToAddPerFraction < numPeptidesDesiredFromEachFraction)
            {
                numToAddPerFraction = numPeptidesDesiredFromEachFraction;
            }

            std::vector<int> peptidesAddedPerFraction(fractions.size());
            std::vector<std::deque<Peptide*>> peptidesObservedInEachFraction(fractions.size());

            for (auto file : biorep)
            {
                if (peptidesObservedInEachFraction[file->Fraction].empty())
                {
#ifdef ORIG
                    peptidesObservedInEachFraction[file->Fraction] = std::deque<Peptide*>(initialList.Where([&] (std::any p)
                    {
                        return p::GetIntensity(file) > 0;
                    }).OrderByDescending([&] (std::any p)
                    {
                        p::GetIntensity(file);
                    }));
#endif
                    std::vector<Peptide*> tempList;
                    for ( auto p: initialList ) {
                        if ( p->GetIntensity(file) > 0 ) {
                            tempList.push_back(p);
                        }
                    }
                    std::sort(tempList.begin(), tempList.end(), [&](Peptide *l, Peptide *r) {
                            return l->GetIntensity(file) > r->GetIntensity(file);
                        });
                    peptidesObservedInEachFraction[file->Fraction].insert(peptidesObservedInEachFraction[file->Fraction].end(), tempList.begin(), tempList.end());
                }
            }

            for (auto fraction : fractions)
            {
                while (peptidesAddedPerFraction[fraction] < numToAddPerFraction &&
                       !peptidesObservedInEachFraction[fraction].empty())
                {
                    Peptide* peptide = peptidesObservedInEachFraction[fraction].front();
                    peptidesObservedInEachFraction[fraction].pop_front();

                    // don't need to check if the return list already contains the peptide because it's a HashSet (no duplicates are allowed)
                    subsetList.insert(peptide);

                    // this peptide is in the return list regardless of whether or not it was actually just added;
                    // we just want to guarantee this fraction has 500 peptides in the return list to normalize with
                    peptidesAddedPerFraction[fraction]++;
                }
            }
        }

        std::vector<Peptide *>retvec;
        for ( auto p: subsetList) {
            retvec.push_back(p);
        }
        return retvec; 
    }

    std::vector<double> IntensityNormalizationEngine::GetNormalizationFactors(
        std::vector<std::vector<std::vector<double>>> &peptideIntensities,
        int numP, int numB, int numF, int maxThreads)
    {
        double step = 0.01;
        //std::any locker = std::any();

        // initialize normalization factors to 1.0
        // normalization factor optimization must improve on these to be valid
        double bestError = 0;
        std::vector<double> bestNormFactors(numF);
        for (int i = 0; i < (int) bestNormFactors.size(); i++)
        {
            bestNormFactors[i] = 1.0;
        }

        // constraint (normalization factors must be >0.3 and <3
        auto parameterArray = std::vector<ParameterBounds*>(numF);
        for (int f = 0; f < numF; f++)
        {
            parameterArray[f] = new ParameterBounds(0.3, 3, Transform::Linear);
        }

        //TODO: put this into a helper method to avoid code repetition...
        // calculate the error between bioreps if all norm factors are 1 (initial error)
        {
            //C# TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class
            // reproduces the rectangular array initialization that is automatic in C#:
            //ORIGINAL LINE: double[,] originalBiorepIntensities = new double[numP, numB];
            std::vector<std::vector<double>> originalBiorepIntensities = RectangularVectors::RectangularDoubleVector(numP, numB);
            std::vector<double> temp(2);

            for (int p = 0; p < numP; p++)
            {
                for (int b = 0; b < numB; b++)
                {
                    for (int f = 0; f < numF; f++)
                    {
                        originalBiorepIntensities[p][b] += peptideIntensities[p][b][f];
                    }
                }
            }

            for (int p = 0; p < numP; p++)
            {
                for (int b2 = 1; b2 < numB; b2++)
                {
                    temp[0] = originalBiorepIntensities[p][0];
                    temp[1] = originalBiorepIntensities[p][b2];

                    // calculate initial error (error if all norm factors are 1)
                    // error metric is sum square error of coefficient of variation of each peptide
                    //double coefficientOfVariation = Statistics::StandardDeviation(temp) / temp.Average();
                    double coefficientOfVariation = Math::StandardDeviation(temp) / Math::Mean(temp);
                    bestError += std::pow(coefficientOfVariation, 2);
                }
            }
        }

        int startN = static_cast<int>(parameterArray[0]->Min / step);
        int endN = static_cast<int>(parameterArray[0]->Max / step);

#ifdef ORIG
        //ParallelOptions *tempVar = new ParallelOptions();
        //tempVar->MaxDegreeOfParallelism = maxThreads;
        //Parallel::For(startN, endN, tempVar, [&] (std::any n)
#endif
        for ( int n=startN; n<endN; n++)  {
            double startPosition = n * step;
    
            auto biorepIntensities = RectangularVectors::RectangularDoubleVector(numP, numB);
            std::vector<double> temp(2);
    
            // define minimization metric
            std::function<OptimizerResult*(std::vector<double>)> minimize = [&] (std::vector<double> v)
            {
                // sum the intensities with the current normalization factors
                // Array::Clear(biorepIntensities, 0, biorepIntensities.size());
                RectangularVectors::Clear (biorepIntensities, 0, biorepIntensities.size() );
                
                for (int p = 0; p < numP; p++) {
                    for (int b = 0; b < numB; b++) {
                        for (int f = 0; f < numF; f++) {
                            if (b == 0) {
                                biorepIntensities[p][b] += peptideIntensities[p][b][f];
                            }
                            else  {
                                biorepIntensities[p][b] += peptideIntensities[p][b][f] * v[f];
                            }
                        }
                    }
                }
                
                // calculate the error for these normalization factors
                double candidateError = 0;
                for (int p = 0; p < numP; p++) {
                    for (int b2 = 1; b2 < numB; b2++) {
                        temp[0] = biorepIntensities[p][0];
                            temp[1] = biorepIntensities[p][b2];
                            
                            // error metric is sum square error of coefficient of variation of each peptide
                            //double coefficientOfVariation = Statistics::StandardDeviation(temp) / temp.Average();
                            double coefficientOfVariation = Math::StandardDeviation(temp) / Math::Mean(temp);
                            candidateError += std::pow(coefficientOfVariation, 2);
                    }
                }
                
                return new OptimizerResult(v, candidateError);
            };
    
            // create optimizer
            NelderMeadWithStartPoints tempVar2(parameterArray, 8, 0.001, 10, 0, 0, 1, 2, -0.5, 0.5, startPosition);
            OptimizerResult *result = (&tempVar2)->OptimizeBest(minimize);
    
            double error = result->getError();
            std::vector<double> normFactors = result->getParameterSet();
    
            if (error < bestError)  {
                bestError = error;
                bestNormFactors = normFactors;
            }
        }

        //C# TO C++ CONVERTER TODO TASK: A 'delete tempVar' statement was not added since
        // tempVar was passed to a method or constructor. Handle memory management manually.
        return bestNormFactors;
    }
}
