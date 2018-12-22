#include "ThermoScanWithPrecursor.h"
#include "ThermoSpectrum.h"
#include "../MzLibUtil/MzRange.h"

using namespace MassSpectrometry;
using namespace MzLibUtil;
namespace IO {
    namespace Thermo {

        ThermoScanWithPrecursor::ThermoScanWithPrecursor(int ScanNumber, ThermoSpectrum *massSpectrum, int MsnOrder, MassSpectrometry::Polarity Polarity, double RetentionTime, MzRange *MzRange, const std::wstring &ScanFilter, MZAnalyzerType MzAnalyzer, double TotalIonCurrent, double selectedIonGuessMZ, Nullable<int> selectedIonGuessChargeStateGuess, Nullable<double> isolationWidth, MassSpectrometry::DissociationType dissociationType, Nullable<int> oneBasedPrecursorScanNumber, Nullable<double> selectedIonGuessMonoisotopicMZ, Nullable<double> injectionTime, std::vector<std::vector<double>> &noiseData, const std::wstring &nativeId) : MsDataScanWithPrecursor<ThermoSpectrum>(massSpectrum, ScanNumber, MsnOrder, true, Polarity, RetentionTime, MzRange, ScanFilter, MzAnalyzer, TotalIonCurrent, selectedIonGuessMZ, selectedIonGuessChargeStateGuess, nullptr, selectedIonGuessMZ, isolationWidth, dissociationType, oneBasedPrecursorScanNumber, selectedIonGuessMonoisotopicMZ, injectionTime, noiseData, nativeId) {
        }
    }
}
