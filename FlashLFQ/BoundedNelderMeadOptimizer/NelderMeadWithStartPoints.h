#pragma once

#include <vector>
#include <cmath>
#include <stdexcept>
#include <functional>

//using namespace SharpLearning::Containers::Arithmetic;
//using namespace SharpLearning::Optimization;
//using namespace SharpLearning::Optimization::ParameterSamplers;

#include "OptimizerResult.h"

namespace FlashLFQ
{
    namespace BoundedNelderMeadOptimizer
    {
        /// <summary>
        /// Globalized bounded Nelder-Mead method. This version of Nelder-Mead optimization 
        /// avoids some of the shortcommings the standard implementation. 
        /// Specifically it is better suited for multimodal optimization problems through its restart property.
        /// It also respect the bounds given by the provided parameter space.
        /// Roughly based on:
        /// http://home.ku.edu.tr/~daksen/2004-Nelder-Mead-Method-Wolff.pdf
        /// and
        /// http://www.emse.fr/~leriche/GBNM_SMO_1026_final.pdf
        /// 
        /// Modified for FlashLFQ by Robert J. Millikin
        /// </summary>
        //class NelderMeadWithStartPoints final : public IOptimizer
        class NelderMeadWithStartPoints final 
        {
        private:
            const int m_maxIterationsPrRestart;
            const int m_maxIterationsWithoutImprovement;
            const int m_maxRestarts;
            const double m_alpha;
            const double m_gamma;
            const double m_rho;
            const double m_sigma;
            const double m_noImprovementThreshold;
            const std::vector<ParameterBounds*> m_parameters;
            Random *const m_random;
            IParameterSampler *const m_sampler;
            const int m_maxFunctionEvaluations;
            const double startingValue;
            int m_totalFunctionEvaluations = 0;

            /// <summary>
            /// Globalized bounded Nelder-Mead method. This version of Nelder-Mead optimization 
            /// avoids some of the shortcommings the standard implementation. 
            /// Specifically it is better suited for multimodal optimization problems through its restart property.
            /// It also respect the bounds given by the provided parameter space.
            /// Roughly based on:
            /// http://home.ku.edu.tr/~daksen/2004-Nelder-Mead-Method-Wolff.pdf
            /// and
            /// http://www.emse.fr/~leriche/GBNM_SMO_1026_final.pdf
            /// </summary>
            /// <param name="parameters">Each row is a series of values for a specific parameter</param>
            /// <param name="maxRestarts">Maximun number of restart (default is 8</param>
            /// <param name="noImprovementThreshold">Minimum value of improvement before the improvement is accepted as an actual improvement (default is 0.001)</param>
            /// <param name="maxIterationsWithoutImprovement">Maximum number of iterations without an improvement (default is 5)</param>
            /// <param name="maxIterationsPrRestart">Maximum iterations pr. restart. 0 is no limit and will run to convergens (default is 0)</param>
            /// <param name="maxFunctionEvaluations">Maximum function evaluations. 0 is no limit and will run to convergens (default is 0)</param>
            /// <param name="alpha">Coefficient for reflection part of the algorithm (default is 1)</param>
            /// <param name="gamma">Coefficient for expansion part of the algorithm (default is 2)</param>
            /// <param name="rho">Coefficient for contraction part of the algorithm (default is -0.5)</param>
            /// <param name="sigma">Coefficient for shrink part of the algorithm (default is 0.5)</param>
        public:
            virtual ~NelderMeadWithStartPoints()
            {
                delete m_random;
                delete m_sampler;
            }

            NelderMeadWithStartPoints(std::vector<ParameterBounds*> &parameters, int maxRestarts = 8, double noImprovementThreshold = 0.001, int maxIterationsWithoutImprovement = 5, int maxIterationsPrRestart = 0, int maxFunctionEvaluations = 0, double alpha = 1, double gamma = 2, double rho = -0.5, double sigma = 0.5, double startingValue = 1.0);
            /// <summary>
            /// Optimization using Globalized bounded Nelder-Mead method.
            /// Returns the result which best minimises the provided function.
            /// </summary>
            /// <param name="functionToMinimize"></param>
            /// <returns></returns>
            OptimizerResult *OptimizeBest(std::function<OptimizerResult*(std::vector<double>)> functionToMinimize);

            /// <summary>
            /// Optimization using Globalized bounded Nelder-Mead method.
            /// Returns the final results ordered from best to worst (minimized).
            /// </summary>
            /// <param name="functionToMinimize"></param>
            /// <returns></returns>
            std::vector<OptimizerResult*> Optimize(std::function<OptimizerResult*(std::vector<double>)> functionToMinimize);

        private:
            OptimizerResult *EvaluateFunction(std::function<OptimizerResult*(std::vector<double>)> functionToMinimize, std::vector<double> &parameters);

            /// <summary>
            /// Make sure the parameter set is within the specified bounds
            /// </summary>
            /// <param name="parameters"></param>
            void BoundCheck(std::vector<double> &parameters);
        };
    }
}
