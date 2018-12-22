#include "IO.MzML.Generated.ReferenceableParamGroupType.h"
#include "IO.MzML.Generated.CVParamType.h"
#include "IO.MzML.Generated.UserParamType.h"

namespace IO {
    namespace MzML {
        namespace Generated {

            std::vector<CVParamType*> ReferenceableParamGroupType::getcvParam() const {
                return this->cvParamField;
            }

            void ReferenceableParamGroupType::setcvParam(const std::vector<CVParamType*> &value) {
                this->cvParamField = value;
            }

            std::vector<UserParamType*> ReferenceableParamGroupType::getuserParam() const {
                return this->userParamField;
            }

            void ReferenceableParamGroupType::setuserParam(const std::vector<UserParamType*> &value) {
                this->userParamField = value;
            }

            std::wstring ReferenceableParamGroupType::getid() const {
                return this->idField;
            }

            void ReferenceableParamGroupType::setid(const std::wstring &value) {
                this->idField = value;
            }
        }
    }
}
