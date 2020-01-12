#pragma once

#include <vector>

namespace FlashLFQ
{
    namespace BoundedNelderMeadOptimizer
    {
        class OptimizerResult
        {

        public:
            double Error;
            std::vector<double> ParameterSet;

            OptimizerResult ( std::vector<double> parameterSet, double error ) {
                ParameterSet = parameterSet;
                Error = error;
            }
        };
    }
}
