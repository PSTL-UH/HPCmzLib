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

    IsotopicEnvelope *DeconvolutionFeature::getMostIntenseEnvelope() const {
#ifdef ORIG
        return isotopicEnvelopes.OrderByDescending([&] (std::any b) {
            b::totalIntensity;
        }).First();
#endif
        IsotopicEnvelope *max_elem;
        std::for_each(isotopicEnvelopes.begin(), isotopicEnvelopes.end(), [&](IsotopicEnvelope *e){
                if ( max_elem == nullptr ) {
                    max_elem = e;
                }
                else if ( e->totalIntensity > max_elem->totalIntensity) {
                    max_elem = e;
                }
            });
        return max_elem;
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

    std::string DeconvolutionFeature::ToString() {
        StringBuilder *sb = new StringBuilder();
        sb->append(" Mass: " + std::to_string(getMass()) + " NumPeaks: " + std::to_string(getNumPeaks()));

#ifdef ORIG
        for (auto heh : isotopicEnvelopes.OrderBy([&] (std::any b) {
            -b::peaks->Count;
                }));
#endif
        std::sort (isotopicEnvelopes.begin(), isotopicEnvelopes.end(), [&](IsotopicEnvelope *l, IsotopicEnvelope *r ){
                return l->peaks.size() > r->peaks.size();
            });
        for ( IsotopicEnvelope *heh : isotopicEnvelopes )   {
            sb->appendLine();
            //C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
            sb->append("     " + heh->ToString());
        }

        std::string s = sb->toString();
        delete sb;

        return s;
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
