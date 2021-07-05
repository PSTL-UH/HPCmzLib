#pragma once

#include <vector>
#include <iostream>
#include <optional>
#include "stringhelper.h"

// Copyright 2017 Stefan Solntsev
//
// This file (TestIsolation.cs) is part of Tests.
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
// License along with Tests. If not, see <http://www.gnu.org/licenses/>.

#include "../Chemistry/Chemistry.h"
using namespace Chemistry;

#include "../MassSpectrometry/MassSpectrometry.h"
using namespace MassSpectrometry;

#include "../MzLibUtil/MzLibUtil.h"
using namespace MzLibUtil;

#include "../Proteomics/AminoAcidPolymer/AminoAcidPolymer.h"
using namespace Proteomics::AminoAcidPolymer;

namespace Test
{
    class TestIsolation final
    {
    public:
        static void TestDistribution402();
        static void TestDistribution1499();
        static void TestDistribution3();
        
        static void TestCoIsolation();

        static void TestCoIsolationDifferentCharges();
    };
}
