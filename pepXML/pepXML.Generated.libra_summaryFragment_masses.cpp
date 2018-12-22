#include "pepXML.Generated.libra_summaryFragment_masses.h"

namespace pepXML {
    namespace Generated {

        unsigned int libra_summaryFragment_masses::getchannel() const {
            return this->channelField;
        }

        void libra_summaryFragment_masses::setchannel(unsigned int value) {
            this->channelField = value;
        }

        float libra_summaryFragment_masses::getmz() const {
            return this->mzField;
        }

        void libra_summaryFragment_masses::setmz(float value) {
            this->mzField = value;
        }

        float libra_summaryFragment_masses::getoffset() const {
            return this->offsetField;
        }

        void libra_summaryFragment_masses::setoffset(float value) {
            this->offsetField = value;
        }

        bool libra_summaryFragment_masses::getoffsetSpecified() const {
            return this->offsetFieldSpecified;
        }

        void libra_summaryFragment_masses::setoffsetSpecified(bool value) {
            this->offsetFieldSpecified = value;
        }
    }
}
