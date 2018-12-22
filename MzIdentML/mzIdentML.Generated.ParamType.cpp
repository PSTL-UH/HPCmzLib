#include "mzIdentML.Generated.ParamType.h"
#include "mzIdentML.Generated.AbstractParamType.h"

namespace mzIdentML {
    namespace Generated {

        AbstractParamType *ParamType::getItem() const {
            return this->itemField;
        }

        void ParamType::setItem(AbstractParamType *value) {
            this->itemField = value;
        }
    }
}
