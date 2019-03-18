#pragma once

#include "MzSpectra/MzSpectrum.h"
#include <vector>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace MassSpectrometry { class IMzPeak; }

namespace MassSpectrometry {
    class GeneratedMzSpectrum : public MzSpectrum<IMzPeak*> {

    public:
        GeneratedMzSpectrum(std::vector<double> &mz, std::vector<double> &intensities, bool shouldCopy);

    protected:
        IMzPeak *GeneratePeak(int index) override;

    };
}
