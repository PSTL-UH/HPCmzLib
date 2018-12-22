#pragma once

#include "../MassSpectrometry/DataScan/MsDataScan.h"
#include "IThermoScan.h"
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
        class ThermoScan : public MsDataScan<ThermoSpectrum*>, public IThermoScan {
    //        #region Public Constructors

        public:
            ThermoScan(int oneBasedScanNumber, ThermoSpectrum *massSpectrum, int msnOrder, MassSpectrometry::Polarity polarity, double retentionTime, MzRange *scanWindowRange, const std::wstring &scanFilter, MZAnalyzerType mzAnalyzer, double totalIonCurrent, Nullable<double> injectionTime, std::vector<std::vector<double>> &noiseData, const std::wstring &nativeId);

    //        #endregion Public Constructors
        };
    }
}
