/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
#pragma once

#include "MzSpectra/MzPeak.h"
#include <vector>


namespace MassSpectrometry {
    class GeneratedPeak : public MzPeak {

    private:
        std::vector<double> mzs = std::vector<double>();
        std::vector<double> intensities = std::vector<double>();

    public:
        GeneratedPeak(double Mz, double Intensity);

        void AddMzPeak(double anotherMz, double anotherIntensity);

    };
}
