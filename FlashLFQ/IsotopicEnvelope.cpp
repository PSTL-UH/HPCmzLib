#include "IsotopicEnvelope.h"
#include "IndexedMassSpectralPeak.h"

namespace FlashLFQ
{

    IsotopicEnvelope::IsotopicEnvelope(IndexedMassSpectralPeak *monoisotopicPeak, int chargeState, double intensity) : IndexedPeak(monoisotopicPeak), ChargeState(chargeState)
    {
        setIntensity(intensity / (double)chargeState);
    }

    double IsotopicEnvelope::getIntensity() const
    {
        return privateIntensity;
    }

    void IsotopicEnvelope::setIntensity(double value)
    {
        privateIntensity = value;
    }

    void IsotopicEnvelope::Normalize(double normalizationFactor)
    {
        setIntensity(getIntensity() * normalizationFactor);
    }

    std::string IsotopicEnvelope::ToString()
    {
        return "+" + std::to_string(ChargeState) + "|" +
            std::to_string(getIntensity()) + "|" +
            std::to_string(IndexedPeak->RetentionTime) + "|" +
            std::to_string(IndexedPeak->ZeroBasedMs1ScanIndex);
    }
}
