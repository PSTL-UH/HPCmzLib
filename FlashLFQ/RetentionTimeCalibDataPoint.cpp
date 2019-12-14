#include "RetentionTimeCalibDataPoint.h"
#include "ChromatographicPeak.h"

namespace FlashLFQ
{

    RetentionTimeCalibDataPoint::RetentionTimeCalibDataPoint(ChromatographicPeak *donorFilePeak, ChromatographicPeak *acceptorFilePeak) : DonorFilePeak(donorFilePeak), AcceptorFilePeak(acceptorFilePeak), RtDiff(acceptorFilePeak->getApex()->IndexedPeak->RetentionTime - donorFilePeak->getApex()->IndexedPeak->RetentionTime)
    {
    }

    std::string RetentionTimeCalibDataPoint::ToString()
    {
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        return "DonorRT: " + DonorFilePeak->getApex()->IndexedPeak->RetentionTime.ToString("F3") + " AcceptorRT: " + AcceptorFilePeak->getApex()->IndexedPeak->RetentionTime.ToString("F3") + " Diff: " + RtDiff.ToString("F3");
    }
}
