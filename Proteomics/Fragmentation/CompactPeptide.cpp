#include "CompactPeptide.h"

using namespace Proteomics::ProteolyticDigestion;
namespace Proteomics
{
    namespace Fragmentation
    {

        CompactPeptide::CompactPeptide(PeptideWithSetModifications *peptideWithSetModifications, FragmentationTerminus fragmentationTerminus)
        {
            setTerminalMasses(ComputeNeutralTerminusFragments(peptideWithSetModifications, fragmentationTerminus).ToArray());
            setMonoisotopicMassIncludingFixedMods(peptideWithSetModifications->getMonoisotopicMass());
        }
    }
}
