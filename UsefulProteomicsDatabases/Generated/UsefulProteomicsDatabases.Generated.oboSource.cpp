#include "UsefulProteomicsDatabases.Generated.oboSource.h"

namespace UsefulProteomicsDatabases
{
    namespace Generated
    {

        std::string oboSource::getsource_type() const
        {
            return this->source_typeField;
        }

        void oboSource::setsource_type(const std::string &value)
        {
            this->source_typeField = value;
        }

        std::string oboSource::getsource_path() const
        {
            return this->source_pathField;
        }

        void oboSource::setsource_path(const std::string &value)
        {
            this->source_pathField = value;
        }
    }
}
