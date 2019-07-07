#pragma once

#include <vector>
#include <cmath>
#include <limits>

#include "../MzLibUtil/MzLibUtil.h"
using namespace MzLibUtil;

//C# TO C++ CONVERTER NOTE: Forward class declarations:
//namespace MassSpectrometry { class MsDataFile; }
//namespace MassSpectrometry { class MsDataScan; }
//namespace MassSpectrometry { class MzSpectrum; }
#include "MsDataFile.h"
#include "MsDataScan.h"
#include "MzSpectra/MzSpectrum.h"

namespace MassSpectrometry {
   class SummedMsDataFile : public MsDataFile {

    private:
        MsDataFile *const raw;
        const int numScansToAverage;
        const double ppmToleranceForPeakCombination;

    public:
        virtual ~SummedMsDataFile() {
            delete raw;
        }

        SummedMsDataFile(MsDataFile *raw, int numScansToAverage, double ppmToleranceForPeakCombination);
        std::vector<MsDataScan*> GetAllScansList() override;
        MsDataScan *GetOneBasedScan(int oneBasedScanNumber) override;

    private:
        static MzSpectrum *CombinePeaks(std::vector<MzSpectrum*> &spectraToCombine, double ppmTolerance);

   };
}
