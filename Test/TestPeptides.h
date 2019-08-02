#pragma once

#include <string>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <any>
#include "exceptionhelper.h"
#include "stringhelper.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Test { class TestChemicalFormula; }

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

#include "MzLibUtil.h"
using namespace MzLibUtil;

#include "../Proteomics/AminoAcidPolymer/AminoAcidPolymer.h"
#include "../Proteomics/AminoAcidPolymer/Peptide.h"
#include "../Proteomics/AminoAcidPolymer/ChemicalFormulaModification.h"
#include "../Proteomics/AminoAcidPolymer/ChemicalFormulaTerminus.h"
using namespace Proteomics::AminoAcidPolymer;

#include "../Proteomics/Fragmentation/Fragmentation.h"
using namespace Proteomics::Fragmentation;

#include "../Proteomics/ProteolyticDigestion/ProteinDigestion.h"
using namespace Proteomics::ProteolyticDigestion;

namespace Test
{
    class TestPeptides final
    {
    private:

    public:

        static void PeptideTestReal();

        static void PeptideMassGlycine();

        static void AApolymerNullEquals();

        static void PeptideCountElements();

        static void PeptideMassTryptic();

        static void PeptideAminoAcidCount();

        static void ParseNTerminalChemicalFormula();

        static void ParseCTerminalChemicalFormula();

        static void ParseCTerminalChemicalFormulaWithLastResidueMod();

        static void ParseCTerminalChemicalFormulaWithLastResidueModStringRepresentation();

        static void ParseNAndCTerminalChemicalFormula();

        static void EmptyStringPeptideConstructorLength();

        static void EmptyStringPeptideConstructorToString();

        static void ParseDoubleModificationToString();

        static void ParseNamedChemicalModificationInvalidName();

        static void SetAminoAcidModification();

        static void SetAminoAcidModificationStronglyTyped();

        static void SetAminoAcidModificationStronglyTypedMultipleLocations();

        static void SetAminoAcidModificationStronglyTypedAny();

        static void SetAminoAcidModificationStronglyTypedAll();

        static void SetAminoAcidModificationStronglyTypedNone();

        static void SetAminoAcidModificationStronglyTypedTermini();

        static void SetAminoAcidCharacterModification();

        static void SetResiduePositionModification();

        static void SetResiduePositionModificationOutOfRangeUpper();

        static void SetResiduePositionModificationOutOfRangeLower();

        static void SetCTerminusModStringRepresentation();

        static void SetCTerminusModStringRepresentationofChemicalModification();

        static void SetNAndCTerminusMod();

        static void SetSameNAndCTerminusMod();

        static void ClearNTerminusMod();

        static void ClearCTerminusMod();

        static void ClearAllMods();

        static void ClearModificationsBySites();

        static void EmptyPeptideLengthIsZero();

        static void EmptyPeptideSequenceIsEmpty();

        static void EmptyPeptideFormulaIsH2O();

        static void PeptideEquality();

        static void PeptideInEqualityAminoAcidSwitch();

        static void PeptideInEqualityAminoAcidModification();

        static void PeptideCloneEquality();

        static void PeptideCloneNotSameReference();

        static void PeptideCloneWithModifications();

        static void PeptideCloneWithoutModifications();

        static void PeptideCloneWithModification();

        static void PeptideParitalCloneInternal();

        static void PeptideParitalClonelWithInternalModification();

        static void PeptideHashing();

        static void ClearMods();

        static void PeptideParitalClonelWithInternalModificationTwoMods();

        static void PeptideParitalCloneInternalWithCTerminusModification();

        static void GetLeucineSequence();

        static void GetLeucineSequenceNoReplacement();

        static void GetSequenceCoverage();

        static void GenerateIsotopologues();

        static void GetSequenceCoverageFraction();

        static void TerminusModification();

        static void DigestionTest();

        static void TestChemicalFormula();

        static void TestChemicalFormula2();

        static void TestMultipleModificationsAtSingleResidue();

        static void TestAApolymerContains();

        static void TestLeucineSequence();

        static void TestClearModifications();

        static void TestGetSubPeptide();

        static void TestRealPeptideWithModifications();

        static void TestGetDigestionPointsWithMethionine();

        static void TestGetDigestionPointsWithMethionineAndSemiDigestion();

        static void BadSeqeunce();

        static void TestNonSpecificOverride();

#ifdef LATER
    private:
        class OkComparer : public IEqualityComparer<DigestionPointAndLength*>
        {
        public:
            bool Equals(DigestionPointAndLength *x, DigestionPointAndLength *y) override;

            int GetHashCode(DigestionPointAndLength *obj) override;
        };
    };

    class TestProtease : public IProtease
    {
    public:
        std::vector<int> GetDigestionSites(AminoAcidPolymer *aminoAcidSequence) override;

        std::vector<int> GetDigestionSites(const std::string &aminoAcidSequence) override;

        int MissedCleavages(AminoAcidPolymer *aminoAcidSequence) override;

        int MissedCleavages(const std::string &sequence) override;
#endif
    };
}
