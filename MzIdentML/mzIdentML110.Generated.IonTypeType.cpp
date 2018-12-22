#include "mzIdentML110.Generated.IonTypeType.h"
#include "mzIdentML110.Generated.FragmentArrayType.h"
#include "mzIdentML110.Generated.CVParamType.h"

namespace mzIdentML110 {
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
