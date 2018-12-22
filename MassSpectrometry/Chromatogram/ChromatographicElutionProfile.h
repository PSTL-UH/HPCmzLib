﻿#pragma once

#include "../../MzLibUtil/DoubleRange.h"
#include <vector>
#include <type_traits>

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work Copyright 2016 Stefan Solntsev
//
// This file (ChromatogramElutionProfile.cs) is part of MassSpectrometry.
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

using namespace MzLibUtil;
using namespace Spectra;

namespace MassSpectrometry {
    template<typename T>
    class ChromatographicElutionProfile {
        static_assert(std::is_base_of<IPeak, T>::value, L"T must inherit from IPeak");

    private:
        DoubleRange *privateTimeRange;
        int privateCount = 0;
        double privateSummedArea = 0;

//        #region Private Fields

        std::vector<T> const _peaks;

//        #endregion Private Fields

//        #region Public Constructors

    public:
        ChromatographicElutionProfile(ICollection<T> *peaks) : _peaks(peaks->ToArray()) {
            setCount(peaks->Count);
            if (getCount() == 0) {
                return;
            }

            setSummedArea(_peaks.Sum([&] (std::any p) {
                p::Y;
            }));
            DoubleRange tempVar(_peaks[0]->getX(), _peaks[getCount() - 1]->getX());
            setTimeRange(&tempVar);
        }

//        #endregion Public Constructors

//        #region Public Properties

        T getStartPeak() const {
            return _peaks[0];
        }

        T getEndPeak() const {
            return _peaks[getCount() - 1];
        }

        DoubleRange *getTimeRange() const {
            return privateTimeRange;
        }
        void setTimeRange(DoubleRange *value) {
            privateTimeRange = value;
        }

        int getCount() const {
            return privateCount;
        }
        void setCount(int value) {
            privateCount = value;
        }

        double getSummedArea() const {
            return privateSummedArea;
        }
        void setSummedArea(double value) {
            privateSummedArea = value;
        }

//        #endregion Public Properties

//        #region Public Methods

        double TrapezoidalArea() {
            double area = 0;
            for (int i = 0; i < getCount() - 1; i++) {
                T peak1 = _peaks[i];
                T peak2 = _peaks[i + 1];
                area += (peak2->getX() - peak1->getX()) * (peak2->getY() + peak1->getY());
            }
            return area / 2.0;
        }

//        #endregion Public Methods
    };
}
