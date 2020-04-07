#include "pepXML.Generated.asapratio_result.h"
#include "pepXML.Generated.asapratio_peptide_data.h"

namespace pepXML
{
    namespace Generated
    {

        pepXML::Generated::asapratio_peptide_data *asapratio_result::getasapratio_peptide_data() const
        {
            return this->asapratio_peptide_dataField;
        }

        void asapratio_result::setasapratio_peptide_data(pepXML::Generated::asapratio_peptide_data *value)
        {
            this->asapratio_peptide_dataField = value;
        }

        float asapratio_result::getmean() const
        {
            return this->meanField;
        }

        void asapratio_result::setmean(float value)
        {
            this->meanField = value;
        }

        float asapratio_result::geterror() const
        {
            return this->errorField;
        }

        void asapratio_result::seterror(float value)
        {
            this->errorField = value;
        }

        float asapratio_result::getheavy2light_mean() const
        {
            return this->heavy2light_meanField;
        }

        void asapratio_result::setheavy2light_mean(float value)
        {
            this->heavy2light_meanField = value;
        }

        float asapratio_result::getheavy2light_error() const
        {
            return this->heavy2light_errorField;
        }

        void asapratio_result::setheavy2light_error(float value)
        {
            this->heavy2light_errorField = value;
        }
    }
}
