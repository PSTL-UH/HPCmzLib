#include "IO.MzML.Generated.SourceFileRefType.h"

namespace IO {
    namespace MzML {
        namespace Generated {

            std::wstring SourceFileRefType::getref() const {
                return this->refField;
            }

            void SourceFileRefType::setref(const std::wstring &value) {
                this->refField = value;
            }
        }
    }
}
