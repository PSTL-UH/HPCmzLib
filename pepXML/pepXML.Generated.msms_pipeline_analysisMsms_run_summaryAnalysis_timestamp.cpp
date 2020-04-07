#include "pepXML.Generated.msms_pipeline_analysisMsms_run_summaryAnalysis_timestamp.h"

namespace pepXML
{
    namespace Generated
    {

        System::Xml::XmlElement *msms_pipeline_analysisMsms_run_summaryAnalysis_timestamp::getAny() const
        {
            return this->anyField;
        }

        void msms_pipeline_analysisMsms_run_summaryAnalysis_timestamp::setAny(System::Xml::XmlElement *value)
        {
            this->anyField = value;
        }

        DateTime msms_pipeline_analysisMsms_run_summaryAnalysis_timestamp::gettime() const
        {
            return this->timeField;
        }

        void msms_pipeline_analysisMsms_run_summaryAnalysis_timestamp::settime(DateTime value)
        {
            this->timeField = value;
        }

        std::string msms_pipeline_analysisMsms_run_summaryAnalysis_timestamp::getanalysis() const
        {
            return this->analysisField;
        }

        void msms_pipeline_analysisMsms_run_summaryAnalysis_timestamp::setanalysis(const std::string &value)
        {
            this->analysisField = value;
        }

        unsigned int msms_pipeline_analysisMsms_run_summaryAnalysis_timestamp::getid() const
        {
            return this->idField;
        }

        void msms_pipeline_analysisMsms_run_summaryAnalysis_timestamp::setid(unsigned int value)
        {
            this->idField = value;
        }
    }
}
