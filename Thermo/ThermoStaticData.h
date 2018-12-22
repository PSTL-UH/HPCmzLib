#pragma once

#include "../MassSpectrometry/IMsStaticDataFile.h"
#include "ThermoFile.h"
#include <string>
#include <vector>
#include <optional>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace IO { namespace Thermo { class IThermoScan; } }
namespace MassSpectrometry { class SourceFile; }
namespace IO { namespace Thermo { class ThermoGlobalParams; } }

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work Copyright 2016 Stefan Solntsev
//
// This file (ThermoRawFile.cs) is part of MassSpecFiles.
//
// MassSpecFiles is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MassSpecFiles is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with MassSpecFiles. If not, see <http://www.gnu.org/licenses/>.

using namespace MassSpectrometry;
using namespace MSFileReaderLib;
using namespace MzLibUtil;

namespace IO {
    namespace Thermo {
        class ThermoStaticData : public ThermoFile, public IMsStaticDataFile<IThermoScan*> {
    //        #region Private Constructors

        private:
            ThermoStaticData(std::vector<IThermoScan*> &scans, IO::Thermo::ThermoGlobalParams *p, MassSpectrometry::SourceFile *sourceFile);

    //        #endregion Private Constructors

    //        #region Public Methods

        public:
            static ThermoStaticData *LoadAllStaticData(const std::wstring &filePath, std::optional<int> &topNpeaks = std::nullopt, std::optional<double> &minRatio = std::nullopt, bool trimMs1Peaks = true, bool trimMsMsPeaks = true);

            IThermoScan *GetOneBasedScan(int oneBasedScanNumber) override;

    //        #endregion Public Methods
        };
    }
}
