#include "UsefulProteomicsDatabases.Generated.brick_t.h"
#include "UsefulProteomicsDatabases.Generated.elem_ref_t.h"

namespace UsefulProteomicsDatabases
{
    namespace Generated
    {

        std::vector<elem_ref_t*> brick_t::getelement() const
        {
            return this->elementField;
        }

        void brick_t::setelement(const std::vector<elem_ref_t*> &value)
        {
            this->elementField = value;
        }

        std::string brick_t::gettitle() const
        {
            return this->titleField;
        }

        void brick_t::settitle(const std::string &value)
        {
            this->titleField = value;
        }

        std::string brick_t::getfull_name() const
        {
            return this->full_nameField;
        }

        void brick_t::setfull_name(const std::string &value)
        {
            this->full_nameField = value;
        }

        double brick_t::getmono_mass() const
        {
            return this->mono_massField;
        }

        void brick_t::setmono_mass(double value)
        {
            this->mono_massField = value;
        }

        bool brick_t::getmono_massSpecified() const
        {
            return this->mono_massFieldSpecified;
        }

        void brick_t::setmono_massSpecified(bool value)
        {
            this->mono_massFieldSpecified = value;
        }

        double brick_t::getavge_mass() const
        {
            return this->avge_massField;
        }

        void brick_t::setavge_mass(double value)
        {
            this->avge_massField = value;
        }

        bool brick_t::getavge_massSpecified() const
        {
            return this->avge_massFieldSpecified;
        }

        void brick_t::setavge_massSpecified(bool value)
        {
            this->avge_massFieldSpecified = value;
        }
    }
}
