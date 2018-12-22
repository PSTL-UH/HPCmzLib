#include "GeneratedPeak.h"


namespace MassSpectrometry {

    GeneratedPeak::GeneratedPeak(double Mz, double Intensity) : MzPeak(Mz, Intensity) {
        mzs.push_back(Mz);
        intensities.push_back(Intensity);
    }

    void GeneratedPeak::AddMzPeak(double anotherMz, double anotherIntensity) {
        mzs.push_back(anotherMz);
        intensities.push_back(anotherIntensity);
        setY(intensities.Sum());
        double weightedSumMz = 0;
        for (int i = 0; i < mzs.size(); i++) {
            weightedSumMz += mzs[i] * intensities[i];
        }
        setX(weightedSumMz / getY());
    }
}
