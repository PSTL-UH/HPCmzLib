/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
#include "GeneratedMzSpectrum.h"
#include "MzSpectra/MzPeak.h"

namespace MassSpectrometry {

    GeneratedMzSpectrum::GeneratedMzSpectrum(std::vector<double> &mz, std::vector<double> &intensities, bool shouldCopy) : MzSpectrum (mz, intensities, shouldCopy) {
    }

    MzPeak *GeneratedMzSpectrum::GeneratePeak(int index) {
        return new MzPeak(getXArray()[index], getYArray()[index]);
    }
}
