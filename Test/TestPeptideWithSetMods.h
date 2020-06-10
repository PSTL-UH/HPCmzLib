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
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [TestFixture] public static class TestPeptideWithSetMods
    class TestPeptideWithSetMods final
    {
    private:

    public:
        /// <summary>
        /// The purpose of this test is to ensure that two peptides digested from two different proteases are not equal even if their sequences are equal
        /// This is important for multiprotease parsimony in MetaMorpheus
        /// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestDifferentProteaseEquals()
        static void TestDifferentProteaseEquals();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestSemiFewCleavages()
        static void TestSemiFewCleavages();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestNonAndSemiSpecificDigests()
        static void TestNonAndSemiSpecificDigests();

    private:
        static void TestSingleProteases(Protein *protein, InitiatorMethionineBehavior initiatorMethionineBehavior, FragmentationTerminus fragmentationTerminus, int numSequencesExpected);

    public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestHardToParseModifiedSequence()
        static void TestHardToParseModifiedSequence();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestCTermAndLastSideChainModParsing()
        static void TestCTermAndLastSideChainModParsing();
    };
}
