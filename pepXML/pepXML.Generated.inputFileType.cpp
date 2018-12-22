#include "pepXML.Generated.inputFileType.h"

namespace pepXML {
    namespace Generated {

        std::wstring inputFileType::getname() const {
            return this->nameField;
        }

        void inputFileType::setname(const std::wstring &value) {
            this->nameField = value;
        }

        std::wstring inputFileType::getdirectory() const {
            return this->directoryField;
        }

        void inputFileType::setdirectory(const std::wstring &value) {
            this->directoryField = value;
        }

        std::wstring inputFileType::getValue() const {
            return this->valueField;
        }

        void inputFileType::setValue(const std::wstring &value) {
            this->valueField = value;
        }
    }
}
