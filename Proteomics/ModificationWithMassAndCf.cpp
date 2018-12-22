#include "ModificationWithMassAndCf.h"
#include "../Chemistry/ChemicalFormula.h"
#include "ModificationMotif.h"

using namespace Chemistry;

namespace Proteomics {

    ModificationWithMassAndCf::ModificationWithMassAndCf(const std::wstring &id, const std::wstring &modificationType, ModificationMotif *motif, TerminusLocalization terminusLocalization, ChemicalFormula *chemicalFormula, std::optional<double> &mm, std::unordered_map<std::wstring, std::vector<std::wstring>> &linksToOtherDbs, std::vector<std::wstring> &keywords, std::vector<double> &neutralLosses, std::vector<double> &diagnosticIons) : ModificationWithMass(id, modificationType, motif, terminusLocalization, mm ? mm : chemicalFormula->getMonoisotopicMass(), linksToOtherDbs, keywords, neutralLosses, diagnosticIons), chemicalFormula(chemicalFormula) {
    }

    std::wstring ModificationWithMassAndCf::ToString() {
        StringBuilder *sb = new StringBuilder();

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
        auto baseString = ModificationWithMass::ToString();
        if (std::abs(monoisotopicMass - chemicalFormula->getMonoisotopicMass()) < tolForEquality) {
            baseString = Regex::Replace(baseString, LR"(MM.*$)", L"CF   " + chemicalFormula->getFormula());
            sb->append(baseString);
        }
        else {
            sb->appendLine(baseString);
            sb->append(L"CF   " + chemicalFormula->getFormula());
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
