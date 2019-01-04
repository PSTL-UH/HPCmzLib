#include "AbsoluteTolerance.h"
#include "DoubleRange.h"


namespace MzLibUtil {

    AbsoluteTolerance::AbsoluteTolerance(double value) : Tolerance(value) {
    }

    std::string AbsoluteTolerance::ToString() {
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
//        return StringHelper::formatSimple(L"{0}{1} Absolute", "±", getValue().ToString("f4", System::Globalization::CultureInfo::InvariantCulture));
        return StringHelper::formatSimple("{0}{1} Absolute", "±", getValue());
    }

    DoubleRange *AbsoluteTolerance::GetRange(double mean) {
        return new DoubleRange(mean - getValue(), mean + getValue());
    }

    double AbsoluteTolerance::GetMinimumValue(double mean) {
        return mean - getValue();
    }

    double AbsoluteTolerance::GetMaximumValue(double mean) {
        return mean + getValue();
    }

    bool AbsoluteTolerance::Within(double experimental, double theoretical) {
        return std::abs(experimental - theoretical) <= getValue();
    }
}
