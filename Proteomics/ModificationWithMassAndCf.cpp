#include "ModificationWithMassAndCf.h"
#include "../Chemistry/ChemicalFormula.h"
#include "ModificationMotif.h"
#include <regex>

using namespace Chemistry;

namespace Proteomics {

    ModificationWithMassAndCf::ModificationWithMassAndCf(const std::string &id, const std::string &modificationType, ModificationMotif *motif, TerminusLocalization terminusLocalization, ChemicalFormula *chemicalFormula, double mm, std::unordered_map<std::string, std::vector<std::string>> *linksToOtherDbs, std::vector<std::string> *keywords, std::vector<double> *neutralLosses, std::vector<double> *diagnosticIons) : ModificationWithMass(id, modificationType, motif, terminusLocalization, mm, linksToOtherDbs, keywords, neutralLosses, diagnosticIons)  {
        monoisotopicMass = (mm==0.0) ? mm : chemicalFormula->getMonoisotopicMass();
        chemicalFormula = chemicalFormula;
    }

    std::string ModificationWithMassAndCf::ToString() {
        StringBuilder *sb = new StringBuilder();

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
        auto baseString = ModificationWithMass::ToString();
        if (std::abs(monoisotopicMass - chemicalFormula->getMonoisotopicMass()) < tolForEquality) {
//            baseString = Regex::Replace(baseString, LR"(MM.*$)", "CF   " + chemicalFormula->getFormula());
//            sb->append(baseString);
            std::regex reg("(MM.*$)");
            std::string b = std::regex_replace ( baseString, reg, "CF   " + chemicalFormula->getFormula());
            sb->append(b);
        }
        else {
            sb->appendLine(baseString);
            sb->append("CF   " + chemicalFormula->getFormula());
        }

        delete sb;
        return sb->toString();
    }

    bool ModificationWithMassAndCf::Equals(ModificationWithMassAndCf *m) {
//        ModificationWithMassAndCf *m = dynamic_cast<ModificationWithMassAndCf*>(o);
        return m != nullptr && ModificationWithMass::Equals(m) && chemicalFormula->Equals(m->chemicalFormula);
    }

    int ModificationWithMassAndCf::GetHashCode() {
        return ModificationWithMass::GetHashCode() ^ chemicalFormula->GetHashCode();
    }
}
