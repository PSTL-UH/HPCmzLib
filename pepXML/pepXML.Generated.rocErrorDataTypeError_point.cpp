#include "pepXML.Generated.rocErrorDataTypeError_point.h"

namespace pepXML
{
    namespace Generated
    {

        float rocErrorDataTypeError_point::geterror() const
        {
            return this->errorField;
        }

        void rocErrorDataTypeError_point::seterror(float value)
        {
            this->errorField = value;
        }

        float rocErrorDataTypeError_point::getmin_prob() const
        {
            return this->min_probField;
        }

        void rocErrorDataTypeError_point::setmin_prob(float value)
        {
            this->min_probField = value;
        }

        unsigned int rocErrorDataTypeError_point::getnum_corr() const
        {
            return this->num_corrField;
        }

        void rocErrorDataTypeError_point::setnum_corr(unsigned int value)
        {
            this->num_corrField = value;
        }

        unsigned int rocErrorDataTypeError_point::getnum_incorr() const
        {
            return this->num_incorrField;
        }

        void rocErrorDataTypeError_point::setnum_incorr(unsigned int value)
        {
            this->num_incorrField = value;
        }
    }
}
