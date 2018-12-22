#include "mzIdentML.Generated.ExternalDataType.h"
#include "mzIdentML.Generated.FileFormatType.h"

namespace mzIdentML {
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
