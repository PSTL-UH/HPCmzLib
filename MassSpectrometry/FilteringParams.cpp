#include "FilteringParams.h"

namespace MassSpectrometry
{

    FilteringParams::FilteringParams(Nullable<int> numberOfPeaksToKeepPerWindow, Nullable<double> minimumAllowedIntensityRatioToBasePeak, Nullable<int> numberOfWindows, bool applyTrimmingToMs1, bool applyTrimmingToMsMs)
    {
        NumberOfPeaksToKeepPerWindow = numberOfPeaksToKeepPerWindow;
        MinimumAllowedIntensityRatioToBasePeakM = minimumAllowedIntensityRatioToBasePeak;
        NumberOfWindows = numberOfWindows;
        ApplyTrimmingToMs1 = applyTrimmingToMs1;
        ApplyTrimmingToMsMs = applyTrimmingToMsMs;
    }

    Nullable<double> FilteringParams::getMinimumAllowedIntensityRatioToBasePeakM() const
    {
        return privateMinimumAllowedIntensityRatioToBasePeakM;
    }

    Nullable<int> FilteringParams::getNumberOfPeaksToKeepPerWindow() const
    {
        return privateNumberOfPeaksToKeepPerWindow;
    }

    Nullable<int> FilteringParams::getNumberOfWindows() const
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
