#include "ModificationWithLocation.h"
#include "ModificationMotif.h"


namespace Proteomics {

const std::unordered_map<std::wstring, TerminusLocalization> ModificationWithLocation::terminusLocalizationTypeCodes;

    ModificationWithLocation::StaticConstructor::StaticConstructor() {
        terminusLocalizationTypeCodes = std::unordered_map<std::wstring, TerminusLocalization> {
            {L"N-terminal.", TerminusLocalization::NProt}, {
            {L"Peptide N-terminal.", TerminusLocalization::NPep}, {
            {L"Anywhere.", TerminusLocalization::Any}, {
            };
    }

ModificationWithLocation::StaticConstructor ModificationWithLocation::staticConstructor;

    ModificationWithLocation::ModificationWithLocation(const std::wstring &id, const std::wstring &modificationType, ModificationMotif *motif, TerminusLocalization terminusLocalization, std::unordered_map<std::wstring, std::vector<std::wstring>> &linksToOtherDbs, std::vector<std::wstring> &keywords) : Modification(id, modificationType), linksToOtherDbs(linksToOtherDbs ? linksToOtherDbs : std::unordered_map<std::wstring, std::vector<std::wstring>>()), keywords(keywords ? keywords : std::vector<std::wstring>()), terminusLocalization(terminusLocalization), motif(motif) {

        // Optional
    }

    std::wstring ModificationWithLocation::ToString() {
        StringBuilder *sb = new StringBuilder();
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
        sb->appendLine(Modification::ToString());
        sb->appendLine(L"PP   " + terminusLocalizationTypeCodes.First([&] (std::any b) {
            b->Value->Equals(terminusLocalization);
        }).Key);
        for (auto nice : linksToOtherDbs) {
            for (auto db : nice.Value) {
                sb->appendLine(L"DR   " + nice.Key + L"; " + db);
            }
        }
        sb->append(L"TG   " + motif);

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
