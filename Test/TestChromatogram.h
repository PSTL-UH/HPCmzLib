#pragma once

#include <vector>
#include <iostream>
#include "stringhelper.h"

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work Copyright 2016 Stefan Solntsev
//
// This file (TestChromatogram.cs) is part of MassSpectrometry.Tests.
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
    class TestChromatogram final
    {
    public:
        static void ChromatogramTest();

        static void TestGetApex();

        static void AnotherChromatogramTest();
    };
}
