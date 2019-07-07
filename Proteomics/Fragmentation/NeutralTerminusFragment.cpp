#include "NeutralTerminusFragment.h"

using namespace Chemistry;
namespace Proteomics
{
    namespace Fragmentation
    {

        NeutralTerminusFragment::NeutralTerminusFragment(FragmentationTerminus terminus, double neutralMass, int fragmentNumber, int aminoAcidPosition) : Terminus(terminus), NeutralMass(static_cast<double>(ClassExtensions::RoundedDouble(std::make_optional(neutralMass)))), FragmentNumber(fragmentNumber), AminoAcidPosition(aminoAcidPosition)
        {
        }

        bool NeutralTerminusFragment::Equals(std::any obj)
        {
            NeutralTerminusFragment *other = std::any_cast<NeutralTerminusFragment*>(obj);

            return this->Terminus == other->Terminus && this->FragmentNumber == other->FragmentNumber && this->AminoAcidPosition == other->AminoAcidPosition && this->NeutralMass == other->NeutralMass;
        }

        int NeutralTerminusFragment::GetHashCode()
        {
            return NeutralMass.GetHashCode();
        }

        std::string NeutralTerminusFragment::ToString()
        {
            return "Term: " + Terminus + "; Mass: " + std::to_string(NeutralMass) + "; FragNum:" + std::to_string(FragmentNumber) + "; AA: " + std::to_string(AminoAcidPosition);
        }
    }
}
