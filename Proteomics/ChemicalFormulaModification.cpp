#include "ChemicalFormulaModification.h"
#include "../Chemistry/ChemicalFormula.h"

using namespace Chemistry;

namespace Proteomics {

    OldSchoolChemicalFormulaModification::OldSchoolChemicalFormulaModification(ChemicalFormula *chemicalFormula) : OldSchoolChemicalFormulaModification(chemicalFormula, ModificationSites::Any) {
    }

    OldSchoolChemicalFormulaModification::OldSchoolChemicalFormulaModification(ChemicalFormula *chemicalFormula, ModificationSites sites) : OldSchoolChemicalFormulaModification(chemicalFormula, "", sites) {
        setName(getThisChemicalFormula()->getFormula());
    }

    OldSchoolChemicalFormulaModification::OldSchoolChemicalFormulaModification(ChemicalFormula *chemicalFormula, const std::string &name) : OldSchoolChemicalFormulaModification(chemicalFormula, name, ModificationSites::Any) {
    }

    OldSchoolChemicalFormulaModification::OldSchoolChemicalFormulaModification(ChemicalFormula *chemicalFormula, const std::string &name, ModificationSites sites) : OldSchoolModification(chemicalFormula->getMonoisotopicMass(), name, sites) {
        setThisChemicalFormula(chemicalFormula);
    }

    OldSchoolChemicalFormulaModification::OldSchoolChemicalFormulaModification(const OldSchoolChemicalFormulaModification &other) : OldSchoolChemicalFormulaModification(ChemicalFormula::ParseFormula(other.getThisChemicalFormula()->getFormula()), other.getName(), other.getSites()) {
    }

    
    ChemicalFormula *OldSchoolChemicalFormulaModification::getThisChemicalFormula() const {
        return privateThisChemicalFormula;
    }

    void OldSchoolChemicalFormulaModification::setThisChemicalFormula(ChemicalFormula *value) {
        privateThisChemicalFormula = value;
    }
}
