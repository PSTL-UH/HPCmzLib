#include "mzIdentML.Generated.ProviderType.h"
#include "mzIdentML.Generated.ContactRoleType.h"

namespace mzIdentML {
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
