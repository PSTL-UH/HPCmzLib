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

#include "../Chemistry/Chemistry.h"
using namespace Chemistry;
#include "../MzML/Mzml.h"
#include "../MzML/MzmlMethods.h"
using namespace IO::MzML;
#include "../Chemistry/Chemistry.h"
using namespace MassSpectrometry;
#include "../MassSpectrometry/MassSpectrometry.h"


//using namespace MzIdentML;


#include "../MzLibUtil/MzLibUtil.h"
using namespace MzLibUtil;

// using namespace NUnit::Framework;
#include "../Proteomics/AminoAcidPolymer/AminoAcidPolymer.h"
using namespace Proteomics::AminoAcidPolymer;

// namespace Stopwatch = System::Diagnostics::Stopwatch;

namespace Test
{
    class TestMzML final
    {
    public:
        static void AnotherMzMLtest();

#ifdef THROWS_EXCEPTION
        static void LoadBadMzml();
#endif

        static void TestPeakTrimmingWithOneWindow();

        static void TestPeakTrimmingWithTooManyWindows();

        static void WriteEmptyScan();

        static void DifferentAnalyzersTest();

        static void Mzid111Test();

        static void Mzid120Test();

        static void LoadMzmlTest();

        static void LoadMzmlFromConvertedMGFTest();

        static void WriteMzmlTest();

        static void MzidTest();

        static void Mzid110Test();

        static void Mzid111Test_();

        static void Mzid120Test_();

        static void MzmlFindPrecursorReferenceScan();

    private:
        //issues with not instantiating object
        // MzSpectrum *CreateMS2spectrum(std::vector<Fragment*> &fragments, int v1, int v2);
        static MzSpectrum *CreateMS2spectrum(std::vector<Fragment*> &fragments, int v1, int v2);

        //MzSpectrum *CreateSpectrum(ChemicalFormula *f, double lowerBound, double upperBound, int minCharge);
        static MzSpectrum *CreateSpectrum(ChemicalFormula *f, double lowerBound, double upperBound, int minCharge);
    };
}
