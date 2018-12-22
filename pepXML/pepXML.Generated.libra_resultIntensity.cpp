#include "pepXML.Generated.libra_resultIntensity.h"

namespace pepXML {
    namespace Generated {

        libra_resultIntensity::libra_resultIntensity() {
            this->rejectField = false;
        }

        unsigned int libra_resultIntensity::getchannel() const {
            return this->channelField;
        }

        void libra_resultIntensity::setchannel(unsigned int value) {
            this->channelField = value;
        }

        float libra_resultIntensity::gettarget_mass() const {
            return this->target_massField;
        }

        void libra_resultIntensity::settarget_mass(float value) {
            this->target_massField = value;
        }

        float libra_resultIntensity::getabsolute() const {
            return this->absoluteField;
        }

        void libra_resultIntensity::setabsolute(float value) {
            this->absoluteField = value;
        }

        float libra_resultIntensity::getnormalized() const {
            return this->normalizedField;
        }

        void libra_resultIntensity::setnormalized(float value) {
            this->normalizedField = value;
        }

        bool libra_resultIntensity::getreject() const {
            return this->rejectField;
        }

        void libra_resultIntensity::setreject(bool value) {
            this->rejectField = value;
        }
    }
}
