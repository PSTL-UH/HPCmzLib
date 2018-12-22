#include "mzIdentML.Generated.PeptideType.h"
#include "mzIdentML.Generated.ModificationType.h"
#include "mzIdentML.Generated.SubstitutionModificationType.h"
#include "mzIdentML.Generated.CVParamType.h"
#include "mzIdentML.Generated.UserParamType.h"

namespace mzIdentML {
    namespace Generated {

        std::wstring PeptideType::getPeptideSequence() const {
            return this->peptideSequenceField;
        }

        void PeptideType::setPeptideSequence(const std::wstring &value) {
            this->peptideSequenceField = value;
        }

        std::vector<ModificationType*> PeptideType::getModification() const {
            return this->modificationField;
        }

        void PeptideType::setModification(const std::vector<ModificationType*> &value) {
            this->modificationField = value;
        }

        std::vector<SubstitutionModificationType*> PeptideType::getSubstitutionModification() const {
            return this->substitutionModificationField;
        }

        void PeptideType::setSubstitutionModification(const std::vector<SubstitutionModificationType*> &value) {
            this->substitutionModificationField = value;
        }

        std::vector<CVParamType*> PeptideType::getcvParam() const {
            return this->cvParamField;
        }

        void PeptideType::setcvParam(const std::vector<CVParamType*> &value) {
            this->cvParamField = value;
        }

        std::vector<UserParamType*> PeptideType::getuserParam() const {
            return this->userParamField;
        }

        void PeptideType::setuserParam(const std::vector<UserParamType*> &value) {
            this->userParamField = value;
        }
    }
}
