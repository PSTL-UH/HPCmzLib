#include "pepXML.Generated.modInfoDataTypeMod_aminoacid_mass.h"

namespace pepXML {
    namespace Generated {

        std::wstring modInfoDataTypeMod_aminoacid_mass::getposition() const {
            return this->positionField;
        }

        void modInfoDataTypeMod_aminoacid_mass::setposition(const std::wstring &value) {
            this->positionField = value;
        }

        double modInfoDataTypeMod_aminoacid_mass::getmass() const {
            return this->massField;
        }

        void modInfoDataTypeMod_aminoacid_mass::setmass(double value) {
            this->massField = value;
        }

        std::wstring modInfoDataTypeMod_aminoacid_mass::getsource() const {
            return this->sourceField;
        }

        void modInfoDataTypeMod_aminoacid_mass::setsource(const std::wstring &value) {
            this->sourceField = value;
        }
    }
}
