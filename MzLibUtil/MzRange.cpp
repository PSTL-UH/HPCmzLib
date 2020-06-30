/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
#include "MzRange.h"

namespace MzLibUtil {

    MzRange::MzRange(double minMZ, double maxMZ) : DoubleRange(minMZ, maxMZ) {
    }

    std::string MzRange::ToString(const std::string &format) {
        return StringHelper::formatSimple("[{0} to {1}] m/z", getMinimum(), getMaximum());
    }
}
