#include "mzIdentML110.Generated.MassTableType.h"
#include "mzIdentML110.Generated.ResidueType.h"
#include "mzIdentML110.Generated.AmbiguousResidueType.h"
#include "mzIdentML110.Generated.CVParamType.h"
#include "mzIdentML110.Generated.UserParamType.h"

namespace mzIdentML110 {
    namespace Generated {

        std::vector<ResidueType*> MassTableType::getResidue() const {
            return this->residueField;
        }

        void MassTableType::setResidue(const std::vector<ResidueType*> &value) {
            this->residueField = value;
        }

        std::vector<AmbiguousResidueType*> MassTableType::getAmbiguousResidue() const {
            return this->ambiguousResidueField;
        }

        void MassTableType::setAmbiguousResidue(const std::vector<AmbiguousResidueType*> &value) {
            this->ambiguousResidueField = value;
        }

        std::vector<CVParamType*> MassTableType::getcvParam() const {
            return this->cvParamField;
        }

        void MassTableType::setcvParam(const std::vector<CVParamType*> &value) {
            this->cvParamField = value;
        }

        std::vector<UserParamType*> MassTableType::getuserParam() const {
            return this->userParamField;
        }

        void MassTableType::setuserParam(const std::vector<UserParamType*> &value) {
            this->userParamField = value;
        }

        std::vector<std::wstring> MassTableType::getmsLevel() const {
            return this->msLevelField;
        }

        void MassTableType::setmsLevel(const std::vector<std::wstring> &value) {
            this->msLevelField = value;
        }
    }
}
