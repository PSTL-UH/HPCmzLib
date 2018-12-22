#pragma once

#include "../Proteomics/Interfaces/IProtease.h"
#include <string>
#include <unordered_set>
#include <vector>
#include "exceptionhelper.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Proteomics { class Peptide; }
namespace Proteomics { class DigestionPointAndLength; }
namespace Proteomics { class AminoAcidPolymer; }

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

using namespace Chemistry;
using namespace MzLibUtil;
using namespace NUnit::Framework;
using namespace Proteomics;

namespace Test {
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [TestFixture] public sealed class TestPeptides
    class TestPeptides final {
//        #region Private Fields

    private:
        Peptide *_mockPeptideEveryAminoAcid;
        Peptide *_mockTrypticPeptide;

//        #endregion Private Fields

//        #region Public Methods

    public:
        virtual ~TestPeptides() {
            delete _mockPeptideEveryAminoAcid;
            delete _mockTrypticPeptide;
        }

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [SetUp] public void SetUp()
        void SetUp();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void PeptideTestReal()
        void PeptideTestReal();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void PeptideMassGlycine()
        void PeptideMassGlycine();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void AApolymerNullEquals()
        void AApolymerNullEquals();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void PeptideCountElements()
        void PeptideCountElements();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void PeptideMassTryptic()
        void PeptideMassTryptic();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void PeptideAminoAcidCount()
        void PeptideAminoAcidCount();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void ParseNTerminalChemicalFormula()
        void ParseNTerminalChemicalFormula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void ParseCTerminalChemicalFormula()
        void ParseCTerminalChemicalFormula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void ParseCTerminalChemicalFormulaWithLastResidueMod()
        void ParseCTerminalChemicalFormulaWithLastResidueMod();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void ParseCTerminalChemicalFormulaWithLastResidueModStringRepresentation()
        void ParseCTerminalChemicalFormulaWithLastResidueModStringRepresentation();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void ParseNAndCTerminalChemicalFormula()
        void ParseNAndCTerminalChemicalFormula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void EmptyStringPeptideConstructorLength()
        void EmptyStringPeptideConstructorLength();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void EmptyStringPeptideConstructorToString()
        void EmptyStringPeptideConstructorToString();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void ParseDoubleModificationToString()
        void ParseDoubleModificationToString();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void ParseNamedChemicalModificationInvalidName()
        void ParseNamedChemicalModificationInvalidName();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void SetAminoAcidModification()
        void SetAminoAcidModification();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void SetAminoAcidModificationStronglyTyped()
        void SetAminoAcidModificationStronglyTyped();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void SetAminoAcidModificationStronglyTypedMultipleLocations()
        void SetAminoAcidModificationStronglyTypedMultipleLocations();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void SetAminoAcidModificationStronglyTypedAny()
        void SetAminoAcidModificationStronglyTypedAny();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void SetAminoAcidModificationStronglyTypedAll()
        void SetAminoAcidModificationStronglyTypedAll();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void SetAminoAcidModificationStronglyTypedNone()
        void SetAminoAcidModificationStronglyTypedNone();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void SetAminoAcidModificationStronglyTypedTermini()
        void SetAminoAcidModificationStronglyTypedTermini();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void SetAminoAcidCharacterModification()
        void SetAminoAcidCharacterModification();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void SetResiduePositionModification()
        void SetResiduePositionModification();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void SetResiduePositionModificationOutOfRangeUpper()
        void SetResiduePositionModificationOutOfRangeUpper();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void SetResiduePositionModificationOutOfRangeLower()
        void SetResiduePositionModificationOutOfRangeLower();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void SetCTerminusModStringRepresentation()
        void SetCTerminusModStringRepresentation();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void SetCTerminusModStringRepresentationofChemicalModification()
        void SetCTerminusModStringRepresentationofChemicalModification();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void SetNAndCTerminusMod()
        void SetNAndCTerminusMod();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void SetSameNAndCTerminusMod()
        void SetSameNAndCTerminusMod();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void ClearNTerminusMod()
        void ClearNTerminusMod();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void ClearCTerminusMod()
        void ClearCTerminusMod();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void ClearAllMods()
        void ClearAllMods();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void ClearModificationsBySites()
        void ClearModificationsBySites();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void EmptyPeptideLengthIsZero()
        void EmptyPeptideLengthIsZero();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void EmptyPeptideSequenceIsEmpty()
        void EmptyPeptideSequenceIsEmpty();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void EmptyPeptideFormulaIsH2O()
        void EmptyPeptideFormulaIsH2O();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void PeptideEquality()
        void PeptideEquality();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void PeptideInEqualityAminoAcidSwitch()
        void PeptideInEqualityAminoAcidSwitch();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void PeptideInEqualityAminoAcidModification()
        void PeptideInEqualityAminoAcidModification();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void PeptideCloneEquality()
        void PeptideCloneEquality();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void PeptideCloneNotSameReference()
        void PeptideCloneNotSameReference();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void PeptideCloneWithModifications()
        void PeptideCloneWithModifications();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void PeptideCloneWithoutModifications()
        void PeptideCloneWithoutModifications();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void PeptideCloneWithModification()
        void PeptideCloneWithModification();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void PeptideParitalCloneInternal()
        void PeptideParitalCloneInternal();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void PeptideParitalClonelWithInternalModification()
        void PeptideParitalClonelWithInternalModification();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void PeptideHashing()
        void PeptideHashing();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void ClearMods()
        void ClearMods();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void PeptideParitalClonelWithInternalModificationTwoMods()
        void PeptideParitalClonelWithInternalModificationTwoMods();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void PeptideParitalCloneInternalWithCTerminusModification()
        void PeptideParitalCloneInternalWithCTerminusModification();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void GetLeucineSequence()
        void GetLeucineSequence();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void GetLeucineSequenceNoReplacement()
        void GetLeucineSequenceNoReplacement();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void GetSequenceCoverage()
        void GetSequenceCoverage();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void GenerateIsotopologues()
        void GenerateIsotopologues();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void GetSequenceCoverageFraction()
        void GetSequenceCoverageFraction();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void TerminusModification()
        void TerminusModification();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void DigestionTest()
        void DigestionTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void TestChemicalFormula()
        void TestChemicalFormula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void TestChemicalFormula2()
        void TestChemicalFormula2();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void TestMultipleModificationsAtSingleResidue()
        void TestMultipleModificationsAtSingleResidue();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void TestAApolymerContains()
        void TestAApolymerContains();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void TestLeucineSequence()
        void TestLeucineSequence();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void TestClearModifications()
        void TestClearModifications();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void TestGetSubPeptide()
        void TestGetSubPeptide();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void TestRealPeptideWithModifications()
        void TestRealPeptideWithModifications();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void TestGetDigestionPointsWithMethionine()
        void TestGetDigestionPointsWithMethionine();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void TestGetDigestionPointsWithMethionineAndSemiDigestion()
        void TestGetDigestionPointsWithMethionineAndSemiDigestion();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void BadSeqeunce()
        void BadSeqeunce();

//        #endregion Public Methods

//        #region Private Classes

    private:
        class OkComparer : public IEqualityComparer<DigestionPointAndLength*> {
//            #region Public Methods

        public:
            bool Equals(DigestionPointAndLength *x, DigestionPointAndLength *y) override;

            int GetHashCode(DigestionPointAndLength *obj) override;

//            #endregion Public Methods
        };

//        #endregion Private Classes
    };

    class TestProtease : public IProtease {
//        #region Public Methods

    public:
        std::vector<int> GetDigestionSites(AminoAcidPolymer *aminoAcidSequence) override;

        std::vector<int> GetDigestionSites(const std::wstring &aminoAcidSequence) override;

        int MissedCleavages(AminoAcidPolymer *aminoAcidSequence) override;

        int MissedCleavages(const std::wstring &sequence) override;

//        #endregion Public Methods
    };
}
