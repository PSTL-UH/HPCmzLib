#pragma once

#include "MsDataFile.h"
#include <vector>
#include <cmath>
#include <limits>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace MassSpectrometry { template<typename TSpectrum>class IMsDataScan; }
namespace MassSpectrometry { class IMzPeak; }
namespace MassSpectrometry { template<typename TPeak>class IMzSpectrum; }
namespace MassSpectrometry { template<typename TScan>class IMsDataFile; }

using namespace MzLibUtil;

namespace MassSpectrometry {
    class SummedMsDataFile : public MsDataFile<IMsDataScan<IMzSpectrum<IMzPeak*>*>*> {
//        #region Private Fields

    private:
        IMsDataFile<IMsDataScan<IMzSpectrum<IMzPeak*>*>*> *const raw;
        const int numScansToAverage;
        const double ppmToleranceForPeakCombination;

//        #endregion Private Fields

//        #region Public Constructors

    public:
        virtual ~SummedMsDataFile() {
            delete raw;
        }

        SummedMsDataFile(IMsDataFile<IMsDataScan<IMzSpectrum<IMzPeak*>*>*> *raw, int numScansToAverage, double ppmToleranceForPeakCombination);

//        #endregion Public Constructors

//        #region Public Methods

        IMsDataScan<IMzSpectrum<IMzPeak*>*> *GetOneBasedScan(int oneBasedScanNumber) override;

//        #endregion Public Methods

//        #region Private Methods

    private:
        IMzSpectrum<IMzPeak*> *CombinePeaks(std::vector<IMzSpectrum<IMzPeak*>*> &spectraToCombine, double ppmTolerance);

//        #endregion Private Methods
    };
}
