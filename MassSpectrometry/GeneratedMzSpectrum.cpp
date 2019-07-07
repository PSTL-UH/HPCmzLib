#include "GeneratedMzSpectrum.h"
#include "MzSpectra/MzPeak.h"

namespace MassSpectrometry {

    GeneratedMzSpectrum::GeneratedMzSpectrum(std::vector<double> &mz, std::vector<double> &intensities, bool shouldCopy) : MzSpectrum (mz, intensities, shouldCopy) {
    }

    IMzPeak *GeneratedMzSpectrum::GeneratePeak(int index) {
        return new MzPeak(getXArray()[index], getYArray()[index]);
    }
}
