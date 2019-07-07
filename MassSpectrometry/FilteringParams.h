#pragma once

#include "IFilteringParams.h"
#include <optional>

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work Copyright 2016 Stefan Solntsev
//
// This file (MsDataFile.cs) is part of MassSpectrometry.
//
// MassSpectrometry is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MassSpectrometry is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with MassSpectrometry. If not, see <http://www.gnu.org/licenses/>.

namespace MassSpectrometry
{
    class FilteringParams : public IFilteringParams
    {
    private:
        Nullable<double> privateMinimumAllowedIntensityRatioToBasePeakM;
        Nullable<int> privateNumberOfPeaksToKeepPerWindow;
        Nullable<int> privateNumberOfWindows;
        bool privateApplyTrimmingToMs1 = false;
        bool privateApplyTrimmingToMsMs = false;

        //Num: the number of windows used to filer; testSize: for comparing the amount of topN is used on
    public:
        FilteringParams(Nullable<int> numberOfPeaksToKeepPerWindow = std::nullopt, Nullable<double> minimumAllowedIntensityRatioToBasePeak = std::nullopt, Nullable<int> numberOfWindows = std::nullopt, bool applyTrimmingToMs1 = true, bool applyTrimmingToMsMs = true);

        Nullable<double> getMinimumAllowedIntensityRatioToBasePeakM() const override;
        Nullable<int> getNumberOfPeaksToKeepPerWindow() const override;
        Nullable<int> getNumberOfWindows() const override;
        bool getApplyTrimmingToMs1() const override;
        bool getApplyTrimmingToMsMs() const override;
    };
}
