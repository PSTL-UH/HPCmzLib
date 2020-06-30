/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
#pragma once

namespace Spectra {
    class IPeak {

    public:
        virtual double getX() const = 0;
        virtual double getY() const = 0;

    };
}
