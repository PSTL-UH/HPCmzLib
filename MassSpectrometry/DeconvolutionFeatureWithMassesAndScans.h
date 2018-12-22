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

//        #region Private Fields

        std::vector<DeconvolutionFeature*> groups = std::vector<DeconvolutionFeature*>();

//        #endregion Private Fields

//        #region Public Constructors

    public:
        DeconvolutionFeatureWithMassesAndScans();

//        #endregion Public Constructors

//        #region Public Properties

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

//        #endregion Public Properties

//        #region Public Methods

        std::wstring ToString() override;

        std::wstring OneLineString();

        void AddEnvelope(IsotopicEnvelope *isotopicEnvelope, int scanIndex, double elutionTime);

//        #endregion Public Methods
    };
}
