#include "OldSchoolModification.h"

using namespace Chemistry;

namespace Proteomics {

    OldSchoolModification::OldSchoolModification(const OldSchoolModification &modification) : OldSchoolModification(modification->MonoisotopicMass, modification->Name, modification->getSites()) {
    }

    OldSchoolModification::OldSchoolModification() : OldSchoolModification(0.0, "", ModificationSites::Any) {
    }

    OldSchoolModification::OldSchoolModification(double monoMass) : OldSchoolModification(monoMass, "", ModificationSites::Any) {
    }

    OldSchoolModification::OldSchoolModification(double monoMass, const std::string &name) : OldSchoolModification(monoMass, name, ModificationSites::Any) {
    }

    OldSchoolModification::OldSchoolModification(double monoMass, const std::string &name, ModificationSites sites) {
        setMonoisotopicMass(monoMass);
        setName(name);
        setSites(sites);
    }

    std::string OldSchoolModification::getName() const {
        return privateName;
    }

    void OldSchoolModification::setName(const std::string &value) {
        privateName = value;
    }

    double OldSchoolModification::getMonoisotopicMass() const {
        return privateMonoisotopicMass;
    }

    void OldSchoolModification::setMonoisotopicMass(double value) {
        privateMonoisotopicMass = value;
    }

    ModificationSites OldSchoolModification::getSites() const {
        return privateSites;
    }

    void OldSchoolModification::setSites(ModificationSites value) {
        privateSites = value;
    }

    std::string OldSchoolModification::getNameAndSites() const {
        return std::string::Format(CultureInfo::InvariantCulture, "{0} ({1})", getName(), getSites());
    }

    std::string OldSchoolModification::ToString() {
        return getName();
    }

    int OldSchoolModification::GetHashCode() {
        return getMonoisotopicMass().GetHashCode();
    }

    bool OldSchoolModification::Equals(std::any obj) {
        OldSchoolModification *modObj = dynamic_cast<OldSchoolModification*>(obj);
        return modObj != nullptr && Equals(modObj);
    }

    bool OldSchoolModification::Equals(OldSchoolModification *other) {
        if (ReferenceEquals(this, other)) {
            return true;
        }

        if (std::abs(getMonoisotopicMass() - other->getMonoisotopicMass()) > 1e-9) {
            return false;
        }

        if (getName() != other->getName()) {
            return false;
        }

        if (!getSites().Equals(other->getSites())) {
            return false;
        }

        return true;
    }
}
