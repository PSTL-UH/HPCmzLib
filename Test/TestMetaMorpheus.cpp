#include "TestMetaMorpheus.h"
#include "../Proteomics/Protein/Protein.h"
#include "../Proteomics/Modifications/Modification.h"
#include "../Proteomics/Modifications/ModificationMotif.h"
#include "../Chemistry/ChemicalFormula.h"
#include "../MassSpectrometry/Enums/DissociationType.h"

#include "../UsefulProteomicsDatabases/PeriodicTableLoader.h"
#include "Assert.h"
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

#ifdef LATER
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
#endif
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
                nTerminalMasses.push_back(v);
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

#ifdef LATER
    void TestCompactPeptide::TestCompactPeptideMasses_nTerminalModifiedPeptide()
    {
        Protein *p = new Protein("PET", "accession");
        ModificationMotif motif;
        ModificationMotif::TryGetMotif("P", motif);
        Modification *phosphorylation = new Modification("phospho", "", "CommonBiological", "", motif, "Anywhere.",
                                                         ChemicalFormula::ParseFormula("H1O3P1"), std::nullopt,
                                                         std::unordered_map<std::string, std::vector<std::string>>(),
                                                         std::unordered_map<std::string, std::vector<std::string>>(),
                                                         std::vector<std::string>(),
                                                         std::unordered_map<DissociationType, std::vector<double>>(),
                                                         std::unordered_map<DissociationType, std::vector<double>>(), "");

        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 2, std::numeric_limits<int>::max(), 1024,
                                                               InitiatorMethionineBehavior::Variable,
                                                               2, CleavageSpecificity::Full, FragmentationTerminus::Both);
        auto aPeptideWithSetModifications = p->Digest(digestionParams, std::vector<Modification*> {phosphorylation},
                                                      std::vector<Modification*>()).front();

        auto aCompactPeptide = new CompactPeptide(aPeptideWithSetModifications, FragmentationTerminus::Both);

        //evaluate N-terminal masses
        auto nTerminalMasses = aCompactPeptide->TerminalMasses.Where([&] (std::any v)
        {
        delete aCompactPeptide;
        // C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams
        // was passed to a method or constructor. Handle memory management manually.
        // C# TO C++ CONVERTER TODO TASK: A 'delete phosphorylation' statement was not added since phosphorylation
        // was passed to a method or constructor. Handle memory management manually.
        delete p;
            return v->Terminus == FragmentationTerminus::N;
        });
        std::unordered_set<int> expectedNTerminalMasses = {177, 306};
        Assert::That(expectedNTerminalMasses.SetEquals(nTerminalMasses->Select([&] (std::any v)
        {
            static_cast<int>(std::round(v::NeutralMass * std::pow(10, 0))) / std::pow(10, 0);
        })));

        //evaluate C-terminal masses
        auto cTerminalMasses = aCompactPeptide->TerminalMasses.Where([&] (std::any v)
        {
        delete aCompactPeptide;
        // C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams
        // was passed to a method or constructor. Handle memory management manually.
        // C# TO C++ CONVERTER TODO TASK: A 'delete phosphorylation' statement was not added since phosphorylation
        // was passed to a method or constructor. Handle memory management manually.
        delete p;
            return v->Terminus == FragmentationTerminus::C;
        });
        std::unordered_set<int> expectedCTerminalMasses = {101, 230, 407};
        Assert::That(expectedCTerminalMasses.SetEquals(cTerminalMasses->Select([&] (std::any v)
        {
            static_cast<int>(std::round(v::NeutralMass * std::pow(10, 0))) / std::pow(10, 0);
        })));

        delete aCompactPeptide;
        // C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams
        // was passed to a method or constructor. Handle memory management manually.
        // C# TO C++ CONVERTER TODO TASK: A 'delete phosphorylation' statement was not added since phosphorylation
        // was passed to a method or constructor. Handle memory management manually.
        delete p;
    }

    void TestCompactPeptide::TestCompactPeptideMasses_cTerminalModifiedPeptide()
    {
        Protein *p = new Protein("PET", "accession");
        ModificationMotif motif;
        ModificationMotif::TryGetMotif("T", motif);
        Modification *phosphorylation = new Modification("phospho", "", "CommonBiological", "", motif, "Anywhere.",
                                                         ChemicalFormula::ParseFormula("H1O3P1"), std::nullopt,
                                                         std::unordered_map<std::string, std::vector<std::string>>(),
                                                         std::unordered_map<std::string, std::vector<std::string>>(),
                                                         std::vector<std::string>(),
                                                         std::unordered_map<DissociationType, std::vector<double>>(),
                                                         std::unordered_map<DissociationType, std::vector<double>>(), "");

        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 2, std::numeric_limits<int>::max(), 1024,
                                                               InitiatorMethionineBehavior::Variable,
                                                               2, CleavageSpecificity::Full, FragmentationTerminus::Both);
        auto aPeptideWithSetModifications = p->Digest(digestionParams, std::vector<Modification*> {phosphorylation},
                                                      std::vector<Modification*>()).front();

        auto aCompactPeptide = new CompactPeptide(aPeptideWithSetModifications, FragmentationTerminus::Both);

        //evaluate N-terminal masses
        auto nTerminalMasses = aCompactPeptide->TerminalMasses.Where([&] (std::any v)
        {
        delete aCompactPeptide;
        // C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams
        // was passed to a method or constructor. Handle memory management manually.
        // C# TO C++ CONVERTER TODO TASK: A 'delete phosphorylation' statement was not added since phosphorylation
        // was passed to a method or constructor. Handle memory management manually.
        delete p;
            return v->Terminus == FragmentationTerminus::N;
        });
        std::unordered_set<int> expectedNTerminalMasses = {97, 226};
        Assert::That(expectedNTerminalMasses.SetEquals(nTerminalMasses->Select([&] (std::any v)
        {
            static_cast<int>(std::round(v::NeutralMass * std::pow(10, 1))) / std::pow(10, 1);
        })));

        //evaluate C-terminal masses
        auto cTerminalMasses = aCompactPeptide->TerminalMasses.Where([&] (std::any v)
        {
        delete aCompactPeptide;
        // C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams
        // was passed to a method or constructor. Handle memory management manually.
        // C# TO C++ CONVERTER TODO TASK: A 'delete phosphorylation' statement was not added since phosphorylation
        // was passed to a method or constructor. Handle memory management manually.
        delete p;
            return v->Terminus == FragmentationTerminus::C;
        });
        std::unordered_set<int> expectedCTerminalMasses = {181, 310, 407};
        Assert::That(expectedCTerminalMasses.SetEquals(cTerminalMasses->Select([&] (std::any v)
        {
            static_cast<int>(std::round(v::NeutralMass * std::pow(10, 1))) / std::pow(10, 1);
        })));

        delete aCompactPeptide;
        // C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams
        // was passed to a method or constructor. Handle memory management manually.
        // C# TO C++ CONVERTER TODO TASK: A 'delete phosphorylation' statement was not added since phosphorylation
        // was passed to a method or constructor. Handle memory management manually.
        delete p;
    }

    void TestCompactPeptide::TestCompactPeptideMasses_internallyModifiedPeptide()
    {
        Protein *p = new Protein("PET", "accession");
        ModificationMotif motif;
        ModificationMotif::TryGetMotif("E", motif);
        Modification *phosphorylation = new Modification("phospho", "", "CommonBiological", "", motif, "Anywhere.",
                                                         ChemicalFormula::ParseFormula("H1O3P1"), std::nullopt,
                                                         std::unordered_map<std::string, std::vector<std::string>>(),
                                                         std::unordered_map<std::string, std::vector<std::string>>(),
                                                         std::vector<std::string>(),
                                                         std::unordered_map<DissociationType, std::vector<double>>(),
                                                         std::unordered_map<DissociationType, std::vector<double>>(), "");

        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 2, std::numeric_limits<int>::max(), 1024,
                                                               InitiatorMethionineBehavior::Variable, 2,
                                                               CleavageSpecificity::Full, FragmentationTerminus::Both);
        auto aPeptideWithSetModifications = p->Digest(digestionParams, std::vector<Modification*> {phosphorylation},
                                                      std::vector<Modification*>()).front();

        auto aCompactPeptide = new CompactPeptide(aPeptideWithSetModifications, FragmentationTerminus::Both);

        //evaluate N-terminal masses
        auto nTerminalMasses = aCompactPeptide->TerminalMasses.Where([&] (std::any v)
        {
        delete aCompactPeptide;
        // C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams
        // was passed to a method or constructor. Handle memory management manually.
        // C# TO C++ CONVERTER TODO TASK: A 'delete phosphorylation' statement was not added since phosphorylation
        // was passed to a method or constructor. Handle memory management manually.
        delete p;
            return v->Terminus == FragmentationTerminus::N;
        });
        std::unordered_set<int> expectedNTerminalMasses = {97, 306};
        std::unordered_set<int> foundNTerminalMasses = std::unordered_set<int>(nTerminalMasses->Select([&] (std::any v)
        {
            static_cast<int>(std::round(v::NeutralMass * std::pow(10, 0))) / std::pow(10, 0);
        }).ToList());

        Assert::That(expectedNTerminalMasses.SetEquals(foundNTerminalMasses));

        //evaluate C-terminal masses
        auto cTerminalMasses = aCompactPeptide->TerminalMasses.Where([&] (std::any v)
        {
        delete aCompactPeptide;
        // C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams
        // was passed to a method or constructor. Handle memory management manually.
        // C# TO C++ CONVERTER TODO TASK: A 'delete phosphorylation' statement was not added since phosphorylation 
        // was passed to a method or constructor. Handle memory management manually.
        delete p;
            return v->Terminus == FragmentationTerminus::C;
        });
        std::unordered_set<int> expectedCTerminalMasses = {101, 310, 407};
        std::unordered_set<int> foundCTerminalMasses = std::unordered_set<int>(cTerminalMasses->Select([&] (std::any v)
        {
            static_cast<int>(std::round(v::NeutralMass * std::pow(10, 0))) / std::pow(10, 0);
        }).ToList());

        Assert::That(expectedCTerminalMasses.SetEquals(foundCTerminalMasses));

        delete aCompactPeptide;
        // C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams
        // was passed to a method or constructor. Handle memory management manually.
        // C# TO C++ CONVERTER TODO TASK: A 'delete phosphorylation' statement was not added since phosphorylation
        // was passed to a method or constructor. Handle memory management manually.
        delete p;
    }

    void TestCompactPeptide::TestCompactPeptideMasses_nTerminalModifiedPeptide_NeutralLoss()
    {
        Protein *p = new Protein("PET", "accession");
        ModificationMotif motif;
        ModificationMotif::TryGetMotif("P", motif);
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

        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 2, std::numeric_limits<int>::max(), 1024,
                                                               InitiatorMethionineBehavior::Variable, 2, CleavageSpecificity::Full,
                                                               FragmentationTerminus::Both);
        auto aPeptideWithSetModifications = p->Digest(digestionParams, std::vector<Modification*> {phosphorylation},
                                                      std::vector<Modification*>()).front();

        auto aCompactPeptide = new CompactPeptide(aPeptideWithSetModifications, FragmentationTerminus::Both);

        //evaluate N-terminal masses
        auto nTerminalMasses = aCompactPeptide->TerminalMasses.Where([&] (std::any v)
        {
        delete aCompactPeptide;
        // C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams
        // was passed to a method or constructor. Handle memory management manually.
        // C# TO C++ CONVERTER TODO TASK: A 'delete phosphorylation' statement was not added since phosphorylation
        // was passed to a method or constructor. Handle memory management manually.
        delete p;
            return v->Terminus == FragmentationTerminus::N;
        });
        std::unordered_set<int> expectedNTerminalMasses = {177, 306};
        Assert::That(expectedNTerminalMasses.SetEquals(nTerminalMasses->Select([&] (std::any v)
        {
            static_cast<int>(std::round(v::NeutralMass * std::pow(10, 0))) / std::pow(10, 0);
        })));

        //evaluate C-terminal masses
        auto cTerminalMasses = aCompactPeptide->TerminalMasses.Where([&] (std::any v)
        {
        delete aCompactPeptide;
        // C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams
        // was passed to a method or constructor. Handle memory management manually.
        // C# TO C++ CONVERTER TODO TASK: A 'delete phosphorylation' statement was not added since phosphorylation
        // was passed to a method or constructor. Handle memory management manually.
        delete p;
            return v->Terminus == FragmentationTerminus::C;
        });
        std::unordered_set<int> expectedCTerminalMasses = {101, 230, 407};
        Assert::That(expectedCTerminalMasses.SetEquals(cTerminalMasses->Select([&] (std::any v)
        {
            static_cast<int>(std::round(v::NeutralMass * std::pow(10, 0))) / std::pow(10, 0);
        })));

        delete aCompactPeptide;
        // C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams
        // was passed to a method or constructor. Handle memory management manually.
        // C# TO C++ CONVERTER TODO TASK: A 'delete phosphorylation' statement was not added since phosphorylation
        // was passed to a method or constructor. Handle memory management manually.
        delete p;
    }

    void TestCompactPeptide::TestCompactPeptideMasses_cTerminalModifiedPeptide_NeutralLoss()
    {
        Protein *p = new Protein("PET", "accession");
        ModificationMotif motif;
        ModificationMotif::TryGetMotif("T", motif);
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

        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 2, std::numeric_limits<int>::max(), 1024,
                                                               InitiatorMethionineBehavior::Variable, 2,
                                                               CleavageSpecificity::Full, FragmentationTerminus::Both);
        auto aPeptideWithSetModifications = p->Digest(digestionParams, std::vector<Modification*> {phosphorylation},
                                                      std::vector<Modification*>()).front();

        auto aCompactPeptide = new CompactPeptide(aPeptideWithSetModifications, FragmentationTerminus::Both);

        //var nTerminalMasses = aCompactPeptide.TerminalMasses.Where(v => v.Terminus == FragmentationTerminus.N);
        auto nTerminalMasses = aCompactPeptide->TerminalMasses.Where([&] (std::any v)
        {
        delete aCompactPeptide;
        // C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams
        // was passed to a method or constructor. Handle memory management manually.
        // C# TO C++ CONVERTER TODO TASK: A 'delete phosphorylation' statement was not added since phosphorylation
        // was passed to a method or constructor. Handle memory management manually.
        delete p;
            return v->Terminus == FragmentationTerminus::N;
        });
        std::unordered_set<int> foundNTerminalMasses = std::unordered_set<int>(nTerminalMasses->Select([&] (std::any v)
        {
            static_cast<int>(std::round(v::NeutralMass * std::pow(10, 0))) / std::pow(10, 0);
        }).ToList());
        std::unordered_set<int> expectedNTerminalMasses = {97, 226};

        Assert::That(expectedNTerminalMasses.SetEquals(foundNTerminalMasses));

        //evaluate C-terminal masses
        auto cTerminalMasses = aCompactPeptide->TerminalMasses.Where([&] (std::any v)
        {
        delete aCompactPeptide;
        // C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams
        // was passed to a method or constructor. Handle memory management manually.
        // C# TO C++ CONVERTER TODO TASK: A 'delete phosphorylation' statement was not added since phosphorylation
        // was passed to a method or constructor. Handle memory management manually.
        delete p;
            return v->Terminus == FragmentationTerminus::C;
        });
        std::unordered_set<int> foundCTerminalMasses = std::unordered_set<int>(cTerminalMasses->Select([&] (std::any v)
        {
            static_cast<int>(std::round(v::NeutralMass * std::pow(10, 0))) / std::pow(10, 0);
        }).ToList());
        std::unordered_set<int> expectedCTerminalMasses = {181, 310, 407};

        Assert::That(expectedCTerminalMasses.SetEquals(foundCTerminalMasses));

        delete aCompactPeptide;
        // C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams
        // was passed to a method or constructor. Handle memory management manually.
        // C# TO C++ CONVERTER TODO TASK: A 'delete phosphorylation' statement was not added since phosphorylation
        // was passed to a method or constructor. Handle memory management manually.
        delete p;
    }

    void TestCompactPeptide::TestCompactPeptideMasses_internallyModifiedPeptide_NeutralLoss()
    {
        Protein *p = new Protein("PET", "accession");
        ModificationMotif motif;
        ModificationMotif::TryGetMotif("E", motif);
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

        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 2, std::numeric_limits<int>::max(), 1024,
                                                               InitiatorMethionineBehavior::Variable, 2, CleavageSpecificity::Full,
                                                               FragmentationTerminus::Both);
        auto aPeptideWithSetModifications = p->Digest(digestionParams, std::vector<Modification*> {phosphorylation},
                                                      std::vector<Modification*>()).front();

        auto allFragmentNeutralMasses = aPeptideWithSetModifications->Fragment(DissociationType::HCD, FragmentationTerminus::Both);

        //evaluate N-terminal masses
        auto n = allFragmentNeutralMasses->Where([&] (std::any f)
        {
            // C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams
            // was passed to a method or constructor. Handle memory management manually.
            // C# TO C++ CONVERTER TODO TASK: A 'delete phosphorylation' statement was not added since phosphorylation
            // was passed to a method or constructor. Handle memory management manually.
        delete p;
            return f::TerminusFragment->Terminus == FragmentationTerminus::N;
        }).ToList();
        std::unordered_set<int> expectedNTerminalMasses = {97, 306, 208};
        Assert::That(expectedNTerminalMasses.SetEquals(n.Select([&] (std::any v)
        {
            static_cast<int>(std::round(v::NeutralMass * std::pow(10, 1))) / std::pow(10, 1);
        })));

        //evaluate C-terminal masses
        auto c = allFragmentNeutralMasses->Where([&] (std::any f)
        {
            // C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams
            // was passed to a method or constructor. Handle memory management manually.
            // C# TO C++ CONVERTER TODO TASK: A 'delete phosphorylation' statement was not added since phosphorylation
            // was passed to a method or constructor. Handle memory management manually.
        delete p;
            return f::TerminusFragment->Terminus == FragmentationTerminus::C;
        }).ToList();
        std::unordered_set<int> expectedCTerminalMasses = {119, 328, 230};
        Assert::That(expectedCTerminalMasses.SetEquals(c.Select([&] (std::any v)
        {
            static_cast<int>(std::round(v::NeutralMass * std::pow(10, 1))) / std::pow(10, 1);
        })));

        // C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams was
        // passed to a method or constructor. Handle memory management manually.
        // C# TO C++ CONVERTER TODO TASK: A 'delete phosphorylation' statement was not added since phosphorylation was
        // passed to a method or constructor. Handle memory management manually.
        delete p;
    }

    void TestCompactPeptide::TestCompactPeptideMasses_nTerminalModifiedPeptide_NeutralLoss_DissociationTypes_AnyActivationType_and_HCD()
    {
        Protein *p = new Protein("PET", "accession");
        ModificationMotif motif;
        ModificationMotif::TryGetMotif("P", motif);
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

        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 2, std::numeric_limits<int>::max(), 1024,
                                                               InitiatorMethionineBehavior::Variable, 2, CleavageSpecificity::Full,
                                                               FragmentationTerminus::Both);
        auto aPeptideWithSetModifications = p->Digest(digestionParams, std::vector<Modification*> {phosphorylation},
                                                      std::vector<Modification*>()).front();

        auto aCompactPeptide = new CompactPeptide(aPeptideWithSetModifications, FragmentationTerminus::Both);

        //evaluate N-terminal masses
        auto nTerminalMasses = aCompactPeptide->TerminalMasses.Where([&] (std::any v)
        {
        delete aCompactPeptide;
        // C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams
        // was passed to a method or constructor. Handle memory management manually.
        // C# TO C++ CONVERTER TODO TASK: A 'delete phosphorylation' statement was not added since phosphorylation
        // was passed to a method or constructor. Handle memory management manually.
        delete p;
            return v->Terminus == FragmentationTerminus::N;
        });
        std::unordered_set<int> expectedNTerminalMasses = {177, 306};
        Assert::That(expectedNTerminalMasses.SetEquals(nTerminalMasses->Select([&] (std::any v)
        {
            static_cast<int>(std::round(v::NeutralMass * std::pow(10, 0))) / std::pow(10, 0);
        })));

        //evaluate C-terminal masses
        auto cTerminalMasses = aCompactPeptide->TerminalMasses.Where([&] (std::any v)
        {
        delete aCompactPeptide;
        // C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams
        // was passed to a method or constructor. Handle memory management manually.
        // C# TO C++ CONVERTER TODO TASK: A 'delete phosphorylation' statement was not added since phosphorylation
        // was passed to a method or constructor. Handle memory management manually.
        delete p;
            return v->Terminus == FragmentationTerminus::C;
        });
        std::unordered_set<int> expectedCTerminalMasses = {101, 230, 407};
        Assert::That(expectedCTerminalMasses.SetEquals(cTerminalMasses->Select([&] (std::any v)
        {
            static_cast<int>(std::round(v::NeutralMass * std::pow(10, 0))) / std::pow(10, 0);
        })));

        delete aCompactPeptide;
        // C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams
        // was passed to a method or constructor. Handle memory management manually.
        // C# TO C++ CONVERTER TODO TASK: A 'delete phosphorylation' statement was not added since phosphorylation
        // was passed to a method or constructor. Handle memory management manually.
        delete p;
    }

    void TestCompactPeptide::TestCompactPeptideMasses_nTerminalModifiedPeptide_NeutralLoss_DissociationTypes_CID_and_HCD()
    {
        Protein *p = new Protein("PET", "accession");
        ModificationMotif motif;
        ModificationMotif::TryGetMotif("P", motif);
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
        
        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 2, std::numeric_limits<int>::max(), 1024,
                                                               InitiatorMethionineBehavior::Variable, 2, CleavageSpecificity::Full,
                                                               FragmentationTerminus::Both);
        auto aPeptideWithSetModifications = p->Digest(digestionParams, std::vector<Modification*> {phosphorylation},
                                                      std::vector<Modification*>()).front();

        auto aCompactPeptide = new CompactPeptide(aPeptideWithSetModifications, FragmentationTerminus::Both);

        //evaluate N-terminal masses
        auto nTerminalMasses = aCompactPeptide->TerminalMasses.Where([&] (std::any v)
        {
        delete aCompactPeptide;
        // C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams
        // was passed to a method or constructor. Handle memory management manually.
        // C# TO C++ CONVERTER TODO TASK: A 'delete phosphorylation' statement was not added since phosphorylation
        // was passed to a method or constructor. Handle memory management manually.
        delete p;
            return v->Terminus == FragmentationTerminus::N;
        });
        std::unordered_set<int> expectedNTerminalMasses = {177, 306};
        Assert::That(expectedNTerminalMasses.SetEquals(nTerminalMasses->Select([&] (std::any v)
        {
            static_cast<int>(std::round(v::NeutralMass * std::pow(10, 1))) / std::pow(10, 1);
        })));

        //evaluate C-terminal masses
        auto cTerminalMasses = aCompactPeptide->TerminalMasses.Where([&] (std::any v)
        {
        delete aCompactPeptide;
        // C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams
        // was passed to a method or constructor. Handle memory management manually.
        // C# TO C++ CONVERTER TODO TASK: A 'delete phosphorylation' statement was not added since phosphorylation
        // was passed to a method or constructor. Handle memory management manually.
        delete p;
            return v->Terminus == FragmentationTerminus::C;
        });
        std::unordered_set<int> expectedCTerminalMasses = {101, 230, 407};
        Assert::That(expectedCTerminalMasses.SetEquals(cTerminalMasses->Select([&] (std::any v)
        {
            static_cast<int>(std::round(v::NeutralMass * std::pow(10, 1))) / std::pow(10, 1);
        })));

        delete aCompactPeptide;
        // C# TO C++ CONVERTER TODO TASK: A 'delete digestionParams' statement was not added since digestionParams
        // was passed to a method or constructor. Handle memory management manually.
        // C# TO C++ CONVERTER TODO TASK: A 'delete phosphorylation' statement was not added since phosphorylation
        // was passed to a method or constructor. Handle memory management manually.
        delete p;
    }
#endif
}
