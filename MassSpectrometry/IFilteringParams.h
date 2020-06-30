/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
#pragma once

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

#include <optional>

namespace MassSpectrometry
{
    class IFilteringParams
    {
    public:
        virtual std::optional<double> getMinimumAllowedIntensityRatioToBasePeakM() const = 0;
        virtual std::optional<int> getNumberOfPeaksToKeepPerWindow() const = 0;
        virtual std::optional<int> getNumberOfWindows() const = 0;
        virtual bool getApplyTrimmingToMs1() const = 0;
        virtual bool getApplyTrimmingToMsMs() const = 0;
    };
}
