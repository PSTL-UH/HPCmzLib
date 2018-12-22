#pragma once

#include "MzSpectra/MzSpectrum.h"
#include <vector>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace MassSpectrometry { class IMzPeak; }

namespace MassSpectrometry {
    class GeneratedMzSpectrum : public MzSpectrum<IMzPeak*> {
//        #region Public Constructors

    public:
        GeneratedMzSpectrum(std::vector<double> &mz, std::vector<double> &intensities, bool shouldCopy);

//        #endregion Public Constructors

//        #region Protected Methods

    protected:
        IMzPeak *GeneratePeak(int index) override;

//        #endregion Protected Methods
    };
}
