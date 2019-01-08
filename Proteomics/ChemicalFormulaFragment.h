#pragma once

#include "../Chemistry/Interfaces/IHasChemicalFormula.h"
#include "Fragment.h"
#include "FragmentTypes.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Chemistry { class ChemicalFormula; }
namespace Proteomics { class AminoAcidPolymer; }

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work copyright 2016 Stefan Solntsev
//
// This file (ChemicalFormulaFragment.cs) is part of Proteomics.
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
    class ChemicalFormulaFragment : public Fragment, public IHasChemicalFormula {
    private:
        ChemicalFormula *privateThisChemicalFormula;


    public:
        ChemicalFormulaFragment(FragmentTypes type, int number, ChemicalFormula *formula, AminoAcidPolymer *parent);

        ChemicalFormula *getThisChemicalFormula() const override;
        void setThisChemicalFormula(ChemicalFormula *value) override;

    };
}
