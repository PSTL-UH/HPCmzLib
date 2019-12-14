#include "IndexedMassSpectralPeak.h"


namespace FlashLFQ
{

    IndexedMassSpectralPeak::IndexedMassSpectralPeak(double mz, double intensity, int zeroBasedMs1ScanIndex, double retentionTime) : ZeroBasedMs1ScanIndex(zeroBasedMs1ScanIndex), Mz(mz), RetentionTime(retentionTime), Intensity(intensity)
    {
    }

    bool IndexedMassSpectralPeak::Equals(std::any obj)
    {
        auto otherPeak = std::any_cast<IndexedMassSpectralPeak*>(obj);

        return otherPeak != nullptr && otherPeak->Mz == this->Mz && otherPeak->ZeroBasedMs1ScanIndex == this->ZeroBasedMs1ScanIndex;
    }

    int IndexedMassSpectralPeak::GetHashCode()
    {
        return Mz.GetHashCode();
    }

    std::string IndexedMassSpectralPeak::ToString()
    {
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        return Mz.ToString("F3") + "; " + std::to_string(ZeroBasedMs1ScanIndex);
    }
}
