#include "mzIdentML.Generated.AbstractParamType.h"

namespace mzIdentML {
    namespace Generated {

        std::wstring AbstractParamType::getname() const {
            return this->nameField;
        }

        void AbstractParamType::setname(const std::wstring &value) {
            this->nameField = value;
        }

        std::wstring AbstractParamType::getvalue() const {
            return this->valueField;
        }

        void AbstractParamType::setvalue(const std::wstring &value) {
            this->valueField = value;
        }

        std::wstring AbstractParamType::getunitAccession() const {
            return this->unitAccessionField;
        }

        void AbstractParamType::setunitAccession(const std::wstring &value) {
            this->unitAccessionField = value;
        }

        std::wstring AbstractParamType::getunitName() const {
            return this->unitNameField;
        }

        void AbstractParamType::setunitName(const std::wstring &value) {
            this->unitNameField = value;
        }

        std::wstring AbstractParamType::getunitCvRef() const {
            return this->unitCvRefField;
        }

        void AbstractParamType::setunitCvRef(const std::wstring &value) {
            this->unitCvRefField = value;
        }
    }
}
