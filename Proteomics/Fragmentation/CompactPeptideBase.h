#pragma once

#include "FragmentationTerminus.h"
#include <vector>
#include <any>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Proteomics { namespace Fragmentation { class NeutralTerminusFragment; } }

using namespace Chemistry;
using namespace Proteomics::AminoAcidPolymer;
using namespace Proteomics::ProteolyticDigestion;

namespace Proteomics
{
    namespace Fragmentation
    {
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Serializable] public abstract class CompactPeptideBase : IEquatable<CompactPeptideBase>
        class CompactPeptideBase : public IEquatable<CompactPeptideBase*>
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
            /// Sometimes says not equal when in reality should be equal, due to rounding errors. Small but annoying bug. Careful when fixing! Make sure Indexing runs at a reasonable speed.
            /// </summary>
            bool Equals(std::any obj) override;

            int GetHashCode() override;

            bool Equals(CompactPeptideBase *cp) override;

        protected:
            static std::vector<NeutralTerminusFragment*> ComputeNeutralTerminusFragments(PeptideWithSetModifications *peptide, FragmentationTerminus fragmentationTerminus);
        };
    }
}
