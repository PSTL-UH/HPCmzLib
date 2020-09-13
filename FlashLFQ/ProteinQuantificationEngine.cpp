#include "ProteinQuantificationEngine.h"
#include "FlashLFQResults.h"
#include "Peptide.h"
#include "ProteinGroup.h"
#include "SpectraFileInfo.h"

#include <cmath>
#include "MzLibMath.h"

#include "SingularValueDecomposition/Matrix.h"
#include "SingularValueDecomposition/Elementwise.h"
#include "SingularValueDecomposition/SingularValueDecomposition.h"

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
        for ( auto p : results->PeptideModifiedSequences ) {
            if (std::get<1>(p)->UseForProteinQuant ) {
                temppeptides.insert (p);
            }
        }
        for ( auto peptide : temppeptides ) 
        {
            for (auto protein : std::get<1>(peptide)->proteinGroups)
            {
                std::unordered_map<ProteinGroup*, std::vector<Peptide*>>::iterator proteinsToPeptides_iterator = proteinsToPeptides.find(protein);
                if (proteinsToPeptides_iterator != proteinsToPeptides.end())
                {
                    proteinsToPeptides_iterator->second.push_back(std::get<1>(peptide));
                }
                else
                {
                    proteinsToPeptides.emplace(protein,  std::vector<Peptide*> {std::get<1>(peptide)} );
                }
            }
        }

        std::vector<std::tuple<ProteinGroup*, std::vector<Peptide*>>> proteinList(proteinsToPeptides.begin(), proteinsToPeptides.end());

#ifdef ORIG
        //ParallelOptions *tempVar = new ParallelOptions();
        //tempVar->MaxDegreeOfParallelism = maxThreads;
        //Parallel::ForEach(Partitioner::Create(0, proteinList.size()), tempVar, [&] (std::any partitionRange)
        //{
#endif
        //for (int i = partitionRange::Item1; i < partitionRange::Item2; i++)
        for (int i = 0; i < (int)proteinList.size(); i++)
        {
            // peptides must have at least one non-zero intensity measurement to be used for this protein quant analysis
            std::vector<Peptide*> peptides;
            
            for (int p = 0; p < (int)std::get<1>(proteinList[i]).size(); p++)
            {
#ifdef ORIG
                for (auto file : results->SpectraFiles.Where([&] (std::any f)  {
                            return f->TechnicalReplicate == 0;
                        }));
#endif
                for ( auto file : results->SpectraFiles ) {
                    if ( file->TechnicalReplicate == 0 ) {
                        if (std::get<1>(proteinList[i])[p]->GetIntensity(file) > 0)
                        {
                            peptides.push_back(std::get<1>(proteinList[i])[p]);
                            break;
                        }
                    }
                }
            }
            
            // if this protein has no valid peptides (i.e., all missing values) its intensity is 0
            if (peptides.empty())
            {
                for (int s = 0; s < (int)results->SpectraFiles.size(); s++)
                {
                    std::get<0>(proteinList[i])->SetIntensity(results->SpectraFiles[s], 0);
                }
                
                //{
                //   std::lock_guard<std::mutex> lock(results->ProteinGroups);
                results->ProteinGroups.emplace(std::get<0>(proteinList[i])->ProteinGroupName, std::get<0>(proteinList[i]));
                //}
                
                continue;
            }
            
            // put intensities from the samples into a 2d (peptides x samples) array
            std::vector<std::vector<double>> intensityArray = GetIntensityArray(peptides);
            
            // subtract reference sample and log-transform
            for (int p = 0; p < (int)intensityArray.size(); p++)
            {
                //double avg = Math::Log(intensityArray[p].Average(), 2);
                double avg = std::log2(Math::Mean(intensityArray[p]));

#ifdef ORIG
                intensityArray[p] = intensityArray[p].Select([&] (std::any v)  {
                        return Math::Log(v, 2) - avg;
                    })->ToArray();
#endif
                std::vector<double> temp;
                for ( auto v: intensityArray[p] ) {
                    temp.push_back(std::log2(v) - avg);
                }
                intensityArray[p].clear(); // Not sure about this line.
                intensityArray[p].insert(intensityArray[p].end(), temp.begin(), temp.end());
            }
            
            // remove NaN/infinity
            for (int p = 0; p < (int)peptides.size(); p++)
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
                std::get<0>(proteinList[i])->SetIntensity(results->SpectraFiles[s], proteinIntensitiesPerFile[s]);
            }
            
            //{
            //  std::lock_guard<std::mutex> lock(results->ProteinGroups);
            results->ProteinGroups.emplace(std::get<0>(proteinList[i])->ProteinGroupName, std::get<0>(proteinList[i]));
            //}
        }
        
        
        //C# TO C++ CONVERTER TODO TASK: A 'delete tempVar' statement was not added since tempVar was
        //passed to a method or constructor. Handle memory management manually.
    }
    
    std::tuple<std::vector<double>, double> ProteinQuantificationEngine::FastFarms(std::vector<std::vector<double>> &readouts,
                                                                                   double mu, double weight, int max_iter,
                                                                                   bool force_iter, double min_noise, double fill_nan)
    {
        // subtract average intensity
        for (int p = 0; p < (int)readouts.size(); p++)
        {

#ifdef ORIG
            double iAvg = readouts[p].Average();
            readouts[p] = readouts[p].Select([&] (std::any i)
            {
                return i - iAvg;
            })->ToArray();
#endif
            double iAvg = Math::Mean(readouts[p]);
            std::vector<double> temp;
            for ( auto i : readouts[p] ) {
                temp.push_back(i - iAvg);                
            }
            readouts[p].clear(); //Not sure about this.
            readouts[p].insert(readouts[p].end(), temp.begin(), temp.end() );
        }

        // calculate std dev
#ifdef ORIG
        std::vector<double> xsd = readouts.Select([&] (std::any p)
        {
            Statistics::PopulationStandardDeviation(p);
        })->ToArray();
#endif
        std::vector<double> xsd;
        for ( auto p: readouts ) {
            xsd.push_back(Math::PopulationStandardDeviation(p));
        }

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
#ifdef ORIG
            readouts[p] = readouts[p].Select([&] (std::any i)
            {
                return i / xsd[p];
            })->ToArray();
#endif
            std::vector<double> temp;
            for ( auto i: readouts[p] ) {
                temp.push_back(i/xsd[p]);                
            }
            readouts[p].clear();
            readouts[p].insert(readouts[p].end(), temp.begin(), temp.end());
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
        auto svd = new Decompositions::SingularValueDecomposition(C);
        std::vector<std::vector<double>> u = svd->getLeftSingularVectors();
        std::vector<double> s = svd->getDiagonal();
        std::vector<std::vector<double>> v = svd->getRightSingularVectors();
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
#ifdef ORIG
        std::vector<double> lambda = Matrix::Diagonal(C)->Select([&] (std::any i)
        {
            std::sqrt(i * 0.75);
        })->ToArray();
#endif
        std::vector<double> lambda;
        auto tempmat2 = Matrix::Diagonal(C);
        for ( auto i: tempmat2 ) {
            lambda.push_back(std::sqrt(i * 0.75));
        }
        std::vector<double> new_psi(lambda.size());

        for (int i = 0; i < (int)lambda.size(); i++)
        {
            new_psi[i] = Matrix::Diagonal(C)[i] - std::pow(lambda[i], 2);
        }

        std::vector<double> old_psi(new_psi.size());
        //new_psi.CopyTo(old_psi);
        old_psi = new_psi;

        double alpha = weight * readouts.size();
        double E = 1.0;

        for (int i = 0; i < max_iter; i++)
        {
            // E step
            std::vector<double> phi = Elementwise::Divide(lambda, new_psi);
            double a = 1 + Matrix::Dot(lambda, phi);
#ifdef ORIG
            std::vector<double> nu = phi.Select([&] (std::any j) {
                    return j / a;
                })->ToArray();
#endif
            std::vector<double> nu;
            for ( auto j : phi ) {
                nu.push_back(j/a);
            }
            std::vector<double> xi = Matrix::Dot(C, nu);
            E = 1 - Matrix::Dot(nu, lambda) + Matrix::Dot(nu, xi);
            
            // M step
            //lambda = Elementwise::Divide(xi, Elementwise::Add(Elementwise::Multiply(new_psi, alpha), E));
            auto tmp1 = Elementwise::Multiply(new_psi, alpha);
            auto tmp2 = Elementwise::Add(tmp1, E);
            lambda = Elementwise::Divide(xi, tmp2);
            
            auto temp1 = Elementwise::Multiply(xi, lambda);
            auto temp2 = Elementwise::Multiply(new_psi, alpha);
            auto temp3 = Elementwise::Multiply(temp2, lambda);
            auto temp4 = Elementwise::Subtract(mu, lambda);
            auto temp5 = Elementwise::Multiply(temp3, temp4);
            
            //new_psi = Elementwise->Add(Elementwise::Subtract(Matrix::Diagonal(C), temp1), temp5);
            auto diag = Matrix::Diagonal(C);
            auto tmp3 = Elementwise::Subtract(diag, temp1);
            new_psi = Elementwise::Add(tmp3, temp5);
            
            for (int j = 0; j < (int)new_psi.size(); j++)
            {
                if (new_psi[j] < std::pow(min_noise, 2))
                {
                    new_psi[j] = std::pow(min_noise, 2);
                }
            }
            
            if (!force_iter)
            {
#ifdef ORIG
                if (Elementwise::Subtract(new_psi, old_psi).Max([&] (std::any p)  {
                            std::abs(p);
                        }) / old_psi.Max() < min_noise / 10)
                {
                    break;
                }
#endif
                auto t = Elementwise::Subtract(new_psi, old_psi);
                std::vector<double> tempvec;
                for ( auto p: t ) {
                    tempvec.push_back(std::abs(p));
                }
                auto max = std::max(tempvec.begin(), tempvec.end() );
                auto old_psi_max = std::max ( old_psi.begin(), old_psi.end() );              
                if ( (*max / *old_psi_max) < (min_noise / 10) ){
                    break;
                }
           
                //new_psi.CopyTo(old_psi);
                old_psi = new_psi;
            }
        }
        
        auto temps = std::sqrt(E);
        std::vector<double> loading = Elementwise::Multiply(lambda, temps);
        auto k = Elementwise::Divide(loading, new_psi);

        double max = *std::max(loading.begin(), loading.end());
#ifdef ORIG
        std::vector<double> weights = loading.Select([&] (std::any p)
        {
            return p / max;
        })->ToArray();
#endif
        std::vector<double> weights;
        for ( auto p: loading ) {
            weights.push_back(p/max);
        }
        
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
                //cov[i][j] = Statistics::PopulationCovariance(data[i], data[j]);
                cov[i][j] = Math::PopulationCovariance(data[i], data[j]);
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

#ifdef ORIG
        //if (spectraFiles.Max([&] (std::any p)
        //{
        //    return p->Fraction == 0;
        //}))
#endif
        std::vector<SpectraFileInfo*> tempvec;
        for ( auto p : spectraFiles ) {
            if ( p->Fraction == 0 ) {
                tempvec.push_back(p);
            }
        }
        auto maxval = *std::max(tempvec.begin(), tempvec.end() );
        
        if ( maxval)
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
            std::vector<std::string> cond;
            for ( auto v: spectraFiles ) {
                bool found = false;
                for ( auto p : cond ) {
                    if ( p == v->Condition ) {
                        found = true;
                        break;
                    }
                }
                if ( ! found ) {
                    cond.push_back(v->Condition);
                }                          
            }

            //std::unordered_map<std::tuple<std::string, int>, int> conditionAndBiorepToSampleNumber;
            std::map<std::tuple<std::string, int>, int> conditionAndBiorepToSampleNumber;

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
                    conditionAndBiorepToSampleNumber.emplace(std::make_tuple(cond[c], biorep), sampleNumber);
                    sampleNumber++;
                }
            }

            for (int p = 0; p < (int)peptides.size(); p++)
            {
                intensityArray[p] = std::vector<double>(sampleNumber + 1);

                for (int s = 0; s < (int)spectraFiles.size(); s++)
                {
                    SpectraFileInfo *spectraFile = spectraFiles[s];
                    sampleNumber = conditionAndBiorepToSampleNumber[std::make_tuple(spectraFile->Condition, spectraFile->BiologicalReplicate)];

                    intensityArray[p][sampleNumber] += peptides[p]->GetIntensity(spectraFiles[s]);
                }
            }
        }

        return intensityArray;
    }
}
