#include "IsotopicEnvelope.h"
#include "IndexedMassSpectralPeak.h"

namespace FlashLFQ
{

    IsotopicEnvelope::IsotopicEnvelope(IndexedMassSpectralPeak *monoisotopicPeak, int chargeState, double intensity) : IndexedPeak(monoisotopicPeak), ChargeState(chargeState)
    {
        setIntensity(intensity / chargeState);
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
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        return "+" + std::to_string(ChargeState) + "|" + getIntensity().ToString("F0") + "|" + IndexedPeak->RetentionTime.ToString("F3") + "|" + std::to_string(IndexedPeak->ZeroBasedMs1ScanIndex);
    }
}
