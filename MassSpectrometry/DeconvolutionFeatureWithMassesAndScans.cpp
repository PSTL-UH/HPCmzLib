#include <algorithm>
#include <string>
#include <iostream>

#include "DeconvolutionFeatureWithMassesAndScans.h"
#include "DeconvolutionFeature.h"
#include "MzSpectra/IsotopicEnvelope.h"
#include "Math.h"

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
#ifdef ORIG        
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
#endif
        double tmp  = std::pow(getTotalNormalizedIntensity(), 0.1);
        double tmp1 = std::pow(std::max((getMaxElutionTime() - getMinElutionTime() * 60), 1.0), 0.1);
        double tmp2 = 1.0;

        double tmp3;
        int sum=0;
        std::for_each(groups.begin(), groups.end(), [&] ( DeconvolutionFeature *b ){
                sum +=  b->getNumPeaks();
            });
        tmp3 = std::pow( (sum/(getMaxScanIndex() - getMinScanIndex() + 1)),1);
        return  std::log (tmp * tmp1 * tmp2 * tmp3);            
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
        
        //The ToString() method of DeconvolutionFeature has been removed in the last version.
        // Need to restore if this is important.
        std::cout << "EG WARNING: DeconvolutionFeatureWithMassesAndScans->ToString is incomplete" << std::endl;

        //for (auto heh: groups) {
        //   sb->appendLine();
            //sb->append("  " + heh->ToString());
        // }

        std::string s = sb->toString();
        delete sb;
        return s;
    }

    std::string DeconvolutionFeatureWithMassesAndScans::OneLineString() {
        //std::vector<(double elutionTime, double intensity)*> elutionTimeAndIntensity;
        std::vector<std::tuple<double, double>> elutionTimeAndIntensity;

#ifdef ORIG
        // EG: The C++ code generated by the convertor does not really make sense. 
        for ( * : groups.SelectMany([&] (std::any b)
        {
            b::isotopicEnvelopes;
        }).Where([&] (std::any b)
        {
            return b::isotopicEnvelope->charge == getMostIntenseEnvelope()->charge;
        }));
            
        // Here is the original C# code
        //foreach (var (scanNumber, elutionTime, isotopicEnvelope) in groups.SelectMany(
        //             b => b.isotopicEnvelopes).Where(
        //             b => b.isotopicEnvelope.charge == MostIntenseEnvelope.charge))
        //        elutionTimeAndIntensity.Add((elutionTime, isotopicEnvelope.totalIntensity));
#endif
        int MostIntenseEnvelopeCharge = getMostIntenseEnvelope()->charge;   
        std::for_each(groups.begin(), groups.end(), [&] (DeconvolutionFeature *b) {
                std::for_each(b->isotopicEnvelopes.begin(), b->isotopicEnvelopes.end(), [&] (ExtendedIsotopicEnvelope *e) {
                if ( e->isotopicEnvelope->totalIntensity == MostIntenseEnvelopeCharge) {
                    elutionTimeAndIntensity.push_back(std::make_tuple(e->elutionTime, e->isotopicEnvelope->totalIntensity));
                }});
        });

#ifdef ORIG            
        int maxCharge = groups.SelectMany([&] (std::any p)
        {
            p::AllCharges;
        }).Max();
#endif
        int maxCharge =0;
        std::for_each (groups.begin(), groups.end(), [&] ( DeconvolutionFeature *b) {
                auto v = b->getAllCharges();
                std::for_each ( v.begin(), v.end(), [&] (int i)  {
                        if ( i > maxCharge ) {
                            maxCharge = i;
                        }
                });
        });

#ifdef ORIF
        auto t = groups.SelectMany([&] (std::any p)
        {
            p::isotopicEnvelopes;
        });
#endif
        
        std::vector<ExtendedIsotopicEnvelope *> t;
        std::for_each (groups.begin(), groups.end(), [&] ( DeconvolutionFeature *b) {
                std::for_each ( b->isotopicEnvelopes.begin(), b->isotopicEnvelopes.end(), [&] (ExtendedIsotopicEnvelope *e) {
                        t.push_back (e);
                });
        });        

        std::string elutionString = "";
        for (int z = 1; z <= maxCharge; z++)
        {
            std::string str = "[" + std::to_string(z) + "|";
#ifdef ORIG
            auto isotopicEnvelopes = t->Where([&] (std::any p)
            {
                return p::isotopicEnvelope->charge == z;
            });
#endif
            std::vector<ExtendedIsotopicEnvelope *> isotopicEnvelopes;
            std::for_each (t.begin(), t.end(), [&] (ExtendedIsotopicEnvelope *e ) {
                    if ( e->isotopicEnvelope->charge == z ) {
                        isotopicEnvelopes.push_back (e);
                    }
            });
            
#ifdef ORIG
            // C++ autogenerated code does not look correct at all.
            for (auto : isotopicEnvelopes)
            {
                str += std::round(elutionTime * std::pow(10, 2)) / std::pow(10, 2) + ";" + isotopicEnvelope::totalIntensity + ",";
            }
            // Here is the original C# code
            //foreach (var (scanNumber, elutionTime, isotopicEnvelope) in isotopicEnvelopes)
            //{
            //    str += Math.Round(elutionTime, 2) + ";" + isotopicEnvelope.totalIntensity + ",";
            // }
#endif
            std::for_each ( isotopicEnvelopes.begin(), isotopicEnvelopes.end(), [&] (ExtendedIsotopicEnvelope *e) {
                    str += std::to_string(Math::Round(e->elutionTime, 2));
                    str += ";" + std::to_string(e->isotopicEnvelope->totalIntensity) + ",";
            });
            str += "]";            

            elutionString += str;
        }

#ifdef ORIG
        auto elutionOfMostIntenseCharge = std::string::Join(";", elutionTimeAndIntensity.OrderBy([&] (std::any b)
        {
            b::elutionTime;
        })->Select([&] (std::any b)
        {
            b::intensity;
        }));
#endif
        std::string elutionOfMostIntenseCharge;
        std::sort (elutionTimeAndIntensity.begin(), elutionTimeAndIntensity.end(), [&] (std::tuple<double,double> &l, std::tuple<double, double> &r)  {
                return std::get<0>(l) > std::get<0>(r);
            });
        std::for_each ( elutionTimeAndIntensity.begin() ,elutionTimeAndIntensity.end(), [&] (std::tuple<double,double> &eb )  {
                elutionOfMostIntenseCharge += std::to_string ( std::get<1>(eb));
            });
            
        std::string s1 = std::to_string(getMass()) + "\t"
            + std::to_string(getScore()) + "\t"
            + std::to_string(getNumPeaks()) + "\t"
            + std::to_string((getMaxScanIndex() - getMinScanIndex() + 1)) + "\t"
            + std::to_string(getMinScanIndex()) + "\t"
            + std::to_string(getMaxScanIndex()) + "\t"
            + std::to_string(getMinElutionTime()) + "\t"
            + std::to_string(getMaxElutionTime()) + "\t"
            + std::to_string(getTotalNormalizedIntensity()) + "\t";
#ifdef ORIG
        + std::string::Join(",", (std::unordered_set<int>(groups.SelectMany([&] (std::any b)
            {
                b::AllCharges;
            })))->OrderBy([&] (std::any b)
           {
                return b;
            })) + "\t" + (getMostIntenseEnvelopeElutionTime()).ToString("F2") + "\t"
            + getMostIntenseEnvelope()->ToString() + StringHelper::toString('\t')
            + elutionOfMostIntenseCharge + StringHelper::toString('\t') + elutionString;
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
        std::string s3 = std::to_string(getMostIntenseEnvelopeElutionTime()) + "\t"
            + getMostIntenseEnvelope()->ToString() + std::to_string('\t') 
            + elutionOfMostIntenseCharge + std::to_string('\t')
            + elutionString;

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
                massGroup->AddEnvelope(scanIndex, elutionTime, isotopicEnvelope);
                added = true;
                break;
            }
        }
        if (!added) {
            auto newMassGroup = new DeconvolutionFeature();
            newMassGroup->AddEnvelope(scanIndex, elutionTime, isotopicEnvelope);
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

        setTotalNormalizedIntensity(getTotalNormalizedIntensity() + isotopicEnvelope->totalIntensity / isotopicEnvelope->charge);

        if (getMostIntenseEnvelope() == nullptr || getMostIntenseEnvelope()->totalIntensity < isotopicEnvelope->totalIntensity)
        {
            setMostIntenseEnvelope(isotopicEnvelope);
            setMostIntenseEnvelopeElutionTime(elutionTime);
        }


    }
}
