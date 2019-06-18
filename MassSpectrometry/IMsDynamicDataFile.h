#pragma once

#include <type_traits>
#include "MzSpectra/IMzSpectrum.h"
#include "MzSpectra/IMzPeak.h"
#include "DataScan/IMsDataScan.h"

namespace MassSpectrometry {
//    class IMsDynamicDataFile : public IDisposable {

    template<typename TScan>
    class IMsDynamicDataFile  {
        static_assert(std::is_base_of<IMsDataScan<IMzSpectrum<IMzPeak>>, TScan>::value, "TScan must inherit from IMsDataScan<IMzSpectrum<IMzPeak>>");

    public:
        virtual void ClearCachedScans() = 0;

    };
}
