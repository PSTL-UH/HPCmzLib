#include "IO.MzML.Generated.IndexListType.h"
#include "IO.MzML.Generated.IndexType.h"

namespace IO
{
    namespace MzML
    {
        namespace Generated
        {

            std::vector<IndexType*> IndexListType::getindex() const
            {
                return this->indexField;
            }

            void IndexListType::setindex(const std::vector<IndexType*> &value)
            {
                this->indexField = value;
            }

            std::string IndexListType::getcount() const
            {
                return this->countField;
            }

            void IndexListType::setcount(const std::string &value)
            {
                this->countField = value;
            }
        }
    }
}
