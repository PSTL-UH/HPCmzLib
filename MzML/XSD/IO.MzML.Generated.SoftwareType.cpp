#include "IO.MzML.Generated.SoftwareType.h"

namespace IO {
    namespace MzML {
        namespace Generated {

            std::wstring SoftwareType::getid() const {
                return this->idField;
            }

            void SoftwareType::setid(const std::wstring &value) {
                this->idField = value;
            }

            std::wstring SoftwareType::getversion() const {
                return this->versionField;
            }

            void SoftwareType::setversion(const std::wstring &value) {
                this->versionField = value;
            }
        }
    }
}
