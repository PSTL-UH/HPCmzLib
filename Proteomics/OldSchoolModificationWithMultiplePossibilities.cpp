#include "OldSchoolModificationWithMultiplePossibilities.h"
#include "../MzLibUtil/MzLibException.h"

using namespace MzLibUtil;

namespace Proteomics {

    ModificationWithMultiplePossibilitiesCollection::ModificationWithMultiplePossibilitiesCollection(const std::wstring &name, ModificationSites sites) : OldSchoolModification(0, name, sites), _modifications(new SortedList<double, OldSchoolModification*>()) {
    }

    int ModificationWithMultiplePossibilitiesCollection::getCount() const {
        return _modifications->Count;
    }

    OldSchoolModification *ModificationWithMultiplePossibilitiesCollection::operator [](int index) {
        return _modifications->Values[index];
    }

    void ModificationWithMultiplePossibilitiesCollection::AddModification(OldSchoolModification *modification) {
        if (!getSites()::ContainsSites(modification->getSites())) {
            throw MzLibException(L"Unable to add a modification with sites other than " + getSites());
        }

        _modifications->Add(modification->MonoisotopicMass, modification);
    }

    bool ModificationWithMultiplePossibilitiesCollection::Contains(OldSchoolModification *modification) {
        return _modifications->ContainsValue(modification);
    }

    IEnumerator<OldSchoolModification*> *ModificationWithMultiplePossibilitiesCollection::GetEnumerator() {
        return _modifications->Values->begin();
    }

    System::Collections::IEnumerator *ModificationWithMultiplePossibilitiesCollection::IEnumerable_GetEnumerator() {
        return _modifications->Values->begin();
    }
}
