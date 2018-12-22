#include "pepXML.Generated.msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitAnalysis_result.h"

namespace pepXML {
    namespace Generated {

        msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitAnalysis_result::msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitAnalysis_result() {
            this->idField = (static_cast<unsigned int>(1));
        }

        std::vector<System::Xml::XmlElement*> msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitAnalysis_result::getAny() const {
            return this->anyField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitAnalysis_result::setAny(const std::vector<System::Xml::XmlElement*> &value) {
            this->anyField = value;
        }

        std::wstring msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitAnalysis_result::getanalysis() const {
            return this->analysisField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitAnalysis_result::setanalysis(const std::wstring &value) {
            this->analysisField = value;
        }

        unsigned int msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitAnalysis_result::getid() const {
            return this->idField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitAnalysis_result::setid(unsigned int value) {
            this->idField = value;
        }
    }
}
