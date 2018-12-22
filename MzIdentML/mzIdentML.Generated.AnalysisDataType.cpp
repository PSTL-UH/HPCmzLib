#include "mzIdentML.Generated.AnalysisDataType.h"
#include "mzIdentML.Generated.SpectrumIdentificationListType.h"
#include "mzIdentML.Generated.ProteinDetectionListType.h"

namespace mzIdentML {
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
