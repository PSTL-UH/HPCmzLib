#include "pepXML.Generated.modInfoDataType.h"
#include "pepXML.Generated.subInfoDataType.h"
#include "pepXML.Generated.modInfoDataTypeMod_aminoacid_mass.h"

namespace pepXML
{
    namespace Generated
    {

        std::vector<subInfoDataType*> modInfoDataType::getaminoacid_substitution() const
        {
            return this->aminoacid_substitutionField;
        }

        void modInfoDataType::setaminoacid_substitution(const std::vector<subInfoDataType*> &value)
        {
            this->aminoacid_substitutionField = value;
        }

        std::vector<modInfoDataTypeMod_aminoacid_mass*> modInfoDataType::getmod_aminoacid_mass() const
        {
            return this->mod_aminoacid_massField;
        }

        void modInfoDataType::setmod_aminoacid_mass(const std::vector<modInfoDataTypeMod_aminoacid_mass*> &value)
        {
            this->mod_aminoacid_massField = value;
        }

        double modInfoDataType::getmod_nterm_mass() const
        {
            return this->mod_nterm_massField;
        }

        void modInfoDataType::setmod_nterm_mass(double value)
        {
            this->mod_nterm_massField = value;
        }

        bool modInfoDataType::getmod_nterm_massSpecified() const
        {
            return this->mod_nterm_massFieldSpecified;
        }

        void modInfoDataType::setmod_nterm_massSpecified(bool value)
        {
            this->mod_nterm_massFieldSpecified = value;
        }

        double modInfoDataType::getmod_cterm_mass() const
        {
            return this->mod_cterm_massField;
        }

        void modInfoDataType::setmod_cterm_mass(double value)
        {
            this->mod_cterm_massField = value;
        }

        bool modInfoDataType::getmod_cterm_massSpecified() const
        {
            return this->mod_cterm_massFieldSpecified;
        }

        void modInfoDataType::setmod_cterm_massSpecified(bool value)
        {
            this->mod_cterm_massFieldSpecified = value;
        }

        std::string modInfoDataType::getmodified_peptide() const
        {
            return this->modified_peptideField;
        }

        void modInfoDataType::setmodified_peptide(const std::string &value)
        {
            this->modified_peptideField = value;
        }
    }
}
