#include "mzIdentML110.Generated.ExternalDataType.h"
#include "mzIdentML110.Generated.FileFormatType.h"

namespace mzIdentML110 {
    namespace Generated {

        std::wstring ExternalDataType::getExternalFormatDocumentation() const {
            return this->externalFormatDocumentationField;
        }

        void ExternalDataType::setExternalFormatDocumentation(const std::wstring &value) {
            this->externalFormatDocumentationField = value;
        }

        FileFormatType *ExternalDataType::getFileFormat() const {
            return this->fileFormatField;
        }

        void ExternalDataType::setFileFormat(FileFormatType *value) {
            this->fileFormatField = value;
        }

        std::wstring ExternalDataType::getlocation() const {
            return this->locationField;
        }

        void ExternalDataType::setlocation(const std::wstring &value) {
            this->locationField = value;
        }
    }
}
