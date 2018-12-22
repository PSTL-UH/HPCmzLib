#include "mzIdentML.Generated.DatabaseTranslationType.h"
#include "mzIdentML.Generated.TranslationTableType.h"

namespace mzIdentML {
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
