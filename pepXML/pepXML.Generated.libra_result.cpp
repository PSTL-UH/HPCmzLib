#include "pepXML.Generated.libra_result.h"
#include "pepXML.Generated.libra_resultIntensity.h"

namespace pepXML {
    namespace Generated {

        libra_result::libra_result() {
            this->is_rejectedField = false;
        }

        std::vector<libra_resultIntensity*> libra_result::getintensity() const {
            return this->intensityField;
        }

        void libra_result::setintensity(const std::vector<libra_resultIntensity*> &value) {
            this->intensityField = value;
        }

        bool libra_result::getis_rejected() const {
            return this->is_rejectedField;
        }

        void libra_result::setis_rejected(bool value) {
            this->is_rejectedField = value;
        }
    }
}
