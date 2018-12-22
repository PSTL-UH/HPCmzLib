#include "IO.MzML.Generated.ReferenceableParamGroupRefType.h"

namespace IO {
    namespace MzML {
        namespace Generated {

            std::wstring ReferenceableParamGroupRefType::getref() const {
                return this->refField;
            }

            void ReferenceableParamGroupRefType::setref(const std::wstring &value) {
                this->refField = value;
            }
        }
    }
}
