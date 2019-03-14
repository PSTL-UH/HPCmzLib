#include "TestModifications.h"
#include "../Proteomics/ModificationMotif.h"
#include "../Proteomics/ModificationWithMass.h"
#include "../Proteomics/TerminusLocalization.h"
#include "../Proteomics/Modification.h"
#include "../Chemistry/ChemicalFormula.h"
#include "../Proteomics/ModificationWithMassAndCf.h"
//#include "../UsefulProteomicsDatabases/PtmListLoader.h"
#include "../Proteomics/OldSchoolModification.h"
#include "../Proteomics/ModificationSites.h"
#include "../Proteomics/ModificationCollection.h"
#include "../Chemistry/Interfaces/IHasMass.h"
#include "../Proteomics/OldSchoolModificationWithMultiplePossibilities.h"
#include "../MzLibUtil/MzLibException.h"
#include "../Proteomics/ChemicalFormulaModification.h"
#include "../Proteomics/ModificationWithLocation.h"
#include "../UsefulProteomicsDatabases/PeriodicTableLoader.h"


#include "Assert.h"

int main ( int argc, char **argv )
{
    int i=0;
    
    std::cout << i << ". PeriodicTableLoader" << std::endl;    
    const std::string elfile="elements.dat";
    const std::string &elr=elfile;
    UsefulProteomicsDatabases::PeriodicTableLoader::Load (elr);
    
    std::cout << ++i << ". Test_modificationsHashCode " << std::endl;    
    Test::TestModifications::Test_modificationsHashCode();

#ifdef LATER
    std::cout << ++i << ". Test_ModificationWithNoMassWritten " << std::endl;    
    Test::TestModifications::Test_ModificationWithNoMassWritten();    
#endif
    std::cout << ++i << ". NameAndSites " << std::endl;    
    Test::TestModifications::NameAndSites();

    std::cout << ++i << ". ModificationEquality " << std::endl;    
    Test::TestModifications::ModificationEquality();

#ifdef LATER
    std::cout << ++i << ". ModificationSitesTest " << std::endl;    
    Test::TestModifications::ModificationSitesTest();

    std::cout << ++i << ". Sites " << std::endl;    
    Test::TestModifications::Sites();

    std::cout << ++i << ". ModificationCollectionTest " << std::endl;    
    Test::TestModifications::ModificationCollectionTest();

    std::cout << ++i << ". ModificationCollectionTest2 " << std::endl;    
    Test::TestModifications::ModificationCollectionTest2();

    std::cout << ++i << ". ModificationWithMultiplePossibilitiesTest " << std::endl;    
    Test::TestModifications::ModificationWithMultiplePossibilitiesTest();

    std::cout << ++i << ". ModificationSitesTest55 " << std::endl;    
    Test::TestModifications::ModificationSitesTest55();

    std::cout << ++i << ". ChemicalFormulaModificaiton " << std::endl;    
    Test::TestModifications::ChemicalFormulaModificaiton();

    std::cout << ++i << ". ModificationCollectionScrambledEquals " << std::endl;    
    Test::TestModifications::ModificationCollectionScrambledEquals();

    std::cout << ++i << ". Test_modification_hash_set " << std::endl;    
    Test::TestModifications::Test_modification_hash_set();

    std::cout << ++i << ". Test_modification2_hash_set " << std::endl;    
    Test::TestModifications::Test_modification2_hash_set();

    std::cout << ++i << ". Test_modification3_hash_set " << std::endl;    
    Test::TestModifications::Test_modification3_hash_set();

#endif    
    return 0;
}


namespace Test {

    void TestModifications::Test_modificationsHashCode() {
        ModificationMotif *motif;
        ModificationMotif::TryGetMotif("M", &motif);
        auto mod1 = new ModificationWithMass("mod", "type", motif, TerminusLocalization::Any, 1, nullptr, nullptr, nullptr);
        auto mod2 = new ModificationWithMass("mod2", "type", motif, TerminusLocalization::Any, 10, nullptr, nullptr, nullptr);

        Assert::AreNotEqual(mod1->GetHashCode(), mod2->GetHashCode());
        Assert::IsFalse(mod1->Equals(mod2));
        std::unordered_set<Modification*> myHashSet = {mod1, mod2};
        Assert::AreEqual((long unsigned int)2, myHashSet.size());

        delete mod2;
        delete mod1;
    }

#ifdef LATER
    void TestModifications::Test_ModificationWithNoMassWritten() {
        ModificationMotif *motif;
        ModificationMotif::TryGetMotif("M", &motif);
        auto mod1 = new ModificationWithMassAndCf("mod", "type", motif, TerminusLocalization::Any, ChemicalFormula::ParseFormula("H"), std::make_optional(ChemicalFormula::ParseFormula("H")->getMonoisotopicMass()), nullptr, nullptr, nullptr);

        auto mod1string = mod1->ToString();
        Assert::IsTrue(!mod1string.find("MM") != std::string::npos);
        auto modAfterWriteRead = dynamic_cast<ModificationWithMassAndCf*>(PtmListLoader::ReadModsFromString(mod1string + "\r\n" + "//").front());
        Assert::IsTrue(mod1->Equals( modAfterWriteRead));

        delete mod1;
    }
#endif

    void TestModifications::NameAndSites() {
        // Empty modification, has no name and by default has Sites = ModificationSites.Any
        OldSchoolModification *a = new OldSchoolModification();
        OldSchoolModification *b = new OldSchoolModification(a);
        std::string s=" (Any)";
        Assert::AreEqual(s , b->getNameAndSites());

        delete b;
        delete a;
    }

    void TestModifications::ModificationEquality() {
        // Empty modification, has no name and by default has Sites = ModificationSites.Any
        OldSchoolModification *a = new OldSchoolModification();
        OldSchoolModification *b = new OldSchoolModification();
        OldSchoolModification *c = new OldSchoolModification(0, "c");
        OldSchoolModification *d = new OldSchoolModification(0, "", ModificationSites::E);
        Assert::IsTrue(a->Equals(b));
        Assert::IsFalse(a->Equals(c));
        Assert::IsFalse(a->Equals(d));

        delete d;
        delete c;
        delete b;
        delete a;
    }

#ifdef LATER
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
        OldSchoolModification tempVar(1, "Mod1");
        ModificationCollection *a = new ModificationCollection({&tempVar, new OldSchoolModification(2, "Mod2")});

        double lala = 0;
        System::Collections::IEnumerable *aasdf = a;
        for (auto jadfk : aasdf) {
            lala += (dynamic_cast<IHasMass*>(jadfk))->getMonoisotopicMass();
        }
        Assert::AreEqual(3, lala);

        Assert::AreEqual("Mod1 | Mod2", a->ToString());
        OldSchoolModification tempVar2(3, "Mod3");
        a->Add(&tempVar2);
        Assert::AreEqual("Mod1 | Mod2 | Mod3", a->ToString());
        OldSchoolModification tempVar3(2, "Mod2");
        Assert::IsTrue(a->Contains(&tempVar3));
        std::vector<IHasMass*> myArray(4);
        a->CopyTo(myArray, 1);
        Assert::AreEqual(3, myArray.Sum([&] (std::any b) {
        delete a;
            return b == nullptr ? 0 : 1;
        }));
        Assert::AreEqual(3, a->Count());
        Assert::IsFalse(a->getIsReadOnly());
        OldSchoolModification tempVar4(2, "Mod2");
        a->Remove(&tempVar4);
        Assert::AreEqual("Mod1 | Mod3", a->ToString());
        double ok = 0;
        for (auto b : a) {
            ok += b->MonoisotopicMass;
        }
        Assert::AreEqual((double)4, ok);

        a->Clear();
        Assert::AreEqual("", a->ToString());

        delete a;
    }

    void TestModifications::ModificationCollectionTest2() {
        OldSchoolModification tempVar(1, "Mod1");
        ModificationCollection *a = new ModificationCollection({&tempVar, new OldSchoolModification(2, "Mod2")});
        OldSchoolModification tempVar2(3, "Mod3");
        Assert::IsFalse(a->Remove(&tempVar2));

        delete a;
    }

    void TestModifications::ModificationWithMultiplePossibilitiesTest() {
        auto m = new ModificationWithMultiplePossibilitiesCollection("My Iso Mod", ModificationSites::E);
        OldSchoolModification tempVar(1, "My Mod1a", ModificationSites::E);
        m->AddModification(&tempVar);
        OldSchoolModification tempVar2(2, "My Mod2b", ModificationSites::E);
        m->AddModification(&tempVar2);
        Assert::AreEqual((long unsigned int)2, m->size());
        Assert::AreEqual("My Mod2b", m[1]->Name);
        Assert::Throws<MzLibException*>([&] () {
            OldSchoolModification tempVar3(1, "gg", ModificationSites::R);
            m->AddModification(&tempVar3);
        }, "Unable to add a modification with sites other than ModificationSites.E");
        OldSchoolModification tempVar4(2, "My Mod2b", ModificationSites::E);
        Assert::IsTrue(std::find(m->begin(), m->end(), &tempVar4) != m->end()));
        double kk = 0;
        System::Collections::IEnumerable *a = m;
        for (auto b : a) {
            kk += (dynamic_cast<OldSchoolModification*>(b))->MonoisotopicMass;
        }
        Assert::AreEqual((double)3, kk);
    
        delete m;
    }

    void TestModifications::ModificationSitesTest55() {
        Assert::IsTrue(ModificationSites::E::ContainsSites(ModificationSites::Any));
        Assert::IsFalse(ModificationSites::E::ContainsSites(ModificationSites::None));
        Assert::IsTrue(ModificationSites::None::ContainsSites(ModificationSites::None));
    }

    void TestModifications::ChemicalFormulaModificaiton() {
        OldSchoolChemicalFormulaModification *a = new OldSchoolChemicalFormulaModification(ChemicalFormula::ParseFormula("OH"));
        OldSchoolChemicalFormulaModification *b = new OldSchoolChemicalFormulaModification(a);
        Assert::AreEqual(a, b);

        delete b;
        delete a;
    }

    void TestModifications::ModificationCollectionScrambledEquals() {
        OldSchoolModification tempVar(1, "Mod1");
        ModificationCollection *a = new ModificationCollection({&tempVar, new OldSchoolModification(2, "Mod2")});
        OldSchoolModification tempVar2(1, "Mod1");
        ModificationCollection *b = new ModificationCollection({&tempVar2, new OldSchoolModification(3, "Mod3")});

        Assert::IsFalse(a->Equals(b));
        delete b;
        delete a;
    }

    void TestModifications::Test_modification_hash_set() {
        Modification *m1 = new Modification("23", "unknown");
        Modification *m2 = new Modification("23", "unknown");
        std::unordered_set<Modification*> mods = std::vector<Modification*> {m1, m2};
        Assert::AreEqual((long unsigned int)1, mods.size());

        delete m2;
        delete m1;
    }

    void TestModifications::Test_modification2_hash_set() {
        ModificationMotif motif;
        ModificationMotif::TryGetMotif("K", motif);
        ModificationWithLocation *m1 = new ModificationWithLocation("id1", "modificationType", motif, TerminusLocalization::Any, std::unordered_map<std::string, std::vector<std::string>>());
        ModificationWithLocation *m2 = new ModificationWithLocation("id1", "modificationType", motif, TerminusLocalization::Any);
        m1->linksToOtherDbs.emplace("key", std::vector<std::string> {"value"});
        m2->linksToOtherDbs.emplace("key", std::vector<std::string> {"value"});
        std::unordered_set<Modification*> mods = std::vector<Modification*> {m1, m2};
        Assert::IsTrue(m1->Equals(m2));
        Assert::AreEqual((long unsigned int)1, mods.size());

        delete m2;
        delete m1;
    }

    void TestModifications::Test_modification3_hash_set() {
        ModificationMotif motif;
        ModificationMotif::TryGetMotif("K", motif);
        ModificationWithMass *m1 = new ModificationWithMass("id1", "modificationType", motif, TerminusLocalization::Any, 1.11111, std::unordered_map<std::string, std::vector<std::string>>(), neutralLosses: {2.222222}, diagnosticIons: std::vector<double> {1.2233});
        ModificationWithMass *m2 = new ModificationWithMass("id1", "modificationType", motif, TerminusLocalization::Any, 1.11111 - 1e-10, std::unordered_map<std::string, std::vector<std::string>>(), neutralLosses: {2.222222 + 1e-10}, diagnosticIons: std::vector<double> {1.2233});
        m1->linksToOtherDbs.emplace("key", std::vector<std::string> {"value"});
        m2->linksToOtherDbs.emplace("key", std::vector<std::string> {"value"});
        std::unordered_set<Modification*> mods = std::vector<Modification*> {m1, m2};
        Assert::AreEqual( (long unsigned int)1, mods.size());
        Assert::IsTrue(m1->Equals(m2));

        delete m2;
        delete m1;
    }
#endif
}
