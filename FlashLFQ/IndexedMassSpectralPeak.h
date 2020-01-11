#pragma once

#include <string>
#include <any>


namespace FlashLFQ
{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Serializable] public class IndexedMassSpectralPeak
    class IndexedMassSpectralPeak
    {
    public:
        const int ZeroBasedMs1ScanIndex;
        const double Mz;
        const double RetentionTime;
        const double Intensity;

        IndexedMassSpectralPeak(double mz, double intensity, int zeroBasedMs1ScanIndex, double retentionTime);

        bool Equals(std::any obj);

        int GetHashCode();

        std::string ToString();
    };
}
