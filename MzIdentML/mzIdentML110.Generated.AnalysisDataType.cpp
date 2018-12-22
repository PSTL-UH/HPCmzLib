#include "mzIdentML110.Generated.AnalysisDataType.h"
#include "mzIdentML110.Generated.SpectrumIdentificationListType.h"
#include "mzIdentML110.Generated.ProteinDetectionListType.h"

namespace mzIdentML110 {
    namespace Generated {

        std::vector<SpectrumIdentificationListType*> AnalysisDataType::getSpectrumIdentificationList() const {
            return this->spectrumIdentificationListField;
        }

        void AnalysisDataType::setSpectrumIdentificationList(const std::vector<SpectrumIdentificationListType*> &value) {
            this->spectrumIdentificationListField = value;
        }

        ProteinDetectionListType *AnalysisDataType::getProteinDetectionList() const {
            return this->proteinDetectionListField;
        }

        void AnalysisDataType::setProteinDetectionList(ProteinDetectionListType *value) {
            this->proteinDetectionListField = value;
        }
    }
}
