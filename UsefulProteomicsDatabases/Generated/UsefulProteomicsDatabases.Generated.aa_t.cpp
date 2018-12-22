#include "UsefulProteomicsDatabases.Generated.aa_t.h"
#include "UsefulProteomicsDatabases.Generated.elem_ref_t.h"

namespace UsefulProteomicsDatabases {
    namespace Generated {

        std::vector<elem_ref_t*> aa_t::getelement() const {
            return this->elementField;
        }

        void aa_t::setelement(const std::vector<elem_ref_t*> &value) {
            this->elementField = value;
        }

        std::wstring aa_t::gettitle() const {
            return this->titleField;
        }

        void aa_t::settitle(const std::wstring &value) {
            this->titleField = value;
        }

        std::wstring aa_t::getthree_letter() const {
            return this->three_letterField;
        }

        void aa_t::setthree_letter(const std::wstring &value) {
            this->three_letterField = value;
        }

        std::wstring aa_t::getfull_name() const {
            return this->full_nameField;
        }

        void aa_t::setfull_name(const std::wstring &value) {
            this->full_nameField = value;
        }

        double aa_t::getmono_mass() const {
            return this->mono_massField;
        }

        void aa_t::setmono_mass(double value) {
            this->mono_massField = value;
        }

        bool aa_t::getmono_massSpecified() const {
            return this->mono_massFieldSpecified;
        }

        void aa_t::setmono_massSpecified(bool value) {
            this->mono_massFieldSpecified = value;
        }

        double aa_t::getavge_mass() const {
            return this->avge_massField;
        }

        void aa_t::setavge_mass(double value) {
            this->avge_massField = value;
        }

        bool aa_t::getavge_massSpecified() const {
            return this->avge_massFieldSpecified;
        }

        void aa_t::setavge_massSpecified(bool value) {
            this->avge_massFieldSpecified = value;
        }
    }
}
