#include "FragmentTypes.h"
#include "../Chemistry/ChemicalFormula.h"
#include "../MzLibUtil/MzLibException.h"
#include <bitset>

#include "../Chemistry/Chemistry.h"
using namespace Chemistry;
#include "MzLibUtil.h"
using namespace MzLibUtil;

namespace Proteomics {
    namespace AminoAcidPolymer {

        const std::vector<FragmentTypes> FragmentTypesExtension::FragmentTypesValues = { FragmentTypes::None,
                                                                                         FragmentTypes::a,
                                                                                         FragmentTypes::adot,
                                                                                         FragmentTypes::b,
                                                                                         FragmentTypes::bdot,
                                                                                         FragmentTypes::c,
                                                                                         FragmentTypes::cdot,
                                                                                         FragmentTypes::x,
                                                                                         FragmentTypes::xdot,
                                                                                         FragmentTypes::y,
                                                                                         FragmentTypes::ydot,
                                                                                         FragmentTypes::z,
                                                                                         FragmentTypes::zdot,
                                                                                         FragmentTypes::Internal,
                                                                                         FragmentTypes::All
        };

        const std::vector<std::string> FragmentTypesExtension::FragmentTypesNames = { "None",
                                                                                      "a", "adot",
                                                                                      "b", "bdot",
                                                                                      "c","cdot",
                                                                                      "x", "xdot",
                                                                                      "y", "ydot",
                                                                                      "z", "zdot"
                                                                                      "Internal", "All"
        };
        
        const std::unordered_map<FragmentTypes, ChemicalFormula*> FragmentTypesExtension::FragmentIonCaps = std::unordered_map<FragmentTypes, ChemicalFormula*> {
            {FragmentTypes::a, ChemicalFormula::ParseFormula("C-1H-1O-1")},
            {FragmentTypes::adot, ChemicalFormula::ParseFormula("C-1O-1")},
            {FragmentTypes::b, ChemicalFormula::ParseFormula("H-1")},
            {FragmentTypes::bdot, new ChemicalFormula()},
            {FragmentTypes::c, ChemicalFormula::ParseFormula("NH2")},
            {FragmentTypes::cdot, ChemicalFormula::ParseFormula("NH3")},
            {FragmentTypes::x, ChemicalFormula::ParseFormula("COH-1")},
            {FragmentTypes::xdot, ChemicalFormula::ParseFormula("CO")},
            {FragmentTypes::y, ChemicalFormula::ParseFormula("H")},
            {FragmentTypes::ydot, ChemicalFormula::ParseFormula("H2")},
            {FragmentTypes::z, ChemicalFormula::ParseFormula("N-1H-2")},
            {FragmentTypes::zdot, ChemicalFormula::ParseFormula("N-1H-1")}
        };
        
        std::vector<FragmentTypes> FragmentTypesExtension::GetIndividualFragmentTypes(FragmentTypes fragmentTypes) {
            std::vector<FragmentTypes> vf;
            for (auto site : GetValues()) {
                if (site == FragmentTypes::None || site == FragmentTypes::All || site == FragmentTypes::Internal) {
                    continue;
                }
                std::bitset<32> bsite((int)site);
                std::bitset<32> bfrag((int)fragmentTypes);
                if ((bfrag & bsite) == bsite) {
                    //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                    // yield return site;
                    vf.push_back(site);
                }
            }
            return vf;
        }
        
        Terminus FragmentTypesExtension::GetTerminus(FragmentTypes fragmentType) {
            // Super handy: http://stackoverflow.com/questions/4624248/c-logical-riddle-with-bit-operations-only-one-bit-is-set
            std::bitset<32> bfrag((int)fragmentType);
            std::bitset<32> bfrag2(((int)fragmentType)-1);
            std::bitset<32> bnone((int)FragmentTypes::None);
            
            if (fragmentType == FragmentTypes::None || (bfrag & bfrag2) != bnone) {
                throw MzLibException("Fragment Type must be a single value to determine the terminus");
            }
            return fragmentType >= FragmentTypes::x ? Terminus::C : Terminus::N;
        }
        
        ChemicalFormula *FragmentTypesExtension::GetIonCap(FragmentTypes fragmentType)  {
            std::bitset<32> bfrag((int)fragmentType);
            std::bitset<32> bfrag2(((int)fragmentType)-1);
            std::bitset<32> bnone((int)FragmentTypes::None);
            if (fragmentType == FragmentTypes::None || (bfrag & bfrag2) != bnone) {
                throw MzLibException("Fragment Type must be a single value to determine the ion cap");
            }
            
            return FragmentIonCaps.find(fragmentType)->second;
        }
    

        // Added by Edgar for the C++ version 
        std::vector<AminoAcidPolymer::FragmentTypes> FragmentTypesExtension::GetValues(){
            return AminoAcidPolymer::FragmentTypesExtension::FragmentTypesValues;
        }

        std::vector<std::string> FragmentTypesExtension::GetNames(){
            return AminoAcidPolymer::FragmentTypesExtension::FragmentTypesNames;
        }
        std::string FragmentTypesExtension::GetName( AminoAcidPolymer::FragmentTypes fragmentType){
            std::string defstring; // empty string
            int i=0;
            for (  auto f: GetValues() ) {
                if ( f == fragmentType ) {
                    return AminoAcidPolymer::FragmentTypesExtension::FragmentTypesNames[i];
                }
                i++;
            }
            return defstring;
        }
    }
}
