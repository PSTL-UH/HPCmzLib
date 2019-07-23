#pragma once

#include <vector>
#include <iostream>
#include <cmath>
#include <optional>
#include "stringhelper.h"
#include "tangible_filesystem.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace MassSpectrometry { class MzSpectrum; }
namespace Chemistry { class ChemicalFormula; }

using namespace Chemistry;
using namespace IO::MzML;
using namespace MassSpectrometry;
using namespace MzIdentML;
using namespace MzLibUtil;
using namespace NUnit::Framework;
using namespace Proteomics::AminoAcidPolymer;
namespace Stopwatch = System::Diagnostics::Stopwatch;

namespace Test
{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [TestFixture] public sealed class TestMzML
    class TestMzML final
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
//ORIGINAL LINE: [Test] public static void AnotherMzMLtest()
        static void AnotherMzMLtest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void LoadBadMzml()
        void LoadBadMzml();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestPeakTrimmingWithOneWindow()
        static void TestPeakTrimmingWithOneWindow();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestPeakTrimmingWithTooManyWindows()
        static void TestPeakTrimmingWithTooManyWindows();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void WriteEmptyScan()
        static void WriteEmptyScan();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void DifferentAnalyzersTest()
        static void DifferentAnalyzersTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void Mzid111Test()
        static void Mzid111Test();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void Mzid120Test()
        static void Mzid120Test();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [OneTimeSetUp] public void Setup()
        void Setup();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void LoadMzmlTest()
        void LoadMzmlTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void LoadMzmlFromConvertedMGFTest()
        void LoadMzmlFromConvertedMGFTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void WriteMzmlTest()
        void WriteMzmlTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void MzidTest()
        void MzidTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void Mzid110Test()
        void Mzid110Test();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void Mzid111Test_()
        void Mzid111Test_();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void Mzid120Test_()
        void Mzid120Test_();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void MzmlFindPrecursorReferenceScan()
        void MzmlFindPrecursorReferenceScan();

    private:
        MzSpectrum *CreateMS2spectrum(std::vector<Fragment*> &fragments, int v1, int v2);

        MzSpectrum *CreateSpectrum(ChemicalFormula *f, double lowerBound, double upperBound, int minCharge);
    };
}
