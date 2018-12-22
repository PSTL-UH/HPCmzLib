#include "mzIdentML.Generated.SubstitutionModificationType.h"

namespace mzIdentML {
    namespace Generated {

        std::wstring SubstitutionModificationType::getoriginalResidue() const {
            return this->originalResidueField;
        }

        void SubstitutionModificationType::setoriginalResidue(const std::wstring &value) {
            this->originalResidueField = value;
        }

        std::wstring SubstitutionModificationType::getreplacementResidue() const {
            return this->replacementResidueField;
        }

        void SubstitutionModificationType::setreplacementResidue(const std::wstring &value) {
            this->replacementResidueField = value;
        }

        int SubstitutionModificationType::getlocation() const {
            return this->locationField;
        }

        void SubstitutionModificationType::setlocation(int value) {
            this->locationField = value;
        }

        bool SubstitutionModificationType::getlocationSpecified() const {
            return this->locationFieldSpecified;
        }

        void SubstitutionModificationType::setlocationSpecified(bool value) {
            this->locationFieldSpecified = value;
        }

        double SubstitutionModificationType::getavgMassDelta() const {
            return this->avgMassDeltaField;
        }

        void SubstitutionModificationType::setavgMassDelta(double value) {
            this->avgMassDeltaField = value;
        }

        bool SubstitutionModificationType::getavgMassDeltaSpecified() const {
            return this->avgMassDeltaFieldSpecified;
        }

        void SubstitutionModificationType::setavgMassDeltaSpecified(bool value) {
            this->avgMassDeltaFieldSpecified = value;
        }

        double SubstitutionModificationType::getmonoisotopicMassDelta() const {
            return this->monoisotopicMassDeltaField;
        }

        void SubstitutionModificationType::setmonoisotopicMassDelta(double value) {
            this->monoisotopicMassDeltaField = value;
        }

        bool SubstitutionModificationType::getmonoisotopicMassDeltaSpecified() const {
            return this->monoisotopicMassDeltaFieldSpecified;
        }

        void SubstitutionModificationType::setmonoisotopicMassDeltaSpecified(bool value) {
            this->monoisotopicMassDeltaFieldSpecified = value;
        }
    }
}
