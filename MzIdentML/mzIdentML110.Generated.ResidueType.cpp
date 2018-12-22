#include "mzIdentML110.Generated.ResidueType.h"

namespace mzIdentML110 {
    namespace Generated {

        std::wstring ResidueType::getcode() const {
            return this->codeField;
        }

        void ResidueType::setcode(const std::wstring &value) {
            this->codeField = value;
        }

        float ResidueType::getmass() const {
            return this->massField;
        }

        void ResidueType::setmass(float value) {
            this->massField = value;
        }
    }
}
