#include "mzIdentML.Generated.OrganizationType.h"
#include "mzIdentML.Generated.ParentOrganizationType.h"

namespace mzIdentML {
    namespace Generated {

        ParentOrganizationType *OrganizationType::getParent() const {
            return this->parentField;
        }

        void OrganizationType::setParent(ParentOrganizationType *value) {
            this->parentField = value;
        }
    }
}
