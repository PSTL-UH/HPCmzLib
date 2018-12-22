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

//        #region Private Fields

        std::vector<IsotopicEnvelope*> isotopicEnvelopes = std::vector<IsotopicEnvelope*>();

//        #endregion Private Fields

//        #region Public Properties

    public:
        double getMass() const;
        void setMass(double value);

        int getNumPeaks() const;
        void setNumPeaks(int value);

        IsotopicEnvelope *getMostIntenseEnvelope() const;

        std::vector<int> getAllCharges() const;

//        #endregion Public Properties

//        #region Public Methods

        std::wstring ToString() override;

//        #endregion Public Methods

//        #region Internal Methods

        void AddEnvelope(IsotopicEnvelope *isotopicEnvelope);

//        #endregion Internal Methods
    };
}
