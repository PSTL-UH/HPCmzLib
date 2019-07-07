#include "IO.MzML.Generated.SourceFileType.h"

namespace IO
{
    namespace MzML
    {
        namespace Generated
        {

            std::string SourceFileType::getid() const
            {
                return this->idField;
            }

            void SourceFileType::setid(const std::string &value)
            {
                this->idField = value;
            }

            std::string SourceFileType::getname() const
            {
                return this->nameField;
            }

            void SourceFileType::setname(const std::string &value)
            {
                this->nameField = value;
            }

            std::string SourceFileType::getlocation() const
            {
                return this->locationField;
            }

            void SourceFileType::setlocation(const std::string &value)
            {
                this->locationField = value;
            }
        }
    }
}
