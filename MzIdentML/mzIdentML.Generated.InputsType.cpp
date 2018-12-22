#include "mzIdentML.Generated.InputsType.h"
#include "mzIdentML.Generated.SourceFileType.h"
#include "mzIdentML.Generated.SearchDatabaseType.h"
#include "mzIdentML.Generated.SpectraDataType.h"

namespace mzIdentML {
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
