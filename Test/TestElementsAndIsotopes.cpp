#include "TestElementsAndIsotopes.h"
#include "../Chemistry/Element.h"
#include "../Chemistry/Isotope.h"
#include "../Chemistry/PeriodicTable.h"
#include "../UsefulProteomicsDatabases/PeriodicTableLoader.h"

#include "Assert.h"

int main ( int argc, char **argv )
{
    
    std::cout << "PeriodicTableLoader" << std::endl;    
    const std::string elfile="elements.dat";
    const std::string &elr=elfile;
    UsefulProteomicsDatabases::PeriodicTableLoader::Load (elr);
    
    std::cout << "AddIsotopeWithExistingMassNumber" << std::endl;    
    Test::ElementsAndIsotopesTest::AddIsotopeWithExistingMassNumber();
    
    
    std::cout << "AddExistingElementsTest" << std::endl;    
    Test::ElementsAndIsotopesTest::AddingExistingElementsTest();
    
    return 0;
}


namespace Test {
    
    
    void ElementsAndIsotopesTest::AddIsotopeWithExistingMassNumber() {
        Element* elementC = new Element("C", 6, 12.0106);
        elementC->AddIsotope(12, 12, 0.9893);
        elementC->AddIsotope(13, 13.00335483507, 0.0107);
        Isotope *isotope = elementC->getIsotopeByMassNumber(13);

        std::string s("C{13}");
        Assert::AreEqual(s, isotope->ToString());
        Assert::AreEqual(6, isotope->getProtons());
        Assert::AreEqual(7, isotope->getNeutrons());

        delete elementC;
    }

    void ElementsAndIsotopesTest::AddingExistingElementsTest() {
        auto elementC = new Element("GGG", 127, 12.0106);
        PeriodicTable::Add(elementC);

    }
}
