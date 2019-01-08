#include "ModificationMotif.h"


namespace Proteomics {

Regex *const ModificationMotif::ModificationMotifRegex = new Regex(LR"(^[A-Za-z]+$)", RegexOptions::Compiled);

    ModificationMotif::ModificationMotif(const std::string &motif) : motifString(motif) {
    }

    bool ModificationMotif::TryGetMotif(const std::string &motifString, ModificationMotif *&motif) {
        motif = nullptr;
        if (ModificationMotifRegex->IsMatch(motifString) && motifString.Count([&] (std::any b) {
            std::isupper(b);
        }) == 1) {
            motif = new ModificationMotif(motifString);
            return true;
        }
        return false;
    }

    bool ModificationMotif::Equals(std::any o) {
        ModificationMotif *m = dynamic_cast<ModificationMotif*>(o);
        return m != nullptr && m->motifString == motifString;
    }

    int ModificationMotif::GetHashCode() {
        return motifString.GetHashCode();
    }

    std::string ModificationMotif::ToString() {
        return motifString;
    }
}
