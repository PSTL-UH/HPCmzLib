#pragma once

namespace FlashLFQ
{
    namespace BoundedNelderMeadOptimizer {
        /// <summary>
        /// Type of the parameter
        /// </summary>
        enum class ParameterType {
            /// <summary>
            /// Discrete parameter, represented by integer values.
            /// </summary>
            Discrete,
                
                /// <summary>
                /// Continuous parameter, represented by floating point numbers.
                /// </summary>
                Continuous
                };
    }
}
