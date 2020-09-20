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

            /// Required for Communication Operations in HPCMetaMorpheus
            static int Pack ( char *buf, size_t *buf_size, MatchedFragmentIon *MaF);
            static void Unpack ( char *buf, size_t buf_size, MatchedFragmentIon **newMaF );
        };
    }
}
