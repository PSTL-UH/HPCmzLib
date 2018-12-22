#include "mzIdentML110.Generated.ParamType.h"
#include "mzIdentML110.Generated.AbstractParamType.h"

namespace mzIdentML110 {
    namespace Generated {

        AbstractParamType *ParamType::getItem() const {
            return this->itemField;
        }

        void ParamType::setItem(AbstractParamType *value) {
            this->itemField = value;
        }
    }
}
