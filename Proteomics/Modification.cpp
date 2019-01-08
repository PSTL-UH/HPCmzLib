#include "../stringhelper.h"
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

    bool Modification::Equals(Modification *m) {
//        Modification *m = dynamic_cast<Modification*>(o);
        return m != nullptr && m->id == id && m->modificationType == modificationType;
    }

    int Modification::GetHashCode() {
        return StringHelper::GetHashCode(id) ^ StringHelper::GetHashCode(modificationType);
    }
}
