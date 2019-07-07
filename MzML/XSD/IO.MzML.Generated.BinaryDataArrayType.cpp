#include "IO.MzML.Generated.BinaryDataArrayType.h"

namespace IO
{
    namespace MzML
    {
        namespace Generated
        {

            std::vector<unsigned char> BinaryDataArrayType::getbinary() const
            {
                return this->binaryField;
            }

            void BinaryDataArrayType::setbinary(const std::vector<unsigned char> &value)
            {
                this->binaryField = value;
            }

            std::string BinaryDataArrayType::getarrayLength() const
            {
                return this->arrayLengthField;
            }

            void BinaryDataArrayType::setarrayLength(const std::string &value)
            {
                this->arrayLengthField = value;
            }

            std::string BinaryDataArrayType::getdataProcessingRef() const
            {
                return this->dataProcessingRefField;
            }

            void BinaryDataArrayType::setdataProcessingRef(const std::string &value)
            {
                this->dataProcessingRefField = value;
            }

            std::string BinaryDataArrayType::getencodedLength() const
            {
                return this->encodedLengthField;
            }

            void BinaryDataArrayType::setencodedLength(const std::string &value)
            {
                this->encodedLengthField = value;
            }
        }
    }
}
