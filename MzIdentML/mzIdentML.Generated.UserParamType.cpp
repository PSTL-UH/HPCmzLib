#include "mzIdentML.Generated.UserParamType.h"

namespace mzIdentML {
    namespace Generated {

        std::wstring UserParamType::gettype() const {
            return this->typeField;
        }

        void UserParamType::settype(const std::wstring &value) {
            this->typeField = value;
        }
    }
}
