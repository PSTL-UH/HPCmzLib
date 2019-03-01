#pragma once

#include "Constants.h"
#include <string>
#include <vector>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Chemistry { class Isotope; }

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work copyright 2016, 2017 Stefan Solntsev
//
// This file (Element.cs) is part of Chemistry Library.
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
    /// Represents a single chemical element. Elements comprises of multiple
    /// isotopes, with the element mass being a weighted average of all the
    /// isotopes atomic masses weighted by their natural relative abundance.
    /// </summary>
    class Element {
    private:
        int privateAtomicNumber = 0;
        std::string privateAtomicSymbol;
        double privateAverageMass = 0;
        Isotope *privatePrincipalIsotope;

        // Two data stores for isotopes! An array for fast access and a list for enumeration!

        /// <summary>
        /// The element's isotopes stored based on their mass number
        /// </summary>
        std::vector<Isotope*> IsotopesByMassNumber = std::vector<Isotope*>(Constants::MaximumMassNumberPossible + 1);

        /// <summary>
        /// The element's isotopes stored in order they were added
        /// </summary>
        std::vector<Isotope*> IsotopesInOrderTheyWereAdded = std::vector<Isotope*>(Constants::MaximumMassNumberPossible + 1);

        /// <summary>
        /// Create a new element
        /// </summary>
        /// <param name="symbol">The symbol of the element</param>
        /// <param name="atomicNumber">The atomic number of the element</param>
        /// <param name="averageMass">The averageMass of the element</param>
    public:
        Element(const std::string &symbol, int atomicNumber, double averageMass);

        /// <summary>
        /// Gets all isotopes of an element
        /// </summary>
        std::vector<Isotope*> getIsotopes() const;

        /// <summary>
        /// The atomic number of this element (also the number of protons)
        /// </summary>
        int getAtomicNumber() const;

        /// <summary>
        /// The atomic symbol of this element
        /// </summary>
        std::string getAtomicSymbol() const;

        /// <summary>
        /// The average mass of all this element's isotopes weighted by their
        /// relative natural abundance (in unified atomic mass units)
        /// </summary>
        double getAverageMass() const;

        /// <summary>
        /// The most abundant (principal) isotope of this element
        /// </summary>
        Isotope *getPrincipalIsotope() const;
        void setPrincipalIsotope(Isotope *value);

        int getProtons() const;

        /// <summary>
        /// Gets an isotope of this element based on its mass number
        /// </summary>
        Isotope *operator [](int massNumber);

        /// <summary>
        /// Can use an integer instead of an element anytime you like
        /// </summary>
        /// <param name="atomicNumber"></param>
//C# TO C++ CONVERTER TODO TASK: C++ cast operators must convert from the enclosing type to another type:
//        static operator Element*(int atomicNumber);
//        operator Element*(int atomicNumber);

        /// <summary>
        /// Can use the atomic symbol instead of an element anytime you like
        /// </summary>
//C# TO C++ CONVERTER TODO TASK: C++ cast operators must convert from the enclosing type to another type:
//      static  operator Element*(const std::wstring &atomicSymbol);
//        operator Element*(const std::string &atomicSymbol);

        /// <summary>
        /// Returns the atomic symbol
        /// </summary>
        /// <returns>The atomic symbol</returns>
        std::string ToString();

        /// <summary>
        /// Add an isotope to this element
        /// </summary>
        /// <param name="massNumber">The mass number of the isotope</param>
        /// <param name="atomicMass">The atomic mass of the isotope </param>
        /// <param name="abundance">The natural relative abundance of the isotope</param>
        /// <returns>The created isotopes that is added to this element</returns>
        void AddIsotope(int massNumber, double atomicMass, double abundance);

    };
}
