#pragma once

#include "../Chemistry/Interfaces/IHasMass.h"
#include <string>

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

namespace Test {
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [TestFixture] public class MassTestFixture
    class MassTestFixture {
//        #region Public Methods

    public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void MassToMzToMass()
        void MassToMzToMass();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void MassToMzPositiveCharge()
        void MassToMzPositiveCharge();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void MassToMzNegativeCharge()
        void MassToMzNegativeCharge();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void MzToMassPostitiveCharge()
        void MzToMassPostitiveCharge();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void MzToMassNegativeCharge()
        void MzToMassNegativeCharge();

//        #endregion Public Methods
    };

    class ObjectWithMass1000 : public IHasMass {
//        #region Public Properties

    public:
        double getMonoisotopicMass() const override;

//        #endregion Public Properties
    };

    class ObjectWithMass100 : public IHasMass {
//        #region Public Properties

    public:
        double getMonoisotopicMass() const override;

//        #endregion Public Properties

//        #region Public Methods

        std::wstring ToString() override;

//        #endregion Public Methods
    };
}
