#pragma once

#include "../MassSpectrometry/IMsStaticDataFile.h"
#include "../MassSpectrometry/MsDataFile.h"
#include <vector>

// Copyright 2016 Stefan Solntsev
//
// This file (FakeMsDataFile.cs) is part of MassSpectrometry.
//
// MassSpectrometry is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MassSpectrometry is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with MassSpectrometry. If not, see <http://www.gnu.org/licenses/>.

using namespace IO::MzML;
using namespace MassSpectrometry;

namespace Test {
    class FakeMsDataFile : public MsDataFile<IMzmlScan*>, public IMsStaticDataFile<IMzmlScan*> {
//        #region Public Constructors

    public:
        FakeMsDataFile(std::vector<IMzmlScan*> &FakeScans);

//        #endregion Public Constructors

//        #region Public Methods

        int GetClosestOneBasedSpectrumNumber(double retentionTime) override;

        IMzmlScan *GetOneBasedScan(int scanNumber) override;

//        #endregion Public Methods
    };
}
