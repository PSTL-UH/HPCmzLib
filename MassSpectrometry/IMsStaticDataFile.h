#pragma once

#include <type_traits>
#include "MzSpectra/IMzSpectrum.h"
#include "MzSpectra/IMzPeak.h"
#include "DataScan/IMsDataScan.h"

namespace MassSpectrometry {
    template<typename TScan>
    class IMsStaticDataFile {
        static_assert(std::is_base_of<IMsDataScan<IMzSpectrum<IMzPeak>>, TScan>::value, "TScan must inherit from IMsDataScan<IMzSpectrum<IMzPeak>>");

    };
}
