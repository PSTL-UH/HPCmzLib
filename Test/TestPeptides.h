#pragma once

#include "../Proteomics/Interfaces/IProtease.h"
#include <string>
#include <unordered_set>
#include <vector>
#include "exceptionhelper.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
//namespace Proteomics { class Peptide; }
//namespace Proteomics { class DigestionPointAndLength; }
//namespace Proteomics { class AminoAcidPolymer; }

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work copyright 2016 Stefan Solntsev
//
// This file (TestPeptides.cs) is part of Proteomics.
//
// Proteomics is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Proteomics is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with Proteomics. If not, see <http://www.gnu.org/licenses/>.

#include "../Chemistry/Chemistry.h"
using namespace Chemistry;

#include "../MzLibUtil/MzLibUtil.h"
using namespace MzLibUtil;

//using namespace NUnit::Framework;

#include "../Proteomics/Proteomics.h"
using namespace Proteomics;

namespace Test {
    class TestPeptides final {

    private:
        Peptide *_mockPeptideEveryAminoAcid;
        Peptide *_mockTrypticPeptide;

    public:
        virtual ~TestPeptides() {
            delete _mockPeptideEveryAminoAcid;
            delete _mockTrypticPeptide;
        }

        void SetUp();

        void PeptideTestReal();

        void PeptideMassGlycine();

        void AApolymerNullEquals();

        void PeptideCountElements();

        void PeptideMassTryptic();

        void PeptideAminoAcidCount();

        void ParseNTerminalChemicalFormula();

        void ParseCTerminalChemicalFormula();

        void ParseCTerminalChemicalFormulaWithLastResidueMod();

        void ParseCTerminalChemicalFormulaWithLastResidueModStringRepresentation();

        void ParseNAndCTerminalChemicalFormula();

        void EmptyStringPeptideConstructorLength();

        void EmptyStringPeptideConstructorToString();

        void ParseDoubleModificationToString();

        void ParseNamedChemicalModificationInvalidName();

        void SetAminoAcidModification();

        void SetAminoAcidModificationStronglyTyped();

        void SetAminoAcidModificationStronglyTypedMultipleLocations();

        void SetAminoAcidModificationStronglyTypedAny();

        void SetAminoAcidModificationStronglyTypedAll();

        void SetAminoAcidModificationStronglyTypedNone();

        void SetAminoAcidModificationStronglyTypedTermini();

        void SetAminoAcidCharacterModification();

        void SetResiduePositionModification();

        void SetResiduePositionModificationOutOfRangeUpper();

        void SetResiduePositionModificationOutOfRangeLower();

        void SetCTerminusModStringRepresentation();

        void SetCTerminusModStringRepresentationofChemicalModification();

        void SetNAndCTerminusMod();

        void SetSameNAndCTerminusMod();

        void ClearNTerminusMod();

        void ClearCTerminusMod();

        void ClearAllMods();

        void ClearModificationsBySites();

        void EmptyPeptideLengthIsZero();

        void EmptyPeptideSequenceIsEmpty();

        void EmptyPeptideFormulaIsH2O();

        void PeptideEquality();

        void PeptideInEqualityAminoAcidSwitch();

        void PeptideInEqualityAminoAcidModification();

        void PeptideCloneEquality();

        void PeptideCloneNotSameReference();

        void PeptideCloneWithModifications();

        void PeptideCloneWithoutModifications();

        void PeptideCloneWithModification();

        void PeptideParitalCloneInternal();

        void PeptideParitalClonelWithInternalModification();

        void PeptideHashing();

        void ClearMods();

        void PeptideParitalClonelWithInternalModificationTwoMods();

        void PeptideParitalCloneInternalWithCTerminusModification();

        void GetLeucineSequence();

        void GetLeucineSequenceNoReplacement();

        void GetSequenceCoverage();

        void GenerateIsotopologues();

        void GetSequenceCoverageFraction();

        void TerminusModification();

        void DigestionTest();

        void TestChemicalFormula();

        void TestChemicalFormula2();

        void TestMultipleModificationsAtSingleResidue();

        void TestAApolymerContains();

        void TestLeucineSequence();

        void TestClearModifications();

        void TestGetSubPeptide();

        void TestRealPeptideWithModifications();

        void TestGetDigestionPointsWithMethionine();

        void TestGetDigestionPointsWithMethionineAndSemiDigestion();

        void BadSeqeunce();

    private:
        class OkComparer : public IEqualityComparer<DigestionPointAndLength*> {

        public:
            bool Equals(DigestionPointAndLength *x, DigestionPointAndLength *y) override;

            int GetHashCode(DigestionPointAndLength *obj) override;

        };

    };

    class TestProtease : public IProtease {

    public:
        std::vector<int> GetDigestionSites(AminoAcidPolymer *aminoAcidSequence) override;

        std::vector<int> GetDigestionSites(const std::wstring &aminoAcidSequence) override;

        int MissedCleavages(AminoAcidPolymer *aminoAcidSequence) override;

        int MissedCleavages(const std::wstring &sequence) override;

    };
}
