#include <sstream>
#include "stringhelper.h"
#include "ModificationWithLocation.h"
#include "ModificationMotif.h"
#include "Modification.h"

namespace Proteomics {

    std::unordered_map<std::string, TerminusLocalization> ModificationWithLocation::terminusLocalizationTypeCodes;

    ModificationWithLocation::StaticConstructor::StaticConstructor() {
        terminusLocalizationTypeCodes = std::unordered_map<std::string, TerminusLocalization> {
            {"N-terminal.", TerminusLocalization::NProt}, 
            {"Peptide N-terminal.", TerminusLocalization::NPep}, 
            {"Anywhere.", TerminusLocalization::Any}, 
        };
    }

    ModificationWithLocation::StaticConstructor ModificationWithLocation::staticConstructor;

    ModificationWithLocation::ModificationWithLocation(const std::string &i,
                                                       const std::string &mType,
                                                       ModificationMotif *motif,
                                                       TerminusLocalization terminusLocalization,
                                                       std::unordered_map<std::string, std::vector<std::string>> *lToOtherDbs,
                                                       std::vector<std::string> *kwords) : Modification(i, mType), terminusLocalization() {

        // According to C++, a reference always has to point to a valid object, it cannot be NULL. Nevertheless, to follow the logic
        // of the original C# code, converting to a pointer and checking for NULL;
        if ( lToOtherDbs != nullptr ) {
            linksToOtherDbs = *lToOtherDbs;
        }

        if ( kwords != nullptr ) {
            keywords = *kwords;
        }

        motif=motif;
    }

    std::string ModificationWithLocation::ToString() {
        StringBuilder *sb = new StringBuilder();

        sb->appendLine(Modification::ToString());
#ifdef ORIG
        sb->appendLine("PP   " + terminusLocalizationTypeCodes.First([&] (std::any b) {
            b->Value->Equals(terminusLocalization);
                }).Key);
#endif
        for ( auto t : terminusLocalizationTypeCodes ) {
            if ( t.second == terminusLocalization ) {
                sb->appendLine("PP  " + t.first);
                break;
            }
        }
                       
        for (auto nice : linksToOtherDbs) {
            for (auto db : nice.second) {
                sb->appendLine("DR   " + nice.first + "; " + db);
            }
        }
        sb->append("TG   " + motif->ToString());

        delete sb;
        return sb->toString();
    }

    bool ModificationWithLocation::Equals(ModificationWithLocation *m) {
//        ModificationWithLocation *m = dynamic_cast<ModificationWithLocation*>(o);
        return m != nullptr && Modification::Equals(m) && motif->Equals(m->motif) && terminusLocalization == m->terminusLocalization;
    }

    int ModificationWithLocation::GetHashCode() {
        return Modification::GetHashCode() ^ StringHelper::GetHashCode(TerminusLocalizationString) ^ motif->GetHashCode();
    }
}
