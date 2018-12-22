#include "mzIdentML.Generated.ParamListType.h"
#include "mzIdentML.Generated.AbstractParamType.h"

namespace mzIdentML {
    namespace Generated {

        std::vector<AbstractParamType*> ParamListType::getItems() const {
            return this->itemsField;
        }

        void ParamListType::setItems(const std::vector<AbstractParamType*> &value) {
            this->itemsField = value;
        }
    }
}
