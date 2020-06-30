/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
#pragma once

#include "MzSpectra/MzSpectrum.h"
#include <vector>

#include "MzSpectra/MzPeak.h"

namespace MassSpectrometry {
    class GeneratedMzSpectrum : public MzSpectrum {
        
    public:
        GeneratedMzSpectrum(std::vector<double> &mz, std::vector<double> &intensities, bool shouldCopy);

    protected:
        MzPeak *GeneratePeak(int index);

    };
}
