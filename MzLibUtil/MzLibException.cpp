#include "MzLibException.h"


namespace MzLibUtil {

    MzLibException::MzLibException(const std::string &message) : std::runtime_error(message) {
    }
}
