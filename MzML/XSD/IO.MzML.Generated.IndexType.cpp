#include "IO.MzML.Generated.IndexType.h"
#include "IO.MzML.Generated.OffsetType.h"

namespace IO {
    namespace MzML {
        namespace Generated {

            std::vector<OffsetType*> IndexType::getoffset() const {
                return this->offsetField;
            }

            void IndexType::setoffset(const std::vector<OffsetType*> &value) {
                this->offsetField = value;
            }

            IndexTypeName IndexType::getname() const {
                return this->nameField;
            }

            void IndexType::setname(IndexTypeName value) {
                this->nameField = value;
            }
        }
    }
}
