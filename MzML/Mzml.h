#pragma once

#include "../MassSpectrometry/MsDataFile.h"
#include "../MassSpectrometry/Enums/Polarity.h"
#include "../MassSpectrometry/Enums/MzAnalyzerType.h"
#include "../MassSpectrometry/Enums/DissociationType.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cmath>
#include <optional>
#include "exceptionhelper.h"
#include "tangible_filesystem.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
#include "../MassSpectrometry/MsDataScan.h"
// namespace MassSpectrometry { class MsDataScan; }
#include "../MassSpectrometry/SourceFile.h"
// namespace MassSpectrometry { class SourceFile; }
#include "../MassSpectrometry/FilteringParams.h"
// namespace MassSpectrometry { class FilteringParams; }
#include "../MassSpectrometry/IFilteringParams.h"
// namespace MassSpectrometry { class IFilteringParams; }
#include "XSD/IO.MzML.Generated.mzMLType.h"
// namespace IO { namespace MzML { namespace Generated { class mzMLType; } } }

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work Copyright 2016, 2017 Stefan Solntsev
//
// This file (Mzml.cs) is part of MassSpecFiles.
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
using namespace MzLibUtil;

namespace IO
{
    namespace MzML
    {
        class Mzml : public MsDataFile
        {
        private:
            static const std::string _zlibCompression;
            static const std::string _64bit;
            static const std::string _32bit;
            static const std::string _filterString;
            static const std::string _centroidSpectrum;
            static const std::string _profileSpectrum;
            static const std::string _peakIntensity;
            static const std::string _totalIonCurrent;
            static const std::string _scanWindowLowerLimit;
            static const std::string _scanWindowUpperLimit;
            static const std::string _msnOrderAccession;
            static const std::string _precursorCharge;
            static const std::string _selectedIonMz;
            static const std::string _isolationWindowTargetMZ;
            static const std::string _isolationWindowLowerOffset;
            static const std::string _isolationWindowUpperOffset;
            static const std::string _oneBasedScanNumber;
            static const std::string _retentionTime;
            static const std::string _ionInjectionTime;
            static const std::string _mzArray;
            static const std::string _intensityArray;
            // static Regex *const MZAnalyzerTypeRegex;

            static std::unordered_map<std::string, Polarity> polarityDictionary;

            static std::unordered_map<std::string, MZAnalyzerType> analyzerDictionary;

            static std::unordered_map<std::string, DissociationType> dissociationDictionary;

            Mzml(std::vector<MsDataScan*> &scans, MassSpectrometry::SourceFile *sourceFile);

        public:
            static Mzml *LoadAllStaticData(const std::string &filePath, FilteringParams *filterParams = nullptr, int maxThreads = -1);

        private:
            static MsDataScan *GetMsDataOneBasedScanFromConnection(Generated::mzMLType *_mzMLConnection, int oneBasedIndex, IFilteringParams *filterParams);

            /// <summary>
            /// Converts a 64-based encoded byte array into an double[]
            /// </summary>
            /// <param name="bytes">the 64-bit encoded byte array</param>
            /// <param name="zlibCompressed">Specifies if the byte array is zlib compressed</param>
            /// <returns>a decompressed, de-encoded double[]</returns>
            static std::vector<double> ConvertBase64ToDoubles(std::vector<unsigned char> &bytes, bool zlibCompressed = false, bool is32bit = true);

            static int GetOneBasedPrecursorScanNumber(Generated::mzMLType *_mzMLConnection, int oneBasedSpectrumNumber);
        };
    }
}
