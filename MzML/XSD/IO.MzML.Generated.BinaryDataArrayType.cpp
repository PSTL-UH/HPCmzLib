#include "IO.MzML.Generated.BinaryDataArrayType.h"

namespace IO {
    namespace MzML {
        namespace Generated {

            std::vector<unsigned char> BinaryDataArrayType::getbinary() const {
                return this->binaryField;
            }

            void BinaryDataArrayType::setbinary(const std::vector<unsigned char> &value) {
                this->binaryField = value;
            }

            std::wstring BinaryDataArrayType::getarrayLength() const {
                return this->arrayLengthField;
            }

            void BinaryDataArrayType::setarrayLength(const std::wstring &value) {
                this->arrayLengthField = value;
            }

            std::wstring BinaryDataArrayType::getdataProcessingRef() const {
                return this->dataProcessingRefField;
            }

            void BinaryDataArrayType::setdataProcessingRef(const std::wstring &value) {
                this->dataProcessingRefField = value;
            }

            std::wstring BinaryDataArrayType::getencodedLength() const {
                return this->encodedLengthField;
            }

            void BinaryDataArrayType::setencodedLength(const std::wstring &value) {
                this->encodedLengthField = value;
            }
        }
    }
}
