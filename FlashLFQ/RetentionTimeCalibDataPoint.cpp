#include "RetentionTimeCalibDataPoint.h"
#include "ChromatographicPeak.h"
#include "IndexedMassSpectralPeak.h"

namespace FlashLFQ
{

    RetentionTimeCalibDataPoint::RetentionTimeCalibDataPoint(ChromatographicPeak *donorFilePeak,
                                                             ChromatographicPeak *acceptorFilePeak) :
        DonorFilePeak(donorFilePeak), AcceptorFilePeak(acceptorFilePeak),
        RtDiff(acceptorFilePeak->getApex()->IndexedPeak->RetentionTime - donorFilePeak->getApex()->IndexedPeak->RetentionTime)
    {
    }

    std::string RetentionTimeCalibDataPoint::ToString()
    {
        return "DonorRT: " + std::to_string(DonorFilePeak->getApex()->IndexedPeak->RetentionTime) +
            " AcceptorRT: " + std::to_string(AcceptorFilePeak->getApex()->IndexedPeak->RetentionTime) +
            " Diff: " + std::to_string(RtDiff);
    }
}
