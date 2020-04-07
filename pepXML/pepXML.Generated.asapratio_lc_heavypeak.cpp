#include "pepXML.Generated.asapratio_lc_heavypeak.h"

namespace pepXML
{
    namespace Generated
    {

        char asapratio_lc_heavypeak::getstatus() const
        {
            return this->statusField;
        }

        void asapratio_lc_heavypeak::setstatus(char value)
        {
            this->statusField = value;
        }

        int asapratio_lc_heavypeak::getleft_valley() const
        {
            return this->left_valleyField;
        }

        void asapratio_lc_heavypeak::setleft_valley(int value)
        {
            this->left_valleyField = value;
        }

        int asapratio_lc_heavypeak::getright_valley() const
        {
            return this->right_valleyField;
        }

        void asapratio_lc_heavypeak::setright_valley(int value)
        {
            this->right_valleyField = value;
        }

        float asapratio_lc_heavypeak::getbackground() const
        {
            return this->backgroundField;
        }

        void asapratio_lc_heavypeak::setbackground(float value)
        {
            this->backgroundField = value;
        }

        float asapratio_lc_heavypeak::getarea() const
        {
            return this->areaField;
        }

        void asapratio_lc_heavypeak::setarea(float value)
        {
            this->areaField = value;
        }

        float asapratio_lc_heavypeak::getarea_error() const
        {
            return this->area_errorField;
        }

        void asapratio_lc_heavypeak::setarea_error(float value)
        {
            this->area_errorField = value;
        }

        float asapratio_lc_heavypeak::gettime() const
        {
            return this->timeField;
        }

        void asapratio_lc_heavypeak::settime(float value)
        {
            this->timeField = value;
        }

        float asapratio_lc_heavypeak::gettime_width() const
        {
            return this->time_widthField;
        }

        void asapratio_lc_heavypeak::settime_width(float value)
        {
            this->time_widthField = value;
        }

        std::string asapratio_lc_heavypeak::getis_heavy() const
        {
            return this->is_heavyField;
        }

        void asapratio_lc_heavypeak::setis_heavy(const std::string &value)
        {
            this->is_heavyField = value;
        }
    }
}
