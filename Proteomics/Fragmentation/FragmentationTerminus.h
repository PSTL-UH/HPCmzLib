#pragma once

#include <string>

namespace Proteomics
{
    namespace Fragmentation
    {
        enum class FragmentationTerminus
        {
            Both, //N- and C-terminus
            N, //N-terminus only
            C, //C-terminus only
            None //could be used for top down intact mass
        };

        static std::string FragmentationTerminusToString( FragmentationTerminus t ) {
            std::string s;

            if ( t == FragmentationTerminus::Both ) {
                s = "Both";
            }
            else if ( t == FragmentationTerminus::N ) {
                s = "N";
            }
            else if ( t == FragmentationTerminus::C ) {
                s = "C";
            }
            else if ( t == FragmentationTerminus::None ) {
                s = "None";
            }
            
            return s;
        }
    }
}
