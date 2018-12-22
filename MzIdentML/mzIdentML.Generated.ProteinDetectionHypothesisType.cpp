#include "mzIdentML.Generated.ProteinDetectionHypothesisType.h"
#include "mzIdentML.Generated.PeptideHypothesisType.h"
#include "mzIdentML.Generated.CVParamType.h"
#include "mzIdentML.Generated.UserParamType.h"

namespace mzIdentML {
    namespace Generated {

        std::vector<PeptideHypothesisType*> ProteinDetectionHypothesisType::getPeptideHypothesis() const {
            return this->peptideHypothesisField;
        }

        void ProteinDetectionHypothesisType::setPeptideHypothesis(const std::vector<PeptideHypothesisType*> &value) {
            this->peptideHypothesisField = value;
        }

        std::vector<CVParamType*> ProteinDetectionHypothesisType::getcvParam() const {
            return this->cvParamField;
        }

        void ProteinDetectionHypothesisType::setcvParam(const std::vector<CVParamType*> &value) {
            this->cvParamField = value;
        }

        std::vector<UserParamType*> ProteinDetectionHypothesisType::getuserParam() const {
            return this->userParamField;
        }

        void ProteinDetectionHypothesisType::setuserParam(const std::vector<UserParamType*> &value) {
            this->userParamField = value;
        }

        std::wstring ProteinDetectionHypothesisType::getdBSequence_ref() const {
            return this->dBSequence_refField;
        }

        void ProteinDetectionHypothesisType::setdBSequence_ref(const std::wstring &value) {
            this->dBSequence_refField = value;
        }

        bool ProteinDetectionHypothesisType::getpassThreshold() const {
            return this->passThresholdField;
        }

        void ProteinDetectionHypothesisType::setpassThreshold(bool value) {
            this->passThresholdField = value;
        }
    }
}
