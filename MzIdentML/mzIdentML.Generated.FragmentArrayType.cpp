#include "mzIdentML.Generated.FragmentArrayType.h"

namespace mzIdentML {
    namespace Generated {

        std::vector<float> FragmentArrayType::getvalues() const {
            return this->valuesField;
        }

        void FragmentArrayType::setvalues(const std::vector<float> &value) {
            this->valuesField = value;
        }

        std::wstring FragmentArrayType::getmeasure_ref() const {
            return this->measure_refField;
        }

        void FragmentArrayType::setmeasure_ref(const std::wstring &value) {
            this->measure_refField = value;
        }
    }
}
