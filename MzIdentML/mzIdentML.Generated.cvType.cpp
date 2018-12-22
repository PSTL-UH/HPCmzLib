#include "mzIdentML.Generated.cvType.h"

namespace mzIdentML {
    namespace Generated {

        std::wstring cvType::getfullName() const {
            return this->fullNameField;
        }

        void cvType::setfullName(const std::wstring &value) {
            this->fullNameField = value;
        }

        std::wstring cvType::getversion() const {
            return this->versionField;
        }

        void cvType::setversion(const std::wstring &value) {
            this->versionField = value;
        }

        std::wstring cvType::geturi() const {
            return this->uriField;
        }

        void cvType::seturi(const std::wstring &value) {
            this->uriField = value;
        }

        std::wstring cvType::getid() const {
            return this->idField;
        }

        void cvType::setid(const std::wstring &value) {
            this->idField = value;
        }
    }
}
