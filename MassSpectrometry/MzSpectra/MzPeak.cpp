#include "MzPeak.h"
#include "stringhelper.h"

using namespace Spectra;

namespace MassSpectrometry {

    MzPeak::MzPeak(double mz, double intensity) : Peak::Peak(mz, intensity) {
    }

    double MzPeak::getIntensity() const {
        return getY();
    }

    double MzPeak::getMz() const {
        return getX();
    }

    std::string MzPeak::ToString() {
        return StringHelper::formatSimple("({0:G7},{1:G7})", getX(), getY());
    }
}
