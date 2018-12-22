#include "pepXML.Generated.rocErrorDataTypeRoc_data_point.h"

namespace pepXML {
    namespace Generated {

        float rocErrorDataTypeRoc_data_point::getmin_prob() const {
            return this->min_probField;
        }

        void rocErrorDataTypeRoc_data_point::setmin_prob(float value) {
            this->min_probField = value;
        }

        float rocErrorDataTypeRoc_data_point::getsensitivity() const {
            return this->sensitivityField;
        }

        void rocErrorDataTypeRoc_data_point::setsensitivity(float value) {
            this->sensitivityField = value;
        }

        float rocErrorDataTypeRoc_data_point::geterror() const {
            return this->errorField;
        }

        void rocErrorDataTypeRoc_data_point::seterror(float value) {
            this->errorField = value;
        }

        unsigned int rocErrorDataTypeRoc_data_point::getnum_corr() const {
            return this->num_corrField;
        }

        void rocErrorDataTypeRoc_data_point::setnum_corr(unsigned int value) {
            this->num_corrField = value;
        }

        unsigned int rocErrorDataTypeRoc_data_point::getnum_incorr() const {
            return this->num_incorrField;
        }

        void rocErrorDataTypeRoc_data_point::setnum_incorr(unsigned int value) {
            this->num_incorrField = value;
        }
    }
}
