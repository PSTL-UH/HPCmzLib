#include <iostream>
#include <algorithm>
#include "ModificationCollection.h"
#include "../Chemistry/Chemistry.h"
#include "../MzLibUtil/ClassExtensions.h"

using namespace Chemistry;
#include "MzLibUtil.h"
using namespace MzLibUtil;

namespace Proteomics {

#ifdef ORIG
    ModificationCollection::ModificationCollection(std::vector<IHasMass> &mods) : _modifications(mods::ToList()) {
        setMonoisotopicMass(_modifications.Sum([&] (std::any m) {
            m::MonoisotopicMass;
        }));
    }
#endif
    ModificationCollection::ModificationCollection(std::vector<IHasMass *> &mods) {
        double msum=0.0;
        for ( auto m: mods ) {
            msum += m->getMonoisotopicMass();
        }
        setMonoisotopicMass(msum);
    }

    double ModificationCollection::getMonoisotopicMass() const {
        return privateMonoisotopicMass;
    }

    void ModificationCollection::setMonoisotopicMass(double value) {
        privateMonoisotopicMass = value;
    }

    int ModificationCollection::getCount() const {
        return _modifications.size();
    }

    bool ModificationCollection::getIsReadOnly() const {
        return false;
    }

    ChemicalFormula *ModificationCollection::getThisChemicalFormula() const {
        ChemicalFormula *chemicalFormula = new ChemicalFormula();
        for (auto ok : _modifications) {
            chemicalFormula->Add(dynamic_cast<IHasChemicalFormula*>(ok));
        }

//C# TO C++ CONVERTER TODO TASK: A 'delete chemicalFormula' statement was not added since chemicalFormula was used in a 'return' or 'throw' statement.
        return chemicalFormula;
    }

    std::string ModificationCollection::ToString() {
        StringBuilder *sb = new StringBuilder();
        for (auto mod : _modifications) {
            sb->append(mod);
            sb->append(" | ");
        }
        if (sb->length() > 0) {
            sb->remove(sb->length() - 3, 3);
        }

        delete sb;
        return sb->toString();
    }

    void ModificationCollection::Add(IHasMass *item) {
        _modifications.push_back(item);
        setMonoisotopicMass(getMonoisotopicMass() + item->getMonoisotopicMass());
    }

    void ModificationCollection::Clear() {
        _modifications.clear();
        setMonoisotopicMass(0);
    }

    bool ModificationCollection::Contains(IHasMass *item) {
        return std::find(_modifications.begin(), _modifications.end(), item) != _modifications.end();
    }

    void ModificationCollection::CopyTo(std::vector<IHasMass*> &array_Renamed, int arrayIndex) {
//        _modifications.CopyTo(array_Renamed, arrayIndex);
        for ( auto m: _modifications ) {
            array_Renamed.at(arrayIndex) = m;
            arrayIndex++;
        }

    }

    bool ModificationCollection::Remove(IHasMass *item) {
        auto i = std::find (_modifications.begin(), _modifications.end(), item );
        if ( i != _modifications.end() ){ 
            return false;
        }
        _modifications.erase(i);
        setMonoisotopicMass(getMonoisotopicMass() - item->getMonoisotopicMass());
        return true;
    }

    bool ModificationCollection::Equals(ModificationCollection *other) {
        return getCount() == other->getCount() &&
            MzLibUtil::ClassExtensions::ScrambledEquals(_modifications, other->_modifications);
    }

    std::vector<IHasMass*>::iterator ModificationCollection::GetEnumerator() {
        return _modifications.begin();
    }
#ifdef ORIG
    // Not implementing this one in C++
    System::Collections::IEnumerator *ModificationCollection::IEnumerable_GetEnumerator() {
        return _modifications.begin();
    }
#endif
}
