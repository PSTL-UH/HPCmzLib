#include <stdlib.h>
#include "ParameterSampler.h"
#include "MzLibUtil.h"

namespace FlashLFQ
{
    namespace BoundedNelderMeadOptimizer
    {
        ParameterSampler::ParameterSampler ( int seed) {
            srand(seed);
        }
        
        /// <summary>
        /// Sample values random uniformly between min and max.
        /// </summary>
        /// <param name="min"></param>
        /// <param name="max"></param>
        /// <param name="parameterType">Selects the type of parameter.
        /// Should the parameter be sampled as discrete values, or
        ///     as continous values.</param>
        /// <returns></returns>
        double ParameterSampler::Sample(double min, double max, ParameterType parameterType)
        {
            if (min >= max)  {
                throw MzLibUtil::MzLibException("ParameterSampler: min is larger than or equal to max");
            }
            
            switch (parameterType)
            {
                case ParameterType::Discrete:
                    return SampleInteger((int)min, (int)max);
                case ParameterType::Continuous:
                    return SampleContinous(min, max);
                default:
                    throw MzLibUtil::MzLibException("ParameterSampler:Unknown parameter type: ");
            }
        }
        
        double ParameterSampler::NextDouble()
        {
            double min=0.0, max=1.0;
            return SampleContinous ( min, max );
        }

        double ParameterSampler::SampleContinous(double min, double max)
        {
            return ((((double)rand()) / (RAND_MAX)) +1) * (max - min) + min;
        }

        
        int ParameterSampler::SampleInteger(int min, int max)
        {
            int maxInclusive = max + 1; // Add one to get inclusive.
            return rand() % maxInclusive + min;
        }
    };
}
