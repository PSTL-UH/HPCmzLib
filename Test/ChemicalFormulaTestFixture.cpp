#include "ChemicalFormulaTestFixture.h"
#include "../Chemistry/Element.h"
#include "../Chemistry/PeriodicTable.h"
#include "../MzLibUtil/MzLibException.h"
#include "../Chemistry/ChemicalFormula.h"
#include "../Chemistry/Isotope.h"
#include "../Chemistry/IsotopicDistribution.h"

using namespace Chemistry;
using namespace MzLibUtil;
using namespace NUnit::Framework;

namespace Test {

    void ChemicalFormulaTestFixture::AddIsotopeWithExistingMassNumber() {
        Element *al = PeriodicTable::GetElement(L"Al");
        Assert::Throws<MzLibException*>([&] () {
            al->AddIsotope(27, 28, 1);
        }, L"Isotope with mass number " + std::to_wstring(28) + L" already exists");
    }

    void ChemicalFormulaTestFixture::AddElementToFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"C2H3N2O");

        Element *n = PeriodicTable::GetElement(7);

        formulaA->Add(n, 1);

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::Multiply() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");
        formulaA->Multiply(2);
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"C4H6N2O2");

        Assert::AreEqual(formulaA, formulaB);

        Assert::IsFalse(formulaA->Equals(nullptr));
    }

    void ChemicalFormulaTestFixture::CheckToStringOfElements() {
        Element *n = PeriodicTable::GetElement(L"N");
        Assert::AreEqual(L"" + n, L"N");
    }

    void ChemicalFormulaTestFixture::AddFormulaToFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"H2O");
        ChemicalFormula *formulaC = ChemicalFormula::ParseFormula(L"C2H5NO2");

        formulaA->Add(formulaB);

        Assert::AreEqual(formulaA, formulaC);
    }

    void ChemicalFormulaTestFixture::AddFormulaToItself() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"C4H6N2O2");

        ChemicalFormula tempVar(formulaA);
        formulaA->Add(&tempVar);

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::AddIChemicalFormulaToFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");
        IHasChemicalFormula *formulaB = new PhysicalObjectWithChemicalFormula(L"H2O");
        ChemicalFormula *formulaC = ChemicalFormula::ParseFormula(L"C2H5NO2");

        formulaA->Add(formulaB);

        Assert::AreEqual(formulaA, formulaC);

//C# TO C++ CONVERTER TODO TASK: A 'delete formulaB' statement was not added since formulaB was passed to a method or constructor. Handle memory management manually.
    }

    void ChemicalFormulaTestFixture::AddIsotopeToFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"C2H3H{1}NO");

        Isotope *h1 = PeriodicTable::GetElement(L"H")[1];

        formulaA->Add(h1, 1);

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::AddLargeElementToFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"C2H3NOFe");

        Element *fe = PeriodicTable::GetElement(L"Fe");

        formulaA->Add(fe, 1);

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::AddNegativeFormulaToFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"C-1H-2");
        ChemicalFormula *formulaC = ChemicalFormula::ParseFormula(L"CHNO");

        formulaA->Add(formulaB);

        Assert::AreEqual(formulaA, formulaC);
    }

    void ChemicalFormulaTestFixture::AddNegativeIsotopeToFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2HH{1}2NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"C2HNO");

        Isotope *h1 = PeriodicTable::GetElement(L"H")[1];

        formulaA->Add(h1, -2);

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::AddELementByAtomicNumber() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H2NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"C2HNO");

        formulaB->Add(1, 1);

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::AddNonExistentSymbolToFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");

        Assert::Throws<KeyNotFoundException*>([&] () {
            formulaA->AddPrincipalIsotopesOf(L"Faa", 1);
        });
    }

    void ChemicalFormulaTestFixture::InexistingElement() {
        Assert::Throws<KeyNotFoundException*>([&] () {
            ChemicalFormula::ParseFormula(L"Q");
        });
    }

    void ChemicalFormulaTestFixture::AddZeroElementToFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"C2H3NO");

        Element *n = PeriodicTable::GetElement(L"N");

        formulaA->Add(n, 0);

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::AddZeroIsotopeToFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"C2H3NO");

        Isotope *h1 = PeriodicTable::GetElement(L"H")[1];

        formulaA->Add(h1, 0);

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::AddZeroSymbolToFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"C2H3NO");

        formulaA->AddPrincipalIsotopesOf(L"H", 0);

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::ClearFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");
        formulaA->Clear();
        ChemicalFormula tempVar();
        Assert::AreEqual(formulaA, &tempVar);
    }

    void ChemicalFormulaTestFixture::ConstructorBlankStringEqualsEmptyFormula() {
        ChemicalFormula *formulaA = new ChemicalFormula();

        ChemicalFormula tempVar();
        Assert::AreEqual(formulaA, &tempVar);

//C# TO C++ CONVERTER TODO TASK: A 'delete formulaA' statement was not added since formulaA was passed to a method or constructor. Handle memory management manually.
    }

    void ChemicalFormulaTestFixture::ConstructorDefaultEqualsEmptyFormula() {
        ChemicalFormula *formulaA = new ChemicalFormula();

        ChemicalFormula tempVar();
        Assert::AreEqual(formulaA, &tempVar);

//C# TO C++ CONVERTER TODO TASK: A 'delete formulaA' statement was not added since formulaA was passed to a method or constructor. Handle memory management manually.
    }

    void ChemicalFormulaTestFixture::CopyConstructorValueEquality() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");
        ChemicalFormula *formulaB = new ChemicalFormula(formulaA);

        Assert::AreEqual(formulaA, formulaB);

//C# TO C++ CONVERTER TODO TASK: A 'delete formulaB' statement was not added since formulaB was passed to a method or constructor. Handle memory management manually.
    }

    void ChemicalFormulaTestFixture::CopyConstructorReferenceInequality() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");
        ChemicalFormula *formulaB = new ChemicalFormula(formulaA);

        Assert::AreNotSame(formulaA, formulaB);

//C# TO C++ CONVERTER TODO TASK: A 'delete formulaB' statement was not added since formulaB was passed to a method or constructor. Handle memory management manually.
    }

    void ChemicalFormulaTestFixture::EmptyMonoisotopicMassIsZero() {
        ChemicalFormula tempVar();
        Assert::AreEqual(0.0, (&tempVar)->getMonoisotopicMass());
    }

    void ChemicalFormulaTestFixture::EmptyAverageMassIsZero() {
        ChemicalFormula tempVar();
        Assert::AreEqual(0.0, (&tempVar)->getAverageMass());
    }

    void ChemicalFormulaTestFixture::EmptyStringIsBlank() {
        ChemicalFormula tempVar();
        Assert::IsEmpty((&tempVar)->getFormula());
    }

    void ChemicalFormulaTestFixture::EmptyAtomCountIsZero() {
        ChemicalFormula tempVar();
        Assert::AreEqual(0, (&tempVar)->getAtomCount());
    }

    void ChemicalFormulaTestFixture::EmptyElementCountIsZero() {
        ChemicalFormula tempVar();
        Assert::AreEqual(0, (&tempVar)->getNumberOfUniqueElementsByAtomicNumber());
    }

    void ChemicalFormulaTestFixture::EmptyIsotopeCountIsZero() {
        ChemicalFormula tempVar();
        Assert::AreEqual(0, (&tempVar)->getNumberOfUniqueIsotopes());
    }

    void ChemicalFormulaTestFixture::FormulaValueInequality() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"NC1OH3");

        Assert::AreNotEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::FormulaValueInequalityHeavyIsotope() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"CC{13}H3NO");

        Assert::AreNotEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::FormulaValueEqualityItself() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");

        Assert::AreEqual(formulaA, formulaA);
    }

    void ChemicalFormulaTestFixture::FormulaValueEquality() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"NC2OH3");

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::FormulaEquality() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");
        Assert::AreEqual(formulaA, formulaA);
    }

    void ChemicalFormulaTestFixture::FormulaAlmostEquality() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"C{12}2H3NO");
        Assert::AreNotEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::HashCodeEquality() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"H3C2NO");

        Assert::AreEqual(formulaA->GetHashCode(), formulaB->GetHashCode());
    }

    void ChemicalFormulaTestFixture::HashCodeImmutableEquality() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");
        Assert::AreEqual(formulaA->GetHashCode(), formulaA->GetHashCode());
    }

    void ChemicalFormulaTestFixture::HashCodeCheck() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"Al");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"Al{27}");
        Assert::AreNotEqual(formulaA->GetHashCode(), formulaB->GetHashCode());
    }

    void ChemicalFormulaTestFixture::HillNotation() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"H3NC2O");

        Assert::AreEqual(L"C2H3NO", formulaA->getFormula());
    }

    void ChemicalFormulaTestFixture::HillNotationNoCarbon() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"BrH");

        Assert::AreEqual(L"HBr", formulaA->getFormula());
    }

    void ChemicalFormulaTestFixture::HillNotationNoCarbonNoHydrogen() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"Ca5O14Br6");

        Assert::AreEqual(L"Br6Ca5O14", formulaA->getFormula());
    }

    void ChemicalFormulaTestFixture::HillNotationNoHydrogen() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"NC2O");

        Assert::AreEqual(L"C2NO", formulaA->getFormula());
    }

    void ChemicalFormulaTestFixture::HillNotationWithHeavyIsotope() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"H3NC2C{13}2O");

        Assert::AreEqual(L"C2C{13}2H3NO", formulaA->getFormula());
    }

    void ChemicalFormulaTestFixture::HillNotationWithNegativeCount() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"H3NC-2O");

        Assert::AreEqual(L"C-2H3NO", formulaA->getFormula());
    }

    void ChemicalFormulaTestFixture::HillNotationWithHeavyIsotopeNegativeCount() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"H3NC2C{13}-2O");

        Assert::AreEqual(L"C2C{13}-2H3NO", formulaA->getFormula());
    }

    void ChemicalFormulaTestFixture::BadFormula() {
        Assert::Throws<MzLibException*>([&] () {
            ChemicalFormula::ParseFormula(L"!@#$");
        }, L"Input string for chemical formula was in an incorrect format");
    }

    void ChemicalFormulaTestFixture::InvalidChemicalElement() {
        Assert::Throws<KeyNotFoundException*>([&] () {
            PeriodicTable::GetElement(L"Faa");
        });
    }

    void ChemicalFormulaTestFixture::InvalidElementIsotope() {
        Assert::IsNull(PeriodicTable::GetElement(L"C")[100]);
    }

    void ChemicalFormulaTestFixture::NumberOfAtoms() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");

        Assert::AreEqual(7, formulaA->getAtomCount());
    }

    void ChemicalFormulaTestFixture::NumberOfAtomsOfEmptyFormula() {
        ChemicalFormula tempVar();
        Assert::AreEqual(0, (&tempVar)->getAtomCount());
    }

    void ChemicalFormulaTestFixture::NumberOfAtomsOfNegativeFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C-2H-3N-1O-1");

        Assert::AreEqual(-7, formulaA->getAtomCount());
    }

    void ChemicalFormulaTestFixture::ParsingFormulaNoNumbers() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"CCHHHNO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"C2H3NO");

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::ParsingFormulaWithInternalSpaces() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2 H3 N O");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"C2H3NO");

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::ParsingFormulaWithSpacesAtEnd() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO  ");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"C2H3NO");

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::ParsingFormulaWithSpacesAtBeginning() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"    C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"C2H3NO");

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::ParsingFormulaWithSpaces() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"  C2 H3 N O  ");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"C2H3NO");

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::ParsingFormulaNoNumbersRandomOrder() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"OCHHCHN");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"C2H3NO");

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::EqualsFalse() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"OCHHCHN");
        Assert::IsFalse(formulaA->Equals(L"C"));
    }

    void ChemicalFormulaTestFixture::Equals() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"OCHHCHN");
        Assert::AreEqual(formulaA, formulaA);
    }

    void ChemicalFormulaTestFixture::ParsingFormulaRepeatedElements() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"CH3NOC");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"C2H3NO");

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::IsSuperSetOf() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"CH3NO{17}C");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"CHNO{16}");

        Assert::IsFalse(formulaA->IsSupersetOf(formulaB));
    }

    void ChemicalFormulaTestFixture::ParsingFormulaRepeatedElementsCancelEachOther() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NOC-2");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"H3NO");

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::RemoveElementCompletelyFromFromula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"C2NO");

        formulaA->RemoveIsotopesOf(PeriodicTable::GetElement(L"H"));

        Assert::AreEqual(formulaB, formulaA);
    }

    void ChemicalFormulaTestFixture::RemoveElementCompletelyFromFromulaBySymbol() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"C2NO");

        formulaA->RemoveIsotopesOf(L"H");

        Assert::AreEqual(formulaB, formulaA);
    }

    void ChemicalFormulaTestFixture::RemoveElementCompletelyFromFromulaWithHeavyIsotope() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2C{13}H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"H3NO");

        formulaA->RemoveIsotopesOf(L"C");

        Assert::AreEqual(formulaA, formulaB);
        Assert::AreEqual(formulaA->getMonoisotopicMass(), formulaB->getMonoisotopicMass());
    }

    void ChemicalFormulaTestFixture::RemoveEmptyFormulaFromFromula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"C2H3NO");

        ChemicalFormula tempVar();
        formulaA->Remove(&tempVar);

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::RemoveFormulaFromFromula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H5NOO{16}");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"H2O{16}");
        ChemicalFormula *formulaC = ChemicalFormula::ParseFormula(L"C2H3NO");

        formulaA->Remove(formulaB);

        Assert::AreEqual(formulaA, formulaC);
    }

    void ChemicalFormulaTestFixture::ContainsSpecificIsotope() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H5NOO{16}");

        Assert::IsTrue(formulaA->ContainsSpecificIsotope(PeriodicTable::GetElement(L"O")[16]));
    }

    void ChemicalFormulaTestFixture::ContainsIsotopesOf() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"O{16}");
        Assert::IsTrue(formulaA->ContainsIsotopesOf(L"O"));
        Assert::IsTrue(formulaA->ContainsSpecificIsotope(L"O", 16));
        Assert::AreEqual(1, formulaA->CountSpecificIsotopes(L"O", 16));
    }

    void ChemicalFormulaTestFixture::HydrogenCarbonRatio() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C8H4");
        Assert::AreEqual(0.5, formulaA->getHydrogenCarbonRatio());
    }

    void ChemicalFormulaTestFixture::RemoveIsotopeCompletelyFromFromula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"C2NO");

        formulaA->RemoveIsotopesOf(PeriodicTable::GetElement(L"H"));

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::RemoveElementFromFromula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"C2HNO");

        formulaA->Remove(PeriodicTable::GetElement(L"H"), 2);

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::RemoveIsotopeFromFromulaEquality() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"C2H3O");

        formulaA->Remove(L"N", 1);

        Assert::AreEqual(formulaB, formulaA);
    }

    void ChemicalFormulaTestFixture::RemoveNegativeElementFromFromula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"C2H5NO");

        formulaA->Remove(PeriodicTable::GetElement(L"H"), -2);

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::RemoveNonExistantIsotopeFromFromula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H5NO2");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"Fe");
        ChemicalFormula *formulaC = ChemicalFormula::ParseFormula(L"C2H5Fe-1NO2");

        formulaA->Remove(formulaB);

        Assert::AreEqual(formulaA, formulaC);
    }

    void ChemicalFormulaTestFixture::RemoveZeroIsotopeFromFromula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"C2H3NO");

        formulaA->Remove(PeriodicTable::GetElement(L"H")[1], 0);

        Assert::AreEqual(formulaA, formulaB);
    }

    void ChemicalFormulaTestFixture::TotalProtons() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C{13}2H3NO");

        Assert::AreEqual(30, formulaA->getProtonCount());
    }

    void ChemicalFormulaTestFixture::TotalProtons2() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C{12}2H3NO");

        Assert::AreEqual(30, formulaA->getProtonCount());
    }

    void ChemicalFormulaTestFixture::AverageMass() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C");

        Assert::AreEqual(PeriodicTable::GetElement(L"C")->getAverageMass(), formulaA->getAverageMass());
    }

    void ChemicalFormulaTestFixture::UniqueElements() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");

        Assert::AreEqual(4, formulaA->getNumberOfUniqueElementsByAtomicNumber());
    }

    void ChemicalFormulaTestFixture::UniqueElementsOfEmptyFormula() {
        ChemicalFormula tempVar();
        Assert::AreEqual(0, (&tempVar)->getNumberOfUniqueElementsByAtomicNumber());
    }

    void ChemicalFormulaTestFixture::UniqueElementsWithHeavyIsotope() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"CC{13}H3NO");

        Assert::AreEqual(4, formulaA->getNumberOfUniqueElementsByAtomicNumber());
    }

    void ChemicalFormulaTestFixture::UniqueIsotopes() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");

        Assert::AreEqual(0, formulaA->getNumberOfUniqueIsotopes());
    }

    void ChemicalFormulaTestFixture::UniqueIsotopesOfEmptyFormula() {
        ChemicalFormula tempVar();
        Assert::AreEqual(0, (&tempVar)->getNumberOfUniqueIsotopes());
    }

    void ChemicalFormulaTestFixture::UniqueIsotopesWithHeavyIsotope() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"CC{13}H3NO");

        Assert::AreEqual(1, formulaA->getNumberOfUniqueIsotopes());
    }

    void ChemicalFormulaTestFixture::ContainsIsotopesOfYe() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"CC{13}H3NO");

        Assert::IsTrue(formulaA->ContainsIsotopesOf(PeriodicTable::GetElement(L"C")));
    }

    void ChemicalFormulaTestFixture::TestReplaceIsotopes() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"CC{13}2H3NO");

        formulaA->Replace(PeriodicTable::GetElement(L"C")[13], PeriodicTable::GetElement(L"C")[12]);
        Assert::AreEqual(L"CC{12}2H3NO", formulaA->getFormula());
    }

    void ChemicalFormulaTestFixture::ChemicalForulaIsSubSet() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"C3H3NO");

        Assert::IsTrue(formulaA->IsSubsetOf(formulaB));
    }

    void ChemicalFormulaTestFixture::ChemicalForulaIsNotSubSet() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"C3H2NO");

        Assert::IsFalse(formulaA->IsSubsetOf(formulaB));
    }

    void ChemicalFormulaTestFixture::ChemicalForulaIsSuperSet() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"C3H3NO");

        Assert::IsTrue(formulaB->IsSupersetOf(formulaA));
    }

    void ChemicalFormulaTestFixture::ChemicalForulaIsNotSuperSet() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO2");
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"C3H3NO");

        Assert::IsFalse(formulaB->IsSupersetOf(formulaA));
    }

    void ChemicalFormulaTestFixture::ChemicalForulaMyTest() {
        ChemicalFormula *formula = new ChemicalFormula();
        formula->Add(ChemicalFormula::ParseFormula(L"C3H5NO"));
        Assert::AreEqual(PeriodicTable::GetElement(L"C")->getPrincipalIsotope()->getAtomicMass() * 3 + PeriodicTable::GetElement(L"H")->getPrincipalIsotope()->getAtomicMass() * 5 + PeriodicTable::GetElement(L"N")->getPrincipalIsotope()->getAtomicMass() + PeriodicTable::GetElement(L"O")->getPrincipalIsotope()->getAtomicMass(), formula->getMonoisotopicMass());

        delete formula;
    }

    void ChemicalFormulaTestFixture::TestIsotopicDistribution() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C2H3NO");

        auto a = IsotopicDistribution::GetDistribution(formulaA);

        Assert::True(std::abs(formulaA->getMonoisotopicMass() - a->getMasses().ToArray()[Array::IndexOf(a->getIntensities().ToArray(), a->getIntensities().Max())]) < 1e-9);
    }

    void ChemicalFormulaTestFixture::TestIsotopicDistribution2() {
        IsotopicDistribution::GetDistribution(ChemicalFormula::ParseFormula(L"AlO{16}"));
    }

    void ChemicalFormulaTestFixture::TestIsotopicDistribution3() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"CO");

        // Distinguish between O and C isotope masses
        auto a = IsotopicDistribution::GetDistribution(formulaA, 0.0001);
        Assert::AreEqual(6, a->getMasses().size()());

        // Do not distinguish between O and C isotope masses
        IsotopicDistribution::GetDistribution(formulaA, 0.001);

        // Do not distinguish between O and C isotope masses
        auto b = IsotopicDistribution::GetDistribution(formulaA);
        Assert::AreEqual(4, b->getMasses().size()());

        IsotopicDistribution::GetDistribution(formulaA, 0.1);

        PhysicalObjectWithChemicalFormula *formulaB = new PhysicalObjectWithChemicalFormula(L"CO");
        IsotopicDistribution::GetDistribution(formulaB->getThisChemicalFormula(), 1);

        delete formulaB;
    }

    void ChemicalFormulaTestFixture::CatchIsotopicDistributionStuff() {
        ChemicalFormula *formula = (ChemicalFormula::ParseFormula(L"C500O50H250N50"));
        IsotopicDistribution::GetDistribution(formula, 0.001, 1e-1, 1e-15);
    }

    void ChemicalFormulaTestFixture::CatchProbStuff() {
        ChemicalFormula *formula = (ChemicalFormula::ParseFormula(L"C50O50"));
        IsotopicDistribution::GetDistribution(formula, 0.001, 1e-50, 1e-15);
    }

    void ChemicalFormulaTestFixture::I0j1() {
        ChemicalFormula *formula = (ChemicalFormula::ParseFormula(L"C50O50"));
        IsotopicDistribution::GetDistribution(formula, 0.01, 0.1);

        IsotopicDistribution::GetDistribution(formula, 0.01, 0.5);

        IsotopicDistribution::GetDistribution(formula, 0.01, 0.75);
    }

    void ChemicalFormulaTestFixture::ThresholdProbability() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"CO");

        // Only the principal isotopes have joint probability of 0.5! So one result when calcuating isotopic distribution
        auto a = IsotopicDistribution::GetDistribution(formulaA, 0.0001, 0.5);
        Assert::AreEqual(1, a->getMasses().size()());
        Assert::IsTrue(std::abs((PeriodicTable::GetElement(L"C")->getPrincipalIsotope()->getAtomicMass() + PeriodicTable::GetElement(L"O")->getPrincipalIsotope()->getAtomicMass() - a->getMasses().front())) < 1e-9);
    }

    void ChemicalFormulaTestFixture::TestAnotherFormula() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"H{1}CC{13}2H3NO{16}");
        Assert::AreEqual(L"CC{13}2H3H{1}NO{16}", formulaA->getFormula());
    }

    void ChemicalFormulaTestFixture::NeutronCount() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C{12}O{16}");
        Assert::AreEqual(14, formulaA->NeutronCount());
    }

    void ChemicalFormulaTestFixture::NeutronCountFail() {
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"CO");
        Assert::Throws<MzLibException*>([&] () {
            formulaA->NeutronCount();
        }, L"Cannot know for sure what the number of neutrons is!");
    }

    void ChemicalFormulaTestFixture::CombineTest() {
        std::vector<IHasChemicalFormula*> theList = {
            new PhysicalObjectWithChemicalFormula(L"C2H3NO"),
            new PhysicalObjectWithChemicalFormula(L"CO")
        };
        auto c = ChemicalFormula::Combine(theList);

        Assert::AreEqual(L"C3H3NO2", c->getFormula());
    }

    void ChemicalFormulaTestFixture::ValidatePeriodicTable() {
        Assert::IsTrue(PeriodicTable::ValidateAverageMasses(1e-2));
        Assert::IsFalse(PeriodicTable::ValidateAverageMasses(1e-3));
        Assert::IsTrue(PeriodicTable::ValidateAbundances(1e-15));
        Assert::IsFalse(PeriodicTable::ValidateAbundances(0));
    }

    void ChemicalFormulaTestFixture::TestAddChemicalFormula() {
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"C");
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"C{12}");
        formulaB->Add(formulaA);
        Assert::AreEqual(L"CC{12}", formulaB->getFormula());
    }

    void ChemicalFormulaTestFixture::NotEqual() {
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"C15O15H15S15N15");
        ChemicalFormula *formulaA = ChemicalFormula::ParseFormula(L"N15S15H15O15C15");
        Assert::AreEqual(formulaA, formulaB);
        Assert::IsTrue(std::abs(formulaA->getMonoisotopicMass() - formulaB->getMonoisotopicMass()) < 1e-9);
    }

    void ChemicalFormulaTestFixture::TestRemoveObjectFromChemicalFormula() {
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"CO");
        auto ok = new PhysicalObjectWithChemicalFormula(L"C");
        formulaB->Remove(ok);

        Assert::AreEqual(L"O", formulaB->getFormula());

//C# TO C++ CONVERTER TODO TASK: A 'delete ok' statement was not added since ok was passed to a method or constructor. Handle memory management manually.
    }

    void ChemicalFormulaTestFixture::TestEquality() {
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"CO");
        Assert::AreEqual(formulaB, formulaB);
    }

    void ChemicalFormulaTestFixture::TestToChemicalFormula() {
        ChemicalFormula *formulaB = ChemicalFormula::ParseFormula(L"CO");
        Assert::AreEqual(ChemicalFormula::ParseFormula(L"CO"), formulaB);
    }

    void ChemicalFormulaTestFixture::IsoTest() {
        ChemicalFormula *formula = ChemicalFormula::ParseFormula(L"C5H8NO");

        IsotopicDistribution *d = IsotopicDistribution::GetDistribution(formula, std::pow(2, -14));

        Assert::AreEqual(324, d->getIntensities().size()());

        d = IsotopicDistribution::GetDistribution(formula, std::pow(2, -1));

        Assert::AreEqual(17, d->getIntensities().size()());
    }

    ChemicalFormulaTestFixture::PhysicalObjectWithChemicalFormula::PhysicalObjectWithChemicalFormula(const std::wstring &v) {
        setThisChemicalFormula(ChemicalFormula::ParseFormula(v));
    }

    double ChemicalFormulaTestFixture::PhysicalObjectWithChemicalFormula::getMonoisotopicMass() const {
        return getThisChemicalFormula()->getMonoisotopicMass();
    }

    ChemicalFormula *ChemicalFormulaTestFixture::PhysicalObjectWithChemicalFormula::getThisChemicalFormula() const {
        return privateThisChemicalFormula;
    }

    void ChemicalFormulaTestFixture::PhysicalObjectWithChemicalFormula::setThisChemicalFormula(ChemicalFormula *value) {
        privateThisChemicalFormula = value;
    }
}
