#pragma once

#include <string>

namespace MassSpectrometry
{
    class MzPeak
    {
    private:
        double privateMz = 0;
        double privateIntensity = 0;

    public:
        double getMz() const;
        void setMz(double value);
        double getIntensity() const;
        void setIntensity(double value);

        MzPeak(double mz, double intensity);

        std::string ToString() override;
    };
}
