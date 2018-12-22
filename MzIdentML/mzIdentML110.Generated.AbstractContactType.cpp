#include "mzIdentML110.Generated.AbstractContactType.h"
#include "mzIdentML110.Generated.CVParamType.h"
#include "mzIdentML110.Generated.UserParamType.h"

namespace mzIdentML110 {
    namespace Generated {

        std::vector<CVParamType*> AbstractContactType::getcvParam() const {
            return this->cvParamField;
        }

        void AbstractContactType::setcvParam(const std::vector<CVParamType*> &value) {
            this->cvParamField = value;
        }

        std::vector<UserParamType*> AbstractContactType::getuserParam() const {
            return this->userParamField;
        }

        void AbstractContactType::setuserParam(const std::vector<UserParamType*> &value) {
            this->userParamField = value;
        }
    }
}
