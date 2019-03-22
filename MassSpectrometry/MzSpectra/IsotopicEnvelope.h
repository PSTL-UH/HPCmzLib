#pragma once

#include <string>
#include <vector>
#include <tuple>

namespace MassSpectrometry {
    class IsotopicEnvelope {

    public:
        const std::vector<std::tuple<double, double>> peaks;
        const double monoisotopicMass;
        const int charge;
        const double totalIntensity;
        const double stDev;
        const int massIndex;

        IsotopicEnvelope(std::vector<std::tuple<double, double>> &bestListOfPeaks, double bestMonoisotopicMass, int bestChargeState, double bestTotalIntensity, double bestStDev, int bestMassIndex);

        std::string ToString();

    };
}
