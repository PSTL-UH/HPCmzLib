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

namespace Test
{
    class TestMassMzCalculations final
    {

    public:

        static void MassToMzToMass();

        static void MassToMzPositiveCharge();

        static void MassToMzPositiveCharge_plus3();

        static void MassToMzNegativeCharge();

        static void MzToMassPostitiveCharge();

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

        std::string ToString();
    };
}
