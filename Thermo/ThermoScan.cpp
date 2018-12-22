#include "ThermoScan.h"
#include "ThermoSpectrum.h"
#include "../MzLibUtil/MzRange.h"

using namespace MassSpectrometry;
using namespace MzLibUtil;
namespace IO {
    namespace Thermo {

        ThermoScan::ThermoScan(int oneBasedScanNumber, ThermoSpectrum *massSpectrum, int msnOrder, MassSpectrometry::Polarity polarity, double retentionTime, MzRange *scanWindowRange, const std::wstring &scanFilter, MZAnalyzerType mzAnalyzer, double totalIonCurrent, Nullable<double> injectionTime, std::vector<std::vector<double>> &noiseData, const std::wstring &nativeId) : MsDataScan<ThermoSpectrum>(massSpectrum, oneBasedScanNumber, msnOrder, true, polarity, retentionTime, scanWindowRange, scanFilter, mzAnalyzer, totalIonCurrent, injectionTime, noiseData, nativeId)

        {
        }
    }
}
