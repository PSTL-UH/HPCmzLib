#pragma once

#include "../Chemistry/Interfaces/IHasChemicalFormula.h"
#include <string>
#include <vector>
#include <cmath>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Chemistry { class ChemicalFormula; }

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work copyright 2016 Stefan Solntsev
//
// This file (ChemicalFormulaTestFixture.cs) is part of Chemistry Library.
//
// Chemistry Library is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Chemistry Library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with Chemistry Library. If not, see <http://www.gnu.org/licenses/>

using namespace Chemistry;
using namespace MzLibUtil;
using namespace NUnit::Framework;

namespace Test {
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [TestFixture] public static class ChemicalFormulaTestFixture
    class ChemicalFormulaTestFixture final {
//        #region Public Methods

    public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void AddIsotopeWithExistingMassNumber()
        static void AddIsotopeWithExistingMassNumber();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void AddElementToFormula()
        static void AddElementToFormula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void Multiply()
        static void Multiply();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void CheckToStringOfElements()
        static void CheckToStringOfElements();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void AddFormulaToFormula()
        static void AddFormulaToFormula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void AddFormulaToItself()
        static void AddFormulaToItself();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void AddIChemicalFormulaToFormula()
        static void AddIChemicalFormulaToFormula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void AddIsotopeToFormula()
        static void AddIsotopeToFormula();

        /// <summary>
        /// This tests that the array for chemical formula properly expands
        /// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void AddLargeElementToFormula()
        static void AddLargeElementToFormula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void AddNegativeFormulaToFormula()
        static void AddNegativeFormulaToFormula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void AddNegativeIsotopeToFormula()
        static void AddNegativeIsotopeToFormula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void AddELementByAtomicNumber()
        static void AddELementByAtomicNumber();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void AddNonExistentSymbolToFormula()
        static void AddNonExistentSymbolToFormula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void InexistingElement()
        static void InexistingElement();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void AddZeroElementToFormula()
        static void AddZeroElementToFormula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void AddZeroIsotopeToFormula()
        static void AddZeroIsotopeToFormula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void AddZeroSymbolToFormula()
        static void AddZeroSymbolToFormula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void ClearFormula()
        static void ClearFormula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void ConstructorBlankStringEqualsEmptyFormula()
        static void ConstructorBlankStringEqualsEmptyFormula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void ConstructorDefaultEqualsEmptyFormula()
        static void ConstructorDefaultEqualsEmptyFormula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void CopyConstructorValueEquality()
        static void CopyConstructorValueEquality();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void CopyConstructorReferenceInequality()
        static void CopyConstructorReferenceInequality();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void EmptyMonoisotopicMassIsZero()
        static void EmptyMonoisotopicMassIsZero();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void EmptyAverageMassIsZero()
        static void EmptyAverageMassIsZero();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void EmptyStringIsBlank()
        static void EmptyStringIsBlank();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void EmptyAtomCountIsZero()
        static void EmptyAtomCountIsZero();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void EmptyElementCountIsZero()
        static void EmptyElementCountIsZero();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void EmptyIsotopeCountIsZero()
        static void EmptyIsotopeCountIsZero();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void FormulaValueInequality()
        static void FormulaValueInequality();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void FormulaValueInequalityHeavyIsotope()
        static void FormulaValueInequalityHeavyIsotope();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void FormulaValueEqualityItself()
        static void FormulaValueEqualityItself();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void FormulaValueEquality()
        static void FormulaValueEquality();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void FormulaEquality()
        static void FormulaEquality();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void FormulaAlmostEquality()
        static void FormulaAlmostEquality();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void HashCodeEquality()
        static void HashCodeEquality();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void HashCodeImmutableEquality()
        static void HashCodeImmutableEquality();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void HashCodeCheck()
        static void HashCodeCheck();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void HillNotation()
        static void HillNotation();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void HillNotationNoCarbon()
        static void HillNotationNoCarbon();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void HillNotationNoCarbonNoHydrogen()
        static void HillNotationNoCarbonNoHydrogen();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void HillNotationNoHydrogen()
        static void HillNotationNoHydrogen();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void HillNotationWithHeavyIsotope()
        static void HillNotationWithHeavyIsotope();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void HillNotationWithNegativeCount()
        static void HillNotationWithNegativeCount();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void HillNotationWithHeavyIsotopeNegativeCount()
        static void HillNotationWithHeavyIsotopeNegativeCount();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void BadFormula()
        static void BadFormula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void InvalidChemicalElement()
        static void InvalidChemicalElement();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void InvalidElementIsotope()
        static void InvalidElementIsotope();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void NumberOfAtoms()
        static void NumberOfAtoms();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void NumberOfAtomsOfEmptyFormula()
        static void NumberOfAtomsOfEmptyFormula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void NumberOfAtomsOfNegativeFormula()
        static void NumberOfAtomsOfNegativeFormula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void ParsingFormulaNoNumbers()
        static void ParsingFormulaNoNumbers();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void ParsingFormulaWithInternalSpaces()
        static void ParsingFormulaWithInternalSpaces();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void ParsingFormulaWithSpacesAtEnd()
        static void ParsingFormulaWithSpacesAtEnd();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void ParsingFormulaWithSpacesAtBeginning()
        static void ParsingFormulaWithSpacesAtBeginning();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void ParsingFormulaWithSpaces()
        static void ParsingFormulaWithSpaces();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void ParsingFormulaNoNumbersRandomOrder()
        static void ParsingFormulaNoNumbersRandomOrder();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void EqualsFalse()
        static void EqualsFalse();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void Equals()
        static void Equals();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void ParsingFormulaRepeatedElements()
        static void ParsingFormulaRepeatedElements();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void IsSuperSetOf()
        static void IsSuperSetOf();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void ParsingFormulaRepeatedElementsCancelEachOther()
        static void ParsingFormulaRepeatedElementsCancelEachOther();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void RemoveElementCompletelyFromFromula()
        static void RemoveElementCompletelyFromFromula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void RemoveElementCompletelyFromFromulaBySymbol()
        static void RemoveElementCompletelyFromFromulaBySymbol();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void RemoveElementCompletelyFromFromulaWithHeavyIsotope()
        static void RemoveElementCompletelyFromFromulaWithHeavyIsotope();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void RemoveEmptyFormulaFromFromula()
        static void RemoveEmptyFormulaFromFromula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void RemoveFormulaFromFromula()
        static void RemoveFormulaFromFromula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void ContainsSpecificIsotope()
        static void ContainsSpecificIsotope();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void ContainsIsotopesOf()
        static void ContainsIsotopesOf();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void HydrogenCarbonRatio()
        static void HydrogenCarbonRatio();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void RemoveIsotopeCompletelyFromFromula()
        static void RemoveIsotopeCompletelyFromFromula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void RemoveElementFromFromula()
        static void RemoveElementFromFromula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void RemoveIsotopeFromFromulaEquality()
        static void RemoveIsotopeFromFromulaEquality();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void RemoveNegativeElementFromFromula()
        static void RemoveNegativeElementFromFromula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void RemoveNonExistantIsotopeFromFromula()
        static void RemoveNonExistantIsotopeFromFromula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void RemoveZeroIsotopeFromFromula()
        static void RemoveZeroIsotopeFromFromula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void TotalProtons()
        static void TotalProtons();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void TotalProtons2()
        static void TotalProtons2();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void AverageMass()
        static void AverageMass();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void UniqueElements()
        static void UniqueElements();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void UniqueElementsOfEmptyFormula()
        static void UniqueElementsOfEmptyFormula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void UniqueElementsWithHeavyIsotope()
        static void UniqueElementsWithHeavyIsotope();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void UniqueIsotopes()
        static void UniqueIsotopes();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void UniqueIsotopesOfEmptyFormula()
        static void UniqueIsotopesOfEmptyFormula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void UniqueIsotopesWithHeavyIsotope()
        static void UniqueIsotopesWithHeavyIsotope();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void ContainsIsotopesOfYe()
        static void ContainsIsotopesOfYe();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void TestReplaceIsotopes()
        static void TestReplaceIsotopes();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void ChemicalForulaIsSubSet()
        static void ChemicalForulaIsSubSet();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void ChemicalForulaIsNotSubSet()
        static void ChemicalForulaIsNotSubSet();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void ChemicalForulaIsSuperSet()
        static void ChemicalForulaIsSuperSet();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void ChemicalForulaIsNotSuperSet()
        static void ChemicalForulaIsNotSuperSet();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void ChemicalForulaMyTest()
        static void ChemicalForulaMyTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void TestIsotopicDistribution()
        static void TestIsotopicDistribution();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void TestIsotopicDistribution2()
        static void TestIsotopicDistribution2();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void TestIsotopicDistribution3()
        static void TestIsotopicDistribution3();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void CatchIsotopicDistributionStuff()
        static void CatchIsotopicDistributionStuff();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void CatchProbStuff()
        static void CatchProbStuff();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void I0j1()
        static void I0j1();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void ThresholdProbability()
        static void ThresholdProbability();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void TestAnotherFormula()
        static void TestAnotherFormula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void NeutronCount()
        static void NeutronCount();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void NeutronCountFail()
        static void NeutronCountFail();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void CombineTest()
        static void CombineTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void ValidatePeriodicTable()
        static void ValidatePeriodicTable();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void TestAddChemicalFormula()
        static void TestAddChemicalFormula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void NotEqual()
        static void NotEqual();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void TestRemoveObjectFromChemicalFormula()
        static void TestRemoveObjectFromChemicalFormula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void TestEquality()
        static void TestEquality();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void TestToChemicalFormula()
        static void TestToChemicalFormula();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void IsoTest()
        static void IsoTest();

//        #endregion Public Methods

//        #region Private Classes

    private:
        class PhysicalObjectWithChemicalFormula : public IHasChemicalFormula {
        private:
            ChemicalFormula *privateThisChemicalFormula;

//            #region Public Constructors

        public:
            PhysicalObjectWithChemicalFormula(const std::wstring &v);

//            #endregion Public Constructors

//            #region Public Properties

            double getMonoisotopicMass() const override;

            ChemicalFormula *getThisChemicalFormula() const override;
            void setThisChemicalFormula(ChemicalFormula *value) override;

//            #endregion Public Properties
        };

//        #endregion Private Classes
    };
}
