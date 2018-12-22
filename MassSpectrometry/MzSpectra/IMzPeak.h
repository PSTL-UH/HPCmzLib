#pragma once

#include "../../Spectra/IPeak.h"

using namespace Spectra;

namespace MassSpectrometry {
    class IMzPeak : public IPeak {
//        #region Public Properties

    public:
        virtual double getIntensity() const = 0;

        virtual double getMz() const = 0;

//        #endregion Public Properties
    };
}
