#include "pepXML.Generated.rocErrorDataType.h"
#include "pepXML.Generated.rocErrorDataTypeRoc_data_point.h"
#include "pepXML.Generated.rocErrorDataTypeError_point.h"

namespace pepXML {
    namespace Generated {

        std::vector<rocErrorDataTypeRoc_data_point*> rocErrorDataType::getroc_data_point() const {
            return this->roc_data_pointField;
        }

        void rocErrorDataType::setroc_data_point(const std::vector<rocErrorDataTypeRoc_data_point*> &value) {
            this->roc_data_pointField = value;
        }

        std::vector<rocErrorDataTypeError_point*> rocErrorDataType::geterror_point() const {
            return this->error_pointField;
        }

        void rocErrorDataType::seterror_point(const std::vector<rocErrorDataTypeError_point*> &value) {
            this->error_pointField = value;
        }

        std::wstring rocErrorDataType::getcharge() const {
            return this->chargeField;
        }

        void rocErrorDataType::setcharge(const std::wstring &value) {
            this->chargeField = value;
        }

        float rocErrorDataType::getcharge_est_correct() const {
            return this->charge_est_correctField;
        }

        void rocErrorDataType::setcharge_est_correct(float value) {
            this->charge_est_correctField = value;
        }

        bool rocErrorDataType::getcharge_est_correctSpecified() const {
            return this->charge_est_correctFieldSpecified;
        }

        void rocErrorDataType::setcharge_est_correctSpecified(bool value) {
            this->charge_est_correctFieldSpecified = value;
        }
    }
}
