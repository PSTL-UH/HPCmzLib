#include "pepXML.Generated.asapratio_lc_lightpeak.h"

namespace pepXML {
    namespace Generated {

        char asapratio_lc_lightpeak::getstatus() const {
            return this->statusField;
        }

        void asapratio_lc_lightpeak::setstatus(char value) {
            this->statusField = value;
        }

        int asapratio_lc_lightpeak::getleft_valley() const {
            return this->left_valleyField;
        }

        void asapratio_lc_lightpeak::setleft_valley(int value) {
            this->left_valleyField = value;
        }

        int asapratio_lc_lightpeak::getright_valley() const {
            return this->right_valleyField;
        }

        void asapratio_lc_lightpeak::setright_valley(int value) {
            this->right_valleyField = value;
        }

        float asapratio_lc_lightpeak::getbackground() const {
            return this->backgroundField;
        }

        void asapratio_lc_lightpeak::setbackground(float value) {
            this->backgroundField = value;
        }

        float asapratio_lc_lightpeak::getarea() const {
            return this->areaField;
        }

        void asapratio_lc_lightpeak::setarea(float value) {
            this->areaField = value;
        }

        float asapratio_lc_lightpeak::getarea_error() const {
            return this->area_errorField;
        }

        void asapratio_lc_lightpeak::setarea_error(float value) {
            this->area_errorField = value;
        }

        float asapratio_lc_lightpeak::gettime() const {
            return this->timeField;
        }

        void asapratio_lc_lightpeak::settime(float value) {
            this->timeField = value;
        }

        float asapratio_lc_lightpeak::gettime_width() const {
            return this->time_widthField;
        }

        void asapratio_lc_lightpeak::settime_width(float value) {
            this->time_widthField = value;
        }

        std::wstring asapratio_lc_lightpeak::getis_heavy() const {
            return this->is_heavyField;
        }

        void asapratio_lc_lightpeak::setis_heavy(const std::wstring &value) {
            this->is_heavyField = value;
        }
    }
}
