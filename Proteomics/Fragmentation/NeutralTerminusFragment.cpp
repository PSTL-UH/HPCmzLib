#include "NeutralTerminusFragment.h"

//using namespace Chemistry;
namespace Proteomics
{
    namespace Fragmentation
    {

        NeutralTerminusFragment::NeutralTerminusFragment(FragmentationTerminus terminus, double neutralMass, int fragmentNumber, int aminoAcidPosition) : Terminus(terminus), NeutralMass(Chemistry::ClassExtensions::RoundedDouble(neutralMass)), FragmentNumber(fragmentNumber), AminoAcidPosition(aminoAcidPosition)
        {
        }

        bool NeutralTerminusFragment::Equals(NeutralTerminusFragment *other)
        {
            
            return this->Terminus == other->Terminus          &&
                this->FragmentNumber == other->FragmentNumber &&
                this->AminoAcidPosition == other->AminoAcidPosition &&
                this->NeutralMass == other->NeutralMass;
        }

        int NeutralTerminusFragment::GetHashCode()
        {
            return StringHelper::GetHashCode(std::to_string(NeutralMass));
        }

        std::string NeutralTerminusFragment::ToString()
        {
            return "Term: " + std::to_string(static_cast<int>(Terminus)) + "; Mass: " + std::to_string(NeutralMass) + "; FragNum:" + std::to_string(FragmentNumber) + "; AA: " + std::to_string(AminoAcidPosition);
        }
    }
}
