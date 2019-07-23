#pragma once

#include "../Chemistry/Interfaces/IHasChemicalFormula.h"
#include <string>
#include <vector>
#include <cmath>

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

#include "../Chemistry/Chemistry.h"
using namespace Chemistry;
#include "../MzLibUtil/MzLibUtil.h"
using namespace MzLibUtil;

namespace Test {

    class ChemicalFormulaTestFixture final {

    public:
        static void AddIsotopeWithExistingMassNumber();

        static void AddElementToFormula();

        static void Multiply();

        static void CheckToStringOfElements();

        static void AddFormulaToFormula();

        static void AddFormulaToItself();

        static void AddIChemicalFormulaToFormula();

        static void AddIsotopeToFormula();

        /// <summary>
        /// This tests that the array for chemical formula properly expands
        /// </summary>
        static void AddLargeElementToFormula();

        static void AddNegativeFormulaToFormula();

        static void AddNegativeIsotopeToFormula();

        static void AddELementByAtomicNumber();

        static void AddNonExistentSymbolToFormula();

        static void InexistingElement();

        static void AddZeroElementToFormula();

        static void AddZeroIsotopeToFormula();

        static void AddZeroSymbolToFormula();

        static void ClearFormula();

        static void ConstructorBlankStringEqualsEmptyFormula();

        static void ConstructorDefaultEqualsEmptyFormula();

        static void CopyConstructorValueEquality();

        static void CopyConstructorReferenceInequality();

        static void EmptyMonoisotopicMassIsZero();

        static void EmptyAverageMassIsZero();

        static void EmptyStringIsBlank();

        static void EmptyAtomCountIsZero();

        static void EmptyElementCountIsZero();

        static void EmptyIsotopeCountIsZero();

        static void FormulaValueInequality();

        static void FormulaValueInequalityHeavyIsotope();

        static void FormulaValueEqualityItself();

        static void FormulaValueEquality();

        static void FormulaEquality();

        static void FormulaAlmostEquality();

        static void HashCodeEquality();

        static void HashCodeImmutableEquality();

        static void HashCodeCheck();

        static void HillNotation();

        static void HillNotationNoCarbon();

        static void HillNotationNoCarbonNoHydrogen();

        static void HillNotationNoHydrogen();

        static void HillNotationWithHeavyIsotope();

        static void HillNotationWithNegativeCount();

        static void HillNotationWithHeavyIsotopeNegativeCount();

        static void BadFormula();

        static void InvalidChemicalElement();

        static void InvalidElementIsotope();

        static void NumberOfAtoms();

        static void NumberOfAtomsOfEmptyFormula();

        static void NumberOfAtomsOfNegativeFormula();

        static void ParsingFormulaNoNumbers();

        static void ParsingFormulaWithInternalSpaces();

        static void ParsingFormulaWithSpacesAtEnd();

        static void ParsingFormulaWithSpacesAtBeginning();

        static void ParsingFormulaWithSpaces();

        static void ParsingFormulaNoNumbersRandomOrder();

        static void EqualsFalse();

        static void Equals();

        static void ParsingFormulaRepeatedElements();

        static void IsSuperSetOf();

        static void ParsingFormulaRepeatedElementsCancelEachOther();

        static void RemoveElementCompletelyFromFromula();

        static void RemoveElementCompletelyFromFromulaBySymbol();

        static void RemoveElementCompletelyFromFromulaWithHeavyIsotope();

        static void RemoveEmptyFormulaFromFromula();

        static void RemoveFormulaFromFromula();

        static void ContainsSpecificIsotope();

        static void ContainsIsotopesOf();

        static void HydrogenCarbonRatio();

        static void RemoveIsotopeCompletelyFromFromula();

        static void RemoveElementFromFromula();

        static void RemoveIsotopeFromFromulaEquality();

        static void RemoveNegativeElementFromFromula();

        static void RemoveNonExistantIsotopeFromFromula();

        static void RemoveZeroIsotopeFromFromula();

        static void TotalProtons();

        static void TotalProtons2();

        static void AverageMass();

        static void UniqueElements();

        static void UniqueElementsOfEmptyFormula();

        static void UniqueElementsWithHeavyIsotope();

        static void UniqueIsotopes();

        static void UniqueIsotopesOfEmptyFormula();

        static void UniqueIsotopesWithHeavyIsotope();

        static void ContainsIsotopesOfYe();

        static void TestReplaceIsotopes();

        static void ChemicalForulaIsSubSet();

        static void ChemicalForulaIsNotSubSet();

        static void ChemicalForulaIsSuperSet();

        static void ChemicalForulaIsNotSuperSet();

        static void ChemicalForulaMyTest();

        static void TestIsotopicDistribution();

        static void TestIsotopicDistribution2();

        static void TestIsotopicDistribution3();

        static void CatchIsotopicDistributionStuff();

        static void CatchProbStuff();

        static void I0j1();

        static void ThresholdProbability();

        static void TestAnotherFormula();

        static void NeutronCount();

        static void NeutronCountFail();

        static void CombineTest();

        static void ValidatePeriodicTable();

        static void TestAddChemicalFormula();

        static void NotEqual();

        static void TestRemoveObjectFromChemicalFormula();

        static void TestEquality();

        static void TestToChemicalFormula();

        static void IsoTest();
    };
    
    
    class PhysicalObjectWithChemicalFormula : public IHasChemicalFormula {
        private:
            ChemicalFormula *privateThisChemicalFormula;

        public:
            PhysicalObjectWithChemicalFormula(const std::string &v);

            double getMonoisotopicMass() const override;

            ChemicalFormula *getThisChemicalFormula() const override;
            void setThisChemicalFormula(ChemicalFormula *value);
        };
}
