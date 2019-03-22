#include "IsotopicEnvelope.h"


namespace MassSpectrometry {

    IsotopicEnvelope::IsotopicEnvelope(std::vector<std::tuple<double, double>> &bestListOfPeaks, double bestMonoisotopicMass, int bestChargeState, double bestTotalIntensity, double bestStDev, int bestMassIndex) : peaks(bestListOfPeaks), monoisotopicMass(bestMonoisotopicMass), charge(bestChargeState), totalIntensity(bestTotalIntensity), stDev(bestStDev), massIndex(bestMassIndex) {
    }

    std::string IsotopicEnvelope::ToString() {
//        return std::to_string(charge) + "\t" + peaks[0]->Item1->ToString("G8") + "\t" + std::to_string(peaks.size());
        return std::to_string(charge) + "\t" + std::to_string(std::get<0>(peaks[0])) + "\t" + std::to_string(peaks.size());
    }
}
