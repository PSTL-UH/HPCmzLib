#include "UsefulProteomicsDatabases.Generated.oboTermRelationship.h"

namespace UsefulProteomicsDatabases {
    namespace Generated {

        std::wstring oboTermRelationship::gettype() const {
            return this->typeField;
        }

        void oboTermRelationship::settype(const std::wstring &value) {
            this->typeField = value;
        }

        std::wstring oboTermRelationship::getto() const {
            return this->toField;
        }

        void oboTermRelationship::setto(const std::wstring &value) {
            this->toField = value;
        }
    }
}
