#include "mzIdentML110.Generated.TranslationTableType.h"
#include "mzIdentML110.Generated.CVParamType.h"

namespace mzIdentML110 {
    namespace Generated {

        std::vector<CVParamType*> TranslationTableType::getcvParam() const {
            return this->cvParamField;
        }

        void TranslationTableType::setcvParam(const std::vector<CVParamType*> &value) {
            this->cvParamField = value;
        }
    }
}
