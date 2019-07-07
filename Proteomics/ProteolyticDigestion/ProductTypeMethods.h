#pragma once

#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace Proteomics::Fragmentation;

namespace Proteomics
{
    namespace ProteolyticDigestion
    {
        class ProductTypeMethods final
        {
        public:
            static FragmentationTerminus IdentifyTerminusType(std::vector<ProductType> &productTypes);

            static std::vector<std::vector<ProductType>> SeparateIonsByTerminus(std::vector<ProductType> &ionTypes);
        };
    }
}
