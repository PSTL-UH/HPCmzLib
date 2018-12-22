#include "mzIdentML.Generated.SearchModificationType.h"
#include "mzIdentML.Generated.CVParamType.h"

namespace mzIdentML {
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

        double SearchModificationType::getmassDelta() const {
            return this->massDeltaField;
        }

        void SearchModificationType::setmassDelta(double value) {
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
