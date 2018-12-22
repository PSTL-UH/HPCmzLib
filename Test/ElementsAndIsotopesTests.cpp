#include "ElementsAndIsotopesTests.h"
#include "../Chemistry/Element.h"
#include "../Chemistry/Isotope.h"
#include "../Chemistry/PeriodicTable.h"

using namespace Chemistry;
using namespace NUnit::Framework;

namespace Test {

    void ElementsAndIsotopesTest::AddIsotopeWithExistingMassNumber() {
        auto elementC = new Element(L"C", 6, 12.0106);
        elementC->AddIsotope(12, 12, 0.9893);
        elementC->AddIsotope(13, 13.00335483507, 0.0107);
        Isotope *isotope = elementC[13];
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
        Assert::AreEqual(L"C{13}", isotope->ToString());
        Assert::AreEqual(6, isotope->getProtons());
        Assert::AreEqual(7, isotope->getNeutrons());

        delete elementC;
    }

    void ElementsAndIsotopesTest::AddingExistingElementsTest() {
        auto elementC = new Element(L"GGG", 127, 12.0106);
        PeriodicTable::Add(elementC);

//C# TO C++ CONVERTER TODO TASK: A 'delete elementC' statement was not added since elementC was passed to a method or constructor. Handle memory management manually.
    }
}
