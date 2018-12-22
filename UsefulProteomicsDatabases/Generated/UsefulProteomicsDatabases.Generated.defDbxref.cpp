#include "UsefulProteomicsDatabases.Generated.defDbxref.h"

namespace UsefulProteomicsDatabases {
    namespace Generated {

        std::wstring defDbxref::getacc() const {
            return this->accField;
        }

        void defDbxref::setacc(const std::wstring &value) {
            this->accField = value;
        }

        std::wstring defDbxref::getdbname() const {
            return this->dbnameField;
        }

        void defDbxref::setdbname(const std::wstring &value) {
            this->dbnameField = value;
        }
    }
}
