#include "pepXML.Generated.msms_pipeline_analysisMsms_run_summarySample_enzyme.h"
#include "pepXML.Generated.msms_pipeline_analysisMsms_run_summarySample_enzymeSpecificity.h"

namespace pepXML
{
    namespace Generated
    {

        msms_pipeline_analysisMsms_run_summarySample_enzyme::msms_pipeline_analysisMsms_run_summarySample_enzyme()
        {
            this->fidelityField = msms_pipeline_analysisMsms_run_summarySample_enzymeFidelity::specific;
            this->independentField = true;
        }

        std::vector<msms_pipeline_analysisMsms_run_summarySample_enzymeSpecificity*> msms_pipeline_analysisMsms_run_summarySample_enzyme::getspecificity() const
        {
            return this->specificityField;
        }

        void msms_pipeline_analysisMsms_run_summarySample_enzyme::setspecificity(const std::vector<msms_pipeline_analysisMsms_run_summarySample_enzymeSpecificity*> &value)
        {
            this->specificityField = value;
        }

        std::string msms_pipeline_analysisMsms_run_summarySample_enzyme::getname() const
        {
            return this->nameField;
        }

        void msms_pipeline_analysisMsms_run_summarySample_enzyme::setname(const std::string &value)
        {
            this->nameField = value;
        }

        std::string msms_pipeline_analysisMsms_run_summarySample_enzyme::getdescription() const
        {
            return this->descriptionField;
        }

        void msms_pipeline_analysisMsms_run_summarySample_enzyme::setdescription(const std::string &value)
        {
            this->descriptionField = value;
        }

        msms_pipeline_analysisMsms_run_summarySample_enzymeFidelity msms_pipeline_analysisMsms_run_summarySample_enzyme::getfidelity() const
        {
            return this->fidelityField;
        }

        void msms_pipeline_analysisMsms_run_summarySample_enzyme::setfidelity(msms_pipeline_analysisMsms_run_summarySample_enzymeFidelity value)
        {
            this->fidelityField = value;
        }

        bool msms_pipeline_analysisMsms_run_summarySample_enzyme::getindependent() const
        {
            return this->independentField;
        }

        void msms_pipeline_analysisMsms_run_summarySample_enzyme::setindependent(bool value)
        {
            this->independentField = value;
        }
    }
}
