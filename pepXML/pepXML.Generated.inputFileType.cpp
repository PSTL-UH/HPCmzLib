#include "pepXML.Generated.inputFileType.h"

namespace pepXML
{
    namespace Generated
    {

        std::string inputFileType::getname() const
        {
            return this->nameField;
        }

        void inputFileType::setname(const std::string &value)
        {
            this->nameField = value;
        }

        std::string inputFileType::getdirectory() const
        {
            return this->directoryField;
        }

        void inputFileType::setdirectory(const std::string &value)
        {
            this->directoryField = value;
        }

        std::string inputFileType::getValue() const
        {
            return this->valueField;
        }

        void inputFileType::setValue(const std::string &value)
        {
            this->valueField = value;
        }
    }
}
