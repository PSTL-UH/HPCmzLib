#pragma once

#include <type_traits>

namespace MassSpectrometry {
    template<typename TScan>
    class IMsStaticDataFile {
        static_assert(std::is_base_of<IMsDataScan<IMzSpectrum<IMzPeak>>, TScan>::value, L"TScan must inherit from IMsDataScan<IMzSpectrum<IMzPeak>>");

    };
}
