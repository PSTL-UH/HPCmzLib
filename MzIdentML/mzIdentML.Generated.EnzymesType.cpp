#include "mzIdentML.Generated.EnzymesType.h"
#include "mzIdentML.Generated.EnzymeType.h"

namespace mzIdentML {
    namespace Generated {

        std::vector<EnzymeType*> EnzymesType::getEnzyme() const {
            return this->enzymeField;
        }

        void EnzymesType::setEnzyme(const std::vector<EnzymeType*> &value) {
            this->enzymeField = value;
        }

        bool EnzymesType::getindependent() const {
            return this->independentField;
        }

        void EnzymesType::setindependent(bool value) {
            this->independentField = value;
        }

        bool EnzymesType::getindependentSpecified() const {
            return this->independentFieldSpecified;
        }

        void EnzymesType::setindependentSpecified(bool value) {
            this->independentFieldSpecified = value;
        }
    }
}
