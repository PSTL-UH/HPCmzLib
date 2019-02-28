#include "ModificationWithMass.h"
#include "ModificationMotif.h"
#include <algorithm>

namespace Proteomics {

//    ModificationWithMass::ModificationWithMass(const std::string &id, const std::string &modificationType, ModificationMotif *motif, TerminusLocalization terminusLocalization, double monoisotopicMass, std::unordered_map<std::string, std::vector<std::string>> *externalDatabaseReferences, std::vector<std::string> *keywords, std::vector<double> &neutralLosses, std::vector<double> &diagnosticIons) : ModificationWithLocation(id, modificationType, motif, terminusLocalization, externalDatabaseReferences, keywords), monoisotopicMass(monoisotopicMass), diagnosticIons(diagnosticIons ? diagnosticIons : std::vector<double> {0}), neutralLosses(neutralLosses ? neutralLosses : std::vector<double> {0}) {
    ModificationWithMass::ModificationWithMass(const std::string &id, const std::string &modificationType, ModificationMotif *motif, TerminusLocalization terminusLocalization, double monoisotopicMass, std::unordered_map<std::string, std::vector<std::string>> *externalDatabaseReferences, std::vector<std::string> *keywords, std::vector<double> *neutralLosses, std::vector<double> *diagnosticIons) : ModificationWithLocation(id, modificationType, motif, terminusLocalization, externalDatabaseReferences, keywords)  {

        monoisotopicMass = monoisotopicMass;
        diagnosticIons   = diagnosticIons;
        neutralLosses    = neutralLosses;
               
        // Optional
#ifdef ORIG
        this->neutralLosses = this->neutralLosses.OrderBy([&] (std::any b) {
            return b;
        }).ToList();
        this->diagnosticIons = this->diagnosticIons.OrderBy([&] (std::any b) {
            return b;
        }).ToList();
#endif
    std::sort(this->neutralLosses.begin(), this->neutralLosses.end());
    std::sort(this->diagnosticIons.begin(), this->diagnosticIons.end());
    }
    
    std::string ModificationWithMass::ToString() {
        StringBuilder *sb = new StringBuilder();
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
        sb->appendLine(ModificationWithLocation::ToString());

#if ORIG
        if (neutralLosses.size()() != 1 || neutralLosses.front() != 0) {
            sb->appendLine("NL   " + std::string::Join(" or ", neutralLosses.Select([&] (std::any b) {
                b.ToString(CultureInfo::InvariantCulture);
            })));
        }
        if (diagnosticIons.size()() > 0) {
            sb->appendLine("DI   " + std::string::Join(" or ", diagnosticIons.Select([&] (std::any b) {
                b.ToString(CultureInfo::InvariantCulture);
            })));
        }

#endif
        if (neutralLosses.size() != 1 || neutralLosses.front() != 0) {
            sb->appendLine("NL    or ");
            std::for_each (neutralLosses.begin(), neutralLosses.end(), [&sb] (double b) {
                    sb->appendLine(std::to_string(b));
                });
        }


        if (diagnosticIons.size() > 0) {
            sb->appendLine("DI    or ");
            std::for_each (diagnosticIons.begin(), diagnosticIons.end(), [&sb] (double b) {
                    sb->appendLine(std::to_string(b));
                });
        }
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
//        sb->append("MM   " + monoisotopicMass.ToString(CultureInfo::InvariantCulture));
        sb->append("MM   " + std::to_string(monoisotopicMass));

        delete sb;
        return sb->toString();
    }

    bool ModificationWithMass::Equals(ModificationWithMass* m) {
//        ModificationWithMass *m = dynamic_cast<ModificationWithMass*>(o);
        return m != nullptr                                                        &&
            ModificationWithLocation::Equals(m)                                    &&
            ApproxSequenceEqual(diagnosticIons, m->diagnosticIons, tolForEquality) &&
            ApproxSequenceEqual(neutralLosses, m->neutralLosses, tolForEquality)   &&
            std::abs(monoisotopicMass - m->monoisotopicMass) < tolForEquality;
    }

    int ModificationWithMass::GetHashCode() {
        return ModificationWithLocation::GetHashCode() ^ diagnosticIons.size() ^ diagnosticIons.size();
    }

    bool ModificationWithMass::ApproxSequenceEqual(std::vector<double> a, std::vector<double> b, double tolForEquality) {
        for (int i = 0; i < a.size(); i++) {
            if (std::abs(a[i] - b[i]) >= tolForEquality) {
                return false;
            }
        }
        return true;
    }
}
