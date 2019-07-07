#pragma once

#include "../Chemistry/Interfaces/IHasChemicalFormula.h"
#include "OldSchoolModification.h"
#include "ModificationSites.h"
#include <string>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
#include "../Chemistry/ChemicalFormula.h"
//namespace Chemistry { class ChemicalFormula; }

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work copyright 2016 Stefan Solntsev
//
// This file (ChemicalFormulaModification.cs) is part of Proteomics.
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
    class OldSchoolChemicalFormulaModification : public OldSchoolModification, public IHasChemicalFormula {
    private:
        ChemicalFormula *privateThisChemicalFormula;

    public:
        OldSchoolChemicalFormulaModification(ChemicalFormula *chemicalFormula);

        OldSchoolChemicalFormulaModification(ChemicalFormula *chemicalFormula, ModificationSites sites);

        OldSchoolChemicalFormulaModification(ChemicalFormula *chemicalFormula, const std::string &name);

        OldSchoolChemicalFormulaModification(ChemicalFormula *chemicalFormula, const std::string &name, ModificationSites sites);

        OldSchoolChemicalFormulaModification(const OldSchoolChemicalFormulaModification &other);

        /// <summary>
        /// The Chemical Formula of this modifications
        /// </summary>
        ChemicalFormula *getThisChemicalFormula() const override;

//        void setThisChemicalFormula(ChemicalFormula *value) override;
        void setThisChemicalFormula(ChemicalFormula *value);

        // Added by EDGAR
        double getMonoisotopicMass() const override;
    };
}
