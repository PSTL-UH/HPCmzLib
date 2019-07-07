#include "IO.MzML.Generated.DataProcessingListType.h"
#include "IO.MzML.Generated.DataProcessingType.h"

namespace IO
{
    namespace MzML
    {
        namespace Generated
        {

            std::vector<DataProcessingType*> DataProcessingListType::getdataProcessing() const
            {
                return this->dataProcessingField;
            }

            void DataProcessingListType::setdataProcessing(const std::vector<DataProcessingType*> &value)
            {
                this->dataProcessingField = value;
            }

            std::string DataProcessingListType::getcount() const
            {
                return this->countField;
            }

            void DataProcessingListType::setcount(const std::string &value)
            {
                this->countField = value;
            }
        }
    }
}
