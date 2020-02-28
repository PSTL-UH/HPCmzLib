#include "ProteinQuantificationEngine.h"
#include "FlashLFQResults.h"
#include "Peptide.h"
#include "ProteinGroup.h"
#include "SpectraFileInfo.h"

//using namespace Accord::Math;
//using namespace Accord::Math::Decompositions;
//using namespace MathNet::Numerics::Statistics;

#include "SingularValueDecomposition/Matrix.h"
#include "SingularValueDecomposition/Elementwise.h"

namespace FlashLFQ
{

    ProteinQuantificationEngine::ProteinQuantificationEngine(FlashLfqResults *results, int maxThreads) :
        results(results), maxThreads(maxThreads)
    {
    }

    void ProteinQuantificationEngine::Run()
    {
        // link proteins to peptides
        std::unordered_map<ProteinGroup*, std::vector<Peptide*>> proteinsToPeptides;
#ifdef ORIG
        for (auto peptide : results->PeptideModifiedSequences.Where([&] (std::any p)
        {
            p->Value->UseForProteinQuant;
        }));
#endif
        std::unordered_map<std::string, Peptide*> temppeptides;
        for ( autp p : results->PeptideModifiedSequences ) {
            if (std::get<1>(p)->UseForProteinQuant ) {
                temppeptides.push_back (p)
            }
        }
        for ( auto peptide : temppeptides ) 
        {
            for (auto protein : std::get<1>(peptide)->proteinGroups)
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
                        //C# TO C++ CONVERTER TODO TASK: A 'delete tempVar' statement was not added since tempVar was
                        //passed to a method or constructor. Handle memory management manually.
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
                if (peptides.empty())
                {
                    for (int s = 0; s < (int)results->SpectraFiles.size(); s++)
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
                for (int p = 0; p < (int)intensityArray.size(); p++)
                {
                    double avg = Math::Log(intensityArray[p].Average(), 2);
    
                    intensityArray[p] = intensityArray[p].Select([&] (std::any v)
                    {
                        //C# TO C++ CONVERTER TODO TASK: A 'delete tempVar' statement was not added since tempVar
                        // was passed to a method or constructor. Handle memory management manually.
                        return Math::Log(v, 2) - avg;
                    })->ToArray();
                }
    
                // remove NaN/infinity
                for (int p = 0; p < peptides.size(); p++)
                {
                    for (int s = 0; s < (int)intensityArray[p].size(); s++)
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
                for (int p = 0; p < (int)peptides.size(); p++)
                {
                    if (weights[p] >= MIN_WEIGHT && !std::isnan(weights[p]))
                    {
                        for (int s = 0; s < (int)proteinIntensitiesPerFile.size(); s++)
                        {
                            proteinIntensitiesPerFile[s] += (weights[p] * peptides[p]->GetIntensity(results->SpectraFiles[s]));
                        }
                    }
                }
    
                // store results
                for (int s = 0; s < (int)results->SpectraFiles.size(); s++)
                {
                    proteinList[i].Key->SetIntensity(results->SpectraFiles[s], proteinIntensitiesPerFile[s]);
                }
    
                {
                    std::lock_guard<std::mutex> lock(results->ProteinGroups);
                    results->ProteinGroups.emplace(proteinList[i].Key->ProteinGroupName, proteinList[i].Key);
                }
            }
        });

        //C# TO C++ CONVERTER TODO TASK: A 'delete tempVar' statement was not added since tempVar was
        //passed to a method or constructor. Handle memory management manually.
    }

    std::tuple<std::vector<double>, double> ProteinQuantificationEngine::FastFarms(std::vector<std::vector<double>> &readouts,
                                                                                   double mu, double weight, int max_iter,
                                                                                   bool force_iter, double min_noise, double fill_nan)
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

        for (int p = 0; p < (int)xsd.size(); p++)
        {
            if (xsd[p] < min_noise)
            {
                xsd[p] = 1.0;
            }
        }

        // divide by std dev
        for (int p = 0; p < (int)readouts.size(); p++)
        {
            readouts[p] = readouts[p].Select([&] (std::any i)
            {
                return i / xsd[p];
            })->ToArray();
        }

        // handle infinity/NaN
        for (int p = 0; p < (int)readouts.size(); p++)
        {
            for (int f = 0; f < (int)readouts[p].size(); f++)
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
        for (int p = 0; p < (int)C.size(); p++)
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
        v = Matrix::Transpose(v, false);

        // min noise
        for (int i = 0; i < (int)s.size(); i++)
        {
            if (s[i] < min_noise)
            {
                s[i] = min_noise;
            }
        }

        auto sDiag = Matrix::Diagonal(s);
        auto tempmat = Matrix::Dot(u, sDiag);
        C = Matrix::Dot(tempmat, v);

        // initiation
        std::vector<double> lambda = Matrix::Diagonal(C)->Select([&] (std::any i)
        {
            std::sqrt(i * 0.75);
        })->ToArray();
        std::vector<double> new_psi(lambda.size());

        for (int i = 0; i < (int)lambda.size(); i++)
        {
            new_psi[i] = Matrix::Diagonal(C)[i] - std::pow(lambda[i], 2);
        }

        std::vector<double> old_psi(new_psi.size());
        new_psi.CopyTo(old_psi);

        double alpha = weight * readouts.size();
        double E = 1.0;

        for (int i = 0; i < max_iter; i++)
        {
            // E step
            std::vector<double> phi = Elementwise::Divide(lambda, new_psi);
            double a = 1 + Matrix::Dot(lambda, phi);
            std::vector<double> nu = phi.Select([&] (std::any j)
            {
                //delete svd;
                return j / a;
            })->ToArray();
            std::vector<double> xi = Matrix::Dot(C, nu);
            E = 1 - Matrix::Dot(nu, lambda) + Matrix::Dot(nu, xi);

            // M step
            lambda = Elementwise::Divide(xi, Elementwise->Add(Elementwise::Multiply(new_psi, alpha), E));

            auto temp1 = Elementwise::Multiply(xi, lambda);
            auto temp2 = Elementwise::Multiply(new_psi, alpha);
            auto temp3 = Elementwise::Multiply(temp2, lambda);
            auto temp4 = Elementwise::Subtract(mu, lambda);
            auto temp5 = Elementwise::Multiply(temp3, temp4);

            new_psi = Elementwise->Add(Elementwise::Subtract(Matrix::Diagonal(C), temp1), temp5);

            for (int j = 0; j < (int)new_psi.size(); j++)
            {
                if (new_psi[j] < std::pow(min_noise, 2))
                {
                    new_psi[j] = std::pow(min_noise, 2);
                }
            }

            if (!force_iter)
            {
                if (Elementwise::Subtract(new_psi, old_psi).Max([&] (std::any p)
                {
                    std::abs(p);
                }) / old_psi.Max() < min_noise / 10)
                {
                    break;
                }
            }

            new_psi.CopyTo(old_psi);
        }

        std::vector<double> loading = Elementwise::Multiply(lambda, std::sqrt(E));
        auto k = Elementwise::Divide(loading, new_psi);

        double max = loading.Max();
        std::vector<double> weights = loading.Select([&] (std::any p)
        {
            //delete svd;
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

        //C# TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper
        // class reproduces the rectangular array initialization that is automatic in C#:
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
#ifdef ORIG
        auto spectraFiles = results->SpectraFiles.Where([&] (std::any p)
        {
            return p->TechnicalReplicate == 0;
        }).ToList();
#endif
        std::vector<SpectraFileInfo*> spectraFiles;
        for ( auto p: results->SpectraFiles ) {
            if ( p->TechnicalReplicate == 0 ) {
                spectraFiles.push_back(p);
            }
        }

        std::vector<std::vector<double>> intensityArray(peptides.size());

        if (spectraFiles.Max([&] (std::any p)
        {
            return p->Fraction == 0;
        }))
        {
            // non-fractionated data
            for (int p = 0; p < (int)peptides.size(); p++)
            {
                intensityArray[p] = std::vector<double>(spectraFiles.size());

                for (int s = 0; s < (int)spectraFiles.size(); s++)
                {
                    intensityArray[p][s] = peptides[p]->GetIntensity(spectraFiles[s]);
                }
            }
        }
        else
        {
            // fractionated data; need to sum by biorep before entering it into the array
#ifdef ORIG
            auto cond = spectraFiles.Select([&] (std::any v)
            {
                v::Condition;
            }).Distinct().ToList();
#endif
            std::vector<string> cond;
            for ( auto v: spectraFiles ) {
                bool found = false;
                for ( auto p : cond ) {
                    if ( p == v->Condition ) {
                        found = true;
                        break;
                    }
                }
                if ( != found ) {
                    cond.push_back(p->Condition);
                }                          
            }

            std::unordered_map<std::tuple<std::string, int>, int> conditionAndBiorepToSampleNumber;

            int sampleNumber = 0;
            for (int c = 0; c < (int)cond.size(); c++)
            {
#ifdef ORIG
                auto bioreps = spectraFiles.Where([&] (std::any v)
                {
                    return v->Condition == cond[c];
                })->Select([&] (std::any v)
                {
                    v::BiologicalReplicate;
                }).Distinct();
#endif
                std::vector<int> bioreps;
                std::vector<SpectraFileInfo *> tempvec;
                for ( auto v: spectraFiles ) {
                    if ( v->Condition == cond[c] ) {
                        tempvec.push_back(v);
                    }
                }
                for ( auto v: tempvec ) {
                    bool found = false;
                    for ( auto b: bioreps ) {
                        if ( b == v->BiologicalReplicate ) {
                            found = true;
                            break;
                        }
                    }
                    if ( !found ) {
                        bioreps.push_back(v->BiologicalReplicate);
                    }
                }
                
                for (auto biorep : bioreps)
                {
                    conditionAndBiorepToSampleNumber.emplace(std::tuple<std::string, int>(cond[c], biorep), sampleNumber);
                    sampleNumber++;
                }
            }

            for (int p = 0; p < (int)peptides.size(); p++)
            {
                intensityArray[p] = std::vector<double>(sampleNumber + 1);

                for (int s = 0; s < (int)spectraFiles.size(); s++)
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
