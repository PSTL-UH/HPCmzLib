#pragma once

#include <string>
#include "ChromatographicPeak.h"

namespace FlashLFQ
{
    class RetentionTimeCalibDataPoint
    {
    public:
        ChromatographicPeak *const DonorFilePeak;
        ChromatographicPeak *const AcceptorFilePeak;
        const double RtDiff;

        virtual ~RetentionTimeCalibDataPoint()
        {
            // delete DonorFilePeak;
            // delete AcceptorFilePeak;
        }

        RetentionTimeCalibDataPoint(ChromatographicPeak *donorFilePeak, ChromatographicPeak *acceptorFilePeak);

        // for debugging
        std::string ToString();
    };
}
