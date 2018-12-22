#include "IO.MzML.Generated.IndexListType.h"
#include "IO.MzML.Generated.IndexType.h"

namespace IO {
    namespace MzML {
        namespace Generated {

            std::vector<IndexType*> IndexListType::getindex() const {
                return this->indexField;
            }

            void IndexListType::setindex(const std::vector<IndexType*> &value) {
                this->indexField = value;
            }

            std::wstring IndexListType::getcount() const {
                return this->countField;
            }

            void IndexListType::setcount(const std::wstring &value) {
                this->countField = value;
            }
        }
    }
}
