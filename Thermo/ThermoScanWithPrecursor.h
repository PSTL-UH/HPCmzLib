#pragma once

#include "../MassSpectrometry/DataScan/MsDataScanWithPrecursor.h"
#include "IThermoScan.h"
#include "../MassSpectrometry/Enums/DissociationType.h"
#include "../MassSpectrometry/Enums/MzAnalyzerType.h"
#include "../MassSpectrometry/Enums/Polarity.h"
#include <string>
#include <vector>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace IO { namespace Thermo { class ThermoSpectrum; } }
namespace MzLibUtil { class MzRange; }

using namespace MassSpectrometry;
using namespace MzLibUtil;

namespace IO {
    namespace Thermo {
        class ThermoScanWithPrecursor : public MsDataScanWithPrecursor<ThermoSpectrum*>, public IThermoScan {
    //        #region Public Constructors

        public:
            ThermoScanWithPrecursor(int ScanNumber, ThermoSpectrum *massSpectrum, int MsnOrder, MassSpectrometry::Polarity Polarity, double RetentionTime, MzRange *MzRange, const std::wstring &ScanFilter, MZAnalyzerType MzAnalyzer, double TotalIonCurrent, double selectedIonGuessMZ, Nullable<int> selectedIonGuessChargeStateGuess, Nullable<double> isolationWidth, MassSpectrometry::DissociationType dissociationType, Nullable<int> oneBasedPrecursorScanNumber, Nullable<double> selectedIonGuessMonoisotopicMZ, Nullable<double> injectionTime, std::vector<std::vector<double>> &noiseData, const std::wstring &nativeId);

    //        #endregion Public Constructors
        };
    }
}
