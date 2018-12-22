#include "UsefulProteomicsDatabases.Generated.def.h"
#include "UsefulProteomicsDatabases.Generated.defDbxref.h"

namespace UsefulProteomicsDatabases {
    namespace Generated {

        std::wstring def::getdefstr() const {
            return this->defstrField;
        }

        void def::setdefstr(const std::wstring &value) {
            this->defstrField = value;
        }

        std::vector<defDbxref*> def::getdbxref() const {
            return this->dbxrefField;
        }

        void def::setdbxref(const std::vector<defDbxref*> &value) {
            this->dbxrefField = value;
        }
    }
}
