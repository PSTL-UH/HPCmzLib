#include "UsefulProteomicsDatabases.Generated.xref_t.h"

namespace UsefulProteomicsDatabases {
    namespace Generated {

        std::wstring xref_t::gettext() const {
            return this->textField;
        }

        void xref_t::settext(const std::wstring &value) {
            this->textField = value;
        }

        xref_source_t xref_t::getsource() const {
            return this->sourceField;
        }

        void xref_t::setsource(xref_source_t value) {
            this->sourceField = value;
        }

        std::wstring xref_t::geturl() const {
            return this->urlField;
        }

        void xref_t::seturl(const std::wstring &value) {
            this->urlField = value;
        }
    }
}
