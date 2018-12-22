#include "mzIdentML.Generated.TranslationTableType.h"
#include "mzIdentML.Generated.CVParamType.h"

namespace mzIdentML {
    namespace Generated {

        std::vector<CVParamType*> TranslationTableType::getcvParam() const {
            return this->cvParamField;
        }

        void TranslationTableType::setcvParam(const std::vector<CVParamType*> &value) {
            this->cvParamField = value;
        }
    }
}
