#include "ChemicalFormulaFragment.h"
#include "../Chemistry/ChemicalFormula.h"
#include "AminoAcidPolymer.h"

using namespace Chemistry;

namespace Proteomics {

    ChemicalFormulaFragment::ChemicalFormulaFragment(FragmentTypes type, int number, ChemicalFormula *formula, AminoAcidPolymer *parent) : Fragment(type, number, formula->getMonoisotopicMass(), parent) {
        setThisChemicalFormula(ChemicalFormula::ParseFormula(formula->getFormula()));
    }

    ChemicalFormula *ChemicalFormulaFragment::getThisChemicalFormula() const {
        return privateThisChemicalFormula;
    }

    void ChemicalFormulaFragment::setThisChemicalFormula(ChemicalFormula *value) {
        privateThisChemicalFormula = value;
    }

    double ChemicalFormulaFragment::getMonoisotopicMass() const {
        return Fragment::getMonoisotopicMass();
    }


}
