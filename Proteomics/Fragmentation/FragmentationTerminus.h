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
        static FragmentationTerminus FragmentationTerminusFromString ( std::string s ) {
            FragmentationTerminus t;
            if ( s == "Both" ) {
                t = FragmentationTerminus::Both;
            }
            else if ( s == "N" ) {
                t = FragmentationTerminus::N;
            }
            else if ( s == "C" ) {
                t = FragmentationTerminus::C;
            }
            else if ( s == "None" ) {
                t = FragmentationTerminus::None;
            }
            return t;
        }
    }
}
