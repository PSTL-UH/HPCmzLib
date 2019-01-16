#include "FragmentTypes.h"
#include "../Chemistry/ChemicalFormula.h"
#include "../MzLibUtil/MzLibException.h"
#include <bitset>

#include "../Chemistry/Chemistry.h"
using namespace Chemistry;
#include "MzLibUtil.h"
using namespace MzLibUtil;

namespace Proteomics {

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
        
    const std::unordered_map<FragmentTypes, ChemicalFormula*> FragmentTypesExtension::FragmentIonCaps = std::unordered_map<FragmentTypes, ChemicalFormula*> {
        {FragmentTypes::a, ChemicalFormula::ParseFormula("C-1H-1O-1")}, 
        {FragmentTypes::b, ChemicalFormula::ParseFormula("H-1")}, 
        {FragmentTypes::c, ChemicalFormula::ParseFormula("NH2")}, 
        {FragmentTypes::x, ChemicalFormula::ParseFormula("COH-1")}, 
        {FragmentTypes::y, ChemicalFormula::ParseFormula("H")}, 
        {FragmentTypes::z, ChemicalFormula::ParseFormula("N-1H-2")}, 
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
//                yield return site;
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

    std::vector<FragmentTypes> GetValues(){
        return FragmentTypesExtension::FragmentTypesValues;

    }
}
