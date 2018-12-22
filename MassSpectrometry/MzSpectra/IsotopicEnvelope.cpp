#include "IsotopicEnvelope.h"


namespace MassSpectrometry {

    IsotopicEnvelope::IsotopicEnvelope(std::vector<(double, double)*> &bestListOfPeaks, double bestMonoisotopicMass, int bestChargeState, double bestTotalIntensity, double bestStDev, int bestMassIndex) : peaks(bestListOfPeaks), monoisotopicMass(bestMonoisotopicMass), charge(bestChargeState), totalIntensity(bestTotalIntensity), stDev(bestStDev), massIndex(bestMassIndex) {
    }

    std::wstring IsotopicEnvelope::ToString() {
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
        return std::to_wstring(charge) + L"\t" + peaks[0]->Item1->ToString(L"G8") + L"\t" + std::to_wstring(peaks.size());
    }
}
