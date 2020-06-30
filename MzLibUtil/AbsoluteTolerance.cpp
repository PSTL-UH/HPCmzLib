/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
#include "AbsoluteTolerance.h"
#include "DoubleRange.h"


namespace MzLibUtil {

    AbsoluteTolerance::AbsoluteTolerance(double value) : Tolerance(value) {
    }

    std::string AbsoluteTolerance::ToString() {
        return StringHelper::formatSimple("{0}{1} Absolute", "±", getValue());
    }

    DoubleRange *AbsoluteTolerance::GetRange(double mean) {
        return new DoubleRange(mean - getValue(), mean + getValue());
    }

    double AbsoluteTolerance::GetMinimumValue(double mean) {
        return mean - getValue();
    }

    double AbsoluteTolerance::GetMaximumValue(double mean) {
        return mean + getValue();
    }

    bool AbsoluteTolerance::Within(double experimental, double theoretical) {
        return std::abs(experimental - theoretical) <= getValue();
    }
}
