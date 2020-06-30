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
#include <unordered_set>
#include <vector>
#include <cmath>
#include <limits>
#include "stringbuilder.h"

#include "DeconvolutionFeature.h"
#include "MzSpectra/IsotopicEnvelope.h"

namespace MassSpectrometry {
    class DeconvolutionFeatureWithMassesAndScans {
    private:
        int privateMinScanIndex = 0;
        int privateMaxScanIndex = 0;
        double privateMass = 0;
        double privateMinElutionTime = 0;
        double privateMaxElutionTime = 0;
        double privateTotalNormalizedIntensity = 0;
        IsotopicEnvelope *privateMostIntenseEnvelope;
        double privateMostIntenseEnvelopeElutionTime = 0;
        

    public:
        std::vector<DeconvolutionFeature*> groups = std::vector<DeconvolutionFeature*>();

        DeconvolutionFeatureWithMassesAndScans();

        int getMinScanIndex() const;
        void setMinScanIndex(int value);

        int getMaxScanIndex() const;
        void setMaxScanIndex(int value);

        double getMass() const;
        void setMass(double value);

        double getScore() const;
        int getNumPeaks() const;

        double getMinElutionTime() const;
        void setMinElutionTime(double value);
        double getMaxElutionTime() const;
        void setMaxElutionTime(double value);

        double getTotalNormalizedIntensity() const;
        void setTotalNormalizedIntensity(double value);
        IsotopicEnvelope *getMostIntenseEnvelope() const;
        void setMostIntenseEnvelope(IsotopicEnvelope *value);
        double getMostIntenseEnvelopeElutionTime() const;
        void setMostIntenseEnvelopeElutionTime(double value);
        
        std::string ToString();
        std::string OneLineString();

        void AddEnvelope(IsotopicEnvelope *isotopicEnvelope, int scanIndex, double elutionTime);

    };
}
