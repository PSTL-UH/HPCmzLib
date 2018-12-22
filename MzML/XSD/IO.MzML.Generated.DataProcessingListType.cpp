#include "IO.MzML.Generated.DataProcessingListType.h"
#include "IO.MzML.Generated.DataProcessingType.h"

namespace IO {
    namespace MzML {
        namespace Generated {

            std::vector<DataProcessingType*> DataProcessingListType::getdataProcessing() const {
                return this->dataProcessingField;
            }

            void DataProcessingListType::setdataProcessing(const std::vector<DataProcessingType*> &value) {
                this->dataProcessingField = value;
            }

            std::wstring DataProcessingListType::getcount() const {
                return this->countField;
            }

            void DataProcessingListType::setcount(const std::wstring &value) {
                this->countField = value;
            }
        }
    }
}
