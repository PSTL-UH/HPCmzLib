#pragma once

#include <string>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Chemistry { class Element; }

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work copyright 2016, 2017 Stefan Solntsev
//
// This file (Isotope.cs) is part of Chemistry Library.
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
    /// Represents a single isotope of a chemical element. Contains a unique number
    /// of protons and neutrons compared to every other isotope.
    /// </summary>
    class Isotope final {
    private:
        Chemistry::Element *privateElement;
        double privateAtomicMass = 0;
        int privateMassNumber = 0;
        double privateRelativeAbundance = 0;

        /// <summary>
        /// Create a new isotope
        /// </summary>
        /// <param name="parentElement">The parent element of the isotope</param>
        /// <param name="massNumber">The mass number of the isotope</param>
        /// <param name="atomicMass">The atomic mass of the isotope</param>
        /// <param name="abundance">The natural relative abundance of the isotope</param>
    public:
        Isotope(Chemistry::Element *parentElement, int massNumber, double atomicMass, double abundance);

        /// <summary>
        /// The atomic number of the isotope's parent element (also the number of protons)
        /// </summary>
        int getAtomicNumber() const;

        /// <summary>
        /// The number of protons in this isotope
        /// </summary>
        int getProtons() const;

        /// <summary>
        /// The number of neutrons in this isotope
        /// </summary>
        int getNeutrons() const;

        /// <summary>
        /// The element this isotope is apart of (based on atomic number)
        /// </summary>
        Chemistry::Element *getElement() const;

        /// <summary>
        /// The atomic mass of this isotope (in unified atomic mass units)
        /// </summary>
        double getAtomicMass() const;

        /// <summary>
        /// The total number of nucleons (protons and neutrons) in this isotope
        /// </summary>
        int getMassNumber() const;

        /// <summary>
        /// The relative natural abundance of this isotope in nature (on Earth)
        /// </summary>
        double getRelativeAbundance() const;

        /// <summary>
        /// Returns a textual representation of this isotope in the following format: H{1} He{4} O{16}
        /// </summary>
        /// <returns>The atomic symbol and mass number combined</returns>
        std::string ToString();

    };
}
