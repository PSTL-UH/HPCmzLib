#include "Modification.h"


namespace Proteomics {

    Modification::Modification(const std::wstring &id, const std::wstring &modificationType) : id(id), modificationType(modificationType) {
    }

    std::wstring Modification::ToString() {
        StringBuilder *sb = new StringBuilder();
        sb->appendLine(L"ID   " + id);
        sb->append(L"MT   " + modificationType);

        delete sb;
        return sb->toString();
    }

    bool Modification::Equals(std::any o) {
        Modification *m = dynamic_cast<Modification*>(o);
        return o != nullptr && m->id == id && m->modificationType == modificationType;
    }

    int Modification::GetHashCode() {
        return id.GetHashCode() ^ modificationType.GetHashCode();
    }
}
