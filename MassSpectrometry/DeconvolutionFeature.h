#pragma once

#include <string>
#include <vector>
#include "stringbuilder.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace MassSpectrometry { class IsotopicEnvelope; }


namespace MassSpectrometry {
    class DeconvolutionFeature {
    private:
        double privateMass = 0;
        int privateNumPeaks = 0;

        std::vector<IsotopicEnvelope*> isotopicEnvelopes = std::vector<IsotopicEnvelope*>();

    public:
        double getMass() const;
        void setMass(double value);

        int getNumPeaks() const;
        void setNumPeaks(int value);

        IsotopicEnvelope *getMostIntenseEnvelope() const;

        std::vector<int> getAllCharges() const;
        std::string ToString();

        void AddEnvelope(IsotopicEnvelope *isotopicEnvelope);

    };
}
