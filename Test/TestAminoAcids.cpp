#include "TestAminoAcids.h"
#include "../Proteomics/Residue.h"
#include "../UsefulProteomicsDatabases/PeriodicTableLoader.h"

#include "Assert.h"


int main ( int argc, char **argv )
{
    
    std::cout << "PeriodicTableLoader" << std::endl;    
    const std::string elfile="elements.dat";
    const std::string &elr=elfile;
    UsefulProteomicsDatabases::PeriodicTableLoader::Load (elr);
    
//    std::cout << "AddIsotopeWithExistingMassNumber" << std::endl;    
//    Test::ElementsAndIsotopesTest::AddIsotopeWithExistingMassNumber();
    
    return 0;
}


namespace Test {

    void TestAminoAcids::GetResidueByCharacter() {
        Residue *aa = Residue::GetResidue('A');

        Assert::AreEqual("Alanine", aa->getName());
    }

    void TestAminoAcids::GetResidueByCharacterString() {
        Residue *aa = Residue::GetResidue("A");

        Assert::AreEqual(aa->getName(), "Alanine");
    }

    void TestAminoAcids::GetResidueByName() {
        Residue *aa = Residue::GetResidue("Alanine");

        Assert::AreEqual("Alanine", aa->getName());
    }

    void TestAminoAcids::GetResidueNotInDictionary() {
        Residue r;
        Assert::IsFalse(Residue::TryGetResidue("?", r));
        Assert::IsFalse(Residue::TryGetResidue('?', r));
    }

    void TestAminoAcids::ResidueMonoisotopicMassTest() {
        Assert::AreEqual(Residue::ResidueMonoisotopicMass['A'], Residue::GetResidue('A')->getMonoisotopicMass(), 1e-9);
    }
}
