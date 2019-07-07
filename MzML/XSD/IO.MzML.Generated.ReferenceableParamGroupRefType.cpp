#include "IO.MzML.Generated.ReferenceableParamGroupRefType.h"

namespace IO
{
    namespace MzML
    {
        namespace Generated
        {

            std::string ReferenceableParamGroupRefType::getref() const
            {
                return this->refField;
            }

            void ReferenceableParamGroupRefType::setref(const std::string &value)
            {
                this->refField = value;
            }
        }
    }
}
