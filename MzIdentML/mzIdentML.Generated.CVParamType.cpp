﻿#include "mzIdentML.Generated.CVParamType.h"

namespace mzIdentML {
    namespace Generated {

        std::wstring CVParamType::getcvRef() const {
            return this->cvRefField;
        }

        void CVParamType::setcvRef(const std::wstring &value) {
            this->cvRefField = value;
        }

        std::wstring CVParamType::getaccession() const {
            return this->accessionField;
        }

        void CVParamType::setaccession(const std::wstring &value) {
            this->accessionField = value;
        }
    }
}
