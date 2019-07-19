#include "MatchedFragmentIon.h"
#include "Product.h"
#include "../../Chemistry/ClassExtensions.h"
#include "stringhelper.h"

using namespace Chemistry;
namespace Proteomics
{
    namespace Fragmentation
    {

        MatchedFragmentIon::MatchedFragmentIon(Product *neutralTheoreticalProduct, double experMz, double experIntensity, int charge) : NeutralTheoreticalProduct(neutralTheoreticalProduct), Mz(experMz), Intensity(experIntensity), Charge(charge)
        {
        }

        double MatchedFragmentIon::getMassErrorDa() const
        {
            return Chemistry::ClassExtensions::ToMass(Mz, Charge) - NeutralTheoreticalProduct->NeutralMass;
        }

        double MatchedFragmentIon::getMassErrorPpm() const
        {
            return (getMassErrorDa() / NeutralTheoreticalProduct->NeutralMass) * 1e6;
        }

        std::string MatchedFragmentIon::getAnnotation() const
        {
            StringBuilder *sb = new StringBuilder();

            bool containsNeutralLoss = NeutralTheoreticalProduct->NeutralLoss != 0;

            if (containsNeutralLoss)
            {
                sb->append("(");
            }

            sb->append(NeutralTheoreticalProduct->getAnnotation());

            if (containsNeutralLoss)
            {
                sb->append(")");
            }

            sb->append("+");
            sb->append(Charge);

            //delete sb;
            return sb->toString();
        }

        std::string MatchedFragmentIon::ToString()
        {
            // we add the blank space in the tostring because the values are treated like
            // integers and looked up as index in the enum instead of being converted to just string and concatenated
            return std::to_string(static_cast<int>(NeutralTheoreticalProduct->productType)) + ""
                + std::to_string(NeutralTheoreticalProduct->TerminusFragment->FragmentNumber) + "+"
                + std::to_string(Charge) + "\t;" + std::to_string(NeutralTheoreticalProduct->NeutralMass);
        }

        bool MatchedFragmentIon::Equals( MatchedFragmentIon *other)
        {
            
            return this->NeutralTheoreticalProduct->Equals(other->NeutralTheoreticalProduct) &&
                this->Charge    == other->Charge     &&
                this->Mz        == other->Mz         &&
                this->Intensity == other->Intensity;
        }

        int MatchedFragmentIon::GetHashCode()
        {
            return StringHelper::GetHashCode(std::to_string(Mz));
        }
    }
}
