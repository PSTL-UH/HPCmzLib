#pragma once

#include "../../Spectra/IPeak.h"

using namespace Spectra;

namespace MassSpectrometry {
    class IMzPeak :  public virtual IPeak {

    public:
        virtual double getIntensity() const = 0;
        virtual double getMz() const = 0;

    };
}
