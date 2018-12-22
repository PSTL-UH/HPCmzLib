#include "MzPeak.h"

using namespace Spectra;

namespace MassSpectrometry {

    MzPeak::MzPeak(double mz, double intensity) : Peak(mz, intensity) {
    }

    double MzPeak::getIntensity() const {
        return getY();
    }

    double MzPeak::getMz() const {
        return getX();
    }

    std::wstring MzPeak::ToString() {
        return std::wstring::Format(L"({0:G7},{1:G7})", getX(), getY());
    }
}
