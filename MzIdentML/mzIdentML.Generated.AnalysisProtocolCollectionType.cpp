#include "mzIdentML.Generated.AnalysisProtocolCollectionType.h"
#include "mzIdentML.Generated.SpectrumIdentificationProtocolType.h"
#include "mzIdentML.Generated.ProteinDetectionProtocolType.h"

namespace mzIdentML {
    namespace Generated {

        std::vector<SpectrumIdentificationProtocolType*> AnalysisProtocolCollectionType::getSpectrumIdentificationProtocol() const {
            return this->spectrumIdentificationProtocolField;
        }

        void AnalysisProtocolCollectionType::setSpectrumIdentificationProtocol(const std::vector<SpectrumIdentificationProtocolType*> &value) {
            this->spectrumIdentificationProtocolField = value;
        }

        ProteinDetectionProtocolType *AnalysisProtocolCollectionType::getProteinDetectionProtocol() const {
            return this->proteinDetectionProtocolField;
        }

        void AnalysisProtocolCollectionType::setProteinDetectionProtocol(ProteinDetectionProtocolType *value) {
            this->proteinDetectionProtocolField = value;
        }
    }
}
