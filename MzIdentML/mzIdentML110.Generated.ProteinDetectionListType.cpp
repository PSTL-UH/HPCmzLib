#include "mzIdentML110.Generated.ProteinDetectionListType.h"
#include "mzIdentML110.Generated.ProteinAmbiguityGroupType.h"
#include "mzIdentML110.Generated.CVParamType.h"
#include "mzIdentML110.Generated.UserParamType.h"

namespace mzIdentML110 {
    namespace Generated {

        std::vector<ProteinAmbiguityGroupType*> ProteinDetectionListType::getProteinAmbiguityGroup() const {
            return this->proteinAmbiguityGroupField;
        }

        void ProteinDetectionListType::setProteinAmbiguityGroup(const std::vector<ProteinAmbiguityGroupType*> &value) {
            this->proteinAmbiguityGroupField = value;
        }

        std::vector<CVParamType*> ProteinDetectionListType::getcvParam() const {
            return this->cvParamField;
        }

        void ProteinDetectionListType::setcvParam(const std::vector<CVParamType*> &value) {
            this->cvParamField = value;
        }

        std::vector<UserParamType*> ProteinDetectionListType::getuserParam() const {
            return this->userParamField;
        }

        void ProteinDetectionListType::setuserParam(const std::vector<UserParamType*> &value) {
            this->userParamField = value;
        }
    }
}
