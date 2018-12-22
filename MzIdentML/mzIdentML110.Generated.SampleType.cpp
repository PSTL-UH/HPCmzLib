#include "mzIdentML110.Generated.SampleType.h"
#include "mzIdentML110.Generated.ContactRoleType.h"
#include "mzIdentML110.Generated.SubSampleType.h"
#include "mzIdentML110.Generated.CVParamType.h"
#include "mzIdentML110.Generated.UserParamType.h"

namespace mzIdentML110 {
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
