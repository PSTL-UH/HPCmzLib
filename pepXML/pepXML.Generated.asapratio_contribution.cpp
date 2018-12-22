#include "pepXML.Generated.asapratio_contribution.h"
#include "pepXML.Generated.asapratio_lc_lightpeak.h"
#include "pepXML.Generated.asapratio_lc_heavypeak.h"

namespace pepXML {
    namespace Generated {

        pepXML::Generated::asapratio_lc_lightpeak *asapratio_contribution::getasapratio_lc_lightpeak() const {
            return this->asapratio_lc_lightpeakField;
        }

        void asapratio_contribution::setasapratio_lc_lightpeak(pepXML::Generated::asapratio_lc_lightpeak *value) {
            this->asapratio_lc_lightpeakField = value;
        }

        pepXML::Generated::asapratio_lc_heavypeak *asapratio_contribution::getasapratio_lc_heavypeak() const {
            return this->asapratio_lc_heavypeakField;
        }

        void asapratio_contribution::setasapratio_lc_heavypeak(pepXML::Generated::asapratio_lc_heavypeak *value) {
            this->asapratio_lc_heavypeakField = value;
        }

        float asapratio_contribution::getratio() const {
            return this->ratioField;
        }

        void asapratio_contribution::setratio(float value) {
            this->ratioField = value;
        }

        float asapratio_contribution::geterror() const {
            return this->errorField;
        }

        void asapratio_contribution::seterror(float value) {
            this->errorField = value;
        }

        std::wstring asapratio_contribution::getcharge() const {
            return this->chargeField;
        }

        void asapratio_contribution::setcharge(const std::wstring &value) {
            this->chargeField = value;
        }

        unsigned char asapratio_contribution::getuse() const {
            return this->useField;
        }

        void asapratio_contribution::setuse(unsigned char value) {
            this->useField = value;
        }
    }
}
