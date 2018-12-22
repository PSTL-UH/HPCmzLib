#include "mzIdentML110.Generated.MeasureType.h"
#include "mzIdentML110.Generated.CVParamType.h"

namespace mzIdentML110 {
    namespace Generated {

        std::vector<CVParamType*> MeasureType::getcvParam() const {
            return this->cvParamField;
        }

        void MeasureType::setcvParam(const std::vector<CVParamType*> &value) {
            this->cvParamField = value;
        }
    }
}
