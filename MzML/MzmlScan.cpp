#include "MzmlScan.h"
#include "MzmlSpectrum.h"
#include "../MzLibUtil/MzRange.h"

using namespace MassSpectrometry;
using namespace MzLibUtil;
namespace IO {
    namespace MzML {

        MzmlScan::MzmlScan(int oneBasedScanNumber, MzmlMzSpectrum *massSpectrum, int msnOrder, bool isCentroid, MassSpectrometry::Polarity polarity, double retentionTime, MzRange *scanWindowRange, const std::wstring &scanFilter, MZAnalyzerType mzAnalyzer, double totalIonCurrent, Nullable<double> injectionTime, const std::wstring &nativeId) : MsDataScan<MzmlMzSpectrum>(massSpectrum, oneBasedScanNumber, msnOrder, isCentroid, polarity, retentionTime, scanWindowRange, scanFilter, mzAnalyzer, totalIonCurrent, injectionTime, nullptr, nativeId) {
        }
    }
}
