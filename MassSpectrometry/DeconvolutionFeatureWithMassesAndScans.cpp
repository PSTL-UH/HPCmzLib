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

    int DeconvolutionFeatureWithMassesAndScans::getNumPeaks() const {
        return groups.Select([&] (std::any b) {
            b::NumPeaks;
        }).Sum();
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

    double DeconvolutionFeatureWithMassesAndScans::getTotalIntensity() const {
        return privateTotalIntensity;
    }

    void DeconvolutionFeatureWithMassesAndScans::setTotalIntensity(double value) {
        privateTotalIntensity = value;
    }

    std::string DeconvolutionFeatureWithMassesAndScans::ToString() {
        StringBuilder *sb = new StringBuilder();
        sb->append(OneLineString());
        for (auto heh : groups.OrderBy([&] (std::any b) {
            -b::NumPeaks;
        })) {
            sb->appendLine();
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
            sb->append("  " + heh.ToString());
        }

        delete sb;
        return sb->toString();
    }

    std::string DeconvolutionFeatureWithMassesAndScans::OneLineString() {
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
        return getMass().ToString("G8") + "\t"
            + getNumPeaks() + "\t"
            + (getMaxScanIndex() - getMinScanIndex() + 1) + "\t"
            + getMinScanIndex() + "\t"
            + getMaxScanIndex() + "\t"
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
            + ((getMinElutionTime() + getMaxElutionTime()) / 2).ToString("F2") + "\t"
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
            + getTotalIntensity().ToString("E5") + "\t"
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
            + std::wstring::Join(",", (std::unordered_set<int>(groups.SelectMany([&] (std::any b) {
                b::AllCharges;
            })))->OrderBy([&] (std::any b) {
                return b;
            })) + "\t" + groups.OrderByDescending([&] (std::any b) {
                b::MostIntenseEnvelope::totalIntensity;
            }).First().MostIntenseEnvelope.ToString();
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

//C# TO C++ CONVERTER TODO TASK: A 'delete newMassGroup' statement was not added since newMassGroup was passed to a method or constructor. Handle memory management manually.
        }

        setMass(groups.OrderBy([&] (std::any b) {
            -b::NumPeaks;
        }).First().Mass);
        setTotalIntensity(getTotalIntensity() + isotopicEnvelope->peaks.Sum([&] (std::any b) {
            b::Item2;
        }));
    }
}
