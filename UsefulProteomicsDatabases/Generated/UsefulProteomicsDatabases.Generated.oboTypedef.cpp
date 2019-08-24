#include "UsefulProteomicsDatabases.Generated.oboTypedef.h"
#include "UsefulProteomicsDatabases.Generated.def.h"

namespace UsefulProteomicsDatabases
{
    namespace Generated
    {

        std::string oboTypedef::getid() const
        {
            return this->idField;
        }

        void oboTypedef::setid(const std::string &value)
        {
            this->idField = value;
        }

        std::string oboTypedef::getname() const
        {
            return this->nameField;
        }

        void oboTypedef::setname(const std::string &value)
        {
            this->nameField = value;
        }

        std::string oboTypedef::getcomment() const
        {
            return this->commentField;
        }

        void oboTypedef::setcomment(const std::string &value)
        {
            this->commentField = value;
        }

        std::string oboTypedef::getis_transitive() const
        {
            return this->is_transitiveField;
        }

        void oboTypedef::setis_transitive(const std::string &value)
        {
            this->is_transitiveField = value;
        }

        std::string oboTypedef::getnamespace_Renamed() const
        {
            return this->namespaceField;
        }

        void oboTypedef::setnamespace_Renamed(const std::string &value)
        {
            this->namespaceField = value;
        }

        std::vector<UsefulProteomicsDatabases::Generated::def*> oboTypedef::getdef() const
        {
            return this->defField;
        }

        void oboTypedef::setdef(const std::vector<UsefulProteomicsDatabases::Generated::def*> &value)
        {
            this->defField = value;
        }
    }
}
