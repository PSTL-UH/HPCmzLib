#include "pepXML.Generated.msms_pipeline_analysisMsms_run_summarySample_enzymeSpecificity.h"

namespace pepXML
{
    namespace Generated
    {

        msms_pipeline_analysisMsms_run_summarySample_enzymeSpecificity::msms_pipeline_analysisMsms_run_summarySample_enzymeSpecificity()
        {
            this->min_spacingField = "1";
        }

        msms_pipeline_analysisMsms_run_summarySample_enzymeSpecificitySense msms_pipeline_analysisMsms_run_summarySample_enzymeSpecificity::getsense() const
        {
            return this->senseField;
        }

        void msms_pipeline_analysisMsms_run_summarySample_enzymeSpecificity::setsense(msms_pipeline_analysisMsms_run_summarySample_enzymeSpecificitySense value)
        {
            this->senseField = value;
        }

        std::string msms_pipeline_analysisMsms_run_summarySample_enzymeSpecificity::getmin_spacing() const
        {
            return this->min_spacingField;
        }

        void msms_pipeline_analysisMsms_run_summarySample_enzymeSpecificity::setmin_spacing(const std::string &value)
        {
            this->min_spacingField = value;
        }

        std::string msms_pipeline_analysisMsms_run_summarySample_enzymeSpecificity::getcut() const
        {
            return this->cutField;
        }

        void msms_pipeline_analysisMsms_run_summarySample_enzymeSpecificity::setcut(const std::string &value)
        {
            this->cutField = value;
        }

        std::string msms_pipeline_analysisMsms_run_summarySample_enzymeSpecificity::getno_cut() const
        {
            return this->no_cutField;
        }

        void msms_pipeline_analysisMsms_run_summarySample_enzymeSpecificity::setno_cut(const std::string &value)
        {
            this->no_cutField = value;
        }
    }
}
