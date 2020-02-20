#include "RandomUniform.h"

namespace SharpLearning::Optimization::ParameterSamplers {

    RandomUniform::RandomUniform(int seed) : m_random(new Random(seed)) {
    }

    double RandomUniform::Sample(double min, double max, ParameterType parameterType) {
        if (min >= max) {
            throw std::invalid_argument(StringHelper::formatSimple("min: {0} is larger than or equal to max: {1}", min, max));
        }

        switch (parameterType) {
            case ParameterType::Discrete:
                return SampleInteger(static_cast<int>(min), static_cast<int>(max));
            case ParameterType::Continuous:
                return SampleContinous(min, max);
            default:
                throw std::invalid_argument("Unknown parameter type: " + parameterType);
        }
    }

    double RandomUniform::SampleContinous(double min, double max) {
        return m_random->NextDouble() * (max - min) + min;
    }

    int RandomUniform::SampleInteger(int min, int max) {
        auto maxInclusive = max + 1; // Add one to get inclusive.
        return m_random->Next(min, maxInclusive);
    }
}
