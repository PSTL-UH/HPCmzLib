#pragma once

#include "../Chemistry/Interfaces/IHasChemicalFormula.h"
#include "ModificationSites.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <cmath>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Chemistry { class ChemicalFormula; }

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work copyright 2016 Stefan Solntsev
//
// This file (AminoAcid.cs) is part of Proteomics.
//
// Proteomics is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Proteomics is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with Proteomics. If not, see <http://www.gnu.org/licenses/>.

using namespace Chemistry;

namespace Proteomics {
    class Residue : public IHasChemicalFormula {
    private:
        ChemicalFormula *privateThisChemicalFormula;
        wchar_t privateLetter = L'\0';
        ModificationSites privateSite = static_cast<ModificationSites>(0);
        double privateMonoisotopicMass = 0;
        std::wstring privateName;
        std::wstring privateSymbol;

//        #region Public Fields

    public:
        static std::vector<double> const ResidueMonoisotopicMass;

//        #endregion Public Fields

//        #region Private Fields

    private:
        static const std::unordered_map<std::wstring, Residue*> ResiduesDictionary;
        static std::vector<Residue*> const ResiduesByLetter;

//        #endregion Private Fields

//        #region Public Constructors

    private:
        class StaticConstructor {
        public:
            StaticConstructor();
        };

    private:
        static Residue::StaticConstructor staticConstructor;


//        #endregion Public Constructors

//        #region Internal Constructors

    public:
        Residue(const std::wstring &name, wchar_t oneLetterAbbreviation, const std::wstring &threeLetterAbbreviation, ChemicalFormula *chemicalFormula, ModificationSites site);

//        #endregion Internal Constructors

//        #region Public Properties

        ChemicalFormula *getThisChemicalFormula() const override;
        void setThisChemicalFormula(ChemicalFormula *value) override;

        wchar_t getLetter() const;
        void setLetter(wchar_t value);

        ModificationSites getSite() const;
        void setSite(ModificationSites value);

        double getMonoisotopicMass() const override;
        void setMonoisotopicMass(double value) override;

        std::wstring getName() const;
        void setName(const std::wstring &value);

        std::wstring getSymbol() const;
        void setSymbol(const std::wstring &value);

//        #endregion Public Properties

//        #region Public Methods

        /// <summary>
        /// Get the residue based on the residues's symbol
        /// </summary>
        /// <param name="symbol"></param>
        /// <returns></returns>
        static Residue *GetResidue(const std::wstring &symbol);

        /// <summary>
        /// Gets the resdiue based on the residue's one-character symbol
        /// </summary>
        /// <param name="letter"></param>
        /// <returns></returns>
        static Residue *GetResidue(wchar_t letter);

        static bool TryGetResidue(wchar_t letter, Residue *&residue);

        static bool TryGetResidue(const std::wstring &name, Residue *&residue);

//        #endregion Public Methods
    };
}
