#include "ModificationWithMassAndCf.h"
#include "../Chemistry/ChemicalFormula.h"
#include "ModificationMotif.h"

using namespace Chemistry;

namespace Proteomics {

    ModificationWithMassAndCf::ModificationWithMassAndCf(const std::string &id, const std::string &modificationType, ModificationMotif *motif, TerminusLocalization terminusLocalization, ChemicalFormula *chemicalFormula, std::optional<double> &mm, std::unordered_map<std::string, std::vector<std::string>> &linksToOtherDbs, std::vector<std::string> &keywords, std::vector<double> &neutralLosses, std::vector<double> &diagnosticIons) : ModificationWithMass(id, modificationType, motif, terminusLocalization, mm ? mm : chemicalFormula->getMonoisotopicMass(), linksToOtherDbs, keywords, neutralLosses, diagnosticIons), chemicalFormula(chemicalFormula) {
    }

    std::string ModificationWithMassAndCf::ToString() {
        StringBuilder *sb = new StringBuilder();

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
        auto baseString = ModificationWithMass::ToString();
        if (std::abs(monoisotopicMass - chemicalFormula->getMonoisotopicMass()) < tolForEquality) {
            baseString = Regex::Replace(baseString, LR"(MM.*$)", "CF   " + chemicalFormula->getFormula());
            sb->append(baseString);
        }
        else {
            sb->appendLine(baseString);
            sb->append("CF   " + chemicalFormula->getFormula());
        }

        delete sb;
        return sb->toString();
    }

    bool ModificationWithMassAndCf::Equals(std::any o) {
        ModificationWithMassAndCf *m = dynamic_cast<ModificationWithMassAndCf*>(o);
        return m != nullptr && ModificationWithMass::Equals(m) && chemicalFormula->Equals(m->chemicalFormula);
    }

    int ModificationWithMassAndCf::GetHashCode() {
        return ModificationWithMass::GetHashCode() ^ chemicalFormula->GetHashCode();
    }
}
