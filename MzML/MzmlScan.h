#pragma once

#include "../MassSpectrometry/DataScan/MsDataScan.h"
#include "IMzmlScan.h"
#include "../MassSpectrometry/Enums/MzAnalyzerType.h"
#include "../MassSpectrometry/Enums/Polarity.h"
#include <string>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace IO { namespace MzML { class MzmlMzSpectrum; } }

using namespace MassSpectrometry;

#include "MzLibUtil.h"
using namespace MzLibUtil;

namespace IO {
    namespace MzML {
        class MzmlScan : public MsDataScan<MzmlMzSpectrum*>, public IMzmlScan {

        public:
            MzmlScan(int oneBasedScanNumber, MzmlMzSpectrum *massSpectrum, int msnOrder, bool isCentroid, MassSpectrometry::Polarity polarity, double retentionTime, MzRange *scanWindowRange, const std::string &scanFilter, MZAnalyzerType mzAnalyzer, double totalIonCurrent, Nullable<double> injectionTime, const std::string &nativeId);

        };
    }
}
