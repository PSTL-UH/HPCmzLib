#include "mzIdentML.Generated.RoleType.h"
#include "mzIdentML.Generated.CVParamType.h"

namespace mzIdentML {
    namespace Generated {

        CVParamType *RoleType::getcvParam() const {
            return this->cvParamField;
        }

        void RoleType::setcvParam(CVParamType *value) {
            this->cvParamField = value;
        }
    }
}
