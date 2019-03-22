#include "ChromatographicPeak.h"
#include "stringhelper.h"

using namespace Spectra;

namespace MassSpectrometry {

    ChromatographicPeak::ChromatographicPeak(double time, double intensity) : Peak(time, intensity) {
    }

    double ChromatographicPeak::getIntensity() const {
        return getY();
    }

    double ChromatographicPeak::getTime() const {
        return getX();
    }

    std::string ChromatographicPeak::ToString() {
        return StringHelper::formatSimple("({0:G4}, {1:G4})", getTime(), getIntensity());
    }
}
