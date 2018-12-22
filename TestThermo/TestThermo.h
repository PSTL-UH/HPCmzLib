#pragma once

#include <vector>
#include <cmath>
#include <limits>
#include <optional>
#include "tangible_filesystem.h"

using namespace Chemistry;
using namespace IO::MzML;
using namespace IO::Thermo;
using namespace MassSpectrometry;
using namespace MzLibUtil;
using namespace NUnit::Framework;

namespace TestThermo {
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [TestFixture] public sealed class TestThermo
    class TestThermo final {
//        #region Public Methods

    public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void ReadWriteReadEtc()
        static void ReadWriteReadEtc();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void ThermoLoadError()
        static void ThermoLoadError();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void LoadCompressedMzml()
        static void LoadCompressedMzml();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void LoadThermoTest2()
        static void LoadThermoTest2();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void LoadThermoFiltered()
        static void LoadThermoFiltered();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void LoadThermoFiltered2()
        static void LoadThermoFiltered2();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void LoadThermoTest3()
        static void LoadThermoTest3();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void ThermoSpectrumTest()
        static void ThermoSpectrumTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void ThermoDynamicTest()
        static void ThermoDynamicTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void TestSummedMsDataFile()
        static void TestSummedMsDataFile();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void WriteIndexedMzmlFromThermoTest()
        static void WriteIndexedMzmlFromThermoTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [OneTimeSetUp] public void Setup()
        void Setup();

//        #endregion Public Methods
    };
}
