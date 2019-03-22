#pragma once

#include "IMzPeak.h"
#include "../../Spectra/Peak.h"
#include <string>

using namespace Spectra;

namespace MassSpectrometry {
    class MzPeak : public virtual Peak, public virtual IMzPeak {

    public:
        MzPeak(double mz, double intensity);

        double getIntensity() const override;

        double getMz() const override;
        std::string ToString();
    };
}
