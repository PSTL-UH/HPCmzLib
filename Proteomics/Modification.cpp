#include "Modification.h"


namespace Proteomics {

    Modification::Modification(const std::string &id, const std::string &modificationType) : id(id), modificationType(modificationType) {
    }

    std::string Modification::ToString() {
        StringBuilder *sb = new StringBuilder();
        sb->appendLine("ID   " + id);
        sb->append("MT   " + modificationType);

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
