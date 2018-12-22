#include "mzIdentML.Generated.SourceFileType.h"
#include "mzIdentML.Generated.CVParamType.h"
#include "mzIdentML.Generated.UserParamType.h"

namespace mzIdentML {
    namespace Generated {

        std::vector<CVParamType*> SourceFileType::getcvParam() const {
            return this->cvParamField;
        }

        void SourceFileType::setcvParam(const std::vector<CVParamType*> &value) {
            this->cvParamField = value;
        }

        std::vector<UserParamType*> SourceFileType::getuserParam() const {
            return this->userParamField;
        }

        void SourceFileType::setuserParam(const std::vector<UserParamType*> &value) {
            this->userParamField = value;
        }
    }
}
