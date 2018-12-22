#include "UsefulProteomicsDatabases.Generated.oboTypedef.h"
#include "UsefulProteomicsDatabases.Generated.def.h"

namespace UsefulProteomicsDatabases {
    namespace Generated {

        std::wstring oboTypedef::getid() const {
            return this->idField;
        }

        void oboTypedef::setid(const std::wstring &value) {
            this->idField = value;
        }

        std::wstring oboTypedef::getname() const {
            return this->nameField;
        }

        void oboTypedef::setname(const std::wstring &value) {
            this->nameField = value;
        }

        std::wstring oboTypedef::getcomment() const {
            return this->commentField;
        }

        void oboTypedef::setcomment(const std::wstring &value) {
            this->commentField = value;
        }

        std::wstring oboTypedef::getis_transitive() const {
            return this->is_transitiveField;
        }

        void oboTypedef::setis_transitive(const std::wstring &value) {
            this->is_transitiveField = value;
        }

        std::wstring oboTypedef::getnamespace_Renamed() const {
            return this->namespaceField;
        }

        void oboTypedef::setnamespace_Renamed(const std::wstring &value) {
            this->namespaceField = value;
        }

        std::vector<UsefulProteomicsDatabases::Generated::def*> oboTypedef::getdef() const {
            return this->defField;
        }

        void oboTypedef::setdef(const std::vector<UsefulProteomicsDatabases::Generated::def*> &value) {
            this->defField = value;
        }
    }
}
