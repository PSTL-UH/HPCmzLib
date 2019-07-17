#pragma once

#include "../../MassSpectrometry/Enums/DissociationType.h"
#include "ProductType.h"
#include <unordered_map>
#include <vector>
#include <optional>
#include "Nullable.h"

#include "../../Chemistry/Chemistry.h"
using namespace Chemistry;

#include "../../MassSpectrometry/MassSpectrometry.h"
using namespace MassSpectrometry;

namespace Proteomics
{
    namespace Fragmentation
    {
        class DissociationTypeCollection
        {
        public:
            static std::unordered_map<DissociationType, std::vector<ProductType>> ProductsFromDissociationType;

        private:
            static std::unordered_map<ProductType, std::optional<double>> NeutralMassShiftFromProductType;

        public:
            static double GetMassShiftFromProductType(ProductType productType);

            static double ProductTypeSpecificFragmentNeutralMass(double mass, ProductType p);
        };
    }
}
