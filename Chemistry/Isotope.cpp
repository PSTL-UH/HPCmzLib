#include "Isotope.h"
#include "Element.h"


namespace Chemistry {

    Isotope::Isotope(Chemistry::Element *parentElement, int massNumber, double atomicMass, double abundance) {
        privateElement = parentElement;
        privateMassNumber = massNumber;
        privateAtomicMass = atomicMass;
        privateRelativeAbundance = abundance;
    }

    int Isotope::getAtomicNumber() const {
        return getElement()->getAtomicNumber();
    }

    int Isotope::getProtons() const {
        return getElement()->getAtomicNumber();
    }

    int Isotope::getNeutrons() const {
        return getMassNumber() - getElement()->getAtomicNumber();
    }

    Chemistry::Element *Isotope::getElement() const {
        return privateElement;
    }

    double Isotope::getAtomicMass() const {
        return privateAtomicMass;
    }

    int Isotope::getMassNumber() const {
        return privateMassNumber;
    }

    double Isotope::getRelativeAbundance() const {
        return privateRelativeAbundance;
    }

    std::string Isotope::ToString() {
        std::string s = getElement()->getAtomicSymbol() + "{" + std::to_string(getMassNumber()) + "}";
        return s;
    }
}
