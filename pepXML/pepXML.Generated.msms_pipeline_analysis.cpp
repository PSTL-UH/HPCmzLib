#include "pepXML.Generated.msms_pipeline_analysis.h"
#include "pepXML.Generated.msms_pipeline_analysisAnalysis_summary.h"
#include "pepXML.Generated.msms_pipeline_analysisDataset_derivation.h"
#include "pepXML.Generated.msms_pipeline_analysisMsms_run_summary.h"

namespace pepXML
{
    namespace Generated
    {

        std::vector<msms_pipeline_analysisAnalysis_summary*> msms_pipeline_analysis::getanalysis_summary() const
        {
            return this->analysis_summaryField;
        }

        void msms_pipeline_analysis::setanalysis_summary(const std::vector<msms_pipeline_analysisAnalysis_summary*> &value)
        {
            this->analysis_summaryField = value;
        }

        std::vector<msms_pipeline_analysisDataset_derivation*> msms_pipeline_analysis::getdataset_derivation() const
        {
            return this->dataset_derivationField;
        }

        void msms_pipeline_analysis::setdataset_derivation(const std::vector<msms_pipeline_analysisDataset_derivation*> &value)
        {
            this->dataset_derivationField = value;
        }

        std::vector<msms_pipeline_analysisMsms_run_summary*> msms_pipeline_analysis::getmsms_run_summary() const
        {
            return this->msms_run_summaryField;
        }

        void msms_pipeline_analysis::setmsms_run_summary(const std::vector<msms_pipeline_analysisMsms_run_summary*> &value)
        {
            this->msms_run_summaryField = value;
        }

        std::string msms_pipeline_analysis::getname() const
        {
            return this->nameField;
        }

        void msms_pipeline_analysis::setname(const std::string &value)
        {
            this->nameField = value;
        }

        DateTime msms_pipeline_analysis::getdate() const
        {
            return this->dateField;
        }

        void msms_pipeline_analysis::setdate(DateTime value)
        {
            this->dateField = value;
        }

        std::string msms_pipeline_analysis::getsummary_xml() const
        {
            return this->summary_xmlField;
        }

        void msms_pipeline_analysis::setsummary_xml(const std::string &value)
        {
            this->summary_xmlField = value;
        }
    }
}
