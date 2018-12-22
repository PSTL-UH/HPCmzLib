#include "mzIdentML.Generated.ProteinDetectionProtocolType.h"
#include "mzIdentML.Generated.ParamListType.h"

namespace mzIdentML {
    namespace Generated {

        ParamListType *ProteinDetectionProtocolType::getAnalysisParams() const {
            return this->analysisParamsField;
        }

        void ProteinDetectionProtocolType::setAnalysisParams(ParamListType *value) {
            this->analysisParamsField = value;
        }

        ParamListType *ProteinDetectionProtocolType::getThreshold() const {
            return this->thresholdField;
        }

        void ProteinDetectionProtocolType::setThreshold(ParamListType *value) {
            this->thresholdField = value;
        }

        std::wstring ProteinDetectionProtocolType::getanalysisSoftware_ref() const {
            return this->analysisSoftware_refField;
        }

        void ProteinDetectionProtocolType::setanalysisSoftware_ref(const std::wstring &value) {
            this->analysisSoftware_refField = value;
        }
    }
}
