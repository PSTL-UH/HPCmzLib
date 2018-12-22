#include "mzIdentML110.Generated.ContactRoleType.h"
#include "mzIdentML110.Generated.RoleType.h"

namespace mzIdentML110 {
    namespace Generated {

        RoleType *ContactRoleType::getRole() const {
            return this->roleField;
        }

        void ContactRoleType::setRole(RoleType *value) {
            this->roleField = value;
        }

        std::wstring ContactRoleType::getcontact_ref() const {
            return this->contact_refField;
        }

        void ContactRoleType::setcontact_ref(const std::wstring &value) {
            this->contact_refField = value;
        }
    }
}
