#include "TestFragments.h"

#include "../Chemistry/ChemicalFormula.h"
#include "../Chemistry/PeriodicTable.h"
#include "../Chemistry/Interfaces/IHasChemicalFormula.h"
#include "../MzLibUtil/MzLibException.h"
#include "../Proteomics/Protein/Protein.h"
#include "../Proteomics/Modifications/Modification.h"
#include "../Proteomics/Modifications/ModificationMotif.h"
#include "../Chemistry/ClassExtensions.h"
#include "../Chemistry/Constants.h"

#include "../UsefulProteomicsDatabases/PeriodicTableLoader.h"
#include "MzLibAssert.h"
#include <bits/stdc++.h>

using namespace Proteomics;

Peptide *_mockPeptideEveryAminoAcid;

int main ( int argc, char **argv )
{

    int i=0;
    std::cout << i << ". PeriodicTableLoader" << std::endl;    
    const std::string elfile="elements.dat";
    const std::string &elr=elfile;
    //UsefulProteomicsDatabases::PeriodicTableLoader::Load (elr);
    Chemistry::PeriodicTable::Load (elr);


    _mockPeptideEveryAminoAcid = new Peptide("ACDEFGHIKLMNPQRSTVWY");

#ifdef LATER
    // uses exceptions
    std::cout << ++i << ". FragmentNumberToHigh" << std::endl;    
    Test::TestFragments::FragmentNumberToHigh();
#endif
    
    std::cout << ++i << ". FragmentName " << std::endl;    
    Test::TestFragments::FragmentName();
    
    std::cout << ++i << ". FragmentAllBIons " << std::endl;    
    Test::TestFragments::FragmentAllBIons();
    
    std::cout << ++i << ". FragmentAnotherTest " << std::endl;    
    Test::TestFragments::FragmentAnotherTest();
    
#ifdef LATER
    // don't want to deal with the arguments to this test right now
    std::cout << ++i << ". TestDissociationProductTypes" << std::endl;    
    Test::TestFragments::TestDissociationProductTypes(DissociationType dissociationType, std::vector<ProductType> &expectedProductTypes);
#endif

    std::cout << ++i << ". FragmentNTermModTest " << std::endl;    
    Test::TestFragments::FragmentNTermModTest();
    
    std::cout << ++i << ". FragmentModifications " << std::endl;    
    Test::TestFragments::FragmentModifications();
    
    std::cout << ++i << ". ChemicalFormulaFragment " << std::endl;    
    Test::TestFragments::ChemicalFormulaFragment();
    
    std::cout << ++i << ". TestGetSiteDeterminingFragments " << std::endl;    
    Test::TestFragments::TestGetSiteDeterminingFragments();
    
    std::cout << ++i << ". TestFormulaTerminusMods " << std::endl;    
    Test::TestFragments::TestFormulaTerminusMods();

#ifdef LATER
    std::cout << ++i << ". CleavageIndicesTest " << std::endl;    
    Test::TestFragments::CleavageIndicesTest();
    
    std::cout << ++i << ". TestGetIonCapFailFail " << std::endl;    
    Test::TestFragments::TestGetIonCapFailFail();

    std::cout << ++i << ". TestGetTerminusFail " << std::endl;    
    Test::TestFragments::TestGetTerminusFail();
#endif
    
    std::cout << ++i << ". Test_GetTheoreticalFragments_UnmodifiedPeptide " << std::endl;    
    Test::TestFragments::Test_GetTheoreticalFragments_UnmodifiedPeptide();
    
    std::cout << ++i << ". Test_GetTheoreticalFragments_nTerminalModifiedPeptide " << std::endl;    
    Test::TestFragments::Test_GetTheoreticalFragments_nTerminalModifiedPeptide();
    
    std::cout << ++i << ". Test_GetTheoreticalFragments_cTerminalModifiedPeptide " << std::endl;    
    Test::TestFragments::Test_GetTheoreticalFragments_cTerminalModifiedPeptide();
    
    std::cout << ++i << ". Test_GetTheoreticalFragments_internallyModifiedPeptide " << std::endl;    
    Test::TestFragments::Test_GetTheoreticalFragments_internallyModifiedPeptide();
    
    std::cout << ++i << ". Test_GetTheoreticalFragments_nTerminalModifiedPeptide_NeutralLoss " << std::endl;    
    Test::TestFragments::Test_GetTheoreticalFragments_nTerminalModifiedPeptide_NeutralLoss();
    
    std::cout << ++i << ". Test_GetTheoreticalFragments_cTerminalModifiedPeptide_NeutralLoss " << std::endl;    
    Test::TestFragments::Test_GetTheoreticalFragments_cTerminalModifiedPeptide_NeutralLoss();
    
    std::cout << ++i << ". Test_GetTheoreticalFragments_internallyModifiedPeptide_NeutralLoss " << std::endl;    
    Test::TestFragments::Test_GetTheoreticalFragments_internallyModifiedPeptide_NeutralLoss();
    
    std::cout << ++i << ". Test_GetTheoreticalFragments_nTerminalModifiedPeptide_NeutralLoss_DissociationTypes_AnyActivationType_and_HCD " << std::endl;    
    Test::TestFragments::Test_GetTheoreticalFragments_nTerminalModifiedPeptide_NeutralLoss_DissociationTypes_AnyActivationType_and_HCD();
    
    std::cout << ++i << ". Test_GetTheoreticalFragments_nTerminalModifiedPeptide_NeutralLoss_DissociationTypes_CID_and_HCD " << std::endl;    
    Test::TestFragments::Test_GetTheoreticalFragments_nTerminalModifiedPeptide_NeutralLoss_DissociationTypes_CID_and_HCD();
    
    std::cout << ++i << ". Test_GetTheoreticalFragments_ProductTypeLabel " << std::endl;    
    Test::TestFragments::Test_GetTheoreticalFragments_ProductTypeLabel();
    
    std::cout << ++i << ". Test_Fragment_DiagnosticIons " << std::endl;    
    Test::TestFragments::Test_Fragment_DiagnosticIons();
    
    std::cout << ++i << ". Test_Fragment_MolecularIon_NeutralLoss " << std::endl;    
    Test::TestFragments::Test_Fragment_MolecularIon_NeutralLoss();
    
    std::cout << ++i << ". Test_Fragment_DiagnosticIons_unmatchedDissociationType " << std::endl;    
    Test::TestFragments::Test_Fragment_DiagnosticIons_unmatchedDissociationType();
    
    std::cout << ++i << ". Test_Fragment_MolecularIon_NeutralLoss_unmatchedDissociationType " << std::endl;    
    Test::TestFragments::Test_Fragment_MolecularIon_NeutralLoss_unmatchedDissociationType();
    
#ifdef LATER
    std::cout << ++i << ". Test_NeutralMassShiftFromProductType " << std::endl;    
    Test::TestFragments::Test_NeutralMassShiftFromProductType();
    
    std::cout << ++i << ". Test_NeutralMassShiftFromProductType_Exceptions " << std::endl;    
    Test::TestFragments::Test_NeutralMassShiftFromProductType_Exceptions();
    
    std::cout << ++i << ". Test_CustomDissociationType " << std::endl;    
    Test::TestFragments::Test_CustomDissociationType();
    
    std::cout << ++i << ". Test_TerminusSpecificProductTypes " << std::endl;    
    Test::TestFragments::Test_TerminusSpecificProductTypes();
    
    std::cout << ++i << ". Test_TerminusSpecificProductTypesFromPeptideWithSetMods " << std::endl;    
    Test::TestFragments::Test_TerminusSpecificProductTypesFromPeptideWithSetMods();
#endif
    
    std::cout << ++i << ". Test_MatchedFragmentIonToString " << std::endl;    
    Test::TestFragments::Test_MatchedFragmentIonToString();
    
    std::cout << ++i << ". Test_CID_Fragmentation_No_Unmodified_B1_ions " << std::endl;    
    Test::TestFragments::Test_CID_Fragmentation_No_Unmodified_B1_ions();

#ifdef LATER
    std::cout << ++i << ". Test_ETD_ECD_EThcD_Fragmentation_No_FragmentsAtProline" << std::endl;    
    Test::TestFragments::Test_ETD_ECD_EThcD_Fragmentation_No_FragmentsAtProline(DissociationType dissociationType, int fragmentCount);
    
    std::cout << ++i << ". CheckProlineFragments " << std::endl;    
    Test::TestFragments::CheckProlineFragments();
    
    std::cout << ++i << ". CheckProlineFragments2 " << std::endl;    
    Test::TestFragments::CheckProlineFragments2();
    
    std::cout << ++i << ". CheckProlineFragments3 " << std::endl;    
    Test::TestFragments::CheckProlineFragments3();
    
    std::cout << ++i << ". CheckProlineFragments4 " << std::endl;    
    Test::TestFragments::CheckProlineFragments4();

    std::cout << ++i << ". TestFragmentAnnotations " << std::endl;    
    Test::TestFragments::TestFragmentAnnotations();
    
    std::cout << ++i << ". TestFragmentErrors " << std::endl;    
    Test::TestFragments::TestFragmentErrors();
    
    std::cout << ++i << ". TestFragmentEquality " << std::endl;    
    Test::TestFragments::TestFragmentEquality();
    
    std::cout << ++i << ". TestThatDiagnosticIonsDontDuplicate " << std::endl;    
    Test::TestFragments::TestThatDiagnosticIonsDontDuplicate();
#endif
    
    return 0;
}

namespace Test
{
#ifdef LATER
    void TestFragments::FragmentNumberToHigh()
    {
        Assert::Throws<std::out_of_range>([&] ()
        {
            _mockPeptideEveryAminoAcid->Fragment(FragmentTypes::b, 25).ToList();
        });
    }
#endif
    
    void TestFragments::FragmentName()
    {
        Fragment *fragment = _mockPeptideEveryAminoAcid->Fragment(FragmentTypes::a, 1)[0];
        std::string s = "a1";
        Assert::AreEqual(s, fragment->ToString());
    }

    void TestFragments::FragmentAllBIons()
    {
        std::vector<Fragment*> fragments = _mockPeptideEveryAminoAcid->Fragment(FragmentTypes::b);
        Assert::AreEqual((long unsigned int) 19, fragments.size());
    }

    void TestFragments::FragmentAnotherTest()
    {
        std::vector<Fragment*> fragments = _mockPeptideEveryAminoAcid->Fragment(FragmentTypes::b, 1, 2);
        Assert::AreEqual((long unsigned int)2, fragments.size());
    }

#ifdef LATER
    void TestFragments::TestDissociationProductTypes(DissociationType dissociationType, std::vector<ProductType> &expectedProductTypes)
    {
        std::vector<ProductType> d = DissociationTypeCollection::ProductsFromDissociationType[dissociationType];
        Assert::IsTrue(expectedProductTypes.All([&] (std::any productType)
        {
            std::find(d.begin(), d.end(), productType) != d.end();
        }));
    }
#endif
    
    void TestFragments::FragmentNTermModTest()
    {
        auto tempVar = new OldSchoolChemicalFormulaModification (ChemicalFormula::ParseFormula("O"),
                                                                 "lala",
                                                                 ModificationSites::NTerminus);
        _mockPeptideEveryAminoAcid->AddModification(tempVar);
        Fragment *fragment = _mockPeptideEveryAminoAcid->Fragment(FragmentTypes::b, 1)[0];

        // Assert::IsTrue(fragment->getModifications().SequenceEqual(std::vector<OldSchoolModification*>
        // {new OldSchoolChemicalFormulaModification(ChemicalFormula::ParseFormula("O"), "lala",
        // ModificationSites::NTerminus)}));
        std::vector<IHasMass*> mods (fragment->getModifications().size(), tempVar);
        Assert::IsTrue ( Assert::SequenceEqual(fragment->getModifications(), mods ));
    }

    void TestFragments::FragmentModifications()
    {
        auto tempVar = new OldSchoolModification (1, "mod1", ModificationSites::C);
        _mockPeptideEveryAminoAcid->AddModification(tempVar);

        auto tempVar2 = new OldSchoolModification(2, "mod2", ModificationSites::D);
        _mockPeptideEveryAminoAcid->AddModification(tempVar2);

        auto tempVar3 = new OldSchoolModification(3, "mod3", ModificationSites::A);
        _mockPeptideEveryAminoAcid->AddModification(tempVar3);

        auto tempVar4 = new OldSchoolModification(4, "mod4", ModificationSites::Y);
        _mockPeptideEveryAminoAcid->AddModification(tempVar4);

        Fragment *fragment = _mockPeptideEveryAminoAcid->Fragment(FragmentTypes::b, 1).front();
        Fragment *fragmentEnd = _mockPeptideEveryAminoAcid->Fragment(FragmentTypes::y, 1).back();

        std::vector<IHasMass *> mods3 (fragment->getModifications().size(), tempVar3);
        Assert::IsTrue(Assert::SequenceEqual(fragment->getModifications(), mods3));

        std::vector<IHasMass *> mods4 (fragmentEnd->getModifications().size(), tempVar4);
        Assert::IsTrue(Assert::SequenceEqual(fragmentEnd->getModifications(), mods4));
    }

    void TestFragments::ChemicalFormulaFragment()
    {
        auto a = _mockPeptideEveryAminoAcid->Fragment(FragmentTypes::b, true);
        // Can break in 19 places
        Assert::AreEqual((long unsigned int)19, a.size());
#ifdef ORIG
        Assert::IsTrue(a.Select([&] (std::any b)
        {
            b::Sequence;
        })->Contains("ACDEFG"));
#endif
        bool found = false;
        for ( auto b : a ) {
            std::string s = b->getSequence();
            std::size_t f = s.find("ACDEFG");
            if (f != std::string::npos ) {
                found = true;
            }
        }
        Assert::IsTrue(found);

        auto y = _mockPeptideEveryAminoAcid->Fragment(FragmentTypes::y, true);
        // Can break in 19 places
#ifdef ORIG
        Assert::IsTrue(y.Select([&] (std::any b)
        {
            b::Sequence;
        })->Contains("TVWY"));
#endif
        found = false;
        for ( auto b : y ) {
            std::string s = b->getSequence();
            std::size_t f = s.find("TVWY");
            if ( f != std::string::npos ) {
                found = true;
            }
        }
        Assert::IsTrue(found);
            
        auto c = _mockPeptideEveryAminoAcid->Fragment(FragmentTypes::b, true);
        Assert::IsTrue(a.front()->Equals( c.front()));
    }

    void TestFragments::TestGetSiteDeterminingFragments()
    {
        auto pep1 = new Peptide("ACDEFG");
        auto pep2 = new Peptide("ACTVWY");
        auto ok = pep1->GetSiteDeterminingFragments(pep2, FragmentTypes::b);
        Assert::AreEqual((long unsigned int) 6, ok.size());
#ifdef ORIG
        Assert->Contains("ACT", ok.Select([&] (std::any b)
        {
            b::Sequence;
        })->ToArray());
#endif
        delete pep1;
        delete pep2;
    }

    void TestFragments::TestFormulaTerminusMods()
    {
        auto pep1 = new Peptide("ACDEFG");
        OldSchoolChemicalFormulaModification tempVar(ChemicalFormula::ParseFormula("H"), ModificationSites::NTerminus);
        pep1->AddModification(&tempVar);

        Assert::IsTrue(dynamic_cast<IHasChemicalFormula*>(pep1->Fragment(FragmentTypes::b, true).front()) != nullptr);

        auto pep2 = new Peptide("ACDEFG");
        OldSchoolModification tempVar2(2, "haha", ModificationSites::NTerminus);
        pep2->AddModification(&tempVar2);
        Assert::IsFalse(dynamic_cast<IHasChemicalFormula*>(pep2->Fragment(FragmentTypes::b, true).front()) != nullptr);

        auto pep3 = new Peptide("ACDEFG");
        OldSchoolModification tempVar3(3, "haha", ModificationSites::D);
        pep3->AddModification(&tempVar3);

        auto list = pep3->Fragment(FragmentTypes::b, true);

        Assert::IsTrue(dynamic_cast<IHasChemicalFormula*>(list[0]) != nullptr);
        Assert::IsFalse(dynamic_cast<IHasChemicalFormula*>(list[2]) != nullptr);

        delete pep3;
        delete pep2;
        delete pep1;
    }

#ifdef LATER
    void TestFragments::CleavageIndicesTest()
    {
        std::vector<IProtease*> proteases = {new TestProtease()};
        auto ok1 = Proteomics::AminoAcidPolymer::AminoAcidPolymer::GetCleavageIndexes("ACDEFG", proteases, true);
        auto ok2 = Proteomics::AminoAcidPolymer::AminoAcidPolymer::GetCleavageIndexes("ACDEFG", proteases, false);
        auto ok3 = Proteomics::AminoAcidPolymer::AminoAcidPolymer::GetCleavageIndexes("ACDE", proteases, true);
        auto ok4 = Proteomics::AminoAcidPolymer::AminoAcidPolymer::GetCleavageIndexes("ACDE", proteases, false);
        Assert::AreEqual(3, (int)ok1.size());
        Assert::AreEqual(2, (int)ok2.size());
        Assert::AreEqual(4, (int)ok3.size());
        Assert::AreEqual(2, (int)ok4.size());
    }

    void TestFragments::TestGetIonCapFailFail()
    {
        FragmentTypes f = FragmentTypes::All;
        Assert::That([&] ()
        {
            f::GetIonCap();
        }, Throws::TypeOf<MzLibException*>().With::Property("Message").EqualTo("Fragment Type must be a single value to determine the ion cap"));
    }

    void TestFragments::TestGetTerminusFail()
    {
        FragmentTypes f = FragmentTypes::a | FragmentTypes::adot;
        Assert::That([&] ()
        {
            f::GetTerminus();
        }, Throws::TypeOf<MzLibException*>().With::Property("Message").EqualTo("Fragment Type must be a single value to determine the terminus"));
    }
#endif
    
    
    void TestFragments::Test_GetTheoreticalFragments_UnmodifiedPeptide()
    {
        Protein *p = new Protein("PET", "accession");
        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 2, INT_MAX, 1024,
                                                               InitiatorMethionineBehavior::Variable, 2,
                                                               CleavageSpecificity::Full, FragmentationTerminus::Both);
        
        std::vector<Modification*> vm1, vm2;
        auto aPeptideWithSetModifications = p->Digest(digestionParams, vm1, vm2).front();
        
        auto theseTheoreticalFragments = aPeptideWithSetModifications->Fragment(DissociationType::HCD, FragmentationTerminus::Both);
        
        //evaluate N-terminal masses
#ifdef ORIG
        auto nTerminalMasses = theseTheoreticalFragments->Where([&] (std::any f)   {
                return f::TerminusFragment->Terminus == FragmentationTerminus::N;
            }).ToList();
#endif
        std::vector<Product*> nTerminalMasses;
        for ( auto f : theseTheoreticalFragments ) {
            if ( f->TerminusFragment->Terminus == FragmentationTerminus::N ) {
                nTerminalMasses.push_back(f);
            }
        }
        
        std::unordered_set<int> expectedNTerminalMasses = {97, 226};
        std::unordered_set<int> intnTerminalMasses;
        for ( auto v: nTerminalMasses ) {
            intnTerminalMasses.emplace(static_cast<int>(std::round(v->NeutralMass * std::pow(10, 0))) / std::pow(10, 0));
        }
        Assert::IsTrue(expectedNTerminalMasses == intnTerminalMasses );
        
#ifdef ORIG
        auto nTerminalMassesLabels = theseTheoreticalFragments->Where([&] (std::any f)    {
                return f::TerminusFragment->Terminus == FragmentationTerminus::N;
            })->Select([&] (std::any f)      {
                    f.ToString();
                }).ToList();
#endif
        std::vector<std::string> nTerminalMassesLabels;
        for ( auto f: nTerminalMasses ) {
            nTerminalMassesLabels.push_back(f->ToString() );
        }
        
        std::vector<std::string> expectedNTerminalMassesLabels = {"b1;97.052763849-0", "b2;226.09535694-0"};
        Assert::IsTrue(expectedNTerminalMassesLabels == nTerminalMassesLabels);
        
        //evaluate C-terminal masses
#ifdef ORIG
        auto cTerminalMasses = theseTheoreticalFragments->Where([&] (std::any f)    {
                return f::TerminusFragment->Terminus == FragmentationTerminus::C;
            }).ToList();
#endif
        std::vector<Product *>cTerminalMasses;
        for ( auto f: theseTheoreticalFragments ) {
            if (f->TerminusFragment->Terminus == FragmentationTerminus::C) {
                cTerminalMasses.push_back(f);
            }
        }
        
        std::unordered_set<int> expectedCTerminalMasses = {119, 248};
        std::unordered_set<int> intCTerminalMasses;
        for ( auto v: cTerminalMasses ) {
            intCTerminalMasses.emplace (static_cast<int>(std::round(v->NeutralMass * std::pow(10, 0))) / std::pow(10, 0));
        }
        Assert::IsTrue(expectedCTerminalMasses == intCTerminalMasses );
        
#ifdef ORIG
        auto cTerminalMassesLabels = theseTheoreticalFragments->Where([&] (std::any f)    {
                return f::TerminusFragment->Terminus == FragmentationTerminus::C;
            })->Select([&] (std::any f)      {
                    f.ToString();
                }).ToList();
#endif
        std::vector<std::string> cTerminalMassesLabels;
        for ( auto f: theseTheoreticalFragments ) {
            if (f->TerminusFragment->Terminus == FragmentationTerminus::C ) {
                cTerminalMassesLabels.push_back(f->ToString() );
            }
        }
        
        std::vector<std::string> expectedCTerminalMassesLabels = {"y1;119.05824315-0", "y2;248.10083624-0"};
                Assert::IsTrue(expectedCTerminalMassesLabels == cTerminalMassesLabels);
        
        delete digestionParams;
        delete p;
    }
    
    void TestFragments::Test_GetTheoreticalFragments_nTerminalModifiedPeptide()
    {
        Protein *p = new Protein("PET", "accession");
        ModificationMotif *motif;
        ModificationMotif::TryGetMotif("P", &motif);
        Modification *phosphorylation = new Modification("phospho", "", "CommonBiological", "", motif, "Anywhere.",
                                                         ChemicalFormula::ParseFormula("H1O3P1"), std::nullopt,
                                                         std::unordered_map<std::string, std::vector<std::string>>(),
                                                         std::unordered_map<std::string, std::vector<std::string>>(),
                                                         std::vector<std::string>(), std::unordered_map<DissociationType,
                                                         std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");
        
        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 2, INT_MAX, 1024, InitiatorMethionineBehavior::Variable, 2,
                                                               CleavageSpecificity::Full, FragmentationTerminus::Both);
        
        std::vector<Modification*> vm1 = {phosphorylation}, vm2 ;
        auto aPeptideWithSetModifications = p->Digest(digestionParams, vm1, vm2).front();
        
        auto theseTheoreticalFragments = aPeptideWithSetModifications->Fragment(DissociationType::HCD, FragmentationTerminus::Both);
        
        //evaluate N-terminal masses
#ifdef ORIG
        auto nTerminalMasses = theseTheoreticalFragments->Where([&] (std::any f)  {
                return f::TerminusFragment->Terminus == FragmentationTerminus::N;
            }).ToList();
#endif
        std::vector<Product *> nTerminalMasses;
        for ( auto f: theseTheoreticalFragments ) {
            if ( f->TerminusFragment->Terminus == FragmentationTerminus::N ) {
                nTerminalMasses.push_back(f);
            }
        }
        std::unordered_set<int> expectedNTerminalMasses = {177, 306};
        std::unordered_set<int> intnTerminalMasses;
        for ( auto v: nTerminalMasses ) {
            intnTerminalMasses.emplace(static_cast<int>(std::round(v->NeutralMass * std::pow(10, 0))) / std::pow(10, 0));
        }
        Assert::IsTrue(expectedNTerminalMasses == intnTerminalMasses );

#ifdef ORIG
        auto nTerminalMassesLabels = theseTheoreticalFragments->Where([&] (std::any f)
        {
            return f::TerminusFragment->Terminus == FragmentationTerminus::N;
        })->Select([&] (std::any f)
        {
            f.ToString();
        }).ToList();
#endif
        std::vector<std::string> nTerminalMassesLabels;
        for ( auto f : nTerminalMasses ) {
            nTerminalMassesLabels.push_back(f->ToString() );
        }

        std::vector<std::string> expectedNTerminalMassesLabels = {"b1;177.01909474-0", "b2;306.06168783-0"};
        Assert::IsTrue(expectedNTerminalMassesLabels == nTerminalMassesLabels);

        //evaluate C-terminal masses
#ifdef ORIG
        auto cTerminalMasses = theseTheoreticalFragments->Where([&] (std::any f)
        {
            return f::TerminusFragment->Terminus == FragmentationTerminus::C;
        }).ToList();
#endif
        std::vector<Product *> cTerminalMasses;
        for ( auto f: theseTheoreticalFragments ) {
            if (f->TerminusFragment->Terminus == FragmentationTerminus::C) {
                cTerminalMasses.push_back(f);
            }
        }

        std::unordered_set<int> expectedCTerminalMasses = {119, 248};
        std::unordered_set<int> intcTerminalMasses;
        for ( auto v: cTerminalMasses ) {
            intcTerminalMasses.emplace(static_cast<int>(std::round(v->NeutralMass * std::pow(10, 0))) / std::pow(10, 0));
        }

        Assert::IsTrue(expectedCTerminalMasses == intcTerminalMasses);

#ifdef ORIG
        auto cTerminalMassesLabels = theseTheoreticalFragments->Where([&] (std::any f)
        {
            return f::TerminusFragment->Terminus == FragmentationTerminus::C;
        })->Select([&] (std::any f)
        {
            f.ToString();
        }).ToList();
#endif
        std::vector<std::string> cTerminalMassesLabels;
        for ( auto f : cTerminalMasses ) {
            cTerminalMassesLabels.push_back(f->ToString());
        }
        std::vector<std::string> expectedCTerminalMassesLabels = {"y1;119.05824315-0", "y2;248.10083624-0"};
                Assert::IsTrue(expectedCTerminalMassesLabels == cTerminalMassesLabels);

        delete digestionParams;
        delete phosphorylation;
        delete p;
    }

    void TestFragments::Test_GetTheoreticalFragments_cTerminalModifiedPeptide()
    {
        Protein *p = new Protein("PET", "accession");
        ModificationMotif *motif;
        ModificationMotif::TryGetMotif("T", &motif);
        Modification *phosphorylation = new Modification("phospho", "", "CommonBiological", "", motif, "Anywhere.",
                                                         ChemicalFormula::ParseFormula("H1O3P1"), std::nullopt,
                                                         std::unordered_map<std::string, std::vector<std::string>>(),
                                                         std::unordered_map<std::string, std::vector<std::string>>(),
                                                         std::vector<std::string>(), std::unordered_map<DissociationType,
                                                         std::vector<double>>(), std::unordered_map<DissociationType,
                                                         std::vector<double>>(), "");
        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 2, INT_MAX, 1024, InitiatorMethionineBehavior::Variable, 2,
                                                               CleavageSpecificity::Full, FragmentationTerminus::Both);
        
        std::vector<Modification*> vm1 = {phosphorylation}, vm2;
        auto aPeptideWithSetModifications = p->Digest(digestionParams, vm1, vm2).front();
        
        auto theseTheoreticalFragments = aPeptideWithSetModifications->Fragment(DissociationType::HCD, FragmentationTerminus::Both);
        
        //evaluate N-terminal masses
#ifdef ORIG
        auto nTerminalMasses = theseTheoreticalFragments->Where([&] (std::any f)   {
                return f::TerminusFragment->Terminus == FragmentationTerminus::N;
            }).ToList();
#endif
        std::vector<Product *> nTerminalMasses;
        for ( auto f: theseTheoreticalFragments ) {
            if ( f->TerminusFragment->Terminus == FragmentationTerminus::N ) {
                nTerminalMasses.push_back(f);
            }
        }
        std::unordered_set<int> expectedNTerminalMasses = {97, 226};
        std::unordered_set<int> intnTerminalMasses;
        for ( auto v : nTerminalMasses ){
            intnTerminalMasses.emplace(static_cast<int>(std::round(v->NeutralMass * std::pow(10, 0))) / std::pow(10, 0) );
        }
        Assert::IsTrue(expectedNTerminalMasses == intnTerminalMasses);
        
#ifdef ORIG
        auto nTerminalMassesLabels = theseTheoreticalFragments->Where([&] (std::any f)   {
                return f::TerminusFragment->Terminus == FragmentationTerminus::N;
            })->Select([&] (std::any f)  {
                    f.ToString();
                }).ToList();
#endif
        std::vector<std::string> nTerminalMassesLabels;
        for ( auto f : nTerminalMasses ) {
            nTerminalMassesLabels.push_back(f->ToString() );
        }
        std::vector<std::string> expectedNTerminalMassesLabels = {"b1;97.052763849-0", "b2;226.09535694-0"};
        Assert::IsTrue(expectedNTerminalMassesLabels == nTerminalMassesLabels);
        
        //evaluate C-terminal masses
#ifdef ORIG
        auto cTerminalMasses = theseTheoreticalFragments->Where([&] (std::any f)   {
                return f::TerminusFragment->Terminus == FragmentationTerminus::C;
            }).ToList();
#endif
        std::vector<Product*> cTerminalMasses;
        for ( auto f: theseTheoreticalFragments  ) {
            if ( f->TerminusFragment->Terminus == FragmentationTerminus::C ) {
                cTerminalMasses.push_back(f);
            }
        }
        
        std::unordered_set<int> expectedCTerminalMasses = {199, 328};
        std::unordered_set<int> intcTerminalMasses;
        for ( auto v: cTerminalMasses ) {
            intcTerminalMasses.emplace(static_cast<int>(std::round(v->NeutralMass * std::pow(10, 0))) / std::pow(10, 0));
        }
        Assert::IsTrue(expectedCTerminalMasses == intcTerminalMasses );
        
#ifdef ORIG
        auto cTerminalMassesLabels = theseTheoreticalFragments->Where([&] (std::any f)    {
            return f::TerminusFragment->Terminus == FragmentationTerminus::C;
        })->Select([&] (std::any f)     {
                f.ToString();
            }).ToList();
#endif
        std::vector<std::string> cTerminalMassesLabels;
        for ( auto f: cTerminalMasses ) {
            cTerminalMassesLabels.push_back(f->ToString() );
        }
        std::vector<std::string> expectedCTerminalMassesLabels = {"y1;199.02457404-0", "y2;328.06716713-0"};
        Assert::IsTrue(expectedCTerminalMassesLabels == cTerminalMassesLabels);
        
        delete digestionParams;
        delete phosphorylation;
        delete p;
    }
    
    void TestFragments::Test_GetTheoreticalFragments_internallyModifiedPeptide()
    {
        Protein *p = new Protein("PET", "accession");
        ModificationMotif *motif;
        ModificationMotif::TryGetMotif("E", &motif);
        Modification *phosphorylation = new Modification("phospho", "", "CommonBiological", "", motif, "Anywhere.",
                                                         ChemicalFormula::ParseFormula("H1O3P1"), std::nullopt,
                                                         std::unordered_map<std::string, std::vector<std::string>>(),
                                                         std::unordered_map<std::string, std::vector<std::string>>(),
                                                         std::vector<std::string>(), std::unordered_map<DissociationType,
                                                         std::vector<double>>(), std::unordered_map<DissociationType,
                                                         std::vector<double>>(), "");
        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 2, INT_MAX, 1024, InitiatorMethionineBehavior::Variable, 2,
                                                               CleavageSpecificity::Full, FragmentationTerminus::Both);

        std::vector<Modification*> vm1 = {phosphorylation}, vm2;
        auto aPeptideWithSetModifications = p->Digest(digestionParams, vm1, vm2).front();

        auto theseTheoreticalFragments = aPeptideWithSetModifications->Fragment(DissociationType::HCD, FragmentationTerminus::Both);

        //evaluate N-terminal masses
        std::unordered_set<int> foundNTerminalMasses;
        std::vector<std::string> nTerminalMassesLabels;
        for ( auto f: theseTheoreticalFragments ) {
            if ( f->TerminusFragment->Terminus == FragmentationTerminus::N ) {
                foundNTerminalMasses.emplace (static_cast<int>(std::round(f->NeutralMass * std::pow(10, 0))) / std::pow(10, 0));
                nTerminalMassesLabels.push_back(f->ToString());
            }
        }

        std::unordered_set<int> expectedNTerminalMasses = {97, 306};
        Assert::IsTrue(expectedNTerminalMasses == foundNTerminalMasses);
        std::vector<std::string> expectedNTerminalMassesLabels = {"b1;97.052763849-0", "b2;306.06168783-0"};
        Assert::IsTrue(expectedNTerminalMassesLabels==nTerminalMassesLabels);

        //evaluate C-terminal masses
        std::unordered_set<int> foundCTerminalMasses;
        std::vector<std::string> cTerminalMassesLabels;
        for ( auto f: theseTheoreticalFragments  ) {
            if ( f->TerminusFragment->Terminus == FragmentationTerminus::C ) {
                foundCTerminalMasses.emplace(static_cast<int>(std::round(f->NeutralMass * std::pow(10, 0))) / std::pow(10, 0));
                cTerminalMassesLabels.push_back(f->ToString() );
            }
        }
        std::unordered_set<int> expectedCTerminalMasses = {119, 328};
        Assert::IsTrue(expectedCTerminalMasses == foundCTerminalMasses);
        std::vector<std::string> expectedCTerminalMassesLabels = {"y1;119.05824315-0", "y2;328.06716713-0"};
        Assert::IsTrue(expectedCTerminalMassesLabels == cTerminalMassesLabels);

        delete digestionParams;
        delete phosphorylation;
        delete p;
    }

    void TestFragments::Test_GetTheoreticalFragments_nTerminalModifiedPeptide_NeutralLoss()
    {
        Protein *p = new Protein("PET", "accession");
        ModificationMotif *motif;
        ModificationMotif::TryGetMotif("P", &motif);
        Modification *phosphorylation = new Modification("phospho", "", "CommonBiological", "", motif, "Anywhere.",
                                                         ChemicalFormula::ParseFormula("H1O3P1"), std::nullopt,
                                                         std::unordered_map<std::string, std::vector<std::string>>(),
                                                         std::unordered_map<std::string, std::vector<std::string>>(),
                                                         std::vector<std::string>(),
                                                         std::unordered_map<DissociationType, std::vector<double>>
          {
              {
                  MassSpectrometry::DissociationType::HCD, {0, ChemicalFormula::ParseFormula("H3O4P1")->getMonoisotopicMass()}
              }
          },
                                                         std::unordered_map<DissociationType, std::vector<double>>(), "");

        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 2, INT_MAX, 1024, InitiatorMethionineBehavior::Variable, 2,
                                                               CleavageSpecificity::Full, FragmentationTerminus::Both);

        std::vector<Modification*> vm1 = {phosphorylation}, vm2;
        auto aPeptideWithSetModifications = p->Digest(digestionParams, vm1, vm2).front();

        auto theseTheoreticalFragments = aPeptideWithSetModifications->Fragment(DissociationType::HCD, FragmentationTerminus::Both);

        //evaluate N-terminal masses
        std::unordered_set<int> foundNTerminalMasses;
        std::set<std::string> nTerminalMassesLabels;
        for ( auto f: theseTheoreticalFragments ) {
            if ( f->TerminusFragment->Terminus == FragmentationTerminus::N ) {
                foundNTerminalMasses.emplace (static_cast<int>(std::round(f->NeutralMass * std::pow(10, 0))) / std::pow(10, 0));
                nTerminalMassesLabels.emplace(f->ToString());
            }
        }
        std::unordered_set<int> expectedNTerminalMasses = {177, 306, 79, 208};
        Assert::IsTrue(expectedNTerminalMasses == foundNTerminalMasses );

        std::set<std::string> expectedNTerminalMassesLabels = {"b1;177.01909474-0", "b2;306.06168783-0",
                                                               "b1;79.042199165-97.976895573",
                                                               "b2;208.08479225-97.976895573"};
        Assert::IsTrue(expectedNTerminalMassesLabels == nTerminalMassesLabels);

        //evaluate C-terminal masses
        std::unordered_set<int> foundCTerminalMasses;
        std::vector<std::string> cTerminalMassesLabels;
        for ( auto f: theseTheoreticalFragments  ) {
            if ( f->TerminusFragment->Terminus == FragmentationTerminus::C ) {
                foundCTerminalMasses.emplace(static_cast<int>(std::round(f->NeutralMass * std::pow(10, 0))) / std::pow(10, 0));
                cTerminalMassesLabels.push_back(f->ToString() );
            }
        }
        std::unordered_set<int> expectedCTerminalMasses = {119, 248};
        Assert::IsTrue(expectedCTerminalMasses == foundCTerminalMasses );
        std::vector<std::string> expectedCTerminalMassesLabels = {"y1;119.05824315-0", "y2;248.10083624-0"};
        Assert::IsTrue(expectedCTerminalMassesLabels == cTerminalMassesLabels);

        delete digestionParams;
        delete phosphorylation;
        delete p;
    }

    void TestFragments::Test_GetTheoreticalFragments_cTerminalModifiedPeptide_NeutralLoss()
    {
        Protein *p = new Protein("PET", "accession");
        ModificationMotif *motif;
        ModificationMotif::TryGetMotif("T", &motif);
        Modification *phosphorylation = new Modification("phospho", "", "CommonBiological", "", motif, "Anywhere.",
                                                         ChemicalFormula::ParseFormula("H1O3P1"), std::nullopt,
                                                         std::unordered_map<std::string, std::vector<std::string>>(),
                                                         std::unordered_map<std::string, std::vector<std::string>>(),
                                                         std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>
        {
            {
                MassSpectrometry::DissociationType::HCD, {0, ChemicalFormula::ParseFormula("H3O4P1")->getMonoisotopicMass()}
            }
        },
                                                         std::unordered_map<DissociationType, std::vector<double>>(), "");
        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 2, INT_MAX, 1024, InitiatorMethionineBehavior::Variable, 2,
                                                               CleavageSpecificity::Full, FragmentationTerminus::Both);
        std::vector<Modification*> vm1  = {phosphorylation}, vm2;
        auto aPeptideWithSetModifications = p->Digest(digestionParams, vm1, vm2).front();

        auto theseTheoreticalFragments = aPeptideWithSetModifications->Fragment(DissociationType::HCD, FragmentationTerminus::Both);

        //var nTerminalMasses = aCompactPeptide.TerminalMasses.Where(v => v.Terminus == FragmentationTerminus.N);
        //evaluate N-terminal masses
        std::unordered_set<int> foundNTerminalMasses;
        std::vector<std::string> nTerminalMassesLabels;
        for ( auto f: theseTheoreticalFragments ) {
            if ( f->TerminusFragment->Terminus == FragmentationTerminus::N ) {
                foundNTerminalMasses.emplace (static_cast<int>(std::round(f->NeutralMass * std::pow(10, 0))) / std::pow(10, 0));
                nTerminalMassesLabels.push_back(f->ToString());
            }
        }
        std::unordered_set<int> expectedNTerminalMasses = {97, 226};

        Assert::IsTrue(expectedNTerminalMasses == foundNTerminalMasses);
        std::vector<std::string> expectedNTerminalMassesLabels = {"b1;97.052763849-0", "b2;226.09535694-0"};
        Assert::IsTrue(expectedNTerminalMassesLabels == nTerminalMassesLabels);

        //evaluate C-terminal masses
        std::unordered_set<int> foundCTerminalMasses;
        std::set<std::string> cTerminalMassesLabels;
        for ( auto f: theseTheoreticalFragments  ) {
            if ( f->TerminusFragment->Terminus == FragmentationTerminus::C ) {
                foundCTerminalMasses.emplace(static_cast<int>(std::round(f->NeutralMass * std::pow(10, 0))) / std::pow(10, 0));
                cTerminalMassesLabels.emplace(f->ToString() );
            }
        }
        std::unordered_set<int> expectedCTerminalMasses = {199, 328, 101, 230};

        Assert::IsTrue(expectedCTerminalMasses == foundCTerminalMasses);
        std::set<std::string> expectedCTerminalMassesLabels = {"y1;199.02457404-0", "y2;328.06716713-0",
                                                               "y1;101.04767847-97.976895573",
                                                               "y2;230.09027156-97.976895573"};
        Assert::IsTrue(expectedCTerminalMassesLabels == cTerminalMassesLabels);

        delete digestionParams;
        delete phosphorylation;
        delete p;
    }


    void TestFragments::Test_GetTheoreticalFragments_internallyModifiedPeptide_NeutralLoss()
    {
        Protein *p = new Protein("PET", "accession");
        ModificationMotif *motif;
        ModificationMotif::TryGetMotif("E", &motif);
        Modification *phosphorylation = new Modification("phospho", "", "CommonBiological", "", motif, "Anywhere.",
                                                         ChemicalFormula::ParseFormula("H1O3P1"), std::nullopt,
                                                         std::unordered_map<std::string, std::vector<std::string>>(),
                                                         std::unordered_map<std::string, std::vector<std::string>>(),
                                                         std::vector<std::string>(),
                                                         std::unordered_map<DissociationType, std::vector<double>>
        {
            {
                MassSpectrometry::DissociationType::HCD, {0, ChemicalFormula::ParseFormula("H3O4P1")->getMonoisotopicMass()}
            }
        },
                                                         std::unordered_map<DissociationType, std::vector<double>>(), "");
        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 2, INT_MAX, 1024,
                                                               InitiatorMethionineBehavior::Variable, 2,
                                                               CleavageSpecificity::Full, FragmentationTerminus::Both);
        std::vector<Modification*> vm1 = {phosphorylation}, vm2;
        auto aPeptideWithSetModifications = p->Digest(digestionParams, vm1, vm2).front();

        auto theseTheoreticalFragments = aPeptideWithSetModifications->Fragment(DissociationType::HCD, FragmentationTerminus::Both);

        //evaluate N-terminal masses
        std::unordered_set<int> foundNTerminalMasses;
        std::set<std::string> nTerminalMassesLabels;
        for ( auto f: theseTheoreticalFragments ) {
            if ( f->TerminusFragment->Terminus == FragmentationTerminus::N ) {
                foundNTerminalMasses.emplace (static_cast<int>(std::round(f->NeutralMass * std::pow(10, 0))) / std::pow(10, 0));
                nTerminalMassesLabels.emplace(f->ToString());
            }
        }

        std::unordered_set<int> expectedNTerminalMasses = {97, 306, 208};
        Assert::IsTrue(expectedNTerminalMasses == foundNTerminalMasses);
        std::set<std::string> expectedNTerminalMassesLabels = {"b1;97.052763849-0", "b2;306.06168783-0", "b2;208.08479225-97.976895573"};
        Assert::IsTrue(expectedNTerminalMassesLabels == nTerminalMassesLabels);

        //evaluate C-terminal masses
        std::unordered_set<int> foundCTerminalMasses;
        std::set<std::string> cTerminalMassesLabels;
        for ( auto f: theseTheoreticalFragments  ) {
            if ( f->TerminusFragment->Terminus == FragmentationTerminus::C ) {
                foundCTerminalMasses.emplace(static_cast<int>(std::round(f->NeutralMass * std::pow(10, 0))) / std::pow(10, 0));
                cTerminalMassesLabels.emplace(f->ToString() );
            }
        }
        std::unordered_set<int> expectedCTerminalMasses = {119, 328, 230};
        Assert::IsTrue(expectedCTerminalMasses == foundCTerminalMasses);
        std::set<std::string> expectedCTerminalMassesLabels = {"y1;119.05824315-0", "y2;328.06716713-0", "y2;230.09027156-97.976895573"};
        Assert::IsTrue(expectedCTerminalMassesLabels == cTerminalMassesLabels);

        delete digestionParams;
        delete phosphorylation;
        delete p;
    }

    void TestFragments::Test_GetTheoreticalFragments_nTerminalModifiedPeptide_NeutralLoss_DissociationTypes_AnyActivationType_and_HCD()
    {
        Protein *p = new Protein("PET", "accession");
        ModificationMotif *motif;
        ModificationMotif::TryGetMotif("P", &motif);
        Modification *phosphorylation = new Modification("phospho", "", "CommonBiological", "", motif, "Anywhere.",
                                                         ChemicalFormula::ParseFormula("H1O3P1"), std::nullopt,
                                                         std::unordered_map<std::string, std::vector<std::string>>(),
                                                         std::unordered_map<std::string, std::vector<std::string>>(),
                                                         std::vector<std::string>(),
                                                         std::unordered_map<DissociationType, std::vector<double>>
        {
            {
                MassSpectrometry::DissociationType::AnyActivationType, {0, ChemicalFormula::ParseFormula("H3O4P1")->getMonoisotopicMass()}
            }
        },
                                                         std::unordered_map<DissociationType, std::vector<double>>(), "");
        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 2, INT_MAX, 1024,
                                                               InitiatorMethionineBehavior::Variable, 2,
                                                               CleavageSpecificity::Full, FragmentationTerminus::Both);
        std::vector<Modification*> vm1 = {phosphorylation}, vm2;
        auto aPeptideWithSetModifications = p->Digest(digestionParams, vm1, vm2).front();

        auto theseTheoreticalFragments = aPeptideWithSetModifications->Fragment(DissociationType::AnyActivationType, FragmentationTerminus::Both);

        //evaluate N-terminal masses
        std::unordered_set<int> foundNTerminalMasses;
        std::set<std::string> nTerminalMassesLabels;
        for ( auto f: theseTheoreticalFragments ) {
            if ( f->TerminusFragment->Terminus == FragmentationTerminus::N ) {
                foundNTerminalMasses.emplace (static_cast<int>(std::round(f->NeutralMass * std::pow(10, 0))) / std::pow(10, 0));
                nTerminalMassesLabels.emplace(f->ToString());
            }
        }
        std::unordered_set<int> expectedNTerminalMasses = {177, 306, 79, 208};
        Assert::IsTrue(expectedNTerminalMasses == foundNTerminalMasses);
        std::set<std::string> expectedNTerminalMassesLabels = {"b1;177.01909474-0",
                                                               "b2;306.06168783-0",
                                                               "b1;79.042199165-97.976895573",
                                                               "b2;208.08479225-97.976895573"};
        Assert::IsTrue(expectedNTerminalMassesLabels == nTerminalMassesLabels);

        //evaluate C-terminal masses
        std::unordered_set<int> foundCTerminalMasses;
        std::set<std::string> cTerminalMassesLabels;
        for ( auto f: theseTheoreticalFragments  ) {
            if ( f->TerminusFragment->Terminus == FragmentationTerminus::C ) {
                foundCTerminalMasses.emplace(static_cast<int>(std::round(f->NeutralMass * std::pow(10, 0))) / std::pow(10, 0));
                cTerminalMassesLabels.emplace(f->ToString() );
            }
        }
        std::unordered_set<int> expectedCTerminalMasses = {119, 248};
        Assert::IsTrue(expectedCTerminalMasses == foundCTerminalMasses);
        std::set<std::string> expectedCTerminalMassesLabels = {"y1;119.05824315-0", "y2;248.10083624-0"};
        Assert::IsTrue(expectedCTerminalMassesLabels == cTerminalMassesLabels);
        
        delete digestionParams;
        delete phosphorylation;
        delete p;
    }

    void TestFragments::Test_GetTheoreticalFragments_nTerminalModifiedPeptide_NeutralLoss_DissociationTypes_CID_and_HCD()
    {
        Protein *p = new Protein("PET", "accession");
        ModificationMotif *motif;
        ModificationMotif::TryGetMotif("P", &motif);
        Modification *phosphorylation = new Modification("phospho", "", "CommonBiological", "", motif, "Anywhere.",
                                                         ChemicalFormula::ParseFormula("H1O3P1"), std::nullopt,
                                                         std::unordered_map<std::string, std::vector<std::string>>(),
                                                         std::unordered_map<std::string, std::vector<std::string>>(),
                                                         std::vector<std::string>(),
                                                         std::unordered_map<DissociationType, std::vector<double>>
        {
            {
                MassSpectrometry::DissociationType::CID, {0, ChemicalFormula::ParseFormula("H3O4P1")->getMonoisotopicMass()}
            }
        },
                                                         std::unordered_map<DissociationType, std::vector<double>>(), "");
        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 2, INT_MAX, 1024,
                                                               InitiatorMethionineBehavior::Variable, 2,
                                                               CleavageSpecificity::Full, FragmentationTerminus::Both);
        std::vector<Modification*> vm1 = {phosphorylation}, vm2;
        auto aPeptideWithSetModifications = p->Digest(digestionParams, vm1, vm2).front();

        auto theseTheoreticalFragments = aPeptideWithSetModifications->Fragment(DissociationType::HCD, FragmentationTerminus::Both);
        //Note that dissociation type here intentionally mismatched to dissociation type in modification constructor

        //evaluate N-terminal masses
        std::unordered_set<int> foundNTerminalMasses;
        std::set<std::string> nTerminalMassesLabels;
        for ( auto f: theseTheoreticalFragments ) {
            if ( f->TerminusFragment->Terminus == FragmentationTerminus::N ) {
                foundNTerminalMasses.emplace (static_cast<int>(std::round(f->NeutralMass * std::pow(10, 0))) / std::pow(10, 0));
                nTerminalMassesLabels.emplace(f->ToString());
            }
        }
        std::unordered_set<int> expectedNTerminalMasses = {177, 306};
        Assert::IsTrue(expectedNTerminalMasses == foundNTerminalMasses );
        std::set<std::string> expectedNTerminalMassesLabels = {"b1;177.01909474-0", "b2;306.06168783-0"};
        Assert::IsTrue(expectedNTerminalMassesLabels == nTerminalMassesLabels);

        //evaluate C-terminal masses
        std::unordered_set<int> foundCTerminalMasses;
        std::set<std::string> cTerminalMassesLabels;
        for ( auto f: theseTheoreticalFragments  ) {
            if ( f->TerminusFragment->Terminus == FragmentationTerminus::C ) {
                foundCTerminalMasses.emplace(static_cast<int>(std::round(f->NeutralMass * std::pow(10, 0))) / std::pow(10, 0));
                cTerminalMassesLabels.emplace(f->ToString() );
            }
        }
        std::unordered_set<int> expectedCTerminalMasses = {119, 248};
        Assert::IsTrue(expectedCTerminalMasses == foundCTerminalMasses);
        std::set<std::string> expectedCTerminalMassesLabels = {"y1;119.05824315-0", "y2;248.10083624-0"};
        Assert::IsTrue(expectedCTerminalMassesLabels == cTerminalMassesLabels);

        delete digestionParams;
        delete phosphorylation;
        delete p;
    }

    void TestFragments::Test_GetTheoreticalFragments_ProductTypeLabel()
    {
        Protein *p = new Protein("PET", "accession");
        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 2, INT_MAX, 1024,
                                                               InitiatorMethionineBehavior::Variable, 2,
                                                               CleavageSpecificity::Full, FragmentationTerminus::Both);
        std::vector<Modification*> vm1, vm2;
        auto aPeptideWithSetModifications = p->Digest(digestionParams, vm1, vm2).front();

        auto theseTheoreticalFragments = aPeptideWithSetModifications->Fragment(DissociationType::HCD,
                                                                                FragmentationTerminus::N);

        std::set<std::string> nTerminalMassesLabels;
        for ( auto f: theseTheoreticalFragments ) {
            if ( f->TerminusFragment->Terminus == FragmentationTerminus::N ) {
                nTerminalMassesLabels.emplace(f->ToString());
            }
        }
        std::set<std::string> expectedNTerminalMassesLabels = {"b1;97.052763849-0", "b2;226.09535694-0"};
        Assert::IsTrue(expectedNTerminalMassesLabels == nTerminalMassesLabels);

        theseTheoreticalFragments = aPeptideWithSetModifications->Fragment(DissociationType::AnyActivationType,
                                                                           FragmentationTerminus::N);
        nTerminalMassesLabels.clear();
        for ( auto f: theseTheoreticalFragments ) {
            if ( f->TerminusFragment->Terminus == FragmentationTerminus::N ) {
                nTerminalMassesLabels.emplace(f->ToString());
            }
        }

        expectedNTerminalMassesLabels.clear();        
        expectedNTerminalMassesLabels = {"b1;97.052763849-0", "b2;226.09535694-0"};
        Assert::IsTrue(expectedNTerminalMassesLabels == nTerminalMassesLabels);

        theseTheoreticalFragments = aPeptideWithSetModifications->Fragment(DissociationType::CID, FragmentationTerminus::N);
        nTerminalMassesLabels.clear();
        for ( auto f: theseTheoreticalFragments ) {
            if ( f->TerminusFragment->Terminus == FragmentationTerminus::N ) {
                nTerminalMassesLabels.emplace(f->ToString());
            }
        }

        expectedNTerminalMassesLabels.clear();        
        expectedNTerminalMassesLabels = {"b2;226.09535694-0"};
        Assert::IsTrue(expectedNTerminalMassesLabels == nTerminalMassesLabels);

        theseTheoreticalFragments = aPeptideWithSetModifications->Fragment(DissociationType::ECD, FragmentationTerminus::N);
        nTerminalMassesLabels.clear();
        for ( auto f: theseTheoreticalFragments ) {
            if ( f->TerminusFragment->Terminus == FragmentationTerminus::N ) {
                nTerminalMassesLabels.emplace(f->ToString());
            }
        }

        expectedNTerminalMassesLabels.clear();        
        expectedNTerminalMassesLabels = {"c1;114.07931295-0", "c2;243.12190604-0"};
        Assert::IsTrue(expectedNTerminalMassesLabels == nTerminalMassesLabels);

        theseTheoreticalFragments = aPeptideWithSetModifications->Fragment(DissociationType::ETD, FragmentationTerminus::N);
        nTerminalMassesLabels.clear();
        for ( auto f: theseTheoreticalFragments ) {
            if ( f->TerminusFragment->Terminus == FragmentationTerminus::N ) {
                nTerminalMassesLabels.emplace(f->ToString());
            }
        }

        expectedNTerminalMassesLabels.clear();        
        expectedNTerminalMassesLabels = {"c1;114.07931295-0", "c2;243.12190604-0"};
        Assert::IsTrue(expectedNTerminalMassesLabels == nTerminalMassesLabels);

        theseTheoreticalFragments = aPeptideWithSetModifications->Fragment(DissociationType::EThcD, FragmentationTerminus::N);
        nTerminalMassesLabels.clear();
        for ( auto f: theseTheoreticalFragments ) {
            if ( f->TerminusFragment->Terminus == FragmentationTerminus::N ) {
                nTerminalMassesLabels.emplace(f->ToString());
            }
        }

        expectedNTerminalMassesLabels.clear();        
        expectedNTerminalMassesLabels = {"b1;97.052763849-0", "b2;226.09535694-0", "c1;114.07931295-0", "c2;243.12190604-0"};
        Assert::IsTrue(expectedNTerminalMassesLabels == nTerminalMassesLabels);

        theseTheoreticalFragments = aPeptideWithSetModifications->Fragment(DissociationType::ISCID, FragmentationTerminus::N);
        nTerminalMassesLabels.clear();
        for ( auto f: theseTheoreticalFragments ) {
            if ( f->TerminusFragment->Terminus == FragmentationTerminus::N ) {
                nTerminalMassesLabels.emplace(f->ToString());
            }
        }

        expectedNTerminalMassesLabels.clear();        
        expectedNTerminalMassesLabels = { };
        Assert::IsTrue(expectedNTerminalMassesLabels == nTerminalMassesLabels);

        DissociationTypeCollection::ProductsFromDissociationType[DissociationType::Custom] = { };
        theseTheoreticalFragments = aPeptideWithSetModifications->Fragment(DissociationType::Custom, FragmentationTerminus::N);
        nTerminalMassesLabels.clear();
        for ( auto f: theseTheoreticalFragments ) {
            if ( f->TerminusFragment->Terminus == FragmentationTerminus::N ) {
                nTerminalMassesLabels.emplace(f->ToString());
            }
        }

        expectedNTerminalMassesLabels.clear();        
        expectedNTerminalMassesLabels = { };
        Assert::IsTrue(expectedNTerminalMassesLabels == nTerminalMassesLabels);

        theseTheoreticalFragments = aPeptideWithSetModifications->Fragment(DissociationType::IRMPD, FragmentationTerminus::N);
        nTerminalMassesLabels.clear();
        for ( auto f: theseTheoreticalFragments ) {
            if ( f->TerminusFragment->Terminus == FragmentationTerminus::N ) {
                nTerminalMassesLabels.emplace(f->ToString());
            }
        }

        expectedNTerminalMassesLabels.clear();        
        expectedNTerminalMassesLabels = {"b1;97.052763849-0", "b2;226.09535694-0"};
        Assert::IsTrue(expectedNTerminalMassesLabels == nTerminalMassesLabels);

        theseTheoreticalFragments = aPeptideWithSetModifications->Fragment(DissociationType::PQD, FragmentationTerminus::N);
        nTerminalMassesLabels.clear();
        for ( auto f: theseTheoreticalFragments ) {
            if ( f->TerminusFragment->Terminus == FragmentationTerminus::N ) {
                nTerminalMassesLabels.emplace(f->ToString());
            }
        }

        expectedNTerminalMassesLabels.clear();        
        expectedNTerminalMassesLabels = { };
        Assert::IsTrue(expectedNTerminalMassesLabels == nTerminalMassesLabels);

        delete digestionParams;
        delete p;
    }

    void TestFragments::Test_Fragment_DiagnosticIons()
    {
        Protein *p = new Protein("PET", "accession");
        ModificationMotif *motif;
        ModificationMotif::TryGetMotif("P", &motif);
        Modification *phosphorylation = new Modification("phospho", "", "CommonBiological", "", motif, "Anywhere.",
                                                         ChemicalFormula::ParseFormula("H1O3P1"), std::nullopt,
                                                         std::unordered_map<std::string, std::vector<std::string>>(),
                                                         std::unordered_map<std::string, std::vector<std::string>>(),
                                                         std::vector<std::string>(),
                                                         std::unordered_map<DissociationType, std::vector<double>>
        {
            {
                MassSpectrometry::DissociationType::HCD, {0, ChemicalFormula::ParseFormula("H3O4P1")->getMonoisotopicMass()}
            }
        },
                                                         std::unordered_map<DissociationType, std::vector<double>>
        {
            {
                MassSpectrometry::DissociationType::HCD, {ChemicalFormula::ParseFormula("H3O4P1")->getMonoisotopicMass()}
            }
        },
        "");
        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 2, INT_MAX, 1024,
                                                               InitiatorMethionineBehavior::Variable, 2,
                                                               CleavageSpecificity::Full, FragmentationTerminus::Both);
        std::vector<Modification*> vm1 = {phosphorylation}, vm2;
        auto aPeptideWithSetModifications = p->Digest(digestionParams, vm1, vm2).front();

        auto theseTheoreticalFragments = aPeptideWithSetModifications->Fragment(DissociationType::HCD,
                                                                                FragmentationTerminus::Both);
        //Note that dissociation type here intentionally mismatched to dissociation type in modification constructor

        //evaluate N-terminal masses
#ifdef ORIG
        auto diagnosticIons = theseTheoreticalFragments->Where([&] (std::any f)
        {
            return f->ProductType == ProductType::D;
        }).ToList();
#endif
        std::vector<Product *>diagnosticIons;
        for ( auto f: theseTheoreticalFragments ) {
            if (f->productType == ProductType::D ) {
                diagnosticIons.push_back(f);
            }
        }
        std::string s = "D99;97.976895574-0";
        Assert::AreEqual( s, diagnosticIons.front()->ToString());
        
        delete digestionParams;
        delete phosphorylation;
        delete p;
    }

    void TestFragments::Test_Fragment_MolecularIon_NeutralLoss()
    {
        Protein *p = new Protein("PTE", "accession");
        ModificationMotif *motif;
        ModificationMotif::TryGetMotif("P", &motif);
        Modification *phosphorylation = new Modification("phospho", "", "CommonBiological", "", motif, "Anywhere.",
                                                         ChemicalFormula::ParseFormula("H1O3P1"), std::nullopt,
                                                         std::unordered_map<std::string, std::vector<std::string>>(),
                                                         std::unordered_map<std::string, std::vector<std::string>>(),
                                                         std::vector<std::string>(),
                                                         std::unordered_map<DissociationType, std::vector<double>>
        {
            {
                MassSpectrometry::DissociationType::HCD, {0, ChemicalFormula::ParseFormula("H3O4P1")->getMonoisotopicMass()}
            }
        },
                                                         std::unordered_map<DissociationType, std::vector<double>>
        {
            {
                MassSpectrometry::DissociationType::HCD, {ChemicalFormula::ParseFormula("H3O4P1")->getMonoisotopicMass()}
            }
        },
        "");
        
        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 2, INT_MAX, 1024,
                                                               InitiatorMethionineBehavior::Variable, 2,
                                                               CleavageSpecificity::Full, FragmentationTerminus::Both);
        std::vector<Modification*> vm1 = {phosphorylation}, vm2;
        auto aPeptideWithSetModifications = p->Digest(digestionParams, vm1, vm2).front();

        auto theseTheoreticalFragments = aPeptideWithSetModifications->Fragment(DissociationType::HCD,
                                                                                FragmentationTerminus::Both);
        //Note that dissociation type here intentionally mismatched to dissociation type in modification constructor

        //evaluate N-terminal masses
#ifdef ORIG
        auto molecularIons = theseTheoreticalFragments->Where([&] (std::any f)
        {
            return f->ProductType == ProductType::M;
        }).ToList();
#endif
        std::vector<Product *> molecularIons;
        for ( auto f: theseTheoreticalFragments ) {
            if (f->productType == ProductType::M ) {
                molecularIons.push_back(f);
            }
        }
        std::string s = "M0;327.14303541-97.976895573";
        Assert::AreEqual( s , molecularIons.front()->ToString());
    
        delete digestionParams;
        delete phosphorylation;
        delete p;
    }

    void TestFragments::Test_Fragment_DiagnosticIons_unmatchedDissociationType()
    {
        Protein *p = new Protein("PET", "accession");
        ModificationMotif *motif;
        ModificationMotif::TryGetMotif("P", &motif);
        Modification *phosphorylation = new Modification("phospho", "", "CommonBiological", "", motif, "Anywhere.",
                                                         ChemicalFormula::ParseFormula("H1O3P1"),
                                                         std::nullopt, std::unordered_map<std::string, std::vector<std::string>>(),
                                                         std::unordered_map<std::string, std::vector<std::string>>(),
                                                         std::vector<std::string>(),
                                                         std::unordered_map<DissociationType, std::vector<double>>
        {
            {
                MassSpectrometry::DissociationType::CID, {0, ChemicalFormula::ParseFormula("H3O4P1")->getMonoisotopicMass()}
            }
        },
                                                         std::unordered_map<DissociationType, std::vector<double>>
        {
            {
                MassSpectrometry::DissociationType::CID, {ChemicalFormula::ParseFormula("H3O4P1")->getMonoisotopicMass()}
            }
        },
                                                         "");
        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 2, INT_MAX, 1024, InitiatorMethionineBehavior::Variable, 2,
                                                               CleavageSpecificity::Full, FragmentationTerminus::Both);
        std::vector<Modification*> vm1 = {phosphorylation}, vm2;
        auto aPeptideWithSetModifications = p->Digest(digestionParams, vm1, vm2).front();

        auto theseTheoreticalFragments = aPeptideWithSetModifications->Fragment(DissociationType::HCD, FragmentationTerminus::Both);
        //Note that dissociation type here intentionally mismatched to dissociation type in modification constructor

        //evaluate N-terminal masses
#ifdef ORIG
        auto diagnosticIons = theseTheoreticalFragments->Where([&] (std::any f)
        {
            return f->ProductType == ProductType::D;
        }).ToList();
#endif
        std::vector<Product *> diagnosticIons;
        for ( auto f: theseTheoreticalFragments ) {
            if ( f->productType == ProductType::D ) {
                diagnosticIons.push_back(f);
            }
        }
        Assert::AreEqual(0, (int)diagnosticIons.size());

        delete digestionParams;
        delete phosphorylation;
        delete p;
    }

    void TestFragments::Test_Fragment_MolecularIon_NeutralLoss_unmatchedDissociationType()
    {
        Protein *p = new Protein("PTE", "accession");
        ModificationMotif *motif;
        ModificationMotif::TryGetMotif("P", &motif);
        Modification *phosphorylation = new Modification("phospho", "", "CommonBiological", "", motif, "Anywhere.", ChemicalFormula::ParseFormula("H1O3P1"),
                                                         std::nullopt, std::unordered_map<std::string, std::vector<std::string>>(),
                                                         std::unordered_map<std::string, std::vector<std::string>>(),
                                                         std::vector<std::string>(),
                                                         std::unordered_map<DissociationType, std::vector<double>>
        {
            {
                MassSpectrometry::DissociationType::CID, {0, ChemicalFormula::ParseFormula("H3O4P1")->getMonoisotopicMass()}
            }
        },
                                                         std::unordered_map<DissociationType, std::vector<double>>
        {
            {
                MassSpectrometry::DissociationType::CID, {ChemicalFormula::ParseFormula("H3O4P1")->getMonoisotopicMass()}
            }
        },
                                                         "");
        
        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 2, INT_MAX, 1024, InitiatorMethionineBehavior::Variable, 2,
                                                               CleavageSpecificity::Full, FragmentationTerminus::Both);
        std::vector<Modification*> vm1 = {phosphorylation}, vm2;
        auto aPeptideWithSetModifications = p->Digest(digestionParams, vm1, vm2).front();

        auto theseTheoreticalFragments = aPeptideWithSetModifications->Fragment(DissociationType::HCD, FragmentationTerminus::Both);
        //Note that dissociation type here intentionally mismatched to dissociation type in modification constructor

        //evaluate N-terminal masses
#ifdef ORIG
        auto molecularIons = theseTheoreticalFragments->Where([&] (std::any f) {
            return f->ProductType == ProductType::M;
        }).ToList();
#endif
        std::vector<Product *> molecularIons;
        for ( auto f: theseTheoreticalFragments ) {
            if (f->productType == ProductType::M ) {
                molecularIons.push_back(f);
            }
        }
        
        Assert::AreEqual(0, (int)molecularIons.size());

        delete digestionParams;
        delete phosphorylation;
        delete p;
    }

#ifdef LATER
    void TestFragments::Test_NeutralMassShiftFromProductType()
    {
        //C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to the C# 'typeof' operator:
        for (auto p : Enum::GetValues(typeof(ProductType)))
        {
            double mass = Chemistry::ClassExtensions::RoundedDouble(std::make_optional(DissociationTypeCollection::ProductTypeSpecificFragmentNeutralMass(0, p))).value();
            switch (p)
            {
                case ProductType::a:
                    Assert::AreEqual(Chemistry::ClassExtensions::RoundedDouble(std::make_optional(ChemicalFormula::ParseFormula("C-1O-1")->getMonoisotopicMass())).value(), mass);
                    break;

                case ProductType::aDegree:
                    Assert::AreEqual(Chemistry::ClassExtensions::RoundedDouble(std::make_optional(ChemicalFormula::ParseFormula("C-1O-2H-2")->getMonoisotopicMass())).value(), mass);
                    break;

                case ProductType::aStar:
                    Assert::AreEqual(Chemistry::ClassExtensions::RoundedDouble(std::make_optional(ChemicalFormula::ParseFormula("C-1O-1N-1H-3")->getMonoisotopicMass())).value(), mass);
                    break;

                case ProductType::b:
                    Assert::AreEqual(0, mass);
                    break;

                case ProductType::bDegree:
                    Assert::AreEqual(Chemistry::ClassExtensions::RoundedDouble(std::make_optional(ChemicalFormula::ParseFormula("H-2O-1")->getMonoisotopicMass())).value(), mass);
                    break;

                case ProductType::bStar:
                    Assert::AreEqual(Chemistry::ClassExtensions::RoundedDouble(std::make_optional(ChemicalFormula::ParseFormula("N-1H-3")->getMonoisotopicMass())).value(), mass);
                    break;

                case ProductType::c:
                    Assert::AreEqual(Chemistry::ClassExtensions::RoundedDouble(std::make_optional(ChemicalFormula::ParseFormula("N1H3")->getMonoisotopicMass())).value(), mass);
                    break;

                case ProductType::D:
                    Assert::AreEqual(0, mass);
                    break;

                case ProductType::M:
                    Assert::AreEqual(0, mass);
                    break;

                case ProductType::x:
                    Assert::AreEqual(Chemistry::ClassExtensions::RoundedDouble(std::make_optional(ChemicalFormula::ParseFormula("C1O2")->getMonoisotopicMass())).value(), mass);
                    break;

                case ProductType::y:
                    Assert::AreEqual(Chemistry::ClassExtensions::RoundedDouble(std::make_optional(ChemicalFormula::ParseFormula("H2O1")->getMonoisotopicMass())).value(), mass);
                    break;

                case ProductType::yDegree:
                    Assert::AreEqual(0, mass);
                    break;

                case ProductType::yStar:
                    Assert::AreEqual(Chemistry::ClassExtensions::RoundedDouble(std::make_optional(ChemicalFormula::ParseFormula("O1H-1N-1")->getMonoisotopicMass())).value(), mass);
                    break;

                case ProductType::zPlusOne:
                    Assert::AreEqual(Chemistry::ClassExtensions::RoundedDouble(std::make_optional(ChemicalFormula::ParseFormula("O1H1N-1")->getMonoisotopicMass())).value(), mass);
                    break;

                case ProductType::zDot:
                    Assert::AreEqual(Chemistry::ClassExtensions::RoundedDouble(std::make_optional(ChemicalFormula::ParseFormula("O1N-1H-1")->getMonoisotopicMass() + Constants::ProtonMass + Constants::ElectronMass)).value(), mass);
                    break;
            }
        }
    }

    void TestFragments::Test_NeutralMassShiftFromProductType_Exceptions()
    {
        ProductType undefinedProduct = static_cast<ProductType>(99);

        Assert::Throws<MzLibException*>([&] ()
        {
            DissociationTypeCollection::ProductTypeSpecificFragmentNeutralMass(0, undefinedProduct);
        }, "Unknown product type!");
    }

    void TestFragments::Test_CustomDissociationType()
    {
        DissociationTypeCollection::ProductsFromDissociationType[DissociationType::Custom].push_back(ProductType::b);
        DissociationTypeCollection::ProductsFromDissociationType[DissociationType::Custom].push_back(ProductType::y);

        Assert::IsTrue(std::find(DissociationTypeCollection::ProductsFromDissociationType[DissociationType::Custom].begin(),
                                 DissociationTypeCollection::ProductsFromDissociationType[DissociationType::Custom].end(), ProductType::b) !=
                       DissociationTypeCollection::ProductsFromDissociationType[DissociationType::Custom].end());

        auto productCollection = TerminusSpecificProductTypes::ProductIonTypesFromSpecifiedTerminus[FragmentationTerminus::N].Intersect(DissociationTypeCollection::ProductsFromDissociationType[DissociationType::Custom]);
        Assert::IsTrue(productCollection->Contains(ProductType::b));

        productCollection = TerminusSpecificProductTypes::ProductIonTypesFromSpecifiedTerminus[FragmentationTerminus::C].Intersect(DissociationTypeCollection::ProductsFromDissociationType[DissociationType::Custom]);
        Assert::IsTrue(productCollection->Contains(ProductType::y));
    }

    void TestFragments::Test_TerminusSpecificProductTypes()
    {
        Assert::AreEqual(std::vector<std::vector<ProductType>>(FragmentationTerminus::Both).Intersect(DissociationTypeCollection::ProductsFromDissociationType[DissociationType::HCD]));
        Assert::AreEqual(std::vector<std::vector<ProductType>>(FragmentationTerminus::N).Intersect(DissociationTypeCollection::ProductsFromDissociationType[DissociationType::HCD]));
        Assert::AreEqual(std::vector<std::vector<ProductType>>(FragmentationTerminus::C).Intersect(DissociationTypeCollection::ProductsFromDissociationType[DissociationType::HCD]));
        Assert::AreEqual(std::vector<std::vector<ProductType>>(FragmentationTerminus::None).Intersect(DissociationTypeCollection::ProductsFromDissociationType[DissociationType::HCD]));

        Assert::AreEqual(std::vector<std::vector<ProductType>>(FragmentationTerminus::Both).Intersect(DissociationTypeCollection::ProductsFromDissociationType[DissociationType::ETD]));
        Assert::AreEqual(std::vector<std::vector<ProductType>>(FragmentationTerminus::N).Intersect(DissociationTypeCollection::ProductsFromDissociationType[DissociationType::ETD]));
        Assert::AreEqual(std::vector<std::vector<ProductType>>(FragmentationTerminus::C).Intersect(DissociationTypeCollection::ProductsFromDissociationType[DissociationType::ETD]));
        Assert::AreEqual(std::vector<std::vector<ProductType>>(FragmentationTerminus::None).Intersect(DissociationTypeCollection::ProductsFromDissociationType[DissociationType::ETD]));

        Assert::AreEqual(std::vector<std::vector<ProductType>>(FragmentationTerminus::Both).Intersect(DissociationTypeCollection::ProductsFromDissociationType[DissociationType::CID]));
        Assert::AreEqual(std::vector<std::vector<ProductType>>(FragmentationTerminus::N).Intersect(DissociationTypeCollection::ProductsFromDissociationType[DissociationType::CID]));
        Assert::AreEqual(std::vector<std::vector<ProductType>>(FragmentationTerminus::C).Intersect(DissociationTypeCollection::ProductsFromDissociationType[DissociationType::CID]));
        Assert::AreEqual(std::vector<std::vector<ProductType>>(FragmentationTerminus::None).Intersect(DissociationTypeCollection::ProductsFromDissociationType[DissociationType::CID]));
    }

    void TestFragments::Test_TerminusSpecificProductTypesFromPeptideWithSetMods()
    {
        Protein *protein = new Protein("PEPTIDE", "accession");
        DigestionParams tempVar();
        PeptideWithSetModifications *p = new PeptideWithSetModifications(protein, &tempVar, 1, 7, CleavageSpecificity::Full, "", 0, std::unordered_map<int, Modification*>(), 0);

        Assert::AreEqual({ProductType::b, ProductType::y}, p->Fragment(DissociationType::HCD, FragmentationTerminus::Both).Select([&] (std::any b)
        {
            b::ProductType;
        }).Distinct().ToList());
        Assert::AreEqual({ProductType::b}, p->Fragment(DissociationType::HCD, FragmentationTerminus::N).Select([&] (std::any b)
        {
            b::ProductType;
        }).Distinct().ToList());
        Assert::AreEqual({ProductType::y}, p->Fragment(DissociationType::HCD, FragmentationTerminus::C).Select([&] (std::any b)
        {
            b::ProductType;
        }).Distinct().ToList());
        Assert::AreEqual({ }, p->Fragment(DissociationType::HCD, FragmentationTerminus::None).Select([&] (std::any b)
        {
            b::ProductType;
        }).Distinct().ToList());

        Assert::AreEqual({ProductType::c, ProductType::y, ProductType::zDot}, p->Fragment(DissociationType::ETD, FragmentationTerminus::Both).Select([&] (std::any b)
        {
            b::ProductType;
        }).Distinct().ToList());
        Assert::AreEqual({ProductType::c}, p->Fragment(DissociationType::ETD, FragmentationTerminus::N).Select([&] (std::any b)
        {
            b::ProductType;
        }).Distinct().ToList());
        Assert::AreEqual({ProductType::y, ProductType::zDot}, p->Fragment(DissociationType::ETD, FragmentationTerminus::C).Select([&] (std::any b)
        {
            b::ProductType;
        }).Distinct().ToList());
        Assert::AreEqual({ }, p->Fragment(DissociationType::ETD, FragmentationTerminus::None).Select([&] (std::any b)
        {
            b::ProductType;
        }).Distinct().ToList());

        Assert::AreEqual({ProductType::b, ProductType::y}, p->Fragment(DissociationType::CID, FragmentationTerminus::Both).Select([&] (std::any b)
        {
            b::ProductType;
        }).Distinct().ToList());
        Assert::AreEqual({ProductType::b}, p->Fragment(DissociationType::CID, FragmentationTerminus::N).Select([&] (std::any b)
        {
            b::ProductType;
        }).Distinct().ToList());
        Assert::AreEqual({ProductType::y}, p->Fragment(DissociationType::CID, FragmentationTerminus::C).Select([&] (std::any b)
        {
            b::ProductType;
        }).Distinct().ToList());
        Assert::AreEqual({ }, p->Fragment(DissociationType::CID, FragmentationTerminus::None).Select([&] (std::any b)
        {
            b::ProductType;
        }).Distinct().ToList());

        delete p;
        delete protein;
    }
#endif
    
    void TestFragments::Test_MatchedFragmentIonToString()
    {
        auto  tempVar = new NeutralTerminusFragment (FragmentationTerminus::N, 1, 1, 1);
        Product *P = new Product(ProductType::b, tempVar, 0);
        MatchedFragmentIon *m = new MatchedFragmentIon(P, 1, 1, 1);

        std::string s = "b1+1\t;1";
        Assert::AreEqual( s, m->ToString());

        delete m;
        delete P;
    }

    void TestFragments::Test_CID_Fragmentation_No_Unmodified_B1_ions()
    {
        //FOR CID B1 ions should always be missing whether or not there is a modification on first amino acid or not.

        Protein *protein = new Protein("PEPTIDE", "accession");
        DigestionParams *tempVar  = new DigestionParams("trypsin");
        std::unordered_map<int, Modification*> vmap;
        PeptideWithSetModifications *p = new PeptideWithSetModifications(protein, tempVar, 1, 7, CleavageSpecificity::Full, "", 0,
                                                                         vmap, 0);

        auto f = p->Fragment(DissociationType::CID, FragmentationTerminus::Both);
        Assert::AreEqual(11, (int)f.size());

        ModificationMotif *motif;
        ModificationMotif::TryGetMotif("P", &motif);
        Modification *m = new Modification("myId", "", "myModType", "", motif, "Anywhere.", nullptr, std::make_optional(10),
                                           std::unordered_map<std::string, std::vector<std::string>>(),
                                           std::unordered_map<std::string, std::vector<std::string>>(),
                                           std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(),
                                           std::unordered_map<DissociationType, std::vector<double>>(), "");
        std::vector<Modification*> modList = {m};
        std::unordered_map<int, std::vector<Modification*>> i =
        {
            {1, modList}
        };

        protein = new Protein("PEPTIDE", "accession", "", std::vector<std::tuple<std::string, std::string>>(), i,
                              std::vector<ProteolysisProduct *>(), "", "", false, false, std::vector<DatabaseReference *>(),
                              std::vector<SequenceVariation *>(), std::vector<SequenceVariation *>(), "",
                              std::vector<DisulfideBond *>(), std::vector<SpliceSite *>(), "");
        DigestionParams *tempVar2 = new DigestionParams("trypsin");
        std::vector<Modification*> vm1, vm2;
        std::vector<PeptideWithSetModifications*> pwsmList = protein->Digest(tempVar2, vm1, vm2 );

#ifdef ORIG
        PeptideWithSetModifications *modifiedPwsm = pwsmList.Where([&] (std::any z) {
            return z::AllModsOneIsNterminus->Count == 1;
        }).First();
#endif
        PeptideWithSetModifications *modifiedPwsm;
        for ( auto z : pwsmList ) {
            if (z->getAllModsOneIsNterminus().size() == 1 ) {
                modifiedPwsm = z;
                break;
            }
        }
#ifdef ORIG
        PeptideWithSetModifications *unmodifiedPwsm = pwsmList.Where([&] (std::any z)  {
            return z::AllModsOneIsNterminus->Count == 0;
        }).First();
#endif
        PeptideWithSetModifications *unmodifiedPwsm;
        for ( auto z : pwsmList ) {
            if ( z->getAllModsOneIsNterminus().size() == 0 ) {
                unmodifiedPwsm = z;
                break;
            }
        }

        std::vector<Product*> modifiedPwsmFragments = modifiedPwsm->Fragment(DissociationType::CID, FragmentationTerminus::Both);
        std::vector<Product*> unmodifiedPwsmFragments = unmodifiedPwsm->Fragment(DissociationType::CID, FragmentationTerminus::Both);
        Assert::AreEqual(11, (int)modifiedPwsmFragments.size());
        Assert::AreEqual(11, (int)unmodifiedPwsmFragments.size());

        i = std::unordered_map<int, std::vector<Modification*>>
        {
            {2, modList}
        };

        protein = new Protein("PPPTIDE", "accession", "", std::vector<std::tuple<std::string, std::string>>(), i,
                              std::vector<ProteolysisProduct *>(), "", "", false, false, std::vector<DatabaseReference*>(),
                              std::vector<SequenceVariation *>(), std::vector<SequenceVariation *>(), "",
                              std::vector<DisulfideBond *>(), std::vector<SpliceSite *>(), "");
        DigestionParams *tempVar3 = new DigestionParams("trypsin");
        std::vector<Modification*> vm3, vm4;
        pwsmList = protein->Digest(tempVar3, vm3, vm4);

#ifdef ORIG
        modifiedPwsm = pwsmList.Where([&] (std::any z)  {
            return z::AllModsOneIsNterminus->Count == 1;
        }).First();
#endif
        for ( auto z : pwsmList ) {
            if ( z->getAllModsOneIsNterminus().size() == 1 ) {
                modifiedPwsm = z;
                break;
            }
        }
#ifdef ORIG
        unmodifiedPwsm = pwsmList.Where([&] (std::any z) {
            return z::AllModsOneIsNterminus->Count == 0;
        }).First();
#endif
        for ( auto z : pwsmList ) {
            if ( z->getAllModsOneIsNterminus().size() == 0 ) {
                unmodifiedPwsm = z;
                break;
            }
        }

        modifiedPwsmFragments = modifiedPwsm->Fragment(DissociationType::CID, FragmentationTerminus::Both);
        unmodifiedPwsmFragments = unmodifiedPwsm->Fragment(DissociationType::CID, FragmentationTerminus::Both);
        Assert::AreEqual(11, (int)modifiedPwsmFragments.size());
        Assert::AreEqual(11, (int)unmodifiedPwsmFragments.size());

        delete m;
        delete p;
        delete protein;
        delete tempVar;
        delete tempVar2;
        delete tempVar3;
    }

#ifdef LATER
    void TestFragments::Test_ETD_ECD_EThcD_Fragmentation_No_FragmentsAtProline(DissociationType dissociationType, int fragmentCount)
    {
        Protein *protein = new Protein("PEPTIDE", "accession", "", std::vector<std::tuple<std::string, std::string>>(), std::unordered_map<int, std::vector<Modification>>(), std::vector<ProteolysisProduct>(), "", "", false, false, std::vector<DatabaseReference>(), std::vector<SequenceVariation>(), std::vector<SequenceVariation>(), "", std::vector<DisulfideBond>(), std::vector<SpliceSite>(), "");
        DigestionParams tempVar();
        std::vector<PeptideWithSetModifications*> pwsmList = protein->Digest(&tempVar, std::vector<Modification*>(), std::vector<Modification*>());
        DigestionParams tempVar2();
        std::vector<PeptideWithSetModifications*> digestionProducts = protein->Digest(&tempVar2, std::vector<Modification*>(), std::vector<Modification*>());
        PeptideWithSetModifications *myPeptide = digestionProducts.front();
        std::vector<Product*> myFragments = myPeptide->Fragment(dissociationType, FragmentationTerminus::Both);
        Assert::AreEqual(fragmentCount, myFragments.size()());

        delete protein;
    }

    void TestFragments::CheckProlineFragments()
    {
        PeptideWithSetModifications *p = new PeptideWithSetModifications("MPEPTIDE", std::unordered_map<std::string, Modification*>());
        auto fragments = p->Fragment(DissociationType::ETD, FragmentationTerminus::Both);

        auto z = fragments.Where([&] (std::any f)
        {
        delete p;
            return f->ProductType == ProductType::zDot;
        }).ToList();

        auto ionNums = z.Select([&] (std::any f)
        {
            f::TerminusFragment::FragmentNumber;
        })->ToArray();
        auto expected = std::vector<int> {1, 2, 3, 4, 6, 8};

        Assert::IsTrue(expected.SequenceEqual(ionNums));

        delete p;
    }

    void TestFragments::CheckProlineFragments2()
    {
        PeptideWithSetModifications *p = new PeptideWithSetModifications("MTETTIDE", std::unordered_map<std::string, Modification*>());
        auto fragments = p->Fragment(DissociationType::ETD, FragmentationTerminus::Both);

        auto z = fragments.Where([&] (std::any f)
        {
        delete p;
            return f->ProductType == ProductType::zDot;
        }).ToList();

        auto ionNums = z.Select([&] (std::any f)
        {
            f::TerminusFragment::FragmentNumber;
        })->ToArray();
        auto expected = std::vector<int> {1, 2, 3, 4, 5, 6, 7, 8};

        Assert::IsTrue(expected.SequenceEqual(ionNums));

        delete p;
    }

    void TestFragments::CheckProlineFragments3()
    {
        PeptideWithSetModifications *p = new PeptideWithSetModifications("METPIPEEEE", std::unordered_map<std::string, Modification*>());
        auto fragments = p->Fragment(DissociationType::ETD, FragmentationTerminus::Both);

        auto z = fragments.Where([&] (std::any f)
        {
        delete p;
            return f->ProductType == ProductType::zDot;
        }).ToList();

        auto ionNums = z.Select([&] (std::any f)
        {
            f::TerminusFragment::FragmentNumber;
        })->ToArray();
        auto expected = std::vector<int> {1, 2, 3, 4, 6, 8, 9, 10};

        Assert::IsTrue(expected.SequenceEqual(ionNums));

        delete p;
    }

    void TestFragments::CheckProlineFragments4()
    {
        ModificationMotif motif;
        ModificationMotif::TryGetMotif("P", motif);
        Modification *m = new Modification("TEST", "", "OK", "", motif, "Anywhere.", nullptr, std::make_optional(20));
        PeptideWithSetModifications *p = new PeptideWithSetModifications("METP[OK:TEST]IPEEEE", std::unordered_map<std::string, Modification*>
        {
            {"TEST", m}
        });
        auto fragments = p->Fragment(DissociationType::ETD, FragmentationTerminus::Both);

        auto z = fragments.Where([&] (std::any f)
        {
            return f->ProductType == ProductType::zDot;
        }).ToList();

        auto ionNums = z.Select([&] (std::any f)
        {
            f::TerminusFragment::FragmentNumber;
        })->ToArray();
        auto expected = std::vector<int> {1, 2, 3, 4, 6, 8, 9, 10};

        Assert::IsTrue(expected.SequenceEqual(ionNums));

        delete p;
//C# TO C++ CONVERTER TODO TASK: A 'delete m' statement was not added since m was passed to a method or constructor. Handle memory management manually.
    }

    void TestFragments::TestFragmentAnnotations()
    {
        NeutralTerminusFragment tempVar(FragmentationTerminus::N, 505.505, 2, 3);
        Product *p = new Product(ProductType::b, &tempVar, 30.3);
        MatchedFragmentIon *f = new MatchedFragmentIon(p, 400.0, 1000.0, 3);

        Assert::IsTrue(p->getAnnotation() == "b2-30.30");
        Assert::IsTrue(f->getAnnotation() == "(b2-30.30)+3");

        NeutralTerminusFragment tempVar2(FragmentationTerminus::N, 505.505, 2, 3);
        p = new Product(ProductType::b, &tempVar2, 0);
        f = new MatchedFragmentIon(p, 400.0, 1000.0, 3);

        Assert::IsTrue(p->getAnnotation() == "b2");
        Assert::IsTrue(f->getAnnotation() == "b2+3");

        delete f;
//C# TO C++ CONVERTER TODO TASK: A 'delete p' statement was not added since p was passed to a method or constructor. Handle memory management manually.
    }

    void TestFragments::TestFragmentErrors()
    {
        NeutralTerminusFragment tempVar(FragmentationTerminus::N, 505.505, 2, 3);
        Product *p = new Product(ProductType::b, &tempVar, 30.3);
        MatchedFragmentIon *f = new MatchedFragmentIon(p, 159.5, 1000.0, 3);

        double experMass = Chemistry::ClassExtensions::ToMass(f->Mz, f->Charge);
        double theorMass = p->NeutralMass;

        Assert::AreEqual(0.2732, std::round(experMass - theorMass * std::pow(10, 4)) / std::pow(10, 4));
        Assert::AreEqual(574.85, std::round(f->getMassErrorPpm() * std::pow(10, 2)) / std::pow(10, 2));
        Assert::AreEqual(0.2732, std::round(f->getMassErrorDa() * std::pow(10, 4)) / std::pow(10, 4));

        delete f;
//C# TO C++ CONVERTER TODO TASK: A 'delete p' statement was not added since p was passed to a method or constructor. Handle memory management manually.
    }

    void TestFragments::TestFragmentEquality()
    {
        NeutralTerminusFragment *n1 = new NeutralTerminusFragment(FragmentationTerminus::N, 505.505, 2, 3);
        Product *p1 = new Product(ProductType::b, n1, 30.3);
        MatchedFragmentIon *f1 = new MatchedFragmentIon(p1, 400.0, 1000.0, 3);

        NeutralTerminusFragment *n2 = new NeutralTerminusFragment(FragmentationTerminus::N, 505.505, 2, 3);
        Product *p2 = new Product(ProductType::b, n2, 30.3);
        MatchedFragmentIon *f2 = new MatchedFragmentIon(p2, 400.0, 1000.0, 3);

        Assert::AreEqual(n1, n2);
        Assert::AreEqual(p1, p2);
        Assert::AreEqual(f1, f2);

//C# TO C++ CONVERTER TODO TASK: A 'delete f2' statement was not added since f2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete p2' statement was not added since p2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete n2' statement was not added since n2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete f1' statement was not added since f1 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete p1' statement was not added since p1 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete n1' statement was not added since n1 was passed to a method or constructor. Handle memory management manually.
    }

    void TestFragments::TestThatDiagnosticIonsDontDuplicate()
    {
        ModificationMotif motif;
        ModificationMotif::TryGetMotif("X", motif);
        Modification *modWithDiagnosticIons = new Modification("Test", "", "TestType", "", motif, "Anywhere.", nullptr, std::make_optional(1), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>
        {
            {
                DissociationType::HCD, {4.0}
            }
        },
        "");

        PeptideWithSetModifications *p = new PeptideWithSetModifications("P[TestType:Test]E[TestType:Test]P[TestType:Test]TIDE", std::unordered_map<std::string, Modification*>
        {
            {"Test", modWithDiagnosticIons}
        });

        auto fragments = p->Fragment(DissociationType::HCD, FragmentationTerminus::Both).ToList();

        auto diagnosticIons = fragments.Where([&] (std::any f)
        {
            return f->ProductType == ProductType::D;
        }).ToList();

        // if there are 3 diagnostic ions (one for each mod on the peptide),
        // diagnostic ions are being incorrectly duplicated!
        Assert::IsTrue(diagnosticIons.size() == 1);

        delete p;
//C# TO C++ CONVERTER TODO TASK: A 'delete modWithDiagnosticIons' statement was not added since modWithDiagnosticIons was passed to a method or constructor. Handle memory management manually.
    }
#endif
}
