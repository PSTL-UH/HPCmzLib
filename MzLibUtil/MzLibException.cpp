#include "MzLibException.h"


namespace MzLibUtil {

    MzLibException::MzLibException(const std::wstring &message) : Exception(message) {
    }
}
