#pragma once

#include <vector>
#include <optional>
#include "tangible_filesystem.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Proteomics { class Fragment; }
namespace Chemistry { class ChemicalFormula; }

using namespace Chemistry;
using namespace IO::MzML;
using namespace MassSpectrometry;
using namespace MzIdentML;
using namespace MzLibUtil;
using namespace NUnit::Framework;
using namespace Proteomics;

namespace Test {
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [TestFixture] public sealed class TestMzML
    class TestMzML final {
//        #region Public Methods

    public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void AnotherMzMLtest()
        static void AnotherMzMLtest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void DifferentAnalyzersTest()
        static void DifferentAnalyzersTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [OneTimeSetUp] public void Setup()
        void Setup();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void LoadMzmlTest()
        void LoadMzmlTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void LoadMzmlAnotherTest()
        void LoadMzmlAnotherTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void LoadMzmlFromConvertedMGFTest()
        void LoadMzmlFromConvertedMGFTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void WriteMzmlTest()
        void WriteMzmlTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void MzidTest()
        void MzidTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void Mzid110Test()
        void Mzid110Test();

//        #endregion Public Methods

//        #region Private Methods

    private:
        MzmlMzSpectrum *CreateMS2spectrum(std::vector<Fragment*> &fragments, int v1, int v2);

        MzmlMzSpectrum *CreateSpectrum(ChemicalFormula *f, double lowerBound, double upperBound, int minCharge);

//        #endregion Private Methods
    };
}
