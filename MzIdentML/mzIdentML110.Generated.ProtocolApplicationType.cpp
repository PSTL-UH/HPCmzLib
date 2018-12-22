#include "mzIdentML110.Generated.ProtocolApplicationType.h"

namespace mzIdentML110 {
    namespace Generated {

        DateTime ProtocolApplicationType::getactivityDate() const {
            return this->activityDateField;
        }

        void ProtocolApplicationType::setactivityDate(DateTime value) {
            this->activityDateField = value;
        }

        bool ProtocolApplicationType::getactivityDateSpecified() const {
            return this->activityDateFieldSpecified;
        }

        void ProtocolApplicationType::setactivityDateSpecified(bool value) {
            this->activityDateFieldSpecified = value;
        }
    }
}
