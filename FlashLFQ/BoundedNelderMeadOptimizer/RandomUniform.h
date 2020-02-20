#pragma once

#include "IParameterSampler.h"
#include "../ParameterType.h"
#include <stdexcept>
#include "stringhelper.h"

namespace SharpLearning::Optimization::ParameterSamplers {
    /// <summary>
    /// Sample values random uniformly between min and max.    
    /// </summary>
    class RandomUniform : public IParameterSampler {
    private:
        Random *const m_random;

        /// <summary>
        /// Sample values random uniformly between min and max. 
        /// </summary>
        /// <param name="seed"></param>
    public:
        virtual ~RandomUniform() {
            delete m_random;
        }

        RandomUniform(int seed = 343);

        /// <summary>
        /// Sample values random uniformly between min and max.
        /// </summary>
        /// <param name="min"></param>
        /// <param name="max"></param>
        /// <param name="parameterType">Selects the type of parameter. Should the parameter be sampled as discrete values, or as continous values.</param>
        /// <returns></returns>
        double Sample(double min, double max, ParameterType parameterType) override;

    private:
        double SampleContinous(double min, double max);

        int SampleInteger(int min, int max);
    };
}
