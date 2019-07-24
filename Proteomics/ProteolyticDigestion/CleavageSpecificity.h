#pragma once

#include <string>
#include <cctype>
#include <algorithm>

namespace Proteomics
{
    namespace ProteolyticDigestion
    {
        enum class CleavageSpecificity
        {
            None,
            Semi,
            Full,
            SingleN,
            SingleC,
            Unknown //used for fast Semi/NonSpecific searches when peptide is cleaved post-search
        };

        class CleavageSpecificityExtension {
        public:
            static CleavageSpecificity ParseString(std::string &s)
            {
                std::transform(s.begin(), s.end(), s.begin(), [] (unsigned char c) {return toupper(c); } );
                if ( s.find("NONE") != std::string::npos ) {
                    return CleavageSpecificity::None;
                }
                else if ( s.find("SEMI") != std::string::npos ) {
                    return CleavageSpecificity::Semi;
                }
                else if ( s.find("FULL") != std::string::npos ) {
                    return CleavageSpecificity::Full;
                }
                else if ( s.find("SINGLEN") != std::string::npos ) {
                    return CleavageSpecificity::SingleN;
                }
                else if ( s.find("SINGLEC") != std::string::npos ) {
                    return CleavageSpecificity::SingleC;
                }
                return  CleavageSpecificity::Unknown;
            }
        };
    }
}
