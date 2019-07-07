#include "Chromatogram.h"

using namespace MzLibUtil;
using namespace Spectra;

namespace MassSpectrometry
{

    Chromatogram::Chromatogram(std::vector<double> &times, std::vector<double> &intensities, bool shouldCopy) : Chromatogram<ChromatographicPeak>(times, intensities, shouldCopy)
    {
    }

    Chromatogram::Chromatogram(std::vector<std::vector<double>> &timeintensities) : Chromatogram<ChromatographicPeak>(timeintensities)
    {
    }

    Chromatogram::Chromatogram(const Chromatogram<void> &other) : Chromatogram<ChromatographicPeak>(other)
    {
    }

    Chromatogram<void> *Chromatogram::CreateSmoothChromatogram(SmoothingType smoothing, int points)
    {
        switch (smoothing)
        {
            case SmoothingType::BoxCar:
            {
                std::vector<double> newTimes = getXArray().BoxCarSmooth(points);
                std::vector<double> newIntensities = getYArray().BoxCarSmooth(points);
                return new Chromatogram(newTimes, newIntensities, false);

            }
            default:
                return new Chromatogram(this);
        }
    }

    ChromatographicPeak *Chromatogram::GeneratePeak(int index)
    {
        return new ChromatographicPeak(getXArray()[index], getYArray()[index]);
    }
}
