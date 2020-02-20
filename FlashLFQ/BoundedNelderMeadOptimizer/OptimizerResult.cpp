#include "OptimizerResult.h"

namespace SharpLearning::Optimization {

    OptimizerResult::OptimizerResult(std::vector<double> &parameterSet, double error) {
//C# TO C++ CONVERTER TODO TASK: Throw expressions are not converted by C# to C++ Converter:
//ORIGINAL LINE: ParameterSet = parameterSet ?? throw new ArgumentException(nameof(parameterSet));
        ParameterSet = parameterSet ? parameterSet : throw std::invalid_argument("parameterSet");
        Error = error;
    }

    double OptimizerResult::getError() const {
        return Error;
    }

    std::vector<double> OptimizerResult::getParameterSet() const {
        return ParameterSet;
    }
}
