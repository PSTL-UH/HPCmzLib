/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
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
        std::optional<double> privateMinimumAllowedIntensityRatioToBasePeakM;
        std::optional<int> privateNumberOfPeaksToKeepPerWindow;
        std::optional<int> privateNumberOfWindows;
        bool privateApplyTrimmingToMs1 = false;
        bool privateApplyTrimmingToMsMs = false;

        //Num: the number of windows used to filer; testSize: for comparing the amount of topN is used on
    public:
        FilteringParams(std::optional<int> numberOfPeaksToKeepPerWindow = std::nullopt,
                        std::optional<double> minimumAllowedIntensityRatioToBasePeak = std::nullopt,
                        std::optional<int> numberOfWindows = std::nullopt,
                        bool applyTrimmingToMs1 = true, bool applyTrimmingToMsMs = true);

        std::optional<double> getMinimumAllowedIntensityRatioToBasePeakM() const override;
        std::optional<int> getNumberOfPeaksToKeepPerWindow() const override;
        std::optional<int> getNumberOfWindows() const override;
        bool getApplyTrimmingToMs1() const override;
        bool getApplyTrimmingToMsMs() const override;
    };
}
