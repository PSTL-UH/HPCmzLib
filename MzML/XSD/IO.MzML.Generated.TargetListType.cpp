#include "IO.MzML.Generated.TargetListType.h"
#include "IO.MzML.Generated.ParamGroupType.h"

namespace IO
{
    namespace MzML
    {
        namespace Generated
        {

            std::vector<ParamGroupType*> TargetListType::gettarget() const
            {
                return this->targetField;
            }

            void TargetListType::settarget(const std::vector<ParamGroupType*> &value)
            {
                this->targetField = value;
            }

            std::string TargetListType::getcount() const
            {
                return this->countField;
            }

            void TargetListType::setcount(const std::string &value)
            {
                this->countField = value;
            }
        }
    }
}
