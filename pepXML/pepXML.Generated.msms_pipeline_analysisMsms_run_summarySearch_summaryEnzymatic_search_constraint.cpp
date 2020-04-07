#include "pepXML.Generated.msms_pipeline_analysisMsms_run_summarySearch_summaryEnzymatic_search_constraint.h"

namespace pepXML
{
    namespace Generated
    {

        std::string msms_pipeline_analysisMsms_run_summarySearch_summaryEnzymatic_search_constraint::getenzyme() const
        {
            return this->enzymeField;
        }

        void msms_pipeline_analysisMsms_run_summarySearch_summaryEnzymatic_search_constraint::setenzyme(const std::string &value)
        {
            this->enzymeField = value;
        }

        std::string msms_pipeline_analysisMsms_run_summarySearch_summaryEnzymatic_search_constraint::getmax_num_internal_cleavages() const
        {
            return this->max_num_internal_cleavagesField;
        }

        void msms_pipeline_analysisMsms_run_summarySearch_summaryEnzymatic_search_constraint::setmax_num_internal_cleavages(const std::string &value)
        {
            this->max_num_internal_cleavagesField = value;
        }

        std::string msms_pipeline_analysisMsms_run_summarySearch_summaryEnzymatic_search_constraint::getmin_number_termini() const
        {
            return this->min_number_terminiField;
        }

        void msms_pipeline_analysisMsms_run_summarySearch_summaryEnzymatic_search_constraint::setmin_number_termini(const std::string &value)
        {
            this->min_number_terminiField = value;
        }
    }
}
