#include "pepXML.Generated.mixtureModelType.h"
#include "pepXML.Generated.mixtureModelTypePoint.h"

namespace pepXML {
    namespace Generated {

        std::vector<mixtureModelTypePoint*> mixtureModelType::getpoint() const {
            return this->pointField;
        }

        void mixtureModelType::setpoint(const std::vector<mixtureModelTypePoint*> &value) {
            this->pointField = value;
        }

        std::wstring mixtureModelType::getname() const {
            return this->nameField;
        }

        void mixtureModelType::setname(const std::wstring &value) {
            this->nameField = value;
        }

        float mixtureModelType::getpos_bandwidth() const {
            return this->pos_bandwidthField;
        }

        void mixtureModelType::setpos_bandwidth(float value) {
            this->pos_bandwidthField = value;
        }

        float mixtureModelType::getneg_bandwidth() const {
            return this->neg_bandwidthField;
        }

        void mixtureModelType::setneg_bandwidth(float value) {
            this->neg_bandwidthField = value;
        }
    }
}
