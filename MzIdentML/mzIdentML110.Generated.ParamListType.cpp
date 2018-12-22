#include "mzIdentML110.Generated.ParamListType.h"
#include "mzIdentML110.Generated.AbstractParamType.h"

namespace mzIdentML110 {
    namespace Generated {

        std::vector<AbstractParamType*> ParamListType::getItems() const {
            return this->itemsField;
        }

        void ParamListType::setItems(const std::vector<AbstractParamType*> &value) {
            this->itemsField = value;
        }
    }
}
