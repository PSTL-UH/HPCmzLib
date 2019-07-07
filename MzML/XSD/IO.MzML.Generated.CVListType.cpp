#include "IO.MzML.Generated.CVListType.h"
#include "IO.MzML.Generated.CVType.h"

namespace IO
{
    namespace MzML
    {
        namespace Generated
        {

            std::vector<CVType*> CVListType::getcv() const
            {
                return this->cvField;
            }

            void CVListType::setcv(const std::vector<CVType*> &value)
            {
                this->cvField = value;
            }

            std::string CVListType::getcount() const
            {
                return this->countField;
            }

            void CVListType::setcount(const std::string &value)
            {
                this->countField = value;
            }
        }
    }
}
