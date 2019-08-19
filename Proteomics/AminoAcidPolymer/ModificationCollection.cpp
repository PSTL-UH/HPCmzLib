#include <iostream>
#include <algorithm>
#include "ModificationCollection.h"
#include "../Chemistry/Chemistry.h"
#include "../MzLibUtil/ClassExtensions.h"

#include "AminoAcidPolymer.h"
#include "OldSchoolModification.h"
#include "../Modifications/Modification.h"

using namespace Chemistry;
#include "MzLibUtil.h"
using namespace MzLibUtil;

namespace Proteomics {
    namespace AminoAcidPolymer    {
    
#ifdef ORIG
        ModificationCollection::ModificationCollection(std::vector<IHasMass> &mods) : _modifications(mods::ToList()) {
            setMonoisotopicMass(_modifications.Sum([&] (std::any m) {
                        m::MonoisotopicMass;
                    }));
        }
#endif
        ModificationCollection::ModificationCollection(std::vector<IHasMass *> mods) {
            
            double msum=0.0;
            for ( auto m: mods ) {
                msum += m->getMonoisotopicMass();
                _modifications.push_back(m);
            }
            setMonoisotopicMass(msum);
        }

        std::vector<IHasMass*> ModificationCollection::getModifications() const {
            return _modifications;
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
            
            //C# TO C++ CONVERTER TODO TASK: A 'delete chemicalFormula' statement was not added
            // since chemicalFormula was used in a 'return' or 'throw' statement.
            return chemicalFormula;
        }
        
        std::string ModificationCollection::ToString() {
            StringBuilder *sb = new StringBuilder();
            for (auto mod : _modifications) {
                if ( dynamic_cast<OldSchoolModification*>(mod) != nullptr ) {
                    sb->append(((OldSchoolModification*)mod)->ToString());
                }
                else if ( dynamic_cast<Modification*>(mod) != nullptr ) {
                    sb->append(((Modification*)mod)->ToString());
                }
//                else if ( dynamic_cast<ModWithOnlyMass*>(mod) != nullptr ) {
//                    sb->append(((ModWithOnlyMass*)mod)->ToString());
//                }
                sb->append(" | ");
            }
            if (sb->length() > 0) {
                sb->remove(sb->length() - 3, 3);
            }
                        
            std::string s= sb->toString();
            delete sb;
            return s;
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
            // doesn't work this way, we cannot compare pointers, we have to look at the content.
            //return std::find(_modifications.begin(), _modifications.end(), item) != _modifications.end();
            bool IsOldSchoolMod = false;
            bool IsModification = false;
            // bool IsmodWithOnlyMass = false;
            if ( dynamic_cast<OldSchoolModification*>(item) != nullptr ) {
               IsOldSchoolMod = true;
            }
            else if ( dynamic_cast<Modification*>(item) != nullptr ) {
                IsModification = true;
            }
            // else if ( dynamic_cast<ModWithOnlyMass*>(mod) != nullptr ) {
            //   IsModWithOnlyMass = true;   
            //  }

            bool found = false;
            for ( auto mod =_modifications.begin(); mod != _modifications.end(); mod ++ ) {
                if ( IsOldSchoolMod ) {
                    if ( ((OldSchoolModification *) *mod)->Equals((OldSchoolModification *)(item) )) {
                            found = true;
                            break;
                    }
                }
                else if ( IsModification ) {
                    if ( ((Modification *) *mod)->Equals((Modification *)(item) )) {
                        found = true;
                        break;
                    }                    
                }
                //else if ( IsModWithOnlyMass ) {
                //    if ( (ModWithOnlyMass *)(mod)->Equals((ModWithOnlyMass *)(item) )) {
                //          found = true;
                //          break;
                //    }                    
                //}
           }
            return found;
        }
        
        void ModificationCollection::CopyTo(std::vector<IHasMass*> &array_Renamed, int arrayIndex) {
            // _modifications.CopyTo(array_Renamed, arrayIndex);
            for ( auto m: _modifications ) {
                array_Renamed.at(arrayIndex) = m;
                arrayIndex++;
            }

        }
        
        bool ModificationCollection::Remove(IHasMass *item) {
            // auto i = std::find (_modifications.begin(), _modifications.end(), item );
            // if ( i != _modifications.end() ){ 
            //    return false;
            // }
            bool IsOldSchoolMod = false;
            bool IsModification = false;
            // bool IsmodWithOnlyMass = false;
            if ( dynamic_cast<OldSchoolModification*>(item) != nullptr ) {
               IsOldSchoolMod = true;
            }
            else if ( dynamic_cast<Modification*>(item) != nullptr ) {
                IsModification = true;
            }
            // else if ( dynamic_cast<ModWithOnlyMass*>(mod) != nullptr ) {
            //   IsModWithOnlyMass = true;   
            //  }

            bool found = false;
            for ( auto mod =_modifications.begin(); mod != _modifications.end(); mod ++ ) {
                if ( IsOldSchoolMod ) {
                    if ( ((OldSchoolModification *) *mod)->Equals((OldSchoolModification *)(item) )) {
                        _modifications.erase(std::remove(_modifications.begin(), _modifications.end(), *mod), _modifications.end());
                        found = true;
                        break;
                    }
                }
                else if ( IsModification ) {
                    if ( ((Modification *) *mod)->Equals((Modification *)(item) )) {
                        _modifications.erase(std::remove(_modifications.begin(), _modifications.end(), *mod), _modifications.end());
                        found = true;
                        break;
                    }                    
                }
                //else if ( IsModWithOnlyMass ) {
                //    if ( (ModWithOnlyMass *)(mod)->Equals((ModWithOnlyMass *)(item) )) {
                //         _modifications.erase(std::remove(_modifications.begin(), _modifications.end(), *mod), _modifications.end());
                //         break;
                //    }                    
                //}
            }
            if ( found == false) {
                return false;
            }
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
}
