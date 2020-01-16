#include "IndexedMassSpectralPeak.h"
#include "stringhelper.h"

namespace FlashLFQ
{

    IndexedMassSpectralPeak::IndexedMassSpectralPeak(double mz, double intensity,
                                                     int zeroBasedMs1ScanIndex, double retentionTime) :
        ZeroBasedMs1ScanIndex(zeroBasedMs1ScanIndex), Mz(mz),
        RetentionTime(retentionTime), Intensity(intensity)
    {
    }

    bool IndexedMassSpectralPeak::Equals(IndexedMassSpectralPeak* otherPeak)
    {
        return otherPeak != nullptr && otherPeak->Mz == this->Mz &&
            otherPeak->ZeroBasedMs1ScanIndex == this->ZeroBasedMs1ScanIndex;
    }

    int IndexedMassSpectralPeak::GetHashCode()
    {
        return StringHelper::GetHashCode(std::to_string(Mz));
    }

    std::string IndexedMassSpectralPeak::ToString()
    {
        return std::to_string(Mz) + "; " + std::to_string(ZeroBasedMs1ScanIndex);
    }
}
