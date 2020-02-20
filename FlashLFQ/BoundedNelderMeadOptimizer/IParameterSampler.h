#pragma once

#include "../ParameterType.h"

namespace SharpLearning::Optimization::ParameterSamplers {
    /// <summary>
    /// Defines the interface for a parameter samplers. 
    /// </summary>
    class IParameterSampler {
        /// <summary>
        /// Returns a sample within in the specified min/max boundaries.
        /// </summary>
        /// <param name="min">Minimum bound</param>
        /// <param name="max">Maximum bound</param>
        /// <param name="parameterType">Selects the type of parameter. Should the parameter be sampled as discrete values, or as continuous values.</param>
        /// <returns></returns>
    public:
        virtual double Sample(double min, double max, ParameterType parameterType) = 0;
    };
}
