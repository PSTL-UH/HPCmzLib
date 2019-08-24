#include "UsefulProteomicsDatabases.Generated.elem_t.h"

namespace UsefulProteomicsDatabases
{
    namespace Generated
    {

        std::string elem_t::gettitle() const
        {
            return this->titleField;
        }

        void elem_t::settitle(const std::string &value)
        {
            this->titleField = value;
        }

        std::string elem_t::getfull_name() const
        {
            return this->full_nameField;
        }

        void elem_t::setfull_name(const std::string &value)
        {
            this->full_nameField = value;
        }

        double elem_t::getavge_mass() const
        {
            return this->avge_massField;
        }

        void elem_t::setavge_mass(double value)
        {
            this->avge_massField = value;
        }

        double elem_t::getmono_mass() const
        {
            return this->mono_massField;
        }

        void elem_t::setmono_mass(double value)
        {
            this->mono_massField = value;
        }
    }
}
