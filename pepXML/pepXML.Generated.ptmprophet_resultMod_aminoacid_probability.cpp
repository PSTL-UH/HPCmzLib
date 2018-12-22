﻿#include "pepXML.Generated.ptmprophet_resultMod_aminoacid_probability.h"

namespace pepXML {
    namespace Generated {

        std::wstring ptmprophet_resultMod_aminoacid_probability::getposition() const {
            return this->positionField;
        }

        void ptmprophet_resultMod_aminoacid_probability::setposition(const std::wstring &value) {
            this->positionField = value;
        }

        float ptmprophet_resultMod_aminoacid_probability::getprobability() const {
            return this->probabilityField;
        }

        void ptmprophet_resultMod_aminoacid_probability::setprobability(float value) {
            this->probabilityField = value;
        }
    }
}
