#include "mzIdentML110.Generated.IdentifiableType.h"

namespace mzIdentML110 {
    namespace Generated {

        std::wstring IdentifiableType::getid() const {
            return this->idField;
        }

        void IdentifiableType::setid(const std::wstring &value) {
            this->idField = value;
        }

        std::wstring IdentifiableType::getname() const {
            return this->nameField;
        }

        void IdentifiableType::setname(const std::wstring &value) {
            this->nameField = value;
        }
    }
}
