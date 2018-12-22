#include "mzIdentML110.Generated.ProteinAmbiguityGroupType.h"
#include "mzIdentML110.Generated.ProteinDetectionHypothesisType.h"
#include "mzIdentML110.Generated.CVParamType.h"
#include "mzIdentML110.Generated.UserParamType.h"

namespace mzIdentML110 {
    namespace Generated {

        std::vector<ProteinDetectionHypothesisType*> ProteinAmbiguityGroupType::getProteinDetectionHypothesis() const {
            return this->proteinDetectionHypothesisField;
        }

        void ProteinAmbiguityGroupType::setProteinDetectionHypothesis(const std::vector<ProteinDetectionHypothesisType*> &value) {
            this->proteinDetectionHypothesisField = value;
        }

        std::vector<CVParamType*> ProteinAmbiguityGroupType::getcvParam() const {
            return this->cvParamField;
        }

        void ProteinAmbiguityGroupType::setcvParam(const std::vector<CVParamType*> &value) {
            this->cvParamField = value;
        }

        std::vector<UserParamType*> ProteinAmbiguityGroupType::getuserParam() const {
            return this->userParamField;
        }

        void ProteinAmbiguityGroupType::setuserParam(const std::vector<UserParamType*> &value) {
            this->userParamField = value;
        }
    }
}
