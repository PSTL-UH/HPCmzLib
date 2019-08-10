#pragma once

#define _USE_MATH_DEFINES
#include <vector>
#include <iostream>
#include <cmath>
#include <limits>
#include "stringhelper.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
//namespace MassSpectrometry { class MzSpectrum; }
#include "../MassSpectrometry/MzSpectra/MzSpectrum.h"

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


#include "../MassSpectrometry/MassSpectrometry.h"
using namespace MassSpectrometry;

#include "MzLibUtil.h"
using namespace MzLibUtil;

namespace Test
{
    class TestSpectra final
    {
    public:
        static void Setup();

        static void SpectrumCount();

        static void SpectrumFirstMZ();

        static void SpectrumLastMZ();

        static void SpectrumBasePeakIntensity();

        static void SpectrumTIC();

        static void SpectrumGetIntensityFirst();

        static void SpectrumGetIntensityRandom();

        static void SpectrumGetMassFirst();

        static void SpectrumGetMassRandom();

        static void SpectrumContainsPeak();

        static void SpectrumContainsPeakInRange();

        static void SpectrumContainsPeakInRangeEnd();

        static void SpectrumContainsPeakInRangeStart();

        static void SpectrumContainsPeakInRangeStartEnd();

        static void SpectrumDoesntContainPeakInRange();

        static void SpectrumMassRange();

        static void SpectrumFilterCount();

        static void FilterByNumberOfMostIntenseTest();

        static void FilterByNumberOfMostIntenseRobTest();

        static void GetBasePeak();

        static void GetClosestPeak();

        static void Extract();

        static void CorrectOrder();

        static void TestFunctionToX();

        static void TestGetClosestPeakXValue();

        static void TestDotProduct();

        static void TestNumPeaksWithinRange();
    };
}
