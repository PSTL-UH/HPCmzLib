#pragma once

#include "FragmentationTerminus.h"
#include <string>
#include <any>

using namespace Chemistry;

namespace Proteomics
{
    namespace Fragmentation
    {
        /// <summary>
        /// This object has the neutral mass, the fragment terminus, and the amino acid position of the last amino acid in the fragment next to the 
        /// break in the peptide backbone. N-terminal amino acid is numbered 1.
        /// See for Reference the following two web-pages.
        /// http://www.matrixscience.com/help/fragmentation_help.html
        /// http://www.matrixscience.com/help/aa_help.html
        /// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Serializable] public class NeutralTerminusFragment
        class NeutralTerminusFragment
        {
        public:
            const FragmentationTerminus Terminus;
            const double NeutralMass;
            const int FragmentNumber;
            const int AminoAcidPosition;

            NeutralTerminusFragment(FragmentationTerminus terminus, double neutralMass, int fragmentNumber, int aminoAcidPosition);

            bool Equals(std::any obj) override;

            int GetHashCode() override;

            std::string ToString() override;
        };
    }
}
