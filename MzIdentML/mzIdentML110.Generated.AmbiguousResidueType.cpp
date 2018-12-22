#include "mzIdentML110.Generated.AmbiguousResidueType.h"
#include "mzIdentML110.Generated.CVParamType.h"
#include "mzIdentML110.Generated.UserParamType.h"

namespace mzIdentML110 {
    namespace Generated {

        std::vector<CVParamType*> AmbiguousResidueType::getcvParam() const {
            return this->cvParamField;
        }

        void AmbiguousResidueType::setcvParam(const std::vector<CVParamType*> &value) {
            this->cvParamField = value;
        }

        std::vector<UserParamType*> AmbiguousResidueType::getuserParam() const {
            return this->userParamField;
        }

        void AmbiguousResidueType::setuserParam(const std::vector<UserParamType*> &value) {
            this->userParamField = value;
        }

        std::wstring AmbiguousResidueType::getcode() const {
            return this->codeField;
        }

        void AmbiguousResidueType::setcode(const std::wstring &value) {
            this->codeField = value;
        }
    }
}
