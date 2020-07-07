#pragma once

#include "FragmentationTerminus.h"
#include <vector>
#include <any>

#include "../ProteolyticDigestion/PeptideWithSetModifications.h"
#include "../Fragmentation/NeutralTerminusFragment.h"

#include "../../Chemistry/Chemistry.h"
using namespace Chemistry;

#include "../AminoAcidPolymer/AminoAcidPolymer.h"
using namespace Proteomics::AminoAcidPolymer;

//#include "../ProteolyticDigestion/ProteolyticPeptide.h"
//using namespace Proteomics::ProteolyticDigestion;

namespace Proteomics
{
    namespace Fragmentation
    {
        //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        //ORIGINAL LINE: [Serializable] public abstract class CompactPeptideBase :
        //               IEquatable<CompactPeptideBase>
        //class CompactPeptideBase : public Equatable<CompactPeptideBase*>

        class CompactPeptideBase 
        {
        private:
            std::vector<NeutralTerminusFragment*> privateTerminalMasses;
            double privateMonoisotopicMassIncludingFixedMods = 0;

            public:
                std::vector<NeutralTerminusFragment*> getTerminalMasses() const;
                void setTerminalMasses(const std::vector<NeutralTerminusFragment*> &value);
                double getMonoisotopicMassIncludingFixedMods() const;
                void setMonoisotopicMassIncludingFixedMods(double value);

            /// <summary>
            /// Sometimes says not equal when in reality should be equal, due to rounding errors. S
            /// mall but annoying bug. Careful when fixing! Make sure Indexing runs at a reasonable speed.
            /// </summary>
            bool Equals(CompactPeptideBase *obj);

            int GetHashCode();

        protected:
            static std::vector<NeutralTerminusFragment*> ComputeNeutralTerminusFragments(ProteolyticDigestion::PeptideWithSetModifications *peptide, FragmentationTerminus fragmentationTerminus);
        };
    }
}
