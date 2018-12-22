#include "ChromatographicPeak.h"

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

    std::wstring ChromatographicPeak::ToString() {
        return std::wstring::Format(L"({0:G4}, {1:G4})", getTime(), getIntensity());
    }
}
