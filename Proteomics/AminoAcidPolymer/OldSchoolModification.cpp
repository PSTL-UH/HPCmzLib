#include "OldSchoolModification.h"
#include "stringhelper.h"

using namespace Chemistry;

namespace Proteomics {
    namespace AminoAcidPolymer    {

        OldSchoolModification::OldSchoolModification(OldSchoolModification *modification) : OldSchoolModification(modification->getMonoisotopicMass(), modification->getName(), modification->getSites()) {
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
            // return std::string::Format(CultureInfo::InvariantCulture, "{0} ({1})", getName(), getSites());
            Proteomics::AminoAcidPolymer::ModificationSites s = getSites();
            int si = (int) s;
            return StringHelper::formatSimple("{0} ({1})", getName(), std::to_string(si));
        }
        
        std::string OldSchoolModification::ToString() {
            return getName();
        }
        
        int OldSchoolModification::GetHashCode() {
            // return getMonoisotopicMass().GetHashCode();
            return StringHelper::GetHashCode(std::to_string(getMonoisotopicMass()));
        }
        
        // EG: Not required anymore
        //    bool OldSchoolModification::Equals(OldSchoolModification *modObj) {
        //        OldSchoolModification *modObj = dynamic_cast<OldSchoolModification*>(obj);
        //        return modObj != nullptr && Equals(modObj);
        //    }

        bool OldSchoolModification::Equals(OldSchoolModification *other) {
            if (this == other) {
                return true;
            }
            
            if (std::abs(getMonoisotopicMass() - other->getMonoisotopicMass()) > 1e-9) {
                return false;
            }
            
            if (getName() != other->getName()) {
                return false;
            }
            
#ifdef ORIG
            if (!getSites() == (other->getSites())) {
                return false;
            }
#endif
            
            return true;
        }
    }
}
