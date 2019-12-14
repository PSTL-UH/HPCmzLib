#include "ProteinQuantificationEngine.h"
#include "FlashLFQResults.h"
#include "Peptide.h"
#include "ProteinGroup.h"
#include "SpectraFileInfo.h"

using namespace Accord::Math;
using namespace Accord::Math::Decompositions;
using namespace MathNet::Numerics::Statistics;

namespace FlashLFQ
{

    ProteinQuantificationEngine::ProteinQuantificationEngine(FlashLfqResults *results, int maxThreads) : results(results), maxThreads(maxThreads)
    {
    }

    void ProteinQuantificationEngine::Run()
    {
        // link proteins to peptides
        std::unordered_map<ProteinGroup*, std::vector<Peptide*>> proteinsToPeptides;
        for (auto peptide : results->PeptideModifiedSequences.Where([&] (std::any p)
        {
            p->Value->UseForProteinQuant;
        }))
        {
            for (auto protein : peptide->Value->proteinGroups)
            {
                TValue peptides;
                std::unordered_map<ProteinGroup*, std::vector<Peptide*>>::const_iterator proteinsToPeptides_iterator = proteinsToPeptides.find(protein);
                if (proteinsToPeptides_iterator != proteinsToPeptides.end())
                {
                    peptides = proteinsToPeptides_iterator->second;
                    peptides->Add(peptide->Value);
                }
                else
                {
                    peptides = proteinsToPeptides_iterator->second;
                    proteinsToPeptides.emplace(protein, std::vector<Peptide*> {peptide->Value});
                }
            }
        }

        auto proteinList = proteinsToPeptides.ToList();

        ParallelOptions *tempVar = new ParallelOptions();
        tempVar->MaxDegreeOfParallelism = maxThreads;
        Parallel::ForEach(Partitioner::Create(0, proteinList.size()), tempVar, [&] (std::any partitionRange)
        {
            for (int i = partitionRange::Item1; i < partitionRange::Item2; i++)
            {
                // peptides must have at least one non-zero intensity measurement to be used for this protein quant analysis
                std::vector<Peptide*> peptides;
    
                for (int p = 0; p < proteinList[i].Value->Count; p++)
                {
                    for (auto file : results->SpectraFiles.Where([&] (std::any f)
                    {
//C# TO C++ CONVERTER TODO TASK: A 'delete tempVar' statement was not added since tempVar was passed to a method or constructor. Handle memory management manually.
                return f->TechnicalReplicate == 0;
                    }))
                    {
                        if (proteinList[i].Value[p].GetIntensity(file) > 0)
                        {
                            peptides.push_back(proteinList[i].Value[p]);
                            break;
                        }
                    }
                }
    
                // if this protein has no valid peptides (i.e., all missing values) its intensity is 0
                if (!peptides.Any())
                {
                    for (int s = 0; s < results->SpectraFiles.size(); s++)
                    {
                        proteinList[i].Key->SetIntensity(results->SpectraFiles[s], 0);
                    }
    
                    {
                        std::lock_guard<std::mutex> lock(results->ProteinGroups);
                        results->ProteinGroups.emplace(proteinList[i].Key->ProteinGroupName, proteinList[i].Key);
                    }
    
                    continue;
                }
    
                // put intensities from the samples into a 2d (peptides x samples) array
                std::vector<std::vector<double>> intensityArray = GetIntensityArray(peptides);
    
                // subtract reference sample and log-transform
                for (int p = 0; p < intensityArray.size(); p++)
                {
                    double avg = Math::Log(intensityArray[p].Average(), 2);
    
                    intensityArray[p] = intensityArray[p].Select([&] (std::any v)
                    {
//C# TO C++ CONVERTER TODO TASK: A 'delete tempVar' statement was not added since tempVar was passed to a method or constructor. Handle memory management manually.
                return Math::Log(v, 2) - avg;
                    })->ToArray();
                }
    
                // remove NaN/infinity
                for (int p = 0; p < peptides.size(); p++)
                {
                    for (int s = 0; s < intensityArray[p].size(); s++)
                    {
                        if (std::isnan(intensityArray[p][s]) || std::isinf(intensityArray[p][s]))
                        {
                            intensityArray[p][s] = 0;
                        }
                    }
                }
    
                std::vector<double> weights;
    
                if (peptides.size() > 1)
                {
                    // calculate peptide weights with FARMS
                    auto weightsAndNoise = FastFarms(intensityArray, MU, ALPHA, MAX_ITER, false, MIN_NOISE, 0.0);
                    weights = std::get<0>(weightsAndNoise);
                }
                else
                {
                    weights = {1.0};
                }
    
                std::vector<double> proteinIntensitiesPerFile(results->SpectraFiles.size());
    
                // calculate weighted-sum peptide intensity
                for (int p = 0; p < peptides.size(); p++)
                {
                    if (weights[p] >= MIN_WEIGHT && !std::isnan(weights[p]))
                    {
                        for (int s = 0; s < proteinIntensitiesPerFile.size(); s++)
                        {
                            proteinIntensitiesPerFile[s] += (weights[p] * peptides[p]->GetIntensity(results->SpectraFiles[s]));
                        }
                    }
                }
    
                // store results
                for (int s = 0; s < results->SpectraFiles.size(); s++)
                {
                    proteinList[i].Key->SetIntensity(results->SpectraFiles[s], proteinIntensitiesPerFile[s]);
                }
    
                {
                    std::lock_guard<std::mutex> lock(results->ProteinGroups);
                    results->ProteinGroups.emplace(proteinList[i].Key->ProteinGroupName, proteinList[i].Key);
                }
            }
        });

//C# TO C++ CONVERTER TODO TASK: A 'delete tempVar' statement was not added since tempVar was passed to a method or constructor. Handle memory management manually.
    }

    std::tuple<std::vector<double>, double> ProteinQuantificationEngine::FastFarms(std::vector<std::vector<double>> &readouts, double mu, double weight, int max_iter, bool force_iter, double min_noise, double fill_nan)
    {
        // subtract average intensity
        for (int p = 0; p < readouts.size(); p++)
        {
            double iAvg = readouts[p].Average();
            readouts[p] = readouts[p].Select([&] (std::any i)
            {
                return i - iAvg;
            })->ToArray();
        }

        // calculate std dev
        std::vector<double> xsd = readouts.Select([&] (std::any p)
        {
            Statistics::PopulationStandardDeviation(p);
        })->ToArray();

        for (int p = 0; p < xsd.size(); p++)
        {
            if (xsd[p] < min_noise)
            {
                xsd[p] = 1.0;
            }
        }

        // divide by std dev
        for (int p = 0; p < readouts.size(); p++)
        {
            readouts[p] = readouts[p].Select([&] (std::any i)
            {
                return i / xsd[p];
            })->ToArray();
        }

        // handle infinity/NaN
        for (int p = 0; p < readouts.size(); p++)
        {
            for (int f = 0; f < readouts[p].size(); f++)
            {
                if (std::isnan(readouts[p][f]) || std::isinf(readouts[p][f]))
                {
                    readouts[p][f] = fill_nan;
                }
            }
        }

        // calculate covariance matrix
        std::vector<std::vector<double>> C = GetCovarianceMatrix(readouts);

        // positive definite
        for (int p = 0; p < C.size(); p++)
        {
            for (int f = 0; f < (C.size() == 0 ? 0 : C[0].size()); f++)
            {
                if (C[p][f] < 0)
                {
                    C[p][f] = 0;
                }
            }
        }

        // singular value decomposition
        auto svd = new SingularValueDecomposition(C);
        std::vector<std::vector<double>> u = svd->LeftSingularVectors;
        std::vector<double> s = svd->Diagonal;
        std::vector<std::vector<double>> v = svd->RightSingularVectors;
        v = Matrix::Transpose(v);

        // min noise
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] < min_noise)
            {
                s[i] = min_noise;
            }
        }

        auto sDiag = Matrix::Diagonal(s);
        C = Matrix::Dot(Matrix::Dot(u, sDiag), v);

        // initiation
        std::vector<double> λ = Matrix::Diagonal(C)->Select([&] (std::any i)
        {
            std::sqrt(i * 0.75);
        })->ToArray();
        std::vector<double> ψ(λ.size());

        for (int i = 0; i < λ.size(); i++)
        {
            ψ[i] = Matrix::Diagonal(C)[i] - std::pow(λ[i], 2);
        }

        std::vector<double> old_psi(ψ.size());
        ψ.CopyTo(old_psi);

        double alpha = weight * readouts.size();
        double E = 1.0;

        for (int i = 0; i < max_iter; i++)
        {
            // E step
            std::vector<double> φ = Elementwise::Divide(λ, ψ);
            double a = 1 + Matrix::Dot(λ, φ);
            std::vector<double> η = φ.Select([&] (std::any j)
            {
            delete svd;
                return j / a;
            })->ToArray();
            std::vector<double> ζ = Matrix::Dot(C, η);
            E = 1 - Matrix::Dot(η, λ) + Matrix::Dot(η, ζ);

            // M step
            λ = Elementwise::Divide(ζ, Elementwise->Add(Elementwise::Multiply(ψ, alpha), E));

            auto temp1 = Elementwise::Multiply(ζ, λ);
            auto temp2 = Elementwise::Multiply(ψ, alpha);
            auto temp3 = Elementwise::Multiply(temp2, λ);
            auto temp4 = Elementwise::Subtract(mu, λ);
            auto temp5 = Elementwise::Multiply(temp3, temp4);

            ψ = Elementwise->Add(Elementwise::Subtract(Matrix::Diagonal(C), temp1), temp5);

            for (int j = 0; j < ψ.size(); j++)
            {
                if (ψ[j] < std::pow(min_noise, 2))
                {
                    ψ[j] = std::pow(min_noise, 2);
                }
            }

            if (!force_iter)
            {
                if (Elementwise::Subtract(ψ, old_psi).Max([&] (std::any p)
                {
                    std::abs(p);
                }) / old_psi.Max() < min_noise / 10)
                {
                    break;
                }
            }

            ψ.CopyTo(old_psi);
        }

        std::vector<double> loading = Elementwise::Multiply(λ, std::sqrt(E));
        auto k = Elementwise::Divide(loading, ψ);

        double max = loading.Max();
        std::vector<double> weights = loading.Select([&] (std::any p)
        {
        delete svd;
            return p / max;
        })->ToArray();
        double noise = 1.0 / (1.0 + Matrix::Dot(loading, k));

        // return weights, noise

        delete svd;
        return std::tuple<std::vector<double>, double>(weights, noise);
    }

    std::vector<std::vector<double>> ProteinQuantificationEngine::GetCovarianceMatrix(std::vector<std::vector<double>> &data)
    {
        int n = data.size();
        std::vector<std::vector<double>> cov(n);

        for (int i = 0; i < n; i++)
        {
            cov[i] = std::vector<double>(n);

            for (int j = 0; j < n; j++)
            {
                cov[i][j] = Statistics::PopulationCovariance(data[i], data[j]);
            }
        }

//C# TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in C#:
//ORIGINAL LINE: double[,] ret = new double[n, n];
        std::vector<std::vector<double>> ret = RectangularVectors::RectangularDoubleVector(n, n);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                ret[i][j] = cov[i][j];
            }
        }

        return ret;
    }

    std::vector<std::vector<double>> ProteinQuantificationEngine::GetIntensityArray(std::vector<Peptide*> &peptides)
    {
        // only use the first tech rep for calculating peptide weights... could change this later
        auto spectraFiles = results->SpectraFiles.Where([&] (std::any p)
        {
            return p->TechnicalReplicate == 0;
        }).ToList();

        std::vector<std::vector<double>> intensityArray(peptides.size());

        if (spectraFiles.Max([&] (std::any p)
        {
            return p->Fraction == 0;
        }))
        {
            // non-fractionated data
            for (int p = 0; p < peptides.size(); p++)
            {
                intensityArray[p] = std::vector<double>(spectraFiles.size());

                for (int s = 0; s < spectraFiles.size(); s++)
                {
                    intensityArray[p][s] = peptides[p]->GetIntensity(spectraFiles[s]);
                }
            }
        }
        else
        {
            // fractionated data; need to sum by biorep before entering it into the array
            auto cond = spectraFiles.Select([&] (std::any v)
            {
                v::Condition;
            }).Distinct().ToList();
            std::unordered_map<std::tuple<std::string, int>, int> conditionAndBiorepToSampleNumber;

            int sampleNumber = 0;
            for (int c = 0; c < cond.size(); c++)
            {
                auto bioreps = spectraFiles.Where([&] (std::any v)
                {
                    return v->Condition == cond[c];
                })->Select([&] (std::any v)
                {
                    v::BiologicalReplicate;
                }).Distinct();

                for (auto biorep : bioreps)
                {
                    conditionAndBiorepToSampleNumber.emplace(std::tuple<std::string, int>(cond[c], biorep), sampleNumber);
                    sampleNumber++;
                }
            }

            for (int p = 0; p < peptides.size(); p++)
            {
                intensityArray[p] = std::vector<double>(sampleNumber + 1);

                for (int s = 0; s < spectraFiles.size(); s++)
                {
                    SpectraFileInfo *spectraFile = spectraFiles[s];
                    sampleNumber = conditionAndBiorepToSampleNumber[std::tuple<std::string, int>(spectraFile->Condition, spectraFile->BiologicalReplicate)];

                    intensityArray[p][sampleNumber] += peptides[p]->GetIntensity(spectraFiles[s]);
                }
            }
        }

        return intensityArray;
    }
}
