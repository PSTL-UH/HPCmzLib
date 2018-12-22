#include "pepXML.Generated.subInfoDataType.h"

namespace pepXML {
    namespace Generated {

        std::wstring subInfoDataType::getposition() const {
            return this->positionField;
        }

        void subInfoDataType::setposition(const std::wstring &value) {
            this->positionField = value;
        }

        std::wstring subInfoDataType::getorig_aa() const {
            return this->orig_aaField;
        }

        void subInfoDataType::setorig_aa(const std::wstring &value) {
            this->orig_aaField = value;
        }

        std::wstring subInfoDataType::getnum_tol_term() const {
            return this->num_tol_termField;
        }

        void subInfoDataType::setnum_tol_term(const std::wstring &value) {
            this->num_tol_termField = value;
        }

        std::wstring subInfoDataType::getpeptide_prev_aa() const {
            return this->peptide_prev_aaField;
        }

        void subInfoDataType::setpeptide_prev_aa(const std::wstring &value) {
            this->peptide_prev_aaField = value;
        }

        std::wstring subInfoDataType::getpeptide_next_aa() const {
            return this->peptide_next_aaField;
        }

        void subInfoDataType::setpeptide_next_aa(const std::wstring &value) {
            this->peptide_next_aaField = value;
        }
    }
}
