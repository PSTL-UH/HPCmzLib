#pragma once

#include <string>
#include "IndexedMassSpectralPeak.h"

namespace FlashLFQ
{
    class IsotopicEnvelope
    {
    private:
        double privateIntensity = 0;

    public:
        IndexedMassSpectralPeak *const IndexedPeak;
        const int ChargeState;

        virtual ~IsotopicEnvelope()
        {
            //delete IndexedPeak;
        }

        IsotopicEnvelope(IndexedMassSpectralPeak *monoisotopicPeak, int chargeState, double intensity);

        double getIntensity() const;
        void setIntensity(double value);

        void Normalize(double normalizationFactor);

        std::string ToString();
    };
}
