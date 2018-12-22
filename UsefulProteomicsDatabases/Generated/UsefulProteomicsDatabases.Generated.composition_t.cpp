#include "UsefulProteomicsDatabases.Generated.composition_t.h"
#include "UsefulProteomicsDatabases.Generated.elem_ref_t.h"

namespace UsefulProteomicsDatabases {
    namespace Generated {

        std::vector<elem_ref_t*> composition_t::getelement() const {
            return this->elementField;
        }

        void composition_t::setelement(const std::vector<elem_ref_t*> &value) {
            this->elementField = value;
        }

        std::wstring composition_t::getcomposition() const {
            return this->compositionField;
        }

        void composition_t::setcomposition(const std::wstring &value) {
            this->compositionField = value;
        }

        double composition_t::getmono_mass() const {
            return this->mono_massField;
        }

        void composition_t::setmono_mass(double value) {
            this->mono_massField = value;
        }

        bool composition_t::getmono_massSpecified() const {
            return this->mono_massFieldSpecified;
        }

        void composition_t::setmono_massSpecified(bool value) {
            this->mono_massFieldSpecified = value;
        }

        double composition_t::getavge_mass() const {
            return this->avge_massField;
        }

        void composition_t::setavge_mass(double value) {
            this->avge_massField = value;
        }

        bool composition_t::getavge_massSpecified() const {
            return this->avge_massFieldSpecified;
        }

        void composition_t::setavge_massSpecified(bool value) {
            this->avge_massFieldSpecified = value;
        }
    }
}
