#pragma once

#include <type_traits>


namespace MassSpectrometry {
    template<typename TScan>
    class IMsDynamicDataFile : public IDisposable {
        static_assert(std::is_base_of<IMsDataScan<IMzSpectrum<IMzPeak>>, TScan>::value, L"TScan must inherit from IMsDataScan<IMzSpectrum<IMzPeak>>");

//        #region Public Methods

    public:
        virtual void ClearCachedScans() = 0;

//        #endregion Public Methods
    };
}
