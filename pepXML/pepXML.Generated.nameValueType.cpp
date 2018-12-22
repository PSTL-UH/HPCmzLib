#include "pepXML.Generated.nameValueType.h"

namespace pepXML {
    namespace Generated {

        std::wstring nameValueType::getname() const {
            return this->nameField;
        }

        void nameValueType::setname(const std::wstring &value) {
            this->nameField = value;
        }

        std::wstring nameValueType::getvalue() const {
            return this->valueField;
        }

        void nameValueType::setvalue(const std::wstring &value) {
            this->valueField = value;
        }

        std::wstring nameValueType::gettype() const {
            return this->typeField;
        }

        void nameValueType::settype(const std::wstring &value) {
            this->typeField = value;
        }

        std::wstring nameValueType::getValue() const {
            return this->valueField1;
        }

        void nameValueType::setValue(const std::wstring &value) {
            this->valueField1 = value;
        }
    }
}
