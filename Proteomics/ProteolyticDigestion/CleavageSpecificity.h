#pragma once

namespace Proteomics
{
    namespace ProteolyticDigestion
    {
        enum class CleavageSpecificity
        {
            None,
            Semi,
            Full,
            SingleN,
            SingleC,
            Unknown //used for fast Semi/NonSpecific searches when peptide is cleaved post-search
        };
    }
}
