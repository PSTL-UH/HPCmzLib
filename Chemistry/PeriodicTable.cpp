﻿#include "PeriodicTable.h"
#include "Element.h"


namespace Chemistry {

const std::unordered_map<std::wstring, Element*> PeriodicTable::_elements = std::unordered_map<std::wstring, Element*>();
std::vector<Element*> const PeriodicTable::_elementsArray = std::vector<Element*>(Constants::MaximumNumberOfElementsAllowed);

    void PeriodicTable::Add(Element *element) {
        if (_elements.find(element->getAtomicSymbol()) == _elements.end()) {
            _elements.emplace(element->getAtomicSymbol(), element);
            _elementsArray[element->getAtomicNumber()] = element;
        }
    }

    Element *PeriodicTable::GetElement(const std::wstring &atomicSymbol) {
        return _elements[atomicSymbol];
    }

    Element *PeriodicTable::GetElement(int atomicNumber) {
        return _elementsArray[atomicNumber];
    }

    bool PeriodicTable::ValidateAbundances(double epsilon) {
        for (auto e : _elements) {
            double totalAbundance = e->Value->Isotopes->Select([&] (std::any b) {
                b::RelativeAbundance;
            }).Sum();
            if (std::abs(totalAbundance - 1) > epsilon) {
                return false;
            }
        }
        return true;
    }

    bool PeriodicTable::ValidateAverageMasses(double epsilon) {
        for (auto e : _elements) {
            double averageMass = e->Value->Isotopes->Select([&] (std::any b) {
                return b::RelativeAbundance * b::AtomicMass;
            }).Sum();
            if (std::abs(averageMass - e->Value->AverageMass) / e->Value->AverageMass > epsilon) {
                return false;
            }
        }
        return true;
    }
}
