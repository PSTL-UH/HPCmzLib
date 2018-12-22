#include "Tolerance.h"
#include "PpmTolerance.h"
#include "AbsoluteTolerance.h"
#include "DoubleRange.h"


namespace MzLibUtil {

Regex *const Tolerance::StringRegex = new Regex(LR"((\+-|-\+|±)?\s*([\d.]+)\s*(PPM|Absolute))", RegexOptions::Compiled | RegexOptions::IgnoreCase);

    Tolerance::Tolerance(double value) {
        Value = std::abs(value);
    }

    double Tolerance::getValue() const {
        return privateValue;
    }

    Tolerance *Tolerance::ParseToleranceString(const std::wstring &s) {
        Match *m = StringRegex->Match(s);
        if (m->Groups[3]->Value->Equals(L"PPM", StringComparison::OrdinalIgnoreCase)) {
            return new PpmTolerance(std::stod(m->Groups[2]->Value));
        }
        else {
            return new AbsoluteTolerance(std::stod(m->Groups[2]->Value));
        }
    }
}
