/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
#include "PpmTolerance.h"
#include "DoubleRange.h"


namespace MzLibUtil {

    PpmTolerance::PpmTolerance(double value) : Tolerance(value) {
    }

    std::string PpmTolerance::ToString() {
        return StringHelper::formatSimple("{0}{1} PPM", "±", getValue());
    }

    DoubleRange *PpmTolerance::GetRange(double mean) {
        double tol = getValue() * mean / 1e6;
        return new DoubleRange(mean - tol, mean + tol);
    }

    double PpmTolerance::GetMinimumValue(double mean) {
        return mean * (1 - (getValue() / 1e6));
    }

    double PpmTolerance::GetMaximumValue(double mean) {
        return mean * (1 + (getValue() / 1e6));
    }

    bool PpmTolerance::Within(double experimental, double theoretical) {
        return std::abs((experimental - theoretical) / theoretical * 1e6) <= getValue();
    }
}
