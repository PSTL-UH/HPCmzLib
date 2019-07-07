#include "Fragment.h"
#include "AminoAcidPolymer.h"
#include "Terminus.h"
#include "../MzLibUtil/MzLibUtil.h"
#include "stringhelper.h"

using namespace Chemistry;

namespace Proteomics {

    Fragment::Fragment(FragmentTypes type, int number, double monoisotopicMass, AminoAcidPolymer *parent) {
        setFragmentType(type);
        setNumber(number);
        setParent(parent);
        setMonoisotopicMass(monoisotopicMass);
    }

    double Fragment::getMonoisotopicMass() const {
        return privateMonoisotopicMass;
    }

    void Fragment::setMonoisotopicMass(double value) {
        privateMonoisotopicMass = value;
    }

    int Fragment::getNumber() const {
        return privateNumber;
    }

    void Fragment::setNumber(int value) {
        privateNumber = value;
    }

    AminoAcidPolymer *Fragment::getParent() const {
        return privateParent;
    }

    void Fragment::setParent(AminoAcidPolymer *value) {
        privateParent = value;
    }

    FragmentTypes Fragment::getFragmentType() const {
        return privateFragmentType;
    }

    void Fragment::setFragmentType(FragmentTypes value) {
        privateFragmentType = value;
    }

    std::vector<IHasMass*> Fragment::getModifications() const {
        std::vector<IHasMass*> *mods = getParent()->getModifications();
        std::vector<IHasMass*> vmods;
        if (FragmentTypesExtension::GetTerminus(getFragmentType()) == Terminus::N) {
            for (int i = 0; i <= getNumber(); i++) {
                if ( mods->at(i) != nullptr) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
//                    yield return mods[i];
                    vmods.push_back(mods->at(i));
                }
            }
        }
        else {
            int length = getParent()->getLength() + 1;
            for (int i = length - getNumber(); i <= length; i++) {
                if (mods->at(i) != nullptr) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
//                    yield return mods[i];
                    vmods.push_back(mods->at(i));
                }
            }
        }
        return vmods;
    }

    std::string Fragment::getSequence() const {
        std::string parentSeq = getParent()->getBaseSequence();
        if (FragmentTypesExtension::GetTerminus(getFragmentType()) == Terminus::N) {
            return parentSeq.substr(0, getNumber());
        }

        return parentSeq.substr(parentSeq.length() - getNumber(), getNumber());
    }

    std::string Fragment::ToString() {
//        return std::string::Format(CultureInfo::InvariantCulture, "{0}{1}", Enum::GetName(FragmentTypes::typeid, getFragmentType()), getNumber());
        return StringHelper::formatSimple("{0}{1}", FragmentTypesExtension::GetName(getFragmentType()), getNumber());
    }

    int Fragment::GetHashCode() {
        double d = getMonoisotopicMass();
        return StringHelper::GetHashCode((const char *) &d, sizeof(double));
    }

    bool Fragment::Equals(Fragment *other) {
        return getFragmentType() == other->getFragmentType() && getNumber() == other->getNumber() && std::abs(getMonoisotopicMass() - other->getMonoisotopicMass()) < 1e-9;
    }
}
