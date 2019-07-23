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

using namespace Chemistry;
using namespace MassSpectrometry;
using namespace NUnit::Framework;
using namespace Proteomics;
using namespace Proteomics::AminoAcidPolymer;
using namespace Proteomics::Fragmentation;
using namespace Proteomics::ProteolyticDigestion;
//C# TO C++ CONVERTER TODO TASK: The C# 'using static' statement  cannot be converted to C++:
//using static Chemistry::PeriodicTable;
namespace Stopwatch = System::Diagnostics::Stopwatch;

namespace Test
{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [TestFixture] public static class TestProteinDigestion
    class TestProteinDigestion final
    {
    private:
        static Stopwatch *privateStopwatch;

        static Stopwatch *getStopwatch();
        static void setStopwatch(Stopwatch *value);

    public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [SetUp] public static void Setup()
        static void Setup();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [TearDown] public static void TearDown()
        static void TearDown();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestGoodPeptide()
        static void TestGoodPeptide();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestNoCleavage()
        static void TestNoCleavage();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestBadPeptide()
        static void TestBadPeptide();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestPeptideWithSetModifications()
        static void TestPeptideWithSetModifications();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestPeptideWithFixedModifications()
        static void TestPeptideWithFixedModifications();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestDigestIndices()
        static void TestDigestIndices();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestDigestDecoy()
        static void TestDigestDecoy();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestGoodPeptideWithLength()
        static void TestGoodPeptideWithLength();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void Test_ProteinDigest()
        static void Test_ProteinDigest();

        /// <summary>
        /// Tests that a PeptideWithSetModifications object can be parsed correctly from a string, with mod info
        /// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestReadPeptideFromString()
        static void TestReadPeptideFromString();
    };
}
