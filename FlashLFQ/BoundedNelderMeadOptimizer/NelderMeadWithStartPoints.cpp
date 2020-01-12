#include "NelderMeadWithStartPoints.h"

using namespace SharpLearning::Containers::Arithmetic;
using namespace SharpLearning::Optimization;
using namespace SharpLearning::Optimization::ParameterSamplers;
namespace FlashLFQ
{
    namespace BoundedNelderMeadOptimizer
    {

        NelderMeadWithStartPoints::NelderMeadWithStartPoints(std::vector<ParameterBounds*> &parameters, int maxRestarts,
                                                             double noImprovementThreshold,
                                                             int maxIterationsWithoutImprovement,
                                                             int maxIterationsPrRestart,
                                                             int maxFunctionEvaluations,
                                                             double alpha, double gamma, double rho, double sigma,
                                                             double startingValue) :
            m_maxIterationsPrRestart(maxIterationsPrRestart),
            m_maxIterationsWithoutImprovement(maxIterationsWithoutImprovement),
            m_maxRestarts(maxRestarts), m_alpha(alpha), m_gamma(gamma), m_rho(rho), m_sigma(sigma),
            m_noImprovementThreshold(noImprovementThreshold), m_parameters(parameters),
            m_random(new Random(startingValue.GetHashCode())),
            m_sampler(new RandomUniform(startingValue.GetHashCode())),
            m_maxFunctionEvaluations(maxFunctionEvaluations),
            startingValue(startingValue)
        {
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
            return Optimize(functionToMinimize).Front();
        }

        std::vector<OptimizerResult*> NelderMeadWithStartPoints::Optimize(std::function<OptimizerResult*(std::vector<double>)> functionToMinimize)
        {
            auto dim = m_parameters.size();

            auto allResults = std::vector<OptimizerResult*>();

            m_totalFunctionEvaluations = 0;

            std::vector<double> initialPoint(dim);
            for (int i = 0; i < initialPoint.size(); i++)
            {
                initialPoint[i] = startingValue;
            }

            for (int restarts = 0; restarts < m_maxRestarts; restarts++)
            {
                auto prevBest = EvaluateFunction(functionToMinimize, initialPoint);
                auto iterationsWithoutImprovement = 0;
                auto results = std::vector<OptimizerResult*> {new OptimizerResult(prevBest->ParameterSet, prevBest->Error)};

                for (int i = 0; i < dim; i++)
                {
                    // % simplex size between 2%-8% of min(xrange)
                    auto a = (0.02 + 0.08 * m_random->NextDouble()) * (m_parameters[i]->Max - m_parameters[i]->Min); 

                    auto p = a * (std::sqrt(dim + 1) + dim - 1) / (dim * std::sqrt(2));
                    auto q = a * (std::sqrt(dim + 1) - 1) / (dim * std::sqrt(2));

                    auto x = initialPoint.ToArray();
                    x[i] = x[i] + p;

                    for (int j = 0; j < dim; j++)
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
                while (true)
                {
                    results = results.OrderBy([&] (std::any r)
                    {
                        r::Error;
                    }).ToList();
                    auto best = results.front();

                    // break after m_maxIterationsPrRestart
                    if (iterations >= m_maxIterationsPrRestart && m_maxIterationsPrRestart != 0)
                    {
                        allResults.insert(allResults.end(), results.begin(), results.end());
                        break;
                    }

                    iterations++;

                    double percentImprovement = -((best->Error - prevBest->Error) / prevBest->Error);

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

                    for (auto tup : results.Take(results.size() - 1))
                    {
                        auto parameters = tup->ParameterSet;
                        for (int i = 0; i < parameters->Length; i++)
                        {
                            x0[i] += parameters[i] / (results.size() - 1);
                        }
                    }

                    BoundCheck(x0);

                    // reflection
                    auto last = results.back();
                    auto xr = x0.Add(x0.Subtract(last->ParameterSet).Multiply(m_alpha));
                    BoundCheck(xr);
                    auto refelctionScore = EvaluateFunction(functionToMinimize, xr);

                    auto first = results.front().Error;
                    if (first <= refelctionScore->Error && refelctionScore->Error < results[results.size() - 2]->Error)
                    {
                        results.pop_back();
                        results.push_back(refelctionScore);
                        continue;
                    }

                    // expansion
                    if (refelctionScore->Error < first)
                    {
                        auto xe = x0.Add(x0.Subtract(last->ParameterSet).Multiply(m_gamma));
                        BoundCheck(xe);
                        auto expansionScore = EvaluateFunction(functionToMinimize, xe);
                        if (expansionScore->Error < refelctionScore->Error)
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
                    auto xc = x0.Add(x0.Subtract(last->ParameterSet).Multiply(m_rho));
                    BoundCheck(xc);
                    auto contractionScore = EvaluateFunction(functionToMinimize, xc);
                    if (contractionScore->Error < last->Error)
                    {
                        results.pop_back();
                        results.push_back(contractionScore);
                        continue;
                    }

                    // shrink
                    auto x1 = results[0]->ParameterSet;
                    auto nres = std::vector<OptimizerResult*>();
                    for (auto tup : results)
                    {
                        auto xs = x1->Add(x1->Subtract(tup->ParameterSet).Multiply(m_sigma));
                        BoundCheck(xs);
                        auto score = EvaluateFunction(functionToMinimize, xs);
                        nres.push_back(score);
                    }

                    results = nres.ToList();
                }

                // check if m_maxFunctionEvaluations is reached
                if (m_totalFunctionEvaluations >= m_maxFunctionEvaluations && m_maxFunctionEvaluations != 0)
                {
                    allResults.insert(allResults.end(), results.begin(), results.end());
                    break;
                }
            }

            return allResults.Where([&] (std::any v)
            {
                !std::isnan(v::Error);
            }).OrderBy([&] (std::any r)
            {
                r::Error;
            })->ToArray();
        }

        OptimizerResult *NelderMeadWithStartPoints::EvaluateFunction(std::function<OptimizerResult*(std::vector<double>)> functionToMinimize, std::vector<double> &parameters)
        {
            m_totalFunctionEvaluations++;
            return functionToMinimize(parameters);
        }

        void NelderMeadWithStartPoints::BoundCheck(std::vector<double> &parameters)
        {
            for (int i = 0; i < parameters.size(); i++)
            {
                auto parameter = m_parameters[i];
                parameters[i] = std::max(parameter->Min, std::min(parameters[i], parameter->Max));
            }
        }
    }
}
