#pragma once

#include "../MassSpectrometry/DataScan/MsDataScan.h"
#include "IMzmlScan.h"
#include "../MassSpectrometry/Enums/MzAnalyzerType.h"
#include "../MassSpectrometry/Enums/Polarity.h"
#include <string>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace IO { namespace MzML { class MzmlMzSpectrum; } }
namespace MzLibUtil { class MzRange; }

using namespace MassSpectrometry;
using namespace MzLibUtil;

namespace IO {
    namespace MzML {
        class MzmlScan : public MsDataScan<MzmlMzSpectrum*>, public IMzmlScan {
    //        #region Public Constructors

        public:
            MzmlScan(int oneBasedScanNumber, MzmlMzSpectrum *massSpectrum, int msnOrder, bool isCentroid, MassSpectrometry::Polarity polarity, double retentionTime, MzRange *scanWindowRange, const std::wstring &scanFilter, MZAnalyzerType mzAnalyzer, double totalIonCurrent, Nullable<double> injectionTime, const std::wstring &nativeId);

    //        #endregion Public Constructors
        };
    }
}
