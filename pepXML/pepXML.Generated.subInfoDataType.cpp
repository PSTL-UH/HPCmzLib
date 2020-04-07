#include "pepXML.Generated.subInfoDataType.h"

namespace pepXML
{
    namespace Generated
    {

        std::string subInfoDataType::getposition() const
        {
            return this->positionField;
        }

        void subInfoDataType::setposition(const std::string &value)
        {
            this->positionField = value;
        }

        std::string subInfoDataType::getorig_aa() const
        {
            return this->orig_aaField;
        }

        void subInfoDataType::setorig_aa(const std::string &value)
        {
            this->orig_aaField = value;
        }

        std::string subInfoDataType::getnum_tol_term() const
        {
            return this->num_tol_termField;
        }

        void subInfoDataType::setnum_tol_term(const std::string &value)
        {
            this->num_tol_termField = value;
        }

        std::string subInfoDataType::getpeptide_prev_aa() const
        {
            return this->peptide_prev_aaField;
        }

        void subInfoDataType::setpeptide_prev_aa(const std::string &value)
        {
            this->peptide_prev_aaField = value;
        }

        std::string subInfoDataType::getpeptide_next_aa() const
        {
            return this->peptide_next_aaField;
        }

        void subInfoDataType::setpeptide_next_aa(const std::string &value)
        {
            this->peptide_next_aaField = value;
        }
    }
}
