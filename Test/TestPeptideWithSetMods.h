#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <tuple>
#include "stringhelper.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Proteomics { class Protein; }

using namespace NUnit::Framework;
using namespace Proteomics;
using namespace Proteomics::Fragmentation;
using namespace Proteomics::ProteolyticDigestion;
namespace Stopwatch = System::Diagnostics::Stopwatch;

namespace Test
{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [TestFixture] public static class TestPeptideWithSetMods
    class TestPeptideWithSetMods final
    {
    private:
        static Stopwatch *privateStopwatch;

        static Stopwatch *getStopwatch();
        static void setStopwatch(Stopwatch *value);

    public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [SetUp] public static void Setuppp()
        static void Setuppp();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [TearDown] public static void TearDown()
        static void TearDown();

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
