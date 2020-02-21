#pragma once

#include <vector>
#include <stdexcept>

namespace FlashLFQ
{
    namespace BoundedNelderMeadOptimizer
    {
        /// <summary>
        /// Optimization result
        /// </summary>
        class OptimizerResult final {
        private:
            double Error = 0;
            std::vector<double> ParameterSet;
            
            /// <summary>
            /// 
            /// </summary>
            /// <param name="error"></param>
            /// <param name="parameterSet"></param>
        public:
            OptimizerResult(std::vector<double> &parameterSet, double error);
            
            /// <summary>
            /// Resulting error using the parameter set.
            /// </summary>
            double getError() const;
            
            /// <summary>
            /// The parameter set.
            /// </summary>
            std::vector<double> getParameterSet() const;
        };
    }
}
