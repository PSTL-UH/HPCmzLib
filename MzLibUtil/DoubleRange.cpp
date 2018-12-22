#include "DoubleRange.h"

namespace MzLibUtil {

    DoubleRange::DoubleRange(double minimum, double maximum) {
        setMinimum(minimum);
        setMaximum(maximum);
    }

    DoubleRange::DoubleRange(const DoubleRange &range) : DoubleRange(range->Minimum, range->Maximum) {
    }

    double DoubleRange::getMaximum() const {
        return privateMaximum;
    }

    void DoubleRange::setMaximum(double value) {
        privateMaximum = value;
    }

    double DoubleRange::getMinimum() const {
        return privateMinimum;
    }

    void DoubleRange::setMinimum(double value) {
        privateMinimum = value;
    }

    double DoubleRange::getMean() const {
        return (getMaximum() + getMinimum()) / 2.0;
    }

    double DoubleRange::getWidth() const {
        return getMaximum() - getMinimum();
    }

    std::wstring DoubleRange::ToString() {
        return ToString(L"G9");
    }

    std::wstring DoubleRange::ToString(const std::wstring &format) {
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
        return StringHelper::formatSimple(L"[{0};{1}]", getMinimum().ToString(format, System::Globalization::CultureInfo::InvariantCulture), getMaximum().ToString(format, System::Globalization::CultureInfo::InvariantCulture));
    }

    int DoubleRange::CompareTo(double item) {
        if (getMinimum().CompareTo(item) > 0) {
            return -1;
        }
        if (getMaximum().CompareTo(item) < 0) {
            return 1;
        }
        return 0;
    }

    bool DoubleRange::IsSuperRange(DoubleRange *other) {
        return getMaximum().CompareTo(other->getMaximum()) >= 0 && getMinimum().CompareTo(other->getMinimum()) <= 0;
    }

    bool DoubleRange::IsSubRange(DoubleRange *other) {
        return getMaximum().CompareTo(other->getMaximum()) <= 0 && getMinimum().CompareTo(other->getMinimum()) >= 0;
    }

    bool DoubleRange::IsOverlapping(DoubleRange *other) {
        return getMaximum().CompareTo(other->getMinimum()) >= 0 && getMinimum().CompareTo(other->getMaximum()) <= 0;
    }

    bool DoubleRange::Contains(double item) {
        return CompareTo(item).Equals(0);
    }
}
