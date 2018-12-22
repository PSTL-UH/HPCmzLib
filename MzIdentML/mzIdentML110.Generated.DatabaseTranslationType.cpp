#include "mzIdentML110.Generated.DatabaseTranslationType.h"
#include "mzIdentML110.Generated.TranslationTableType.h"

namespace mzIdentML110 {
    namespace Generated {

        std::vector<TranslationTableType*> DatabaseTranslationType::getTranslationTable() const {
            return this->translationTableField;
        }

        void DatabaseTranslationType::setTranslationTable(const std::vector<TranslationTableType*> &value) {
            this->translationTableField = value;
        }

        std::vector<int> DatabaseTranslationType::getframes() const {
            return this->framesField;
        }

        void DatabaseTranslationType::setframes(const std::vector<int> &value) {
            this->framesField = value;
        }
    }
}
