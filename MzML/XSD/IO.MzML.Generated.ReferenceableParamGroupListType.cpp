#include "IO.MzML.Generated.ReferenceableParamGroupListType.h"
#include "IO.MzML.Generated.ReferenceableParamGroupType.h"

namespace IO {
    namespace MzML {
        namespace Generated {

            std::vector<ReferenceableParamGroupType*> ReferenceableParamGroupListType::getreferenceableParamGroup() const {
                return this->referenceableParamGroupField;
            }

            void ReferenceableParamGroupListType::setreferenceableParamGroup(const std::vector<ReferenceableParamGroupType*> &value) {
                this->referenceableParamGroupField = value;
            }

            std::wstring ReferenceableParamGroupListType::getcount() const {
                return this->countField;
            }

            void ReferenceableParamGroupListType::setcount(const std::wstring &value) {
                this->countField = value;
            }
        }
    }
}
