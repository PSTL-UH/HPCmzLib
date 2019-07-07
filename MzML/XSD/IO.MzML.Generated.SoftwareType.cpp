#include "IO.MzML.Generated.SoftwareType.h"

namespace IO
{
    namespace MzML
    {
        namespace Generated
        {

            std::string SoftwareType::getid() const
            {
                return this->idField;
            }

            void SoftwareType::setid(const std::string &value)
            {
                this->idField = value;
            }

            std::string SoftwareType::getversion() const
            {
                return this->versionField;
            }

            void SoftwareType::setversion(const std::string &value)
            {
                this->versionField = value;
            }
        }
    }
}
