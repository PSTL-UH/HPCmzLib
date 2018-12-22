#include "mzIdentML.Generated.EnzymeType.h"
#include "mzIdentML.Generated.ParamListType.h"

namespace mzIdentML {
    namespace Generated {

        std::wstring EnzymeType::getSiteRegexp() const {
            return this->siteRegexpField;
        }

        void EnzymeType::setSiteRegexp(const std::wstring &value) {
            this->siteRegexpField = value;
        }

        ParamListType *EnzymeType::getEnzymeName() const {
            return this->enzymeNameField;
        }

        void EnzymeType::setEnzymeName(ParamListType *value) {
            this->enzymeNameField = value;
        }

        std::wstring EnzymeType::getnTermGain() const {
            return this->nTermGainField;
        }

        void EnzymeType::setnTermGain(const std::wstring &value) {
            this->nTermGainField = value;
        }

        std::wstring EnzymeType::getcTermGain() const {
            return this->cTermGainField;
        }

        void EnzymeType::setcTermGain(const std::wstring &value) {
            this->cTermGainField = value;
        }

        bool EnzymeType::getsemiSpecific() const {
            return this->semiSpecificField;
        }

        void EnzymeType::setsemiSpecific(bool value) {
            this->semiSpecificField = value;
        }

        bool EnzymeType::getsemiSpecificSpecified() const {
            return this->semiSpecificFieldSpecified;
        }

        void EnzymeType::setsemiSpecificSpecified(bool value) {
            this->semiSpecificFieldSpecified = value;
        }

        int EnzymeType::getmissedCleavages() const {
            return this->missedCleavagesField;
        }

        void EnzymeType::setmissedCleavages(int value) {
            this->missedCleavagesField = value;
        }

        bool EnzymeType::getmissedCleavagesSpecified() const {
            return this->missedCleavagesFieldSpecified;
        }

        void EnzymeType::setmissedCleavagesSpecified(bool value) {
            this->missedCleavagesFieldSpecified = value;
        }

        int EnzymeType::getminDistance() const {
            return this->minDistanceField;
        }

        void EnzymeType::setminDistance(int value) {
            this->minDistanceField = value;
        }

        bool EnzymeType::getminDistanceSpecified() const {
            return this->minDistanceFieldSpecified;
        }

        void EnzymeType::setminDistanceSpecified(bool value) {
            this->minDistanceFieldSpecified = value;
        }
    }
}
