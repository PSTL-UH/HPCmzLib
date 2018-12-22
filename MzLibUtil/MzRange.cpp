#include "MzRange.h"

namespace MzLibUtil {

    MzRange::MzRange(double minMZ, double maxMZ) : DoubleRange(minMZ, maxMZ) {
    }

    std::wstring MzRange::ToString(const std::wstring &format) {
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
        return StringHelper::formatSimple(L"[{0} to {1}] m/z", getMinimum().ToString(format, System::Globalization::CultureInfo::InvariantCulture), getMaximum().ToString(format, System::Globalization::CultureInfo::InvariantCulture));
    }
}
