#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <cmath>
#include <tuple>
#include "stringbuilder.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
//namespace Chemistry { class Isotope; }
#include "Isotope.h"

//namespace Chemistry { class Element; }
#include "Element.h"

//namespace Chemistry { class IHasChemicalFormula; }
#include "Interfaces/IHasChemicalFormula.h"

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work copyright 2016, 2017 Stefan Solntsev
//
// This file (ChemicalFormula.cs) is part of Chemistry Library.
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
// License along with Chemistry Library. If not, see <http://www.gnu.org/licenses/>.

#include "MzLibUtil.h"
using namespace MzLibUtil;

namespace Chemistry {
    /// <summary>
    /// A chemical formula class. This does NOT correspond to a physical object. A physical object can have a chemical formula.
    /// Formula can change!!! If isotopes or elements are changed.
    /// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Serializable] public sealed class ChemicalFormula : IEquatable<ChemicalFormula>
//    class ChemicalFormula final : public IEquatable<ChemicalFormula*> {
    class ChemicalFormula final {
    private:
        std::unordered_map<Isotope*, int> privateIsotopes;
        std::unordered_map<Element*, int> privateElements;

        // Main data stores, the isotopes and elements


        /// <summary>
        /// A regular expression for matching chemical formulas such as: C2C{13}3H5NO5
        /// \s* (at end as well) allows for optional spacing among the elements, i.e. C2 C{13}3 H5 N O5
        /// The first group is the only non-optional group and that handles the chemical symbol: H, He, etc..
        /// The second group is optional, which handles isotopes of elements: C{13} means carbon-13, while C is the carbon element with unspecified mass number
        /// The third group is optional and indicates if we are adding or subtracting the elements form the formula, C-2C{13}5 would mean first subtract 2 carbons and then add 5 carbon-13
        /// The fourth group is optional and represents the number of isotopes or elements to add, if not present it assumes 1: H2O means 2 Hydrogen and 1 Oxygen
        /// Modified from: http://stackoverflow.com/questions/4116786/parsing-a-chemical-formula-from-a-string-in-c

        /// </summary>
        // EG removed: static regex *const FormulaRegex;

        /// <summary>
        /// A wrapper for the formula regex that validates if a string is in the correct chemical formula format or not
        /// </summary>
        // EG removed: static regex *const ValidateFormulaRegex;

        std::string formulaString;


    public:
        ChemicalFormula();

//        ChemicalFormula(const ChemicalFormula &capFormula);
        ChemicalFormula(ChemicalFormula *capFormula);

        /// <summary>
        /// Gets the average mass of this chemical formula
        /// </summary>
        double getAverageMass() const;

        /// <summary>
        /// Gets the monoisotopic mass of this chemical formula: for elements use the principle isotope mass, not average mass
        /// </summary>
        double getMonoisotopicMass() const;

        /// <summary>
        /// Gets the number of atoms in this chemical formula
        /// </summary>
        int getAtomCount() const;

        /// <summary>
        /// Gets the number of unique chemical elements in this chemical formula
        /// </summary>
        int getNumberOfUniqueElementsByAtomicNumber() const;

        /// <summary>
        /// Gets the number of unique chemical isotopes in this chemical formula
        /// </summary>
        int getNumberOfUniqueIsotopes() const;

        /// <summary>
        /// Gets the string representation (Hill Notation) of this chemical formula
        /// </summary>
        std::string getFormula();

        int getProtonCount() const;

        /// <summary>
        /// The ratio of the number of Carbon to Hydrogen in this chemical formula
        /// </summary>
        /// <returns></returns>
        double getHydrogenCarbonRatio();

        std::unordered_map<Isotope*, int> getIsotopes() const;
        void setIsotopes(const std::unordered_map<Isotope*, int> &value);
        std::unordered_map<Element*, int> getElements() const;
        void setElements(const std::unordered_map<Element*, int> &value);

        static ChemicalFormula *Combine(std::vector<IHasChemicalFormula*> &formulas);

        /// <summary>
        /// Parses a string representation of chemical formula and adds the elements
        /// to this chemical formula
        /// </summary>
        /// <param name="formula">the Chemical Formula to parse</param>
        static ChemicalFormula *ParseFormula(const std::string &formula);

        int NeutronCount();

        /// <summary>
        /// Replaces one isotope with another.
        /// Replacement happens on a 1 to 1 basis, i.e., if you remove 5 you will add 5
        /// </summary>
        /// <param name="isotopeToRemove">The isotope to remove</param>
        /// <param name="isotopeToAdd">The isotope to add</param>
        void Replace(Isotope *isotopeToRemove, Isotope *isotopeToAdd);

        /// <summary>
        /// Add a chemical formula containing object to this chemical formula
        /// </summary>
        /// <param name="item">The object that contains a chemical formula</param>
        void Add(IHasChemicalFormula *item);

        void Multiply(int multiplier);

        /// <summary>
        /// Add a chemical formula to this chemical formula.
        /// </summary>
        /// <param name="formula">The chemical formula to add to this</param>
        void Add(ChemicalFormula *formula);

        /// <summary>
        /// Add the principal isotope of the element to this chemical formula
        /// given its chemical symbol
        /// </summary>
        /// <param name="element">The chemical element to add</param>
        /// <param name="count">The number of the element to add</param>
        void AddPrincipalIsotopesOf(Element *element, int count);

        void Add(Element *element, int count);
        void Add(int atomicNumber, int count);
        
        /// <summary>
        /// Add an isotope to this chemical formula
        /// </summary>
        /// <param name="isotope">The isotope to add</param>
        /// <param name="count">The number of the isotope to add</param>
        void Add(Isotope *isotope, int count);

        /// <summary>
        /// Remove a chemical formula containing object from this chemical formula
        /// </summary>
        /// <param name="item">The object that contains a chemical formula</param>
        void Remove(IHasChemicalFormula *item);

        /// <summary>
        /// Remove a chemical formula from this chemical formula
        /// </summary>
        /// <param name="formula">The chemical formula to remove</param>
        void Remove(ChemicalFormula *formula);

        /// <summary>
        /// Remove the provided number of elements (not isotopes!) from formula
        /// </summary>
        /// <param name="element">The chemical element to remove</param>
        /// <param name="count">The number of elements to remove</param>
        void Remove(Element *element, int count);

        /// <summary>
        /// Remove a isotope from this chemical formula
        /// </summary>
        /// <param name="isotope">The isotope to remove</param>
        /// <param name="count">The number of isotopes to remove</param>
        void Remove(Isotope *isotope, int count);

        /// <summary>
        /// Completely removes a particular isotope from this chemical formula.
        /// </summary>
        /// <param name="isotope">The isotope to remove</param>
        /// <returns>Number of removed isotopes</returns>
        int Remove(Isotope *isotope);

        /// <summary>
        /// Remove all the isotopes of an chemical element from this
        /// chemical formula
        /// </summary>
        /// <param name="element">The chemical element to remove</param>
        /// <returns>Number of removed isotopes</returns>
        int RemoveIsotopesOf(Element *element);

        /// <summary>
        /// Remove all isotopes and elements
        /// </summary>
        void Clear();

        /// <summary>
        /// Checks if any isotope of the specified element is present in this chemical formula
        /// </summary>
        /// <param name="element">The element to look for</param>
        /// <returns>True if there is a non-zero number of the element in this formula</returns>
        bool ContainsIsotopesOf(Element *element);

        bool IsSubsetOf(ChemicalFormula *formula);

        /// <summary>
        /// Checks whether this formula contains all the isotopes of the specified formula
        /// MIGHT CONSIDER ELEMENTS TO BE SUPERSET OF ISOTOPES IF NEEDED!!!
        /// Right now they are distinct
        /// </summary>
        /// <param name="formula"></param>
        /// <returns></returns>
        bool IsSupersetOf(ChemicalFormula *formula);

        bool ContainsSpecificIsotope(Element *element, int atomicNumber);

        /// <summary>
        /// Checks if the isotope is present in this chemical formula
        /// </summary>
        /// <param name="isotope">The isotope to look for</param>
        /// <returns>True if there is a non-negative number of the isotope in this formula</returns>
        bool ContainsSpecificIsotope(Isotope *isotope);

        /// <summary>
        /// Return the number of given isotopes in this chemical fomrula
        /// </summary>
        /// <param name="isotope"></param>
        /// <returns></returns>
        int CountSpecificIsotopes(Isotope *isotope);

        /// <summary>
        /// Count the number of isotopes and elements from this element that are
        /// present in this chemical formula
        /// </summary>
        /// <param name="element">The element to search for</param>
        /// <returns>The total number of all the element isotopes in this chemical formula</returns>
        int CountWithIsotopes(Element *element);

        int CountSpecificIsotopes(Element *element, int massNumber);

//        int GetHashCode() override;
        int GetHashCode();

//        bool Equals(ChemicalFormula *other) override;
        bool Equals(ChemicalFormula *other);

        /// <summary>
        /// Produces the Hill Notation of the chemical formula
        /// </summary>
    private:
        std::string GetHillNotation();
    };
}
