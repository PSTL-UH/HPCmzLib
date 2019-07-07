#include <algorithm>
#include "DeconvolutionFeature.h"
#include "MzSpectra/IsotopicEnvelope.h"


namespace MassSpectrometry {

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
            b::charge;
        }).ToList();
#endif
        std::vector<int> v;
        std::for_each (isotopicEnvelopes.begin(), isotopicEnvelopes.end(), [&](IsotopicEnvelope *e){
                v.push_back ( e->charge);
            });        
        return v;
    }


    void DeconvolutionFeature::AddEnvelope(IsotopicEnvelope *isotopicEnvelope) {
        isotopicEnvelopes.push_back(isotopicEnvelope);
#ifdef ORIG
        setMass(isotopicEnvelopes.Select([&] (std::any b) {
            b::monoisotopicMass;
                }).Average());
#endif
        double avg = 0.0, dsum=0.0;
        int count=0;
        std::for_each(isotopicEnvelopes.begin(), isotopicEnvelopes.end(), [&](IsotopicEnvelope *b ){
                count++;
                dsum += b->monoisotopicMass;
            });
        avg = dsum / (double)count;
        setMass(avg);
        
#ifdef ORIG
        setNumPeaks(isotopicEnvelopes.Select([&] (std::any b) {
            b::peaks->Count;
        }).Sum());
#endif
        int sum=0;
        std::for_each(isotopicEnvelopes.begin(), isotopicEnvelopes.end(), [&](IsotopicEnvelope *b ){
                sum += (int) (b->peaks.size());
            });
        setNumPeaks(sum);
    }
}
