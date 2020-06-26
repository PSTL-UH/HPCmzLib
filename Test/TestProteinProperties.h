#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <tuple>
#include <optional>
#include "stringhelper.h"

#include "../Proteomics/AminoAcidPolymer/AminoAcidPolymer.h"
using namespace Proteomics;


namespace Test
{
    class TestProteinProperties
    {
    public:
        static void TestHashAndEqualsProtein();

        static void TestHashAndEqualsSequenceVariation();

        static void TestHashAndEqualsDbRef();

        static void TestHashAndEqualsSpliceSite();

        static void TestHashAndEqualsDisulfide();

        static void TestHashAndEqualsProteolysis();

        static void CompareProteinProperties();
    };
}
