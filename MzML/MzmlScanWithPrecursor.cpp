#include "MzmlScanWithPrecursor.h"
#include "MzmlSpectrum.h"
#include "../MzLibUtil/MzRange.h"

using namespace MassSpectrometry;
using namespace MzLibUtil;
namespace IO {
    namespace MzML {

        MzmlScanWithPrecursor::MzmlScanWithPrecursor(int ScanNumber, MzmlMzSpectrum *massSpectrum, int MsnOrder, bool isCentroid, MassSpectrometry::Polarity Polarity, double RetentionTime, MzRange *MzRange, const std::string &ScanFilter, MZAnalyzerType MzAnalyzer, double TotalIonCurrent, double selectedIonMz, Nullable<int> selectedIonChargeStateGuess, Nullable<double> selectedIonIntensity, Nullable<double> isolationMZ, Nullable<double> isolationWidth, MassSpectrometry::DissociationType dissociationType, Nullable<int> oneBasedPrecursorScanNumber, Nullable<double> selectedIonGuessMonoisotopicMZ, Nullable<double> injectionTime, const std::string &nativeId) : MsDataScanWithPrecursor<MzmlMzSpectrum>(massSpectrum, ScanNumber, MsnOrder, isCentroid, Polarity, RetentionTime, MzRange, ScanFilter, MzAnalyzer, TotalIonCurrent, selectedIonMz, selectedIonChargeStateGuess, selectedIonIntensity, isolationMZ, isolationWidth, dissociationType, oneBasedPrecursorScanNumber, selectedIonGuessMonoisotopicMZ, injectionTime, nullptr, nativeId) {
        }
    }
}
