#include "ChemicalFormula.h"
#include "Isotope.h"
#include "Element.h"
#include "Interfaces/IHasChemicalFormula.h"
#include "../MzLibUtil/MzLibException.h"
#include "PeriodicTable.h"
#include "Constants.h"

#include "MzLibUtil.h"
using namespace MzLibUtil;

namespace Chemistry {

Regex *const ChemicalFormula::FormulaRegex = new Regex(LR"(\s*([A-Z][a-z]*)(?:\{([0-9]+)\})?(-)?([0-9]+)?\s*)", RegexOptions::Compiled);
Regex *const ChemicalFormula::ValidateFormulaRegex = new Regex(L"^(" + FormulaRegex + L")+$", RegexOptions::Compiled);

    ChemicalFormula::ChemicalFormula() {
        setIsotopes(std::unordered_map<Isotope*, int>());
        setElements(std::unordered_map<Element*, int>());
    }

    ChemicalFormula::ChemicalFormula(const ChemicalFormula &capFormula) {
        setIsotopes(std::unordered_map<Isotope*, int>(capFormula->getIsotopes()));
        setElements(std::unordered_map<Element*, int>(capFormula->getElements()));
    }

    double ChemicalFormula::getAverageMass() const {
        return getIsotopes().Sum([&] (std::any b) {
            return b::Key->AtomicMass * b->Value;
        }) + getElements().Sum([&] (std::any b) {
            return b::Key->AverageMass * b->Value;
        });
    }

    double ChemicalFormula::getMonoisotopicMass() const {
        return getIsotopes().Sum([&] (std::any b) {
            return b::Key->AtomicMass * b->Value;
        }) + getElements().Sum([&] (std::any b) {
            return b::Key->PrincipalIsotope.AtomicMass * b->Value;
        });
    }

    int ChemicalFormula::getAtomCount() const {
        return getIsotopes().Sum([&] (std::any b) {
            b->Value;
        }) + getElements().Sum([&] (std::any b) {
            b->Value;
        });
    }

    int ChemicalFormula::getNumberOfUniqueElementsByAtomicNumber() const {
        std::unordered_set<int> ok;
        for (auto i : getIsotopes()) {
            ok.insert(i.Key->AtomicNumber);
        }
        for (auto i : getElements()) {
            ok.insert(i.Key->AtomicNumber);
        }
        return ok.size();
    }

    int ChemicalFormula::getNumberOfUniqueIsotopes() const {
        return getIsotopes().size();
    }

    std::wstring ChemicalFormula::getFormula() const {
        if (formulaString == L"") {
            formulaString = GetHillNotation();
        }
        return formulaString;
    }

    int ChemicalFormula::getProtonCount() const {
        return getIsotopes().Sum([&] (std::any b) {
            return b::Key->Protons * b->Value;
        }) + getElements().Sum([&] (std::any b) {
            return b::Key->Protons * b->Value;
        });
    }

    double ChemicalFormula::getHydrogenCarbonRatio() const {
        int carbonCount = CountWithIsotopes(L"C");
        int hydrogenCount = CountWithIsotopes(L"H");
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

    ChemicalFormula *ChemicalFormula::ParseFormula(const std::wstring &formula) {
        ChemicalFormula *f = new ChemicalFormula();

        if (!ValidateFormulaRegex->IsMatch(formula)) {
            delete f;
            throw MzLibException(L"Input string for chemical formula was in an incorrect format: " + formula);
        }

        for (auto match : FormulaRegex->Matches(formula)) {
            std::wstring chemsym = match->Groups[1]->Value; // Group 1: Chemical Symbol

            Element *element = PeriodicTable::GetElement(chemsym);

            int sign = match->Groups[3].Success ? -1 : 1;

            int numofelem = match->Groups[4].Success ? std::stoi(match->Groups[4]->Value, CultureInfo::InvariantCulture) : 1;

            if (match->Groups[2].Success) { // Group 2 (optional): Isotope Mass Number
                // Adding isotope!
                f->Add(element[std::stoi(match->Groups[2]->Value, CultureInfo::InvariantCulture)], sign * numofelem);
            }
            else {
                // Adding element!
                f->Add(element, numofelem * sign);
            }
        }

//C# TO C++ CONVERTER TODO TASK: A 'delete f' statement was not added since f was used in a 'return' or 'throw' statement.
        return f;
    }

    int ChemicalFormula::NeutronCount() {
        if (getElements().size() > 0) {
            throw MzLibException(L"Cannot know for sure what the number of neutrons is!");
        }
        return getIsotopes().Sum([&] (std::any b) {
            return b::Key->Neutrons * b->Value;
        });
    }

    void ChemicalFormula::Replace(Isotope *isotopeToRemove, Isotope *isotopeToAdd) {
        int numberRemoved = Remove(isotopeToRemove);
        Add(isotopeToAdd, numberRemoved);
    }

    void ChemicalFormula::Add(IHasChemicalFormula *item) {
        Add(item->getThisChemicalFormula());
    }

    void ChemicalFormula::Multiply(int multiplier) {
        std::vector<Element*> keys(getElements().Keys);
        for (auto key : keys) {
            getElements()[key] *= multiplier;
        }
        std::vector<Isotope*> keysIsotope(getIsotopes().Keys);
        for (auto key : keysIsotope) {
            getIsotopes()[key] *= multiplier;
        }
    }

    void ChemicalFormula::Add(ChemicalFormula *formula) {
        for (auto e : formula->getElements()) {
            Add(e.Key, e.Value);
        }
        for (auto i : formula->getIsotopes()) {
            Add(i.Key, i.Value);
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
        formulaString = L"";
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
        formulaString = L"";
    }

    void ChemicalFormula::Remove(IHasChemicalFormula *item) {
        Remove(item->getThisChemicalFormula());
    }

    void ChemicalFormula::Remove(ChemicalFormula *formula) {
        for (auto e : formula->getElements()) {
            Remove(e.Key, e.Value);
        }
        for (auto i : formula->getIsotopes()) {
            Remove(i.Key, i.Value);
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
        for (auto k : getIsotopes().Where([&] (std::any b) {
            return b::Key->Element == element;
        }).ToList()) {
            getIsotopes().erase(k::Key);
        }
        return count;
    }

    void ChemicalFormula::Clear() {
        setIsotopes(std::unordered_map<Isotope*, int>());
        setElements(std::unordered_map<Element*, int>());
        formulaString = L"";
    }

    bool ChemicalFormula::ContainsIsotopesOf(Element *element) {
        return CountWithIsotopes(element) != 0;
    }

    bool ChemicalFormula::IsSubsetOf(ChemicalFormula *formula) {
        return formula->IsSupersetOf(this);
    }

    bool ChemicalFormula::IsSupersetOf(ChemicalFormula *formula) {
        for (auto aa : formula->getElements()) {
            if (getElements().find(aa.Key) == getElements().end() || aa.Value > getElements()[aa.Key]) {
                return false;
            }
        }
        for (auto aa : formula->getIsotopes()) {
            if (getIsotopes().find(aa.Key) == getIsotopes().end() || aa.Value > getIsotopes()[aa.Key]) {
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
        int isotopeCount;
        std::unordered_map<Isotope*, int>::const_iterator Isotopes_iterator = Isotopes.find(isotope);
        return (getIsotopes()_iterator != getIsotopes().end() ? isotopeCount : 0);
        isotopeCount = Isotopes_iterator->second;
    }

    int ChemicalFormula::CountWithIsotopes(Element *element) {
        auto isotopeCount = element->getIsotopes().Sum([&] (std::any isotope) {
            CountSpecificIsotopes(isotope);
        });
        int ElementCount;
        std::unordered_map<Element*, int>::const_iterator Elements_iterator = Elements.find(element);
        return isotopeCount + (getElements()_iterator != getElements().end() ? ElementCount : 0);
        ElementCount = Elements_iterator->second;
    }

    int ChemicalFormula::CountSpecificIsotopes(Element *element, int massNumber) {
        Isotope *isotope = element[massNumber];
        return CountSpecificIsotopes(isotope);
    }

    int ChemicalFormula::GetHashCode() {
        return std::make_tuple(getIsotopes().Sum([&] (std::any b) {
            return b::Key->AtomicMass * b->Value;
        }), getElements().Sum([&] (std::any b) {
            return b::Key->AverageMass * b->Value;
        }))->GetHashCode();
    }

    bool ChemicalFormula::Equals(ChemicalFormula *other) {
        if (other == nullptr) {
            return false;
        }
        if (ReferenceEquals(this, other)) {
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

    std::wstring ChemicalFormula::GetHillNotation() {
        StringBuilder *s = new StringBuilder();

        // Find carbons
        if (getElements().find(PeriodicTable::GetElement(Constants::CarbonAtomicNumber)) != getElements().end()) {
            s->append(L"C" + (getElements()[PeriodicTable::GetElement(Constants::CarbonAtomicNumber)] == 1 ? L"" : L"" + std::to_wstring(getElements()[PeriodicTable::GetElement(Constants::CarbonAtomicNumber)])));
        }

        // Find carbon isotopes
        for (auto i : PeriodicTable::GetElement(Constants::CarbonAtomicNumber)->getIsotopes()) {
            if (getIsotopes().find(i) != getIsotopes().end()) {
                s->append(L"C{" + std::to_wstring(i->getMassNumber()) + L"}" + (getIsotopes()[i] == 1 ? L"" : L"" + std::to_wstring(getIsotopes()[i])));
            }
        }

        // Find hydrogens
        if (getElements().find(PeriodicTable::GetElement(Constants::HydrogenAtomicNumber)) != getElements().end()) {
            s->append(L"H" + (getElements()[PeriodicTable::GetElement(Constants::HydrogenAtomicNumber)] == 1 ? L"" : L"" + std::to_wstring(getElements()[PeriodicTable::GetElement(Constants::HydrogenAtomicNumber)])));
        }

        // Find hydrogen isotopes
        for (auto i : PeriodicTable::GetElement(Constants::HydrogenAtomicNumber)->getIsotopes()) {
            if (getIsotopes().find(i) != getIsotopes().end()) {
                s->append(L"H{" + std::to_wstring(i->getMassNumber()) + L"}" + (getIsotopes()[i] == 1 ? L"" : L"" + std::to_wstring(getIsotopes()[i])));
            }
        }

        std::vector<std::wstring> otherParts;

        // Find other elements
        for (auto i : getElements()) {
            if (i.Key != PeriodicTable::GetElement(Constants::CarbonAtomicNumber) && i.Key != PeriodicTable::GetElement(Constants::HydrogenAtomicNumber)) {
                otherParts.push_back(i.Key->AtomicSymbol + (i.Value == 1 ? L"" : L"" + i.Value));
            }
        }

        // Find other isotopes
        for (auto i : getIsotopes()) {
            if (i.Key->Element != PeriodicTable::GetElement(Constants::CarbonAtomicNumber) && i.Key->Element != PeriodicTable::GetElement(Constants::HydrogenAtomicNumber)) {
                otherParts.push_back(i.Key->Element->AtomicSymbol + L"{" + i.Key->MassNumber + L"}" + (i.Value == 1 ? L"" : L"" + i.Value));
            }
        }

        std::sort(otherParts.begin(), otherParts.end());

        delete s;
        return s + std::wstring::Join(L"", otherParts);
    }
}
