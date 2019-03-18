#pragma once

#include <type_traits>


namespace MassSpectrometry {
    template<typename TScan>
    class IMsDynamicDataFile : public IDisposable {
        static_assert(std::is_base_of<IMsDataScan<IMzSpectrum<IMzPeak>>, TScan>::value, "TScan must inherit from IMsDataScan<IMzSpectrum<IMzPeak>>");

    public:
        virtual void ClearCachedScans() = 0;

    };
}
