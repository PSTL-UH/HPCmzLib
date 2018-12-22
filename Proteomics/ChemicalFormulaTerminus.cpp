#include "ChemicalFormulaTerminus.h"
#include "../Chemistry/ChemicalFormula.h"

using namespace Chemistry;

namespace Proteomics {

    ChemicalFormulaTerminus::ChemicalFormulaTerminus(ChemicalFormula *chemicalFormula) {
        setThisChemicalFormula(chemicalFormula);
    }

    double ChemicalFormulaTerminus::getMonoisotopicMass() const {
        return getThisChemicalFormula()->getMonoisotopicMass();
    }

    ChemicalFormula *ChemicalFormulaTerminus::getThisChemicalFormula() const {
        return privateThisChemicalFormula;
    }

    void ChemicalFormulaTerminus::setThisChemicalFormula(ChemicalFormula *value) {
        privateThisChemicalFormula = value;
    }
}
