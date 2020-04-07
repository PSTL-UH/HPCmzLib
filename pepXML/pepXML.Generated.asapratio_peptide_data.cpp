#include "pepXML.Generated.asapratio_peptide_data.h"
#include "pepXML.Generated.asapratio_contribution.h"

namespace pepXML
{
    namespace Generated
    {

        std::vector<pepXML::Generated::asapratio_contribution*> asapratio_peptide_data::getasapratio_contribution() const
        {
            return this->asapratio_contributionField;
        }

        void asapratio_peptide_data::setasapratio_contribution(const std::vector<pepXML::Generated::asapratio_contribution*> &value)
        {
            this->asapratio_contributionField = value;
        }

        char asapratio_peptide_data::getstatus() const
        {
            return this->statusField;
        }

        void asapratio_peptide_data::setstatus(char value)
        {
            this->statusField = value;
        }

        int asapratio_peptide_data::getcidIndex() const
        {
            return this->cidIndexField;
        }

        void asapratio_peptide_data::setcidIndex(int value)
        {
            this->cidIndexField = value;
        }

        float asapratio_peptide_data::getlight_mass() const
        {
            return this->light_massField;
        }

        void asapratio_peptide_data::setlight_mass(float value)
        {
            this->light_massField = value;
        }

        float asapratio_peptide_data::getheavy_mass() const
        {
            return this->heavy_massField;
        }

        void asapratio_peptide_data::setheavy_mass(float value)
        {
            this->heavy_massField = value;
        }

        unsigned int asapratio_peptide_data::getarea_flag() const
        {
            return this->area_flagField;
        }

        void asapratio_peptide_data::setarea_flag(unsigned int value)
        {
            this->area_flagField = value;
        }
    }
}
