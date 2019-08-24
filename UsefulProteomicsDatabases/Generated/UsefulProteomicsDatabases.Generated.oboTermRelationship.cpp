#include "UsefulProteomicsDatabases.Generated.oboTermRelationship.h"

namespace UsefulProteomicsDatabases
{
    namespace Generated
    {

        std::string oboTermRelationship::gettype() const
        {
            return this->typeField;
        }

        void oboTermRelationship::settype(const std::string &value)
        {
            this->typeField = value;
        }

        std::string oboTermRelationship::getto() const
        {
            return this->toField;
        }

        void oboTermRelationship::setto(const std::string &value)
        {
            this->toField = value;
        }
    }
}
