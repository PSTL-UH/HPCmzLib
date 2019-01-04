#include "DoubleRange.h"

namespace MzLibUtil {

    DoubleRange::DoubleRange(double minimum, double maximum) {
        setMinimum(minimum);
        setMaximum(maximum);
    }

    DoubleRange::DoubleRange(const DoubleRange &range) {
        privateMinimum= range.privateMinimum;
        privateMaximum =range.privateMaximum;
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

    std::string DoubleRange::ToString() {
        return ToString("G9");
    }

    std::string DoubleRange::ToString(const std::string &format) {
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
//        return StringHelper::formatSimple(L"[{0};{1}]", getMinimum().ToString(format, System::Globalization::CultureInfo::InvariantCulture), getMaximum().ToString(format, System::Globalization::CultureInfo::InvariantCulture));
        return StringHelper::formatSimple("[{0};{1}]", getMinimum(), getMaximum());
    }

    int DoubleRange::CompareTo(double item) {
#if ORIG
        if (getMinimum().CompareTo(item) > 0) {
            return -1;
        }
        if (getMaximum().CompareTo(item) < 0) {
            return 1;
        }
#endif
        if ( getMinimum() > item ) {
            return -1;
        }
        if ( getMaximum() < item ) {
            return 1;
        }
        
        return 0;
    }

    bool DoubleRange::IsSuperRange(DoubleRange *other) {
#if ORIG
        return getMaximum().CompareTo(other->getMaximum()) >= 0 && getMinimum().CompareTo(other->getMinimum()) <= 0;
#endif
        return  (( getMaximum() >= other->getMaximum()) && (getMinimum()<= other->getMinimum()));
    }

    bool DoubleRange::IsSubRange(DoubleRange *other) {
#if ORIG
        return getMaximum().CompareTo(other->getMaximum()) <= 0 && getMinimum().CompareTo(other->getMinimum()) >= 0;
#endif
        return ((getMaximum() <= other->getMaximum())  && (getMinimum() >= other->getMinimum()));
    }

    bool DoubleRange::IsOverlapping(DoubleRange *other) {
#if ORIG
        return getMaximum().CompareTo(other->getMinimum()) >= 0 && getMinimum().CompareTo(other->getMaximum()) <= 0;
#endif
        return ((getMaximum() >= other->getMinimum()) && (getMinimum() <= other->getMaximum()));
    }

    bool DoubleRange::Contains(double item) {
#if ORIG
        return CompareTo(item).Equals(0);
#endif
        return (CompareTo(item) == 0);
    }
}
