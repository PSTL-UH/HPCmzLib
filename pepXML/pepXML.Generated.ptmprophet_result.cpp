#include "pepXML.Generated.ptmprophet_result.h"
#include "pepXML.Generated.ptmprophet_resultMod_aminoacid_probability.h"

namespace pepXML
{
    namespace Generated
    {

        std::vector<ptmprophet_resultMod_aminoacid_probability*> ptmprophet_result::getmod_aminoacid_probability() const
        {
            return this->mod_aminoacid_probabilityField;
        }

        void ptmprophet_result::setmod_aminoacid_probability(const std::vector<ptmprophet_resultMod_aminoacid_probability*> &value)
        {
            this->mod_aminoacid_probabilityField = value;
        }

        float ptmprophet_result::getprior() const
        {
            return this->priorField;
        }

        void ptmprophet_result::setprior(float value)
        {
            this->priorField = value;
        }

        std::string ptmprophet_result::getptm() const
        {
            return this->ptmField;
        }

        void ptmprophet_result::setptm(const std::string &value)
        {
            this->ptmField = value;
        }

        std::string ptmprophet_result::getptm_peptide() const
        {
            return this->ptm_peptideField;
        }

        void ptmprophet_result::setptm_peptide(const std::string &value)
        {
            this->ptm_peptideField = value;
        }
    }
}
