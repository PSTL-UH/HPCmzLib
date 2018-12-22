#include "pepXML.Generated.msms_pipeline_analysisAnalysis_summary.h"
#include "pepXML.Generated.nameValueType.h"

namespace pepXML {
    namespace Generated {

        System::Xml::XmlElement *msms_pipeline_analysisAnalysis_summary::getAny() const {
            return this->anyField;
        }

        void msms_pipeline_analysisAnalysis_summary::setAny(System::Xml::XmlElement *value) {
            this->anyField = value;
        }

        std::vector<nameValueType*> msms_pipeline_analysisAnalysis_summary::getparameter() const {
            return this->parameterField;
        }

        void msms_pipeline_analysisAnalysis_summary::setparameter(const std::vector<nameValueType*> &value) {
            this->parameterField = value;
        }

        DateTime msms_pipeline_analysisAnalysis_summary::gettime() const {
            return this->timeField;
        }

        void msms_pipeline_analysisAnalysis_summary::settime(DateTime value) {
            this->timeField = value;
        }

        std::wstring msms_pipeline_analysisAnalysis_summary::getanalysis() const {
            return this->analysisField;
        }

        void msms_pipeline_analysisAnalysis_summary::setanalysis(const std::wstring &value) {
            this->analysisField = value;
        }

        std::wstring msms_pipeline_analysisAnalysis_summary::getversion() const {
            return this->versionField;
        }

        void msms_pipeline_analysisAnalysis_summary::setversion(const std::wstring &value) {
            this->versionField = value;
        }
    }
}
