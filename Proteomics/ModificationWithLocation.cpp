#include "ModificationWithLocation.h"
#include "ModificationMotif.h"


namespace Proteomics {

const std::unordered_map<std::string, TerminusLocalization> ModificationWithLocation::terminusLocalizationTypeCodes;

    ModificationWithLocation::StaticConstructor::StaticConstructor() {
        terminusLocalizationTypeCodes = std::unordered_map<std::string, TerminusLocalization> {
            {"N-terminal.", TerminusLocalization::NProt}, {
            {"Peptide N-terminal.", TerminusLocalization::NPep}, {
            {"Anywhere.", TerminusLocalization::Any}, {
            };
    }

ModificationWithLocation::StaticConstructor ModificationWithLocation::staticConstructor;

    ModificationWithLocation::ModificationWithLocation(const std::string &id, const std::string &modificationType, ModificationMotif *motif, TerminusLocalization terminusLocalization, std::unordered_map<std::string, std::vector<std::string>> &linksToOtherDbs, std::vector<std::string> &keywords) : Modification(id, modificationType), linksToOtherDbs(linksToOtherDbs ? linksToOtherDbs : std::unordered_map<std::string, std::vector<std::string>>()), keywords(keywords ? keywords : std::vector<std::string>()), terminusLocalization(terminusLocalization), motif(motif) {

        // Optional
    }

    std::string ModificationWithLocation::ToString() {
        StringBuilder *sb = new StringBuilder();
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
        sb->appendLine(Modification::ToString());
        sb->appendLine("PP   " + terminusLocalizationTypeCodes.First([&] (std::any b) {
            b->Value->Equals(terminusLocalization);
        }).Key);
        for (auto nice : linksToOtherDbs) {
            for (auto db : nice.Value) {
                sb->appendLine("DR   " + nice.Key + "; " + db);
            }
        }
        sb->append("TG   " + motif);

        delete sb;
        return sb->toString();
    }

    bool ModificationWithLocation::Equals(std::any o) {
        ModificationWithLocation *m = dynamic_cast<ModificationWithLocation*>(o);
        return m != nullptr && Modification::Equals(m) && motif->Equals(m->motif) && terminusLocalization == m->terminusLocalization;
    }

    int ModificationWithLocation::GetHashCode() {
        return Modification::GetHashCode() ^ terminusLocalization.GetHashCode() ^ motif->GetHashCode();
    }
}
