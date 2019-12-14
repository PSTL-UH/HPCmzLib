#include "Ms1ScanInfo.h"

namespace FlashLFQ
{

    Ms1ScanInfo::Ms1ScanInfo(int oneBasedScanNumber, int zeroBasedMs1ScanIndex, double retentionTime) : OneBasedScanNumber(oneBasedScanNumber), ZeroBasedMs1ScanIndex(zeroBasedMs1ScanIndex), RetentionTime(retentionTime)
    {
    }

    std::string Ms1ScanInfo::ToString()
    {
        return std::to_string(ZeroBasedMs1ScanIndex) + "; " + std::to_string(OneBasedScanNumber) + "; " + std::to_string(RetentionTime);
    }
}
