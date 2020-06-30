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
#include <vector>
#include "stringbuilder.h"

#include "MzSpectra/IsotopicEnvelope.h"

namespace MassSpectrometry {

    class ExtendedIsotopicEnvelope {
    public:
        int scanNumber;
        double elutionTime;
        IsotopicEnvelope *isotopicEnvelope;
        
        ExtendedIsotopicEnvelope( int sN, double eT, IsotopicEnvelope *iE);
    };  
    
    class DeconvolutionFeature {
    private:
        double privateMass = 0;
        int privateNumPeaks = 0;

    public:
        std::vector<ExtendedIsotopicEnvelope*> isotopicEnvelopes;
//        std::vector<(int scanNumber, double elutionTime, IsotopicEnvelope isEnvelope)*> isotopicEnvelopes = std::vector<(int scanNumber, double elutionTime, IsotopicEnvelope isotopicEnvelope)*>();

        double getMass() const;
        void setMass(double value);

        int getNumPeaks() const;
        void setNumPeaks(int value);

        std::vector<int> getAllCharges() const;

        void AddEnvelope(int scanNumber, double elutionTime, IsotopicEnvelope *isotopicEnvelope);

    };
}
