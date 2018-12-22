#include "mzIdentML110.Generated.AnalysisCollectionType.h"
#include "mzIdentML110.Generated.SpectrumIdentificationType.h"
#include "mzIdentML110.Generated.ProteinDetectionType.h"

namespace mzIdentML110 {
    namespace Generated {

        std::vector<SpectrumIdentificationType*> AnalysisCollectionType::getSpectrumIdentification() const {
            return this->spectrumIdentificationField;
        }

        void AnalysisCollectionType::setSpectrumIdentification(const std::vector<SpectrumIdentificationType*> &value) {
            this->spectrumIdentificationField = value;
        }

        ProteinDetectionType *AnalysisCollectionType::getProteinDetection() const {
            return this->proteinDetectionField;
        }

        void AnalysisCollectionType::setProteinDetection(ProteinDetectionType *value) {
            this->proteinDetectionField = value;
        }
    }
}
