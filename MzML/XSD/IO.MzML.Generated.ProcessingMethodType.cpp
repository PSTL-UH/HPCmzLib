#include "IO.MzML.Generated.ProcessingMethodType.h"

namespace IO
{
    namespace MzML
    {
        namespace Generated
        {

            std::string ProcessingMethodType::getorder() const
            {
                return this->orderField;
            }

            void ProcessingMethodType::setorder(const std::string &value)
            {
                this->orderField = value;
            }

            std::string ProcessingMethodType::getsoftwareRef() const
            {
                return this->softwareRefField;
            }

            void ProcessingMethodType::setsoftwareRef(const std::string &value)
            {
                this->softwareRefField = value;
            }
        }
    }
}
