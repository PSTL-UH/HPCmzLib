#include "mzIdentML.Generated.SubSampleType.h"

namespace mzIdentML {
    namespace Generated {

        std::wstring SubSampleType::getsample_ref() const {
            return this->sample_refField;
        }

        void SubSampleType::setsample_ref(const std::wstring &value) {
            this->sample_refField = value;
        }
    }
}
