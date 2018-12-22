#include "IO.MzML.Generated.SoftwareRefType.h"

namespace IO {
    namespace MzML {
        namespace Generated {

            std::wstring SoftwareRefType::getref() const {
                return this->refField;
            }

            void SoftwareRefType::setref(const std::wstring &value) {
                this->refField = value;
            }
        }
    }
}
