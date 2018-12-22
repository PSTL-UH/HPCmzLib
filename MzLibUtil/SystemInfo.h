#pragma once

#include <string>
#include <any>
#include "stringbuilder.h"

using namespace Microsoft::Win32;

#if defined(ONLYNETSTANDARD)
#else


#endif


namespace MzLibUtil {
    class SystemInfo final {
//        #region Public Methods

    public:
        static std::wstring CompleteSystemInfo();

        static std::wstring SystemProse();

//        #endregion Public Methods

//        #region Private Methods

    private:
        static std::wstring GetManufacturer();

        static std::wstring GetWindowsOs();

        static std::wstring GetCpuRegister();

        static std::wstring GetMaxClockSpeed();

        static std::wstring WindowsOperatingSystemVersion();

        static std::wstring DotNet();

        static std::wstring InstalledRam();

        static std::wstring ProcessorCount();

        static std::wstring MsFileReader_FileIo();

        static std::wstring MsFileReader_Fregistry();

        static std::wstring MsFileReader_XRawfile2();

        static std::wstring CheckFor45PlusVersion(int releaseKey);

//        #endregion Private Methods
    };
}
