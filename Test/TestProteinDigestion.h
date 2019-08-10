#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <cmath>
#include <tuple>
#include <optional>
#include "stringhelper.h"

#include "../Chemistry/Chemistry.h"
using namespace Chemistry;

#include "../MassSpectrometry/MassSpectrometry.h"
using namespace MassSpectrometry;

#include "../Proteomics/AminoAcidPolymer/AminoAcidPolymer.h"
using namespace Proteomics;
using namespace Proteomics::AminoAcidPolymer;

#include "../Proteomics/Fragmentation/Fragmentation.h"
using namespace Proteomics::Fragmentation;

#include "../Proteomics/ProteolyticDigestion/ProteinDigestion.h"
using namespace Proteomics::ProteolyticDigestion;

namespace Test
{
    class TestProteinDigestion final
    {
    public:
        static void TestGoodPeptide();

        static void TestNoCleavage();

        static void TestBadPeptide();

        static void TestPeptideWithSetModifications();

        static void TestPeptideWithFixedModifications();

        static void TestDigestIndices();

        static void TestDigestDecoy();

        static void TestGoodPeptideWithLength();

        static void Test_ProteinDigest();

        static void TestReadPeptideFromString();
    };
}
