#pragma once

#include <string>
#include <unordered_set>
#include <vector>
#include <cmath>
#include <limits>
#include "stringbuilder.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace MassSpectrometry { class DeconvolutionFeature; }
namespace MassSpectrometry { class IsotopicEnvelope; }


namespace MassSpectrometry {
    class DeconvolutionFeatureWithMassesAndScans {
    private:
        int privateMinScanIndex = 0;
        int privateMaxScanIndex = 0;
        double privateMass = 0;
        double privateMinElutionTime = 0;
        double privateMaxElutionTime = 0;
        double privateTotalIntensity = 0;

        std::vector<DeconvolutionFeature*> groups = std::vector<DeconvolutionFeature*>();

    public:
        DeconvolutionFeatureWithMassesAndScans();

        int getMinScanIndex() const;
        void setMinScanIndex(int value);

        int getMaxScanIndex() const;
        void setMaxScanIndex(int value);

        double getMass() const;
        void setMass(double value);

        int getNumPeaks() const;

        double getMinElutionTime() const;
        void setMinElutionTime(double value);
        double getMaxElutionTime() const;
        void setMaxElutionTime(double value);
        double getTotalIntensity() const;
        void setTotalIntensity(double value);

        std::string ToString();
        std::string OneLineString();

        void AddEnvelope(IsotopicEnvelope *isotopicEnvelope, int scanIndex, double elutionTime);

    };
}
