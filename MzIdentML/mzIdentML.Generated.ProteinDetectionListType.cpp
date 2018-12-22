#include "mzIdentML.Generated.ProteinDetectionListType.h"
#include "mzIdentML.Generated.ProteinAmbiguityGroupType.h"
#include "mzIdentML.Generated.CVParamType.h"
#include "mzIdentML.Generated.UserParamType.h"

namespace mzIdentML {
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
