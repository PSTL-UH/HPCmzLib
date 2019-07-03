#pragma once

#include <vector>
#include <cmath>
#include <limits>

#include "../MzLibUtil/MzLibUtil.h"
using namespace MzLibUtil;

//C# TO C++ CONVERTER NOTE: Forward class declarations:
//namespace MassSpectrometry { template<typename TSpectrum>class IMsDataScan; }
//namespace MassSpectrometry { class IMzPeak; }
//namespace MassSpectrometry { template<typename TPeak>class IMzSpectrum; }
//namespace MassSpectrometry { template<typename TScan>class IMsDataFile; }
#include "MzSpectra/IMzSpectrum.h"
#include "MzSpectra/IMzPeak.h"
#include "DataScan/IMsDataScan.h"
#include "MsDataFile.h"

namespace MassSpectrometry {
   class SummedMsDataFile : public MsDataFile<IMsDataScan<IMzSpectrum<IMzPeak*>*>*> {

    private:
        IMsDataFile<IMsDataScan<IMzSpectrum<IMzPeak*>*>*> *const raw;
        const int numScansToAverage;
        const double ppmToleranceForPeakCombination;

    public:
        virtual ~SummedMsDataFile() {
            delete raw;
        }

        SummedMsDataFile(IMsDataFile<IMsDataScan<IMzSpectrum<IMzPeak*>*>*> *raw, int numScansToAverage, double ppmToleranceForPeakCombination);

        IMsDataScan<IMzSpectrum<IMzPeak*>*> *GetOneBasedScan(int oneBasedScanNumber) override;

    private:
        IMzSpectrum<IMzPeak*> *CombinePeaks(std::vector<IMzSpectrum<IMzPeak*>*> &spectraToCombine, double ppmTolerance);

   };
}
