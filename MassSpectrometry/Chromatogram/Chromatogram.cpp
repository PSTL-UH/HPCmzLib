#include "Chromatogram.h"

using namespace MzLibUtil;
using namespace Spectra;

namespace MassSpectrometry
{

#ifdef ORIG
    Chromatogram::Chromatogram(std::vector<double> &times, std::vector<double> &intensities, bool shouldCopy) : Chromatogram<ChromatographicPeak>(times, intensities, shouldCopy)
    {
    }

    Chromatogram::Chromatogram(std::vector<std::vector<double>> &timeintensities) : Chromatogram<ChromatographicPeak>(timeintensities)
    {
    }

    Chromatogram::Chromatogram(const Chromatogram<void> &other) : Chromatogram<ChromatographicPeak>(other)
    {
    }
#endif
    
    Chromatogram *Chromatogram::CreateSmoothChromatogram(SmoothingType smoothing, int points)
    {
        switch (smoothing)
        {
            case SmoothingType::BoxCar:
            {
                //std::vector<double> newTimes = this->getXArray().BoxCarSmooth(points);
                std::vector<double> newTimes = Math::BoxCarSmooth(this->getXArray(), points);
                //std::vector<double> newIntensities = this->getYArray().BoxCarSmooth(points);
                 std::vector<double> newIntensities = Math::BoxCarSmooth(this->getYArray(), points);
                return new Chromatogram(newTimes, newIntensities, false);

            }
            default:
                return new Chromatogram(this->getXArray(), this->getYArray(), false);
        }
    }

    ChromatographicPeak *Chromatogram::GeneratePeak(int index)
    {
        return new ChromatographicPeak(this->getXArray()[index], this->getYArray()[index]);
    }
}
