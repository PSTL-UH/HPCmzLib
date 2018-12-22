#include "UsefulProteomicsDatabases.Generated.oboTerm.h"
#include "UsefulProteomicsDatabases.Generated.def.h"
#include "UsefulProteomicsDatabases.Generated.oboTermSynonym.h"
#include "UsefulProteomicsDatabases.Generated.oboTermXref_analog.h"
#include "UsefulProteomicsDatabases.Generated.oboTermIs_a.h"
#include "UsefulProteomicsDatabases.Generated.oboTermRelationship.h"

namespace UsefulProteomicsDatabases {
    namespace Generated {

        std::wstring oboTerm::getid() const {
            return this->idField;
        }

        void oboTerm::setid(const std::wstring &value) {
            this->idField = value;
        }

        std::wstring oboTerm::getname() const {
            return this->nameField;
        }

        void oboTerm::setname(const std::wstring &value) {
            this->nameField = value;
        }

        std::wstring oboTerm::getis_obsolete() const {
            return this->is_obsoleteField;
        }

        void oboTerm::setis_obsolete(const std::wstring &value) {
            this->is_obsoleteField = value;
        }

        std::wstring oboTerm::getcomment() const {
            return this->commentField;
        }

        void oboTerm::setcomment(const std::wstring &value) {
            this->commentField = value;
        }

        std::wstring oboTerm::getsubset() const {
            return this->subsetField;
        }

        void oboTerm::setsubset(const std::wstring &value) {
            this->subsetField = value;
        }

        std::wstring oboTerm::getnamespace_Renamed() const {
            return this->namespaceField;
        }

        void oboTerm::setnamespace_Renamed(const std::wstring &value) {
            this->namespaceField = value;
        }

        std::wstring oboTerm::getis_root() const {
            return this->is_rootField;
        }

        void oboTerm::setis_root(const std::wstring &value) {
            this->is_rootField = value;
        }

        std::vector<UsefulProteomicsDatabases::Generated::def*> oboTerm::getdef() const {
            return this->defField;
        }

        void oboTerm::setdef(const std::vector<UsefulProteomicsDatabases::Generated::def*> &value) {
            this->defField = value;
        }

        std::vector<oboTermSynonym*> oboTerm::getsynonym() const {
            return this->synonymField;
        }

        void oboTerm::setsynonym(const std::vector<oboTermSynonym*> &value) {
            this->synonymField = value;
        }

        std::vector<oboTermXref_analog*> oboTerm::getxref_analog() const {
            return this->xref_analogField;
        }

        void oboTerm::setxref_analog(const std::vector<oboTermXref_analog*> &value) {
            this->xref_analogField = value;
        }

        std::vector<oboTermIs_a*> oboTerm::getis_a() const {
            return this->is_aField;
        }

        void oboTerm::setis_a(const std::vector<oboTermIs_a*> &value) {
            this->is_aField = value;
        }

        std::vector<oboTermRelationship*> oboTerm::getrelationship() const {
            return this->relationshipField;
        }

        void oboTerm::setrelationship(const std::vector<oboTermRelationship*> &value) {
            this->relationshipField = value;
        }
    }
}
