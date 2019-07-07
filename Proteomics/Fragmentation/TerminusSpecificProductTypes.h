#pragma once

#include "FragmentationTerminus.h"
#include "ProductType.h"
#include <unordered_map>
#include <vector>


namespace Proteomics
{
    namespace Fragmentation
    {
        class TerminusSpecificProductTypes
        {
        public:
            static std::unordered_map<FragmentationTerminus, std::vector<ProductType>> ProductIonTypesFromSpecifiedTerminus;

            static std::unordered_map<ProductType, FragmentationTerminus> ProductTypeToFragmentationTerminus;

        };
    }
}
