#include "mzIdentML110.Generated.SearchModificationType.h"
#include "mzIdentML110.Generated.CVParamType.h"

namespace mzIdentML110 {
    namespace Generated {

        std::vector<CVParamType*> SearchModificationType::getSpecificityRules() const {
            return this->specificityRulesField;
        }

        void SearchModificationType::setSpecificityRules(const std::vector<CVParamType*> &value) {
            this->specificityRulesField = value;
        }

        std::vector<CVParamType*> SearchModificationType::getcvParam() const {
            return this->cvParamField;
        }

        void SearchModificationType::setcvParam(const std::vector<CVParamType*> &value) {
            this->cvParamField = value;
        }

        bool SearchModificationType::getfixedMod() const {
            return this->fixedModField;
        }

        void SearchModificationType::setfixedMod(bool value) {
            this->fixedModField = value;
        }

        float SearchModificationType::getmassDelta() const {
            return this->massDeltaField;
        }

        void SearchModificationType::setmassDelta(float value) {
            this->massDeltaField = value;
        }

        std::wstring SearchModificationType::getresidues() const {
            return this->residuesField;
        }

        void SearchModificationType::setresidues(const std::wstring &value) {
            this->residuesField = value;
        }
    }
}
