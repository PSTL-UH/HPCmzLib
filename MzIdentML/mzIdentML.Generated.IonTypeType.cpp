#include "mzIdentML.Generated.IonTypeType.h"
#include "mzIdentML.Generated.FragmentArrayType.h"
#include "mzIdentML.Generated.CVParamType.h"

namespace mzIdentML {
    namespace Generated {

        std::vector<FragmentArrayType*> IonTypeType::getFragmentArray() const {
            return this->fragmentArrayField;
        }

        void IonTypeType::setFragmentArray(const std::vector<FragmentArrayType*> &value) {
            this->fragmentArrayField = value;
        }

        CVParamType *IonTypeType::getcvParam() const {
            return this->cvParamField;
        }

        void IonTypeType::setcvParam(CVParamType *value) {
            this->cvParamField = value;
        }

        std::vector<std::wstring> IonTypeType::getindex() const {
            return this->indexField;
        }

        void IonTypeType::setindex(const std::vector<std::wstring> &value) {
            this->indexField = value;
        }

        int IonTypeType::getcharge() const {
            return this->chargeField;
        }

        void IonTypeType::setcharge(int value) {
            this->chargeField = value;
        }
    }
}
