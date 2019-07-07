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

    public:
        std::vector<(int scanNumber, double elutionTime, IsotopicEnvelope isotopicEnvelope)*> isotopicEnvelopes = std::vector<(int scanNumber, double elutionTime, IsotopicEnvelope isotopicEnvelope)*>();

        double getMass() const;
        void setMass(double value);

        int getNumPeaks() const;
        void setNumPeaks(int value);

        std::vector<int> getAllCharges() const;

        void AddEnvelope(IsotopicEnvelope *isotopicEnvelope);
    };
}
