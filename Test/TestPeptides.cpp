#include "TestPeptides.h"
#include "../Chemistry/ChemicalFormula.h"
#include "../Chemistry/Isotope.h"
#include "../Chemistry/PeriodicTable.h"
#include "TestMassMzCalculations.h"
#include "../MzLibUtil/MzLibException.h"
#include "../Chemistry/Interfaces/IHasChemicalFormula.h"
#include "TestChemicalFormula.h"

#include "Assert.h"

int main ( int argc, char **argv )
{
    
    int i=0;
    std::cout << i << "PeriodicTableLoader" << std::endl;    
    const std::string elfile="elements.dat";
    const std::string &elr=elfile;
    Chemistry::PeriodicTable::Load (elr);
    
    std::cout <<++i << "TestPeptideTestReal" << std::endl;    
    Test::TestPeptides::PeptideTestReal();
    
    std::cout <<++i << "PeptideMassGlycine" << std::endl;    
    Test::TestPeptides::PeptideMassGlycine();

    std::cout <<++i << "AApolymerNullEquals" << std::endl;    
    Test::TestPeptides::AApolymerNullEquals();

#ifdef LATER
    std::cout <<++i << "PeptideCountElements" << std::endl;    
    Test::TestPeptides::PeptideCountElements();
    
    std::cout <<++i << "PeptideMassTryptic" << std::endl;    
    Test::TestPeptides::PeptideMassTryptic();
    
    std::cout <<++i << "PeptideAminoAcidCount" << std::endl;    
    Test::TestPeptides::PeptideAminoAcidCount();
    
    std::cout <<++i << "ParseNTerminalChemicalFormula" << std::endl;    
    Test::TestPeptides::ParseNTerminalChemicalFormula();
    
    std::cout <<++i << "ParseCTerminalChemicalFormula" << std::endl;    
    Test::TestPeptides::ParseCTerminalChemicalFormula();
    
    std::cout <<++i << "ParseCTerminalChemicalFormulaWithLastResidueMod" << std::endl;    
    Test::TestPeptides::ParseCTerminalChemicalFormulaWithLastResidueMod();

    std::cout <<++i << "ParseCTerminalChemicalFormulaWithLastResidueModStringRepresentation" << std::endl;    
    Test::TestPeptides::ParseCTerminalChemicalFormulaWithLastResidueModStringRepresentation();

    std::cout <<++i << "ParseNAndCTerminalChemicalFormula" << std::endl;    
    Test::TestPeptides::ParseNAndCTerminalChemicalFormula();

    std::cout <<++i << "EmptyStringPeptideConstructorLength" << std::endl;    
    Test::TestPeptides::EmptyStringPeptideConstructorLength();

    std::cout <<++i << "EmptyStringPeptideConstructorToString" << std::endl;    
    Test::TestPeptides::EmptyStringPeptideConstructorToString();

    std::cout <<++i << "ParseDoubleModificationToString" << std::endl;    
    Test::TestPeptides::ParseDoubleModificationToString();

    std::cout <<++i << "ParseNamedChemicalModificationInvalidName" << std::endl;    
    Test::TestPeptides::ParseNamedChemicalModificationInvalidName();

    std::cout <<++i << "SetAminoAcidModification" << std::endl;    
    Test::TestPeptides::SetAminoAcidModification();

    std::cout <<++i << "SetAminoAcidModificationStronglyTyped" << std::endl;    
    Test::TestPeptides::SetAminoAcidModificationStronglyTyped();

    std::cout <<++i << "SetAminoAcidModificationStronglyTypedMultipleLocations" << std::endl;    
    Test::TestPeptides::SetAminoAcidModificationStronglyTypedMultipleLocations();

    std::cout <<++i << "SetAminoAcidModificationStronglyTypedAny" << std::endl;    
    Test::TestPeptides::SetAminoAcidModificationStronglyTypedAny();

    std::cout <<++i << "SetAminoAcidModificationStronglyTypedAll" << std::endl;    
    Test::TestPeptides::SetAminoAcidModificationStronglyTypedAll();

    std::cout <<++i << "SetAminoAcidModificationStronglyTypedNone" << std::endl;    
    Test::TestPeptides::SetAminoAcidModificationStronglyTypedNone();

    std::cout <<++i << "SetAminoAcidModificationStronglyTypedTermini" << std::endl;    
    Test::TestPeptides::SetAminoAcidModificationStronglyTypedTermini();

    std::cout <<++i << "SetAminoAcidCharacterModification" << std::endl;    
    Test::TestPeptides::SetAminoAcidCharacterModification();

    std::cout <<++i << "SetResiduePositionModification" << std::endl;    
    Test::TestPeptides::SetResiduePositionModification();

    std::cout <<++i << "SetResiduePositionModificationOutOfRangeUpper" << std::endl;    
    Test::TestPeptides::SetResiduePositionModificationOutOfRangeUpper();

    std::cout <<++i << "SetResiduePositionModificationOutOfRangeLower" << std::endl;    
    Test::TestPeptides::SetResiduePositionModificationOutOfRangeLower();

    std::cout <<++i << "SetCTerminusModStringRepresentation" << std::endl;    
    Test::TestPeptides::SetCTerminusModStringRepresentation();

    std::cout <<++i << "SetCTerminusModStringRepresentationofChemicalModification" << std::endl;    
    Test::TestPeptides::SetCTerminusModStringRepresentationofChemicalModification();

    std::cout <<++i << "SetNAndCTerminusMod" << std::endl;    
    Test::TestPeptides::SetNAndCTerminusMod();

    std::cout <<++i << "SetSameNAndCTerminusMod" << std::endl;    
    Test::TestPeptides::SetSameNAndCTerminusMod();

    std::cout <<++i << "ClearNTerminusMod" << std::endl;    
    Test::TestPeptides::ClearNTerminusMod();

    std::cout <<++i << "ClearCTerminusMod" << std::endl;    
    Test::TestPeptides::ClearCTerminusMod();

    std::cout <<++i << "ClearAllMods" << std::endl;    
    Test::TestPeptides::ClearAllMods();

    std::cout <<++i << "ClearModificationsBySites" << std::endl;    
    Test::TestPeptides::ClearModificationsBySites();

    std::cout <<++i << "EmptyPeptideLengthIsZero" << std::endl;    
    Test::TestPeptides::EmptyPeptideLengthIsZero();

    std::cout <<++i << "EmptyPeptideSequenceIsEmpty" << std::endl;    
    Test::TestPeptides::EmptyPeptideSequenceIsEmpty();

    std::cout <<++i << "EmptyPeptideFormulaIsH2O" << std::endl;    
    Test::TestPeptides::EmptyPeptideFormulaIsH2O();

    std::cout <<++i << "PeptideEquality" << std::endl;    
    Test::TestPeptides::PeptideEquality();

    std::cout <<++i << "PeptideInEqualityAminoAcidSwitch" << std::endl;    
    Test::TestPeptides::PeptideInEqualityAminoAcidSwitch();

    std::cout <<++i << "PeptideInEqualityAminoAcidModification" << std::endl;    
    Test::TestPeptides::PeptideInEqualityAminoAcidModification();

    std::cout <<++i << "PeptideCloneEquality" << std::endl;    
    Test::TestPeptides::PeptideCloneEquality();

    std::cout <<++i << "PeptideCloneNotSameReference" << std::endl;    
    Test::TestPeptides::PeptideCloneNotSameReference();

    std::cout <<++i << "PeptideCloneWithModifications" << std::endl;    
    Test::TestPeptides::PeptideCloneWithModifications();

    std::cout <<++i << "PeptideCloneWithoutModifications" << std::endl;    
    Test::TestPeptides::PeptideCloneWithoutModifications();

    std::cout <<++i << "PeptideCloneWithModification" << std::endl;    
    Test::TestPeptides::PeptideCloneWithModification();

    std::cout <<++i << "PeptideParitalCloneInternal" << std::endl;    
    Test::TestPeptides::PeptideParitalCloneInternal();

    std::cout <<++i << "PeptideParitalClonelWithInternalModification" << std::endl;    
    Test::TestPeptides::PeptideParitalClonelWithInternalModification();

    std::cout <<++i << "PeptideHashing" << std::endl;    
    Test::TestPeptides::PeptideHashing();

    std::cout <<++i << "ClearMods" << std::endl;    
    Test::TestPeptides::ClearMods();

    std::cout <<++i << "PeptideParitalClonelWithInternalModificationTwoMods" << std::endl;    
    Test::TestPeptides::PeptideParitalClonelWithInternalModificationTwoMods();

    std::cout <<++i << "PeptideParitalCloneInternalWithCTerminusModification" << std::endl;    
    Test::TestPeptides::PeptideParitalCloneInternalWithCTerminusModification();

    std::cout <<++i << "GetLeucineSequence" << std::endl;    
    Test::TestPeptides::GetLeucineSequence();

    std::cout <<++i << "GetLeucineSequenceNoReplacement" << std::endl;    
    Test::TestPeptides::GetLeucineSequenceNoReplacement();

    std::cout <<++i << "GetSequenceCoverage" << std::endl;    
    Test::TestPeptides::GetSequenceCoverage();

    std::cout <<++i << "GenerateIsotopologues" << std::endl;    
    Test::TestPeptides::GenerateIsotopologues();

    std::cout <<++i << "GetSequenceCoverageFraction" << std::endl;    
    Test::TestPeptides::GetSequenceCoverageFraction();

    std::cout <<++i << "TerminusModification" << std::endl;    
    Test::TestPeptides::TerminusModification();

    std::cout <<++i << "DigestionTest" << std::endl;    
    Test::TestPeptides::DigestionTest();

    std::cout <<++i << "TestChemicalFormula" << std::endl;    
    Test::TestPeptides::TestChemicalFormula();

    std::cout <<++i << "TestChemicalFormula2" << std::endl;    
    Test::TestPeptides::TestChemicalFormula2();

    std::cout <<++i << "TestMultipleModificationsAtSingleResidue" << std::endl;    
    Test::TestPeptides::TestMultipleModificationsAtSingleResidue();

    std::cout <<++i << "TestAApolymerContains" << std::endl;    
    Test::TestPeptides::TestAApolymerContains();

    std::cout <<++i << "TestLeucineSequence" << std::endl;    
    Test::TestPeptides::TestLeucineSequence();

    std::cout <<++i << "TestClearModifications" << std::endl;    
    Test::TestPeptides::TestClearModifications();

    std::cout <<++i << "TestGetSubPeptide" << std::endl;    
    Test::TestPeptides::TestGetSubPeptide();

    std::cout <<++i << "TestRealPeptideWithModifications" << std::endl;    
    Test::TestPeptides::TestRealPeptideWithModifications();

    std::cout <<++i << "TestGetDigestionPointsWithMethionine" << std::endl;    
    Test::TestPeptides::TestGetDigestionPointsWithMethionine();

    std::cout <<++i << "TestGetDigestionPointsWithMethionineAndSemiDigestion" << std::endl;    
    Test::TestPeptides::TestGetDigestionPointsWithMethionineAndSemiDigestion();

    std::cout <<++i << "BadSeqeunce" << std::endl;    
    Test::TestPeptides::BadSeqeunce();

    std::cout <<++i << "TestNonSpecificOverride" << std::endl;    
    Test::TestPeptides::TestNonSpecificOverride();
#endif
    return 0;
}        

namespace Test
{

    void TestPeptides::PeptideTestReal()
    {
        Peptide *pep = new Peptide("LDNLQQEIDFLTALYQAELSQMQTQISETNVILSMDNNR");
    }

    void TestPeptides::PeptideMassGlycine()
    {
        Peptide *pep = new Peptide("G");
        ChemicalFormula *formula = new ChemicalFormula(ChemicalFormula::ParseFormula("C2H5NO2"));
        ChemicalFormula *formula2;
        formula2 = pep->GetChemicalFormula();

        Assert::AreEqual(formula, formula2);

        delete formula;
        delete pep;
    }

    void TestPeptides::AApolymerNullEquals()
    {
        Peptide *pep = new Peptide("G");
        Assert::IsFalse(pep->Equals(nullptr));

        delete pep;
    }

#ifdef LATER    
    void TestPeptides::PeptideCountElements()
    {
        Peptide *pep = new Peptide("G");
        OldSchoolModification tempVar(1);
        pep->AddModification(&tempVar);
        Assert::AreEqual(5, pep->ElementCountWithIsotopes("H"));

        OldSchoolChemicalFormulaModification tempVar2(ChemicalFormula::ParseFormula("H{1}"));
        pep->AddModification(&tempVar2);
        Assert::AreEqual(5, pep->ElementCountWithIsotopes("H")); // NOTHING HAS BEEN ADDED!

        OldSchoolChemicalFormulaModification tempVar3(ChemicalFormula::ParseFormula("H{1}"), ModificationSites::G);
        pep->AddModification(&tempVar3);
        Assert::AreEqual(6, pep->ElementCountWithIsotopes("H"));

        Isotope *isotope = PeriodicTable::GetElement("H")->getPrincipalIsotope();
        Assert::AreEqual(1, pep->SpecificIsotopeCount(isotope));

        delete pep;
    }

    void TestPeptides::PeptideMassTryptic()
    {
        ChemicalFormula *formula = new ChemicalFormula(ChemicalFormula::ParseFormula("C37H66N12O21"));
        ChemicalFormula *formula2;
        formula2 = _mockTrypticPeptide->GetChemicalFormula();
        Assert::AreEqual(formula, formula2);

//C# TO C++ CONVERTER TODO TASK: A 'delete formula' statement was not added since formula was passed to a method or constructor. Handle memory management manually.
    }

    void TestPeptides::PeptideAminoAcidCount()
    {
        Assert::AreEqual(20, _mockPeptideEveryAminoAcid->getLength());
    }

    void TestPeptides::ParseNTerminalChemicalFormula()
    {
        Peptide *peptide = new Peptide("[C2H3NO]-TTGSSSSSSSK");
        ChemicalFormula *formulaA = new ChemicalFormula(ChemicalFormula::ParseFormula("C39H69N13O22"));
        ChemicalFormula *formulaB;
        formulaB = peptide->GetChemicalFormula();

        Assert::AreEqual(formulaA, formulaB);

//C# TO C++ CONVERTER TODO TASK: A 'delete formulaA' statement was not added since formulaA was passed to a method or constructor. Handle memory management manually.
        delete peptide;
    }

    void TestPeptides::ParseCTerminalChemicalFormula()
    {
        Peptide *peptide = new Peptide("TTGSSSSSSSK-[C2H3NO]");
        ChemicalFormula *formulaA = new ChemicalFormula(ChemicalFormula::ParseFormula("C39H69N13O22"));
        ChemicalFormula *formulaB;
        formulaB = peptide->GetChemicalFormula();

        Assert::AreEqual(formulaA, formulaB);

//C# TO C++ CONVERTER TODO TASK: A 'delete formulaA' statement was not added since formulaA was passed to a method or constructor. Handle memory management manually.
        delete peptide;
    }

    void TestPeptides::ParseCTerminalChemicalFormulaWithLastResidueMod()
    {
        Peptide *peptide = new Peptide("TTGSSSSSSSK[H2O]-[C2H3NO]");
        ChemicalFormula *formulaA = new ChemicalFormula(ChemicalFormula::ParseFormula("C39H71N13O23"));
        ChemicalFormula *formulaB;
        formulaB = peptide->GetChemicalFormula();

        Assert::AreEqual(formulaA, formulaB);

//C# TO C++ CONVERTER TODO TASK: A 'delete formulaA' statement was not added since formulaA was passed to a method or constructor. Handle memory management manually.
        delete peptide;
    }

    void TestPeptides::ParseCTerminalChemicalFormulaWithLastResidueModStringRepresentation()
    {
        Peptide *peptide = new Peptide("TTGSSSSSSSK[H2O]-[C2H3NO]");

        Assert::AreEqual("TTGSSSSSSSK[H2O]-[C2H3NO]", peptide->GetSequenceWithModifications());

        ChemicalFormulaTerminus tempVar(ChemicalFormula::ParseFormula("N"));
        peptide->setNTerminus(&tempVar);

        Assert::AreEqual("TTGSSSSSSSK[H2O]-[C2H3NO]", peptide->GetSequenceWithModifications());

        ChemicalFormula *formulaA = new ChemicalFormula(ChemicalFormula::ParseFormula("C39H70N14O23"));
        auto formulaB = peptide->GetChemicalFormula();
        Assert::AreEqual(formulaA, formulaB);

        ObjectWithMass100 tempVar2();
        peptide->AddModification(&tempVar2, 0);

        Assert::AreEqual("[mass: 100]-TTGSSSSSSSK[H2O]-[C2H3NO]", peptide->GetSequenceWithModifications());

        ObjectWithMass100 tempVar3();
        Assert::AreEqual(1, peptide->AddModification(&tempVar3, Terminus::C));

        Assert::AreEqual(3, peptide->ModificationCount());

        ObjectWithMass100 tempVar4();
        ObjectWithMass100 tempVar5();
        Assert::AreEqual(0, peptide->ReplaceModification(&tempVar4, &tempVar5));

        Assert::That([&] ()
        {
            ObjectWithMass100 tempVar6();
            peptide->ReplaceModification(nullptr, &tempVar6);
        }, Throws::TypeOf<MzLibException*>().With::Property("Message").EqualTo("Cannot replace a null modification"));

        ObjectWithMass100 tempVar7();
        peptide->SetModification(&tempVar7, std::vector<int> {1, 11});
        Assert::AreEqual(4, peptide->ModificationCount());

        OldSchoolModification *mod1 = new OldSchoolModification(5, "mass 5 on T", ModificationSites::T);
        peptide->SetModifications(std::vector<OldSchoolModification*> {mod1});
        Assert::AreEqual(5, peptide->ModificationCount());

//C# TO C++ CONVERTER TODO TASK: A 'delete mod1' statement was not added since mod1 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete formulaA' statement was not added since formulaA was passed to a method or constructor. Handle memory management manually.
        delete peptide;
    }

    void TestPeptides::ParseNAndCTerminalChemicalFormula()
    {
        Peptide *peptide = new Peptide("[C2H3NO]-TTGSSSSSSSK-[C2H3NO]");
        ChemicalFormula *formulaA = new ChemicalFormula(ChemicalFormula::ParseFormula("C41H72N14O23"));
        ChemicalFormula *formulaB;
        formulaB = peptide->GetChemicalFormula();

        Assert::AreEqual(formulaA, formulaB);

//C# TO C++ CONVERTER TODO TASK: A 'delete formulaA' statement was not added since formulaA was passed to a method or constructor. Handle memory management manually.
        delete peptide;
    }

    void TestPeptides::EmptyStringPeptideConstructorLength()
    {
        Peptide *peptide = new Peptide();

        Assert::AreEqual(0, peptide->getLength());

        delete peptide;
    }

    void TestPeptides::EmptyStringPeptideConstructorToString()
    {
        Peptide *peptide = new Peptide();

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual("", peptide->ToString());

        delete peptide;
    }

    void TestPeptides::ParseDoubleModificationToString()
    {
        Peptide *peptide = new Peptide("THGEAK[25.132]K");

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual("THGEAK[25.132]K", peptide->ToString());

        delete peptide;
    }

    void TestPeptides::ParseNamedChemicalModificationInvalidName()
    {
        Assert::That([&] ()
        {
            new Peptide("T[TMT 7-plex]HGEAK[Acetyl]K");
        }, Throws::TypeOf<MzLibException*>());
    }

    void TestPeptides::SetAminoAcidModification()
    {
        auto Asparagine = Residue::GetResidue("N");
        OldSchoolChemicalFormulaModification tempVar(ChemicalFormula::ParseFormula("Fe"));
        _mockPeptideEveryAminoAcid->SetModification(&tempVar, Asparagine);

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual("ACDEFGHIKLMN[Fe]PQRSTVWY", _mockPeptideEveryAminoAcid->ToString());
    }

    void TestPeptides::SetAminoAcidModificationStronglyTyped()
    {
        OldSchoolChemicalFormulaModification tempVar(ChemicalFormula::ParseFormula("Fe"));
        _mockPeptideEveryAminoAcid->SetModification(&tempVar, ModificationSites::N);

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual("ACDEFGHIKLMN[Fe]PQRSTVWY", _mockPeptideEveryAminoAcid->ToString());
    }

    void TestPeptides::SetAminoAcidModificationStronglyTypedMultipleLocations()
    {
        OldSchoolChemicalFormulaModification tempVar(ChemicalFormula::ParseFormula("Fe"));
        _mockPeptideEveryAminoAcid->SetModification(&tempVar, ModificationSites::N | ModificationSites::F | ModificationSites::V);

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual("ACDEF[Fe]GHIKLMN[Fe]PQRSTV[Fe]WY", _mockPeptideEveryAminoAcid->ToString());
    }

    void TestPeptides::SetAminoAcidModificationStronglyTypedAny()
    {
        OldSchoolChemicalFormulaModification tempVar(ChemicalFormula::ParseFormula("Fe"));
        _mockPeptideEveryAminoAcid->SetModification(&tempVar, ModificationSites::Any);

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual("ACDEFGHIKLMNPQRSTVWY", _mockPeptideEveryAminoAcid->ToString());
    }

    void TestPeptides::SetAminoAcidModificationStronglyTypedAll()
    {
        OldSchoolChemicalFormulaModification tempVar(ChemicalFormula::ParseFormula("Fe"));
        _mockPeptideEveryAminoAcid->SetModification(&tempVar, ModificationSites::All);

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual("[Fe]-A[Fe]C[Fe]D[Fe]E[Fe]F[Fe]G[Fe]H[Fe]I[Fe]K[Fe]L[Fe]M[Fe]N[Fe]P[Fe]Q[Fe]R[Fe]S[Fe]T[Fe]V[Fe]W[Fe]Y[Fe]-[Fe]", _mockPeptideEveryAminoAcid->ToString());
    }

    void TestPeptides::SetAminoAcidModificationStronglyTypedNone()
    {
        OldSchoolChemicalFormulaModification tempVar(ChemicalFormula::ParseFormula("Fe"));
        _mockPeptideEveryAminoAcid->SetModification(&tempVar, ModificationSites::None);

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual("ACDEFGHIKLMNPQRSTVWY", _mockPeptideEveryAminoAcid->ToString());
    }

    void TestPeptides::SetAminoAcidModificationStronglyTypedTermini()
    {
        OldSchoolChemicalFormulaModification tempVar(ChemicalFormula::ParseFormula("Fe"));
        _mockPeptideEveryAminoAcid->SetModification(&tempVar, ModificationSites::NPep | ModificationSites::PepC);

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual("[Fe]-ACDEFGHIKLMNPQRSTVWY-[Fe]", _mockPeptideEveryAminoAcid->ToString());
    }

    void TestPeptides::SetAminoAcidCharacterModification()
    {
        OldSchoolChemicalFormulaModification tempVar(ChemicalFormula::ParseFormula("Fe"));
        _mockPeptideEveryAminoAcid->SetModification(&tempVar, 'D');

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual("ACD[Fe]EFGHIKLMNPQRSTVWY", _mockPeptideEveryAminoAcid->ToString());
    }

    void TestPeptides::SetResiduePositionModification()
    {
        OldSchoolChemicalFormulaModification tempVar(ChemicalFormula::ParseFormula("Fe"));
        _mockPeptideEveryAminoAcid->SetModification(&tempVar, 5);

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual("ACDEF[Fe]GHIKLMNPQRSTVWY", _mockPeptideEveryAminoAcid->ToString());
    }

    void TestPeptides::SetResiduePositionModificationOutOfRangeUpper()
    {
        Assert::That([&] ()
        {
            OldSchoolChemicalFormulaModification tempVar(ChemicalFormula::ParseFormula("Fe"));
            _mockPeptideEveryAminoAcid->SetModification(&tempVar, 25);
        }, Throws::TypeOf<MzLibException*>());
    }

    void TestPeptides::SetResiduePositionModificationOutOfRangeLower()
    {
        Assert::That([&] ()
        {
            OldSchoolChemicalFormulaModification tempVar(ChemicalFormula::ParseFormula("Fe"));
            _mockPeptideEveryAminoAcid->SetModification(&tempVar, 0);
        }, Throws::TypeOf<MzLibException*>());
    }

    void TestPeptides::SetCTerminusModStringRepresentation()
    {
        OldSchoolChemicalFormulaModification tempVar(ChemicalFormula::ParseFormula("Fe"));
        _mockPeptideEveryAminoAcid->SetModification(&tempVar, Terminus::C);

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual("ACDEFGHIKLMNPQRSTVWY-[Fe]", _mockPeptideEveryAminoAcid->ToString());
    }

    void TestPeptides::SetCTerminusModStringRepresentationofChemicalModification()
    {
        IHasChemicalFormula *formula = new OldSchoolChemicalFormulaModification(ChemicalFormula::ParseFormula("Fe"), "Test");
        _mockPeptideEveryAminoAcid->SetModification(formula, Terminus::C);

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual("ACDEFGHIKLMNPQRSTVWY-[Test]", _mockPeptideEveryAminoAcid->ToString());

//C# TO C++ CONVERTER TODO TASK: A 'delete formula' statement was not added since formula was passed to a method or constructor. Handle memory management manually.
    }

    void TestPeptides::SetNAndCTerminusMod()
    {
        OldSchoolChemicalFormulaModification tempVar(ChemicalFormula::ParseFormula("Fe"));
        _mockPeptideEveryAminoAcid->SetModification(&tempVar, Terminus::C);
        OldSchoolChemicalFormulaModification tempVar2(ChemicalFormula::ParseFormula("H2NO"));
        _mockPeptideEveryAminoAcid->SetModification(&tempVar2, Terminus::N);

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual("[H2NO]-ACDEFGHIKLMNPQRSTVWY-[Fe]", _mockPeptideEveryAminoAcid->ToString());
    }

    void TestPeptides::SetSameNAndCTerminusMod()
    {
        OldSchoolChemicalFormulaModification tempVar(ChemicalFormula::ParseFormula("Fe"));
        _mockPeptideEveryAminoAcid->SetModification(&tempVar, Terminus::C | Terminus::N);

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual("[Fe]-ACDEFGHIKLMNPQRSTVWY-[Fe]", _mockPeptideEveryAminoAcid->ToString());
    }

    void TestPeptides::ClearNTerminusMod()
    {
        OldSchoolChemicalFormulaModification tempVar(ChemicalFormula::ParseFormula("Fe"));
        _mockPeptideEveryAminoAcid->SetModification(&tempVar, Terminus::N);

        _mockPeptideEveryAminoAcid->ClearModifications(Terminus::N);

        Assert::IsNull(_mockPeptideEveryAminoAcid->getNTerminusModification());
    }

    void TestPeptides::ClearCTerminusMod()
    {
        OldSchoolChemicalFormulaModification tempVar(ChemicalFormula::ParseFormula("Fe"));
        _mockPeptideEveryAminoAcid->SetModification(&tempVar, Terminus::C);

        _mockPeptideEveryAminoAcid->ClearModifications(Terminus::C);

        Assert::IsNull(_mockPeptideEveryAminoAcid->getCTerminusModification());
    }

    void TestPeptides::ClearAllMods()
    {
        OldSchoolChemicalFormulaModification tempVar(ChemicalFormula::ParseFormula("Fe"));
        _mockPeptideEveryAminoAcid->SetModification(&tempVar, ModificationSites::All);

        _mockPeptideEveryAminoAcid->ClearModifications();

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual("ACDEFGHIKLMNPQRSTVWY", _mockPeptideEveryAminoAcid->ToString());
    }

    void TestPeptides::ClearModificationsBySites()
    {
        auto peptide = new Peptide("AC[Fe]DEFGHIKLMNP[Fe]QRSTV[Fe]WY");

        peptide->ClearModifications(ModificationSites::C | ModificationSites::V);

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual("ACDEFGHIKLMNP[Fe]QRSTVWY", peptide->ToString());

        delete peptide;
    }

    void TestPeptides::EmptyPeptideLengthIsZero()
    {
        Peptide *pepA = new Peptide();

        Assert::AreEqual(0, pepA->getLength());

        delete pepA;
    }

    void TestPeptides::EmptyPeptideSequenceIsEmpty()
    {
        Peptide *pepA = new Peptide();

        Assert::AreEqual("", pepA->getBaseSequence());

        delete pepA;
    }

    void TestPeptides::EmptyPeptideFormulaIsH2O()
    {
        Peptide *pepA = new Peptide();
        ChemicalFormula *h2O = new ChemicalFormula(ChemicalFormula::ParseFormula("H2O"));
        ChemicalFormula *formulaB;
        formulaB = pepA->GetChemicalFormula();

        Assert::AreEqual(h2O, formulaB);

//C# TO C++ CONVERTER TODO TASK: A 'delete h2O' statement was not added since h2O was passed to a method or constructor. Handle memory management manually.
        delete pepA;
    }

    void TestPeptides::PeptideEquality()
    {
        Peptide *pepA = new Peptide("DEREK");
        Peptide *pepB = new Peptide("DEREK");
        Assert::AreEqual(pepA, pepB);

        Peptide *pepC = new Peptide("DEREKK");
        Assert::AreNotEqual(pepA, pepC);

//C# TO C++ CONVERTER TODO TASK: A 'delete pepC' statement was not added since pepC was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete pepB' statement was not added since pepB was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete pepA' statement was not added since pepA was passed to a method or constructor. Handle memory management manually.
    }

    void TestPeptides::PeptideInEqualityAminoAcidSwitch()
    {
        Peptide *pepA = new Peptide("DEREK");
        Peptide *pepB = new Peptide("DEERK");
        Assert::AreNotEqual(pepA, pepB);

//C# TO C++ CONVERTER TODO TASK: A 'delete pepB' statement was not added since pepB was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete pepA' statement was not added since pepA was passed to a method or constructor. Handle memory management manually.
    }

    void TestPeptides::PeptideInEqualityAminoAcidModification()
    {
        Peptide *pepA = new Peptide("DEREK");
        Peptide *pepB = new Peptide("DEREK");
        OldSchoolChemicalFormulaModification tempVar(ChemicalFormula::ParseFormula("H2O"));
        pepB->SetModification(&tempVar, 'R');
        Assert::AreNotEqual(pepA, pepB);
        OldSchoolChemicalFormulaModification tempVar2(ChemicalFormula::ParseFormula("H2O2"));
        pepA->SetModification(&tempVar2, 'R');
        Assert::AreNotEqual(pepA, pepB);

//C# TO C++ CONVERTER TODO TASK: A 'delete pepB' statement was not added since pepB was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete pepA' statement was not added since pepA was passed to a method or constructor. Handle memory management manually.
    }

    void TestPeptides::PeptideCloneEquality()
    {
        Peptide *pepA = new Peptide("DEREK");
        Peptide *pepB = new Peptide(pepA);
        Assert::AreEqual(pepA, pepB);

//C# TO C++ CONVERTER TODO TASK: A 'delete pepB' statement was not added since pepB was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete pepA' statement was not added since pepA was passed to a method or constructor. Handle memory management manually.
    }

    void TestPeptides::PeptideCloneNotSameReference()
    {
        Peptide *pepA = new Peptide("DEREK");
        Peptide *pepB = new Peptide(pepA);

        Assert::AreNotSame(pepA, pepB);

//C# TO C++ CONVERTER TODO TASK: A 'delete pepB' statement was not added since pepB was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete pepA' statement was not added since pepA was passed to a method or constructor. Handle memory management manually.
    }

    void TestPeptides::PeptideCloneWithModifications()
    {
        Peptide *pepA = new Peptide("DER[Fe]EK");
        Peptide *pepB = new Peptide(pepA);
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual("DER[Fe]EK", pepB->ToString());

        delete pepB;
//C# TO C++ CONVERTER TODO TASK: A 'delete pepA' statement was not added since pepA was passed to a method or constructor. Handle memory management manually.
    }

    void TestPeptides::PeptideCloneWithoutModifications()
    {
        Peptide *pepA = new Peptide("DER[Fe]EK");
        Peptide *pepB = new Peptide(pepA, false);
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual("DEREK", pepB->ToString());

        delete pepB;
//C# TO C++ CONVERTER TODO TASK: A 'delete pepA' statement was not added since pepA was passed to a method or constructor. Handle memory management manually.
    }

    void TestPeptides::PeptideCloneWithModification()
    {
        Peptide *pepA = new Peptide("DEREK");
        OldSchoolChemicalFormulaModification tempVar(ChemicalFormula::ParseFormula("H2O"));
        pepA->SetModification(&tempVar, 'R');
        Peptide *pepB = new Peptide(pepA);

        Assert::AreEqual(pepB, pepA);

//C# TO C++ CONVERTER TODO TASK: A 'delete pepB' statement was not added since pepB was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete pepA' statement was not added since pepA was passed to a method or constructor. Handle memory management manually.
    }

    void TestPeptides::PeptideParitalCloneInternal()
    {
        Peptide *pepA = new Peptide("DEREK");
        Peptide *pepB = new Peptide(pepA, 1, 3);
        Peptide *pepC = new Peptide("ERE");
        Assert::AreEqual(pepB, pepC);

//C# TO C++ CONVERTER TODO TASK: A 'delete pepC' statement was not added since pepC was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete pepB' statement was not added since pepB was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete pepA' statement was not added since pepA was passed to a method or constructor. Handle memory management manually.
    }

    void TestPeptides::PeptideParitalClonelWithInternalModification()
    {
        Peptide *pepA = new Peptide("DER[Fe]EK");
        Peptide *pepB = new Peptide(pepA, 2, 3);
        Peptide *pepC = new Peptide("R[Fe]EK");
        Assert::AreEqual(pepB, pepC);

//C# TO C++ CONVERTER TODO TASK: A 'delete pepC' statement was not added since pepC was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete pepB' statement was not added since pepB was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete pepA' statement was not added since pepA was passed to a method or constructor. Handle memory management manually.
    }

    void TestPeptides::PeptideHashing()
    {
        Peptide *pep1 = new Peptide("DEREK");
        Peptide *pep2 = new Peptide("DEREKN");
        Peptide *pep3 = new Peptide("DEREKM");
        Peptide *pep4 = new Peptide("DEREKM");
        std::unordered_set<Peptide*> uu = {pep1, pep2, pep3, pep4};
        Peptide tempVar("DEREKN");
        uu.insert(&tempVar);
        Assert::AreEqual(3, uu.size());

        delete pep4;
        delete pep3;
        delete pep2;
        delete pep1;
    }

    void TestPeptides::ClearMods()
    {
        Peptide *pepA = new Peptide("DE[Al]R[Fe]EK");
        OldSchoolChemicalFormulaModification tempVar(ChemicalFormula::ParseFormula("Al"));
        pepA->ClearModifications(&tempVar);
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual("DER[Fe]EK", pepA->ToString());
        OldSchoolChemicalFormulaModification tempVar2(ChemicalFormula::ParseFormula("C"));
        pepA->ClearModifications(&tempVar2);
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual("DER[Fe]EK", pepA->ToString());
        pepA->ClearModifications();
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual("DEREK", pepA->ToString());
        pepA->ClearModifications();
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual("DEREK", pepA->ToString());
        pepA->ClearModifications(ModificationSites::Any);
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual("DEREK", pepA->ToString());
        pepA->ClearModifications(Terminus::C);
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual("DEREK", pepA->ToString());

        delete pepA;
    }

    void TestPeptides::PeptideParitalClonelWithInternalModificationTwoMods()
    {
        Peptide *pepA = new Peptide("DE[Al]R[Fe]EK");
        Peptide *pepB = new Peptide(pepA, 2, 3);
        Peptide *pepC = new Peptide("R[Fe]EK");
        Assert::AreEqual(pepB, pepC);

//C# TO C++ CONVERTER TODO TASK: A 'delete pepC' statement was not added since pepC was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete pepB' statement was not added since pepB was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete pepA' statement was not added since pepA was passed to a method or constructor. Handle memory management manually.
    }

    void TestPeptides::PeptideParitalCloneInternalWithCTerminusModification()
    {
        Peptide *pepA = new Peptide("DEREK");
        OldSchoolChemicalFormulaModification tempVar(ChemicalFormula::ParseFormula("H2O"));
        pepA->SetModification(&tempVar, Terminus::C);
        Peptide *pepB = new Peptide(pepA, 2, 3);

        Peptide *pepC = new Peptide("REK");
        OldSchoolChemicalFormulaModification tempVar2(ChemicalFormula::ParseFormula("H2O"));
        pepC->SetModification(&tempVar2, Terminus::C);

        Assert::AreEqual(pepC, pepB);

//C# TO C++ CONVERTER TODO TASK: A 'delete pepC' statement was not added since pepC was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete pepB' statement was not added since pepB was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete pepA' statement was not added since pepA was passed to a method or constructor. Handle memory management manually.
    }

    void TestPeptides::GetLeucineSequence()
    {
        Peptide *pepA = new Peptide("DERIEK");
        std::string leuSeq = pepA->getBaseLeucineSequence();

        Assert::AreEqual("DERLEK", leuSeq);

        delete pepA;
    }

    void TestPeptides::GetLeucineSequenceNoReplacement()
    {
        Peptide *pepA = new Peptide("DERLEK");

        std::string leuSeq = pepA->getBaseLeucineSequence();

        Assert::AreEqual("DERLEK", leuSeq);

        delete pepA;
    }

    void TestPeptides::GetSequenceCoverage()
    {
        Peptide *pepA = new Peptide("DERLEK");
        Peptide *pepAa = new Peptide("ER");
        Peptide *pepAb = new Peptide("RL");
        Peptide *pepAc = new Peptide("LEK");
        std::vector<Peptide*> myList = {pepAa, pepAb, pepAc};
        Assert::IsTrue(pepA->GetSequenceCoverage(myList).SequenceEqual(std::vector<int> {0, 1, 2, 2, 1, 1}));

        delete pepAc;
        delete pepAb;
        delete pepAa;
        delete pepA;
    }

    void TestPeptides::GenerateIsotopologues()
    {
        Peptide *pep = new Peptide("DERLEK");
        auto a = pep->GenerateAllModificationCombinations().ToArray();
        Assert::AreEqual(0, a.Count());
        auto i = new ModificationWithMultiplePossibilitiesCollection("My Iso Mod", ModificationSites::E);
        OldSchoolModification tempVar(1, "My Mod1a", ModificationSites::E);
        i->AddModification(&tempVar);
        OldSchoolModification tempVar2(2, "My Mod2b", ModificationSites::E);
        i->AddModification(&tempVar2);
        pep->SetModification(i);
        auto i2 = new ModificationWithMultiplePossibilitiesCollection("My Iso Mod2", ModificationSites::R);
        OldSchoolModification tempVar3(1, "My Mod2a", ModificationSites::R);
        i2->AddModification(&tempVar3);
        OldSchoolModification tempVar4(2, "My Mod2b", ModificationSites::R);
        i2->AddModification(&tempVar4);
        OldSchoolModification tempVar5(3, "My Mod2c", ModificationSites::R);
        i2->AddModification(&tempVar5);
        pep->SetModification(i2);
        a = pep->GenerateAllModificationCombinations().ToArray();
        // Only 6 and not 12, because in the first modification, it is one choice that is substituted across all modification sites
        Assert::AreEqual(6, a.Count());

//C# TO C++ CONVERTER TODO TASK: A 'delete i2' statement was not added since i2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete i' statement was not added since i was passed to a method or constructor. Handle memory management manually.
        delete pep;
    }

    void TestPeptides::GetSequenceCoverageFraction()
    {
        Peptide *pepA = new Peptide("DERLEK");
        Peptide *pepAa = new Peptide("ER");
        Peptide *pepAb = new Peptide("RL");
        std::vector<Peptide*> myList = {pepAa, pepAb};
        Assert::AreEqual(0.5, pepA->GetSequenceCoverageFraction(myList));

        delete pepAb;
        delete pepAa;
        delete pepA;
    }

    void TestPeptides::TerminusModification()
    {
        Peptide *pepA = new Peptide("DERLEK");
        OldSchoolChemicalFormulaModification tempVar(ChemicalFormula::ParseFormula("SO"));
        pepA->AddModification(&tempVar, Terminus::N);
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual("[OS]-DERLEK", pepA->ToString());

        delete pepA;
    }

    void TestPeptides::DigestionTest()
    {
        IProtease *protease = new TestProtease();
        Assert::AreEqual(6, AminoAcidPolymer::Digest(_mockPeptideEveryAminoAcid, protease).size()());

//C# TO C++ CONVERTER TODO TASK: A 'delete protease' statement was not added since protease was passed to a method or constructor. Handle memory management manually.
    }

    void TestPeptides::TestChemicalFormula()
    {
        Residue::GetResidue('A');

        Peptide *A = new Peptide("A");

        Residue::GetResidue('A');

        ChemicalFormula *ok = new ChemicalFormula(Residue::GetResidue('A')->getThisChemicalFormula());
        ChemicalFormulaTerminus tempVar(ChemicalFormula::ParseFormula("OH"));
        ok->Add(&tempVar);
        ChemicalFormulaTerminus tempVar2(ChemicalFormula::ParseFormula("H"));
        ok->Add(&tempVar2);

        Residue::GetResidue('A');

        Residue::GetResidue('A');

        Assert::AreEqual(ok, A->GetChemicalFormula());

//C# TO C++ CONVERTER TODO TASK: A 'delete ok' statement was not added since ok was passed to a method or constructor. Handle memory management manually.
        delete A;
    }

    void TestPeptides::TestChemicalFormula2()
    {
        Peptide *A = new Peptide("A");
        OldSchoolModification *a = new OldSchoolModification(1, "Modification without chemical formula", ModificationSites::A);
        A->AddModification(a);
        Assert::Throws<MzLibException*>([&] ()
        {
            A->GetChemicalFormula();
        }, "Modification Modification without chemical formula does not have a chemical formula!");

//C# TO C++ CONVERTER TODO TASK: A 'delete a' statement was not added since a was passed to a method or constructor. Handle memory management manually.
        delete A;
    }

    void TestPeptides::TestMultipleModificationsAtSingleResidue()
    {
        Peptide *a = new Peptide("ACDEFGHIKLMNPQRSTVWY");
        OldSchoolChemicalFormulaModification tempVar(ChemicalFormula::ParseFormula("O"), ModificationSites::D);
        a->AddModification(&tempVar);
        OldSchoolChemicalFormulaModification tempVar2(ChemicalFormula::ParseFormula("H"), ModificationSites::D);
        a->AddModification(&tempVar2);
        auto products = a->Fragment(FragmentTypes::b | FragmentTypes::y, true);
        for (auto fragment : products)
        {
        }
        for (auto fragment : products)
        {
        }

        delete a;
    }

    void TestPeptides::TestAApolymerContains()
    {
        Assert::IsFalse(_mockTrypticPeptide->Contains('A'));
        Assert::IsTrue(_mockTrypticPeptide->Contains(Residue::GetResidue('T')));
    }

    void TestPeptides::TestLeucineSequence()
    {
        Assert::AreEqual("ACDEFGHLKLMNPQRSTVWY", _mockPeptideEveryAminoAcid->GetSequenceWithModifications(true));
        Assert::AreEqual(20, _mockPeptideEveryAminoAcid->ResidueCount());
        Assert::AreEqual(7, _mockTrypticPeptide->ResidueCount('S'));
        Assert::AreEqual(7, _mockTrypticPeptide->ResidueCount(Residue::GetResidue('S')));
        Assert::AreEqual(2, _mockTrypticPeptide->ResidueCount(Residue::GetResidue('S'), 2, 3));
        Assert::AreEqual(3, _mockTrypticPeptide->ResidueCount('S', 2, 4));

        Peptide *peptide = new Peptide("III-[C2H3NO]");
        Assert::AreEqual("LLL-[C2H3NO]", peptide->GetSequenceWithModifications(true));

        delete peptide;
    }

    void TestPeptides::TestClearModifications()
    {
        Peptide *a = new Peptide("ACDEFGHIKLMNPQRSTVWY");
        OldSchoolChemicalFormulaModification tempVar(ChemicalFormula::ParseFormula("O"), ModificationSites::D);
        a->AddModification(&tempVar);
        OldSchoolChemicalFormulaModification tempVar2(ChemicalFormula::ParseFormula("H"), ModificationSites::E);
        a->AddModification(&tempVar2);
        Assert::AreEqual(2, a->ModificationCount());
        a->ClearModifications();
        Assert::AreEqual(0, a->ModificationCount());
        OldSchoolChemicalFormulaModification tempVar3(ChemicalFormula::ParseFormula("O"), ModificationSites::NTerminus);
        a->AddModification(&tempVar3);
        OldSchoolModification tempVar4(1);
        a->AddModification(&tempVar4, ModificationSites::TerminusC);
        Assert::AreEqual(2, a->ModificationCount());
        a->Fragment(FragmentTypes::y);

        Peptide *peptide = new Peptide("[C2H3NO]-LLL-[C2H3NO]");
        ModificationSites ff = ModificationSites::NPep | ModificationSites::PepC;
        peptide->ClearModifications(ff);
        Assert::AreEqual("LLL", peptide->GetSequenceWithModifications());

        delete peptide;
        delete a;
    }

    void TestPeptides::TestGetSubPeptide()
    {
        Peptide *pep = new Peptide("DERLEK");
        Peptide tempVar("LE");
        Assert::AreEqual(&tempVar, pep->GetSubPeptide(3, 2));

        delete pep;
    }

    void TestPeptides::TestRealPeptideWithModifications()
    {
        Peptide *a = new Peptide("LDNLQQEIDFLTALYQAELSQM[O]QTQISETNVILSM[O]DNNR");
        Assert::AreEqual(2, a->ModificationCount());

        delete a;
    }

    void TestPeptides::TestGetDigestionPointsWithMethionine()
    {
        auto ok = AminoAcidPolymer::GetDigestionPointsAndLengths("MDERLEKDERLE", std::vector<TestProtease*> {new TestProtease()}, 0, 0, 10000, true, false).ToList();
        Assert::AreEqual(1, ok[0].Index); // Methionine cleaved, digestion is at 1
        Assert::AreEqual(4, ok[0].Length); // The test protease cleaves at index 4, so after L.
        Assert::AreEqual(0, ok[1].Index); // Regular digestion 1
        Assert::AreEqual(5, ok[1].Length); // Regular digestion 1
        Assert::AreEqual(5, ok[2].Index); // Regular digestion 2
        Assert::AreEqual(1, ok[2].Length); // Regular digestion 2
        Assert::AreEqual(6, ok[3].Index); // Regular digestion 3
        Assert::AreEqual(6, ok[3].Length); // Regular digestion 3
    }

    void TestPeptides::TestGetDigestionPointsWithMethionineAndSemiDigestion()
    {
        auto ok = AminoAcidPolymer::GetDigestionPointsAndLengths("MDERLEK", std::vector<TestProtease*> {new TestProtease()}, 0, 0, 10000, true, true).ToList();

        IEqualityComparer<DigestionPointAndLength*> *jj = new OkComparer();
        auto yee = std::unordered_set<DigestionPointAndLength*>(ok, jj);

        Assert::AreEqual(1 + 3 + 1 + (8 - 1) + 1 + 1, yee.size());

//C# TO C++ CONVERTER TODO TASK: A 'delete jj' statement was not added since jj was passed to a method or constructor. Handle memory management manually.
    }

    void TestPeptides::BadSeqeunce()
    {
        Assert::That([&] ()
        {
            new Peptide("ABC");
        }, Throws::TypeOf<MzLibException*>().With::Property("Message").EqualTo("Amino Acid Letter B does not exist in the Amino Acid Dictionary. B is also not a valid character"));

        Assert::That([&] ()
        {
            new Peptide("A[");
        }, Throws::TypeOf<MzLibException*>().With::Property("Message").EqualTo("Couldn't find the closing ] for a modification in this sequence: A["));
    }

    void TestPeptides::TestNonSpecificOverride()
    {
        std::string trypsin = "trypsin";
        DigestionParams *digestionParams = new DigestionParams(trypsin);
        Assert::AreEqual(digestionParams->getProtease()->getName(), trypsin);

        digestionParams = new DigestionParams(trypsin, 2, 7, int::MaxValue, 1024, InitiatorMethionineBehavior::Variable, 2, CleavageSpecificity::None, FragmentationTerminus::N);
        Assert::AreEqual(digestionParams->getProtease()->getName(), "singleN");
        Assert::AreEqual(digestionParams->getSpecificProtease()->getName(), trypsin);

        digestionParams = new DigestionParams(trypsin, 2, 7, int::MaxValue, 1024, InitiatorMethionineBehavior::Variable, 2, CleavageSpecificity::None, FragmentationTerminus::C);
        Assert::AreEqual(digestionParams->getProtease()->getName(), "singleC");
        Assert::AreEqual(digestionParams->getSpecificProtease()->getName(), trypsin);

        delete digestionParams;
    }

    bool TestPeptides::OkComparer::Equals(DigestionPointAndLength *x, DigestionPointAndLength *y)
    {
        return x->getIndex().Equals(y->getIndex()) && x->getLength().Equals(y->getLength());
    }

    int TestPeptides::OkComparer::GetHashCode(DigestionPointAndLength *obj)
    {
        return obj->getLength() + obj->getIndex() * 256;
    }

    std::vector<int> TestProtease::GetDigestionSites(AminoAcidPolymer *aminoAcidSequence)
    {
        return GetDigestionSites(aminoAcidSequence->getBaseSequence());
    }

    std::vector<int> TestProtease::GetDigestionSites(const std::string &aminoAcidSequence)
    {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
        yield return 4;
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
        yield return 5;
    }

    int TestProtease::MissedCleavages(AminoAcidPolymer *aminoAcidSequence)
    {
        throw NotImplementedException();
    }

    int TestProtease::MissedCleavages(const std::string &sequence)
    {
        throw NotImplementedException();
    }
#endif
}
