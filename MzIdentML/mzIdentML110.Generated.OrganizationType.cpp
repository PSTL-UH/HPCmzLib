#include "mzIdentML110.Generated.OrganizationType.h"
#include "mzIdentML110.Generated.ParentOrganizationType.h"

namespace mzIdentML110 {
    namespace Generated {

        ParentOrganizationType *OrganizationType::getParent() const {
            return this->parentField;
        }

        void OrganizationType::setParent(ParentOrganizationType *value) {
            this->parentField = value;
        }
    }
}
