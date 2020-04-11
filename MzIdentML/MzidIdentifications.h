#pragma once

#include "../MassSpectrometry/IIdentifications.h"
#include <string>
#include <vector>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
#include "mzIdentML110.h"
#include "mzIdentML111.h"
#include "mzIdentML120.h"
#include "Tolerance.h"

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

namespace MzIdentML
{
    class MzidIdentifications : public IIdentifications
    {

    private:
        mzIdentML110::MzIdentMLType *dd110;
        mzIdentML111::MzIdentMLType *dd111;
        mzIdentML120::MzIdentMLType *dd120;

    public:
        virtual ~MzidIdentifications()
        {
            delete dd110;
            delete dd111;
            delete dd120;
        }

        MzidIdentifications(const std::string &mzidFile);

        Tolerance *getParentTolerance() const override;

        Tolerance *getFragmentTolerance() const override;

        int getCount() const override;

        double CalculatedMassToCharge(int sirIndex, int siiIndex) override;

        int ChargeState(int sirIndex, int siiIndex) override;

        double ExperimentalMassToCharge(int sirIndex, int siiIndex) override;

        bool IsDecoy(int sirIndex, int siiIndex) override;

        double QValue(int sirIndex, int siiIndex) override;

        int NumPSMsFromScan(int sirIndex) override;

        std::string ModificationAcession(int sirIndex, int siiIndex, int i) override;

        std::string ModificationValue(int sirIndex, int siiIndex, int i) override;

        std::string ModificationDictionary(int sirIndex, int siiIndex, int i) override;

        int ModificationLocation(int sirIndex, int siiIndex, int i) override;

        double ModificationMass(int sirIndex, int siiIndex, int i) override;

        int NumModifications(int sirIndex, int siiIndex) override;

        std::string PeptideSequenceWithoutModifications(int sirIndex, int siiIndex) override;

        std::string Ms2SpectrumID(int sirIndex) override;

        std::vector<float> MatchedIons(int sirIndex, int siiIndex, int i) override;

        int MatchedIonCounts(int sirIndex, int siiIndex, int i) override;

        std::string ProteinAccession(int sirIndex, int siiIndex) override;

        std::string ProteinFullName(int sirIndex, int siiIndex) override;

        std::string StartResidueInProtein(int sirIndex, int siiIndex) override;

        std::string EndResidueInProtein(int sirIndex, int siiIndex) override;

    };
}
