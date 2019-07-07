#pragma once

#include <string>
#include <any>
#include "stringbuilder.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Proteomics { namespace Fragmentation { class Product; } }

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
            /// Constructs a new MatchedFragmentIon given information about a theoretical and an experimental fragment mass spectral peak
            /// </summary>
            virtual ~MatchedFragmentIon()
            {
                delete NeutralTheoreticalProduct;
            }

            MatchedFragmentIon(Product *neutralTheoreticalProduct, double experMz, double experIntensity, int charge);

            double getMassErrorDa() const;

            double getMassErrorPpm() const;

            std::string getAnnotation() const;

            /// <summary>
            /// Summarizes a TheoreticalFragmentIon into a string for debug purposes
            /// </summary>
            std::string ToString() override;

            bool Equals(std::any obj) override;

            int GetHashCode() override;
        };
    }
}
