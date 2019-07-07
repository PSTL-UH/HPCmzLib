#include "IO.MzML.Generated.CVType.h"

namespace IO
{
    namespace MzML
    {
        namespace Generated
        {

            std::string CVType::getid() const
            {
                return this->idField;
            }

            void CVType::setid(const std::string &value)
            {
                this->idField = value;
            }

            std::string CVType::getfullName() const
            {
                return this->fullNameField;
            }

            void CVType::setfullName(const std::string &value)
            {
                this->fullNameField = value;
            }

            std::string CVType::getversion() const
            {
                return this->versionField;
            }

            void CVType::setversion(const std::string &value)
            {
                this->versionField = value;
            }

            std::string CVType::getURI() const
            {
                return this->uRIField;
            }

            void CVType::setURI(const std::string &value)
            {
                this->uRIField = value;
            }
        }
    }
}
