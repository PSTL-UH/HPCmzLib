#include "IO.MzML.Generated.ChromatogramType.h"
#include "IO.MzML.Generated.PrecursorType.h"
#include "IO.MzML.Generated.ProductType.h"
#include "IO.MzML.Generated.BinaryDataArrayListType.h"

namespace IO
{
    namespace MzML
    {
        namespace Generated
        {

            PrecursorType *ChromatogramType::getprecursor() const
            {
                return this->precursorField;
            }

            void ChromatogramType::setprecursor(PrecursorType *value)
            {
                this->precursorField = value;
            }

            ProductType *ChromatogramType::getproduct() const
            {
                return this->productField;
            }

            void ChromatogramType::setproduct(ProductType *value)
            {
                this->productField = value;
            }

            BinaryDataArrayListType *ChromatogramType::getbinaryDataArrayList() const
            {
                return this->binaryDataArrayListField;
            }

            void ChromatogramType::setbinaryDataArrayList(BinaryDataArrayListType *value)
            {
                this->binaryDataArrayListField = value;
            }

            std::string ChromatogramType::getid() const
            {
                return this->idField;
            }

            void ChromatogramType::setid(const std::string &value)
            {
                this->idField = value;
            }

            std::string ChromatogramType::getindex() const
            {
                return this->indexField;
            }

            void ChromatogramType::setindex(const std::string &value)
            {
                this->indexField = value;
            }

            int ChromatogramType::getdefaultArrayLength() const
            {
                return this->defaultArrayLengthField;
            }

            void ChromatogramType::setdefaultArrayLength(int value)
            {
                this->defaultArrayLengthField = value;
            }

            std::string ChromatogramType::getdataProcessingRef() const
            {
                return this->dataProcessingRefField;
            }

            void ChromatogramType::setdataProcessingRef(const std::string &value)
            {
                this->dataProcessingRefField = value;
            }
        }
    }
}
