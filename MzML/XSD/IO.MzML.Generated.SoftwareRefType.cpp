#include "IO.MzML.Generated.SoftwareRefType.h"

namespace IO
{
    namespace MzML
    {
        namespace Generated
        {

            std::string SoftwareRefType::getref() const
            {
                return this->refField;
            }

            void SoftwareRefType::setref(const std::string &value)
            {
                this->refField = value;
            }
        }
    }
}
