#include "TestModifications.h"
#include "../Proteomics/Proteomics.h"
#include "../Chemistry/ChemicalFormula.h"
//#include "../UsefulProteomicsDatabases/PtmListLoader.h"
#include "../MzLibUtil/MzLibException.h"
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
    // Uses PtmLoader
    std::cout << ++i << ". Test_ModificationWithNoMassWritten " << std::endl;    
    Test::TestModifications::Test_ModificationWithNoMassWritten();    
#endif
    std::cout << ++i << ". NameAndSites " << std::endl;    
    Test::TestModifications::NameAndSites();

    std::cout << ++i << ". ModificationEquality " << std::endl;    
    Test::TestModifications::ModificationEquality();

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

#ifdef LATER    
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
//        auto mod1 = new ModificationWithMass("mod", "type", motif, TerminusLocalization::Any, 1, nullptr, nullptr, nullptr);
//        auto mod2 = new ModificationWithMass("mod2", "type", motif, TerminusLocalization::Any, 10, nullptr, nullptr, nullptr);
        auto mod1 = new Modification("mod", "", "type", "", motif, "Anywhere.", nullptr, std::make_optional(1), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");
        auto mod2 = new Modification("mod2", "", "type", "", motif, "Anywhere.", nullptr, std::make_optional(10), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");


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
//        auto mod1 = new ModificationWithMassAndCf("mod", "type", motif, TerminusLocalization::Any, ChemicalFormula::ParseFormula("H"), std::make_optional(ChemicalFormula::ParseFormula("H")->getMonoisotopicMass()), nullptr, nullptr, nullptr);
        auto mod1 = new Modification("mod of M", "", "type", "", motif, "Anywhere.", ChemicalFormula::ParseFormula("H"), std::make_optional(ChemicalFormula::ParseFormula("H")->getMonoisotopicMass()), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");

        auto mod1string = mod1->ToString();
        Assert::IsTrue(!mod1string.find("MM") != std::string::npos);
        std::vector<(Modification, string)> errors;
        auto modAfterWriteRead = dynamic_cast<Modification*>(PtmListLoader::ReadModsFromString(mod1string + "\r\n" + "//", errors).front());
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

    }

    void TestModifications::ModificationSitesTest() {
        // Empty modification, has no name and by default has Sites = ModificationSites.Any
        auto a = ModificationSites::A | ModificationSites::E;
        auto b = ModificationSites::A | ModificationSites::E;
        Assert::IsTrue( a == b);
    }

    void TestModifications::Sites() {
        // Empty modification, has no name and by default has Sites = ModificationSites.Any
        auto a = ModificationSites::A | ModificationSites::C | ModificationSites::E;
        Assert::IsTrue( ModificationSiteExtensions::ContainsSites(a, ModificationSites::E));

        Assert::IsTrue(ModificationSiteExtensions::ContainsSites(a, ModificationSites::A | ModificationSites::C));
        Assert::IsFalse(ModificationSiteExtensions::ContainsSites(a, ModificationSites::N));
        Assert::IsFalse(ModificationSiteExtensions::ContainsSites(a, ModificationSites::N | ModificationSites::C));
        auto b = ModificationSiteExtensions::EnumerateActiveSites(a);
        Assert::AreEqual(3, (int)b.size());
    }
    
    void TestModifications::ModificationCollectionTest() {
        OldSchoolModification tempVar(1, "Mod1");
        OldSchoolModification m1 ( 2, "Mod2");
        ModificationCollection *a = new ModificationCollection({&tempVar, &m1});

        double lala = 0;
        for (auto jadfk : a->getModifications())
        {
            lala += (dynamic_cast<IHasMass*>(jadfk))->getMonoisotopicMass();
        }
        Assert::IsTrue(std::abs(3 - lala) < 1e-09);

        std::string s1 = "Mod1 | Mod2";
        Assert::AreEqual(s1, a->ToString());
        OldSchoolModification tempVar2(3, "Mod3");
        a->Add(&tempVar2);

        std::string s2 = "Mod1 | Mod2 | Mod3";
        Assert::AreEqual(s2, a->ToString());
        OldSchoolModification tempVar3(2, "Mod2");
        Assert::IsTrue(a->Contains(&tempVar3));

        std::vector<IHasMass*> myArray(4);
        a->CopyTo(myArray, 1);
#ifdef ORIG
        Assert::AreEqual(3, myArray.Sum([&] (std::any b)
        {
        delete a;
            return b == nullptr ? 0 : 1;
        }));
#endif
        double sum=0.0;
        for ( auto b: myArray ) {
            if ( b != nullptr ){
                sum++;
            }
        }
        Assert::IsTrue(std::abs(3 - sum) < 1e-09);

        Assert::AreEqual(3, a->getCount());
        Assert::IsFalse(a->getIsReadOnly());
        OldSchoolModification tempVar4(2, "Mod2");
        a->Remove(&tempVar4);

        std::string s3 = "Mod1 | Mod3";
        Assert::AreEqual(s3, a->ToString());
        double ok = 0;
        for (auto b : a->getModifications())
        {
            ok += b->getMonoisotopicMass();
        }
        Assert::IsTrue(std::abs(4- ok) < 1e-09);

        a->Clear();
        std::string s4;
        Assert::AreEqual(s4, a->ToString());
        //delete a;
    }

    void TestModifications::ModificationCollectionTest2() {
        OldSchoolModification tempVar(1, "Mod1");
        OldSchoolModification m1(2, "Mod2");
        ModificationCollection *a = new ModificationCollection({&tempVar,&m1 });
        OldSchoolModification tempVar2(3, "Mod3");
        Assert::IsFalse(a->Remove(&tempVar2));

        //delete a;
    }

    void TestModifications::ModificationWithMultiplePossibilitiesTest() {
        auto m = new ModificationWithMultiplePossibilitiesCollection("My Iso Mod",
                                                                     ModificationSites::E);
        OldSchoolModification tempVar(1, "My Mod1a", ModificationSites::E);
        m->AddModification(&tempVar);
        OldSchoolModification tempVar2(2, "My Mod2b", ModificationSites::E);
        m->AddModification(&tempVar2);
        
        Assert::AreEqual(2, (int)m->getCount());
        // std::string s1="My Mod2b";
        // Edgar: according to my understanding, the name has to by Mod1a, not Mod2b.
        std::string s1="My Mod1a";
        auto m1 = m->getModifications();
        Assert::AreEqual(s1, m1[1]->getName());
#ifdef ORIG
        Assert::Throws<MzLibException*>([&] () {
                OldSchoolModification tempVar3(1, "gg", ModificationSites::R);
                m->AddModification(&tempVar3);
            }, "Unable to add a modification with sites other than ModificationSites.E");
        
#endif
        OldSchoolModification tempVar3(1, "gg", ModificationSites::R);
        m->AddModification(&tempVar3);
        Assert::AreEqual(2, (int)m->getCount()); // should be unchanged


        OldSchoolModification tempVar4(2, "My Mod2b", ModificationSites::E);
        //Assert::IsTrue(std::find(m->begin(), m->end(), &tempVar4) != m->end());
        Assert::IsTrue ( m->Contains(&tempVar4));
        double kk = 0;
        for (auto b = m->getModifications().begin(); b!=m->getModifications().end(); b++ ) {
            kk += (dynamic_cast<OldSchoolModification*>(b->second))->getMonoisotopicMass();
        }
        Assert::AreEqual((double)3, kk);
    
        delete m;
    }

#ifdef LATER
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

    void TestModifications::ModificationCollectionTestTest()    {
        OldSchoolModification *mod1 = new OldSchoolModification(10, "mass 10 modification");
        OldSchoolModification *mod2 = new OldSchoolModification(100, "mass 100 modification");
        OldSchoolModification *mod3 = new OldSchoolModification(1000, "mass 1000 modification");
        ModificationCollection *a = new ModificationCollection({mod1, mod2, mod3, mod1});
        ModificationCollection *b = new ModificationCollection({mod1, mod3, mod1, mod2});
        Assert::IsTrue(a->Equals(b));
        ModificationCollection *c = new ModificationCollection({mod1});
        Assert::IsFalse(c->Equals(b));

        delete c;
        //C# TO C++ CONVERTER TODO TASK: A 'delete b' statement was not added since b was passed to a
        // method or constructor. Handle memory management manually.
        delete a;
        //C# TO C++ CONVERTER TODO TASK: A 'delete mod3' statement was not added since mod3 was passed to
        // a method or constructor. Handle memory management manually.
        //C# TO C++ CONVERTER TODO TASK: A 'delete mod2' statement was not added since mod2 was passed to
        // a method or constructor. Handle memory management manually.
        //C# TO C++ CONVERTER TODO TASK: A 'delete mod1' statement was not added since mod1 was passed to
        //a method or constructor. Handle memory management manually.
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

void TestModifications::TestInvalidModificationHash()
    {
        ModificationMotif motif;
        ModificationMotif::TryGetMotif("K", motif);
        Modification *m1 = new Modification("id1", "", "modificationType", "", motif, "Anywhere.", nullptr, std::nullopt, std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");
        Modification *m2 = new Modification("id1", "", "modificationType", "", motif, "Anywhere.", nullptr, std::nullopt, std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");
        std::unordered_set<Modification*> mods = std::vector<Modification*> {m1, m2};
        Assert::IsFalse(m1->getValidModification());
        Assert::IsFalse(m2->getValidModification());
        Assert::True(m1->Equals(m2));
        Assert::AreEqual(1, mods.size());

        // test comparing invalid mods with null vs not-null MMs
        m1 = new Modification("id1", "", "", "", motif, "Anywhere.", nullptr, std::make_optional(1), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");
        m2 = new Modification("id1", "", "", "", motif, "Anywhere.", nullptr, std::nullopt, std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");
        mods = std::vector<Modification*> {m1, m2};
        Assert::IsFalse(m1->getValidModification());
        Assert::IsFalse(m2->getValidModification());
        Assert::False(m1->Equals(m2));
        Assert::AreEqual(2, mods.size());

        // test comparing invalid mods with null vs not-null IDs
        m1 = new Modification("id1", "", "", "", motif, "Anywhere.", nullptr, std::nullopt, std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");
        m2 = new Modification("", "", "", "", motif, "Anywhere.", nullptr, std::nullopt, std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");
        mods = std::vector<Modification*> {m1, m2};
        Assert::IsFalse(m1->getValidModification());
        Assert::IsFalse(m2->getValidModification());
        Assert::False(m1->Equals(m2));
        Assert::AreEqual(2, mods.size());

//C# TO C++ CONVERTER TODO TASK: A 'delete m2' statement was not added since m2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete m1' statement was not added since m1 was passed to a method or constructor. Handle memory management manually.
    }
 void TestModifications::TestFragmentationNoMod()
    {
        // First we're checking to see if the fragment masses of an unmodified peptide a calculated correctly
        auto prot = new Protein("PEPTIDE", "");
        DigestionParams *digestionParams = new DigestionParams("trypsin", 0, 1, int::MaxValue, 1024, InitiatorMethionineBehavior::Retain, 2, CleavageSpecificity::Full, FragmentationTerminus::Both);
        std::vector<Modification*> variableModifications;
        auto ye = prot->Digest(digestionParams, std::vector<Modification*>(), variableModifications).ToList();

        // check unmodified
        auto unmodPeptide = ye.Where([&] (std::any p)
        {
//C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams was passed to a method or constructor. Handle memory management manually.
        delete prot;
            return p::AllModsOneIsNterminus->Count == 0;
        }).First();
        auto fragments = unmodPeptide->Fragment(DissociationType::HCD, FragmentationTerminus::Both);
        auto myUnmodFragmentMasses = fragments->Select([&] (std::any v)
        {
            static_cast<int>(std::round(v::NeutralMass::ToMz(1) * std::pow(10, 1))) / std::pow(10, 1);
        }).ToList();
        std::unordered_set<int> expectedMzs = {98, 227, 324, 425, 538, 653, 703, 574, 477, 376, 263, 148};

        Assert::That(expectedMzs.SetEquals(myUnmodFragmentMasses));

//C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams was passed to a method or constructor. Handle memory management manually.
        delete prot;
    }
void TestModifications::TestFragmentationModNoNeutralLoss()
    {
        // Now we'll check the mass of modified peptide with no neutral losses
        ModificationMotif motif;
        ModificationMotif::TryGetMotif("T", motif);
        Modification *mod = new Modification("oxidation", "", "testModType", "", motif, "Anywhere.", ChemicalFormula::ParseFormula("O1"), std::nullopt, std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");
        std::vector<Modification*> modlist = {mod};
        DigestionParams *digestionParams = new DigestionParams("trypsin", 0, 1, int::MaxValue, 1024, InitiatorMethionineBehavior::Retain, 2, CleavageSpecificity::Full, FragmentationTerminus::Both);

        auto prot = new Protein("PEPTIDE", nullptr, oneBasedModifications: std::unordered_map<int, std::vector<Modification*>>
        {
            {4, modlist}
        });
        auto ye = prot->Digest(digestionParams, std::vector<Modification*>(), std::vector<Modification*>()).ToList();

        // check unmodified
        auto unmodPeptide = ye.Where([&] (std::any p)
        {
        delete prot;
//C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams was passed to a method or constructor. Handle memory management manually.
        delete mod;
            return p::AllModsOneIsNterminus->Count == 0;
        }).First();
        auto myUnmodFragments = unmodPeptide->Fragment(DissociationType::HCD, FragmentationTerminus::Both).ToList();
        auto neutralMasses = std::vector<double>();
        neutralMasses.AddRange(myUnmodFragments.Select([&] (std::any m)
        {
            m::NeutralMass;
        }).ToList());
        auto expectedMasses = std::vector<double> {97, 226, 323, 424, 537, 652, 147, 262, 375, 476, 573, 702};
        for (int i = 0; i < neutralMasses.size(); i++)
        {
            neutralMasses[i] = Chemistry::ClassExtensions::RoundedDouble(std::make_optional(neutralMasses[i]), 0).value();
        }

        auto firstNotSecond = neutralMasses.Except(expectedMasses).ToList();
        auto secondNotFirst = expectedMasses.Except(neutralMasses).ToList();

        //this is the set without oxidation
        Assert::AreEqual(12, myUnmodFragments.size());
        Assert::AreEqual(0, firstNotSecond.size());
        Assert::AreEqual(0, secondNotFirst.size());

// with oxidation, no neutral loss
        auto modPeptide = ye.Where([&] (std::any p)
        {
        delete prot;
//C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams was passed to a method or constructor. Handle memory management manually.
        delete mod;
            return p::AllModsOneIsNterminus->Count == 1;
        }).First();

        auto myModFragments = modPeptide->Fragment(DissociationType::HCD, FragmentationTerminus::Both);
        neutralMasses = std::vector<double>();
        neutralMasses.AddRange(myModFragments->Select([&] (std::any m)
        {
            m::NeutralMass;
        }).ToList());
        expectedMasses = {97, 226, 323, 440, 553, 668, 147, 262, 375, 492, 589, 718};
        for (int i = 0; i < neutralMasses.size(); i++)
        {
            neutralMasses[i] = Chemistry::ClassExtensions::RoundedDouble(std::make_optional(neutralMasses[i]), 0).value();
        }

        firstNotSecond = neutralMasses.Except(expectedMasses).ToList();
        secondNotFirst = expectedMasses.Except(neutralMasses).ToList();

        //this is the set with oxidation
        Assert::AreEqual(12, myUnmodFragments.size());
        Assert::AreEqual(0, firstNotSecond.size());
        Assert::AreEqual(0, secondNotFirst.size());

        delete prot;
//C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams was passed to a method or constructor. Handle memory management manually.
        delete mod;
    }
 void TestModifications::Test_FragmentationModNeutralLoss()
    {
        // Now we'll check the mass of modified peptide with no neutral losses
        ModificationMotif motif;
        ModificationMotif::TryGetMotif("T", motif);
        Modification *mod = new Modification("phospho", "", "testModType", "", motif, "Anywhere.", ChemicalFormula::ParseFormula("H1 O3 P1"), std::nullopt, std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>
        {
            {
                DissociationType::HCD, {ChemicalFormula::ParseFormula("H3 O4 P1")->getMonoisotopicMass()}
            }
        },
        std::unordered_map<DissociationType, std::vector<double>>(), "");
        std::vector<Modification*> modlist = {mod};
        DigestionParams *digestionParams = new DigestionParams("trypsin", 0, 1, int::MaxValue, 1024, InitiatorMethionineBehavior::Retain, 2, CleavageSpecificity::Full, FragmentationTerminus::Both);

        auto prot = new Protein("PEPTIDE", nullptr, oneBasedModifications: std::unordered_map<int, std::vector<Modification*>>
        {
            {4, modlist}
        });
        auto ye = prot->Digest(digestionParams, std::vector<Modification*>(), std::vector<Modification*>()).ToList();

        auto peptideWithNeutralMassMod = ye.Where([&] (std::any v)
        {
        delete prot;
//C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams was passed to a method or constructor. Handle memory management manually.
        delete mod;
            return v::AllModsOneIsNterminus->Count > 0;
        }).First();

        auto myModFragments = peptideWithNeutralMassMod->Fragment(DissociationType::HCD, FragmentationTerminus::Both).ToList();
        std::unordered_set<int> neutralMasses = std::unordered_set<int>(myModFragments.Select([&] (std::any m)
        {
            static_cast<int>(m::NeutralMass::ToMz(1));
        }).ToList());
        std::unordered_set<int> expectedMasses = {98,227, 324, 407, 520, 635, 505, 618, 733, 148, 263, 376, 459, 556, 685, 557, 654, 783, 782};

        Assert::That(neutralMasses.SetEquals(expectedMasses));

        delete prot;
//C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams was passed to a method or constructor. Handle memory management manually.
        delete mod;
    }

 void TestModifications::Test_FragmentationTwoModNeutralLoss()
    {
        // Now we'll check the mass of modified peptide with 2 neutral loss mods
        ModificationMotif motifone;
        ModificationMotif::TryGetMotif("Q", motifone);
        Modification *modone = new Modification("ammonia", "", "testModType", "", motifone, "Anywhere.", nullptr, std::make_optional(0), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>
        {
            {
                DissociationType::HCD, {ChemicalFormula::ParseFormula("H3 N1")->getMonoisotopicMass()}
            }
        },
        std::unordered_map<DissociationType, std::vector<double>>(), "");

        ModificationMotif motiftwo;
        ModificationMotif::TryGetMotif("T", motiftwo);
        Modification *modtwo = new Modification("phospho", "", "testModType", "", motiftwo, "Anywhere.", ChemicalFormula::ParseFormula("H1 O3 P1"), std::nullopt, std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>
        {
            {
                DissociationType::HCD, {ChemicalFormula::ParseFormula("H3 O4 P1")->getMonoisotopicMass()}
            }
        },
        std::unordered_map<DissociationType, std::vector<double>>(), "");

        std::vector<Modification*> modlistone = {modone};
        std::vector<Modification*> modlisttwo = {modtwo};

        DigestionParams *digestionParams = new DigestionParams("trypsin", 0, 1, int::MaxValue, 1024, InitiatorMethionineBehavior::Retain, 2, CleavageSpecificity::Full, FragmentationTerminus::Both);

        auto prot = new Protein("PEQTIDE", nullptr, oneBasedModifications: std::unordered_map<int, std::vector<Modification*>>
        {
            {3, modlistone},
            {4, modlisttwo}
        });
        auto ye = prot->Digest(digestionParams, std::vector<Modification*>(), std::vector<Modification*>()).ToList();

        auto peptideWithNeutralMassMod = ye.Where([&] (std::any v)
        {
        delete prot;
//C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams was passed to a method or constructor. Handle memory management manually.
        delete modtwo;
        delete modone;
            return v::AllModsOneIsNterminus->Count == 2;
}).First();

        auto myModFragments = peptideWithNeutralMassMod->Fragment(DissociationType::HCD, FragmentationTerminus::Both).ToList();
        std::unordered_set<int> neutralMasses = std::unordered_set<int>(myModFragments.Select([&] (std::any m)
        {
            static_cast<int>(m::NeutralMass::ToMz(1));
        }).ToList());
        std::unordered_set<int> expectedMasses = {98, 227, 355, 536, 649, 764, 438, 551, 666, 338, 519, 632, 747, 148, 263, 376, 557, 685, 814, 668, 797, 459, 587, 716, 813, 894};

        Assert::That(neutralMasses.SetEquals(expectedMasses));

        delete prot;
//C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams was passed to a method or constructor. Handle memory management manually.
        delete modtwo;
        delete modone;
    }

   void TestModifications::Test_FragmentationTwoModNeutralLossTwoFragTypes()
    {
        // Now we'll check the mass of modified peptide with no neutral losses
        ModificationMotif motif;
        ModificationMotif::TryGetMotif("T", motif);

        std::unordered_map<DissociationType, std::vector<double>> myNeutralLosses =
        {
            {
                DissociationType::HCD, {ChemicalFormula::ParseFormula("H3 O4 P1")->getMonoisotopicMass()}
            },
            {
//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
                DissociationType::ETD, std::vector<double>() { ChemicalFormula::ParseFormula("H3 N1")->getMonoisotopicMass() }
            }
        };

        Modification *mod = new Modification("phospho", "", "testModType", "", motif, "Anywhere.", ChemicalFormula::ParseFormula("H1 O3 P1"), std::nullopt, std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), myNeutralLosses, std::unordered_map<DissociationType, std::vector<double>>(), "");
        std::vector<Modification*> modlist = {mod};
        DigestionParams *digestionParams = new DigestionParams("trypsin", 0, 1, int::MaxValue, 1024, InitiatorMethionineBehavior::Retain, 2, CleavageSpecificity::Full, FragmentationTerminus::Both);

        auto prot = new Protein("PEPTIDE", nullptr, oneBasedModifications: std::unordered_map<int, std::vector<Modification*>>
        {
            {4, modlist}
        });
        auto ye = prot->Digest(digestionParams, std::vector<Modification*>(), std::vector<Modification*>()).ToList();

        auto peptideWithNeutralMassMod = ye.Where([&] (std::any v)
        {
        delete prot;
//C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams was passed to a method or constructor. Handle memory management manually.
        delete mod;
            return v::AllModsOneIsNterminus->Count == 1;
        }).First();

        auto myModFragmentsHCD = peptideWithNeutralMassMod->Fragment(DissociationType::HCD, FragmentationTerminus::Both);

        auto neutralMassesHCD = myModFragmentsHCD->Select([&] (std::any m)
        {
            static_cast<int>(m::NeutralMass::ToMz(1));
        });
        auto expectedMassesHCD = std::unordered_set<int> {98, 227, 324, 407, 520, 635, 505, 618, 733, 148, 263, 376, 459, 556, 685, 557, 654, 783, 782};

        Assert::That(expectedMassesHCD.SetEquals(neutralMassesHCD));

        //Now try the other half
        auto myModFragmentsETD = peptideWithNeutralMassMod->Fragment(DissociationType::ETD, FragmentationTerminus::Both);

        auto neutralMassesETD = myModFragmentsETD->Select([&] (std::any m)
        {
            static_cast<int>(m::NeutralMass::ToMz(1));
        });
        auto expectedMassesETD = std::unordered_set<int> {115, 244, 341, 505, 618, 733, 522, 635, 750, 148, 263, 376, 540, 637, 766, 557, 654, 783, 133, 248, 361, 525, 622, 751, 542, 639, 768, 863};

        Assert::That(expectedMassesHCD.SetEquals(neutralMassesHCD));

        delete prot;
//C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams was passed to a method or constructor. Handle memory management manually.
        delete mod;
    }

  void TestModifications::TestCompactPeptideSerialization()
    {
        // purpose of this test is to serialize/deserialize a CompactPeptide and make sure the deserialized peptide
        // has the same properties as before it was serialized. This peptide is unmodified
        std::string sequence = "PEPTIDE";
        PeptideWithSetModifications *p = new PeptideWithSetModifications(sequence, std::unordered_map<std::string, Modification*>(), 0, nullptr, nullptr, 0, 7, 0);
        CompactPeptide *cp = new CompactPeptide(p, FragmentationTerminus::Both);
        CompactPeptide *deserializedCp = nullptr;

        std::string dir = FileSystem::combine(TestContext::CurrentContext->TestDirectory, "TestCompactPeptideSerialization");
        FileSystem::createDirectory(dir);
        std::string path = FileSystem::combine(dir, "myCompactPeptideIndex.ind");

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
        auto messageTypes = typeof(CompactPeptide);
        auto ser = new NetSerializer::Serializer(std::vector<std::type_info> {messageTypes});

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (var file = System.IO.File.Create(path))
        {
            auto file = System::IO::File::Create(path);
            ser->Serialize(file, cp);
        }

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (var file = System.IO.File.OpenRead(path))
        {
            auto file = System::IO::File::OpenRead(path);
            deserializedCp = static_cast<CompactPeptide*>(ser->Deserialize(file));
        }

        Assert::That(cp->Equals(deserializedCp));

        delete ser;
//C# TO C++ CONVERTER TODO TASK: A 'delete cp' statement was not added since cp was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete p' statement was not added since p was passed to a method or constructor. Handle memory management manually.
    }
 void TestModifications::TestSerializationPeptideFromString()
    {
        // purpose of this test is to serialize/deserialize a PeptideWithSetModifications and make sure the deserialized peptide
        // has the same properties as before it was serialized. This peptide is unmodified and generated from reading in a string
        std::string sequence = "PEPTIDE";
        PeptideWithSetModifications *peptide = new PeptideWithSetModifications(sequence, std::unordered_map<std::string, Modification*>(), 0, nullptr, nullptr, 1, 7, 0);
        PeptideWithSetModifications *deserializedPeptide = nullptr;

        std::string dir = FileSystem::combine(TestContext::CurrentContext->TestDirectory, "TestSerializationPeptideFromString");
        FileSystem::createDirectory(dir);
        std::string path = FileSystem::combine(dir, "myPeptideIndex.ind");

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
        auto messageTypes = typeof(PeptideWithSetModifications);
        auto ser = new NetSerializer::Serializer(std::vector<std::type_info> {messageTypes});

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (var file = System.IO.File.Create(path))
        {
            auto file = System::IO::File::Create(path);
            ser->Serialize(file, peptide);
        }

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (var file = System.IO.File.OpenRead(path))
        {
            auto file = System::IO::File::OpenRead(path);
            deserializedPeptide = static_cast<PeptideWithSetModifications*>(ser->Deserialize(file));
        }

        deserializedPeptide->SetNonSerializedPeptideInfo(std::unordered_map<std::string, Modification*>(), std::unordered_map<std::string, Protein*>());

        // not asserting any protein properties - since the peptide was created from a sequence string it didn't have a protein to begin with

        Assert::That(peptide->Equals(deserializedPeptide));
        Assert::That(deserializedPeptide->getMonoisotopicMass() == peptide->getMonoisotopicMass());
        Assert::That(deserializedPeptide->getSequenceWithChemicalFormulas() == peptide->getSequenceWithChemicalFormulas());

        std::vector<double> deserializedPeptideFragments = deserializedPeptide->Fragment(DissociationType::HCD, FragmentationTerminus::Both).Select([&] (std::any v)
        {
            v::NeutralMass;
        }).ToList();
        std::vector<double> peptideFragments = peptide->Fragment(DissociationType::HCD, FragmentationTerminus::Both).Select([&] (std::any v)
        {
            v::NeutralMass;
        }).ToList();
        Assert::That(deserializedPeptideFragments.SequenceEqual(peptideFragments));

        delete ser;
//C# TO C++ CONVERTER TODO TASK: A 'delete peptide' statement was not added since peptide was passed to a method or constructor. Handle memory management manually.
    }

void TestModifications::TestSerializationPeptideFromProtein()
    {
        // purpose of this test is to serialize/deserialize a PeptideWithSetModifications and make sure the deserialized peptide
        // has the same properties as before it was serialized. This peptide is unmodified and generated from digesting a protein
        Protein *protein = new Protein("PEPTIDE", "Accession1", "", std::vector<std::tuple<std::string, std::string>>(), std::unordered_map<int, std::vector<Modification>>(), std::vector<ProteolysisProduct>(), "MyProtein", "", false, false, std::vector<DatabaseReference>(), std::vector<SequenceVariation>(), std::vector<SequenceVariation>(), "", std::vector<DisulfideBond>(), std::vector<SpliceSite>(), "");

        DigestionParams tempVar();
        PeptideWithSetModifications *peptide = protein->Digest(&tempVar, std::vector<Modification*>(), std::vector<Modification*>()).front();
        PeptideWithSetModifications *deserializedPeptide = nullptr;

        std::string dir = FileSystem::combine(TestContext::CurrentContext->TestDirectory, "TestSerializationPeptideFromProtein");
        FileSystem::createDirectory(dir);
        std::string path = FileSystem::combine(dir, "myPeptideIndex.ind");

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
        auto messageTypes = typeof(PeptideWithSetModifications);
        auto ser = new NetSerializer::Serializer(std::vector<std::type_info> {messageTypes});

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (var file = System.IO.File.Create(path))
        {
            auto file = System::IO::File::Create(path);
            ser->Serialize(file, peptide);
        }

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (var file = System.IO.File.OpenRead(path))
        {
            auto file = System::IO::File::OpenRead(path);
            deserializedPeptide = static_cast<PeptideWithSetModifications*>(ser->Deserialize(file));
        }

        deserializedPeptide->SetNonSerializedPeptideInfo(std::unordered_map<std::string, Modification*>(), std::unordered_map<std::string, Protein*>
        {
            {protein->getAccession(), protein}
        });

        Assert::That(peptide->getDigestionParams()->Equals(deserializedPeptide->getDigestionParams()));
        Assert::That(peptide->Equals(deserializedPeptide));
        Assert::That(deserializedPeptide->getProtein()->getName() == peptide->getProtein()->getName());
        Assert::That(deserializedPeptide->getMonoisotopicMass() == peptide->getMonoisotopicMass());
        Assert::That(deserializedPeptide->getSequenceWithChemicalFormulas() == peptide->getSequenceWithChemicalFormulas());

        std::vector<double> deserializedPeptideFragments = deserializedPeptide->Fragment(DissociationType::HCD, FragmentationTerminus::Both).Select([&] (std::any v)
                                                                                                                                                    {
            v::NeutralMass;
        }).ToList();
        std::vector<double> peptideFragments = peptide->Fragment(DissociationType::HCD, FragmentationTerminus::Both).Select([&] (std::any v)
        {
            v::NeutralMass;
        }).ToList();

        Assert::That(deserializedPeptideFragments.SequenceEqual(peptideFragments));

        delete ser;
//C# TO C++ CONVERTER TODO TASK: A 'delete protein' statement was not added since protein was passed to a method or constructor. Handle memory management manually.
    }

void TestModifications::TestSerializationPeptideFromProteinWithMod()
    {
        // purpose of this test is to serialize/deserialize a PeptideWithSetModifications and make sure the deserialized peptide
        // has the same properties as before it was serialized. This peptide is modified with a phosphorylation

        ModificationMotif motif;
        ModificationMotif::TryGetMotif("T", motif);

        std::unordered_map<DissociationType, std::vector<double>> myNeutralLosses =
        {
            {
                DissociationType::HCD, {ChemicalFormula::ParseFormula("H3 O4 P1")->getMonoisotopicMass()}
            },
            {
//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
                DissociationType::ETD, std::vector<double>() { ChemicalFormula::ParseFormula("H3 N1")->getMonoisotopicMass() }
            }
        };

        Modification *mod = new Modification("phospho", "", "testModType", "", motif, "Anywhere.", ChemicalFormula::ParseFormula("H1 O3 P1"), std::nullopt, std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), myNeutralLosses, std::unordered_map<DissociationType, std::vector<double>>(), "");

        std::unordered_map<int, std::vector<Modification*>> mods =
        {
            {
                4, {mod}
            }
        };

        Protein *protein = new Protein("PEPTIDE", "Accession1", "", std::vector<std::tuple<std::string, std::string>>(), mods, std::vector<ProteolysisProduct>(), "MyProtein", "", false, false, std::vector<DatabaseReference>(), std::vector<SequenceVariation>(), std::vector<SequenceVariation>(), "", std::vector<DisulfideBond>(), std::vector<SpliceSite>(), "");

        DigestionParams tempVar();
        PeptideWithSetModifications *peptide = protein->Digest(&tempVar, std::vector<Modification*>(), std::vector<Modification*>()).Where([&] (std::any v)
        {
        delete protein;
        delete mod;
            return v::AllModsOneIsNterminus->Count == 1;
        }).First();
        PeptideWithSetModifications *deserializedPeptide = nullptr;

        std::string dir = FileSystem::combine(TestContext::CurrentContext->TestDirectory, "TestSerializationPeptideFromProteinWithMod");
        FileSystem::createDirectory(dir);
        std::string path = FileSystem::combine(dir, "myPeptideIndex.ind");

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
        auto messageTypes = typeof(PeptideWithSetModifications);
        auto ser = new NetSerializer::Serializer(std::vector<std::type_info> {messageTypes});

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (var file = System.IO.File.Create(path))
        {
            auto file = System::IO::File::Create(path);
            ser->Serialize(file, peptide);
        }

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (var file = System.IO.File.OpenRead(path))
        {
            auto file = System::IO::File::OpenRead(path);
            deserializedPeptide = static_cast<PeptideWithSetModifications*>(ser->Deserialize(file));
        }

        std::unordered_map<std::string, Modification*> stringToMod =
        {
            {mods.Values->First().First().IdWithMotif, mods.Values->First().First()}
        };

        deserializedPeptide->SetNonSerializedPeptideInfo(stringToMod, std::unordered_map<std::string, Protein*>
        {
            {protein->getAccession(), protein}
        });

        Assert::That(peptide->Equals(deserializedPeptide));
        Assert::That(deserializedPeptide->getProtein()->getName() == peptide->getProtein()->getName());
        Assert::That(deserializedPeptide->getMonoisotopicMass() == peptide->getMonoisotopicMass());
        Assert::That(deserializedPeptide->getSequenceWithChemicalFormulas() == peptide->getSequenceWithChemicalFormulas());

        std::vector<double> deserializedPeptideFragments = deserializedPeptide->Fragment(DissociationType::HCD, FragmentationTerminus::Both).Select([&] (std::any v)
        {
            v::NeutralMass;
        }).ToList();
        std::vector<double> peptideFragments = peptide->Fragment(DissociationType::HCD, FragmentationTerminus::Both).Select([&] (std::any v)
        {
            v::NeutralMass;
        }).ToList();

        Assert::That(deserializedPeptideFragments.SequenceEqual(peptideFragments));

        delete ser;
//C# TO C++ CONVERTER TODO TASK: A 'delete protein' statement was not added since protein was passed to a method or constructor. Handle memory management manually.
        delete mod;
    }

    void TestModifications::TestFragmentNterminalModifiedPeptide()
    {
        ModificationMotif motif;
        ModificationMotif::TryGetMotif("P", motif);
        Modification *nTermMod = new Modification("acetylation", "", "testModType", "", motif, "N-terminal.", ChemicalFormula::ParseFormula("C2H2O1"), std::nullopt, std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");

        std::unordered_map<int, std::vector<Modification*>> mods =
        {
            {
                1, {nTermMod}
            }
        };

        Protein *protein = new Protein("PEPTIDE", "", "", std::vector<std::tuple<std::string, std::string>>(), mods, std::vector<ProteolysisProduct>(), "", "", false, false, std::vector<DatabaseReference>(), std::vector<SequenceVariation>(), std::vector<SequenceVariation>(), "", std::vector<DisulfideBond>(), std::vector<SpliceSite>(), "");
        DigestionParams tempVar();
        PeptideWithSetModifications *peptide = protein->Digest(&tempVar, std::vector<Modification*>(), std::vector<Modification*>()).Where([&] (std::any p)
        {
        delete protein;
        delete nTermMod;
            return p::AllModsOneIsNterminus->Count == 1;
        }).First();
        Assert::That(peptide->getFullSequence() == "[testModType:acetylation on P]PEPTIDE");

        auto fragments = peptide->Fragment(DissociationType::HCD, FragmentationTerminus::Both).ToList();
        auto roundedFragments = fragments.Select([&] (std::any f)
        {
            (int)f.NeutralMass;
        }).ToList();
        Assert::That(roundedFragments.SequenceEqual(std::vector<int> {139, 268, 365, 466, 579, 694, 147, 262, 375, 476, 573, 702}));

        delete protein;
        delete nTermMod;
    }
   void TestModifications::TestFragmentCTerminalModifiedPeptide()
    {
        ModificationMotif motif;
        ModificationMotif::TryGetMotif("E", motif);
        Modification *cTermMod = new Modification("acetylation", "", "testModType", "", motif, "C-terminal.", ChemicalFormula::ParseFormula("C2H2O1"), std::nullopt, std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");

        std::unordered_map<int, std::vector<Modification*>> mods =
        {
            {
                7, {cTermMod}
            }
        };

        Protein *protein = new Protein("PEPTIDE", "", "", std::vector<std::tuple<std::string, std::string>>(), mods, std::vector<ProteolysisProduct>(), "", "", false, false, std::vector<DatabaseReference>(), std::vector<SequenceVariation>(), std::vector<SequenceVariation>(), "", std::vector<DisulfideBond>(), std::vector<SpliceSite>(), "");
        DigestionParams tempVar();
        PeptideWithSetModifications *peptide = protein->Digest(&tempVar, std::vector<Modification*>(), std::vector<Modification*>()).Where([&] (std::any p)
        {
        delete protein;
        delete cTermMod;
            return p::AllModsOneIsNterminus->Count == 1;
        }).First();
        Assert::That(peptide->getFullSequence() == "PEPTIDE[testModType:acetylation on E]");

        auto fragments = peptide->Fragment(DissociationType::HCD, FragmentationTerminus::Both).ToList();
        auto roundedFragments = fragments.Select([&] (std::any f)
        {
            (int)f.NeutralMass;
        }).ToList();
        Assert::That(roundedFragments.SequenceEqual(std::vector<int> {97, 226, 323, 424, 537, 652, 189, 304, 417, 518, 615, 744}));

        delete protein;
        delete cTermMod;
    }

#endif
}
