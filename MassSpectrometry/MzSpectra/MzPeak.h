/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
#pragma once

#include <string>

namespace MassSpectrometry
{
    class MzPeak
    {
    private:
        double privateMz = 0;
        double privateIntensity = 0;

    public:
        double getMz() const;
        void setMz(double value);
        double getIntensity() const;
        void setIntensity(double value);

        MzPeak(double mz, double intensity);

        std::string ToString();
    };
}
