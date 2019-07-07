#include "TerminusSpecificProductTypes.h"

namespace Proteomics
{
    namespace Fragmentation
    {

std::unordered_map<FragmentationTerminus, std::vector<ProductType>> TerminusSpecificProductTypes::ProductIonTypesFromSpecifiedTerminus =
{
    {
        FragmentationTerminus::N, {ProductType::a, ProductType::aDegree, ProductType::aStar, ProductType::b, ProductType::bDegree, ProductType::bStar, ProductType::c}
    },
    {
        FragmentationTerminus::C, {ProductType::x, ProductType::y, ProductType::yDegree, ProductType::yStar, ProductType::zDot, ProductType::zPlusOne}
    },
    {
        FragmentationTerminus::Both, {ProductType::a, ProductType::aDegree, ProductType::aStar, ProductType::b, ProductType::bDegree, ProductType::bStar, ProductType::c, ProductType::x, ProductType::y, ProductType::yDegree, ProductType::yStar, ProductType::zDot, ProductType::zPlusOne}
    },
    {FragmentationTerminus::None, std::vector<ProductType>()}
};
std::unordered_map<ProductType, FragmentationTerminus> TerminusSpecificProductTypes::ProductTypeToFragmentationTerminus =
{
    {ProductType::a, FragmentationTerminus::N},
    {ProductType::aDegree, FragmentationTerminus::N},
    {ProductType::aStar, FragmentationTerminus::N},
    {ProductType::b, FragmentationTerminus::N},
    {ProductType::bDegree, FragmentationTerminus::N},
    {ProductType::bStar, FragmentationTerminus::N},
    {ProductType::c, FragmentationTerminus::N},
    {ProductType::x, FragmentationTerminus::C},
    {ProductType::y, FragmentationTerminus::C},
    {ProductType::yDegree, FragmentationTerminus::C},
    {ProductType::yStar, FragmentationTerminus::C},
    {ProductType::zDot, FragmentationTerminus::C},
    {ProductType::zPlusOne, FragmentationTerminus::C}
};
    }
}
