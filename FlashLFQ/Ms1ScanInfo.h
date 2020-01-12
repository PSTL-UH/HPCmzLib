#pragma once

#include <string>

namespace FlashLFQ
{
    class Ms1ScanInfo
    {
    public:
        const int OneBasedScanNumber;
        const int ZeroBasedMs1ScanIndex;
        const double RetentionTime;

        Ms1ScanInfo(int oneBasedScanNumber, int zeroBasedMs1ScanIndex, double retentionTime);

        std::string ToString();
    };
}
