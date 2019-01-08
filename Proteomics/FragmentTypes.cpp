#include "FragmentTypes.h"
#include "../Chemistry/ChemicalFormula.h"
#include "../MzLibUtil/MzLibException.h"

using namespace Chemistry;
#include "MzLibUtil.h"
using namespace MzLibUtil;

namespace Proteomics {

const std::unordered_map<FragmentTypes, ChemicalFormula*> FragmentTypesExtension::FragmentIonCaps = std::unordered_map<FragmentTypes, ChemicalFormula*> {
    {FragmentTypes::a, ChemicalFormula::ParseFormula("C-1H-1O-1")}, {
    {FragmentTypes::b, ChemicalFormula::ParseFormula("H-1")}, {
    {FragmentTypes::c, ChemicalFormula::ParseFormula("NH2")}, {
    {FragmentTypes::x, ChemicalFormula::ParseFormula("COH-1")}, {
    {FragmentTypes::y, ChemicalFormula::ParseFormula("H")}, {
    {FragmentTypes::z, ChemicalFormula::ParseFormula("N-1H-2")}, {
    };

    std::vector<FragmentTypes> FragmentTypesExtension::GetIndividualFragmentTypes(FragmentTypes fragmentTypes) {
        for (auto site : Enum::GetValues(FragmentTypes::typeid)) {
            if (site == FragmentTypes::None || site == FragmentTypes::All || site == FragmentTypes::Internal) {
                continue;
            }
            if ((fragmentTypes & site) == site) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                yield return site;
            }
        }
    }

    Terminus FragmentTypesExtension::GetTerminus(FragmentTypes fragmentType) {
        // Super handy: http://stackoverflow.com/questions/4624248/c-logical-riddle-with-bit-operations-only-one-bit-is-set
        if (fragmentType == FragmentTypes::None || (fragmentType & (fragmentType - 1)) != FragmentTypes::None) {
            throw MzLibException("Fragment Type must be a single value to determine the terminus");
        }
        return fragmentType >= FragmentTypes::x ? Terminus::C : Terminus::N;
    }

    ChemicalFormula *FragmentTypesExtension::GetIonCap(FragmentTypes fragmentType) {
        if (fragmentType == FragmentTypes::None || (fragmentType & (fragmentType - 1)) != FragmentTypes::None) {
            throw MzLibException("Fragment Type must be a single value to determine the ion cap");
        }
        return FragmentIonCaps[fragmentType];
    }
}
