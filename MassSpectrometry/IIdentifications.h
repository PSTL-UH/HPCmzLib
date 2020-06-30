/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
#pragma once

#include <string>
#include <vector>

#include "Tolerance.h"

using namespace MzLibUtil;

namespace MassSpectrometry {
    class IIdentifications {

    public:
        virtual int getCount() const = 0;

        virtual Tolerance *getParentTolerance() const = 0;

        virtual Tolerance *getFragmentTolerance() const = 0;

        virtual std::string Ms2SpectrumID(int matchIndex) = 0;

        virtual int ChargeState(int matchIndex, int siiIndex) = 0;

        virtual std::vector<float> MatchedIons(int matchIndex, int siiIndex, int i) = 0;

        virtual int MatchedIonCounts(int matchIndex, int siiIndex, int i) = 0;

        virtual std::string ProteinAccession(int matchIndex, int siiIndex) = 0;

        virtual std::string ProteinFullName(int matchIndex, int siiIndex) = 0;

        virtual std::string StartResidueInProtein(int matchIndex, int siiIndex) = 0;

        virtual std::string EndResidueInProtein(int matchIndex, int siiIndex) = 0;

        virtual bool IsDecoy(int matchIndex, int siiIndex) = 0;

        virtual double QValue(int matchIndex, int siiIndex) = 0;

        virtual double CalculatedMassToCharge(int matchIndex, int siiIndex) = 0;

        virtual double ExperimentalMassToCharge(int matchIndex, int siiIndex) = 0;

        virtual std::string PeptideSequenceWithoutModifications(int matchIndex, int siiIndex) = 0;

        virtual int NumModifications(int matchIndex, int siiIndex) = 0;

        virtual int ModificationLocation(int matchIndex, int siiIndex, int i) = 0;

        virtual std::string ModificationDictionary(int matchIndex, int siiIndex, int i) = 0;

        virtual std::string ModificationAcession(int matchIndex, int siiIndex, int i) = 0;

        virtual int NumPSMsFromScan(int matchIndex) = 0;

        virtual double ModificationMass(int matchIndex, int siiIndex, int i) = 0;

        virtual std::string ModificationValue(int matchIndex, int siiIndex, int i) = 0;

    };
}
