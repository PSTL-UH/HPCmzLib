/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
#include "ClassExtensions.h"

namespace MzLibUtil {

    std::vector<double> ClassExtensions::BoxCarSmooth(std::vector<double> &data, int points) {
        // Force to be odd
        points = points - (1 - points % 2);

        int count = data.size();

        int newCount = count - points + 1;

        std::vector<double> smoothedData(newCount);

        for (int i = 0; i < newCount; i++) {
            double value = 0;

            for (int j = i; j < i + points; j++) {
                value += data[j];
            }

            smoothedData[i] = value / points;
        }
        return smoothedData;
    }

}
