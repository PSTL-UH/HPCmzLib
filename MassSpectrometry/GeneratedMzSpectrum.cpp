#include "GeneratedMzSpectrum.h"
#include "MzSpectra/IMzPeak.h"
#include "MzSpectra/MzPeak.h"

namespace MassSpectrometry {

    GeneratedMzSpectrum::GeneratedMzSpectrum(std::vector<double> &mz, std::vector<double> &intensities, bool shouldCopy) : MzSpectrum<IMzPeak*>(mz, intensities, shouldCopy) {
    }

    IMzPeak *GeneratedMzSpectrum::GeneratePeak(int index) {
        return new MzPeak(XArray[index], YArray[index]);
    }
}
