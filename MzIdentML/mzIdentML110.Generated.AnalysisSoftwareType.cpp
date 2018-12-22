#include "mzIdentML110.Generated.AnalysisSoftwareType.h"
#include "mzIdentML110.Generated.ContactRoleType.h"
#include "mzIdentML110.Generated.ParamType.h"

namespace mzIdentML110 {
    namespace Generated {

        ContactRoleType *AnalysisSoftwareType::getContactRole() const {
            return this->contactRoleField;
        }

        void AnalysisSoftwareType::setContactRole(ContactRoleType *value) {
            this->contactRoleField = value;
        }

        ParamType *AnalysisSoftwareType::getSoftwareName() const {
            return this->softwareNameField;
        }

        void AnalysisSoftwareType::setSoftwareName(ParamType *value) {
            this->softwareNameField = value;
        }

        std::wstring AnalysisSoftwareType::getCustomizations() const {
            return this->customizationsField;
        }

        void AnalysisSoftwareType::setCustomizations(const std::wstring &value) {
            this->customizationsField = value;
        }

        std::wstring AnalysisSoftwareType::getversion() const {
            return this->versionField;
        }

        void AnalysisSoftwareType::setversion(const std::wstring &value) {
            this->versionField = value;
        }

        std::wstring AnalysisSoftwareType::geturi() const {
            return this->uriField;
        }

        void AnalysisSoftwareType::seturi(const std::wstring &value) {
            this->uriField = value;
        }
    }
}
