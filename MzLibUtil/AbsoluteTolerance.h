﻿#pragma once

#include "Tolerance.h"
#include <string>
#include <cmath>
#include "stringhelper.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace MzLibUtil { class DoubleRange; }

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work copyright 2016 Stefan Solntsev
//
// This file (Tolerance.cs) is part of MassSpectrometry.
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


namespace MzLibUtil {
    /// <summary>
    /// The tolerance, or error, of two points
    /// </summary>
    class AbsoluteTolerance : public Tolerance {
//        #region Public Constructors

        /// <summary>
        /// Creates a new tolerance given a unit, value, and whether the tolerance is ±
        /// </summary>
        /// <param name="unit">The units for this tolerance</param>
        /// <param name="value">The numerical value of the tolerance</param>
    public:
        AbsoluteTolerance(double value);

//        #endregion Public Constructors

//        #region Public Methods

        std::wstring ToString() override;

        DoubleRange *GetRange(double mean) override;

        double GetMinimumValue(double mean) override;

        double GetMaximumValue(double mean) override;

        bool Within(double experimental, double theoretical) override;

//        #endregion Public Methods
    };
}
