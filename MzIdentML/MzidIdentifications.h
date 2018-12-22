#pragma once

#include "../MassSpectrometry/IIdentifications.h"
#include <string>
#include <vector>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace mzIdentML { namespace Generated { class MzIdentMLType; } }
namespace mzIdentML110 { namespace Generated { class MzIdentMLType; } }
namespace MzLibUtil { class Tolerance; }

// Copyright 2016 Stefan Solntsev
//
// This file (MzidIdentifications.cs) is part of MassSpecFiles.
//
// MassSpecFiles is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MassSpecFiles is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with MassSpecFiles. If not, see <http://www.gnu.org/licenses/>.

using namespace MassSpectrometry;
using namespace MzLibUtil;

namespace MzIdentML {
    class MzidIdentifications : public IIdentifications {
//        #region Private Fields

    private:
        mzIdentML::Generated::MzIdentMLType *const dd;
        mzIdentML110::Generated::MzIdentMLType *const dd110;

//        #endregion Private Fields

//        #region Public Constructors

    public:
        virtual ~MzidIdentifications() {
            delete dd;
            delete dd110;
        }

        MzidIdentifications(const std::wstring &mzidFile);

//        #endregion Public Constructors

//        #region Public Properties

        Tolerance *getParentTolerance() const override;

        Tolerance *getFragmentTolerance() const override;

        int getCount() const override;

//        #endregion Public Properties

//        #region Public Methods

        double CalculatedMassToCharge(int sirIndex, int siiIndex) override;

        int ChargeState(int sirIndex, int siiIndex) override;

        double ExperimentalMassToCharge(int sirIndex, int siiIndex) override;

        bool IsDecoy(int sirIndex, int siiIndex) override;

        double QValue(int sirIndex, int siiIndex) override;

        int NumPSMsFromScan(int sirIndex) override;

        std::wstring ModificationAcession(int sirIndex, int siiIndex, int i) override;

        std::wstring ModificationValue(int sirIndex, int siiIndex, int i) override;

        std::wstring ModificationDictionary(int sirIndex, int siiIndex, int i) override;

        int ModificationLocation(int sirIndex, int siiIndex, int i) override;

        double ModificationMass(int sirIndex, int siiIndex, int i) override;

        int NumModifications(int sirIndex, int siiIndex) override;

        std::wstring PeptideSequenceWithoutModifications(int sirIndex, int siiIndex) override;

        std::wstring Ms2SpectrumID(int sirIndex) override;

        std::vector<float> MatchedIons(int sirIndex, int siiIndex, int i) override;

        int MatchedIonCounts(int sirIndex, int siiIndex, int i) override;

        std::wstring ProteinAccession(int sirIndex, int siiIndex) override;

        std::wstring ProteinFullName(int sirIndex, int siiIndex) override;

        std::wstring StartResidueInProtein(int sirIndex, int siiIndex) override;

        std::wstring EndResidueInProtein(int sirIndex, int siiIndex) override;

//        #endregion Public Methods
    };
}
