#pragma once

#include <string>
#include "stringhelper.h"

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work copyright 2016 Stefan Solntsev
//
// This file (DoubleRange.cs) is part of MassSpectrometry.
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
    class DoubleRange {
    private:
        double privateMaximum = 0;
        double privateMinimum = 0;

//        #region Public Constructors

        /// <summary>
        /// Creates a range from the minimum to maximum values
        /// </summary>
        /// <param name="minimum">The minimum value of the range</param>
        /// <param name="maximum">The maximum value of the range</param>
    public:
        DoubleRange(double minimum, double maximum);

        /// <summary>
        /// Creates a range from another double range. This is the
        /// clone constructor.
        /// </summary>
        /// <param name="range">The other range to copy</param>
        DoubleRange(const DoubleRange &range);

//        #endregion Public Constructors

//        #region Public Properties

        /// <summary>
        /// The maximum value of the range
        /// </summary>
        double getMaximum() const;
        void setMaximum(double value);

        /// <summary>
        /// The minimum value of the range
        /// </summary>
        double getMinimum() const;
        void setMinimum(double value);

        /// <summary>
        /// The mean value of this range:
        /// (Max + Min) / 2
        /// </summary>
        double getMean() const;

        /// <summary>
        /// The width of this range:
        /// (Max - Min)
        /// </summary>
        double getWidth() const;

//        #endregion Public Properties

//        #region Public Methods

        std::wstring ToString() override;

        virtual std::wstring ToString(const std::wstring &format);

        int CompareTo(double item);

        /// <summary>
        /// Checks to see if this range is a proper super range of another range (inclusive)
        /// </summary>
        /// <param name="other">The other range to compare to</param>
        /// <returns>True if this range is fully encloses the other range, false otherwise</returns>
        bool IsSuperRange(DoubleRange *other);

        /// <summary>
        /// Checks to see if this range is a proper sub range of another range (inclusive)
        /// </summary>
        /// <param name="other">The other range to compare to</param>
        /// <returns>True if this range is fully enclosed by the other range, false otherwise</returns>
        bool IsSubRange(DoubleRange *other);

        /// <summary>
        /// Checks to see if this range overlaps another range (inclusive)
        /// </summary>
        /// <param name="other">The other range to compare to</param>
        /// <returns>True if the other range in any way overlaps this range, false otherwise</returns>
        bool IsOverlapping(DoubleRange *other);

        /// <summary>
        /// Determines if the item is contained within a range of values
        /// </summary>
        /// <param name="item">The item to compare against the range</param>
        /// <returns>True if the item is within the range (inclusive), false otherwise</returns>
        bool Contains(double item);

//        #endregion Public Methods
    };
}
