#pragma once

#include <vector>
#include <limits>
#include <stdexcept>

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work Copyright 2016 Stefan Solntsev
//
// This file (TestSpectra.cs) is part of MassSpectrometry.Tests.
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

using namespace IO::MzML;
using namespace MzLibUtil;
using namespace NUnit::Framework;

namespace Test {
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [TestFixture] public sealed class SpectrumTestFixture
    class SpectrumTestFixture final {
//        #region Private Fields

    private:
        MzmlMzSpectrum *_mzSpectrumA;

//        #endregion Private Fields

//        #region Public Methods

    public:
        virtual ~SpectrumTestFixture() {
            delete _mzSpectrumA;
        }

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [SetUp] public void Setup()
        void Setup();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void SpectrumCount()
        void SpectrumCount();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void SpectrumFirstMZ()
        void SpectrumFirstMZ();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void SpectrumLastMZ()
        void SpectrumLastMZ();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void SpectrumBasePeakIntensity()
        void SpectrumBasePeakIntensity();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void SpectrumTIC()
        void SpectrumTIC();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void SpectrumGetIntensityFirst()
        void SpectrumGetIntensityFirst();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void SpectrumGetIntensityRandom()
        void SpectrumGetIntensityRandom();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void SpectrumGetMassFirst()
        void SpectrumGetMassFirst();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void SpectrumGetMassRandom()
        void SpectrumGetMassRandom();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void SpectrumContainsPeak()
        void SpectrumContainsPeak();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void SpectrumContainsPeakInRange()
        void SpectrumContainsPeakInRange();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void SpectrumContainsPeakInRangeEnd()
        void SpectrumContainsPeakInRangeEnd();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void SpectrumContainsPeakInRangeStart()
        void SpectrumContainsPeakInRangeStart();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void SpectrumContainsPeakInRangeStartEnd()
        void SpectrumContainsPeakInRangeStartEnd();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void SpectrumDoesntContainPeakInRange()
        void SpectrumDoesntContainPeakInRange();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void SpectrumMassRange()
        void SpectrumMassRange();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void SpectrumFilterCount()
        void SpectrumFilterCount();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void FilterByNumberOfMostIntenseTest()
        void FilterByNumberOfMostIntenseTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void FilterByNumberOfMostIntenseRobTest()
        void FilterByNumberOfMostIntenseRobTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void GetBasePeak()
        void GetBasePeak();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void GetClosestPeak()
        void GetClosestPeak();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void Extract()
        void Extract();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void CorrectOrder()
        void CorrectOrder();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void TestFunctionToX()
        void TestFunctionToX();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void TestGetClosestPeakXValue()
        void TestGetClosestPeakXValue();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void TestNumPeaksWithinRange()
        void TestNumPeaksWithinRange();

//        #endregion Public Methods
    };
}
