#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include "stringhelper.h"
#include "tangible_filesystem.h"

using namespace NUnit::Framework;
using namespace Proteomics;
using namespace Proteomics::ProteolyticDigestion;
namespace Stopwatch = System::Diagnostics::Stopwatch;

namespace Test
{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [TestFixture] public class TestSeqCoverage
    class TestSeqCoverage
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
//ORIGINAL LINE: [Test] public static void MultipleProteaseSelectionTest()
        static void MultipleProteaseSelectionTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void MultipleProteaseSelectionTestMissedCleavage()
        static void MultipleProteaseSelectionTestMissedCleavage();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void MultipleProteaseSelectionTestPreventCleavage()
        static void MultipleProteaseSelectionTestPreventCleavage();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void ReadCustomFile()
        static void ReadCustomFile();
    };
}
