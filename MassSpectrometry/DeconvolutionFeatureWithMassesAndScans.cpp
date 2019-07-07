#include <algorithm>
#include <string>

#include "DeconvolutionFeatureWithMassesAndScans.h"
#include "DeconvolutionFeature.h"
#include "MzSpectra/IsotopicEnvelope.h"


namespace MassSpectrometry {

    DeconvolutionFeatureWithMassesAndScans::DeconvolutionFeatureWithMassesAndScans() {
        setMinScanIndex(std::numeric_limits<int>::max());

        setMaxScanIndex(std::numeric_limits<int>::min());
        setMinElutionTime(std::numeric_limits<double>::max());

        setMaxElutionTime(std::numeric_limits<double>::lowest());
    }

    int DeconvolutionFeatureWithMassesAndScans::getMinScanIndex() const {
        return privateMinScanIndex;
    }

    void DeconvolutionFeatureWithMassesAndScans::setMinScanIndex(int value) {
        privateMinScanIndex = value;
    }

    int DeconvolutionFeatureWithMassesAndScans::getMaxScanIndex() const {
        return privateMaxScanIndex;
    }

    void DeconvolutionFeatureWithMassesAndScans::setMaxScanIndex(int value) {
        privateMaxScanIndex = value;
    }

    double DeconvolutionFeatureWithMassesAndScans::getMass() const {
        return privateMass;
    }

    void DeconvolutionFeatureWithMassesAndScans::setMass(double value) {
        privateMass = value;
    }

    double DeconvolutionFeatureWithMassesAndScans::getScore() const
    {
        return std::log(std::pow(getTotalNormalizedIntensity(), 0.1) * std::pow(std::max((getMaxElutionTime() - getMinElutionTime() * 60), 1), 0.1) * std::pow(((std::unordered_set<int>(groups.SelectMany([&] (std::any b)

       {
           b::AllCharges;
       })))->OrderBy([&] (std::any b)
       {
           return b;
       }))->Count(), 1) * std::pow(static_cast<double>(groups.Select([&] (std::any b)
       {
           b::NumPeaks;
       }).Sum()) / (getMaxScanIndex() - getMinScanIndex() + 1), 1));
    }
    
    int DeconvolutionFeatureWithMassesAndScans::getNumPeaks() const {
#ifdef ORIG
        return groups.Select([&] (std::any b) {
            b::NumPeaks;
        }).Sum();
#endif
        int sum=0;
        std::for_each(groups.begin(), groups.end(), [&] ( DeconvolutionFeature *b ){
                sum +=  b->getNumPeaks();
            });
        return sum;
    }

    double DeconvolutionFeatureWithMassesAndScans::getMinElutionTime() const {
        return privateMinElutionTime;
    }

    void DeconvolutionFeatureWithMassesAndScans::setMinElutionTime(double value) {
        privateMinElutionTime = value;
    }

    double DeconvolutionFeatureWithMassesAndScans::getMaxElutionTime() const {
        return privateMaxElutionTime;
    }

    void DeconvolutionFeatureWithMassesAndScans::setMaxElutionTime(double value) {
        privateMaxElutionTime = value;
    }
    
    double DeconvolutionFeatureWithMassesAndScans::getTotalNormalizedIntensity() const
    {
        return privateTotalNormalizedIntensity;
    }

    void DeconvolutionFeatureWithMassesAndScans::setTotalNormalizedIntensity(double value)
    {
        privateTotalNormalizedIntensity = value;
    }

    IsotopicEnvelope *DeconvolutionFeatureWithMassesAndScans::getMostIntenseEnvelope() const
    {
        return privateMostIntenseEnvelope;
    }

    void DeconvolutionFeatureWithMassesAndScans::setMostIntenseEnvelope(IsotopicEnvelope *value)
    {
        privateMostIntenseEnvelope = value;
    }

    double DeconvolutionFeatureWithMassesAndScans::getMostIntenseEnvelopeElutionTime() const
    {
        return privateMostIntenseEnvelopeElutionTime;
    }

    void DeconvolutionFeatureWithMassesAndScans::setMostIntenseEnvelopeElutionTime(double value)
    {
        privateMostIntenseEnvelopeElutionTime = value;
    }

    std::string DeconvolutionFeatureWithMassesAndScans::ToString() {
        StringBuilder *sb = new StringBuilder();
        sb->append(OneLineString());
#ifdef ORIG
        for (auto heh : groups.OrderBy([&] (std::any b) {
            -b::NumPeaks;
                }));
        
#endif
        std::sort (groups.begin(), groups.end(), [&](DeconvolutionFeature *l, DeconvolutionFeature *r ){
                // C++ note: using > instead of < to account for the minus in the
                // original code. 
                return l->getNumPeaks() > r->getNumPeaks();
            });
        for (auto heh: groups) {
            sb->appendLine();
            //C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
            sb->append("  " + heh->ToString());
        }

        delete sb;
        return sb->toString();
    }

    std::string DeconvolutionFeatureWithMassesAndScans::OneLineString() {
        std::string s1 =  std::to_string(getMass()) + "\t"
            + std::to_string(getNumPeaks()) + "\t"
            + std::to_string((getMaxScanIndex() - getMinScanIndex() + 1)) + "\t"
            + std::to_string(getMinScanIndex()) + "\t"
            + std::to_string(getMaxScanIndex()) + "\t"
            + std::to_string(((getMinElutionTime() + getMaxElutionTime()) / 2)) + "\t"
            + std::to_string(getTotalIntensity()) + "\t";

#ifdef ORIG        
        std::string s2 = std::string::Join(",", (std::unordered_set<int>(groups.SelectMany([&] (std::any b) {
                b::AllCharges;
                        })))->OrderBy([&] (std::any b) {
                return b;
                 })) + "\t";
#endif
        std::vector<int> v;
        for ( auto g: groups ) {
            std::vector<int> w = g->getAllCharges();
            for ( int  x : w ) {
                v.push_back(x);
            }
        }
        std::sort (v.begin(), v.end());
        std::string s2;
        for ( auto ve : v) {
            s2 += std::to_string(ve) + "\t";
        }
        
#ifdef ORIG
        std:: string s3 = groups.OrderByDescending([&] (std::any b) {
                b::MostIntenseEnvelope::totalIntensity;
            }).First().MostIntenseEnvelope.ToString();
#endif
        std::sort (groups.begin(), groups.end(), [&](DeconvolutionFeature *l, DeconvolutionFeature *r ){
                return l->getMostIntenseEnvelope()->totalIntensity < r->getMostIntenseEnvelope()->totalIntensity;
            });
        std::string s3 = groups[0]->getMostIntenseEnvelope()->ToString();
        
        return s1+s2+s3;
    }

    void DeconvolutionFeatureWithMassesAndScans::AddEnvelope(IsotopicEnvelope *isotopicEnvelope, int scanIndex, double elutionTime) {
        setMinScanIndex(std::min(scanIndex, getMinScanIndex()));
        setMaxScanIndex(std::max(scanIndex, getMaxScanIndex()));
        setMinElutionTime(std::min(elutionTime, getMinElutionTime()));
        setMaxElutionTime(std::max(elutionTime, getMaxElutionTime()));
        bool added = false;
        for (auto massGroup : groups) {
            if (std::abs(massGroup->getMass() - isotopicEnvelope->monoisotopicMass) < 0.5) {
                massGroup->AddEnvelope(isotopicEnvelope);
                added = true;
                break;
            }
        }
        if (!added) {
            auto newMassGroup = new DeconvolutionFeature();
            newMassGroup->AddEnvelope(isotopicEnvelope);
            groups.push_back(newMassGroup);

            // C# TO C++ CONVERTER TODO TASK: A 'delete newMassGroup' statement
            // was not added since newMassGroup was passed to a method or constructor.
            // Handle memory management manually.
        }

#ifdef ORIG
        setMass(groups.OrderBy([&] (std::any b) {
            -b::NumPeaks;
        }).First().Mass);
#endif
        std::sort (groups.begin(), groups.end(), [&](DeconvolutionFeature *l, DeconvolutionFeature *r ){
                // C++ note: using > instead of < to account for the minus in the
                // original code. 
                return l->getNumPeaks() > r->getNumPeaks();
            });
        setMass ( groups[0]->getMass());
        
#ifdef ORIG        
        setTotalIntensity(getTotalIntensity() + isotopicEnvelope->peaks.Sum([&] (std::any b) {
            b::Item2;
        }));
#endif
        double sum=0.0;
        std::for_each(isotopicEnvelope->peaks.begin(), isotopicEnvelope->peaks.end(), [&] (std::tuple<double,double> b) {
                sum += std::get<1>(b);
            });
        setTotalIntensity(getTotalIntensity() + sum);
    }
}
