#include "mzIdentML110.Generated.ProviderType.h"
#include "mzIdentML110.Generated.ContactRoleType.h"

namespace mzIdentML110 {
    namespace Generated {

        ContactRoleType *ProviderType::getContactRole() const {
            return this->contactRoleField;
        }

        void ProviderType::setContactRole(ContactRoleType *value) {
            this->contactRoleField = value;
        }

        std::wstring ProviderType::getanalysisSoftware_ref() const {
            return this->analysisSoftware_refField;
        }

        void ProviderType::setanalysisSoftware_ref(const std::wstring &value) {
            this->analysisSoftware_refField = value;
        }
    }
}
