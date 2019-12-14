#include "IntensityNormalizationEngine.h"
#include "FlashLFQResults.h"
#include "Peptide.h"
#include "SpectraFileInfo.h"

using namespace FlashLFQ::BoundedNelderMeadOptimizer;
using namespace MathNet::Numerics::Statistics;
using namespace SharpLearning::Optimization;

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
        auto peptides = results->PeptideModifiedSequences.Select([&] (std::any v)
        {
            v->Value;
        }).ToList();
        auto conditions = results->SpectraFiles.GroupBy([&] (std::any v)
        {
            v::Condition;
        });

        for (auto condition : conditions)
        {
            auto bioreps = condition->GroupBy([&] (std::any v)
            {
                v::BiologicalReplicate;
            });

            for (auto biorep : bioreps)
            {
                auto fractions = biorep->GroupBy([&] (std::any v)
                {
                    v::Fraction;
                });

                for (auto fraction : fractions)
                {
                    auto techreps = fraction->ToList();

                    for (int t = 1; t < techreps.size(); t++)
                    {
                        std::vector<double> foldChanges;

                        for (int p = 0; p < peptides.size(); p++)
                        {
                            double techrep1Intensity = peptides[p].GetIntensity(techreps[0]);
                            double techrepTIntensity = peptides[p].GetIntensity(techreps[t]);

                            if (techrep1Intensity > 0 && techrepTIntensity > 0)
                            {
                                foldChanges.push_back(techrepTIntensity / techrep1Intensity);
                            }
                        }

                        if (!foldChanges.Any())
                        {
                            // TODO: throw an exception?
                            return;
                        }

                        double medianFoldChange = foldChanges.Median();
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
        if (results->SpectraFiles.Max([&] (std::any p)
        {
            p::Fraction;
        }) == 0)
        {
            return;
        }

        auto peptides = results->PeptideModifiedSequences.Select([&] (std::any v)
        {
            v->Value;
        }).ToList();
        auto conditions = results->SpectraFiles.Select([&] (std::any p)
        {
            p::Condition;
        }).Distinct().OrderBy([&] (std::any p)
        {
            return p;
        }).ToList();
        auto filesForCond1Biorep1 = results->SpectraFiles.Where([&] (std::any p)
        {
            return p->Condition == conditions[0] && p->BiologicalReplicate == 0 && p->TechnicalReplicate == 0;
        }).ToList();

        for (auto condition : conditions)
        {
            auto filesForThisCondition = results->SpectraFiles.Where([&] (std::any p)
            {
                p::Condition->Equals(condition);
            }).ToList();

            int numB = filesForThisCondition.Select([&] (std::any p)
            {
                p::BiologicalReplicate;
            }).Distinct()->Count();

            for (int b = 0; b < numB; b++)
            {
                // condition 1 biorep 1 is the reference, don't normalize it
                if (b == 0 && conditions.find(condition) == 0)
                {
                    continue;
                }

                // run the normalization function
                if (!silent)
                {
                    std::cout << "Normalizing condition \"" << condition << "\" biorep " << (b + 1) << std::endl;
                }

                auto filesForThisBiorep = filesForThisCondition.Where([&] (std::any p)
                {
                    return p->BiologicalReplicate == b && p->TechnicalReplicate == 0;
                });

                int numF = std::max(filesForCond1Biorep1.Max([&] (std::any p)
                {
                    p::Fraction;
                }), filesForThisBiorep->Max([&] (std::any p)
                {
                    p::Fraction;
                })) + 1;

                // only normalize on peptides seen in both bioreps
                std::vector<Peptide*> seenInBothBioreps;
                for (int p = 0; p < peptides.size(); p++)
                {
                    bool seenInBiorep1 = false;
                    bool seenInBiorep2 = false;

                    for (auto file : filesForCond1Biorep1)
                    {
                        if (peptides[p].GetIntensity(file) > 0)
                        {
                            seenInBiorep1 = true;
                        }
                    }

                    for (auto file : filesForThisBiorep)
                    {
                        if (peptides[p].GetIntensity(file) > 0)
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
                seenInBothBioreps = SubsetData(seenInBothBioreps, filesForThisBiorep->Concat(filesForCond1Biorep1)->ToList());

                // add the data to the array to set up for the normalization function
                int numP = seenInBothBioreps.size();
//C# TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in C#:
//ORIGINAL LINE: double[,,] myIntensityArray = new double[numP, 2, numF];
                std::vector<std::vector<std::vector<double>>> myIntensityArray = RectangularVectors::RectangularDoubleVector(numP, 2, numF);

                for (int p = 0; p < numP; p++)
                {
                    auto peptide = seenInBothBioreps[p];

                    for (auto file : filesForCond1Biorep1)
                    {
                        myIntensityArray[p][0][file.Fraction] = peptide->GetIntensity(file);
                    }

                    for (auto file : filesForThisBiorep)
                    {
                        myIntensityArray[p][1][file->Fraction] = peptide->GetIntensity(file);
                    }
                }

                // solve for normalization factors
                auto normFactors = GetNormalizationFactors(myIntensityArray, numP, 2, numF, maxThreads);
                if (normFactors.All([&] (std::any p)
                {
                    return p == 1.0;
                }) && !silent)
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
        auto peptides = results->PeptideModifiedSequences.Select([&] (std::any v)
        {
            v->Value;
        }).ToList();
        auto conditions = results->SpectraFiles.GroupBy([&] (std::any v)
        {
            v::Condition;
        }).ToList();

//C# TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in C#:
//ORIGINAL LINE: double[,] biorepIntensityPair = new double[peptides.Count, 2];
        std::vector<std::vector<double>> biorepIntensityPair = RectangularVectors::RectangularDoubleVector(peptides.size(), 2);

        auto firstConditionFirstBiorep = conditions.front().Where([&] (std::any v)
        {
            return v->BiologicalReplicate == 0 && v->TechnicalReplicate == 0;
        });

        for (auto file : firstConditionFirstBiorep)
        {
            for (int p = 0; p < peptides.size(); p++)
            {
                biorepIntensityPair[p][0] += peptides[p].GetIntensity(file);
            }
        }

        for (auto condition : conditions)
        {
            auto bioreps = condition.GroupBy([&] (std::any v)
            {
                v::BiologicalReplicate;
            });

            for (auto biorep : bioreps)
            {
                for (int p = 0; p < peptides.size(); p++)
                {
                    biorepIntensityPair[p][1] = 0;
                }

                auto fractions = biorep->GroupBy([&] (std::any v)
                {
                    v::Fraction;
                });

                for (auto fraction : fractions)
                {
                    auto firstTechrep = fraction->Where([&] (std::any v)
                    {
                        return v->TechnicalReplicate == 0;
                    }).First();

                    for (int p = 0; p < peptides.size(); p++)
                    {
                        biorepIntensityPair[p][1] += peptides[p].GetIntensity(firstTechrep);
                    }
                }

                std::vector<double> foldChanges;

                for (int p = 0; p < peptides.size(); p++)
                {
                    if (biorepIntensityPair[p][0] > 0 && biorepIntensityPair[p][1] > 0)
                    {
                        foldChanges.push_back(biorepIntensityPair[p][1] / biorepIntensityPair[p][0]);
                    }
                }

                if (!foldChanges.Any())
                {
                    // TODO: throw an exception?
                    return;
                }

                double medianFoldChange = foldChanges.Median();
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

    std::vector<Peptide*> IntensityNormalizationEngine::SubsetData(std::vector<Peptide*> &initialList, std::vector<SpectraFileInfo*> &spectraFiles)
    {
        std::vector<std::vector<SpectraFileInfo*>> bothBioreps(2);
        auto temp1 = spectraFiles.GroupBy([&] (std::any p)
        {
            p::Condition;
        }).ToList();
        if (temp1.size()() == 1)
        {
            // normalizing bioreps within a condition
            auto temp2 = spectraFiles.GroupBy([&] (std::any p)
            {
                p::BiologicalReplicate;
            }).ToList();
            bothBioreps[0] = temp2[0].ToList();
            bothBioreps[1] = temp2[1].ToList();
        }
        else
        {
            // normalizing bioreps between conditions
            bothBioreps[0] = temp1[0].ToList();
            bothBioreps[1] = temp1[1].ToList();
        }

        std::unordered_set<Peptide*> subsetList;
        int maxFractionIndex = bothBioreps.SelectMany([&] (std::any p)
        {
            return p;
        }).Max([&] (std::any v)
        {
            v::Fraction;
        });

        for (auto biorep : bothBioreps)
        {
            std::vector<int> fractions = biorep.Select([&] (std::any p)
            {
                p::Fraction;
            }).Distinct().ToList();

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
                    peptidesObservedInEachFraction[file->Fraction] = std::deque<Peptide*>(initialList.Where([&] (std::any p)
                    {
                        return p::GetIntensity(file) > 0;
                    }).OrderByDescending([&] (std::any p)
                    {
                        p::GetIntensity(file);
                    }));
                }
            }

            for (auto fraction : fractions)
            {
                while (peptidesAddedPerFraction[fraction] < numToAddPerFraction && peptidesObservedInEachFraction[fraction].Any())
                {
                    auto peptide = peptidesObservedInEachFraction[fraction].pop_front();

                    // don't need to check if the return list already contains the peptide because it's a HashSet (no duplicates are allowed)
                    subsetList.insert(peptide);

                    // this peptide is in the return list regardless of whether or not it was actually just added;
                    // we just want to guarantee this fraction has 500 peptides in the return list to normalize with
                    peptidesAddedPerFraction[fraction]++;
                }
            }
        }

        return subsetList.ToList();
    }

    std::vector<double> IntensityNormalizationEngine::GetNormalizationFactors(std::vector<std::vector<std::vector<double>>> &peptideIntensities, int numP, int numB, int numF, int maxThreads)
    {
        double step = 0.01;
        std::any locker = std::any();

        // initialize normalization factors to 1.0
        // normalization factor optimization must improve on these to be valid
        double bestError = 0;
        std::vector<double> bestNormFactors(numF);
        for (int i = 0; i < bestNormFactors.size(); i++)
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
//C# TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in C#:
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
                    double coefficientOfVariation = Statistics::StandardDeviation(temp) / temp.Average();
                    bestError += std::pow(coefficientOfVariation, 2);
                }
            }
        }

        int startN = static_cast<int>(parameterArray[0]->Min / step);
        int endN = static_cast<int>(parameterArray[0]->Max / step);

        ParallelOptions *tempVar = new ParallelOptions();
        tempVar->MaxDegreeOfParallelism = maxThreads;
        Parallel::For(startN, endN, tempVar, [&] (std::any n)
        {
            double startPosition = n * step;
    
            std::vector<std::vector<double>> biorepIntensities = RectangularVectors::RectangularDoubleVector(numP, numB);
            std::vector<double> temp(2);
    
            // define minimization metric
            std::function<OptimizerResult*(std::vector<double>)> minimize = [&] (std::vector<double> v)
            {
                    // sum the intensities with the current normalization factors
                    Array::Clear(biorepIntensities, 0, biorepIntensities.size());

                    for (int p = 0; p < numP; p++)
                    {
                        for (int b = 0; b < numB; b++)
                        {
                            for (int f = 0; f < numF; f++)
                            {
                                if (b == 0)
                                {
                                    biorepIntensities[p][b] += peptideIntensities[p][b][f];
                                }
                                else
                                {
                                    biorepIntensities[p][b] += peptideIntensities[p][b][f] * v[f];
                                }
                            }
                        }
                    }

                    // calculate the error for these normalization factors
                    double candidateError = 0;
                    for (int p = 0; p < numP; p++)
                    {
                        for (int b2 = 1; b2 < numB; b2++)
                        {
                            temp[0] = biorepIntensities[p][0];
                            temp[1] = biorepIntensities[p][b2];

                            // error metric is sum square error of coefficient of variation of each peptide
                            double coefficientOfVariation = Statistics::StandardDeviation(temp) / temp.Average();
                            candidateError += std::pow(coefficientOfVariation, 2);
                        }
                    }

//C# TO C++ CONVERTER TODO TASK: A 'delete tempVar' statement was not added since tempVar was passed to a method or constructor. Handle memory management manually.
                    return new OptimizerResult(v, candidateError);
            };
    
            // create optimizer
            NelderMeadWithStartPoints tempVar2(parameterArray, 8, 0.001, 10, 0, 0, 1, 2, -0.5, 0.5, startPosition);
            OptimizerResult *result = (&tempVar2)->OptimizeBest(minimize);
    
            double error = result->Error;
            std::vector<double> normFactors = result->ParameterSet;
    
            if (error < bestError)
            {
                {
                    std::lock_guard<std::mutex> lock(locker);
                    if (error < bestError)
                    {
                        bestError = error;
                        bestNormFactors = normFactors;
                    }
                }
            }
        });

//C# TO C++ CONVERTER TODO TASK: A 'delete tempVar' statement was not added since tempVar was passed to a method or constructor. Handle memory management manually.
        return bestNormFactors;
    }
}
