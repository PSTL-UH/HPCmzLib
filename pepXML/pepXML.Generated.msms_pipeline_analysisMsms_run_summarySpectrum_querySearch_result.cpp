#include "pepXML.Generated.msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_result.h"
#include "pepXML.Generated.msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit.h"

namespace pepXML
{
    namespace Generated
    {

        msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_result::msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_result()
        {
            this->search_idField = (static_cast<unsigned int>(1));
        }

        std::vector<msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit*> msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_result::getsearch_hit() const
        {
            return this->search_hitField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_result::setsearch_hit(const std::vector<msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hit*> &value)
        {
            this->search_hitField = value;
        }

        unsigned int msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_result::getsearch_id() const
        {
            return this->search_idField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_result::setsearch_id(unsigned int value)
        {
            this->search_idField = value;
        }
    }
}
