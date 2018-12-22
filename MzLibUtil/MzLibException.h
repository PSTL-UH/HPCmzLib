#pragma once

#include <string>
#include <stdexcept>


namespace MzLibUtil {
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Serializable] public class MzLibException : Exception
    class MzLibException : public std::runtime_error {
//        #region Public Constructors

    public:
        MzLibException(const std::wstring &message);

//        #endregion Public Constructors
    };
}
