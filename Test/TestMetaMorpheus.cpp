#include "TestMetaMorpheus.h"
#include "../Proteomics/Protein/Protein.h"
#include "../Proteomics/Modifications/Modification.h"
#include "../Proteomics/Modifications/ModificationMotif.h"
#include "../Chemistry/ChemicalFormula.h"
#include "../MassSpectrometry/Enums/DissociationType.h"

#include "../UsefulProteomicsDatabases/PeriodicTableLoader.h"
#include "MzLibAssert.h"
#include <limits>

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

    std::cout << ++i << ". TestCompactPeptideMasses_UnmodifiedPeptide" << std::endl;        
    Test::TestCompactPeptide::TestCompactPeptideMasses_UnmodifiedPeptide();

    std::cout << ++i << ". TestCompactPeptideMasses_nTerminalModifiedPeptide" << std::endl;        
    Test::TestCompactPeptide::TestCompactPeptideMasses_nTerminalModifiedPeptide();

    std::cout << ++i << ". TestCompactPeptideMasses_cTerminalModifiedPeptide" << std::endl;        
    Test::TestCompactPeptide::TestCompactPeptideMasses_cTerminalModifiedPeptide();

    std::cout << ++i << ". TestCompactPeptideMasses_internallyModifiedPeptide" << std::endl;
    Test::TestCompactPeptide::TestCompactPeptideMasses_internallyModifiedPeptide();

    std::cout << ++i << ". TestCompactPeptideMasses_nTerminalModifiedPeptide_NeutralLoss" << std::endl;        
    Test::TestCompactPeptide::TestCompactPeptideMasses_nTerminalModifiedPeptide_NeutralLoss();

    std::cout << ++i << ". TestCompactPeptideMasses_cTerminalModifiedPeptide_NeutralLoss" << std::endl;        
    Test::TestCompactPeptide::TestCompactPeptideMasses_cTerminalModifiedPeptide_NeutralLoss();

    std::cout << ++i << ". TestCompactPeptideMasses_internallyModifiedPeptide_NeutralLoss" << std::endl;        
    Test::TestCompactPeptide::TestCompactPeptideMasses_internallyModifiedPeptide_NeutralLoss();

    std::cout << ++i << ". TestCompactPeptideMasses_nTerminalModifiedPeptide_NeutralLoss_DissociationTypes_AnyActivationType_and_HCD" << std::endl;    
    Test::TestCompactPeptide::TestCompactPeptideMasses_nTerminalModifiedPeptide_NeutralLoss_DissociationTypes_AnyActivationType_and_HCD();

    std::cout << ++i << ". TestCompactPeptideMasses_nTerminalModifiedPeptide_NeutralLoss_DissociationTypes_CID_and_HCD" << std::endl;    
    Test::TestCompactPeptide::TestCompactPeptideMasses_nTerminalModifiedPeptide_NeutralLoss_DissociationTypes_CID_and_HCD();
    return 0;
}


namespace Test
{

    void TestCompactPeptide::TestCompactPeptideMasses_UnmodifiedPeptide()
    {
        Protein *p = new Protein("PET", "accession");
        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 2, std::numeric_limits<int>::max(), 1024,
                                                               InitiatorMethionineBehavior::Variable,
                                                               2, CleavageSpecificity::Full, FragmentationTerminus::Both);
        std::vector<Modification*> v, v2;
        auto aPeptideWithSetModifications = p->Digest(digestionParams, v, v2).front();

        auto aCompactPeptide = new CompactPeptide(aPeptideWithSetModifications, FragmentationTerminus::Both);

#ifdef ORIG
        //evaluate N-terminal masses
        auto nTerminalMasses = aCompactPeptide->TerminalMasses.Where([&] (std::any v)
        {
            delete aCompactPeptide;
            delete p;
            return v->Terminus == FragmentationTerminus::N;
        });
#endif
        std::vector<NeutralTerminusFragment*> nTerminalMasses;
        for ( auto v: aCompactPeptide->getTerminalMasses() ) {
            if ( v->Terminus == FragmentationTerminus::N ) {
                nTerminalMasses.push_back(v);
            }
        }

        std::unordered_set<int> expectedNTerminalMasses = {97, 226};
#ifdef ORIG
        Assert::That(expectedNTerminalMasses.SetEquals(nTerminalMasses->Select([&] (std::any v)
        {
            static_cast<int>(std::round(v::NeutralMass * std::pow(10, 1))) / std::pow(10, 1);
        })));
#endif
        std::unordered_set<int> SubsetnTerminalMasses;
        for ( auto v: nTerminalMasses ) {
            SubsetnTerminalMasses.insert(static_cast<int>(std::round(v->NeutralMass * std::pow(10, 1))) / std::pow(10, 1));
        }
        Assert::IsTrue ( expectedNTerminalMasses == SubsetnTerminalMasses);
        
        //evaluate C-terminal masses
#ifdef ORIG
        auto cTerminalMasses = aCompactPeptide->TerminalMasses.Where([&] (std::any v)
        {
            delete aCompactPeptide;
            delete p;
            return v->Terminus == FragmentationTerminus::C;
        });
#endif
        std::vector<NeutralTerminusFragment*> cTerminalMasses;
        for ( auto v: aCompactPeptide->getTerminalMasses() ) {
            if ( v->Terminus == FragmentationTerminus::C ) {
                cTerminalMasses.push_back(v);
            }
        }
        
        std::unordered_set<int> expectedCTerminalMasses = {101, 230, 327};
#ifdef ORIG
        Assert::That(expectedCTerminalMasses.SetEquals(cTerminalMasses->Select([&] (std::any v)
        {
            static_cast<int>(std::round(v::NeutralMass * std::pow(10, 1))) / std::pow(10, 1);
        })));
#endif
        std::unordered_set<int> SubsetcTerminalMasses;
        for ( auto v: cTerminalMasses ) {
            SubsetcTerminalMasses.insert(static_cast<int>(std::round(v->NeutralMass * std::pow(10, 1))) / std::pow(10, 1));
        }
        Assert::IsTrue ( expectedCTerminalMasses == SubsetcTerminalMasses);

        delete aCompactPeptide;
        delete p;
        delete digestionParams;
    }

    void TestCompactPeptide::TestCompactPeptideMasses_nTerminalModifiedPeptide()
    {
        Protein *p = new Protein("PET", "accession");
        ModificationMotif *motif;
        ModificationMotif::TryGetMotif("P", &motif);
        std::unordered_map<std::string, std::vector<std::string>> map1, map2;
        std::unordered_map<DissociationType, std::vector<double>> map3, map4;
        std::vector<std::string> svec;        
        Modification *phosphorylation = new Modification("phospho", "", "CommonBiological", "", motif, "Anywhere.",
                                                         ChemicalFormula::ParseFormula("H1O3P1"), std::nullopt,
                                                         map1, map2, svec, map3, map4, "");


        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 2, std::numeric_limits<int>::max(), 1024,
                                                               InitiatorMethionineBehavior::Variable,
                                                               2, CleavageSpecificity::Full, FragmentationTerminus::Both);

        std::vector<Modification*> mvec;
        std::vector<Modification*> pvec = {phosphorylation};
        auto aPeptideWithSetModifications = p->Digest(digestionParams, pvec, mvec).front();

        auto aCompactPeptide = new CompactPeptide(aPeptideWithSetModifications, FragmentationTerminus::Both);

        //evaluate N-terminal masses
        std::vector<NeutralTerminusFragment*> nTerminalMasses;
        for ( auto v: aCompactPeptide->getTerminalMasses() ) {
            if ( v->Terminus == FragmentationTerminus::N ) {
                nTerminalMasses.push_back(v);
            }
        }

        std::unordered_set<int> expectedNTerminalMasses = {177, 306};
        std::unordered_set<int> SubsetnTerminalMasses;
        for ( auto v: nTerminalMasses ) {
            SubsetnTerminalMasses.insert(static_cast<int>(std::round(v->NeutralMass * std::pow(10, 1))) / std::pow(10, 1));
        }
        Assert::IsTrue ( expectedNTerminalMasses == SubsetnTerminalMasses);

        
        //evaluate C-terminal masses
        std::vector<NeutralTerminusFragment*> cTerminalMasses;
        for ( auto v: aCompactPeptide->getTerminalMasses() ) {
            if ( v->Terminus == FragmentationTerminus::C ) {
                cTerminalMasses.push_back(v);
            }
        }

        std::unordered_set<int> expectedCTerminalMasses = {101, 230, 407};
        std::unordered_set<int> SubsetcTerminalMasses;
        for ( auto v: cTerminalMasses ) {
            SubsetcTerminalMasses.insert(static_cast<int>(std::round(v->NeutralMass * std::pow(10, 1))) / std::pow(10, 1));
        }
        Assert::IsTrue ( expectedCTerminalMasses == SubsetcTerminalMasses);


        delete aCompactPeptide;
        delete p;
        delete digestionParams;
        delete phosphorylation;
    }


    void TestCompactPeptide::TestCompactPeptideMasses_cTerminalModifiedPeptide()
    {
        Protein *p = new Protein("PET", "accession");
        ModificationMotif *motif;
        ModificationMotif::TryGetMotif("T", &motif);
        std::unordered_map<std::string, std::vector<std::string>> map1, map2;
        std::unordered_map<DissociationType, std::vector<double>> map3, map4;
        std::vector<std::string> svec;        

        Modification *phosphorylation = new Modification("phospho", "", "CommonBiological", "", motif, "Anywhere.",
                                                         ChemicalFormula::ParseFormula("H1O3P1"), std::nullopt,
                                                         map1, map2, svec, map3, map4,  "");

        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 2, std::numeric_limits<int>::max(), 1024,
                                                               InitiatorMethionineBehavior::Variable,
                                                               2, CleavageSpecificity::Full, FragmentationTerminus::Both);

        std::vector<Modification*> mvec;
        std::vector<Modification*> pvec = {phosphorylation};
        auto aPeptideWithSetModifications = p->Digest(digestionParams, pvec, mvec).front();

        auto aCompactPeptide = new CompactPeptide(aPeptideWithSetModifications, FragmentationTerminus::Both);

        //evaluate N-terminal masses
        std::vector<NeutralTerminusFragment*> nTerminalMasses;
        for ( auto v: aCompactPeptide->getTerminalMasses() ) {
            if ( v->Terminus == FragmentationTerminus::N ) {
                nTerminalMasses.push_back(v);
            }
        }
        std::unordered_set<int> expectedNTerminalMasses = {97, 226};
        std::unordered_set<int> SubsetnTerminalMasses;
        for ( auto v: nTerminalMasses ) {
            SubsetnTerminalMasses.insert(static_cast<int>(std::round(v->NeutralMass * std::pow(10, 1))) / std::pow(10, 1));
        }
        Assert::IsTrue ( expectedNTerminalMasses == SubsetnTerminalMasses);

        //evaluate C-terminal masses
        std::vector<NeutralTerminusFragment*> cTerminalMasses;
        for ( auto v: aCompactPeptide->getTerminalMasses() ) {
            if ( v->Terminus == FragmentationTerminus::C ) {
                cTerminalMasses.push_back(v);
            }
        }

        std::unordered_set<int> expectedCTerminalMasses = {181, 310, 407};
        std::unordered_set<int> SubsetcTerminalMasses;
        for ( auto v: cTerminalMasses ) {
            SubsetcTerminalMasses.insert(static_cast<int>(std::round(v->NeutralMass * std::pow(10, 1))) / std::pow(10, 1));
        }
        Assert::IsTrue ( expectedCTerminalMasses == SubsetcTerminalMasses);

        delete aCompactPeptide;
        delete digestionParams;
        delete phosphorylation;
        delete p;
    }

    void TestCompactPeptide::TestCompactPeptideMasses_internallyModifiedPeptide()
    {
        Protein *p = new Protein("PET", "accession");
        ModificationMotif *motif;
        ModificationMotif::TryGetMotif("E", &motif);
        std::unordered_map<std::string, std::vector<std::string>> map1, map2;
        std::unordered_map<DissociationType, std::vector<double>> map3, map4;
        std::vector<std::string> svec;        

        Modification *phosphorylation = new Modification("phospho", "", "CommonBiological", "", motif, "Anywhere.",
                                                         ChemicalFormula::ParseFormula("H1O3P1"), std::nullopt,
                                                         map1, map2, svec, map3, map4, "");

        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 2, std::numeric_limits<int>::max(), 1024,
                                                               InitiatorMethionineBehavior::Variable, 2,
                                                               CleavageSpecificity::Full, FragmentationTerminus::Both);

        std::vector<Modification*> mvec;
        std::vector<Modification*> pvec = {phosphorylation};
        auto aPeptideWithSetModifications = p->Digest(digestionParams, pvec, mvec ).front();


        auto aCompactPeptide = new CompactPeptide(aPeptideWithSetModifications, FragmentationTerminus::Both);

        //evaluate N-terminal masses
        std::vector<NeutralTerminusFragment*> nTerminalMasses;
        for ( auto v: aCompactPeptide->getTerminalMasses() ) {
            if ( v->Terminus == FragmentationTerminus::N ) {
                nTerminalMasses.push_back(v);
            }
        }

        std::unordered_set<int> expectedNTerminalMasses = {97, 306};
        std::unordered_set<int> foundnTerminalMasses;
        for ( auto v: nTerminalMasses ) {
            foundnTerminalMasses.insert(static_cast<int>(std::round(v->NeutralMass * std::pow(10, 1))) / std::pow(10, 1));
        }
        Assert::IsTrue ( expectedNTerminalMasses == foundnTerminalMasses);
        
        //evaluate C-terminal masses
        std::vector<NeutralTerminusFragment*> cTerminalMasses;
        for ( auto v: aCompactPeptide->getTerminalMasses() ) {
            if ( v->Terminus == FragmentationTerminus::C ) {
                cTerminalMasses.push_back(v);
            }
        }

        std::unordered_set<int> expectedCTerminalMasses = {101, 310, 407};
        std::unordered_set<int> foundcTerminalMasses;
        for ( auto v: cTerminalMasses ) {
            foundcTerminalMasses.insert(static_cast<int>(std::round(v->NeutralMass * std::pow(10, 1))) / std::pow(10, 1));
        }
        Assert::IsTrue ( expectedCTerminalMasses == foundcTerminalMasses );

        delete aCompactPeptide;
        delete digestionParams;
        delete phosphorylation;
        delete p;
    }

    void TestCompactPeptide::TestCompactPeptideMasses_nTerminalModifiedPeptide_NeutralLoss()
    {
        Protein *p = new Protein("PET", "accession");
        ModificationMotif *motif;
        ModificationMotif::TryGetMotif("P", &motif);
        std::unordered_map<std::string, std::vector<std::string>> map1, map2;
        std::vector<double> dvec = {0, ChemicalFormula::ParseFormula("H3O4P1")->getMonoisotopicMass()};
        std::unordered_map<DissociationType, std::vector<double>> map3;
        map3[MassSpectrometry::DissociationType::HCD] =  dvec;
        std::unordered_map<DissociationType, std::vector<double>> map4;
        std::vector<std::string> svec;        

        Modification *phosphorylation = new Modification("phospho", "", "CommonBiological", "", motif, "Anywhere.",
                                                         ChemicalFormula::ParseFormula("H1O3P1"), std::nullopt,
                                                         map1, map2, svec, map3, map4, "");

        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 2, std::numeric_limits<int>::max(), 1024,
                                                               InitiatorMethionineBehavior::Variable, 2,
                                                               CleavageSpecificity::Full,
                                                               FragmentationTerminus::Both);

        std::vector<Modification*> mvec;
        std::vector<Modification*> pvec = {phosphorylation};
        auto aPeptideWithSetModifications = p->Digest(digestionParams, pvec, mvec).front();

        auto aCompactPeptide = new CompactPeptide(aPeptideWithSetModifications, FragmentationTerminus::Both);

        //evaluate N-terminal masses
        std::vector<NeutralTerminusFragment*> nTerminalMasses;
        for ( auto v: aCompactPeptide->getTerminalMasses() ) {
            if ( v->Terminus == FragmentationTerminus::N ) {
                nTerminalMasses.push_back(v);
            }
        }

        std::unordered_set<int> expectedNTerminalMasses = {177, 306};
        std::unordered_set<int> foundnTerminalMasses;
        for ( auto v: nTerminalMasses ) {
            foundnTerminalMasses.insert(static_cast<int>(std::round(v->NeutralMass * std::pow(10, 1))) / std::pow(10, 1));
        }
        Assert::IsTrue ( expectedNTerminalMasses == foundnTerminalMasses);

        //evaluate C-terminal masses
        std::vector<NeutralTerminusFragment*> cTerminalMasses;
        for ( auto v: aCompactPeptide->getTerminalMasses() ) {
            if ( v->Terminus == FragmentationTerminus::C ) {
                cTerminalMasses.push_back(v);
            }
        }

        std::unordered_set<int> expectedCTerminalMasses = {101, 230, 407};
        std::unordered_set<int> foundcTerminalMasses;
        for ( auto v: cTerminalMasses ) {
            foundcTerminalMasses.insert(static_cast<int>(std::round(v->NeutralMass * std::pow(10, 1))) / std::pow(10, 1));
        }
        Assert::IsTrue ( expectedCTerminalMasses == foundcTerminalMasses );

        delete aCompactPeptide;
        delete digestionParams;
        delete phosphorylation;
        delete p;
    }

    void TestCompactPeptide::TestCompactPeptideMasses_cTerminalModifiedPeptide_NeutralLoss()
    {
        Protein *p = new Protein("PET", "accession");
        ModificationMotif *motif;
        ModificationMotif::TryGetMotif("T", &motif);
        std::unordered_map<std::string, std::vector<std::string>> map1, map2;
        std::vector<double> dvec = {0, ChemicalFormula::ParseFormula("H3O4P1")->getMonoisotopicMass()};
        std::unordered_map<DissociationType, std::vector<double>> map3;
        map3[MassSpectrometry::DissociationType::HCD] =  dvec;
        std::unordered_map<DissociationType, std::vector<double>> map4;
        std::vector<std::string> svec;        

        Modification *phosphorylation = new Modification("phospho", "", "CommonBiological", "", motif, "Anywhere.",
                                                         ChemicalFormula::ParseFormula("H1O3P1"), std::nullopt,
                                                         map1, map2, svec, map3, map4, "");

        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 2, std::numeric_limits<int>::max(), 1024,
                                                               InitiatorMethionineBehavior::Variable, 2,
                                                               CleavageSpecificity::Full, FragmentationTerminus::Both);

        std::vector<Modification*> mvec;
        std::vector<Modification*> pvec = {phosphorylation};
        auto aPeptideWithSetModifications = p->Digest(digestionParams, pvec, mvec).front();

        auto aCompactPeptide = new CompactPeptide(aPeptideWithSetModifications, FragmentationTerminus::Both);

        //var nTerminalMasses = aCompactPeptide.TerminalMasses.Where(v => v.Terminus == FragmentationTerminus.N);
        std::vector<NeutralTerminusFragment*> nTerminalMasses;
        for ( auto v: aCompactPeptide->getTerminalMasses() ) {
            if ( v->Terminus == FragmentationTerminus::N ) {
                nTerminalMasses.push_back(v);
            }
        }
        std::unordered_set<int> expectedNTerminalMasses = {97, 226};
        std::unordered_set<int> foundnTerminalMasses;
        for ( auto v: nTerminalMasses ) {
            foundnTerminalMasses.insert(static_cast<int>(std::round(v->NeutralMass * std::pow(10, 1))) / std::pow(10, 1));
        }
        Assert::IsTrue ( expectedNTerminalMasses == foundnTerminalMasses);

        //evaluate C-terminal masses
        std::vector<NeutralTerminusFragment*> cTerminalMasses;
        for ( auto v: aCompactPeptide->getTerminalMasses() ) {
            if ( v->Terminus == FragmentationTerminus::C ) {
                cTerminalMasses.push_back(v);
            }
        }

        std::unordered_set<int> expectedCTerminalMasses = {181, 310, 407};
        std::unordered_set<int> foundcTerminalMasses;
        for ( auto v: cTerminalMasses ) {
            foundcTerminalMasses.insert(static_cast<int>(std::round(v->NeutralMass * std::pow(10, 1))) / std::pow(10, 1));
        }
        Assert::IsTrue ( expectedCTerminalMasses == foundcTerminalMasses );

        delete aCompactPeptide;
        delete digestionParams;
        delete phosphorylation;
        delete p;
    }

    void TestCompactPeptide::TestCompactPeptideMasses_internallyModifiedPeptide_NeutralLoss()
    {
        Protein *p = new Protein("PET", "accession");
        ModificationMotif *motif;
        ModificationMotif::TryGetMotif("E", &motif);
        std::unordered_map<std::string, std::vector<std::string>> map1, map2;
        std::vector<double> dvec = {0, ChemicalFormula::ParseFormula("H3O4P1")->getMonoisotopicMass()};
        std::unordered_map<DissociationType, std::vector<double>> map3;
        map3[MassSpectrometry::DissociationType::HCD] =  dvec;
        std::unordered_map<DissociationType, std::vector<double>> map4;
        std::vector<std::string> svec;        
        
        Modification *phosphorylation = new Modification("phospho", "", "CommonBiological", "", motif, "Anywhere.",
                                                         ChemicalFormula::ParseFormula("H1O3P1"), std::nullopt,
                                                         map1, map2, svec, map3, map4, "");

        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 2, std::numeric_limits<int>::max(), 1024,
                                                               InitiatorMethionineBehavior::Variable, 2,
                                                               CleavageSpecificity::Full,
                                                               FragmentationTerminus::Both);

        std::vector<Modification*> mvec;
        std::vector<Modification*> pvec = {phosphorylation};
        auto aPeptideWithSetModifications = p->Digest(digestionParams, pvec, mvec).front();

        std::vector<Product*> allFragmentNeutralMasses = aPeptideWithSetModifications->Fragment(
            DissociationType::HCD,
            FragmentationTerminus::Both);

        //evaluate N-terminal masses
#ifdef ORIG
        // EDGAR: This test is different, that's why I retain the original code from the C# to C++ translator
        // as well
        auto n = allFragmentNeutralMasses->Where([&] (std::any f)
        {
            delete p;
            return f::TerminusFragment->Terminus == FragmentationTerminus::N;
        }).ToList();
#endif        
        std::vector<Product*> n;
        for ( auto *f: allFragmentNeutralMasses ) {
            if ( f->TerminusFragment->Terminus == FragmentationTerminus::N ) {
                n.push_back(f);
            }
        }
        std::unordered_set<int> expectedNTerminalMasses = {97, 306, 208};
        std::unordered_set<int> foundn;
        for ( auto v: n ) {
            foundn.insert(static_cast<int>(std::round(v->NeutralMass * std::pow(10, 1))) / std::pow(10, 1));
        }
        Assert::IsTrue ( expectedNTerminalMasses == foundn );

        //evaluate C-terminal masses
#ifdef ORIG
        auto c = allFragmentNeutralMasses->Where([&] (std::any f)
        {
            delete p;
            return f::TerminusFragment->Terminus == FragmentationTerminus::C;
        }).ToList();
#endif
        std::vector<Product*> c;
        for ( auto f: allFragmentNeutralMasses ) {
            if ( f->TerminusFragment->Terminus == FragmentationTerminus::C ) {
                c.push_back(f);
            }
        }
        std::unordered_set<int> expectedCTerminalMasses = {119, 328, 230};
        std::unordered_set<int> foundc;
        for ( auto v: c ) {
            foundc.insert(static_cast<int>(std::round(v->NeutralMass * std::pow(10, 1))) / std::pow(10, 1));
        }
        Assert::IsTrue ( expectedCTerminalMasses == foundc );
        
        delete digestionParams;
        delete phosphorylation;
        delete p;
    }


    void TestCompactPeptide::TestCompactPeptideMasses_nTerminalModifiedPeptide_NeutralLoss_DissociationTypes_AnyActivationType_and_HCD()
    {
        Protein *p = new Protein("PET", "accession");
        ModificationMotif *motif;
        ModificationMotif::TryGetMotif("P", &motif);
        std::unordered_map<std::string, std::vector<std::string>> map1, map2;
        std::vector<double> dvec = {0, ChemicalFormula::ParseFormula("H3O4P1")->getMonoisotopicMass()};
        std::unordered_map<DissociationType, std::vector<double>> map3;
        map3[MassSpectrometry::DissociationType::AnyActivationType] =  dvec;
        std::unordered_map<DissociationType, std::vector<double>> map4;
        std::vector<std::string> svec;        

        Modification *phosphorylation = new Modification("phospho", "", "CommonBiological", "", motif, "Anywhere.",
                                                         ChemicalFormula::ParseFormula("H1O3P1"), std::nullopt,
                                                         map1, map2, svec, map3, map4, "");

        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 2, std::numeric_limits<int>::max(), 1024,
                                                               InitiatorMethionineBehavior::Variable, 2, CleavageSpecificity::Full,
                                                               FragmentationTerminus::Both);

        std::vector<Modification*> mvec;
        std::vector<Modification*> pvec = {phosphorylation};
        auto aPeptideWithSetModifications = p->Digest(digestionParams, pvec, mvec).front();

        auto aCompactPeptide = new CompactPeptide(aPeptideWithSetModifications, FragmentationTerminus::Both);

        //evaluate N-terminal masses
        std::vector<NeutralTerminusFragment*> nTerminalMasses;
        for ( auto v: aCompactPeptide->getTerminalMasses() ) {
            if ( v->Terminus == FragmentationTerminus::N ) {
                nTerminalMasses.push_back(v);
            }
        }

        std::unordered_set<int> expectedNTerminalMasses = {177, 306};
        std::unordered_set<int> foundnTerminalMasses;
        for ( auto v: nTerminalMasses ) {
            foundnTerminalMasses.insert(static_cast<int>(std::round(v->NeutralMass * std::pow(10, 1))) / std::pow(10, 1));
        }
        Assert::IsTrue ( expectedNTerminalMasses == foundnTerminalMasses);

        //evaluate C-terminal masses
        std::vector<NeutralTerminusFragment*> cTerminalMasses;
        for ( auto v: aCompactPeptide->getTerminalMasses() ) {
            if ( v->Terminus == FragmentationTerminus::C ) {
                cTerminalMasses.push_back(v);
            }
        }

        std::unordered_set<int> expectedCTerminalMasses = {101, 230, 407};
        std::unordered_set<int> foundcTerminalMasses;
        for ( auto v: cTerminalMasses ) {
            foundcTerminalMasses.insert(static_cast<int>(std::round(v->NeutralMass * std::pow(10, 1))) / std::pow(10, 1));
        }
        Assert::IsTrue ( expectedCTerminalMasses == foundcTerminalMasses );

        delete aCompactPeptide;
        delete digestionParams;
        delete phosphorylation;
        delete p;
    }

    void TestCompactPeptide::TestCompactPeptideMasses_nTerminalModifiedPeptide_NeutralLoss_DissociationTypes_CID_and_HCD()
    {
        Protein *p = new Protein("PET", "accession");
        ModificationMotif *motif;
        ModificationMotif::TryGetMotif("P", &motif);
        std::unordered_map<std::string, std::vector<std::string>> map1, map2;
        std::vector<double> dvec = {0, ChemicalFormula::ParseFormula("H3O4P1")->getMonoisotopicMass()};
        std::unordered_map<DissociationType, std::vector<double>> map3;
        map3[MassSpectrometry::DissociationType::CID] =  dvec;
        std::unordered_map<DissociationType, std::vector<double>> map4;
        std::vector<std::string> svec;        

        Modification *phosphorylation = new Modification("phospho", "", "CommonBiological", "", motif, "Anywhere.",
                                                         ChemicalFormula::ParseFormula("H1O3P1"), std::nullopt,
                                                         map1, map2, svec, map3, map4, "");
        
        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 2, std::numeric_limits<int>::max(), 1024,
                                                               InitiatorMethionineBehavior::Variable, 2, CleavageSpecificity::Full,
                                                               FragmentationTerminus::Both);

        std::vector<Modification*> mvec;
        std::vector<Modification*> pvec = {phosphorylation};
        auto aPeptideWithSetModifications = p->Digest(digestionParams, pvec, mvec).front();

        auto aCompactPeptide = new CompactPeptide(aPeptideWithSetModifications, FragmentationTerminus::Both);

        //evaluate N-terminal masses
        std::vector<NeutralTerminusFragment*> nTerminalMasses;
        for ( auto v: aCompactPeptide->getTerminalMasses() ) {
            if ( v->Terminus == FragmentationTerminus::N ) {
                nTerminalMasses.push_back(v);
            }
        }

        std::unordered_set<int> expectedNTerminalMasses = {177, 306};
        std::unordered_set<int> foundnTerminalMasses;
        for ( auto v: nTerminalMasses ) {
            foundnTerminalMasses.insert(static_cast<int>(std::round(v->NeutralMass * std::pow(10, 1))) / std::pow(10, 1));
        }
        Assert::IsTrue ( expectedNTerminalMasses == foundnTerminalMasses);

        //evaluate C-terminal masses
        std::vector<NeutralTerminusFragment*> cTerminalMasses;
        for ( auto v: aCompactPeptide->getTerminalMasses() ) {
            if ( v->Terminus == FragmentationTerminus::C ) {
                cTerminalMasses.push_back(v);
            }
        }

        std::unordered_set<int> expectedCTerminalMasses = {101, 230, 407};
        std::unordered_set<int> foundcTerminalMasses;
        for ( auto v: cTerminalMasses ) {
            foundcTerminalMasses.insert(static_cast<int>(std::round(v->NeutralMass * std::pow(10, 1))) / std::pow(10, 1));
        }
        Assert::IsTrue ( expectedCTerminalMasses == foundcTerminalMasses );

        delete aCompactPeptide;
        delete digestionParams;
        delete phosphorylation;
        delete p;
    }

}
