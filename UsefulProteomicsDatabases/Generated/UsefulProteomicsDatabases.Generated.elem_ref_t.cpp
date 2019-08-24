#include "UsefulProteomicsDatabases.Generated.elem_ref_t.h"

namespace UsefulProteomicsDatabases
{
    namespace Generated
    {

        elem_ref_t::elem_ref_t()
        {
            this->numberField = "1";
        }

        std::string elem_ref_t::getsymbol() const
        {
            return this->symbolField;
        }

        void elem_ref_t::setsymbol(const std::string &value)
        {
            this->symbolField = value;
        }

        std::string elem_ref_t::getnumber() const
        {
            return this->numberField;
        }

        void elem_ref_t::setnumber(const std::string &value)
        {
            this->numberField = value;
        }
    }
}
