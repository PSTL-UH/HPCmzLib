#include "mzIdentML.Generated.MeasureType.h"
#include "mzIdentML.Generated.CVParamType.h"

namespace mzIdentML {
    namespace Generated {

        std::vector<CVParamType*> MeasureType::getcvParam() const {
            return this->cvParamField;
        }

        void MeasureType::setcvParam(const std::vector<CVParamType*> &value) {
            this->cvParamField = value;
        }
    }
}
