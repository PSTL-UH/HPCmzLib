#include "ChemicalFormula.h"
#include "Isotope.h"
#include "Element.h"
#include "Interfaces/IHasChemicalFormula.h"
#include "../MzLibUtil/MzLibException.h"
#include "PeriodicTable.h"
#include "Constants.h"
#include <regex>
#include <iostream>

#include <algorithm>

#include "MzLibUtil.h"
using namespace MzLibUtil;

namespace Chemistry {

//regex *const ChemicalFormula::FormulaRegex = new regex(LR"(\s*([A-Z][a-z]*)(?:\{([0-9]+)\})?(-)?([0-9]+)?\s*)", RegexOptions::Compiled);
//regex *const ChemicalFormula::ValidateFormulaRegex = new regex(L"^(" + FormulaRegex + L")+$", RegexOptions::Compiled);

    ChemicalFormula::ChemicalFormula() {
        setIsotopes(std::unordered_map<Isotope*, int>());
        setElements(std::unordered_map<Element*, int>());
    }

    ChemicalFormula::ChemicalFormula(ChemicalFormula *capFormula) {
        setIsotopes(std::unordered_map<Isotope*, int>(capFormula->getIsotopes()));
        setElements(std::unordered_map<Element*, int>(capFormula->getElements()));
    }

    double ChemicalFormula::getAverageMass() const {
#ifdef ORIG
        return getIsotopes().Sum([&] (std::any b) {
            return b::Key->AtomicMass * b->Value;
        }) + getElements().Sum([&] (std::any b) {
            return b::Key->AverageMass * b->Value;
        });
#endif
        double sum=0.0;
        for ( auto b: getIsotopes() ) {
            sum += b.first->getAtomicMass() * b.second;
        }
        for ( auto b: getElements() ) {
            sum += b.first->getAverageMass() * b.second;
        }
        return sum;
    }

    double ChemicalFormula::getMonoisotopicMass() const {
#ifdef ORIG
        return getIsotopes().Sum([&] (std::any b) {
            return b::Key->AtomicMass * b->Value;
        }) + getElements().Sum([&] (std::any b) {
            return b::Key->PrincipalIsotope.AtomicMass * b->Value;
        });
#endif
        double sum=0.0;
        for ( auto b: getIsotopes() ) {
            sum += b.first->getAtomicMass() * b.second;
        }
        for ( auto b: getElements()) {
            sum += b.first->getPrincipalIsotope()->getAtomicMass() * b.second;
        }
        return sum;
    }

    int ChemicalFormula::getAtomCount() const {
#ifdef ORIG
        return getIsotopes().Sum([&] (std::any b) {
            b->Value;
        }) + getElements().Sum([&] (std::any b) {
            b->Value;
        });
#endif
        int sum=0;
        for ( auto b: getIsotopes() ) {
            sum += b.second;
        }
        for ( auto b: getElements() ) {
            sum += b.second;
        }
        return sum;
    }

    int ChemicalFormula::getNumberOfUniqueElementsByAtomicNumber() const {
        std::unordered_set<int> ok;
        for (auto i : getIsotopes()) {
            ok.insert(i.first->getAtomicNumber());
        }
        for (auto i : getElements()) {
            ok.insert(i.first->getAtomicNumber());
        }
        return ok.size();
    }

    int ChemicalFormula::getNumberOfUniqueIsotopes() const {
        return getIsotopes().size();
    }

    std::string ChemicalFormula::getFormula() {
        if (formulaString == "") {
            formulaString = GetHillNotation();
        }
        return formulaString;
    }

    int ChemicalFormula::getProtonCount() const {
#ifdef ORIG
        return getIsotopes().Sum([&] (std::any b) {
            return b::Key->Protons * b->Value;
        }) + getElements().Sum([&] (std::any b) {
            return b::Key->Protons * b->Value;
        });
#endif
        int sum=0;
        for ( auto b: getIsotopes() ) {
            sum += b.first->getProtons() * b.second;
        }
        for ( auto b: getElements() ) {
            sum += b.first->getProtons() * b.second;
        }
        return sum;
    }

    double ChemicalFormula::getHydrogenCarbonRatio() {
        Element *carbon = PeriodicTable::GetElement("C");
        int carbonCount = CountWithIsotopes(carbon);
        Element *hydrogen = PeriodicTable::GetElement("H");
        int hydrogenCount = CountWithIsotopes(hydrogen);
        return hydrogenCount / static_cast<double>(carbonCount);
    }

    std::unordered_map<Isotope*, int> ChemicalFormula::getIsotopes() const {
        return privateIsotopes;
    }

    void ChemicalFormula::setIsotopes(const std::unordered_map<Isotope*, int> &value) {
        privateIsotopes = value;
    }

    std::unordered_map<Element*, int> ChemicalFormula::getElements() const {
        return privateElements;
    }

    void ChemicalFormula::setElements(const std::unordered_map<Element*, int> &value) {
        privateElements = value;
    }

    ChemicalFormula *ChemicalFormula::Combine(std::vector<IHasChemicalFormula*> &formulas) {
        ChemicalFormula *returnFormula = new ChemicalFormula();
        for (auto iformula : formulas) {
            returnFormula->Add(iformula);
        }

//C# TO C++ CONVERTER TODO TASK: A 'delete returnFormula' statement was not added since returnFormula was used in a 'return' or 'throw' statement.
        return returnFormula;
    }

    ChemicalFormula *ChemicalFormula::ParseFormula(const std::string &formula) {
        ChemicalFormula *f = new ChemicalFormula();

        // These two lines represent the equivalent of the Regex stored in C# shown at
        // the top of the file. There is slight difference in the syntax, but the
        // outcome should be the same based on my tests
        std::regex FormulaRegex( R"(\s*([A-Z][a-z]*)(?:\{([0-9]+)\})?(-)?([0-9]+)?\s*)");
        std::regex ValidateFormulaRegex("^(\\s*([A-Z][a-z]*)(\\{?[0-9]*\\}?)?-?[0-9]*\\s*)+$");

#if ORIG        
//        if (!ValidateFormulaRegex->IsMatch(formula)) {
#endif
        std::smatch sm;
        if ( !std::regex_match(formula, sm, ValidateFormulaRegex) ){
            delete f;
            throw MzLibException("Input string for chemical formula was in an incorrect format: " + formula);
        }

        std::sregex_iterator match(formula.begin(), formula.end(), FormulaRegex);
        std::sregex_iterator reg_end;

#ifdef ORIG
//      for (auto match : FormulaRegex->Matches(formula)) {
#endif
        for ( ; match != reg_end; ++match) {

            std::smatch res;
            std::string group = match->str();
            if ( std::regex_search(group, res, FormulaRegex) ) {
                
                std::string chemsym = res[1]; // Group 1: Chemical Symbol

                Element *element = PeriodicTable::GetElement(chemsym);

                int sign = std::stoi(res[3]) ? -1 : 1;
                int numofelem = std::stoi(res[4]) ? std::stoi(res[4]) : 1;

            if ( std::stoi(res[2]) ) { // Group 2 (optional): Isotope Mass Number
                // Adding isotope!
                f->Add(element->getIsotopeByMassNumber(std::stoi(res[2])), sign * numofelem);
            }
            else {
                // Adding element!
                f->Add(element, numofelem * sign);
            }
        }
    }

//C# TO C++ CONVERTER TODO TASK: A 'delete f' statement was not added since f was used in a 'return' or 'throw' statement.
      return f;
    }

    int ChemicalFormula::NeutronCount() {
        if (getElements().size() > 0) {
            throw MzLibException("Cannot know for sure what the number of neutrons is!");
        }
#ifdef ORIG
        return getIsotopes().Sum([&] (std::any b) {
            return b::Key->Neutrons * b->Value;
        });
#endif
        int sum = 0;
        for ( auto b: getIsotopes() ) {
            sum += b.first->getNeutrons() * b.second;
        }
        return sum;
    }

    void ChemicalFormula::Replace(Isotope *isotopeToRemove, Isotope *isotopeToAdd) {
        int numberRemoved = Remove(isotopeToRemove);
        Add(isotopeToAdd, numberRemoved);
    }

    void ChemicalFormula::Add(IHasChemicalFormula *item) {
        Add(item->getThisChemicalFormula());
    }

    void ChemicalFormula::Multiply(int multiplier) {
#ifdef ORIG
        std::vector<Element*> keys(getElements().Keys);
        for (auto key : keys) {
            getElements()[key] *= multiplier;
        }
        std::vector<Isotope*> keysIsotope(getIsotopes().Keys);
        for (auto key : keysIsotope) {
            getIsotopes()[key] *= multiplier;
        }
 #endif       
        for ( auto k: getElements() ) {
            k.second *= multiplier;
        }
        for ( auto k: getIsotopes() ) {
            k.second *= multiplier;
        }
    }

    void ChemicalFormula::Add(ChemicalFormula *formula) {
        for (auto e : formula->getElements()) {
            Add(e.first, e.second);
        }
        for (auto i : formula->getIsotopes()) {
            Add(i.first, i.second);
        }
    }

    void ChemicalFormula::AddPrincipalIsotopesOf(Element *element, int count) {
        Isotope *isotope = element->getPrincipalIsotope();
        Add(isotope, count);
    }

    void ChemicalFormula::Add(Element *element, int count) {
        if (count == 0) {
            return;
        }
        if (getElements().find(element) == getElements().end()) {
            getElements().emplace(element, count);
        }
        else {
            getElements()[element] += count;
            if (getElements()[element] == 0) {
                getElements().erase(element);
            }
        }
        formulaString = "";
    }

    void ChemicalFormula::Add(Isotope *isotope, int count) {
        if (count == 0) {
            return;
        }
        if (getIsotopes().find(isotope) == getIsotopes().end()) {
            getIsotopes().emplace(isotope, count);
        }
        else {
            getIsotopes()[isotope] += count;
            if (getIsotopes()[isotope] == 0) {
                getIsotopes().erase(isotope);
            }
        }
        formulaString = "";
    }

    void ChemicalFormula::Remove(IHasChemicalFormula *item) {
        Remove(item->getThisChemicalFormula());
    }

    void ChemicalFormula::Remove(ChemicalFormula *formula) {
        for (auto e : formula->getElements()) {
            Remove(e.first, e.second);
        }
        for (auto i : formula->getIsotopes()) {
            Remove(i.first, i.second);
        }
    }

    void ChemicalFormula::Remove(Element *element, int count) {
        Add(element, -count);
    }

    void ChemicalFormula::Remove(Isotope *isotope, int count) {
        Add(isotope, -count);
    }

    int ChemicalFormula::Remove(Isotope *isotope) {
        int count = getIsotopes()[isotope];
        Add(isotope, -count);
        return count;
    }

    int ChemicalFormula::RemoveIsotopesOf(Element *element) {
        int count = getElements()[element];
        Add(element, -count);
        for (auto k : getIsotopes() ) {
            if ( k.first->getElement() == element ) {
                getIsotopes().erase(k.first);
            }
        }
        return count;
    }

    void ChemicalFormula::Clear() {
        setIsotopes(std::unordered_map<Isotope*, int>());
        setElements(std::unordered_map<Element*, int>());
        formulaString = "";
    }

    bool ChemicalFormula::ContainsIsotopesOf(Element *element) {
        return CountWithIsotopes(element) != 0;
    }

    bool ChemicalFormula::IsSubsetOf(ChemicalFormula *formula) {
        return formula->IsSupersetOf(this);
    }

    bool ChemicalFormula::IsSupersetOf(ChemicalFormula *formula) {
        for (auto aa : formula->getElements()) {
            if (getElements().find(aa.first) == getElements().end() ||
                aa.second > getElements()[aa.first]) {
                return false;
            }
        }
        for (auto aa : formula->getIsotopes()) {
            if (getIsotopes().find(aa.first) == getIsotopes().end() ||
                aa.second > getIsotopes()[aa.first]) {
                return false;
            }
        }
        return true;
    }

    bool ChemicalFormula::ContainsSpecificIsotope(Element *element, int atomicNumber) {
        return CountSpecificIsotopes(element, atomicNumber) != 0;
    }

    bool ChemicalFormula::ContainsSpecificIsotope(Isotope *isotope) {
        return CountSpecificIsotopes(isotope) != 0;
    }

    int ChemicalFormula::CountSpecificIsotopes(Isotope *isotope) {
        int isotopeCount=0;
        std::unordered_map<Isotope*, int>::const_iterator Is_iter = getIsotopes().find(isotope);
        if (Is_iter != getIsotopes().end() ) {
            isotopeCount = Is_iter->second;
        }
        return isotopeCount;
    }

    int ChemicalFormula::CountWithIsotopes(Element *element) {
#ifdef ORIG
        auto isotopeCount = element->getIsotopes().Sum([&] (std::any isotope) {
            CountSpecificIsotopes(isotope);
        });
#endif
        int isotopeCount=0;
        for ( auto isotope : element->getIsotopes() ) {
            isotopeCount += CountSpecificIsotopes(isotope);
        }
        
        int ElementCount=0;
        std::unordered_map<Element*, int>::const_iterator El_iter = getElements().find(element);
        if (El_iter != getElements().end() ) {
            ElementCount = El_iter->second;
        }
        return isotopeCount + ElementCount;
    }

    int ChemicalFormula::CountSpecificIsotopes(Element *element, int massNumber) {
#ifdef ORIG
        Isotope *isotope = PeriodicTable::GetElement(massNumber);
        return CountSpecificIsotopes(isotope);
#endif
        // Not sure how to convert from an Element* to an Isotope*
        std::cout << "EG WARNING: The routine mzLib ChemicalFormula::CountWithIsotopes(Element*, massnumber) is not implemented CORRECTLY in the C++ version" << std::endl;
        return 0;
    }

    int ChemicalFormula::GetHashCode() {
#ifdef ORIG
        return std::make_tuple(getIsotopes().Sum([&] (std::any b) {
            return b::Key->AtomicMass * b->Value;
        }), getElements().Sum([&] (std::any b) {
            return b::Key->AverageMass * b->Value;
        }))->GetHashCode();
#endif
        double is_sum=0.0;
        for ( auto i : getIsotopes() ){
            is_sum += i.first->getAtomicMass() * i.second;           
        }
        double el_sum=0.0;
        for ( auto e: getElements() ) {
            el_sum += e.first->getAverageMass() * e.second;
        }
        return StringHelper::GetHashCode(std::tuple<std::string, std::string> {std::to_string(is_sum), std::to_string(el_sum)});
    }

    bool ChemicalFormula::Equals(ChemicalFormula *other) {
        if (other == nullptr) {
            return false;
        }
        if ( this == other) {
            return true;
        }
        if (std::abs(getMonoisotopicMass() - other->getMonoisotopicMass()) > 1e-9) {
            return false;
        }
        if (std::abs(getAverageMass() - other->getAverageMass()) > 1e-9) {
            return false;
        }
        return true;
    }

    std::string ChemicalFormula::GetHillNotation() {
        StringBuilder *s = new StringBuilder();

        // Find carbons
        if (getElements().find(PeriodicTable::GetElement(Constants::CarbonAtomicNumber)) != getElements().end()) {
            s->append("C" + (getElements()[PeriodicTable::GetElement(Constants::CarbonAtomicNumber)] == 1 ? "" : "" +
                             std::to_string(getElements()[PeriodicTable::GetElement(Constants::CarbonAtomicNumber)])));
        }

        // Find carbon isotopes
        for (auto i : PeriodicTable::GetElement(Constants::CarbonAtomicNumber)->getIsotopes()) {
            if (getIsotopes().find(i) != getIsotopes().end()) {
                s->append("C{" + std::to_string(i->getMassNumber()) + "}" + (getIsotopes()[i] == 1 ? "" : "" +
                                                                             std::to_string(getIsotopes()[i])));
            }
        }

        // Find hydrogens
        if (getElements().find(PeriodicTable::GetElement(Constants::HydrogenAtomicNumber)) != getElements().end()) {
            s->append("H" + (getElements()[PeriodicTable::GetElement(Constants::HydrogenAtomicNumber)] == 1 ? "" : "" +
                             std::to_string(getElements()[PeriodicTable::GetElement(Constants::HydrogenAtomicNumber)])));
        }

        // Find hydrogen isotopes
        for (auto i : PeriodicTable::GetElement(Constants::HydrogenAtomicNumber)->getIsotopes()) {
            if (getIsotopes().find(i) != getIsotopes().end()) {
                s->append("H{" + std::to_string(i->getMassNumber()) + "}" + (getIsotopes()[i] == 1 ? "" : "" +
                                                                             std::to_string(getIsotopes()[i])));
            }
        }

        std::vector<std::string> otherParts;

        // Find other elements
        for (auto i : getElements()) {
            if (i.first != PeriodicTable::GetElement(Constants::CarbonAtomicNumber) &&
                i.first != PeriodicTable::GetElement(Constants::HydrogenAtomicNumber)) {
                std::string temp = i.first->getAtomicSymbol() + (i.second == 1 ? "" : "" + i.second);
                otherParts.push_back(temp);
            }
        }

        // Find other isotopes
        for (auto i : getIsotopes()) {
            if (i.first->getElement() != PeriodicTable::GetElement(Constants::CarbonAtomicNumber) &&
                i.first->getElement() != PeriodicTable::GetElement(Constants::HydrogenAtomicNumber)) {
                std::string temp = i.first->getElement()->getAtomicSymbol() + "{" + std::to_string(i.first->getMassNumber()) +
                                   "}" + (i.second == 1 ? "" : "" + i.second);
                otherParts.push_back(temp);
            }
        }

        std::sort(otherParts.begin(), otherParts.end());

        delete s;
        std::string st;
        for ( auto sp: otherParts ){
            st += sp;
        }

        return st;
    }
}
