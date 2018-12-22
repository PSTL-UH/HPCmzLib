#include "pepXML.Generated.asapratio_timestamp.h"

namespace pepXML {
    namespace Generated {

        std::wstring asapratio_timestamp::getquant_label_masses() const {
            return this->quant_label_massesField;
        }

        void asapratio_timestamp::setquant_label_masses(const std::wstring &value) {
            this->quant_label_massesField = value;
        }

        std::wstring asapratio_timestamp::getstatic_quant_label() const {
            return this->static_quant_labelField;
        }

        void asapratio_timestamp::setstatic_quant_label(const std::wstring &value) {
            this->static_quant_labelField = value;
        }
    }
}
