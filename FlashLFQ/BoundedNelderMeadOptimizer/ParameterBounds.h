#pragma once

#include "Transform.h"
#include "ParameterType.h"

namespace FlashLFQ
{
    namespace BoundedNelderMeadOptimizer {
        /// <summary>
        /// Type of the parameter
        /// </summary>
        class ParameterBounds {
        private:
            Transform const transform;            
            const ParameterType parameterType;

        public:
            double Min=0, Max=0;

            ParameterBounds (double min, double max, Transform trans = Transform::Linear, ParameterType paramType = ParameterType::Continuous): transform(trans), parameterType(paramType) {
                if ( min > max ) {
                    //uff
                }
                Min = min;
                Max = max;

            }
            
            //double SampleValue(ParameterSampler *sampler) override;
        };
    }
}
