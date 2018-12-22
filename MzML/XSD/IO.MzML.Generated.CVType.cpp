#include "IO.MzML.Generated.CVType.h"

namespace IO {
    namespace MzML {
        namespace Generated {

            std::wstring CVType::getid() const {
                return this->idField;
            }

            void CVType::setid(const std::wstring &value) {
                this->idField = value;
            }

            std::wstring CVType::getfullName() const {
                return this->fullNameField;
            }

            void CVType::setfullName(const std::wstring &value) {
                this->fullNameField = value;
            }

            std::wstring CVType::getversion() const {
                return this->versionField;
            }

            void CVType::setversion(const std::wstring &value) {
                this->versionField = value;
            }

            std::wstring CVType::getURI() const {
                return this->uRIField;
            }

            void CVType::setURI(const std::wstring &value) {
                this->uRIField = value;
            }
        }
    }
}
