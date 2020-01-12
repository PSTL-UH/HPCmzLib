#pragma once

namespace FlashLFQ
{
    namespace BoundedNelderMeadOptimizer
    {
        class ParameterSampler
        {
        public:
            double Sample ( double min, double max, ParameterType type );
            
        };
    }
}
