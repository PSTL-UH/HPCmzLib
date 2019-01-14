#pragma once

#include "../Chemistry/Interfaces/IHasChemicalFormula.h"
#include "ModificationSites.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <cmath>

//C# TO C++ CONVERTER NOTE: Forward class declarations:

#include "../Chemistry/Chemistry.h"
//namespace Chemistry { class ChemicalFormula; }

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
        char privateLetter = '\0';
        ModificationSites privateSite = static_cast<ModificationSites>(0);
        double privateMonoisotopicMass = 0;
        std::string privateName;
        std::string privateSymbol;


    public:
        static std::vector<double> ResidueMonoisotopicMass;

    private:
        static std::unordered_map<std::string, Residue*> ResiduesDictionary;
        static std::vector<Residue*> ResiduesByLetter;


    private:
        class StaticConstructor {
        public:
            StaticConstructor();
        };

    private:
        static Residue::StaticConstructor staticConstructor;


    public:
        Residue(const std::string &name, char oneLetterAbbreviation, const std::string &threeLetterAbbreviation, ChemicalFormula *chemicalFormula, ModificationSites site);


        ChemicalFormula *getThisChemicalFormula() const override;
//        void setThisChemicalFormula(ChemicalFormula *value) override;
        void setThisChemicalFormula(ChemicalFormula *value);

        char getLetter() const;
        void setLetter(char value);

        ModificationSites getSite() const;
        void setSite(ModificationSites value);

        double getMonoisotopicMass() const override;
//        void setMonoisotopicMass(double value) override;
        void setMonoisotopicMass(double value);

        std::string getName() const;
        void setName(const std::string &value);

        std::string getSymbol() const;
        void setSymbol(const std::string &value);

        /// <summary>
        /// Get the residue based on the residues's symbol
        /// </summary>
        /// <param name="symbol"></param>
        /// <returns></returns>
        static Residue *GetResidue(const std::string &symbol);

        /// <summary>
        /// Gets the resdiue based on the residue's one-character symbol
        /// </summary>
        /// <param name="letter"></param>
        /// <returns></returns>
        static Residue *GetResidue(char letter);

        static bool TryGetResidue(char letter, Residue *&residue);

        static bool TryGetResidue(const std::string &name, Residue *&residue);

    };
}
