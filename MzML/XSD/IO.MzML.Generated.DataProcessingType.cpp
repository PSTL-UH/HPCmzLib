#include "IO.MzML.Generated.DataProcessingType.h"
#include "IO.MzML.Generated.ProcessingMethodType.h"

namespace IO {
    namespace MzML {
        namespace Generated {

            std::vector<ProcessingMethodType*> DataProcessingType::getprocessingMethod() const {
                return this->processingMethodField;
            }

            void DataProcessingType::setprocessingMethod(const std::vector<ProcessingMethodType*> &value) {
                this->processingMethodField = value;
            }

            std::wstring DataProcessingType::getid() const {
                return this->idField;
            }

            void DataProcessingType::setid(const std::wstring &value) {
                this->idField = value;
            }
        }
    }
}
