/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
#include "ChromatographicPeak.h"
#include "stringhelper.h"

using namespace Spectra;

namespace MassSpectrometry {

    ChromatographicPeak::ChromatographicPeak(double time, double intensity) : Peak(time, intensity) {
    }
    ChromatographicPeak::ChromatographicPeak() : Peak((double)0, (double)0) {
    }

    double ChromatographicPeak::getIntensity() const {
        return getY();
    }

    double ChromatographicPeak::getTime() const {
        return getX();
    }

    std::string ChromatographicPeak::ToString() {
        return StringHelper::formatSimple("({0:G4}, {1:G4})", getTime(), getIntensity());
    }
}
