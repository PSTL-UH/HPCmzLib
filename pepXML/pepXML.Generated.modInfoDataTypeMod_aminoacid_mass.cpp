#include "pepXML.Generated.modInfoDataTypeMod_aminoacid_mass.h"

namespace pepXML
{
    namespace Generated
    {

        std::string modInfoDataTypeMod_aminoacid_mass::getposition() const
        {
            return this->positionField;
        }

        void modInfoDataTypeMod_aminoacid_mass::setposition(const std::string &value)
        {
            this->positionField = value;
        }

        double modInfoDataTypeMod_aminoacid_mass::getmass() const
        {
            return this->massField;
        }

        void modInfoDataTypeMod_aminoacid_mass::setmass(double value)
        {
            this->massField = value;
        }

        std::string modInfoDataTypeMod_aminoacid_mass::getsource() const
        {
            return this->sourceField;
        }

        void modInfoDataTypeMod_aminoacid_mass::setsource(const std::string &value)
        {
            this->sourceField = value;
        }
    }
}
