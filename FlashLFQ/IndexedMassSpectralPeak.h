#pragma once

#include <string>
#include <any>


namespace FlashLFQ
{
    class IndexedMassSpectralPeak
    {
    public:
        const int ZeroBasedMs1ScanIndex;
        const double Mz;
        const double RetentionTime;
        const double Intensity;

        IndexedMassSpectralPeak(double mz, double intensity, int zeroBasedMs1ScanIndex, double retentionTime);

        bool Equals(IndexedMassSpectralPeak* obj);

        int GetHashCode();

        std::string ToString();
    };
}
