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

using namespace MassSpectrometry;
using namespace MzLibUtil;
using namespace NUnit::Framework;
namespace Stopwatch = System::Diagnostics::Stopwatch;

namespace Test
{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [TestFixture] public sealed class TestChromatogram
    class TestChromatogram final
    {
    private:
        static Stopwatch *privateStopwatch;

        static Stopwatch *getStopwatch();
        static void setStopwatch(Stopwatch *value);

    public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [SetUp] public static void Setup()
        static void Setup();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [TearDown] public static void TearDown()
        static void TearDown();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void ChromatogramTest()
        void ChromatogramTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void TestGetApex()
        void TestGetApex();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void AnotherChromatogramTest()
        void AnotherChromatogramTest();
    };
}
