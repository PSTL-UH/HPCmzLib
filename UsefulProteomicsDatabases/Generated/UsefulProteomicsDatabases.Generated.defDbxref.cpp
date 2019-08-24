#include "UsefulProteomicsDatabases.Generated.defDbxref.h"

namespace UsefulProteomicsDatabases
{
    namespace Generated
    {

        std::string defDbxref::getacc() const
        {
            return this->accField;
        }

        void defDbxref::setacc(const std::string &value)
        {
            this->accField = value;
        }

        std::string defDbxref::getdbname() const
        {
            return this->dbnameField;
        }

        void defDbxref::setdbname(const std::string &value)
        {
            this->dbnameField = value;
        }
    }
}
