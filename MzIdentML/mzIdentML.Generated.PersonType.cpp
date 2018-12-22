#include "mzIdentML.Generated.PersonType.h"
#include "mzIdentML.Generated.AffiliationType.h"

namespace mzIdentML {
    namespace Generated {

        std::vector<AffiliationType*> PersonType::getAffiliation() const {
            return this->affiliationField;
        }

        void PersonType::setAffiliation(const std::vector<AffiliationType*> &value) {
            this->affiliationField = value;
        }

        std::wstring PersonType::getlastName() const {
            return this->lastNameField;
        }

        void PersonType::setlastName(const std::wstring &value) {
            this->lastNameField = value;
        }

        std::wstring PersonType::getfirstName() const {
            return this->firstNameField;
        }

        void PersonType::setfirstName(const std::wstring &value) {
            this->firstNameField = value;
        }

        std::wstring PersonType::getmidInitials() const {
            return this->midInitialsField;
        }

        void PersonType::setmidInitials(const std::wstring &value) {
            this->midInitialsField = value;
        }
    }
}
