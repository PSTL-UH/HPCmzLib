#pragma once

#include <string>
#include <any>
#include "stringbuilder.h"

#include "Product.h"

using namespace Chemistry;

namespace Proteomics
{
    namespace Fragmentation
    {
        class MatchedFragmentIon
        {
        public:
            Product *const NeutralTheoreticalProduct;
            const double Mz;
            const double Intensity;
            const int Charge;

            /// <summary>
            /// Constructs a new MatchedFragmentIon given information about a theoretical and an experimental
            /// fragment mass spectral peak
            /// </summary>
            virtual ~MatchedFragmentIon()
            {
                // delete NeutralTheoreticalProduct;
            }

            MatchedFragmentIon(Product *neutralTheoreticalProduct, double experMz, double experIntensity, int charge);

            double getMassErrorDa() const;

            double getMassErrorPpm() const;

            std::string getAnnotation() const;

            /// <summary>
            /// Summarizes a TheoreticalFragmentIon into a string for debug purposes
            /// </summary>
            std::string ToString();

            bool Equals(MatchedFragmentIon* obj);

            int GetHashCode();

            /// <summary>
            /// Pack a MatchedFragmentIon into a character buffer.
            /// Required for Communication Operations in HPCMetaMorpheus
            ///
            /// Arguments:
            /// buf :     INOUT buffer used for packing
            /// buf_size: IN size of the allocated buffer provided by the upper layer
            ///           OUT size of required buffer if not large enough (return value -1)
            ///               or number of bytes used for packgin (return value > 0)
            /// MaF :     IN (vector of) MatchedFragmentIon(s) to pack
            ///
            /// Return value:
            ///   -1 : input buffer was not large enough. buf_size will contain the required number
            ///        of bytes in this case
            ///   >0 : packing successful, number of bytes used up.
            /// </summary>
            static int Pack ( char *buf, size_t &buf_size, MatchedFragmentIon *MaF);
            static int Pack ( char *buf, size_t &buf_size, const std::vector<MatchedFragmentIon *> &MaF);

            /// <summary>
            /// Functionality used to reconstruct a MatchedFragmentIon based on a
            /// packed buffer.
            ///
            /// Arguments
            /// ---------
            /// buf:      IN input character buffer
            /// buf_size: IN size of input buffer
            /// len:      OUT number of bytes used for unpacking 'count' elements
            /// newMaF:   OUT (vector of) new MatchedFragmentIon(s) .
            /// count:    IN how many elements to unpack.
            ///           default : -1 (until end of buffer is reached)
            /// </summary>
            static void Unpack ( char *buf, size_t buf_size, size_t &len,
                                 std::vector<MatchedFragmentIon *> &newMaF,
                                 int count = -1 );
            static void Unpack ( char *buf, size_t buf_size, size_t &len,
                                 MatchedFragmentIon **newMaF );
            static void Unpack ( std::string line, size_t &len,
                                 MatchedFragmentIon **newMaF );


        };
    }
}
