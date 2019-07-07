#pragma once

#include "CompactPeptideBase.h"
#include "FragmentationTerminus.h"

using namespace Proteomics::ProteolyticDigestion;

namespace Proteomics
{
    namespace Fragmentation
    {
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Serializable] public class CompactPeptide : CompactPeptideBase
        class CompactPeptide : public CompactPeptideBase
        {
        public:
            CompactPeptide(PeptideWithSetModifications *peptideWithSetModifications, FragmentationTerminus fragmentationTerminus);
        };
    }
}
