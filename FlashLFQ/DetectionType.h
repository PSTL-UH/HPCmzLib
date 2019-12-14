#pragma once

namespace FlashLFQ
{
    enum class DetectionType
    {
        MSMS,
        MBR,
        NotDetected,
        MSMSAmbiguousPeakfinding,
        MSMSIdentifiedButNotQuantified,
        Imputed
    };
}
