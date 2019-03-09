#include "TestModifications.h"
#include "../Proteomics/ModificationMotif.h"
#include "../Proteomics/ModificationWithMass.h"
#include "../Proteomics/TerminusLocalization.h"
#include "../Proteomics/Modification.h"
#include "../Chemistry/ChemicalFormula.h"
#include "../Proteomics/ModificationWithMassAndCf.h"
#include "../UsefulProteomicsDatabases/PtmListLoader.h"
#include "../Proteomics/OldSchoolModification.h"
#include "../Proteomics/ModificationSites.h"
#include "../Proteomics/ModificationCollection.h"
#include "../Chemistry/Interfaces/IHasMass.h"
#include "../Proteomics/OldSchoolModificationWithMultiplePossibilities.h"
#include "../MzLibUtil/MzLibException.h"
#include "../Proteomics/ChemicalFormulaModification.h"
#include "../Proteomics/ModificationWithLocation.h"


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

    void TestModifications::Test_modificationsHashCode() {
        ModificationMotif motif;
        ModificationMotif::TryGetMotif(L"M", motif);
        auto mod1 = new ModificationWithMass(L"mod", L"type", motif, TerminusLocalization::Any, 1, nullptr, nullptr, nullptr);
        auto mod2 = new ModificationWithMass(L"mod2", L"type", motif, TerminusLocalization::Any, 10, nullptr, nullptr, nullptr);

        Assert::AreNotEqual(mod1->GetHashCode(), mod2->GetHashCode());
        Assert::AreNotEqual(mod1, mod2);
        std::unordered_set<Modification*> myHashSet = {mod1, mod2};
        Assert::AreEqual(2, myHashSet.size());

//C# TO C++ CONVERTER TODO TASK: A 'delete mod2' statement was not added since mod2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete mod1' statement was not added since mod1 was passed to a method or constructor. Handle memory management manually.
    }

    void TestModifications::Test_ModificationWithNoMassWritten() {
        ModificationMotif motif;
        ModificationMotif::TryGetMotif(L"M", motif);
        auto mod1 = new ModificationWithMassAndCf(L"mod", L"type", motif, TerminusLocalization::Any, ChemicalFormula::ParseFormula(L"H"), std::make_optional(ChemicalFormula::ParseFormula(L"H")->getMonoisotopicMass()), nullptr, nullptr, nullptr);
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
        auto mod1string = mod1->ToString();
        Assert::IsTrue(!mod1string.find(L"MM") != std::wstring::npos);
        auto modAfterWriteRead = dynamic_cast<ModificationWithMassAndCf*>(PtmListLoader::ReadModsFromString(mod1string + L"\r\n" + L"//").front());
        Assert::AreEqual(mod1, modAfterWriteRead);

//C# TO C++ CONVERTER TODO TASK: A 'delete mod1' statement was not added since mod1 was passed to a method or constructor. Handle memory management manually.
    }

    void TestModifications::NameAndSites() {
        // Empty modification, has no name and by default has Sites = ModificationSites.Any
        OldSchoolModification *a = new OldSchoolModification();
        OldSchoolModification *b = new OldSchoolModification(a);
        Assert::AreEqual(L" (Any)", b->getNameAndSites());

        delete b;
//C# TO C++ CONVERTER TODO TASK: A 'delete a' statement was not added since a was passed to a method or constructor. Handle memory management manually.
    }

    void TestModifications::ModificationEquality() {
        // Empty modification, has no name and by default has Sites = ModificationSites.Any
        OldSchoolModification *a = new OldSchoolModification();
        OldSchoolModification *b = new OldSchoolModification();
        OldSchoolModification *c = new OldSchoolModification(0, L"c");
        OldSchoolModification *d = new OldSchoolModification(0, L"", ModificationSites::E);
        Assert::IsTrue(a->Equals(b));
        Assert::IsFalse(a->Equals(c));
        Assert::IsFalse(a->Equals(d));

//C# TO C++ CONVERTER TODO TASK: A 'delete d' statement was not added since d was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete c' statement was not added since c was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete b' statement was not added since b was passed to a method or constructor. Handle memory management manually.
        delete a;
    }

    void TestModifications::ModificationSitesTest() {
        // Empty modification, has no name and by default has Sites = ModificationSites.Any
        auto a = ModificationSites::A | ModificationSites::E;
        Assert::AreEqual(ModificationSites::A | ModificationSites::E, a);
    }

    void TestModifications::Sites() {
        // Empty modification, has no name and by default has Sites = ModificationSites.Any
        auto a = ModificationSites::A | ModificationSites::C | ModificationSites::E;
        Assert::IsTrue(a::ContainsSites(ModificationSites::E));

        Assert::IsTrue(a::ContainsSites(ModificationSites::A | ModificationSites::C));
        Assert::IsFalse(a::ContainsSites(ModificationSites::N));
        Assert::IsFalse(a::ContainsSites(ModificationSites::N | ModificationSites::C));
        auto b = a::EnumerateActiveSites();
        Assert::IsTrue(b->Count() == 3);
    }

    void TestModifications::ModificationCollectionTest() {
        OldSchoolModification tempVar(1, L"Mod1");
        ModificationCollection *a = new ModificationCollection({&tempVar, new OldSchoolModification(2, L"Mod2")});

        double lala = 0;
        System::Collections::IEnumerable *aasdf = a;
        for (auto jadfk : aasdf) {
            lala += (dynamic_cast<IHasMass*>(jadfk))->getMonoisotopicMass();
        }
        Assert::AreEqual(3, lala);

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
        Assert::AreEqual(L"Mod1 | Mod2", a->ToString());
        OldSchoolModification tempVar2(3, L"Mod3");
        a->Add(&tempVar2);
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
        Assert::AreEqual(L"Mod1 | Mod2 | Mod3", a->ToString());
        OldSchoolModification tempVar3(2, L"Mod2");
        Assert::IsTrue(a->Contains(&tempVar3));
        std::vector<IHasMass*> myArray(4);
        a->CopyTo(myArray, 1);
        Assert::AreEqual(3, myArray.Sum([&] (std::any b) {
        delete a;
            return b == nullptr ? 0 : 1;
        }));
        Assert::AreEqual(3, a->Count());
        Assert::IsFalse(a->getIsReadOnly());
        OldSchoolModification tempVar4(2, L"Mod2");
        a->Remove(&tempVar4);
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
        Assert::AreEqual(L"Mod1 | Mod3", a->ToString());
        double ok = 0;
        for (auto b : a) {
            ok += b->MonoisotopicMass;
        }
        Assert::AreEqual(4, ok);

        a->Clear();
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
        Assert::AreEqual(L"", a->ToString());

        delete a;
    }

    void TestModifications::ModificationCollectionTest2() {
        OldSchoolModification tempVar(1, L"Mod1");
        ModificationCollection *a = new ModificationCollection({&tempVar, new OldSchoolModification(2, L"Mod2")});
        OldSchoolModification tempVar2(3, L"Mod3");
        Assert::IsFalse(a->Remove(&tempVar2));

        delete a;
    }

    void TestModifications::ModificationWithMultiplePossibilitiesTest() {
        auto m = new ModificationWithMultiplePossibilitiesCollection(L"My Iso Mod", ModificationSites::E);
        OldSchoolModification tempVar(1, L"My Mod1a", ModificationSites::E);
        m->AddModification(&tempVar);
        OldSchoolModification tempVar2(2, L"My Mod2b", ModificationSites::E);
        m->AddModification(&tempVar2);
        Assert::AreEqual(2, m->size());
        Assert::AreEqual(L"My Mod2b", m[1]->Name);
        Assert::Throws<MzLibException*>([&] () {
            OldSchoolModification tempVar3(1, L"gg", ModificationSites::R);
            m->AddModification(&tempVar3);
        }, L"Unable to add a modification with sites other than ModificationSites.E");
        OldSchoolModification tempVar4(2, L"My Mod2b", ModificationSites::E);
        Assert::IsTrue(std::find(m->begin(), m->end(), &tempVar4) != m->end()));
        double kk = 0;
        System::Collections::IEnumerable *a = m;
        for (auto b : a) {
            kk += (dynamic_cast<OldSchoolModification*>(b))->MonoisotopicMass;
        }
        Assert::AreEqual(3, kk);

        delete m;
    }

    void TestModifications::ModificationSitesTest55() {
        Assert::IsTrue(ModificationSites::E::ContainsSites(ModificationSites::Any));
        Assert::IsFalse(ModificationSites::E::ContainsSites(ModificationSites::None));
        Assert::IsTrue(ModificationSites::None::ContainsSites(ModificationSites::None));
    }

    void TestModifications::ChemicalFormulaModificaiton() {
        OldSchoolChemicalFormulaModification *a = new OldSchoolChemicalFormulaModification(ChemicalFormula::ParseFormula(L"OH"));
        OldSchoolChemicalFormulaModification *b = new OldSchoolChemicalFormulaModification(a);
        Assert::AreEqual(a, b);

//C# TO C++ CONVERTER TODO TASK: A 'delete b' statement was not added since b was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete a' statement was not added since a was passed to a method or constructor. Handle memory management manually.
    }

    void TestModifications::ModificationCollectionScrambledEquals() {
        OldSchoolModification tempVar(1, L"Mod1");
        ModificationCollection *a = new ModificationCollection({&tempVar, new OldSchoolModification(2, L"Mod2")});
        OldSchoolModification tempVar2(1, L"Mod1");
        ModificationCollection *b = new ModificationCollection({&tempVar2, new OldSchoolModification(3, L"Mod3")});

        Assert::IsFalse(a->Equals(b));

//C# TO C++ CONVERTER TODO TASK: A 'delete b' statement was not added since b was passed to a method or constructor. Handle memory management manually.
        delete a;
    }

    void TestModifications::Test_modification_hash_set() {
        Modification *m1 = new Modification(L"23", L"unknown");
        Modification *m2 = new Modification(L"23", L"unknown");
        std::unordered_set<Modification*> mods = std::vector<Modification*> {m1, m2};
        Assert::AreEqual(1, mods.size());

//C# TO C++ CONVERTER TODO TASK: A 'delete m2' statement was not added since m2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete m1' statement was not added since m1 was passed to a method or constructor. Handle memory management manually.
    }

    void TestModifications::Test_modification2_hash_set() {
        ModificationMotif motif;
        ModificationMotif::TryGetMotif(L"K", motif);
        ModificationWithLocation *m1 = new ModificationWithLocation(L"id1", L"modificationType", motif, TerminusLocalization::Any, std::unordered_map<std::wstring, std::vector<std::wstring>>());
        ModificationWithLocation *m2 = new ModificationWithLocation(L"id1", L"modificationType", motif, TerminusLocalization::Any);
        m1->linksToOtherDbs.emplace(L"key", std::vector<std::wstring> {L"value"});
        m2->linksToOtherDbs.emplace(L"key", std::vector<std::wstring> {L"value"});
        std::unordered_set<Modification*> mods = std::vector<Modification*> {m1, m2};
        Assert::True(m1->Equals(m2));
        Assert::AreEqual(1, mods.size());

//C# TO C++ CONVERTER TODO TASK: A 'delete m2' statement was not added since m2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete m1' statement was not added since m1 was passed to a method or constructor. Handle memory management manually.
    }

    void TestModifications::Test_modification3_hash_set() {
        ModificationMotif motif;
        ModificationMotif::TryGetMotif(L"K", motif);
        ModificationWithMass *m1 = new ModificationWithMass(L"id1", L"modificationType", motif, TerminusLocalization::Any, 1.11111, std::unordered_map<std::wstring, std::vector<std::wstring>>(), neutralLosses: {2.222222}, diagnosticIons: std::vector<double> {1.2233});
        ModificationWithMass *m2 = new ModificationWithMass(L"id1", L"modificationType", motif, TerminusLocalization::Any, 1.11111 - 1e-10, std::unordered_map<std::wstring, std::vector<std::wstring>>(), neutralLosses: {2.222222 + 1e-10}, diagnosticIons: std::vector<double> {1.2233});
        m1->linksToOtherDbs.emplace(L"key", std::vector<std::wstring> {L"value"});
        m2->linksToOtherDbs.emplace(L"key", std::vector<std::wstring> {L"value"});
        std::unordered_set<Modification*> mods = std::vector<Modification*> {m1, m2};
        Assert::AreEqual(1, mods.size());
        Assert::True(m1->Equals(m2));

//C# TO C++ CONVERTER TODO TASK: A 'delete m2' statement was not added since m2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete m1' statement was not added since m1 was passed to a method or constructor. Handle memory management manually.
    }
}
