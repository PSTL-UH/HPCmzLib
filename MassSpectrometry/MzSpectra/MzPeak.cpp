#include "MzPeak.h"
#include "stringhelper.h"

namespace MassSpectrometry
{

    double MzPeak::getMz() const
    {
        return privateMz;
    }

    void MzPeak::setMz(double value)
    {
        privateMz = value;
    }

    double MzPeak::getIntensity() const
    {
        return privateIntensity;
    }

    void MzPeak::setIntensity(double value)
    {
        privateIntensity = value;
    }

    MzPeak::MzPeak(double mz, double intensity)
    {
        setMz(mz);
        setIntensity(intensity);
    }

    std::string MzPeak::ToString()
    {
        return StringHelper::formatSimple("({0:G7},{1:G7})", getMz(), getIntensity());
    }
}
