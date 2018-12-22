#include "pepXML.Generated.msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlink.h"
#include "pepXML.Generated.msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlinkLinked_peptide.h"
#include "pepXML.Generated.nameValueType.h"

namespace pepXML {
    namespace Generated {

        std::vector<msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlinkLinked_peptide*> msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlink::getlinked_peptide() const {
            return this->linked_peptideField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlink::setlinked_peptide(const std::vector<msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlinkLinked_peptide*> &value) {
            this->linked_peptideField = value;
        }

        std::vector<nameValueType*> msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlink::getxlink_score() const {
            return this->xlink_scoreField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlink::setxlink_score(const std::vector<nameValueType*> &value) {
            this->xlink_scoreField = value;
        }

        std::wstring msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlink::getidentifier() const {
            return this->identifierField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlink::setidentifier(const std::wstring &value) {
            this->identifierField = value;
        }

        float msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlink::getmass() const {
            return this->massField;
        }

        void msms_pipeline_analysisMsms_run_summarySpectrum_querySearch_resultSearch_hitXlink::setmass(float value) {
            this->massField = value;
        }
    }
}
