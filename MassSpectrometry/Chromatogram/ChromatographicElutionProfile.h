/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
#pragma once

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
#include "../../Spectra/IPeak.h"
using namespace Spectra;

namespace MassSpectrometry {
    template<typename T>
    class ChromatographicElutionProfile {
        static_assert(std::is_base_of<IPeak, T>::value, "T must inherit from IPeak");

    private:
        DoubleRange *privateTimeRange;
        int privateCount = 0;
        double privateSummedArea = 0;

        std::vector<T> const _peaks;

    public:
    ChromatographicElutionProfile(std::vector<T> *peaks) : _peaks(peaks) {
            setCount(peaks->Count);
            if (getCount() == 0) {
                return;
            }
            double sum=0.0;
            std::for_each(_peaks.begin(), _peaks.end(), [&] (T p) {
                    sum+= p.getY();
                } );
            setSummedArea (sum);
            DoubleRange tempVar(_peaks[0]->getX(), _peaks[getCount() - 1]->getX());
            setTimeRange(&tempVar);
        }

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

        double TrapezoidalArea() {
            double area = 0;
            for (int i = 0; i < getCount() - 1; i++) {
                T peak1 = _peaks[i];
                T peak2 = _peaks[i + 1];
                area += (peak2->getX() - peak1->getX()) * (peak2->getY() + peak1->getY());
            }
            return area / 2.0;
        }

    };
}
