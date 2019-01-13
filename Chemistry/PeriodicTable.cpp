#include "PeriodicTable.h"
#include "Element.h"
#include "Isotope.h"
#include <any>

namespace Chemistry {

std::unordered_map<std::string, Element*> PeriodicTable::_elements = std::unordered_map<std::string, Element*>();
std::vector<Element*> PeriodicTable::_elementsArray = std::vector<Element*>(Constants::MaximumNumberOfElementsAllowed);

    void PeriodicTable::Add(Element *element) {
        if (_elements.find(element->getAtomicSymbol()) == _elements.end()) {
            _elements.emplace(element->getAtomicSymbol(), element);
            _elementsArray[element->getAtomicNumber()] = element;
        }
    }

    Element *PeriodicTable::GetElement(const std::string &atomicSymbol) {
        return _elements[atomicSymbol];
    }

    Element *PeriodicTable::GetElement(int atomicNumber) {
        return _elementsArray[atomicNumber];
    }

    bool PeriodicTable::ValidateAbundances(double epsilon) {
        for (auto e : _elements) {
#ifdef ORIG
            double totalAbundance = e->Value->Isotopes->Select([&] (std::any b) {
                b::RelativeAbundance;
            }).Sum();
#endif
            double totalAbundance =0.0;
            for ( auto b: e.second->getIsotopes() ) {
                totalAbundance += b->getRelativeAbundance();
            }
            if (std::abs(totalAbundance - 1) > epsilon) {
                return false;
            }
        }
        return true;
    }

    bool PeriodicTable::ValidateAverageMasses(double epsilon) {
        for (auto e : _elements) {
#ifdef ORIG
            double averageMass = e->Value->Isotopes->Select([&] (std::any b) {
                return b::RelativeAbundance * b::AtomicMass;
            }).Sum();
#endif
            double averageMass = 0.0;
            for ( auto b: e.second->getIsotopes() ){
                averageMass += b->getRelativeAbundance() * b->getAtomicMass();
            }

//            if (std::abs(averageMass - e->Value->AverageMass) / e->Value->AverageMass > epsilon) {
            if (std::abs(averageMass - e.second->getAverageMass()) / e.second->getAverageMass() > epsilon) {
                return false;
            }
        }
        
        return true;
    }
}
