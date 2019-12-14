#pragma once

#include <string>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace FlashLFQ { class ChromatographicPeak; }

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
            delete DonorFilePeak;
            delete AcceptorFilePeak;
        }

        RetentionTimeCalibDataPoint(ChromatographicPeak *donorFilePeak, ChromatographicPeak *acceptorFilePeak);

        // for debugging
        std::string ToString() override;
    };
}
