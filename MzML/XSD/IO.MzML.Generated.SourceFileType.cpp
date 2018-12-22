#include "IO.MzML.Generated.SourceFileType.h"

namespace IO {
    namespace MzML {
        namespace Generated {

            std::wstring SourceFileType::getid() const {
                return this->idField;
            }

            void SourceFileType::setid(const std::wstring &value) {
                this->idField = value;
            }

            std::wstring SourceFileType::getname() const {
                return this->nameField;
            }

            void SourceFileType::setname(const std::wstring &value) {
                this->nameField = value;
            }

            std::wstring SourceFileType::getlocation() const {
                return this->locationField;
            }

            void SourceFileType::setlocation(const std::wstring &value) {
                this->locationField = value;
            }
        }
    }
}
