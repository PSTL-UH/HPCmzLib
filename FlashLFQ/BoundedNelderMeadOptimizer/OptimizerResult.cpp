#include "OptimizerResult.h"

namespace FlashLFQ
{
    namespace BoundedNelderMeadOptimizer
    {
        OptimizerResult::OptimizerResult(std::vector<double> &parameterSet, double error) {
            ParameterSet = parameterSet;
            Error = error;
        }

        double OptimizerResult::getError() const {
            return Error;
        }
        
        std::vector<double> OptimizerResult::getParameterSet() const {
            return ParameterSet;
        }
    }
}
