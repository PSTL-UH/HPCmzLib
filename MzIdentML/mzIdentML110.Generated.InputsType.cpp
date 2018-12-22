#include "mzIdentML110.Generated.InputsType.h"
#include "mzIdentML110.Generated.SourceFileType.h"
#include "mzIdentML110.Generated.SearchDatabaseType.h"
#include "mzIdentML110.Generated.SpectraDataType.h"

namespace mzIdentML110 {
    namespace Generated {

        std::vector<SourceFileType*> InputsType::getSourceFile() const {
            return this->sourceFileField;
        }

        void InputsType::setSourceFile(const std::vector<SourceFileType*> &value) {
            this->sourceFileField = value;
        }

        std::vector<SearchDatabaseType*> InputsType::getSearchDatabase() const {
            return this->searchDatabaseField;
        }

        void InputsType::setSearchDatabase(const std::vector<SearchDatabaseType*> &value) {
            this->searchDatabaseField = value;
        }

        std::vector<SpectraDataType*> InputsType::getSpectraData() const {
            return this->spectraDataField;
        }

        void InputsType::setSpectraData(const std::vector<SpectraDataType*> &value) {
            this->spectraDataField = value;
        }
    }
}
