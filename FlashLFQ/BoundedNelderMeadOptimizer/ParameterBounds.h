#pragma once

// This is just a temporary placeholder until its clear what else we need from this class.
// It is based of the SharpLearning.Optimization.ParameterSpecs::MinMaxParameterSpec class.

namespace FlashLFQ
{
    namespace BoundedNelderMeadOptimizer {
        /// <summary>
        /// Type of the parameter
        /// </summary>
        class ParameterBounds {
        public:
            double Min=0, Max=0;

            ParameterBounds (double min, double max) {
                if ( min > max ) {
                    //uff
                }
                Min = min;
                Max = max;
            }
            
            //Transform transform=Transform::Linear; 
            //ParameterType parameterType = ParameterType::Continuous;

            //double SampleValue(ParameterSampler *sampler) override;
        };
    }
}
