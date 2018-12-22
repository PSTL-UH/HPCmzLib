#include "TestFragments.h"
#include "../Proteomics/Peptide.h"
#include "../Proteomics/Fragment.h"
#include "../Proteomics/FragmentTypes.h"
#include "../Chemistry/ChemicalFormula.h"
#include "../Proteomics/ChemicalFormulaModification.h"
#include "../Proteomics/ModificationSites.h"
#include "../Proteomics/OldSchoolModification.h"
#include "../Proteomics/ChemicalFormulaFragment.h"
#include "../Chemistry/Interfaces/IHasChemicalFormula.h"
#include "../Proteomics/Interfaces/IProtease.h"
#include "TestPeptides.h"
#include "../Proteomics/AminoAcidPolymer.h"
#include "../MzLibUtil/MzLibException.h"

using namespace Chemistry;
using namespace MzLibUtil;
using namespace NUnit::Framework;
using namespace Proteomics;

namespace Test {

    void TestFragments::SetUp() {
        _mockPeptideEveryAminoAcid = new Peptide(L"ACDEFGHIKLMNPQRSTVWY");
    }

    void TestFragments::FragmentNumberToHigh() {
        Assert::Throws<std::out_of_range>([&] () {
            _mockPeptideEveryAminoAcid->Fragment(FragmentTypes::b, 25).ToList();
        });
    }

    void TestFragments::FragmentName() {
        Fragment *fragment = _mockPeptideEveryAminoAcid->Fragment(FragmentTypes::a, 1).ToArray()[0];

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
        Assert::AreEqual(L"a1", fragment->ToString());
    }

    void TestFragments::FragmentAllBIons() {
        std::vector<Fragment*> fragments = _mockPeptideEveryAminoAcid->Fragment(FragmentTypes::b).ToList();

        Assert::AreEqual(19, fragments.size());
    }

    void TestFragments::FragmentAnotherTest() {
        std::vector<Fragment*> fragments = _mockPeptideEveryAminoAcid->Fragment(FragmentTypes::b, 1, 2).ToList();

        Assert::AreEqual(2, fragments.size());
    }

    void TestFragments::FragmentNTermModTest() {
        OldSchoolChemicalFormulaModification tempVar(ChemicalFormula::ParseFormula(L"O"), L"lala", ModificationSites::NTerminus);
        _mockPeptideEveryAminoAcid->AddModification(&tempVar);
        Fragment *fragment = _mockPeptideEveryAminoAcid->Fragment(FragmentTypes::b, 1).front();
        Assert::IsTrue(fragment->getModifications().SequenceEqual(std::vector<OldSchoolModification*> {new OldSchoolChemicalFormulaModification(ChemicalFormula::ParseFormula(L"O"), L"lala", ModificationSites::NTerminus)}));
    }

    void TestFragments::FragmentModifications() {
        OldSchoolModification tempVar(1, L"mod1", ModificationSites::C);
        _mockPeptideEveryAminoAcid->AddModification(&tempVar);
        OldSchoolModification tempVar2(2, L"mod2", ModificationSites::D);
        _mockPeptideEveryAminoAcid->AddModification(&tempVar2);
        OldSchoolModification tempVar3(3, L"mod3", ModificationSites::A);
        _mockPeptideEveryAminoAcid->AddModification(&tempVar3);
        OldSchoolModification tempVar4(4, L"mod4", ModificationSites::Y);
        _mockPeptideEveryAminoAcid->AddModification(&tempVar4);
        Fragment *fragment = _mockPeptideEveryAminoAcid->Fragment(FragmentTypes::b, 1).front();
        Fragment *fragmentEnd = _mockPeptideEveryAminoAcid->Fragment(FragmentTypes::y, 1).back();

        Assert::IsTrue(fragment->getModifications().SequenceEqual(std::vector<OldSchoolModification*> {new OldSchoolModification(3, L"mod3", ModificationSites::A)}));

        Assert::IsTrue(fragmentEnd->getModifications().SequenceEqual(std::vector<OldSchoolModification*> {new OldSchoolModification(4, L"mod4", ModificationSites::Y)}));
    }

    void TestFragments::ChemicalFormulaFragment() {
        auto a = _mockPeptideEveryAminoAcid->Fragment(FragmentTypes::b, true);
        // Can break in 19 places
        Assert::AreEqual(19, a.size()());
        Assert::IsTrue(a.Select([&] (std::any b) {
            b::Sequence;
        })->Contains(L"ACDEFG"));

        auto y = _mockPeptideEveryAminoAcid->Fragment(FragmentTypes::y, true);
        // Can break in 19 places
        Assert::IsTrue(y.Select([&] (std::any b) {
            b::Sequence;
        })->Contains(L"TVWY"));

        auto c = _mockPeptideEveryAminoAcid->Fragment(FragmentTypes::b, true);

        Assert::AreEqual(a.front(), c.front());
    }

    void TestFragments::TestGetSiteDeterminingFragments() {
        auto pep1 = new Peptide(L"ACDEFG");
        auto pep2 = new Peptide(L"ACTVWY");
        auto ok = pep1->GetSiteDeterminingFragments(pep2, FragmentTypes::b);
        Assert::AreEqual(6, ok.size()());
        Assert->Contains(L"ACT", ok.Select([&] (std::any b) {
            b::Sequence;
        })->ToArray());

//C# TO C++ CONVERTER TODO TASK: A 'delete pep2' statement was not added since pep2 was passed to a method or constructor. Handle memory management manually.
        delete pep1;
    }

    void TestFragments::TestFormulaTerminusMods() {
        auto pep1 = new Peptide(L"ACDEFG");
        OldSchoolChemicalFormulaModification tempVar(ChemicalFormula::ParseFormula(L"H"), ModificationSites::NTerminus);
        pep1->AddModification(&tempVar);

        Assert::IsTrue(dynamic_cast<IHasChemicalFormula*>(pep1->Fragment(FragmentTypes::b, true).front()) != nullptr);

        auto pep2 = new Peptide(L"ACDEFG");
        OldSchoolModification tempVar2(2, L"haha", ModificationSites::NTerminus);
        pep2->AddModification(&tempVar2);
        Assert::IsFalse(dynamic_cast<IHasChemicalFormula*>(pep2->Fragment(FragmentTypes::b, true).front()) != nullptr);

        auto pep3 = new Peptide(L"ACDEFG");
        OldSchoolModification tempVar3(3, L"haha", ModificationSites::D);
        pep3->AddModification(&tempVar3);

        auto list = pep3->Fragment(FragmentTypes::b, true).ToList();

        Assert::IsTrue(dynamic_cast<IHasChemicalFormula*>(list[0]) != nullptr);
        Assert::IsFalse(dynamic_cast<IHasChemicalFormula*>(list[2]) != nullptr);

        delete pep3;
        delete pep2;
        delete pep1;
    }

    void TestFragments::CleavageIndicesTest() {
        std::vector<IProtease*> proteases = {new TestProtease()};
        auto ok1 = AminoAcidPolymer::GetCleavageIndexes(L"ACDEFG", proteases, true).ToList();
        auto ok2 = AminoAcidPolymer::GetCleavageIndexes(L"ACDEFG", proteases, false).ToList();
        auto ok3 = AminoAcidPolymer::GetCleavageIndexes(L"ACDE", proteases, true).ToList();
        auto ok4 = AminoAcidPolymer::GetCleavageIndexes(L"ACDE", proteases, false).ToList();
        Assert::AreEqual(3, ok1.size()());
        Assert::AreEqual(2, ok2.size()());
        Assert::AreEqual(4, ok3.size()());
        Assert::AreEqual(2, ok4.size()());
    }

    void TestFragments::TestGetIonCapFailFail() {
        FragmentTypes f = FragmentTypes::All;
        Assert::That([&] () {
            f::GetIonCap();
        }, Throws::TypeOf<MzLibException*>().With::Property(L"Message").EqualTo(L"Fragment Type must be a single value to determine the ion cap"));
    }

    void TestFragments::TestGetTerminusFail() {
        FragmentTypes f = FragmentTypes::a | FragmentTypes::adot;
        Assert::That([&] () {
            f::GetTerminus();
        }, Throws::TypeOf<MzLibException*>().With::Property(L"Message").EqualTo(L"Fragment Type must be a single value to determine the terminus"));
    }
}
