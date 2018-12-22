#pragma once

#include "IMzPeak.h"
#include "../../Spectra/Peak.h"
#include <string>

using namespace Spectra;

namespace MassSpectrometry {
    class MzPeak : public Peak, public IMzPeak {
//        #region Public Constructors

    public:
        MzPeak(double mz, double intensity);

//        #endregion Public Constructors

//        #region Public Properties

        double getIntensity() const override;

        double getMz() const override;

//        #endregion Public Properties

//        #region Public Methods

        std::wstring ToString() override;

//        #endregion Public Methods
    };
}
