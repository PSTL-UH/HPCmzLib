#include "pepXML.Generated.database_refresh_timestamp.h"

namespace pepXML
{
    namespace Generated
    {

        std::string database_refresh_timestamp::getdatabase() const
        {
            return this->databaseField;
        }

        void database_refresh_timestamp::setdatabase(const std::string &value)
        {
            this->databaseField = value;
        }

        std::string database_refresh_timestamp::getmin_num_enz_term() const
        {
            return this->min_num_enz_termField;
        }

        void database_refresh_timestamp::setmin_num_enz_term(const std::string &value)
        {
            this->min_num_enz_termField = value;
        }
    }
}
