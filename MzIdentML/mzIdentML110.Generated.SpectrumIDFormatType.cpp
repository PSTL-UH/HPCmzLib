#include "mzIdentML110.Generated.SpectrumIDFormatType.h"
#include "mzIdentML110.Generated.CVParamType.h"

namespace mzIdentML110 {
    namespace Generated {

        CVParamType *SpectrumIDFormatType::getcvParam() const {
            return this->cvParamField;
        }

        void SpectrumIDFormatType::setcvParam(CVParamType *value) {
            this->cvParamField = value;
        }
    }
}
