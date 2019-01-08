#include "ModificationWithMass.h"
#include "ModificationMotif.h"


namespace Proteomics {

    ModificationWithMass::ModificationWithMass(const std::string &id, const std::string &modificationType, ModificationMotif *motif, TerminusLocalization terminusLocalization, double monoisotopicMass, std::unordered_map<std::string, std::vector<std::string>> &externalDatabaseReferences, std::vector<std::string> &keywords, std::vector<double> &neutralLosses, std::vector<double> &diagnosticIons) : ModificationWithLocation(id, modificationType, motif, terminusLocalization, externalDatabaseReferences, keywords), monoisotopicMass(monoisotopicMass), diagnosticIons(diagnosticIons ? diagnosticIons : std::vector<double>()), neutralLosses(neutralLosses ? neutralLosses : std::vector<double> {0}) {

        // Optional

        this->neutralLosses = this->neutralLosses.OrderBy([&] (std::any b) {
            return b;
        }).ToList();
        this->diagnosticIons = this->diagnosticIons.OrderBy([&] (std::any b) {
            return b;
        }).ToList();
    }

    std::string ModificationWithMass::ToString() {
        StringBuilder *sb = new StringBuilder();
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
        sb->appendLine(ModificationWithLocation::ToString());
        if (neutralLosses.size()() != 1 || neutralLosses.front() != 0) {
            sb->appendLine(L"NL   " + std::string::Join(L" or ", neutralLosses.Select([&] (std::any b) {
                b.ToString(CultureInfo::InvariantCulture);
            })));
        }
        if (diagnosticIons.size()() > 0) {
            sb->appendLine(L"DI   " + std::string::Join(L" or ", diagnosticIons.Select([&] (std::any b) {
                b.ToString(CultureInfo::InvariantCulture);
            })));
        }
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
        sb->append(L"MM   " + monoisotopicMass.ToString(CultureInfo::InvariantCulture));

        delete sb;
        return sb->toString();
    }

    bool ModificationWithMass::Equals(std::any o) {
        ModificationWithMass *m = dynamic_cast<ModificationWithMass*>(o);
        return m != nullptr && ModificationWithLocation::Equals(m) && ApproxSequenceEqual(diagnosticIons, m->diagnosticIons, tolForEquality) && ApproxSequenceEqual(neutralLosses, m->neutralLosses, tolForEquality) && std::abs(monoisotopicMass - m->monoisotopicMass) < tolForEquality;
    }

    int ModificationWithMass::GetHashCode() {
        return ModificationWithLocation::GetHashCode() ^ diagnosticIons.size() ^ diagnosticIons.size();
    }

    bool ModificationWithMass::ApproxSequenceEqual(std::vector<double> &a, std::vector<double> &b, double tolForEquality) {
        for (int i = 0; i < a.size(); i++) {
            if (std::abs(a[i] - b[i]) >= tolForEquality) {
                return false;
            }
        }
        return true;
    }
}
