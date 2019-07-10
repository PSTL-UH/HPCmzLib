#include "FilteringParams.h"

namespace MassSpectrometry
{

    FilteringParams::FilteringParams(std::optional<int> numberOfPeaksToKeepPerWindow, std::optional<double> minimumAllowedIntensityRatioToBasePeak, std::optional<int> numberOfWindows, bool applyTrimmingToMs1, bool applyTrimmingToMsMs)
    {
        privateNumberOfPeaksToKeepPerWindow = numberOfPeaksToKeepPerWindow;
        privateMinimumAllowedIntensityRatioToBasePeakM = minimumAllowedIntensityRatioToBasePeak;
        privateNumberOfWindows = numberOfWindows;
        privateApplyTrimmingToMs1 = applyTrimmingToMs1;
        privateApplyTrimmingToMsMs = applyTrimmingToMsMs;
    }

    std::optional<double> FilteringParams::getMinimumAllowedIntensityRatioToBasePeakM() const
    {
        return privateMinimumAllowedIntensityRatioToBasePeakM;
    }

    std::optional<int> FilteringParams::getNumberOfPeaksToKeepPerWindow() const
    {
        return privateNumberOfPeaksToKeepPerWindow;
    }

    std::optional<int> FilteringParams::getNumberOfWindows() const
    {
        return privateNumberOfWindows;
    }

    bool FilteringParams::getApplyTrimmingToMs1() const
    {
        return privateApplyTrimmingToMs1;
    }

    bool FilteringParams::getApplyTrimmingToMsMs() const
    {
        return privateApplyTrimmingToMsMs;
    }
}
