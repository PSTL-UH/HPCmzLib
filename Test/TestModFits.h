#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <cmath>
#include "stringhelper.h"

using namespace NUnit::Framework;
using namespace Proteomics;
namespace Stopwatch = System::Diagnostics::Stopwatch;

namespace Test
{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [TestFixture] public static class TestModFits
    class TestModFits final
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
//ORIGINAL LINE: [Test] public static void TestModFitss()
        static void TestModFitss();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test][TestCase("M", "X", true)][TestCase("M", "J", false)][TestCase("I", "J", true)][TestCase("L", "X", true)][TestCase("M", "B", false)][TestCase("D", "B", true)][TestCase("N", "B", true)][TestCase("M", "Z", false)][TestCase("E", "Z", true)][TestCase("Q", "Z", true)] public static void TestAmbiguousModFits(string proteinSequence, string motifString, bool result)
        static void TestAmbiguousModFits(const std::string &proteinSequence, const std::string &motifString, bool result);
    };
}
