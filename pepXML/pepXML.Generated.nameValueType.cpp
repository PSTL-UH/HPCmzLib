#include "pepXML.Generated.nameValueType.h"

namespace pepXML
{
    namespace Generated
    {

        std::string nameValueType::getname() const
        {
            return this->nameField;
        }

        void nameValueType::setname(const std::string &value)
        {
            this->nameField = value;
        }

        std::string nameValueType::getvalue() const
        {
            return this->valueField;
        }

        void nameValueType::setvalue(const std::string &value)
        {
            this->valueField = value;
        }

        std::string nameValueType::gettype() const
        {
            return this->typeField;
        }

        void nameValueType::settype(const std::string &value)
        {
            this->typeField = value;
        }

        std::string nameValueType::getValue() const
        {
            return this->valueField1;
        }

        void nameValueType::setValue(const std::string &value)
        {
            this->valueField1 = value;
        }
    }
}
