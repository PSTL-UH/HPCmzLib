#include "mzIdentML.Generated.FileFormatType.h"
#include "mzIdentML.Generated.CVParamType.h"

namespace mzIdentML {
    namespace Generated {

        CVParamType *FileFormatType::getcvParam() const {
            return this->cvParamField;
        }

        void FileFormatType::setcvParam(CVParamType *value) {
            this->cvParamField = value;
        }
    }
}
