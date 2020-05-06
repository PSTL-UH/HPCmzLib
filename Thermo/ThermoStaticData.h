#pragma once

#include "ThermoDataFile.h"
#include <string>
#include <vector>
#include <any>
#include <typeinfo>
#include <optional>
#include "exceptionhelper.h"
#include "stringhelper.h"
#include "tangible_filesystem.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace MassSpectrometry { class MsDataScan; }
namespace MassSpectrometry { class SourceFile; }
namespace IO { namespace Thermo { class ThermoGlobalParams; } }
namespace MassSpectrometry { class IFilteringParams; }

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

namespace IO
{
    namespace Thermo
    {
        class ThermoStaticData : public ThermoDataFile
        {
        private:
            static Regex *const PolarityRegex;
            static Regex *const mFindParentIonOnlyNonMsx;
            static Regex *const mFindParentIonOnlyMsx;

            ThermoStaticData(std::vector<MsDataScan*> &scans, IO::Thermo::ThermoGlobalParams *thermoGlobalParams, MassSpectrometry::SourceFile *sourceFile);

        private:
            enum class ThermoMzAnalyzer
            {
                None = -1,
                ITMS = 0,
                TQMS = 1,
                SQMS = 2,
                TOFMS = 3,
                FTMS = 4,
                Sector = 5
            };

        public:
            static ThermoStaticData *LoadAllStaticData(const std::string &filePath, IFilteringParams *filterParams = nullptr);

            static MsDataScan *GetMsDataOneBasedScanFromThermoFile(IXRawfile5 *theConnection, int nScanNumber, IO::Thermo::ThermoGlobalParams *globalParams, IFilteringParams *filterParams = nullptr);

            static IO::Thermo::ThermoGlobalParams *GetAllGlobalStuff(IXRawfile5 *_rawConnection, std::vector<ManagedThermoHelperLayer::PrecursorInfo*> &couldBePrecursor, const std::string &filePath);

            static bool CheckForMsFileReader();
        };
    }
}
