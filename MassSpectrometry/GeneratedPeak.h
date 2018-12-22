#pragma once

#include "MzSpectra/MzPeak.h"
#include <vector>


namespace MassSpectrometry {
    class GeneratedPeak : public MzPeak {
//        #region Private Fields

    private:
        std::vector<double> mzs = std::vector<double>();
        std::vector<double> intensities = std::vector<double>();

//        #endregion Private Fields

//        #region Public Constructors

    public:
        GeneratedPeak(double Mz, double Intensity);

//        #endregion Public Constructors

//        #region Internal Methods

        void AddMzPeak(double anotherMz, double anotherIntensity);

//        #endregion Internal Methods
    };
}
