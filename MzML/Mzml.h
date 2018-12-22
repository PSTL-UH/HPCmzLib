#pragma once

#include "../MassSpectrometry/IMsStaticDataFile.h"
#include "../MassSpectrometry/MsDataFile.h"
#include "../MassSpectrometry/Enums/Polarity.h"
#include "../MassSpectrometry/Enums/MzAnalyzerType.h"
#include "../MassSpectrometry/Enums/DissociationType.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <optional>
#include "tangible_filesystem.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace IO { namespace MzML { class IMzmlScan; } }
namespace MassSpectrometry { class SourceFile; }
namespace IO { namespace MzML { namespace Generated { class mzMLType; } } }

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

namespace IO {
    namespace MzML {
        class Mzml : public MsDataFile<IMzmlScan*>, public IMsStaticDataFile<IMzmlScan*> {
    //        #region Private Fields

        private:
            static const std::wstring _zlibCompression;
            static const std::wstring _64bit;
            static const std::wstring _32bit;
            static const std::wstring _filterString;
            static const std::wstring _centroidSpectrum;
            static const std::wstring _profileSpectrum;
            static const std::wstring _peakIntensity;
            static const std::wstring _totalIonCurrent;
            static const std::wstring _scanWindowLowerLimit;
            static const std::wstring _scanWindowUpperLimit;
            static const std::wstring _msnOrderAccession;
            static const std::wstring _precursorCharge;
            static const std::wstring _selectedIonMz;
            static const std::wstring _isolationWindowTargetMZ;
            static const std::wstring _isolationWindowLowerOffset;
            static const std::wstring _isolationWindowUpperOffset;
            static const std::wstring _retentionTime;
            static const std::wstring _ionInjectionTime;
            static const std::wstring _mzArray;
            static const std::wstring _intensityArray;
            static Regex *const MZAnalyzerTypeRegex;

            static const std::unordered_map<std::wstring, Polarity> polarityDictionary;

            static const std::unordered_map<std::wstring, MZAnalyzerType> analyzerDictionary;

            static const std::unordered_map<std::wstring, DissociationType> dissociationDictionary;

    //        #endregion Private Fields

    //        #region Private Constructors

            Mzml(std::vector<IMzmlScan*> &scans, MassSpectrometry::SourceFile *sourceFile);

    //        #endregion Private Constructors

    //        #region Public Methods

        public:
            static Mzml *LoadAllStaticData(const std::wstring &filePath, std::optional<int> &topNpeaks = std::nullopt, std::optional<double> &minRatio = std::nullopt, bool trimMs1Peaks = true, bool trimMsMsPeaks = true);

            IMzmlScan *GetOneBasedScan(int scanNumber) override;

    //        #endregion Public Methods

    //        #region Private Methods

        private:
            static IMzmlScan *GetMsDataOneBasedScanFromConnection(Generated::mzMLType *_mzMLConnection, int oneBasedSpectrumNumber, std::optional<int> &topNpeaks, std::optional<double> &minRatio, bool trimMs1Peaks, bool trimMsMsPeaks);

            /// <summary>
            /// Converts a 64-based encoded byte array into an double[]
            /// </summary>
            /// <param name="bytes">the 64-bit encoded byte array</param>
            /// <param name="zlibCompressed">Specifies if the byte array is zlib compressed</param>
            /// <returns>a decompressed, de-encoded double[]</returns>
            static std::vector<double> ConvertBase64ToDoubles(std::vector<unsigned char> &bytes, bool zlibCompressed = false, bool is32bit = true);

            static int GetOneBasedPrecursorScanNumber(Generated::mzMLType *_mzMLConnection, int oneBasedSpectrumNumber);

    //        #endregion Private Methods
        };
    }
}
