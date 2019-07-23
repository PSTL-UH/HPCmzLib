#pragma once

#include "../Chemistry/Interfaces/IHasMass.h"
#include <string>
#include <iostream>
#include "stringhelper.h"

// Copyright 2012, 2013, 2014 Derek J. Bailey
//
// This file (MassTestFixture.cs) is part of CSMSL.Tests.
//
// CSMSL.Tests is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// CSMSL.Tests is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with CSMSL.Tests. If not, see <http://www.gnu.org/licenses/>.

using namespace Chemistry;
using namespace NUnit::Framework;
namespace Stopwatch = System::Diagnostics::Stopwatch;

namespace Test
{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [TestFixture] public static class TestMassMzCalculations
    class TestMassMzCalculations final
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
//ORIGINAL LINE: [Test] public static void MassToMzToMass()
        static void MassToMzToMass();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void MassToMzPositiveCharge()
        static void MassToMzPositiveCharge();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void MassToMzPositiveCharge_plus3()
        static void MassToMzPositiveCharge_plus3();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void MassToMzNegativeCharge()
        static void MassToMzNegativeCharge();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void MzToMassPostitiveCharge()
        static void MzToMassPostitiveCharge();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void MzToMassNegativeCharge()
        static void MzToMassNegativeCharge();
    };

    class ObjectWithMass1000 : public IHasMass
    {
    public:
        double getMonoisotopicMass() const override;
    };

    class ObjectWithMass100 : public IHasMass
    {
    public:
        double getMonoisotopicMass() const override;

        std::string ToString() override;
    };
}
