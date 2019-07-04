#pragma once

#include "../MassSpectrometry/DataScan/MsDataScanWithPrecursor.h"
#include "IMzmlScan.h"
#include "../MassSpectrometry/Enums/DissociationType.h"
#include "../MassSpectrometry/Enums/MzAnalyzerType.h"
#include "../MassSpectrometry/Enums/Polarity.h"
#include <string>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace IO { namespace MzML { class MzmlMzSpectrum; } }
namespace MzLibUtil { class MzRange; }

using namespace MassSpectrometry;
#include "MzLibUtil.h"
using namespace MzLibUtil;

namespace IO {
    namespace MzML {
        class MzmlScanWithPrecursor : public MsDataScanWithPrecursor<MzmlMzSpectrum*>, public IMzmlScan {

        public:
            MzmlScanWithPrecursor(int ScanNumber, MzmlMzSpectrum *massSpectrum, int MsnOrder, bool isCentroid, MassSpectrometry::Polarity Polarity, double RetentionTime, MzRange *MzRange, const std::string &ScanFilter, MZAnalyzerType MzAnalyzer, double TotalIonCurrent, double selectedIonMz, Nullable<int> selectedIonChargeStateGuess, Nullable<double> selectedIonIntensity, Nullable<double> isolationMZ, Nullable<double> isolationWidth, MassSpectrometry::DissociationType dissociationType, Nullable<int> oneBasedPrecursorScanNumber, Nullable<double> selectedIonGuessMonoisotopicMZ, Nullable<double> injectionTime, const std::string &nativeId);

        };
    }
}
