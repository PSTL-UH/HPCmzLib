#include "mzIdentML110.Generated.AnalysisProtocolCollectionType.h"
#include "mzIdentML110.Generated.SpectrumIdentificationProtocolType.h"
#include "mzIdentML110.Generated.ProteinDetectionProtocolType.h"

namespace mzIdentML110 {
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
