#include "mzIdentML110.Generated.ModificationType.h"
#include "mzIdentML110.Generated.CVParamType.h"

namespace mzIdentML110 {
    namespace Generated {

        std::vector<CVParamType*> ModificationType::getcvParam() const {
            return this->cvParamField;
        }

        void ModificationType::setcvParam(const std::vector<CVParamType*> &value) {
            this->cvParamField = value;
        }

        int ModificationType::getlocation() const {
            return this->locationField;
        }

        void ModificationType::setlocation(int value) {
            this->locationField = value;
        }

        bool ModificationType::getlocationSpecified() const {
            return this->locationFieldSpecified;
        }

        void ModificationType::setlocationSpecified(bool value) {
            this->locationFieldSpecified = value;
        }

        std::vector<std::wstring> ModificationType::getresidues() const {
            return this->residuesField;
        }

        void ModificationType::setresidues(const std::vector<std::wstring> &value) {
            this->residuesField = value;
        }

        double ModificationType::getavgMassDelta() const {
            return this->avgMassDeltaField;
        }

        void ModificationType::setavgMassDelta(double value) {
            this->avgMassDeltaField = value;
        }

        bool ModificationType::getavgMassDeltaSpecified() const {
            return this->avgMassDeltaFieldSpecified;
        }

        void ModificationType::setavgMassDeltaSpecified(bool value) {
            this->avgMassDeltaFieldSpecified = value;
        }

        double ModificationType::getmonoisotopicMassDelta() const {
            return this->monoisotopicMassDeltaField;
        }

        void ModificationType::setmonoisotopicMassDelta(double value) {
            this->monoisotopicMassDeltaField = value;
        }

        bool ModificationType::getmonoisotopicMassDeltaSpecified() const {
            return this->monoisotopicMassDeltaFieldSpecified;
        }

        void ModificationType::setmonoisotopicMassDeltaSpecified(bool value) {
            this->monoisotopicMassDeltaFieldSpecified = value;
        }
    }
}
