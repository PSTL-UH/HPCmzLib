#include "TestChemicalFormula.h"
#include "../Chemistry/Element.h"
#include "../Chemistry/PeriodicTable.h"
#include "../MzLibUtil/MzLibException.h"
#include "../Chemistry/ChemicalFormula.h"
#include "../Chemistry/Isotope.h"
#include "../Chemistry/IsotopicDistribution.h"
#include "../UsefulProteomicsDatabases/PeriodicTableLoader.h"

using namespace Chemistry;
using namespace MzLibUtil;

#include "Assert.h"

int main ( int argc, char **argv )
{
    int i=0;
    std::cout << i << ". PeriodicTableLoader" << std::endl;    
    const std::string elfile="elements.dat";
    const std::string &elr=elfile;
    UsefulProteomicsDatabases::PeriodicTableLoader::Load (elr);
    
#ifdef LATER
    // throws an exception
    std::cout << ++i << ". AddIsotopeWithExistingMassNumber" << std::endl;    
    Test::ChemicalFormulaTestFixture::AddIsotopeWithExistingMassNumber();
#endif
    
    std::cout << ++i << ". AddElementToFormula" << std::endl;    
    Test::ChemicalFormulaTestFixture::AddElementToFormula();

    std::cout << ++i << ". Multiply" << std::endl;    
    Test::ChemicalFormulaTestFixture::Multiply();

    std::cout << ++i << ". CheckToStringOfElements" << std::endl;    
    Test::ChemicalFormulaTestFixture::CheckToStringOfElements();

    std::cout << ++i << ". AddFormulaToFormula" << std::endl;    
    Test::ChemicalFormulaTestFixture::AddFormulaToFormula();

    std::cout << ++i << ". AddFormulaToItself" << std::endl;    
    Test::ChemicalFormulaTestFixture::AddFormulaToItself();

    std::cout << ++i << ". AddIChemicalFormulaToFormula" << std::endl;    
    Test::ChemicalFormulaTestFixture::AddIChemicalFormulaToFormula();
    
    std::cout << ++i << ". AddIsotopeToFormula" << std::endl;
    Test::ChemicalFormulaTestFixture::AddIsotopeToFormula();

    std::cout << ++i << ". AddLargeElementToFormula" << std::endl;    
    Test::ChemicalFormulaTestFixture::AddLargeElementToFormula();

    std::cout << ++i << ". AddNegativeFormulaToFormula" << std::endl;    
    Test::ChemicalFormulaTestFixture::AddNegativeFormulaToFormula();
    
    std::cout << ++i << ". AddNegativeIsotopeToFormula" << std::endl;    
    Test::ChemicalFormulaTestFixture::AddNegativeIsotopeToFormula();

    std::cout << ++i << ". AddELementByAtomicNumber" << std::endl;    
    Test::ChemicalFormulaTestFixture::AddELementByAtomicNumber();

#ifdef LATER
    // These two elements
    std::cout << ++i << ". " << std::endl;    
    Test::ChemicalFormulaTestFixture::AddNonExistentSymbolToFormula();

    std::cout << ++i << ". " << std::endl;    
    Test::ChemicalFormulaTestFixture::InexistingElement();
#endif 
    std::cout << ++i << ". AddZeroELementToFormula" << std::endl;    
    Test::ChemicalFormulaTestFixture::AddZeroElementToFormula();

    std::cout << ++i << ". AddZeroIsotopeToFormula" << std::endl;    
    Test::ChemicalFormulaTestFixture::AddZeroIsotopeToFormula();

    std::cout << ++i << ". AddZeroSymbolToFormula" << std::endl;    
    Test::ChemicalFormulaTestFixture::AddZeroSymbolToFormula();

    std::cout << ++i << ". ClearFormula" << std::endl;    
    Test::ChemicalFormulaTestFixture::ClearFormula();

    std::cout << ++i << ". ConstructorBlankStringEqualsEmptyFormula" << std::endl;    
    Test::ChemicalFormulaTestFixture::ConstructorBlankStringEqualsEmptyFormula();

#ifdef LATER
    // is identical to the previous one in C++ version
    std::cout << ++i << ". ConstructorDefaultEqualsEmptyFormula" << std::endl;    
    Test::ChemicalFormulaTestFixture::ConstructorDefaultEqualsEmptyFormula();
#endif

    std::cout << ++i << ". CopyConstructorValueEquality" << std::endl;    
    Test::ChemicalFormulaTestFixture::CopyConstructorValueEquality();

    std::cout << ++i << ". CopyConstructorReferenceInequality" << std::endl;    
    Test::ChemicalFormulaTestFixture::CopyConstructorReferenceInequality();

    std::cout << ++i << ". EmptyMonoisotopicMassIsZero" << std::endl;    
    Test::ChemicalFormulaTestFixture::EmptyMonoisotopicMassIsZero();

    std::cout << ++i << ". EmptyAverageMassIsZero" << std::endl;    
    Test::ChemicalFormulaTestFixture::EmptyAverageMassIsZero();

    std::cout << ++i << ". EmptyStringIsBlank" << std::endl;    
    Test::ChemicalFormulaTestFixture::EmptyStringIsBlank();

    std::cout << ++i << ". EmptyAtomCountIsZero" << std::endl;    
    Test::ChemicalFormulaTestFixture::EmptyAtomCountIsZero();

    std::cout << ++i << ". EmptyElementCountIsZero" << std::endl;    
    Test::ChemicalFormulaTestFixture::EmptyElementCountIsZero();

    std::cout << ++i << ". EmptyIsotopeCountIsZero" << std::endl;    
    Test::ChemicalFormulaTestFixture::EmptyIsotopeCountIsZero();

    std::cout << ++i << ". FormulaValueInequality" << std::endl;    
    Test::ChemicalFormulaTestFixture::FormulaValueInequality();

    std::cout << ++i << ". FormulaValueInequalityHeavyIsotope" << std::endl;    
    Test::ChemicalFormulaTestFixture::FormulaValueInequalityHeavyIsotope();

    std::cout << ++i << ". FormulaValueEqualityItself" << std::endl;    
    Test::ChemicalFormulaTestFixture::FormulaValueEqualityItself();

    std::cout << ++i << ". FormulaValueEquality" << std::endl;    
    Test::ChemicalFormulaTestFixture::FormulaValueEquality();

    std::cout << ++i << ". FormulaEquality" << std::endl;    
    Test::ChemicalFormulaTestFixture::FormulaEquality();

    std::cout << ++i << ". FormulaAlmostEquality" << std::endl;    
    Test::ChemicalFormulaTestFixture::FormulaAlmostEquality();

    std::cout << ++i << ". HashCodeEquality" << std::endl;    
    Test::ChemicalFormulaTestFixture::HashCodeEquality();

    std::cout << ++i << ". HashCodeImmutableEquality" << std::endl;    
    Test::ChemicalFormulaTestFixture::HashCodeImmutableEquality();

    std::cout << ++i << ". HashCodeCheck" << std::endl;    
    Test::ChemicalFormulaTestFixture::HashCodeCheck();

    std::cout << ++i << ". HillNotation" << std::endl;    
    Test::ChemicalFormulaTestFixture::HillNotation();

    std::cout << ++i << ". HillNotationNoCarbon" << std::endl;    
    Test::ChemicalFormulaTestFixture::HillNotationNoCarbon();

    std::cout << ++i << ". HillNotationNoCarbonNoHydrogen" << std::endl;    
    Test::ChemicalFormulaTestFixture::HillNotationNoCarbonNoHydrogen();

    std::cout << ++i << ". HillNotationNoHydrogen" << std::endl;    
    Test::ChemicalFormulaTestFixture::HillNotationNoHydrogen();

    std::cout << ++i << ". HillNotationWithHeavyIsotope" << std::endl;    
    Test::ChemicalFormulaTestFixture::HillNotationWithHeavyIsotope();

    std::cout << ++i << ". HillNotationWithNegativeCount" << std::endl;    
    Test::ChemicalFormulaTestFixture::HillNotationWithNegativeCount();

    std::cout << ++i << ". HillNotationWithHeavyIsotopeNegativeCount" << std::endl;    
    Test::ChemicalFormulaTestFixture::HillNotationWithHeavyIsotopeNegativeCount();

#ifdef LATER
    //uses exceptions
    std::cout << ++i << ". BadFormula" << std::endl;    
    Test::ChemicalFormulaTestFixture::BadFormula();

    std::cout << ++i << ". InvalidChemicalElement" << std::endl;    
    Test::ChemicalFormulaTestFixture::InvalidChemicalElement();
#endif

    std::cout << ++i << ". InvalidElementIsotope" << std::endl;    
    Test::ChemicalFormulaTestFixture::InvalidElementIsotope();

    std::cout << ++i << ". NumberOfAtoms" << std::endl;    
    Test::ChemicalFormulaTestFixture::NumberOfAtoms();

    std::cout << ++i << ". NumberOfAtomsOfEmptyFormula" << std::endl;    
    Test::ChemicalFormulaTestFixture::NumberOfAtomsOfEmptyFormula();

    std::cout << ++i << ". NumberOfAtomsOfNegativeFormula" << std::endl;    
    Test::ChemicalFormulaTestFixture::NumberOfAtomsOfNegativeFormula();

    std::cout << ++i << ". ParsingFormulaNoNumbers" << std::endl;    
    Test::ChemicalFormulaTestFixture::ParsingFormulaNoNumbers();

    std::cout << ++i << ". ParsingFormulaWithInternalSpaces" << std::endl;    
    Test::ChemicalFormulaTestFixture::ParsingFormulaWithInternalSpaces();

    std::cout << ++i << ". ParsingFormulaWithSpacesAtEnd" << std::endl;    
    Test::ChemicalFormulaTestFixture::ParsingFormulaWithSpacesAtEnd();

    std::cout << ++i << ". ParsingFormulaWithSpacesAtBeginning" << std::endl;    
    Test::ChemicalFormulaTestFixture::ParsingFormulaWithSpacesAtBeginning();

    std::cout << ++i << ". ParsingFormulaWithSpaces" << std::endl;    
    Test::ChemicalFormulaTestFixture::ParsingFormulaWithSpaces();

    std::cout << ++i << ". ParsingFormulaNoNumbersRandomOrder" << std::endl;    
    Test::ChemicalFormulaTestFixture::ParsingFormulaNoNumbersRandomOrder();

    std::cout << ++i << ". EqualsFalse" << std::endl;    
    Test::ChemicalFormulaTestFixture::EqualsFalse();

    std::cout << ++i << ". Equals" << std::endl;    
    Test::ChemicalFormulaTestFixture::Equals();

    std::cout << ++i << ". ParsingFormulaRepeatedElements" << std::endl;    
    Test::ChemicalFormulaTestFixture::ParsingFormulaRepeatedElements();

    std::cout << ++i << ". IsSuperSetOf" << std::endl;    
    Test::ChemicalFormulaTestFixture::IsSuperSetOf();

    //False but should be true.  Issue with parsing '-' symbol
    std::cout << ++i << ". ParsingFormulaRepeatedElementsCancelEachOther" << std::endl;    
    Test::ChemicalFormulaTestFixture::ParsingFormulaRepeatedElementsCancelEachOther();

    std::cout << ++i << ". RemoveElementCompletelyFromFromula" << std::endl;    
    Test::ChemicalFormulaTestFixture::RemoveElementCompletelyFromFromula();

    std::cout << ++i << ". RemoveElementCompletelyFromFromulaBySymbol" << std::endl;    
    Test::ChemicalFormulaTestFixture::RemoveElementCompletelyFromFromulaBySymbol();

    std::cout << ++i << ". RemoveElementCompletelyFromFromulaWithHeavyIsotope" << std::endl;    
    Test::ChemicalFormulaTestFixture::RemoveElementCompletelyFromFromulaWithHeavyIsotope();

    std::cout << ++i << ". RemoveEmptyFormulaFromFromula" << std::endl;    
    Test::ChemicalFormulaTestFixture::RemoveEmptyFormulaFromFromula();

    std::cout << ++i << ". RemoveFormulaFromFromula" << std::endl;    
    Test::ChemicalFormulaTestFixture::RemoveFormulaFromFromula();

#ifdef LATER
    //uses CountWithIsotopes function that is not correctly implemented in C++ version
    std::cout << ++i << ". ContainsSpecificIsotope" << std::endl;    
    Test::ChemicalFormulaTestFixture::ContainsSpecificIsotope();

    std::cout << ++i << ". ContainsIsotopesOf" << std::endl;    
    Test::ChemicalFormulaTestFixture::ContainsIsotopesOf();

    std::cout << ++i << ". HydrogenCarbonRatio" << std::endl;    
    Test::ChemicalFormulaTestFixture::HydrogenCarbonRatio();
#endif

    std::cout << ++i << ". RemoveIsotopeCompletelyFromFromula" << std::endl;    
    Test::ChemicalFormulaTestFixture::RemoveIsotopeCompletelyFromFromula();

    std::cout << ++i << ". RemoveElementFromFromula" << std::endl;    
    Test::ChemicalFormulaTestFixture::RemoveElementFromFromula();

    std::cout << ++i << ". RemoveIsotopeFromFromulaEquality" << std::endl;    
    Test::ChemicalFormulaTestFixture::RemoveIsotopeFromFromulaEquality();

    std::cout << ++i << ". RemoveNegativeElementFromFromula" << std::endl;    
    Test::ChemicalFormulaTestFixture::RemoveNegativeElementFromFromula();

    //False but should be true.  Issue with parsing '-' symbol
    std::cout << ++i << ". RemoveNonExistantIsotopeFromFromula" << std::endl;    
    Test::ChemicalFormulaTestFixture::RemoveNonExistantIsotopeFromFromula();

#ifdef LATER
    //uses CountWithIsotopes function that is not correctly implemented in C++ version
    std::cout << ++i << ". RemoveZeroIsotopeFromFromula" << std::endl;    
    Test::ChemicalFormulaTestFixture::RemoveZeroIsotopeFromFromula();
#endif

    std::cout << ++i << ". TotalProtons" << std::endl;    
    Test::ChemicalFormulaTestFixture::TotalProtons();

    std::cout << ++i << ". TotalProtons2" << std::endl;    
    Test::ChemicalFormulaTestFixture::TotalProtons2();

    std::cout << ++i << ". AverageMass" << std::endl;    
    Test::ChemicalFormulaTestFixture::AverageMass();

    std::cout << ++i << ". UniqueElements" << std::endl;    
    Test::ChemicalFormulaTestFixture::UniqueElements();

    std::cout << ++i << ". UniqueElementsOfEmptyFormula" << std::endl;    
    Test::ChemicalFormulaTestFixture::UniqueElementsOfEmptyFormula();

    std::cout << ++i << ". UniqueElementsWithHeavyIsotope" << std::endl;    
    Test::ChemicalFormulaTestFixture::UniqueElementsWithHeavyIsotope();

    std::cout << ++i << ". UniqueIsotopes" << std::endl;    
    Test::ChemicalFormulaTestFixture::UniqueIsotopes();

    std::cout << ++i << ". UniqueIsotopesOfEmptyFormula" << std::endl;    
    Test::ChemicalFormulaTestFixture::UniqueIsotopesOfEmptyFormula();

    std::cout << ++i << ". UniqueIsotopesWithHeavyIsotope" << std::endl;    
    Test::ChemicalFormulaTestFixture::UniqueIsotopesWithHeavyIsotope();

    std::cout << ++i << ". ContainsIsotopesOfYe" << std::endl;    
    Test::ChemicalFormulaTestFixture::ContainsIsotopesOfYe();

#ifdef LATER // Uses IsotopicsDistribution::GetDistribution() which is not correct in C++ version
    std::cout << ++i << ". TestReplaceIsotopes" << std::endl;    
    Test::ChemicalFormulaTestFixture::TestReplaceIsotopes();
#endif

    std::cout << ++i << ". ChemicalForulaIsSubSet" << std::endl;    
    Test::ChemicalFormulaTestFixture::ChemicalForulaIsSubSet();

    std::cout << ++i << ". ChemicalForulaIsNotSubSet" << std::endl;    
    Test::ChemicalFormulaTestFixture::ChemicalForulaIsNotSubSet();

    std::cout << ++i << ". ChemicalForulaIsSuperSet" << std::endl;    
    Test::ChemicalFormulaTestFixture::ChemicalForulaIsSuperSet();

    std::cout << ++i << ". ChemicalForulaIsNotSuperSet" << std::endl;    
    Test::ChemicalFormulaTestFixture::ChemicalForulaIsNotSuperSet();

    std::cout << ++i << ". ChemicalForulaMyTest" << std::endl;    
    Test::ChemicalFormulaTestFixture::ChemicalForulaMyTest();

#ifdef LATER // Uses IsotopicsDistribution::GetDistribution() which is not correct in C++ version
    std::cout << ++i << ". TestIsotopicDistribution" << std::endl;    
    Test::ChemicalFormulaTestFixture::TestIsotopicDistribution();

    std::cout << ++i << ". TestIsotopicDistribution2" << std::endl;    
    Test::ChemicalFormulaTestFixture::TestIsotopicDistribution2();

    std::cout << ++i << ". TestIsotopicDistribution3" << std::endl;    
    Test::ChemicalFormulaTestFixture::TestIsotopicDistribution3();

    std::cout << ++i << ". CatchIsotopicDistributionStuff" << std::endl;    
    Test::ChemicalFormulaTestFixture::CatchIsotopicDistributionStuff();

    std::cout << ++i << ". CatchProbStuff" << std::endl;    
    Test::ChemicalFormulaTestFixture::CatchProbStuff();

    std::cout << ++i << ". I0j1" << std::endl;    
    Test::ChemicalFormulaTestFixture::I0j1();

    std::cout << ++i << ". ThresholdProbability" << std::endl;    
    Test::ChemicalFormulaTestFixture::ThresholdProbability();
#endif

    std::cout << ++i << ". TestAnotherFormula" << std::endl;    
    Test::ChemicalFormulaTestFixture::TestAnotherFormula();

    std::cout << ++i << ". NeutronCount" << std::endl;    
    Test::ChemicalFormulaTestFixture::NeutronCount();

#ifdef LATER //Throws exception
    std::cout << ++i << ". NeutronCountFail" << std::endl;    
    Test::ChemicalFormulaTestFixture::NeutronCountFail();
#endif

    std::cout << ++i << ". CombineTest" << std::endl;    
    Test::ChemicalFormulaTestFixture::CombineTest();

    std::cout << ++i << ". ValidatePeriodicTable" << std::endl;
    Test::ChemicalFormulaTestFixture::ValidatePeriodicTable();

    std::cout << ++i << ". TestAddChemicalFormula" << std::endl;    
    Test::ChemicalFormulaTestFixture::TestAddChemicalFormula();

    std::cout << ++i << ". NotEqual" << std::endl;    
    Test::ChemicalFormulaTestFixture::NotEqual();

    std::cout << ++i << ". TestRemoveObjectFromChemicalFormula" << std::endl;    
    Test::ChemicalFormulaTestFixture::TestRemoveObjectFromChemicalFormula();

    std::cout << ++i << ". TestEquality" << std::endl;    
    Test::ChemicalFormulaTestFixture::TestEquality();

    std::cout << ++i << ". TestToChemicalFormula" << std::endl;    
    Test::ChemicalFormulaTestFixture::TestToChemicalFormula();

#ifdef LATER // Uses IsotopicsDistribution::GetDistribution() which is not correct in C++ version
    std::cout << ++i << ".  IsoTest" << std::endl;    
    Test::ChemicalFormulaTestFixture::IsoTest();    
#endif

    return 0;
}

namespace Test {

#ifdef LATER
    void ChemicalFormulaTestFixture::AddIsotopeWithExistingMassNumber() {
        Element *al = PeriodicTable::GetElement("Al");
        Assert::Throws<MzLibException*>([&] () {
            al->AddIsotope(27, 28, 1);
        }, "Isotope with mass number " + std::to_string(28) + " already exists");
    }
#endif

    void ChemicalFormulaTestFixture::AddElementToFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H3N2O");

        Element *n = PeriodicTable::GetElement(7);

        formulaA->Add(n, 1);

        Assert::IsTrue(formulaA->Equals(formulaB));
    }

    void ChemicalFormulaTestFixture::Multiply() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        formulaA->Multiply(2);
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C4H6N2O2");

        Assert::IsTrue(formulaA->Equals(formulaB));
        Assert::IsFalse(formulaA->Equals(nullptr));
    }

    void ChemicalFormulaTestFixture::CheckToStringOfElements() {
        Element *n = PeriodicTable::GetElement("N");
        std::string a = n->ToString();
        std::string b = "N";
        Assert::AreEqual(a, b);
    }

    void ChemicalFormulaTestFixture::AddFormulaToFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("H2O");
        ChemicalFormula *formulaC = ChemicalFormula::ParseFormula("C2H5NO2");

        formulaA->Add(formulaB);

        Assert::IsTrue(formulaA->Equals(formulaC));
    }

    void ChemicalFormulaTestFixture::AddFormulaToItself() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C4H6N2O2");

        ChemicalFormula tempVar(formulaA);
        formulaA->Add(&tempVar);

        Assert::IsTrue(formulaA->Equals(formulaB));
    }

    
    void ChemicalFormulaTestFixture::AddIChemicalFormulaToFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        IHasChemicalFormula *formulaB = new PhysicalObjectWithChemicalFormula("H2O");
        ChemicalFormula *formulaC = ChemicalFormula::ParseFormula("C2H5NO2");

        formulaA->Add(formulaB);

        Assert::IsTrue(formulaA->Equals(formulaC));
        delete formulaB;
    }
    
    void ChemicalFormulaTestFixture::AddIsotopeToFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H3H{1}NO");
        Isotope *h1 = PeriodicTable::GetElement("H")->getIsotopeByMassNumber(1);

        formulaA->Add(h1, 1);

        Assert::IsTrue(formulaA->Equals(formulaB));

    }

    void ChemicalFormulaTestFixture::AddLargeElementToFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H3NOFe");

        Element *fe = PeriodicTable::GetElement("Fe");

        formulaA->Add(fe, 1);

        Assert::IsTrue(formulaA->Equals(formulaB));
    }

    void ChemicalFormulaTestFixture::AddNegativeFormulaToFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C-1H-2");
        ChemicalFormula *formulaC = ChemicalFormula::ParseFormula("CHNO");

        formulaA->Add(formulaB);

        Assert::IsTrue(formulaA->Equals( formulaC));
    }

    void ChemicalFormulaTestFixture::AddNegativeIsotopeToFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2HH{1}2NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2HNO");

        Isotope *h1 = PeriodicTable::GetElement("H")->getIsotopeByMassNumber(1);

        formulaA->Add(h1, -2);

        Assert::IsTrue(formulaA->Equals(formulaB));

    }

    void ChemicalFormulaTestFixture::AddELementByAtomicNumber() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H2NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2HNO");

        formulaB->Add(1, 1);

        Assert::IsTrue(formulaA->Equals(formulaB));
    }

#ifdef LATER    
    void ChemicalFormulaTestFixture::AddNonExistentSymbolToFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");

        Assert::Throws<KeyNotFoundException*>([&] () {
            formulaA->AddPrincipalIsotopesOf("Faa", 1);
        });
    }

    void ChemicalFormulaTestFixture::InexistingElement() {
        Assert::Throws<KeyNotFoundException*>([&] () {
            ChemicalFormula::ParseFormula("Q");
        });
    }

#endif
    
    void ChemicalFormulaTestFixture::AddZeroElementToFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H3NO");

        Element *n = PeriodicTable::GetElement("N");

        formulaA->Add(n, 0);

        Assert::IsTrue(formulaA->Equals(formulaB));
    }

    void ChemicalFormulaTestFixture::AddZeroIsotopeToFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H3NO");

        Isotope *h1 = PeriodicTable::GetElement("H")->getIsotopeByMassNumber(1);

        formulaA->Add(h1, 0);

        Assert::IsTrue(formulaA->Equals(formulaB));
    }

    void ChemicalFormulaTestFixture::AddZeroSymbolToFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H3NO");

        formulaA->AddPrincipalIsotopesOf(PeriodicTable::GetElement("H"), 0);

        Assert::IsTrue(formulaA->Equals(formulaB));
    }

    void ChemicalFormulaTestFixture::ClearFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        formulaA->Clear();
        ChemicalFormula tempVar;
        Assert::IsTrue(formulaA->Equals(&tempVar));
    }
    
    
    void ChemicalFormulaTestFixture::ConstructorBlankStringEqualsEmptyFormula() {
        ChemicalFormula *formulaA = new ChemicalFormula();

        ChemicalFormula tempVar;
        Assert::IsTrue(formulaA->Equals(&tempVar));

        delete formulaA;
    }

#ifdef LATER
    void ChemicalFormulaTestFixture::ConstructorDefaultEqualsEmptyFormula() {
        ChemicalFormula *formulaA = new ChemicalFormula();

        ChemicalFormula tempVar();
        Assert::AreEqual(formulaA, &tempVar);

        delete formulaA;
    }
#endif
    
    void ChemicalFormulaTestFixture::CopyConstructorValueEquality() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = new ChemicalFormula(formulaA);

        Assert::IsTrue(formulaA->Equals(formulaB));

        delete formulaB;
    }

    void ChemicalFormulaTestFixture::CopyConstructorReferenceInequality() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = new ChemicalFormula(formulaA);

        Assert::IsFalse(formulaA->Equals(formulaB));

        delete formulaB;
    }

    void ChemicalFormulaTestFixture::EmptyMonoisotopicMassIsZero() {
        ChemicalFormula tempVar;
        Assert::AreEqual(0.0, (&tempVar)->getMonoisotopicMass());
    }

    void ChemicalFormulaTestFixture::EmptyAverageMassIsZero() {
        ChemicalFormula tempVar;
        Assert::AreEqual(0.0, (&tempVar)->getAverageMass());
    }

    void ChemicalFormulaTestFixture::EmptyStringIsBlank() {
        ChemicalFormula tempVar;
        std::string s;
        Assert::AreEqual((&tempVar)->getFormula(), s);
    }

    void ChemicalFormulaTestFixture::EmptyAtomCountIsZero() {
        ChemicalFormula tempVar;
        Assert::AreEqual(0, (&tempVar)->getAtomCount());
    }

    void ChemicalFormulaTestFixture::EmptyElementCountIsZero() {
        ChemicalFormula tempVar;
        Assert::AreEqual(0, (&tempVar)->getNumberOfUniqueElementsByAtomicNumber());
    }

    void ChemicalFormulaTestFixture::EmptyIsotopeCountIsZero() {
        ChemicalFormula tempVar;
        Assert::AreEqual(0, (&tempVar)->getNumberOfUniqueIsotopes());
    }

    void ChemicalFormulaTestFixture::FormulaValueInequality() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("NC1OH3");

        Assert::IsFalse(formulaA->Equals(formulaB));
    }

    void ChemicalFormulaTestFixture::FormulaValueInequalityHeavyIsotope() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("CC{13}H3NO");

        Assert::IsFalse(formulaA->Equals(formulaB));
    }

    void ChemicalFormulaTestFixture::FormulaValueEqualityItself() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");

        Assert::IsTrue(formulaA->Equals(formulaA));
    }

    void ChemicalFormulaTestFixture::FormulaValueEquality() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("NC2OH3");

        Assert::IsTrue(formulaA->Equals(formulaB));
    }

    void ChemicalFormulaTestFixture::FormulaEquality() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        Assert::IsTrue(formulaA->Equals(formulaA));
    }

    void ChemicalFormulaTestFixture::FormulaAlmostEquality() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C{12}2H3NO");
        Assert::IsFalse(formulaA->Equals(formulaB));
    }

    void ChemicalFormulaTestFixture::HashCodeEquality() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("H3C2NO");

        Assert::AreEqual(formulaA->GetHashCode(), formulaB->GetHashCode());
    }

    void ChemicalFormulaTestFixture::HashCodeImmutableEquality() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        Assert::AreEqual(formulaA->GetHashCode(), formulaA->GetHashCode());
    }

    void ChemicalFormulaTestFixture::HashCodeCheck() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("Al");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("Al{27}");
        Assert::AreNotEqual(formulaA->GetHashCode(), formulaB->GetHashCode());
    }

    void ChemicalFormulaTestFixture::HillNotation() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("H3NC2O");
        std::string s="C2H3NO";
        Assert::AreEqual( s, formulaA->getFormula());
    }

    void ChemicalFormulaTestFixture::HillNotationNoCarbon() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("BrH");
        std::string s="HBr";
        
        Assert::AreEqual(s, formulaA->getFormula());
    }

    void ChemicalFormulaTestFixture::HillNotationNoCarbonNoHydrogen() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("Ca5O14Br6");
        std::string s="Br6Ca5O14";
        Assert::AreEqual( s, formulaA->getFormula());
    }

    void ChemicalFormulaTestFixture::HillNotationNoHydrogen() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("NC2O");
        std::string s="C2NO";
        Assert::AreEqual(s, formulaA->getFormula());
    }

    void ChemicalFormulaTestFixture::HillNotationWithHeavyIsotope() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("H3NC2C{13}2O");
        std::string s="C2C{13}2H3NO";
        Assert::AreEqual(s, formulaA->getFormula());
    }

    void ChemicalFormulaTestFixture::HillNotationWithNegativeCount() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("H3NC-2O");
//        std::string s="C-2H3NO";
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C-2H3NO");
        
        Assert::AreEqual(formulaA->getFormula(), formulaB->getFormula());
    }

    void ChemicalFormulaTestFixture::HillNotationWithHeavyIsotopeNegativeCount() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("H3NC2C{13}-2O");
//        std::string s="C2C{13}-2H3NO";
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2C{13}-2H3NO");
        Assert::AreEqual(formulaA->getFormula(), formulaB->getFormula());
    }

#ifdef LATER    
    void ChemicalFormulaTestFixture::BadFormula() {
        Assert::Throws<MzLibException*>([&] () {
            ChemicalFormula::ParseFormula("!@#$");
        }, "Input string for chemical formula was in an incorrect format");
    }

    void ChemicalFormulaTestFixture::InvalidChemicalElement() {
        Assert::Throws<KeyNotFoundException*>([&] () {
            PeriodicTable::GetElement("Faa");
        });
    }
#endif
    
    void ChemicalFormulaTestFixture::InvalidElementIsotope() {
        Assert::IsNull(PeriodicTable::GetElement("C")->getIsotopeByMassNumber(100));
    }

    void ChemicalFormulaTestFixture::NumberOfAtoms() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");

        Assert::AreEqual(7, formulaA->getAtomCount());
    }

    void ChemicalFormulaTestFixture::NumberOfAtomsOfEmptyFormula() {
        ChemicalFormula tempVar;
        Assert::AreEqual(0, (&tempVar)->getAtomCount());
    }

    void ChemicalFormulaTestFixture::NumberOfAtomsOfNegativeFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C-2H-3N-1O-1");

        Assert::AreEqual(-7, formulaA->getAtomCount());
    }

    void ChemicalFormulaTestFixture::ParsingFormulaNoNumbers() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("CCHHHNO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H3NO");

        Assert::IsTrue(formulaA->Equals(formulaB));
    }

    void ChemicalFormulaTestFixture::ParsingFormulaWithInternalSpaces() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2 H3 N O");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H3NO");

        Assert::IsTrue(formulaA->Equals(formulaB));
    }

    void ChemicalFormulaTestFixture::ParsingFormulaWithSpacesAtEnd() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO  ");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H3NO");

        Assert::IsTrue(formulaA->Equals(formulaB));
    }

    void ChemicalFormulaTestFixture::ParsingFormulaWithSpacesAtBeginning() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("    C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H3NO");

        Assert::IsTrue(formulaA->Equals(formulaB));
    }

    void ChemicalFormulaTestFixture::ParsingFormulaWithSpaces() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("  C2 H3 N O  ");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H3NO");

        Assert::IsTrue(formulaA->Equals(formulaB));
    }

    void ChemicalFormulaTestFixture::ParsingFormulaNoNumbersRandomOrder() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("OCHHCHN");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H3NO");

        Assert::IsTrue(formulaA->Equals(formulaB));
    }

    void ChemicalFormulaTestFixture::EqualsFalse() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("OCHHCHN");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C");
        Assert::IsFalse(formulaA->Equals(formulaB));
    }

    void ChemicalFormulaTestFixture::Equals() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("OCHHCHN");
        Assert::AreEqual(formulaA, formulaA);
    }

    void ChemicalFormulaTestFixture::ParsingFormulaRepeatedElements() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("CH3NOC");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H3NO");

        Assert::IsTrue(formulaA->Equals(formulaB));
    }

    void ChemicalFormulaTestFixture::IsSuperSetOf() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("CH3NO{17}C");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("CHNO{16}");

        Assert::IsFalse(formulaA->IsSupersetOf(formulaB));
    }

    void ChemicalFormulaTestFixture::ParsingFormulaRepeatedElementsCancelEachOther() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NOC-2");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("H3NO");

    	//False but should be true.  Check ChemicalFormula::ParseFormula on line 159 of Chemistry/ChemiaclFormula.cpp
    	std::cout << "formula A " << formulaA->getFormula() << ", formula B " << formulaB->getFormula() << std::endl;
        Assert::IsTrue(formulaA->Equals(formulaB));
    }

    void ChemicalFormulaTestFixture::RemoveElementCompletelyFromFromula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2NO");

        formulaA->RemoveIsotopesOf(PeriodicTable::GetElement("H"));

        Assert::IsTrue(formulaA->Equals(formulaB));
    }

    void ChemicalFormulaTestFixture::RemoveElementCompletelyFromFromulaBySymbol() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2NO");

        formulaA->RemoveIsotopesOf(PeriodicTable::GetElement("H"));

        Assert::IsTrue(formulaA->Equals(formulaB));
    }

    void ChemicalFormulaTestFixture::RemoveElementCompletelyFromFromulaWithHeavyIsotope() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2C{13}H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("H3NO");

        formulaA->RemoveIsotopesOf(PeriodicTable::GetElement("C"));

        Assert::IsTrue(formulaA->Equals(formulaB));
        Assert::AreEqual(formulaA->getMonoisotopicMass(), formulaB->getMonoisotopicMass());
    }

    void ChemicalFormulaTestFixture::RemoveEmptyFormulaFromFromula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H3NO");

        // ChemicalFormula tempVar();
        ChemicalFormula *tempVar = ChemicalFormula::ParseFormula("C");
        tempVar->Clear();
        formulaA->Remove(tempVar);

        Assert::IsTrue(formulaA->Equals(formulaB));
    }

    void ChemicalFormulaTestFixture::RemoveFormulaFromFromula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H5NOO{16}");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("H2O{16}");
        ChemicalFormula *formulaC = ChemicalFormula::ParseFormula("C2H3NO");

        formulaA->Remove(formulaB);

        Assert::IsTrue(formulaA->Equals(formulaC));
    }

//Need CountWithIsotopes to be working correctly
#ifdef LATER
    void ChemicalFormulaTestFixture::ContainsSpecificIsotope() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H5NOO{16}");

        // Assert::IsTrue(formulaA->ContainsSpecificIsotope(PeriodicTable::GetElement("O")[16]));
        Assert::IsTrue(formulaA->ContainsSpecificIsotope(PeriodicTable::GetElement("O"), 16));
    }

    void ChemicalFormulaTestFixture::ContainsIsotopesOf() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("O{16}");
        Assert::IsTrue(formulaA->ContainsIsotopesOf(PeriodicTable::GetElement("O")));
        Assert::IsTrue(formulaA->ContainsSpecificIsotope(PeriodicTable::GetElement("O"), 16));
        Assert::AreEqual(1, formulaA->CountSpecificIsotopes(PeriodicTable::GetElement("O"), 16));
    }

    void ChemicalFormulaTestFixture::HydrogenCarbonRatio() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C8H4");
        Assert::AreEqual(0.5, formulaA->getHydrogenCarbonRatio());
    }
#endif

    void ChemicalFormulaTestFixture::RemoveIsotopeCompletelyFromFromula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2NO");

        formulaA->RemoveIsotopesOf(PeriodicTable::GetElement("H"));

        Assert::IsTrue(formulaA->Equals(formulaB));
    }

    void ChemicalFormulaTestFixture::RemoveElementFromFromula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2HNO");

        formulaA->Remove(PeriodicTable::GetElement("H"), 2);

        Assert::IsTrue(formulaA->Equals(formulaB));
    }

    void ChemicalFormulaTestFixture::RemoveIsotopeFromFromulaEquality() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H3O");

        formulaA->Remove(PeriodicTable::GetElement("N"), 1);

        Assert::IsTrue(formulaA->Equals(formulaB));
    }

    void ChemicalFormulaTestFixture::RemoveNegativeElementFromFromula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H5NO");

        formulaA->Remove(PeriodicTable::GetElement("H"), -2);

        Assert::IsTrue(formulaA->Equals(formulaB));
    }

    void ChemicalFormulaTestFixture::RemoveNonExistantIsotopeFromFromula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H5NO2");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("Fe");
        ChemicalFormula *formulaC = ChemicalFormula::ParseFormula("C2H5Fe-1NO2");

        formulaA->Remove(formulaB);

        //False but should be true.  Check ChemicalFormula::ParseFormula on line 159 of Chemistry/ChemiaclFormula.cpp
        std::cout << "formula A " << formulaA->getFormula() << ", formula C " << formulaC->getFormula() << std::endl;
        Assert::IsTrue(formulaA->Equals(formulaC));
    }

#ifdef LATER
    void ChemicalFormulaTestFixture::RemoveZeroIsotopeFromFromula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C2H3NO");

        formulaA->Remove(PeriodicTable::GetElement("H")[1], 0);

        Assert::AreEqual(formulaA, formulaB);
    }
#endif

    void ChemicalFormulaTestFixture::TotalProtons() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C{13}2H3NO");

        Assert::AreEqual(30, formulaA->getProtonCount());
    }

    void ChemicalFormulaTestFixture::TotalProtons2() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C{12}2H3NO");

        Assert::AreEqual(30, formulaA->getProtonCount());
    }

    void ChemicalFormulaTestFixture::AverageMass() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C");

        Assert::AreEqual(PeriodicTable::GetElement("C")->getAverageMass(), formulaA->getAverageMass());
    }

    void ChemicalFormulaTestFixture::UniqueElements() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");

        Assert::AreEqual(4, formulaA->getNumberOfUniqueElementsByAtomicNumber());
    }

    void ChemicalFormulaTestFixture::UniqueElementsOfEmptyFormula() {
        // ChemicalFormula tempVar();
        ChemicalFormula *tempVar = ChemicalFormula::ParseFormula("C");
        tempVar->Clear();

        Assert::AreEqual(0, tempVar->getNumberOfUniqueElementsByAtomicNumber());
    }

    void ChemicalFormulaTestFixture::UniqueElementsWithHeavyIsotope() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("CC{13}H3NO");

        Assert::AreEqual(4, formulaA->getNumberOfUniqueElementsByAtomicNumber());
    }

    void ChemicalFormulaTestFixture::UniqueIsotopes() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");

        Assert::AreEqual(0, formulaA->getNumberOfUniqueIsotopes());
    }

    void ChemicalFormulaTestFixture::UniqueIsotopesOfEmptyFormula() {
        // ChemicalFormula tempVar();
        ChemicalFormula *tempVar = ChemicalFormula::ParseFormula("C");
        tempVar->Clear();

        Assert::AreEqual(0, tempVar->getNumberOfUniqueIsotopes());
    }

    void ChemicalFormulaTestFixture::UniqueIsotopesWithHeavyIsotope() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("CC{13}H3NO");

        Assert::AreEqual(1, formulaA->getNumberOfUniqueIsotopes());
    }

    void ChemicalFormulaTestFixture::ContainsIsotopesOfYe() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("CC{13}H3NO");

        Assert::IsTrue(formulaA->ContainsIsotopesOf(PeriodicTable::GetElement("C")));
    }

#ifdef LATER
    void ChemicalFormulaTestFixture::TestReplaceIsotopes() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("CC{13}2H3NO");

        formulaA->Replace(PeriodicTable::GetElement("C")[13], PeriodicTable::GetElement("C")[12]);
        Assert::AreEqual("CC{12}2H3NO", formulaA->getFormula());
    }
#endif

    void ChemicalFormulaTestFixture::ChemicalForulaIsSubSet() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C3H3NO");

        Assert::IsTrue(formulaA->IsSubsetOf(formulaB));
    }

    void ChemicalFormulaTestFixture::ChemicalForulaIsNotSubSet() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C3H2NO");

        Assert::IsFalse(formulaA->IsSubsetOf(formulaB));
    }

    void ChemicalFormulaTestFixture::ChemicalForulaIsSuperSet() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C3H3NO");

        Assert::IsTrue(formulaB->IsSupersetOf(formulaA));
    }

    void ChemicalFormulaTestFixture::ChemicalForulaIsNotSuperSet() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO2");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C3H3NO");

        Assert::IsFalse(formulaB->IsSupersetOf(formulaA));
    }

    void ChemicalFormulaTestFixture::ChemicalForulaMyTest() {
        ChemicalFormula *formula = new ChemicalFormula();
        formula->Add(ChemicalFormula::ParseFormula("C3H5NO"));
        Assert::AreEqual(PeriodicTable::GetElement("C")->getPrincipalIsotope()->getAtomicMass() * 3 + PeriodicTable::GetElement("H")->getPrincipalIsotope()->getAtomicMass() * 5 + PeriodicTable::GetElement("N")->getPrincipalIsotope()->getAtomicMass() + PeriodicTable::GetElement("O")->getPrincipalIsotope()->getAtomicMass(), formula->getMonoisotopicMass());

        delete formula;
    }

#ifdef LATER
    void ChemicalFormulaTestFixture::TestIsotopicDistribution() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C2H3NO");

        auto a = IsotopicDistribution::GetDistribution(formulaA);

        Assert::IsTrue(std::abs(formulaA->getMonoisotopicMass() - a->getMasses().ToArray()[Array::IndexOf(a->getIntensities().ToArray(), a->getIntensities().Max())]) < 1e-9);
    }

    void ChemicalFormulaTestFixture::TestIsotopicDistribution2() {
        IsotopicDistribution::GetDistribution(ChemicalFormula::ParseFormula("AlO{16}"));
    }

    void ChemicalFormulaTestFixture::TestIsotopicDistribution3() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("CO");

        // Distinguish between O and C isotope masses
        auto a = IsotopicDistribution::GetDistribution(formulaA, 0.0001);
        // Assert::AreEqual(6, a->getMasses().size()());

        std::vector<double> a_values = a->getMasses();
        int a_count = a_values.size();

        Assert::AreEqual(6, a_count);

        // Do not distinguish between O and C isotope masses
        IsotopicDistribution::GetDistribution(formulaA, 0.001);

        // Do not distinguish between O and C isotope masses
        auto b = IsotopicDistribution::GetDistribution(formulaA);

        std::vector<double> b_values = b->getMasses();
        int b_count = b_values.size();

        // Assert::AreEqual(4, b->getMasses().size()());
        Assert::AreEqual(4, b_count);

        IsotopicDistribution::GetDistribution(formulaA, 0.1);

        PhysicalObjectWithChemicalFormula *formulaB = new PhysicalObjectWithChemicalFormula("CO");
        IsotopicDistribution::GetDistribution(formulaB->getThisChemicalFormula(), 1);

        delete formulaB;
    }

    void ChemicalFormulaTestFixture::CatchIsotopicDistributionStuff() {
        ChemicalFormula *formula = (ChemicalFormula::ParseFormula("C500O50H250N50"));
        IsotopicDistribution::GetDistribution(formula, 0.001, 1e-1, 1e-15);
    }

    void ChemicalFormulaTestFixture::CatchProbStuff() {
        ChemicalFormula *formula = (ChemicalFormula::ParseFormula("C50O50"));
        IsotopicDistribution::GetDistribution(formula, 0.001, 1e-50, 1e-15);
    }

    void ChemicalFormulaTestFixture::I0j1() {
        ChemicalFormula *formula = (ChemicalFormula::ParseFormula("C50O50"));
        IsotopicDistribution::GetDistribution(formula, 0.01, 0.1);

        IsotopicDistribution::GetDistribution(formula, 0.01, 0.5);

        IsotopicDistribution::GetDistribution(formula, 0.01, 0.75);
    }

    void ChemicalFormulaTestFixture::ThresholdProbability() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("CO");

        // Only the principal isotopes have joint probability of 0.5! So one result when calcuating isotopic distribution
        auto a = IsotopicDistribution::GetDistribution(formulaA, 0.0001, 0.5);
        std::vector<double> a_values = a->getMasses();
        int a_count = a_values.size();

        // Assert::AreEqual(1, a->getMasses().size());
        //False 0 != 1
        Assert::AreEqual(1, a_count);

        //casues seg-fault.  Is it because of front()?
        // Assert::IsTrue(std::abs((PeriodicTable::GetElement("C")->getPrincipalIsotope()->getAtomicMass() + PeriodicTable::GetElement("O")->getPrincipalIsotope()->getAtomicMass() - a->getMasses().front())) < 1e-9);
    }
#endif

    void ChemicalFormulaTestFixture::TestAnotherFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("H{1}CC{13}2H3NO{16}");
        // Assert::AreEqual("CC{13}2H3H{1}NO{16}", formulaA->getFormula());

        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("CC{13}2H3H{1}NO{16}");
        Assert::AreEqual(formulaB->getFormula(), formulaA->getFormula());
    }

    void ChemicalFormulaTestFixture::NeutronCount() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C{12}O{16}");
        Assert::AreEqual(14, formulaA->NeutronCount());
    }

#ifdef LATER
    void ChemicalFormulaTestFixture::NeutronCountFail() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("CO");
        Assert::Throws<MzLibException*>([&] () {
            formulaA->NeutronCount();
        }, "Cannot know for sure what the number of neutrons is!");
    }
#endif

    void ChemicalFormulaTestFixture::CombineTest() {
        std::vector<IHasChemicalFormula*> theList = {
            new PhysicalObjectWithChemicalFormula("C2H3NO"),
            new PhysicalObjectWithChemicalFormula("CO")
        };
        auto c = ChemicalFormula::Combine(theList);

        // Assert::AreEqual("C3H3NO2", c->getFormula());
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C3H3NO2");

        Assert::AreEqual(formulaA->getFormula(), c->getFormula());
    }

    void ChemicalFormulaTestFixture::ValidatePeriodicTable() {
        Assert::IsTrue(PeriodicTable::ValidateAverageMasses(1e-2));
        Assert::IsFalse(PeriodicTable::ValidateAverageMasses(1e-3));
        Assert::IsTrue(PeriodicTable::ValidateAbundances(1e-15));
        Assert::IsFalse(PeriodicTable::ValidateAbundances(0));
    }

    void ChemicalFormulaTestFixture::TestAddChemicalFormula() {
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C");
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("C{12}");
        formulaB->Add(formulaA);

        ChemicalFormula *formulaC = ChemicalFormula::ParseFormula("CC{12}");
        // Assert::AreEqual("CC{12}", formulaB->getFormula());
        Assert::AreEqual(formulaC->getFormula(), formulaB->getFormula());
    }

    void ChemicalFormulaTestFixture::NotEqual() {
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("C15O15H15S15N15");
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula("N15S15H15O15C15");
        // Assert::AreEqual(formulaA, formulaB);
        Assert::IsTrue(formulaA->Equals(formulaB));

        //-1e-9 fails but 1e-19 does not?
        Assert::IsTrue(std::abs(formulaA->getMonoisotopicMass() - formulaB->getMonoisotopicMass()) < 1e-9);
    }

    void ChemicalFormulaTestFixture::TestRemoveObjectFromChemicalFormula() {
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("CO");
        auto ok = new PhysicalObjectWithChemicalFormula("C");
        formulaB->Remove(ok);

        // Assert::AreEqual("O", formulaB->getFormula());
        Assert::AreEqual(ChemicalFormula::ParseFormula("O")->getFormula(), formulaB->getFormula());

//C# TO C++ CONVERTER TODO TASK: A 'delete ok' statement was not added since ok was passed to a method or constructor. Handle memory management manually.
    }

    void ChemicalFormulaTestFixture::TestEquality() {
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("CO");
        // Assert::AreEqual(formulaB, formulaB);
        Assert::IsTrue(formulaB->Equals(formulaB));
    }

    void ChemicalFormulaTestFixture::TestToChemicalFormula() {
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula("CO");
        // Assert::AreEqual(ChemicalFormula::ParseFormula("CO"), formulaB);
        Assert::IsTrue(formulaB->Equals(ChemicalFormula::ParseFormula("CO")));
    }

#ifdef LATER
    void ChemicalFormulaTestFixture::IsoTest() {
        ChemicalFormula *formula = ChemicalFormula::ParseFormula("C5H8NO");

        IsotopicDistribution *d = IsotopicDistribution::GetDistribution(formula, std::pow(2, -14));
        std::vector<double> d_values = d->getIntensities();
        int d_count = d_values.size();

        // Assert::AreEqual(324, d->getIntensities().size()());
        Assert::AreEqual(324, d_count);

        d = IsotopicDistribution::GetDistribution(formula, std::pow(2, -1));
        std::vector<double> d_values2 = d->getIntensities();
        int d_count2 = d_values.size();

        // Assert::AreEqual(17, d->getIntensities().size()());
        Assert::AreEqual(17, d_count2);
    }
#endif
    
    PhysicalObjectWithChemicalFormula::PhysicalObjectWithChemicalFormula(const std::string &v) {
        setThisChemicalFormula(ChemicalFormula::ParseFormula(v));
    }

    double PhysicalObjectWithChemicalFormula::getMonoisotopicMass() const {
        return getThisChemicalFormula()->getMonoisotopicMass();
    }

    ChemicalFormula * PhysicalObjectWithChemicalFormula::getThisChemicalFormula() const {
        return privateThisChemicalFormula;
    }

    void PhysicalObjectWithChemicalFormula::setThisChemicalFormula(ChemicalFormula *value) {
        privateThisChemicalFormula = value;
    }


}
