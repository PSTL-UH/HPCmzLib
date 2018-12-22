#include "TestAminoAcids.h"
#include "../Proteomics/Residue.h"

using namespace NUnit::Framework;
using namespace Proteomics;

namespace Test {

    void TestAminoAcids::GetResidueByCharacter() {
        Residue *aa = Residue::GetResidue(L'A');

        Assert::AreEqual(L"Alanine", aa->getName());
    }

    void TestAminoAcids::GetResidueByCharacterString() {
        Residue *aa = Residue::GetResidue(L"A");

        Assert::AreEqual(aa->getName(), L"Alanine");
    }

    void TestAminoAcids::GetResidueByName() {
        Residue *aa = Residue::GetResidue(L"Alanine");

        Assert::AreEqual(L"Alanine", aa->getName());
    }

    void TestAminoAcids::GetResidueNotInDictionary() {
        Residue r;
        Assert::IsFalse(Residue::TryGetResidue(L"?", r));
        Assert::IsFalse(Residue::TryGetResidue(L'?', r));
    }

    void TestAminoAcids::ResidueMonoisotopicMassTest() {
        Assert::AreEqual(Residue::ResidueMonoisotopicMass[L'A'], Residue::GetResidue(L'A')->getMonoisotopicMass(), 1e-9);
    }
}
