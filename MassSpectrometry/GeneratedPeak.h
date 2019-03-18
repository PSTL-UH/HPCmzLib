#pragma once

#include "MzSpectra/MzPeak.h"
#include <vector>


namespace MassSpectrometry {
    class GeneratedPeak : public MzPeak {

    private:
        std::vector<double> mzs = std::vector<double>();
        std::vector<double> intensities = std::vector<double>();

    public:
        GeneratedPeak(double Mz, double Intensity);

        void AddMzPeak(double anotherMz, double anotherIntensity);

    };
}
