#include "ProductTypeMethods.h"

using namespace Proteomics::Fragmentation;
namespace Proteomics
{
    namespace ProteolyticDigestion
    {

        FragmentationTerminus ProductTypeMethods::IdentifyTerminusType(std::vector<ProductType> &productTypes)
        {
            if ((std::find(productTypes.begin(), productTypes.end(), ProductType::b) != productTypes.end() || productTypes.Contains(ProductType::c) || productTypes.Contains(ProductType::aDegree)) && (productTypes.Contains(ProductType::y) || productTypes.Contains(ProductType::zDot) || productTypes.Contains(ProductType::zPlusOne) || productTypes.Contains(ProductType::x)))
            {
                return FragmentationTerminus::Both;
            }
            else if (std::find(productTypes.begin(), productTypes.end(), ProductType::y) != productTypes.end() || productTypes.Contains(ProductType::zDot) || productTypes.Contains(ProductType::zPlusOne) || productTypes.Contains(ProductType::x))
            {
                return FragmentationTerminus::C;
            }
            else //"lp.Contains(ProductType.B) || lp.Contains(ProductType.BnoB1ions) || lp.Contains(ProductType.C) || lp.Contains(ProductType.Adot))"
            {
                return FragmentationTerminus::N;
            }
        }

        std::vector<std::vector<ProductType>> ProductTypeMethods::SeparateIonsByTerminus(std::vector<ProductType> &ionTypes)
        {
            std::vector<ProductType> nIons;
            std::vector<ProductType> cIons;
            for (auto productType : ionTypes)
            {
                if (productType == ProductType::b || productType == ProductType::c)
                {
                    nIons.push_back(productType);
                }
                else // Y and Z
                {
                    cIons.push_back(productType);
                }
            }
            if (nIons.size() != 0 && cIons.size() != 0)
            {
                return std::vector<std::vector<ProductType>> {nIons, cIons};
            }
            else if (nIons.size() != 0)
            {
                return std::vector<std::vector<ProductType>> {nIons};
            }
            else if (cIons.size() != 0)
            {
                return std::vector<std::vector<ProductType>> {cIons};
            }
            else
            {
                throw std::invalid_argument("No ions types were selected.");
            }
        }
    }
}
