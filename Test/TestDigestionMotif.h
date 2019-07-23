#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "stringhelper.h"

using namespace MzLibUtil;
using namespace NUnit::Framework;
using namespace Proteomics;
using namespace Proteomics::ProteolyticDigestion;
namespace Stopwatch = System::Diagnostics::Stopwatch;

namespace Test
{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [TestFixture] public class TestDigestionMotif
    class TestDigestionMotif
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
//ORIGINAL LINE: [Test] public static void TestParseProtease()
        static void TestParseProtease();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestBasicProtease1()
        static void TestBasicProtease1();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestBasicProtease2()
        static void TestBasicProtease2();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestWildCardExclusion()
        static void TestWildCardExclusion();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestMultiLetterProtease()
        static void TestMultiLetterProtease();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestNTerminusProtease()
        static void TestNTerminusProtease();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestSyntax()
        static void TestSyntax();
    };
}
