#pragma once

#include <vector>
#include <algorithm>
#include <stdexcept>

#include "../Fragmentation/ProductType.h"
#include "../Fragmentation/FragmentationTerminus.h"
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
