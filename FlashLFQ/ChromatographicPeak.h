#pragma once

#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <cmath>
#include "stringhelper.h"
#include "stringbuilder.h"

#include "IsotopicEnvelope.h"
#include "Identification.h"
#include "SpectraFileInfo.h"

#include "../Chemistry/Chemistry.h"
using namespace Chemistry;

namespace FlashLFQ
{
    class ChromatographicPeak
    {
    private:
        IsotopicEnvelope *privateApex;
        std::vector<Identification*> privateIdentifications;
        int privateNumChargeStatesObserved = 0;
        int privateNumIdentificationsByBaseSeq = 0;
        int privateNumIdentificationsByFullSeq = 0;
        double privateMassError = 0;

    public:
        double Intensity = 0;
        SpectraFileInfo *const spectraFileInfo;
        std::vector<IsotopicEnvelope*> IsotopicEnvelopes;
        double SplitRT = 0;
        const bool IsMbrPeak;

        virtual ~ChromatographicPeak()
        {
            // delete SpectraFileInfo;
        }

        ChromatographicPeak(Identification *id, bool isMbrPeak, SpectraFileInfo *fileInfo);

        IsotopicEnvelope *getApex() const;
        void setApex(IsotopicEnvelope *value);
        std::vector<Identification*> getIdentifications() const;
        void setIdentifications(const std::vector<Identification*> &value);
        int getNumChargeStatesObserved() const;
        void setNumChargeStatesObserved(int value);
        int getNumIdentificationsByBaseSeq() const;
        void setNumIdentificationsByBaseSeq(int value);
        int getNumIdentificationsByFullSeq() const;
        void setNumIdentificationsByFullSeq(int value);
        double getMassError() const;
        void setMassError(double value);

        static std::string getTabSeparatedHeader();

        void CalculateIntensityForThisFeature(bool integrate);

        void MergeFeatureWith(ChromatographicPeak *otherFeature, bool integrate);

        void ResolveIdentifications();
        std::string ToString();
    };
}
