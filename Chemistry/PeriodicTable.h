#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <cmath>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Chemistry { class Element; }

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work copyright 2016, 2017 Stefan Solntsev
//
// This file (PeriodicTable.cs) is part of Chemistry Library.
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


namespace Chemistry {
    /// <summary>
    /// A static store of elements accessible by anyone
    /// </summary>
    class PeriodicTable final {
        // Two datastores storing same elements! Need both for efficient access by both
        // symbol and atomic number

        /// <summary>
        /// The internal dictionary housing elements, keyed by their unique atomic symbol
        /// </summary>
    private:
//        static const std::unordered_map<std::wstring, Element*> _elements;
        static std::unordered_map<std::wstring, Element*> _elements;

        /// <summary>
        /// The internal dictionary housing elements, keyed by their unique atomic number
        /// </summary>
//        static std::vector<Element*> const _elementsArray;
        static std::vector<Element*> _elementsArray;

        /// <summary>
        /// Populate the periodic table by calling this method
        /// </summary>
    public:
        static void Add(Element *element);

        /// <summary>
        /// Fast method for getting an element by its atomic symbol
        /// </summary>
        static Element *GetElement(const std::wstring &atomicSymbol);

        /// <summary>
        /// Fast method for getting an element by its atomic number
        /// </summary>
        static Element *GetElement(int atomicNumber);

        /// <summary>
        /// Validates the abundances in the periodic table
        /// </summary>
        static bool ValidateAbundances(double epsilon);

        /// <summary>
        /// Validates the average masses in the periodic table
        /// </summary>
        static bool ValidateAverageMasses(double epsilon);

    };
}
