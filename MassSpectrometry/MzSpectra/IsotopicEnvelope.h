#pragma once

#include <string>
#include <vector>


namespace MassSpectrometry {
    class IsotopicEnvelope {
//        #region Public Fields

    public:
        const std::vector<(double, double)*> peaks;
        const double monoisotopicMass;
        const int charge;
        const double totalIntensity;
        const double stDev;
        const int massIndex;

//        #endregion Public Fields

//        #region Public Constructors

        IsotopicEnvelope(std::vector<(double, double)*> &bestListOfPeaks, double bestMonoisotopicMass, int bestChargeState, double bestTotalIntensity, double bestStDev, int bestMassIndex);

//        #endregion Public Constructors

//        #region Public Methods

        std::wstring ToString() override;

//        #endregion Public Methods
    };
}
