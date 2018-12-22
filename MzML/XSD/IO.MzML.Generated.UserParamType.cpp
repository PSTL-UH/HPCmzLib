#include "IO.MzML.Generated.UserParamType.h"

namespace IO {
    namespace MzML {
        namespace Generated {

            std::wstring UserParamType::getname() const {
                return this->nameField;
            }

            void UserParamType::setname(const std::wstring &value) {
                this->nameField = value;
            }

            std::wstring UserParamType::gettype() const {
                return this->typeField;
            }

            void UserParamType::settype(const std::wstring &value) {
                this->typeField = value;
            }

            std::wstring UserParamType::getvalue() const {
                return this->valueField;
            }

            void UserParamType::setvalue(const std::wstring &value) {
                this->valueField = value;
            }

            std::wstring UserParamType::getunitAccession() const {
                return this->unitAccessionField;
            }

            void UserParamType::setunitAccession(const std::wstring &value) {
                this->unitAccessionField = value;
            }

            std::wstring UserParamType::getunitName() const {
                return this->unitNameField;
            }

            void UserParamType::setunitName(const std::wstring &value) {
                this->unitNameField = value;
            }

            std::wstring UserParamType::getunitCvRef() const {
                return this->unitCvRefField;
            }

            void UserParamType::setunitCvRef(const std::wstring &value) {
                this->unitCvRefField = value;
            }
        }
    }
}
