#include "NelderMeadWithStartPoints.h"
#include "MzLibUtil.h"

namespace FlashLFQ
{
    namespace BoundedNelderMeadOptimizer
    {
        
        NelderMeadWithStartPoints::NelderMeadWithStartPoints(std::vector<ParameterBounds*> &parameters,
                                                             int maxRestarts,
                                                             double noImprovementThreshold,
                                                             int maxIterationsWithoutImprovement,
                                                             int maxIterationsPrRestart,
                                                             int maxFunctionEvaluations,
                                                             double alpha, double gamma,
                                                             double rho, double sigma,
                                                             double startingValue) :
            m_maxIterationsPrRestart(maxIterationsPrRestart),
            m_maxIterationsWithoutImprovement(maxIterationsWithoutImprovement),
            m_maxRestarts(maxRestarts), m_alpha(alpha), m_gamma(gamma),
            m_rho(rho), m_sigma(sigma),
            m_noImprovementThreshold(noImprovementThreshold), m_parameters(parameters),
            m_random(new ParameterSampler((int)startingValue)),
            m_sampler(new ParameterSampler((int)startingValue)),
            m_maxFunctionEvaluations(maxFunctionEvaluations),
            startingValue(startingValue)    {
            if (parameters.empty())
            {
                throw std::invalid_argument("parameters");
            }
            if (maxIterationsWithoutImprovement <= 0)
            {
                throw std::invalid_argument("maxIterationsWithoutImprovement must be at least 1");
            }
            if (maxFunctionEvaluations < 0)
            {
                throw std::invalid_argument("maxFunctionEvaluations must be at least 1");
            }
                        
        }
                      
        OptimizerResult *NelderMeadWithStartPoints::OptimizeBest(std::function<OptimizerResult*(std::vector<double>)> functionToMinimize)
        {
            return Optimize(functionToMinimize).front();
        }
        
        std::vector<OptimizerResult*> NelderMeadWithStartPoints::Optimize(std::function<OptimizerResult*(std::vector<double>)> functionToMinimize)
        {
            auto dim = m_parameters.size();
            
            auto allResults = std::vector<OptimizerResult*>();
            
            m_totalFunctionEvaluations = 0;
            
            std::vector<double> initialPoint(dim);
            for (int i = 0; i < (int)initialPoint.size(); i++)
            {
                initialPoint[i] = startingValue;
            }
            
            for (int restarts = 0; restarts < m_maxRestarts; restarts++)
            {
                auto prevBest = EvaluateFunction(functionToMinimize, initialPoint);
                auto iterationsWithoutImprovement = 0;
                auto paramset = prevBest->getParameterSet();
                auto results = std::vector<OptimizerResult*> {new OptimizerResult(paramset, prevBest->getError())};
                
                for (int i = 0; i < (int)dim; i++)
                {
                    // % simplex size between 2%-8% of min(xrange)
                    auto a = (0.02 + 0.08 * m_random->NextDouble()) * (m_parameters[i]->Max - m_parameters[i]->Min); 
                    
                    auto p = a * (std::sqrt(dim + 1) + dim - 1) / (dim * std::sqrt(2));
                    auto q = a * (std::sqrt(dim + 1) - 1) / (dim * std::sqrt(2));
                    
                    auto x = initialPoint; //.ToArray();
                    x[i] = x[i] + p;
                    
                    for (int j = 0; j < (int)dim; j++)
                    {
                        if (j != i)
                        {
                            x[j] = x[j] + q;
                        }
                    }
                    
                    BoundCheck(x);
                    auto score = EvaluateFunction(functionToMinimize, x);
                    results.push_back(score);
                }
                
                // simplex iter
                auto iterations = 0;
                while (true) {
#ifdef ORIG
                    results = results.OrderBy([&] (std::any r)
                                              {
                                                  r::Error;
                                              }).ToList();
#endif
                    std::sort (results.begin(), results.end(), [&] (OptimizerResult *r, OptimizerResult *l) {
                            return r->getError() > l->getError();
                        });
                    auto best = results.front();
                    
                    // break after m_maxIterationsPrRestart
                    if (iterations >= m_maxIterationsPrRestart && m_maxIterationsPrRestart != 0)
                    {
                        allResults.insert(allResults.end(), results.begin(), results.end());
                        break;
                    }
                    
                    iterations++;
                    
                    double percentImprovement = -((best->getError() - prevBest->getError()) / prevBest->getError());
                    
                    if (percentImprovement > m_noImprovementThreshold)
                    {
                        iterationsWithoutImprovement = 0;
                        prevBest = best;
                    }
                    else
                    {
                        iterationsWithoutImprovement++;
                    }
                    
                    // break after no_improv_break iterations with no improvement
                    if (iterationsWithoutImprovement >= m_maxIterationsWithoutImprovement)
                    {
                        allResults.insert(allResults.end(), results.begin(), results.end());
                        break;
                    }
                    
                    // check if m_maxFunctionEvaluations is reached
                    if (m_totalFunctionEvaluations >= m_maxFunctionEvaluations && m_maxFunctionEvaluations != 0)
                    {
                        allResults.insert(allResults.end(), results.begin(), results.end());
                        break;
                    }
                    
                    // centroid
                    auto x0 = std::vector<double>(dim);
                    
                    //for (auto tup : results.Take(results.size() - 1))
                    for (auto tup=results.begin(); tup != results.end()-1; tup++)
                    {
                        auto parameters = (*tup)->getParameterSet();
                        for (int i = 0; i < (int)parameters.size(); i++)
                        {
                            x0[i] += parameters[i] / (results.size() - 1);
                        }
                    }
                    
                    BoundCheck(x0);
                    
                    // reflection
                    auto last = results.back();
#ifdef ORIG
                    auto xr = x0.Add(x0.Subtract(last->getParameterSet()).Multiply(m_alpha));
#endif
                    auto xsub = last->getParameterSet();
                    if (x0.size() != xsub.size() ) {
                        throw MzLibUtil::MzLibException("NelderMeadWithStartPoints: cannot perform Sub operation");
                    }
                    std::vector<double> xr(x0.size());
                    for ( int i = 0; i < (int)x0.size(); i++ ) {
                        xr[i] = x0[i] + (m_alpha * (x0[i] - xsub[i]));
                    }

                    BoundCheck(xr);
                    auto refelctionScore = EvaluateFunction(functionToMinimize, xr);
                    
                    auto first = results.front()->getError();
                    if (first <= refelctionScore->getError() && refelctionScore->getError() < results[results.size() - 2]->getError())
                    {
                        results.pop_back();
                        results.push_back(refelctionScore);
                        continue;
                    }
                    
                    // expansion
                    if (refelctionScore->getError() < first)
                    {
#ifdef ORIG
                        auto xe = x0.Add(x0.Subtract(last->getParameterSet()).Multiply(m_gamma));
#endif
                        auto xsub = last->getParameterSet();
                        if (x0.size() != xsub.size() ) {
                            throw MzLibUtil::MzLibException("NelderMeadWithStartPoints: cannot perform Sub operation");
                        }
                        std::vector<double> xe(x0.size());
                        for ( int i = 0; i < (int)x0.size(); i++ ) {
                            xe[i] = x0[i] + (m_gamma * (x0[i] - xsub[i]));
                        }

                        
                        BoundCheck(xe);
                        auto expansionScore = EvaluateFunction(functionToMinimize, xe);
                        if (expansionScore->getError() < refelctionScore->getError())
                        {
                            results.pop_back();
                            results.push_back(expansionScore);
                            continue;
                        }
                        else
                        {
                            results.pop_back();
                            results.push_back(refelctionScore);
                            continue;
                        }
                    }

                    // contraction
#ifdef ORIG
                    auto xc = x0.Add(x0.Subtract(last->getParameterSet()).Multiply(m_rho));
#endif
                    auto xsub2 = last->getParameterSet();
                    if (x0.size() != xsub2.size() ) {
                        throw MzLibUtil::MzLibException("NelderMeadWithStartPoints: cannot perform Sub operation");
                    }
                    std::vector<double> xc(x0.size());
                    for ( int i = 0; i < (int)x0.size(); i++ ) {
                        xc[i] = x0[i] + (m_rho * (x0[i] - xsub2[i]));
                    }

                    BoundCheck(xc);
                    auto contractionScore = EvaluateFunction(functionToMinimize, xc);
                    if (contractionScore->getError() < last->getError())
                    {
                        results.pop_back();
                        results.push_back(contractionScore);
                        continue;
                    }

                    // shrink
                    auto x1 = results[0]->getParameterSet();
                    auto nres = std::vector<OptimizerResult*>();
                    for (auto tup : results)
                    {
#ifdef ORIG
                        auto xs = x1->Add(x1->Subtract(tup->getParameterSet()).Multiply(m_sigma));
#endif
                        auto xsub = tup->getParameterSet();
                        if (x1.size() != xsub.size() ) {
                            throw MzLibUtil::MzLibException("NelderMeadWithStartPoints: cannot perform Sub operation");
                        }
                        std::vector<double> xs(x1.size());
                        for ( int i = 0; i < (int)x1.size(); i++ ) {
                            xs[i] = x1[i] + (m_sigma * (x1[i] - xsub[i]));
                        }

                        BoundCheck(xs);
                        OptimizerResult* score = EvaluateFunction(functionToMinimize, xs);
                        nres.push_back(score);
                    }

                    //results = nres.ToList();
                    results.insert (results.end(), nres.begin(), nres.end());
                }

                // check if m_maxFunctionEvaluations is reached
                if (m_totalFunctionEvaluations >= m_maxFunctionEvaluations && m_maxFunctionEvaluations != 0)
                {
                    allResults.insert(allResults.end(), results.begin(), results.end());
                    break;
                }
            }

#ifdef ORIG
            return allResults.Where([&] (std::any v)
            {
                !std::isnan(v::Error);
            }).OrderBy([&] (std::any r)
            {
                r::Error;
            })->ToArray();
#endif
            std::vector<OptimizerResult*> resv;
            for ( auto v: allResults ) {
                if ( !std::isnan (v->getError() )) {
                        resv.push_back(v);
                }
            }
            std::sort (resv.begin(), resv.end(), [&] (OptimizerResult *l, OptimizerResult *r) {
                    return l->getError() > r->getError(); } );
            
            return resv;
        }

        OptimizerResult *NelderMeadWithStartPoints::EvaluateFunction(std::function<OptimizerResult*(std::vector<double>)> functionToMinimize, std::vector<double> &parameters)
        {
            m_totalFunctionEvaluations++;
            return functionToMinimize(parameters);
        }

        void NelderMeadWithStartPoints::BoundCheck(std::vector<double> &parameters)
        {
            for (int i = 0; i < (int)parameters.size(); i++)
            {
                auto parameter = m_parameters[i];
                auto min = parameters[i] < parameter->Max ? parameters[i] : parameter->Max;                
                parameters[i] = parameter->Min > min ? parameter->Min : min;
            }
        }
    }
}
