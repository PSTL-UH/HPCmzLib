/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
#include "MzLibException.h"


namespace MzLibUtil {

    MzLibException::MzLibException(const std::string &message) : std::runtime_error(message) {
    }
}
