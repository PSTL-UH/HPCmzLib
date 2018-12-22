#include "UsefulProteomicsDatabases.Generated.elem_ref_t.h"

namespace UsefulProteomicsDatabases {
    namespace Generated {

        elem_ref_t::elem_ref_t() {
            this->numberField = L"1";
        }

        std::wstring elem_ref_t::getsymbol() const {
            return this->symbolField;
        }

        void elem_ref_t::setsymbol(const std::wstring &value) {
            this->symbolField = value;
        }

        std::wstring elem_ref_t::getnumber() const {
            return this->numberField;
        }

        void elem_ref_t::setnumber(const std::wstring &value) {
            this->numberField = value;
        }
    }
}
