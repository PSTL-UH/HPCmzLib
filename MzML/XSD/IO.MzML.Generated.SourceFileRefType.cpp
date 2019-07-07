#include "IO.MzML.Generated.SourceFileRefType.h"

namespace IO
{
    namespace MzML
    {
        namespace Generated
        {

            std::string SourceFileRefType::getref() const
            {
                return this->refField;
            }

            void SourceFileRefType::setref(const std::string &value)
            {
                this->refField = value;
            }
        }
    }
}
