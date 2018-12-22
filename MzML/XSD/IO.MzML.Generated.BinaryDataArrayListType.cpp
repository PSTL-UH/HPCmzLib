#include "IO.MzML.Generated.BinaryDataArrayListType.h"
#include "IO.MzML.Generated.BinaryDataArrayType.h"

namespace IO {
    namespace MzML {
        namespace Generated {

            std::vector<BinaryDataArrayType*> BinaryDataArrayListType::getbinaryDataArray() const {
                return this->binaryDataArrayField;
            }

            void BinaryDataArrayListType::setbinaryDataArray(const std::vector<BinaryDataArrayType*> &value) {
                this->binaryDataArrayField = value;
            }

            std::wstring BinaryDataArrayListType::getcount() const {
                return this->countField;
            }

            void BinaryDataArrayListType::setcount(const std::wstring &value) {
                this->countField = value;
            }
        }
    }
}
