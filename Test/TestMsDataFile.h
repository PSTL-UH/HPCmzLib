#pragma once

#include <vector>
#include <iostream>
#include "stringhelper.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace MassSpectrometry { class MzSpectrum; }
namespace Test { class FakeMsDataFile; }
namespace Chemistry { class ChemicalFormula; }

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work Copyright 2016 Stefan Solntsev
//
// This file (TestDataFile.cs) is part of MassSpectrometry.Tests.
//
// MassSpectrometry.Tests is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MassSpectrometry.Tests is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with MassSpectrometry.Tests. If not, see <http://www.gnu.org/licenses/>.

using namespace Chemistry;
using namespace MassSpectrometry;
using namespace MzLibUtil;
using namespace NUnit::Framework;
using namespace Proteomics::AminoAcidPolymer;
namespace Stopwatch = System::Diagnostics::Stopwatch;

namespace Test
{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [TestFixture] public sealed class TestMsDataFile
    class TestMsDataFile final
    {
    private:
        static Stopwatch *privateStopwatch;

        MzSpectrum *_mzSpectrumA;
        FakeMsDataFile *myMsDataFile;
    public:
        virtual ~TestMsDataFile()
        {
            delete _mzSpectrumA;
            delete myMsDataFile;
        }

    private:
        static Stopwatch *getStopwatch();
        static void setStopwatch(Stopwatch *value);

    public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [OneTimeSetUp] public void Setup()
        void Setup();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [SetUp] public static void Setuppp()
        static void Setuppp();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [TearDown] public static void TearDown()
        static void TearDown();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void SpectrumCount()
        void SpectrumCount();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void SpectrumFirstMZ()
        void SpectrumFirstMZ();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void SpectrumLastMZ()
        void SpectrumLastMZ();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void DataFileTest()
        void DataFileTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void TestAMoreRealFile()
        void TestAMoreRealFile();

    private:
        MzSpectrum *CreateMS2spectrum(std::vector<Fragment*> &fragments, int v1, int v2);

        MzSpectrum *CreateSpectrum(ChemicalFormula *f, double lowerBound, double upperBound, int minCharge);
    };
}
