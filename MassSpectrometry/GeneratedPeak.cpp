#include <algorithm>
#include "GeneratedPeak.h"


namespace MassSpectrometry {

    GeneratedPeak::GeneratedPeak(double Mz, double Intensity) : MzPeak(Mz, Intensity){
        mzs.push_back(Mz);
        intensities.push_back(Intensity);
    }

    void GeneratedPeak::AddMzPeak(double anotherMz, double anotherIntensity) {
        mzs.push_back(anotherMz);
        intensities.push_back(anotherIntensity);
        //setIntensity(intensities.Sum());
        double s = 0.0;
        std::for_each(intensities.begin(), intensities.end(), [&] (double i) {
                s+= i;
            });
        setIntensity(s);
        double weightedSumMz = 0;
        for (int i = 0; i < (int) mzs.size(); i++) {
            weightedSumMz += mzs[i] * intensities[i];
        }
        setMz(weightedSumMz / getIntensity());
    }
}
