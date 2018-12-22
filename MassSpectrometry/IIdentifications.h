#pragma once

#include <string>
#include <vector>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace MzLibUtil { class Tolerance; }

using namespace MzLibUtil;

namespace MassSpectrometry {
    class IIdentifications {
//        #region Public Properties

    public:
        virtual int getCount() const = 0;

        virtual Tolerance *getParentTolerance() const = 0;

        virtual Tolerance *getFragmentTolerance() const = 0;

//        #endregion Public Properties

//        #region Public Methods

        virtual std::wstring Ms2SpectrumID(int matchIndex) = 0;

        virtual int ChargeState(int matchIndex, int siiIndex) = 0;

        virtual std::vector<float> MatchedIons(int matchIndex, int siiIndex, int i) = 0;

        virtual int MatchedIonCounts(int matchIndex, int siiIndex, int i) = 0;

        virtual std::wstring ProteinAccession(int matchIndex, int siiIndex) = 0;

        virtual std::wstring ProteinFullName(int matchIndex, int siiIndex) = 0;

        virtual std::wstring StartResidueInProtein(int matchIndex, int siiIndex) = 0;

        virtual std::wstring EndResidueInProtein(int matchIndex, int siiIndex) = 0;

        virtual bool IsDecoy(int matchIndex, int siiIndex) = 0;

        virtual double QValue(int matchIndex, int siiIndex) = 0;

        virtual double CalculatedMassToCharge(int matchIndex, int siiIndex) = 0;

        virtual double ExperimentalMassToCharge(int matchIndex, int siiIndex) = 0;

        virtual std::wstring PeptideSequenceWithoutModifications(int matchIndex, int siiIndex) = 0;

        virtual int NumModifications(int matchIndex, int siiIndex) = 0;

        virtual int ModificationLocation(int matchIndex, int siiIndex, int i) = 0;

        virtual std::wstring ModificationDictionary(int matchIndex, int siiIndex, int i) = 0;

        virtual std::wstring ModificationAcession(int matchIndex, int siiIndex, int i) = 0;

        virtual int NumPSMsFromScan(int matchIndex) = 0;

        virtual double ModificationMass(int matchIndex, int siiIndex, int i) = 0;

        virtual std::wstring ModificationValue(int matchIndex, int siiIndex, int i) = 0;

//        #endregion Public Methods
    };
}
