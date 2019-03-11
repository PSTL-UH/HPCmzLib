#include "TestAminoAcids.h"
#include "../Proteomics/Residue.h"
#include "../UsefulProteomicsDatabases/PeriodicTableLoader.h"

#include "Assert.h"

using namespace Proteomics;

int main ( int argc, char **argv )
{
    int i=0;
    
    std::cout << i << ". PeriodicTableLoader" << std::endl;    
    const std::string elfile="elements.dat";
    const std::string &elr=elfile;
    UsefulProteomicsDatabases::PeriodicTableLoader::Load (elr);

    std::cout << ++i << ". Residue::StaticConstructor" << std::endl;    
    Residue::StaticConstructor ();
    
    std::cout << ++i << ". GetResidueByCharacter" << std::endl;    
    Test::TestAminoAcids::GetResidueByCharacter();
#ifdef LATER
    std::cout << ++i << ". GetResidueByCharacterString" << std::endl;    
    Test::TestAminoAcids::GetResidueByCharacterString();

    std::cout << ++i << ". GetResidueByName" << std::endl;    
    Test::TestAminoAcids::GetResidueByName();    

    std::cout << ++i << ". GetResidueNotInDictionary" << std::endl;    
    Test::TestAminoAcids::GetResidueNotInDictionary();

    std::cout << ++i << ". ResidueMonoisotopicMassTest" << std::endl;    
    Test::TestAminoAcids::ResidueMonoisotopicMassTest();
#endif

    return 0;
}


namespace Test {

    void TestAminoAcids::GetResidueByCharacter() {
        Residue *aa = Residue::GetResidue('A');
        std::string s="Alanine";
        Assert::AreEqual(s, aa->getName());
    }
#ifdef LATER
    void TestAminoAcids::GetResidueByCharacterString() {
        Residue *aa = Residue::GetResidue("A");
        std::string s="Alanine";

        Assert::AreEqual(aa->getName(), s);
    }

    void TestAminoAcids::GetResidueByName() {
        Residue *aa = Residue::GetResidue("Alanine");
        std::string s="Alanine";

        Assert::AreEqual(s, aa->getName());
    }

    void TestAminoAcids::GetResidueNotInDictionary() {
        Residue *r;
        Assert::IsFalse(Residue::TryGetResidue("?", &r));
        Assert::IsFalse(Residue::TryGetResidue('?', &r));
    }

    void TestAminoAcids::ResidueMonoisotopicMassTest() {
        double d1 = Residue::ResidueMonoisotopicMass['A'];
        double d2 = Residue::GetResidue('A')->getMonoisotopicMass();
        Assert::AreEqual(d1, d2 , 1e-9);
    }
#endif
}
