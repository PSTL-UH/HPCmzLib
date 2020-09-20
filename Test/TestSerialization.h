#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <tuple>
#include "../include/stringhelper.h"
#include "../Proteomics/Proteomics.h"

using namespace Proteomics;
using namespace Proteomics::Fragmentation;
using namespace Proteomics::ProteolyticDigestion;

namespace Test
{
    class TestSerialization final
    {
    public:
        static void SerializePeptideWithSetModifications1();
        
        static void SerializePeptideWithSetModifications2();

#ifdef USE_MPI
        static void SerializePeptideWithSetModifications_MPI();
#endif
        
        static void SerializeMatchedFragmentIon();
#ifdef USE_MPI
        static void SerializeMatchedFragmentIon_MPI();
#endif
    };
}
