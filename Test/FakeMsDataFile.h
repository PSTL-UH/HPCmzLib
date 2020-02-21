#pragma once

#include "../MassSpectrometry/MsDataFile.h"
#include <vector>
#include "exceptionhelper.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace MassSpectrometry { class MsDataScan; }

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

using namespace MassSpectrometry;

namespace Test
{
    class FakeMsDataFile : public MsDataFile
    {
    public:
        FakeMsDataFile(std::vector<MsDataScan*> &FakeScans);

        int GetClosestOneBasedSpectrumNumber(double retentionTime) override;

        std::vector<MsDataScan*> GetMS1Scans() override;

        MsDataScan *GetOneBasedScan(int scanNumber) override;
    };
}
