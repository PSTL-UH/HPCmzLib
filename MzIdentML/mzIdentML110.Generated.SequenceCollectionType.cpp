#include "mzIdentML110.Generated.SequenceCollectionType.h"
#include "mzIdentML110.Generated.DBSequenceType.h"
#include "mzIdentML110.Generated.PeptideType.h"
#include "mzIdentML110.Generated.PeptideEvidenceType.h"

namespace mzIdentML110 {
    namespace Generated {

        std::vector<DBSequenceType*> SequenceCollectionType::getDBSequence() const {
            return this->dBSequenceField;
        }

        void SequenceCollectionType::setDBSequence(const std::vector<DBSequenceType*> &value) {
            this->dBSequenceField = value;
        }

        std::vector<PeptideType*> SequenceCollectionType::getPeptide() const {
            return this->peptideField;
        }

        void SequenceCollectionType::setPeptide(const std::vector<PeptideType*> &value) {
            this->peptideField = value;
        }

        std::vector<PeptideEvidenceType*> SequenceCollectionType::getPeptideEvidence() const {
            return this->peptideEvidenceField;
        }

        void SequenceCollectionType::setPeptideEvidence(const std::vector<PeptideEvidenceType*> &value) {
            this->peptideEvidenceField = value;
        }
    }
}
