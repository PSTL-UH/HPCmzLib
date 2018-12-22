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
        return isotopicEnvelopes.OrderByDescending([&] (std::any b) {
            b::totalIntensity;
        }).First();
    }

    std::vector<int> DeconvolutionFeature::getAllCharges() const {
        return isotopicEnvelopes.Select([&] (std::any b) {
            b::charge;
        }).ToList();
    }

    std::wstring DeconvolutionFeature::ToString() {
        StringBuilder *sb = new StringBuilder();
        sb->append(L" Mass: " + std::to_wstring(getMass()) + L" NumPeaks: " + std::to_wstring(getNumPeaks()));
        for (auto heh : isotopicEnvelopes.OrderBy([&] (std::any b) {
            -b::peaks->Count;
        })) {
            sb->appendLine();
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
            sb->append(L"     " + heh.ToString());
        }

        delete sb;
        return sb->toString();
    }

    void DeconvolutionFeature::AddEnvelope(IsotopicEnvelope *isotopicEnvelope) {
        isotopicEnvelopes.push_back(isotopicEnvelope);
        setMass(isotopicEnvelopes.Select([&] (std::any b) {
            b::monoisotopicMass;
        }).Average());
        setNumPeaks(isotopicEnvelopes.Select([&] (std::any b) {
            b::peaks->Count;
        }).Sum());
    }
}
