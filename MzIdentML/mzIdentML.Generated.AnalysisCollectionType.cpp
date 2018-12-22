#include "mzIdentML.Generated.AnalysisCollectionType.h"
#include "mzIdentML.Generated.SpectrumIdentificationType.h"
#include "mzIdentML.Generated.ProteinDetectionType.h"

namespace mzIdentML {
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
