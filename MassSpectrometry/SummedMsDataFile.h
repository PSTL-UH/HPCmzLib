/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
#pragma once

#include <vector>
#include <cmath>
#include <limits>

#include "../MzLibUtil/MzLibUtil.h"
using namespace MzLibUtil;

#include "MsDataFile.h"
#include "MsDataScan.h"
#include "MzSpectra/MzSpectrum.h"

namespace MassSpectrometry {
   class SummedMsDataFile : public MsDataFile {

    private:
        MsDataFile *const raw;
        const int numScansToAverage;
        const double ppmToleranceForPeakCombination;

    public:
        virtual ~SummedMsDataFile() {
            if ( raw != nullptr ) {
                delete raw;
            }
        }

        SummedMsDataFile(MsDataFile *raw, int numScansToAverage, double ppmToleranceForPeakCombination);
        std::vector<MsDataScan*> GetAllScansList() override;
        MsDataScan *GetOneBasedScan(int oneBasedScanNumber) override;

    private:
        static MzSpectrum *CombinePeaks(std::vector<MzSpectrum*> &spectraToCombine, double ppmTolerance);

   };
}
