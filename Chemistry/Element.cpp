#include "Element.h"
#include "Isotope.h"
#include "PeriodicTable.h"
#include "../MzLibUtil/MzLibException.h"

#include "MzLibUtil.h"
using namespace MzLibUtil;

namespace Chemistry {

    Element::Element(const std::wstring &symbol, int atomicNumber, double averageMass) {
        privateAtomicSymbol = symbol;
        privateAtomicNumber = atomicNumber;
        privateAverageMass = averageMass;
    }

    std::vector<Isotope*> Element::getIsotopes() const {
        std::vector<Isotope*> tmpvector;
        for (auto i : IsotopesInOrderTheyWereAdded) {
            if (i != nullptr) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
//                yield return i;
                tmpvector.push_back(i);
            }
            else {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
//                yield break;
                break;
            }
        }
        return tmpvector;
    }

    int Element::getAtomicNumber() const {
        return privateAtomicNumber;
    }

    std::wstring Element::getAtomicSymbol() const {
        return privateAtomicSymbol;
    }

    double Element::getAverageMass() const {
        return privateAverageMass;
    }

    Isotope *Element::getPrincipalIsotope() const {
        return privatePrincipalIsotope;
    }

    void Element::setPrincipalIsotope(Isotope *value) {
        privatePrincipalIsotope = value;
    }

    int Element::getProtons() const {
        return getAtomicNumber();
    }

    Isotope *Element::operator [](int massNumber) {
        return IsotopesByMassNumber[massNumber];
    }

//C# TO C++ CONVERTER TODO TASK: C++ cast operators must convert from the enclosing type to another type:
//    Element::operator Element*(int atomicNumber) {
//        return PeriodicTable::GetElement(atomicNumber);
//    }

//C# TO C++ CONVERTER TODO TASK: C++ cast operators must convert from the enclosing type to another type:
//    Element::operator Element*(const std::wstring &atomicSymbol) {
//        return PeriodicTable::GetElement(atomicSymbol);
//    }

    std::wstring Element::ToString() {
        return getAtomicSymbol();
    }

    void Element::AddIsotope(int massNumber, double atomicMass, double abundance) {
        if (IsotopesByMassNumber[massNumber] != nullptr) {
            throw MzLibException(L"Isotope with mass number " + std::to_wstring(massNumber) + L" already exists!");
        }
        auto isotope = new Isotope(this, massNumber, atomicMass, abundance);
        IsotopesByMassNumber[massNumber] = isotope;
        int ok = 0;
        while (IsotopesInOrderTheyWereAdded[ok] != nullptr) {
            ok++;
        }
        IsotopesInOrderTheyWereAdded[ok] = isotope;
        if (getPrincipalIsotope() == nullptr || (abundance > getPrincipalIsotope()->getRelativeAbundance())) {
            setPrincipalIsotope(isotope);
        }

//C# TO C++ CONVERTER TODO TASK: A 'delete isotope' statement was not added since isotope was assigned to another object. Handle memory management manually.
    }
}
