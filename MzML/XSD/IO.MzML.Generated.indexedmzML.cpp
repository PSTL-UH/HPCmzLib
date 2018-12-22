#include "IO.MzML.Generated.indexedmzML.h"
#include "IO.MzML.Generated.mzMLType.h"
#include "IO.MzML.Generated.IndexListType.h"

namespace IO {
    namespace MzML {
        namespace Generated {

            mzMLType *indexedmzML::getmzML() const {
                return this->mzMLField;
            }

            void indexedmzML::setmzML(mzMLType *value) {
                this->mzMLField = value;
            }

            IndexListType *indexedmzML::getindexList() const {
                return this->indexListField;
            }

            void indexedmzML::setindexList(IndexListType *value) {
                this->indexListField = value;
            }

            std::optional<long long> indexedmzML::getindexListOffset() const {
                return this->indexListOffsetField;
            }

            void indexedmzML::setindexListOffset(const std::optional<long long> &value) {
                this->indexListOffsetField = value;
            }

            std::wstring indexedmzML::getfileChecksum() const {
                return this->fileChecksumField;
            }

            void indexedmzML::setfileChecksum(const std::wstring &value) {
                this->fileChecksumField = value;
            }
        }
    }
}
