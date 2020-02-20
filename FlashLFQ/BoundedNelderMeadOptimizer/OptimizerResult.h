#pragma once

#include <vector>
#include <stdexcept>

namespace SharpLearning::Optimization {
    /// <summary>
    /// Optimization result
    /// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Serializable] public sealed class OptimizerResult
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
