#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <limits>
#include <optional>
#include "stringhelper.h"
#include "tangible_filesystem.h"

using namespace Chemistry;
using namespace IO::MzML;
using namespace IO::Thermo;
using namespace MassSpectrometry;
using namespace MzLibUtil;
using namespace NUnit::Framework;
namespace Stopwatch = System::Diagnostics::Stopwatch;

namespace TestThermo
{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [TestFixture][Ignore("Takes 20 mins on appveyor")] public sealed class TestThermo
    class TestThermo final
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

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test][TestCase("testFileWMS2.raw", "a.mzML", "aa.mzML")][TestCase("small.raw", "a.mzML", "aa.mzML")][TestCase("05-13-16_cali_MS_60K-res_MS.raw", "a.mzML", "aa.mzML")] public static void ReadWriteReadEtc(string infile, string outfile1, string outfile2)
        static void ReadWriteReadEtc(const std::string &infile, const std::string &outfile1, const std::string &outfile2);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void ThermoLoadError()
        static void ThermoLoadError();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void ThermoReaderNotInstalled()
        static void ThermoReaderNotInstalled();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void LoadCompressedMzml()
        static void LoadCompressedMzml();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void LoadThermoTest2()
        static void LoadThermoTest2();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void WindowFilteringStaticTest()
        static void WindowFilteringStaticTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void MultiWindowFiltering()
        static void MultiWindowFiltering();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void LoadThermoFiltered()
        static void LoadThermoFiltered();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void LoadThermoFiltered2()
        static void LoadThermoFiltered2();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void LoadThermoTest3()
        static void LoadThermoTest3();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void ThermoSpectrumTest()
        static void ThermoSpectrumTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void ThermoDynamicTest()
        static void ThermoDynamicTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestSummedMsDataFile()
        static void TestSummedMsDataFile();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void WriteIndexedMzmlFromThermoTest()
        static void WriteIndexedMzmlFromThermoTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [OneTimeSetUp] public void Setup()
        void Setup();
    };
}
