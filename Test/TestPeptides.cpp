#include "TestPeptides.h"
#include "../Chemistry/ChemicalFormula.h"
#include "../Chemistry/Isotope.h"
#include "../Chemistry/PeriodicTable.h"
#include "TestMassMzCalculations.h"
#include "../MzLibUtil/MzLibException.h"
#include "../Chemistry/Interfaces/IHasChemicalFormula.h"
#include "TestChemicalFormula.h"

#include "../UsefulProteomicsDatabases/PeriodicTableLoader.h"

#include <limits>
#include "Assert.h"


Peptide *_mockPeptideEveryAminoAcid;
Peptide *_mockTrypticPeptide;

int main ( int argc, char **argv )
{
    
    int i=0;
    std::cout << i << ". PeriodicTableLoader" << std::endl;    
    const std::string elfile="elements.dat";
    const std::string &elr=elfile;
    // Chemistry::PeriodicTable::Load (elr);
    UsefulProteomicsDatabases::PeriodicTableLoader::Load (elr);

    
    _mockPeptideEveryAminoAcid = new Peptide("ACDEFGHIKLMNPQRSTVWY");
    _mockTrypticPeptide = new Peptide("TTGSSSSSSSK");
    
    std::cout <<++i << ". TestPeptideTestReal" << std::endl;    
    Test::TestPeptides::PeptideTestReal();
    
    std::cout <<++i << ". PeptideMassGlycine" << std::endl;    
    Test::TestPeptides::PeptideMassGlycine();

    std::cout <<++i << ". AApolymerNullEquals" << std::endl;    
    Test::TestPeptides::AApolymerNullEquals();

    std::cout <<++i << ". PeptideCountElements" << std::endl;    
    Test::TestPeptides::PeptideCountElements();

    std::cout <<++i << ". PeptideMassTryptic" << std::endl;    
    Test::TestPeptides::PeptideMassTryptic();
 
    std::cout <<++i << ". PeptideAminoAcidCount" << std::endl;    
    Test::TestPeptides::PeptideAminoAcidCount();

    std::cout <<++i << ". ParseNTerminalChemicalFormula" << std::endl;    
    Test::TestPeptides::ParseNTerminalChemicalFormula();
     
    std::cout <<++i << ". ParseCTerminalChemicalFormula" << std::endl;    
    Test::TestPeptides::ParseCTerminalChemicalFormula();
   
    std::cout <<++i << ". ParseCTerminalChemicalFormulaWithLastResidueMod" << std::endl;    
    Test::TestPeptides::ParseCTerminalChemicalFormulaWithLastResidueMod();

#ifdef LATER
    // many asserts, but also throws exception
    std::cout <<++i << ". ParseCTerminalChemicalFormulaWithLastResidueModStringRepresentation" << std::endl;    
    Test::TestPeptides::ParseCTerminalChemicalFormulaWithLastResidueModStringRepresentation();
#endif

    std::cout <<++i << ". ParseNAndCTerminalChemicalFormula" << std::endl;    
    Test::TestPeptides::ParseNAndCTerminalChemicalFormula();

    std::cout <<++i << ". EmptyStringPeptideConstructorLength" << std::endl;    
    Test::TestPeptides::EmptyStringPeptideConstructorLength();

    std::cout <<++i << ". EmptyStringPeptideConstructorToString" << std::endl;    
    Test::TestPeptides::EmptyStringPeptideConstructorToString();

    std::cout <<++i << ". ParseDoubleModificationToString" << std::endl;    
    Test::TestPeptides::ParseDoubleModificationToString();

#ifdef LATER
    // test is supposed to throw exception
    std::cout <<++i << ". ParseNamedChemicalModificationInvalidName" << std::endl;    
    Test::TestPeptides::ParseNamedChemicalModificationInvalidName();
#endif
    
    std::cout <<++i << ". SetAminoAcidModification" << std::endl;    
    Test::TestPeptides::SetAminoAcidModification();

    std::cout <<++i << ". SetAminoAcidModificationStronglyTyped" << std::endl;    
    Test::TestPeptides::SetAminoAcidModificationStronglyTyped();

    std::cout <<++i << ". SetAminoAcidModificationStronglyTypedMultipleLocations" << std::endl;    
    Test::TestPeptides::SetAminoAcidModificationStronglyTypedMultipleLocations();

    std::cout <<++i << ". SetAminoAcidModificationStronglyTypedAny" << std::endl;    
    Test::TestPeptides::SetAminoAcidModificationStronglyTypedAny();

    std::cout <<++i << ". SetAminoAcidModificationStronglyTypedAll" << std::endl;    
    Test::TestPeptides::SetAminoAcidModificationStronglyTypedAll();

    std::cout <<++i << ". SetAminoAcidModificationStronglyTypedNone" << std::endl;    
    Test::TestPeptides::SetAminoAcidModificationStronglyTypedNone();

    std::cout <<++i << ". SetAminoAcidModificationStronglyTypedTermini" << std::endl;    
    Test::TestPeptides::SetAminoAcidModificationStronglyTypedTermini();

    std::cout <<++i << ". SetAminoAcidCharacterModification" << std::endl;    
    Test::TestPeptides::SetAminoAcidCharacterModification();

    std::cout <<++i << ". SetResiduePositionModification" << std::endl;    
    Test::TestPeptides::SetResiduePositionModification();

#ifdef LATER
    // Uses Assert::That and throws exception
    std::cout <<++i << ". SetResiduePositionModificationOutOfRangeUpper" << std::endl;    
    Test::TestPeptides::SetResiduePositionModificationOutOfRangeUpper();

    // Uses Assert::That and throws exception
    std::cout <<++i << ". SetResiduePositionModificationOutOfRangeLower" << std::endl;    
    Test::TestPeptides::SetResiduePositionModificationOutOfRangeLower();
#endif

    std::cout <<++i << ". SetCTerminusModStringRepresentation" << std::endl;    
    Test::TestPeptides::SetCTerminusModStringRepresentation();

    std::cout <<++i << ". SetCTerminusModStringRepresentationofChemicalModification" << std::endl;    
    Test::TestPeptides::SetCTerminusModStringRepresentationofChemicalModification();

    std::cout <<++i << ". SetNAndCTerminusMod" << std::endl;    
    Test::TestPeptides::SetNAndCTerminusMod();

    std::cout <<++i << ". SetSameNAndCTerminusMod" << std::endl;    
    Test::TestPeptides::SetSameNAndCTerminusMod();
    
    std::cout <<++i << ". ClearNTerminusMod" << std::endl;    
    Test::TestPeptides::ClearNTerminusMod();

    std::cout <<++i << ". ClearCTerminusMod" << std::endl;    
    Test::TestPeptides::ClearCTerminusMod();

    std::cout <<++i << ". ClearAllMods" << std::endl;    
    Test::TestPeptides::ClearAllMods();

    std::cout <<++i << ". ClearModificationsBySites" << std::endl;    
    Test::TestPeptides::ClearModificationsBySites();

    std::cout <<++i << ". EmptyPeptideLengthIsZero" << std::endl;    
    Test::TestPeptides::EmptyPeptideLengthIsZero();

    std::cout <<++i << ". EmptyPeptideSequenceIsEmpty" << std::endl;    
    Test::TestPeptides::EmptyPeptideSequenceIsEmpty();

    std::cout <<++i << ". EmptyPeptideFormulaIsH2O" << std::endl;    
    Test::TestPeptides::EmptyPeptideFormulaIsH2O();

    std::cout <<++i << ". PeptideEquality" << std::endl;    
    Test::TestPeptides::PeptideEquality();

    std::cout <<++i << ". PeptideInEqualityAminoAcidSwitch" << std::endl;    
    Test::TestPeptides::PeptideInEqualityAminoAcidSwitch();

    std::cout <<++i << ". PeptideInEqualityAminoAcidModification" << std::endl;    
    Test::TestPeptides::PeptideInEqualityAminoAcidModification();

    std::cout <<++i << ". PeptideCloneEquality" << std::endl;    
    Test::TestPeptides::PeptideCloneEquality();

    std::cout <<++i << ". PeptideCloneNotSameReference" << std::endl;    
    Test::TestPeptides::PeptideCloneNotSameReference();

    std::cout <<++i << ". PeptideCloneWithModifications" << std::endl;    
    Test::TestPeptides::PeptideCloneWithModifications();

    std::cout <<++i << ". PeptideCloneWithoutModifications" << std::endl;    
    Test::TestPeptides::PeptideCloneWithoutModifications();

    std::cout <<++i << ". PeptideCloneWithModification" << std::endl;    
    Test::TestPeptides::PeptideCloneWithModification();

    std::cout <<++i << ". PeptideParitalCloneInternal" << std::endl;    
    Test::TestPeptides::PeptideParitalCloneInternal();

    std::cout <<++i << ". PeptideParitalClonelWithInternalModification" << std::endl;    
    Test::TestPeptides::PeptideParitalClonelWithInternalModification();

    //Edgar: will not fix this test.
    std::cout <<++i << ". PeptideHashing" << std::endl;    
    Test::TestPeptides::PeptideHashing();

    std::cout <<++i << ". ClearMods" << std::endl;    
    Test::TestPeptides::ClearMods();

    std::cout <<++i << ". PeptideParitalClonelWithInternalModificationTwoMods" << std::endl;    
    Test::TestPeptides::PeptideParitalClonelWithInternalModificationTwoMods();

    std::cout <<++i << ". PeptideParitalCloneInternalWithCTerminusModification" << std::endl;    
    Test::TestPeptides::PeptideParitalCloneInternalWithCTerminusModification();

    std::cout <<++i << ". GetLeucineSequence" << std::endl;    
    Test::TestPeptides::GetLeucineSequence();

    std::cout <<++i << ". GetLeucineSequenceNoReplacement" << std::endl;    
    Test::TestPeptides::GetLeucineSequenceNoReplacement();

#ifdef LATER
    // error: ‘class Proteomics::AminoAcidPolymer::Peptide’ has no member named ‘GetSequenceCoverage’
    std::cout <<++i << ". GetSequenceCoverage" << std::endl;    
    Test::TestPeptides::GetSequenceCoverage();

    std::cout <<++i << ". GenerateIsotopologues" << std::endl;    
    Test::TestPeptides::GenerateIsotopologues();

    // error: ‘class Proteomics::AminoAcidPolymer::Peptide’ has no member named ‘GetSequenceCoverageFraction’;
    std::cout <<++i << ". GetSequenceCoverageFraction" << std::endl;    
    Test::TestPeptides::GetSequenceCoverageFraction();
#endif

    std::cout <<++i << ". TerminusModification" << std::endl;    
    Test::TestPeptides::TerminusModification();

#ifdef LATER
    // class TestProtease is in a LATER ifdef block in TestPeptides.h
    std::cout <<++i << ". DigestionTest" << std::endl;    
    Test::TestPeptides::DigestionTest();
#endif

    std::cout <<++i << ". TestChemicalFormula" << std::endl;    
    Test::TestPeptides::TestChemicalFormula();

#ifdef LATER
    // Throws expcetion
    std::cout <<++i << ". TestChemicalFormula2" << std::endl;    
    Test::TestPeptides::TestChemicalFormula2();

    // Test doesn't do anything useful.
    std::cout <<++i << ". TestMultipleModificationsAtSingleResidue" << std::endl;    
    Test::TestPeptides::TestMultipleModificationsAtSingleResidue();
#endif

    std::cout <<++i << ". TestAApolymerContains" << std::endl;    
    Test::TestPeptides::TestAApolymerContains();

    std::cout <<++i << ". TestLeucineSequence" << std::endl;    
    Test::TestPeptides::TestLeucineSequence();

    std::cout <<++i << ". TestClearModifications" << std::endl;    
    Test::TestPeptides::TestClearModifications();

    std::cout <<++i << ". TestGetSubPeptide" << std::endl;    
    Test::TestPeptides::TestGetSubPeptide();

    std::cout <<++i << ". TestRealPeptideWithModifications" << std::endl;    
    Test::TestPeptides::TestRealPeptideWithModifications();

#ifdef LATER
    // uses class TestProtease which is in a LATER ifdef block in TestPeptides.h
    std::cout <<++i << ". TestGetDigestionPointsWithMethionine" << std::endl;    
    Test::TestPeptides::TestGetDigestionPointsWithMethionine();

    // uses class TestProtease which is in a LATER ifdef block in TestPeptides.h,
    // also uses OkComparer which is in a LATER ifdef block in TestPeptides.h
    std::cout <<++i << ". TestGetDigestionPointsWithMethionineAndSemiDigestion" << std::endl;    
    Test::TestPeptides::TestGetDigestionPointsWithMethionineAndSemiDigestion();

    // throws exception
    std::cout <<++i << ". BadSeqeunce" << std::endl;    
    Test::TestPeptides::BadSeqeunce();
#endif

    std::cout <<++i << ". TestNonSpecificOverride" << std::endl;    
    Test::TestPeptides::TestNonSpecificOverride();

    return 0;
}        

namespace Test
{

    void TestPeptides::PeptideTestReal()
    {
        Peptide *pep = new Peptide("LDNLQQEIDFLTALYQAELSQMQTQISETNVILSMDNNR");
        delete pep;
    }

    void TestPeptides::PeptideMassGlycine()
    {
        Peptide *pep = new Peptide("G");
        ChemicalFormula *formula = new ChemicalFormula(ChemicalFormula::ParseFormula("C2H5NO2"));
        ChemicalFormula *formula2;
        formula2 = pep->GetChemicalFormula();

        Assert::IsTrue(formula->Equals(formula2));

        delete formula;
        delete pep;
    }

    void TestPeptides::AApolymerNullEquals()
    {
        Peptide *pep = new Peptide("G");
        Assert::IsFalse(pep->Equals(nullptr));

        delete pep;
    }

    void TestPeptides::PeptideCountElements()
    {
        Peptide *pep = new Peptide("G");
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
        ChemicalFormula *formula2 = _mockTrypticPeptide->GetChemicalFormula();

        Assert::IsTrue(formula->Equals(formula2));

        delete formula;
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

        Assert::IsTrue(formulaA->Equals(formulaB));

        delete formulaA;
        delete peptide;
    }

    void TestPeptides::ParseCTerminalChemicalFormula()
    {
        Peptide *peptide = new Peptide("TTGSSSSSSSK-[C2H3NO]");
        ChemicalFormula *formulaA = new ChemicalFormula(ChemicalFormula::ParseFormula("C39H69N13O22"));
        ChemicalFormula *formulaB;
        formulaB = peptide->GetChemicalFormula();

        Assert::IsTrue(formulaA->Equals(formulaB));

        delete peptide;
        delete formulaA;
    }

    void TestPeptides::ParseCTerminalChemicalFormulaWithLastResidueMod()
    {
        Peptide *peptide = new Peptide("TTGSSSSSSSK[H2O]-[C2H3NO]");
        ChemicalFormula *formulaA = new ChemicalFormula(ChemicalFormula::ParseFormula("C39H71N13O23"));
        ChemicalFormula *formulaB;
        formulaB = peptide->GetChemicalFormula();

        Assert::IsTrue(formulaA->Equals(formulaB));

        delete peptide;
        delete formulaA;
    }


#ifdef LATER
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
        delete formulaA;
    }
#endif


    void TestPeptides::ParseNAndCTerminalChemicalFormula()
    {
        Peptide *peptide = new Peptide("[C2H3NO]-TTGSSSSSSSK-[C2H3NO]");
        ChemicalFormula *formulaA = new ChemicalFormula(ChemicalFormula::ParseFormula("C41H72N14O23"));
        ChemicalFormula *formulaB;
        formulaB = peptide->GetChemicalFormula();

        Assert::IsTrue(formulaA->Equals(formulaB));

        delete peptide;
        delete formulaA;
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

        std::string str = "";

        Assert::AreEqual(str, peptide->ToString());
        delete peptide;
    }

    void TestPeptides::ParseDoubleModificationToString()
    {
        Peptide *peptide = new Peptide("THGEAK[25.132]K");

        std::string str = "THGEAK[25.132]K";
        Assert::AreEqual(str, peptide->ToString());

        delete peptide;
    }

#ifdef LATER
    void TestPeptides::ParseNamedChemicalModificationInvalidName()
    {
        Assert::That([&] ()
        {
            new Peptide("T[TMT 7-plex]HGEAK[Acetyl]K");
        }, Throws::TypeOf<MzLibException*>());
    }

#endif
    
    void TestPeptides::SetAminoAcidModification()
    {
        auto Asparagine = Residue::GetResidue("N");
        auto tempVar = new OldSchoolChemicalFormulaModification(ChemicalFormula::ParseFormula("Fe"));

        _mockPeptideEveryAminoAcid->SetModification(tempVar, Asparagine);
        std::string str = "ACDEFGHIKLMN[Fe]PQRSTVWY";

        Assert::AreEqual(str, _mockPeptideEveryAminoAcid->ToString());
    }

    void TestPeptides::SetAminoAcidModificationStronglyTyped()
    {
        auto tempVar = new OldSchoolChemicalFormulaModification(ChemicalFormula::ParseFormula("Fe"));

        _mockPeptideEveryAminoAcid->SetModification(tempVar, ModificationSites::N);
        std::string str = "ACDEFGHIKLMN[Fe]PQRSTVWY";

        Assert::AreEqual(str, _mockPeptideEveryAminoAcid->ToString());
    }

    void TestPeptides::SetAminoAcidModificationStronglyTypedMultipleLocations()
    {
        auto tempVar = new OldSchoolChemicalFormulaModification(ChemicalFormula::ParseFormula("Fe"));

        // need overload of operator |
        _mockPeptideEveryAminoAcid->SetModification(tempVar, ModificationSites::N | ModificationSites::F | ModificationSites::V);
        std::string str = "ACDEF[Fe]GHIKLMN[Fe]PQRSTV[Fe]WY";
        
        Assert::AreEqual(str, _mockPeptideEveryAminoAcid->ToString());
    }

    void TestPeptides::SetAminoAcidModificationStronglyTypedAny()
    {
        auto tempVar = new OldSchoolChemicalFormulaModification(ChemicalFormula::ParseFormula("Fe"));

        _mockPeptideEveryAminoAcid->ClearModifications();
        _mockPeptideEveryAminoAcid->SetModification(tempVar, ModificationSites::Any);
        std::string str = "ACDEFGHIKLMNPQRSTVWY";

        Assert::AreEqual(str, _mockPeptideEveryAminoAcid->ToString());
    }

    void TestPeptides::SetAminoAcidModificationStronglyTypedAll()
    {
        auto tempVar = new OldSchoolChemicalFormulaModification(ChemicalFormula::ParseFormula("Fe"));

        _mockPeptideEveryAminoAcid->SetModification(tempVar, ModificationSites::All);
        std::string str = "[Fe]-A[Fe]C[Fe]D[Fe]E[Fe]F[Fe]G[Fe]H[Fe]I[Fe]K[Fe]L[Fe]M[Fe]N[Fe]P[Fe]Q[Fe]R[Fe]S[Fe]T[Fe]V[Fe]W[Fe]Y[Fe]-[Fe]";

        Assert::AreEqual(str, _mockPeptideEveryAminoAcid->ToString());
    }

    void TestPeptides::SetAminoAcidModificationStronglyTypedNone()
    {
        auto tempVar = new OldSchoolChemicalFormulaModification(ChemicalFormula::ParseFormula("Fe"));

        _mockPeptideEveryAminoAcid->ClearModifications();
        _mockPeptideEveryAminoAcid->SetModification(tempVar, ModificationSites::None);
        std::string str = "ACDEFGHIKLMNPQRSTVWY";

        Assert::AreEqual(str, _mockPeptideEveryAminoAcid->ToString());
    }

    void TestPeptides::SetAminoAcidModificationStronglyTypedTermini()
    {
        auto tempVar = new OldSchoolChemicalFormulaModification(ChemicalFormula::ParseFormula("Fe"));

        _mockPeptideEveryAminoAcid->ClearModifications();
        _mockPeptideEveryAminoAcid->SetModification(tempVar, ModificationSites::NPep | ModificationSites::PepC);
        std::string str = "[Fe]-ACDEFGHIKLMNPQRSTVWY-[Fe]";

        Assert::AreEqual(str, _mockPeptideEveryAminoAcid->ToString());
    }

    void TestPeptides::SetAminoAcidCharacterModification()
    {
        auto tempVar = new OldSchoolChemicalFormulaModification(ChemicalFormula::ParseFormula("Fe"));

        _mockPeptideEveryAminoAcid->ClearModifications();
        _mockPeptideEveryAminoAcid->SetModification(tempVar, 'D');
        std::string str = "ACD[Fe]EFGHIKLMNPQRSTVWY";

        Assert::AreEqual(str, _mockPeptideEveryAminoAcid->ToString());
    }

    void TestPeptides::SetResiduePositionModification()
    {
        auto tempVar = new OldSchoolChemicalFormulaModification(ChemicalFormula::ParseFormula("Fe"));

        _mockPeptideEveryAminoAcid->ClearModifications();
        _mockPeptideEveryAminoAcid->SetModification(tempVar, 5);
        std::string str = "ACDEF[Fe]GHIKLMNPQRSTVWY";

        Assert::AreEqual(str, _mockPeptideEveryAminoAcid->ToString());
    }

#ifdef LATER
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
#endif

    void TestPeptides::SetCTerminusModStringRepresentation()
    {
        auto tempVar = new OldSchoolChemicalFormulaModification(ChemicalFormula::ParseFormula("Fe"));

        _mockPeptideEveryAminoAcid->ClearModifications();
        _mockPeptideEveryAminoAcid->SetModification(tempVar, Terminus::C);
        std::string str = "ACDEFGHIKLMNPQRSTVWY-[Fe]";

        Assert::AreEqual(str, _mockPeptideEveryAminoAcid->ToString());
    }

    void TestPeptides::SetCTerminusModStringRepresentationofChemicalModification()
    {
        IHasChemicalFormula *formula = new OldSchoolChemicalFormulaModification(ChemicalFormula::ParseFormula("Fe"), "Test");

        _mockPeptideEveryAminoAcid->ClearModifications();
        _mockPeptideEveryAminoAcid->SetModification(formula, Terminus::C);
        std::string str = "ACDEFGHIKLMNPQRSTVWY-[Test]";

        Assert::AreEqual(str, _mockPeptideEveryAminoAcid->ToString());

        //delete formula;
    }

    void TestPeptides::SetNAndCTerminusMod()
    {
        auto tempVar = new OldSchoolChemicalFormulaModification(ChemicalFormula::ParseFormula("Fe"));
        _mockPeptideEveryAminoAcid->ClearModifications();

        _mockPeptideEveryAminoAcid->SetModification(tempVar, Terminus::C);

        auto tempVar2 = new OldSchoolChemicalFormulaModification(ChemicalFormula::ParseFormula("H2NO"));
        _mockPeptideEveryAminoAcid->SetModification(tempVar2, Terminus::N);
        std::string str = "[H2NO]-ACDEFGHIKLMNPQRSTVWY-[Fe]";

        Assert::AreEqual(str, _mockPeptideEveryAminoAcid->ToString());
    }

    void TestPeptides::SetSameNAndCTerminusMod()
    {
        auto tempVar = new OldSchoolChemicalFormulaModification(ChemicalFormula::ParseFormula("Fe"));
        _mockPeptideEveryAminoAcid->SetModification(tempVar, Terminus::C | Terminus::N);
        std::string str = "[Fe]-ACDEFGHIKLMNPQRSTVWY-[Fe]";

        Assert::AreEqual(str, _mockPeptideEveryAminoAcid->ToString());
    }

    void TestPeptides::ClearNTerminusMod()
    {
        auto tempVar = new OldSchoolChemicalFormulaModification(ChemicalFormula::ParseFormula("Fe"));
        _mockPeptideEveryAminoAcid->SetModification(tempVar, Terminus::N);

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
        std::string str = "ACDEFGHIKLMNPQRSTVWY";

        Assert::AreEqual(str, _mockPeptideEveryAminoAcid->ToString());
    }

    void TestPeptides::ClearModificationsBySites()
    {
        auto peptide = new Peptide("AC[Fe]DEFGHIKLMNP[Fe]QRSTV[Fe]WY");

        peptide->ClearModifications(ModificationSites::C | ModificationSites::V);
        std::string str = "ACDEFGHIKLMNP[Fe]QRSTVWY";

        Assert::AreEqual(str, peptide->ToString());

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
        std::string str = "";

        Assert::AreEqual(str, pepA->getBaseSequence());

        delete pepA;
    }

    void TestPeptides::EmptyPeptideFormulaIsH2O()
    {
        Peptide *pepA = new Peptide();
        ChemicalFormula *h2O = new ChemicalFormula(ChemicalFormula::ParseFormula("H2O"));
        ChemicalFormula *formulaB;
        formulaB = pepA->GetChemicalFormula();

        // Assert::AreEqual(h2O, formulaB);
        Assert::IsTrue(h2O->Equals(formulaB));

        delete pepA;
        delete h2O;
    }

    void TestPeptides::PeptideEquality()
    {
        Peptide *pepA = new Peptide("DEREK");
        Peptide *pepB = new Peptide("DEREK");
        // Assert::AreEqual(pepA, pepB);
        Assert::IsTrue(pepA->Equals(pepB));

        Peptide *pepC = new Peptide("DEREKK");
        // Assert::AreNotEqual(pepA, pepC);
        Assert::IsFalse(pepA->Equals(pepC));

        delete pepA;
        delete pepB;
        delete pepC;
    }

    void TestPeptides::PeptideInEqualityAminoAcidSwitch()
    {
        Peptide *pepA = new Peptide("DEREK");
        Peptide *pepB = new Peptide("DEERK");

        // Assert::AreNotEqual(pepA, pepB);
        Assert::IsFalse(pepA->Equals(pepB));

        delete pepA;
        delete pepB;
    }

    void TestPeptides::PeptideInEqualityAminoAcidModification()
    {
        Peptide *pepA = new Peptide("DEREK");
        Peptide *pepB = new Peptide("DEREK");
        OldSchoolChemicalFormulaModification tempVar(ChemicalFormula::ParseFormula("H2O"));
        pepB->SetModification(&tempVar, 'R');

        // Assert::AreNotEqual(pepA, pepB);
        Assert::IsFalse(pepA->Equals(pepB));

        OldSchoolChemicalFormulaModification tempVar2(ChemicalFormula::ParseFormula("H2O2"));
        pepA->SetModification(&tempVar2, 'R');
        Assert::AreNotEqual(pepA, pepB);

        // this causes seg fault
        Assert::IsFalse(pepA->Equals(pepB));

        delete pepA;
        delete pepB;
    }


    void TestPeptides::PeptideCloneEquality()
    {
        Peptide *pepA = new Peptide("DEREK");
        Peptide *pepB = new Peptide(pepA);

        // Assert::AreEqual(pepA, pepB);
        Assert::IsTrue(pepA->Equals(pepB));

        delete pepA;
        delete pepB;
    }

    void TestPeptides::PeptideCloneNotSameReference()
    {
        Peptide *pepA = new Peptide("DEREK");
        Peptide *pepB = new Peptide(pepA);

        // Assert::AreNotSame(pepA, pepB);
        Assert::AreNotEqual(pepA, pepB);

        delete pepA;
        delete pepB;    
    }

    void TestPeptides::PeptideCloneWithModifications()
    {
        Peptide *pepA = new Peptide("DER[Fe]EK");
        Peptide *pepB = new Peptide(pepA);
        std::string str = "DER[Fe]EK";

        Assert::AreEqual(str, pepB->ToString());

        delete pepA;
        delete pepB;
    }

    void TestPeptides::PeptideCloneWithoutModifications()
    {
        Peptide *pepA = new Peptide("DER[Fe]EK");
        Peptide *pepB = new Peptide(pepA, false);
        std::string str = "DEREK";

        Assert::AreEqual(str, pepB->ToString());

        delete pepA;
        delete pepB;
    }

    void TestPeptides::PeptideCloneWithModification()
    {
        Peptide *pepA = new Peptide("DEREK");
        OldSchoolChemicalFormulaModification tempVar(ChemicalFormula::ParseFormula("H2O"));
        pepA->SetModification(&tempVar, 'R');
        Peptide *pepB = new Peptide(pepA);

        Assert::IsTrue(pepA->Equals(pepB));

        delete pepA;
        delete pepB;
    }

    void TestPeptides::PeptideParitalCloneInternal()
    {
        Peptide *pepA = new Peptide("DEREK");
        Peptide *pepB = new Peptide(pepA, 1, 3);
        Peptide *pepC = new Peptide("ERE");

        std::string peptideB = pepB->ToString();
        std::string peptideC = pepC->ToString();

        // this test is False but should be True also compares memory references rather than peptide strings
        // Assert::AreEqual(pepB, pepC);

        // This test is False but should be True
        Assert::IsTrue(pepB->Equals(pepC));

        // This test is True, but both strings have the same extra charaters
        Assert::AreEqual(peptideB, peptideC);

        delete pepA;
        delete pepB;
        delete pepC;
    }

    void TestPeptides::PeptideParitalClonelWithInternalModification()
    {
        Peptide *pepA = new Peptide("DER[Fe]EK");
        Peptide *pepB = new Peptide(pepA, 2, 3);
        Peptide *pepC = new Peptide("R[Fe]EK");

        Assert::IsTrue(pepB->Equals(pepC));

        delete pepA;
        delete pepB;
        delete pepC;
    }

    void TestPeptides::PeptideHashing()
    {
        // Edgar; will not fix this test
        Peptide pep1("DEREK");
        Peptide pep2("DEREKN");
        Peptide pep3("DEREKM");
        Peptide pep4("DEREKM");
        std::unordered_set<Peptide*> uu = {&pep1, &pep2, &pep3, &pep4};
        Peptide tempVar("DEREKN");
        uu.insert(&tempVar);
        Assert::AreEqual(3, static_cast<int>(uu.size()));

    }


    void TestPeptides::ClearMods()
    {
        Peptide *pepA = new Peptide("DE[Al]R[Fe]EK");
        OldSchoolChemicalFormulaModification tempVar(ChemicalFormula::ParseFormula("Al"));
        pepA->ClearModifications(&tempVar);

        std::string s1 = "DER[Fe]EK";
        Assert::AreEqual(s1, pepA->ToString());

        OldSchoolChemicalFormulaModification tempVar2(ChemicalFormula::ParseFormula("C"));
        pepA->ClearModifications(&tempVar2);

        Assert::AreEqual(s1, pepA->ToString());
        pepA->ClearModifications();

        std::string s2 = "DEREK";
        Assert::AreEqual(s2, pepA->ToString());
        pepA->ClearModifications();

        Assert::AreEqual(s2, pepA->ToString());
        pepA->ClearModifications(ModificationSites::Any);

        Assert::AreEqual(s2, pepA->ToString());
        pepA->ClearModifications(Terminus::C);

        Assert::AreEqual(s2, pepA->ToString());

        delete pepA;
    }



    void TestPeptides::PeptideParitalClonelWithInternalModificationTwoMods()
    {
        Peptide *pepA = new Peptide("DE[Al]R[Fe]EK");
        Peptide *pepB = new Peptide(pepA, 2, 3);
        Peptide *pepC = new Peptide("R[Fe]EK");

        Assert::IsTrue(pepB->Equals(pepC));

        delete pepA;
        delete pepB;
        delete pepC;
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

        Assert::IsTrue(pepB->Equals(pepC));

        delete pepA;
        delete pepB;
        delete pepC;
    }

    void TestPeptides::GetLeucineSequence()
    {
        Peptide *pepA = new Peptide("DERIEK");
        std::string leuSeq = pepA->getBaseLeucineSequence();
        std::string str = "DERLEK";

        // should there be a modification or should this equal DERIEK?
        Assert::AreEqual(str, leuSeq);

        delete pepA;
    }

    void TestPeptides::GetLeucineSequenceNoReplacement()
    {
        Peptide *pepA = new Peptide("DERLEK");

        std::string leuSeq = pepA->getBaseLeucineSequence();
        std::string str = "DERLEK";

        Assert::AreEqual(str, leuSeq);

        delete pepA;
    }

#ifdef LATER
    void TestPeptides::GetSequenceCoverage()
    {
        Peptide *pepA = new Peptide("DERLEK");
        Peptide *pepAa = new Peptide("ER");
        Peptide *pepAb = new Peptide("RL");
        Peptide *pepAc = new Peptide("LEK");
        std::vector<Peptide*> myList = {pepAa, pepAb, pepAc};

        // error: ‘class Proteomics::AminoAcidPolymer::Peptide’ has no member named ‘GetSequenceCoverage’
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

        // error: ‘class Proteomics::AminoAcidPolymer::Peptide’ has no member named ‘GetSequenceCoverageFraction’;
        Assert::AreEqual(0.5, pepA->GetSequenceCoverageFraction(myList));

        delete pepAb;
        delete pepAa;
        delete pepA;
    }
#endif

    void TestPeptides::TerminusModification()
    {
        Peptide *pepA = new Peptide("DERLEK");
        OldSchoolChemicalFormulaModification tempVar(ChemicalFormula::ParseFormula("SO"));
        pepA->AddModification(&tempVar, Terminus::N);
        std::string str = "[OS]-DERLEK";
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual(str, pepA->ToString());

        delete pepA;
    }

#ifdef LATER
    void TestPeptides::DigestionTest()
    {
        IProtease *protease = new TestProtease();
        Assert::AreEqual(6, AminoAcidPolymer::Digest(_mockPeptideEveryAminoAcid, protease).size()());

//C# TO C++ CONVERTER TODO TASK: A 'delete protease' statement was not added since protease was passed to a method or constructor. Handle memory management manually.
    }
#endif

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

        // Assert::AreEqual(ok, A->GetChemicalFormula());
        Assert::IsTrue(ok->Equals(A->GetChemicalFormula()));

        delete A;
        delete ok;
    }

#ifdef LATER
    void TestPeptides::TestChemicalFormula2()
    {
        Peptide *A = new Peptide("A");
        OldSchoolModification *a = new OldSchoolModification(1, "Modification without chemical formula", ModificationSites::A);
        A->AddModification(a);
        Assert::Throws<MzLibException*>([&] ()
        {
            A->GetChemicalFormula();
        }, "Modification Modification without chemical formula does not have a chemical formula!");

        //C# TO C++ CONVERTER TODO TASK: A 'delete a' statement was not added since a was passed to a
        // method or constructor. Handle memory management manually.
        delete A;
        delete a;
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
#endif

    void TestPeptides::TestAApolymerContains()
    {
        Assert::IsFalse(_mockTrypticPeptide->Contains('A'));
        Assert::IsTrue(_mockTrypticPeptide->Contains(Residue::GetResidue('T')));
    }

    void TestPeptides::TestLeucineSequence()
    {
    	std::string str1 = "ACDEFGHLKLMNPQRSTVWY";
        Assert::AreEqual(str1, _mockPeptideEveryAminoAcid->GetSequenceWithModifications(true));
        Assert::AreEqual(20, _mockPeptideEveryAminoAcid->ResidueCount());
        Assert::AreEqual(7, _mockTrypticPeptide->ResidueCount('S'));
        Assert::AreEqual(7, _mockTrypticPeptide->ResidueCount(Residue::GetResidue('S')));
        Assert::AreEqual(2, _mockTrypticPeptide->ResidueCount(Residue::GetResidue('S'), 2, 3));
        Assert::AreEqual(3, _mockTrypticPeptide->ResidueCount('S', 2, 4));

        Peptide *peptide = new Peptide("III-[C2H3NO]");
        std::string str2 = "LLL-[C2H3NO]";
        Assert::AreEqual(str2, peptide->GetSequenceWithModifications(true));

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
        std::string str = "LLL";
        Assert::AreEqual(str, peptide->GetSequenceWithModifications());

        delete peptide;
        delete a;
    }

    void TestPeptides::TestGetSubPeptide()
    {
        Peptide *pep = new Peptide("DERLEK");
        Peptide tempVar("LE");

        Peptide *subpep = pep->GetSubPeptide(3, 2);
        Assert::IsTrue(subpep->Equals(&tempVar));

        delete pep;
    }

    void TestPeptides::TestRealPeptideWithModifications()
    {
        Peptide *a = new Peptide("LDNLQQEIDFLTALYQAELSQM[O]QTQISETNVILSM[O]DNNR");
        Assert::AreEqual(2, a->ModificationCount());

        delete a;
    }

#ifdef LATER
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
#endif

    void TestPeptides::TestNonSpecificOverride()
    {
        std::string trypsin = "trypsin";
        std::string singleN = "singleN";
        std::string singleC = "singleC";
        DigestionParams *digestionParams = new DigestionParams(trypsin);
        Assert::AreEqual(digestionParams->getProtease()->getName(), trypsin);

        digestionParams = new DigestionParams(trypsin, 2, 7, std::numeric_limits<int>::max(), 1024, InitiatorMethionineBehavior::Variable, 2, CleavageSpecificity::None, FragmentationTerminus::N);
        Assert::AreEqual(digestionParams->getProtease()->getName(), singleN);
        Assert::AreEqual(digestionParams->getSpecificProtease()->getName(), trypsin);

        digestionParams = new DigestionParams(trypsin, 2, 7, std::numeric_limits<int>::max(), 1024, InitiatorMethionineBehavior::Variable, 2, CleavageSpecificity::None, FragmentationTerminus::C);
        Assert::AreEqual(digestionParams->getProtease()->getName(), singleC);
        Assert::AreEqual(digestionParams->getSpecificProtease()->getName(), trypsin);

        delete digestionParams;
    }

#ifdef LATER
    bool TestPeptides::OkComparer::Equals(DigestionPointAndLength *x, DigestionPointAndLength *y)
    {
        return x->getIndex().Equals(y->getIndex()) && x->getLength().Equals(y->getLength());
    }

    int TestPeptides::OkComparer::GetHashCode(DigestionPointAndLength *obj)
    {
        return obj->getLength() + obj->getIndex() * 256;
    }
#endif
    
    std::vector<int> TestProtease::GetDigestionSites(AminoAcidPolymer *aminoAcidSequence)
    {
        return GetDigestionSites(aminoAcidSequence->getBaseSequence());
    }

    std::vector<int> TestProtease::GetDigestionSites(const std::string &aminoAcidSequence)
    {
        std::vector<int> res = {4,5};
        return res;
    }

    int TestProtease::MissedCleavages(AminoAcidPolymer *aminoAcidSequence)
    {
        throw NotImplementedException();
    }

    int TestProtease::MissedCleavages(const std::string &sequence)
    {
        throw NotImplementedException();
    }
}
