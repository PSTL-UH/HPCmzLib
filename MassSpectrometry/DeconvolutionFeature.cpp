/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
#include <algorithm>
#include "DeconvolutionFeature.h"
#include "MzSpectra/IsotopicEnvelope.h"


namespace MassSpectrometry {


    ExtendedIsotopicEnvelope::ExtendedIsotopicEnvelope( int sN, double eT, IsotopicEnvelope *iE) : scanNumber(sN), elutionTime(eT), isotopicEnvelope(iE){
    }
    
    double DeconvolutionFeature::getMass() const {
        return privateMass;
    }

    void DeconvolutionFeature::setMass(double value) {
        privateMass = value;
    }

    int DeconvolutionFeature::getNumPeaks() const {
        return privateNumPeaks;
    }

    void DeconvolutionFeature::setNumPeaks(int value) {
        privateNumPeaks = value;
    }


    std::vector<int> DeconvolutionFeature::getAllCharges() const {
#ifdef ORIG
        return isotopicEnvelopes.Select([&] (std::any b) {
            b::isotopicEnvelope::charge;
        }).ToList();
#endif
        std::vector<int> v;
        std::for_each (isotopicEnvelopes.begin(), isotopicEnvelopes.end(), [&](ExtendedIsotopicEnvelope *e){
                v.push_back ( e->isotopicEnvelope->charge);
            });        
        return v;
    }


    void DeconvolutionFeature::AddEnvelope(int scanNumber, double elutionTime, IsotopicEnvelope *isotopicEnvelope) {
        ExtendedIsotopicEnvelope *e = new ExtendedIsotopicEnvelope (scanNumber, elutionTime, isotopicEnvelope );
        isotopicEnvelopes.push_back(e);
#ifdef ORIG
        setMass(isotopicEnvelopes.Select([&] (std::any b) {
            b::isotopicEnvelope::monoisotopicMass;
                }).Average());
#endif
        double avg = 0.0, dsum=0.0;
        int count=0;
        std::for_each(isotopicEnvelopes.begin(), isotopicEnvelopes.end(), [&](ExtendedIsotopicEnvelope *b ){
                count++;
                dsum += b->isotopicEnvelope->monoisotopicMass;
            });
        avg = dsum / (double)count;
        setMass(avg);
        
#ifdef ORIG
        setNumPeaks(isotopicEnvelopes.Select([&] (std::any b) {
            b::isotopicEnvelope::peaks->Count;
        }).Sum());
#endif
        int sum=0;
        std::for_each(isotopicEnvelopes.begin(), isotopicEnvelopes.end(), [&](ExtendedIsotopicEnvelope *b ){
                sum += (int) (b->isotopicEnvelope->peaks.size());
            });
        setNumPeaks(sum);
    }
}
