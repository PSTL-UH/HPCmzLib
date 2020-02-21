#pragma once

#include "ParameterType.h"

namespace FlashLFQ
{
    namespace BoundedNelderMeadOptimizer
    {
        class ParameterSampler
        {
        public:
            ParameterSampler (int seed=343);
            double Sample ( double min, double max, ParameterType type );
            double NextDouble ();
            
        private:
            double SampleContinous(double min, double max);
            int SampleInteger(int min, int max);

        };
    }
}
