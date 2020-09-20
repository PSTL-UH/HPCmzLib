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
        static void SerializePeptideWithSetModifications();

        static void SerializeMatchedFragmentIon();
    };
}
