#include "IO.MzML.Generated.ProcessingMethodType.h"

namespace IO {
    namespace MzML {
        namespace Generated {

            std::wstring ProcessingMethodType::getorder() const {
                return this->orderField;
            }

            void ProcessingMethodType::setorder(const std::wstring &value) {
                this->orderField = value;
            }

            std::wstring ProcessingMethodType::getsoftwareRef() const {
                return this->softwareRefField;
            }

            void ProcessingMethodType::setsoftwareRef(const std::wstring &value) {
                this->softwareRefField = value;
            }
        }
    }
}
