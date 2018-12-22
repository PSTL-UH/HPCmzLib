#include "mzIdentML110.Generated.PeptideHypothesisType.h"
#include "mzIdentML110.Generated.SpectrumIdentificationItemRefType.h"

namespace mzIdentML110 {
    namespace Generated {

        std::vector<SpectrumIdentificationItemRefType*> PeptideHypothesisType::getSpectrumIdentificationItemRef() const {
            return this->spectrumIdentificationItemRefField;
        }

        void PeptideHypothesisType::setSpectrumIdentificationItemRef(const std::vector<SpectrumIdentificationItemRefType*> &value) {
            this->spectrumIdentificationItemRefField = value;
        }

        std::wstring PeptideHypothesisType::getpeptideEvidence_ref() const {
            return this->peptideEvidence_refField;
        }

        void PeptideHypothesisType::setpeptideEvidence_ref(const std::wstring &value) {
            this->peptideEvidence_refField = value;
        }
    }
}
