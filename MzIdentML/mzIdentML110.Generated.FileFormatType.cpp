#include "mzIdentML110.Generated.FileFormatType.h"
#include "mzIdentML110.Generated.CVParamType.h"

namespace mzIdentML110 {
    namespace Generated {

        CVParamType *FileFormatType::getcvParam() const {
            return this->cvParamField;
        }

        void FileFormatType::setcvParam(CVParamType *value) {
            this->cvParamField = value;
        }
    }
}
