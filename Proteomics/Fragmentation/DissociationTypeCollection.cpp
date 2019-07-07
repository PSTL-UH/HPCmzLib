#include "DissociationTypeCollection.h"
#include "../../Chemistry/ChemicalFormula.h"
#include "../../Chemistry/Constants.h"
#include "../../MzLibUtil/MzLibException.h"
#include "../../Chemistry/ClassExtensions.h"

using namespace Chemistry;
using namespace MassSpectrometry;
namespace Proteomics
{
    namespace Fragmentation
    {

std::unordered_map<DissociationType, std::vector<ProductType>> DissociationTypeCollection::ProductsFromDissociationType =
{
    {DissociationType::Unknown, std::vector<ProductType>()},
    {
        DissociationType::CID, {ProductType::b, ProductType::y}
    },
    {
        DissociationType::IRMPD, {ProductType::b, ProductType::y}
    },
    {
        DissociationType::ECD, {ProductType::c, ProductType::y, ProductType::zDot}
    },
    {DissociationType::PQD, std::vector<ProductType>()},
    {
        DissociationType::ETD, {ProductType::c, ProductType::y, ProductType::zDot}
    },
    {
        DissociationType::HCD, {ProductType::b, ProductType::y}
    },
    {
        DissociationType::AnyActivationType, {ProductType::b, ProductType::y}
    },
    {
        DissociationType::EThcD, {ProductType::b, ProductType::y, ProductType::c, ProductType::zDot}
    },
    {DissociationType::Custom, std::vector<ProductType>()},
    {DissociationType::ISCID, std::vector<ProductType>()}
};
std::unordered_map<ProductType, std::optional<double>> DissociationTypeCollection::NeutralMassShiftFromProductType =
{
    {ProductType::a, nullptr},
    {ProductType::aStar, nullptr},
    {ProductType::aDegree, nullptr},
    {ProductType::b, nullptr},
    {ProductType::bStar, nullptr},
    {ProductType::bDegree, nullptr},
    {ProductType::c, nullptr},
    {ProductType::x, nullptr},
    {ProductType::y, nullptr},
    {ProductType::yStar, nullptr},
    {ProductType::yDegree, nullptr},
    {ProductType::zDot, nullptr},
    {ProductType::zPlusOne, nullptr},
    {ProductType::M, nullptr},
    {ProductType::D, nullptr}
};

        double DissociationTypeCollection::GetMassShiftFromProductType(ProductType productType)
        {
            Nullable<double> shift;
            std::unordered_map<ProductType, std::optional<double>>::const_iterator NeutralMassShiftFromProductType_iterator = NeutralMassShiftFromProductType.find(productType);
            if (NeutralMassShiftFromProductType_iterator != NeutralMassShiftFromProductType.end())
            {
                shift = NeutralMassShiftFromProductType_iterator->second;
                if (!shift.HasValue)
                {
                    // compute formula
                    switch (productType)
                    {
                        case ProductType::a:
                            NeutralMassShiftFromProductType[productType] = std::make_optional(ChemicalFormula::ParseFormula("C-1O-1")->getMonoisotopicMass());
                            break;
                        case ProductType::aStar:
                            NeutralMassShiftFromProductType[productType] = std::make_optional(ChemicalFormula::ParseFormula("C-1O-1N-1H-3")->getMonoisotopicMass());
                            break;
                        case ProductType::aDegree:
                            NeutralMassShiftFromProductType[productType] = std::make_optional(ChemicalFormula::ParseFormula("C-1O-2H-2")->getMonoisotopicMass());
                            break; // -46.0054793036,-C -O2 -H2
                        case ProductType::b:
                            NeutralMassShiftFromProductType[productType] = std::make_optional(0);
                            break; // 0, no change
                        case ProductType::bStar:
                            NeutralMassShiftFromProductType[productType] = std::make_optional(ChemicalFormula::ParseFormula("N-1H-3")->getMonoisotopicMass());
                            break; // -17.02654910112, -N -H3
                        case ProductType::bDegree:
                            NeutralMassShiftFromProductType[productType] = std::make_optional(ChemicalFormula::ParseFormula("H-2O-1")->getMonoisotopicMass());
                            break; // -18.01056468403, -H2 -O1
                        case ProductType::c:
                            NeutralMassShiftFromProductType[productType] = std::make_optional(ChemicalFormula::ParseFormula("N1H3")->getMonoisotopicMass());
                            break; // 17.02654910112, +N1 +H3
                        case ProductType::x:
                            NeutralMassShiftFromProductType[productType] = std::make_optional(ChemicalFormula::ParseFormula("C1O2")->getMonoisotopicMass());
                            break; // 43.98982923914, +C1 +O2
                        case ProductType::y:
                            NeutralMassShiftFromProductType[productType] = std::make_optional(ChemicalFormula::ParseFormula("H2O1")->getMonoisotopicMass());
                            break; // 18.01056468403, +O +H2
                        case ProductType::yStar:
                            NeutralMassShiftFromProductType[productType] = std::make_optional(ChemicalFormula::ParseFormula("O1H-1N-1")->getMonoisotopicMass());
                            break; // 0.98401558291000057, +O -H -N
                        case ProductType::yDegree:
                            NeutralMassShiftFromProductType[productType] = std::make_optional(0);
                            break; // 0, no change
                        case ProductType::zDot:
                            NeutralMassShiftFromProductType[productType] = std::make_optional(ChemicalFormula::ParseFormula("O1N-1H-1")->getMonoisotopicMass() + Constants::ElectronMass + Constants::ProtonMass);
                            break; //1.991840552567, +O -NH + e- + p+
                        case ProductType::zPlusOne:
                            NeutralMassShiftFromProductType[productType] = std::make_optional(ChemicalFormula::ParseFormula("O1H1N-1")->getMonoisotopicMass());
                            break; //; 2.9996656473699996, +O +H -N:
                        case ProductType::M:
                            NeutralMassShiftFromProductType[productType] = std::make_optional(0);
                            break; // no change
                        case ProductType::D:
                            NeutralMassShiftFromProductType[productType] = std::make_optional(0);
                            break; // no change
                    }
                }

                return NeutralMassShiftFromProductType[productType].value();
            }
            else
            {
                shift = NeutralMassShiftFromProductType_iterator->second;
                throw MzLibUtil::MzLibException("Unknown product type!");
            }
        }

        double DissociationTypeCollection::ProductTypeSpecificFragmentNeutralMass(double mass, ProductType p)
        {
            return static_cast<double>(ClassExtensions::RoundedDouble(std::make_optional(mass + GetMassShiftFromProductType(p)), 9));
        }
    }
}
