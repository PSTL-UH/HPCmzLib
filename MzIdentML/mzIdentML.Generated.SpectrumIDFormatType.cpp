#include "mzIdentML.Generated.SpectrumIDFormatType.h"
#include "mzIdentML.Generated.CVParamType.h"

namespace mzIdentML {
    namespace Generated {

        CVParamType *SpectrumIDFormatType::getcvParam() const {
            return this->cvParamField;
        }

        void SpectrumIDFormatType::setcvParam(CVParamType *value) {
            this->cvParamField = value;
        }
    }
}
