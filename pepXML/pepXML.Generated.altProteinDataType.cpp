#include "pepXML.Generated.altProteinDataType.h"
#include "pepXML.Generated.subInfoDataType.h"

namespace pepXML
{
    namespace Generated
    {

        std::vector<subInfoDataType*> altProteinDataType::getaminoacid_substitution() const
        {
            return this->aminoacid_substitutionField;
        }

        void altProteinDataType::setaminoacid_substitution(const std::vector<subInfoDataType*> &value)
        {
            this->aminoacid_substitutionField = value;
        }

        std::string altProteinDataType::getprotein() const
        {
            return this->proteinField;
        }

        void altProteinDataType::setprotein(const std::string &value)
        {
            this->proteinField = value;
        }

        std::string altProteinDataType::getprotein_descr() const
        {
            return this->protein_descrField;
        }

        void altProteinDataType::setprotein_descr(const std::string &value)
        {
            this->protein_descrField = value;
        }

        std::string altProteinDataType::getnum_tol_term() const
        {
            return this->num_tol_termField;
        }

        void altProteinDataType::setnum_tol_term(const std::string &value)
        {
            this->num_tol_termField = value;
        }

        double altProteinDataType::getprotein_mw() const
        {
            return this->protein_mwField;
        }

        void altProteinDataType::setprotein_mw(double value)
        {
            this->protein_mwField = value;
        }

        bool altProteinDataType::getprotein_mwSpecified() const
        {
            return this->protein_mwFieldSpecified;
        }

        void altProteinDataType::setprotein_mwSpecified(bool value)
        {
            this->protein_mwFieldSpecified = value;
        }

        std::string altProteinDataType::getpeptide_prev_aa() const
        {
            return this->peptide_prev_aaField;
        }

        void altProteinDataType::setpeptide_prev_aa(const std::string &value)
        {
            this->peptide_prev_aaField = value;
        }

        std::string altProteinDataType::getpeptide_next_aa() const
        {
            return this->peptide_next_aaField;
        }

        void altProteinDataType::setpeptide_next_aa(const std::string &value)
        {
            this->peptide_next_aaField = value;
        }
    }
}
