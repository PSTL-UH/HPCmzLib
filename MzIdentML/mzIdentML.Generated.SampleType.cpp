#include "mzIdentML.Generated.SampleType.h"
#include "mzIdentML.Generated.ContactRoleType.h"
#include "mzIdentML.Generated.SubSampleType.h"
#include "mzIdentML.Generated.CVParamType.h"
#include "mzIdentML.Generated.UserParamType.h"

namespace mzIdentML {
    namespace Generated {

        std::vector<ContactRoleType*> SampleType::getContactRole() const {
            return this->contactRoleField;
        }

        void SampleType::setContactRole(const std::vector<ContactRoleType*> &value) {
            this->contactRoleField = value;
        }

        std::vector<SubSampleType*> SampleType::getSubSample() const {
            return this->subSampleField;
        }

        void SampleType::setSubSample(const std::vector<SubSampleType*> &value) {
            this->subSampleField = value;
        }

        std::vector<CVParamType*> SampleType::getcvParam() const {
            return this->cvParamField;
        }

        void SampleType::setcvParam(const std::vector<CVParamType*> &value) {
            this->cvParamField = value;
        }

        std::vector<UserParamType*> SampleType::getuserParam() const {
            return this->userParamField;
        }

        void SampleType::setuserParam(const std::vector<UserParamType*> &value) {
            this->userParamField = value;
        }
    }
}
