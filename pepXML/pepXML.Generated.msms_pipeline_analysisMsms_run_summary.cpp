#include "pepXML.Generated.msms_pipeline_analysisMsms_run_summary.h"
#include "pepXML.Generated.msms_pipeline_analysisMsms_run_summarySample_enzyme.h"
#include "pepXML.Generated.msms_pipeline_analysisMsms_run_summaryCross_linker.h"
#include "pepXML.Generated.msms_pipeline_analysisMsms_run_summarySearch_summary.h"
#include "pepXML.Generated.msms_pipeline_analysisMsms_run_summaryAnalysis_timestamp.h"
#include "pepXML.Generated.msms_pipeline_analysisMsms_run_summarySpectrum_query.h"

namespace pepXML
{
    namespace Generated
    {

        msms_pipeline_analysisMsms_run_summarySample_enzyme *msms_pipeline_analysisMsms_run_summary::getsample_enzyme() const
        {
            return this->sample_enzymeField;
        }

        void msms_pipeline_analysisMsms_run_summary::setsample_enzyme(msms_pipeline_analysisMsms_run_summarySample_enzyme *value)
        {
            this->sample_enzymeField = value;
        }

        msms_pipeline_analysisMsms_run_summaryCross_linker *msms_pipeline_analysisMsms_run_summary::getcross_linker() const
        {
            return this->cross_linkerField;
        }

        void msms_pipeline_analysisMsms_run_summary::setcross_linker(msms_pipeline_analysisMsms_run_summaryCross_linker *value)
        {
            this->cross_linkerField = value;
        }

        std::vector<msms_pipeline_analysisMsms_run_summarySearch_summary*> msms_pipeline_analysisMsms_run_summary::getsearch_summary() const
        {
            return this->search_summaryField;
        }

        void msms_pipeline_analysisMsms_run_summary::setsearch_summary(const std::vector<msms_pipeline_analysisMsms_run_summarySearch_summary*> &value)
        {
            this->search_summaryField = value;
        }

        std::vector<msms_pipeline_analysisMsms_run_summaryAnalysis_timestamp*> msms_pipeline_analysisMsms_run_summary::getanalysis_timestamp() const
        {
            return this->analysis_timestampField;
        }

        void msms_pipeline_analysisMsms_run_summary::setanalysis_timestamp(const std::vector<msms_pipeline_analysisMsms_run_summaryAnalysis_timestamp*> &value)
        {
            this->analysis_timestampField = value;
        }

        std::vector<msms_pipeline_analysisMsms_run_summarySpectrum_query*> msms_pipeline_analysisMsms_run_summary::getspectrum_query() const
        {
            return this->spectrum_queryField;
        }

        void msms_pipeline_analysisMsms_run_summary::setspectrum_query(const std::vector<msms_pipeline_analysisMsms_run_summarySpectrum_query*> &value)
        {
            this->spectrum_queryField = value;
        }

        std::string msms_pipeline_analysisMsms_run_summary::getbase_name() const
        {
            return this->base_nameField;
        }

        void msms_pipeline_analysisMsms_run_summary::setbase_name(const std::string &value)
        {
            this->base_nameField = value;
        }

        std::string msms_pipeline_analysisMsms_run_summary::getraw_data_type() const
        {
            return this->raw_data_typeField;
        }

        void msms_pipeline_analysisMsms_run_summary::setraw_data_type(const std::string &value)
        {
            this->raw_data_typeField = value;
        }

        std::string msms_pipeline_analysisMsms_run_summary::getraw_data() const
        {
            return this->raw_dataField;
        }

        void msms_pipeline_analysisMsms_run_summary::setraw_data(const std::string &value)
        {
            this->raw_dataField = value;
        }

        std::string msms_pipeline_analysisMsms_run_summary::getmsManufacturer() const
        {
            return this->msManufacturerField;
        }

        void msms_pipeline_analysisMsms_run_summary::setmsManufacturer(const std::string &value)
        {
            this->msManufacturerField = value;
        }

        std::string msms_pipeline_analysisMsms_run_summary::getmsModel() const
        {
            return this->msModelField;
        }

        void msms_pipeline_analysisMsms_run_summary::setmsModel(const std::string &value)
        {
            this->msModelField = value;
        }

        std::string msms_pipeline_analysisMsms_run_summary::getmsIonization() const
        {
            return this->msIonizationField;
        }

        void msms_pipeline_analysisMsms_run_summary::setmsIonization(const std::string &value)
        {
            this->msIonizationField = value;
        }

        std::string msms_pipeline_analysisMsms_run_summary::getmsMassAnalyzer() const
        {
            return this->msMassAnalyzerField;
        }

        void msms_pipeline_analysisMsms_run_summary::setmsMassAnalyzer(const std::string &value)
        {
            this->msMassAnalyzerField = value;
        }

        std::string msms_pipeline_analysisMsms_run_summary::getmsDetector() const
        {
            return this->msDetectorField;
        }

        void msms_pipeline_analysisMsms_run_summary::setmsDetector(const std::string &value)
        {
            this->msDetectorField = value;
        }
    }
}
