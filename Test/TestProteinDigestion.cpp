#include "TestProteinDigestion.h"
#include "../Proteomics/Proteomics.h"
#include "../MassSpectrometry/Enums/DissociationType.h"
#include "../Chemistry/Chemistry.h"

#include "../UsefulProteomicsDatabases/PeriodicTableLoader.h"
#include "MzLibAssert.h"

#include <limits>
#include <cmath>

int main ( int argc, char **argv )
{

    int i=0;
    std::cout << i << ". PeriodicTableLoader" << std::endl;    
    const std::string elfile="elements.dat";
    const std::string &elr=elfile;
    //UsefulProteomicsDatabases::PeriodicTableLoader::Load (elr);
    Chemistry::PeriodicTable::Load (elr);

    std::cout << ++i << ". TestGoodPeptide" << std::endl;        
    Test::TestProteinDigestion::TestGoodPeptide();
    
    std::cout << ++i << ". TestNoCleavage" << std::endl;        
    Test::TestProteinDigestion::TestNoCleavage();

    std::cout << ++i << ". TestBadPeptide" << std::endl;        
    Test::TestProteinDigestion::TestBadPeptide();
    
    std::cout << ++i << ". TestPeptideWithSetModifications" << std::endl;        
    Test::TestProteinDigestion::TestPeptideWithSetModifications();

    std::cout << ++i << ". TestPeptideWithFixedModifications" << std::endl;        
    Test::TestProteinDigestion::TestPeptideWithFixedModifications();

    std::cout << ++i << ". TestDigestIndices" << std::endl;        
    Test::TestProteinDigestion::TestDigestIndices();

#ifdef LATER
    std::cout << ++i << ". TestDigestDecoy" << std::endl;        
    Test::TestProteinDigestion::TestDigestDecoy();

    std::cout << ++i << ". TestGoodPeptideWithLength" << std::endl;        
    Test::TestProteinDigestion::TestGoodPeptideWithLength();

    std::cout << ++i << ". Test_ProteinDigest" << std::endl;        
    Test::TestProteinDigestion::Test_ProteinDigest();

    std::cout << ++i << ". TestReadPeptideFromString" << std::endl;        
    Test::TestProteinDigestion::TestReadPeptideFromString();
#endif
    
    return 0;
}

namespace Test
{

    void TestProteinDigestion::TestGoodPeptide()
    {
        auto prot = new Protein("MNNNKQQQQ", "");
        auto motifList = DigestionMotif::ParseDigestionMotifsFromString("K|");
        auto protease = new Protease("CustomizedProtease", CleavageSpecificity::Full, "", "", motifList);
        ProteaseDictionary::insert(protease->getName(), protease);
        DigestionParams *digestionParams = new DigestionParams(protease->getName(), 0, 1, std::numeric_limits<int>::max(), 
							       1024, InitiatorMethionineBehavior::Retain, 2, 
							       CleavageSpecificity::Full,
							       FragmentationTerminus::Both);
        std::vector<Modification*> variableModifications;
        std::vector<Modification*> vMods;
        auto ye = prot->Digest(digestionParams, vMods, variableModifications);//.ToList();

        Assert::AreEqual(2, (int)ye.size());

        auto pep1 = ye[0];
        Assert::IsTrue(pep1->getMonoisotopicMass() > 0);

        auto test = pep1->Fragment(DissociationType::HCD, FragmentationTerminus::Both);

        for (auto huh : pep1->Fragment(DissociationType::HCD, FragmentationTerminus::Both))
        {
            Assert::IsTrue(huh->NeutralMass > 0);
        }
        auto pep2 = ye[1];
        Assert::IsTrue(pep2->getMonoisotopicMass() > 0);
        for (auto huh : pep2->Fragment(DissociationType::HCD, FragmentationTerminus::Both))
        {
            Assert::IsTrue(huh->NeutralMass > 0);
        }

	delete digestionParams;
	//delete protease;
        delete prot;
    }

    void TestProteinDigestion::TestNoCleavage()
    {
        std::vector<Modification*> fixedModifications;
        std::vector<ProteolysisProduct*> vP ={ new ProteolysisProduct(std::make_optional(5),std::make_optional(6), "lala")};
        std::string accession="", organism="";
        std::vector<std::tuple<std::string, std::string>> geneNames;
        auto prot = new Protein("MNNNKQQQQ", accession, organism, geneNames,
                                std::unordered_map<int, std::vector<Modification*>>(), vP);
        
        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 5, std::numeric_limits<int>::max(), 
							       1024, InitiatorMethionineBehavior::Variable, 2, 
							       CleavageSpecificity::Full, FragmentationTerminus::Both);
        std::vector<Modification*> vM;
        auto ye = prot->Digest(digestionParams, fixedModifications, vM);//.ToList();
        Assert::AreEqual(3, (int)ye.size());
        
	delete digestionParams;
        delete prot;
    }

        void TestProteinDigestion::TestBadPeptide()
    {
        auto prot = new Protein("MNNNKQQXQ", "");
        auto motifList = DigestionMotif::ParseDigestionMotifsFromString("K|");
        auto protease = new Protease("Custom Protease7", CleavageSpecificity::Full, "", "", motifList);
        ProteaseDictionary::insert(protease->getName(), protease);
        DigestionParams *digestionParams = new DigestionParams(protease->getName(), 0, 1, std::numeric_limits<int>::max(), 
							       1024, InitiatorMethionineBehavior::Retain, 2, 
							       CleavageSpecificity::Full, FragmentationTerminus::Both);
        std::vector<Modification*>v1, v2;
        auto ye = prot->Digest(digestionParams, v1, v2);//.ToList();

        Assert::AreEqual(2, (int)ye.size() );
        auto pep1 = ye[0];
        
        Assert::IsTrue(pep1->getMonoisotopicMass() > 0);
        for (auto huh : pep1->Fragment(DissociationType::HCD, FragmentationTerminus::Both))
        {
            Assert::IsTrue(huh->NeutralMass > 0);
        }
        
        auto pep2 = ye[1];
        Assert::IsTrue(std::isnan(pep2->getMonoisotopicMass()) );
        auto cool = pep2->Fragment(DissociationType::HCD, FragmentationTerminus::Both);//->ToArray();
        Assert::IsTrue(cool[0]->NeutralMass > 0);
        Assert::IsTrue(cool[1]->NeutralMass > 0);
        Assert::IsTrue(cool[3]->NeutralMass > 0);
        Assert::IsTrue(std::isnan(cool[2]->NeutralMass));
        Assert::IsTrue(std::isnan(cool[4]->NeutralMass));
        Assert::IsTrue(std::isnan(cool[5]->NeutralMass));
        Assert::IsTrue((int)cool.size() == 6);

	delete digestionParams;
	delete protease;
        delete prot;
    }

    void TestProteinDigestion::TestPeptideWithSetModifications()
    {
        auto prot = new Protein("M", "");
        DigestionParams *digestionParams = new DigestionParams("trypsin", 0, 1, std::numeric_limits<int>::max(), 
							       1024, InitiatorMethionineBehavior::Variable, 3, 
							       CleavageSpecificity::Full, FragmentationTerminus::Both); 
	// if you pass Custom Protease7 this test gets really flakey.
        std::vector<Modification*> variableModifications;
        ModificationMotif *motif;
        ModificationMotif::TryGetMotif("M", &motif);

        Modification tempVar("ProtNmod", "", "", "", motif, "N-terminal.", ChemicalFormula::ParseFormula("H"), std::make_optional(PeriodicTable::GetElement(1)->getPrincipalIsotope()->getAtomicMass()), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");
        variableModifications.push_back(&tempVar);

        Modification tempVar2("pepNmod", "", "", "", motif, "Peptide N-terminal.", ChemicalFormula::ParseFormula("H"), std::make_optional(PeriodicTable::GetElement(1)->getPrincipalIsotope()->getAtomicMass()), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");
        variableModifications.push_back(&tempVar2);

        Modification tempVar3("resMod", "", "", "", motif, "Anywhere.", ChemicalFormula::ParseFormula("H"), std::make_optional(PeriodicTable::GetElement(1)->getPrincipalIsotope()->getAtomicMass()), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");
        variableModifications.push_back(&tempVar3);

        Modification tempVar4("PepCmod", "", "", "", motif, "Peptide C-terminal.", ChemicalFormula::ParseFormula("H"), std::make_optional(PeriodicTable::GetElement(1)->getPrincipalIsotope()->getAtomicMass()), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");
        variableModifications.push_back(&tempVar4);

        Modification tempVar5("ProtCmod", "", "", "", motif, "C-terminal.", ChemicalFormula::ParseFormula("H"), std::make_optional(PeriodicTable::GetElement(1)->getPrincipalIsotope()->getAtomicMass()), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");
        variableModifications.push_back(&tempVar5);

        std::vector<Modification*> vM;
        auto ye = prot->Digest(digestionParams, vM, variableModifications);
        Assert::AreEqual(3 * 2 * 3, (int)ye.size());
        std::string s = "[H]M[H][H]";
        Assert::AreEqual( s, ye.back()->getSequenceWithChemicalFormulas());

        double m1 = 5 * PeriodicTable::GetElement("H")->getPrincipalIsotope()->getAtomicMass() + 
	  Residue::ResidueMonoisotopicMass['M'] + PeriodicTable::GetElement("O")->getPrincipalIsotope()->getAtomicMass();

        //m1 = Math::Round(static_cast<double>(m1), 9, MidpointRounding::AwayFromZero);
        m1 = std::round(static_cast<double>(m1));
        
        double m2 = ye.back()->getMonoisotopicMass();
        double m3 = m1 - m2;

        Assert::IsTrue(m3 < 1e-9);

	delete digestionParams;
        delete prot;
    }


    void TestProteinDigestion::TestPeptideWithFixedModifications()
    {
        auto prot = new Protein("M", "");
        DigestionParams *digestionParams = new DigestionParams("trypsin", 0, 1, std::numeric_limits<int>::max(), 
							       1024, InitiatorMethionineBehavior::Variable, 3, 
							       CleavageSpecificity::Full, FragmentationTerminus::Both);
	// if you pass Custom Protease7 this test gets really flakey.
        std::vector<Modification*> fixedMods;
        ModificationMotif *motif;
        ModificationMotif::TryGetMotif("M", &motif);

        Modification tempVar("ProtNmod", "", "", "", motif, "N-terminal.", ChemicalFormula::ParseFormula("H"), std::make_optional(PeriodicTable::GetElement(1)->getPrincipalIsotope()->getAtomicMass()), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");
        fixedMods.push_back(&tempVar);

        Modification tempVar2("pepNmod", "", "", "", motif, "Peptide N-terminal.", ChemicalFormula::ParseFormula("H"), std::make_optional(PeriodicTable::GetElement(1)->getPrincipalIsotope()->getAtomicMass()), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");
        fixedMods.push_back(&tempVar2);

        Modification tempVar3("resMod", "", "", "", motif, "Anywhere.", ChemicalFormula::ParseFormula("H"), std::make_optional(PeriodicTable::GetElement(1)->getPrincipalIsotope()->getAtomicMass()), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");
        fixedMods.push_back(&tempVar3);

        Modification tempVar4("PepCmod", "", "", "", motif, "Peptide C-terminal.", ChemicalFormula::ParseFormula("H"), std::make_optional(PeriodicTable::GetElement(1)->getPrincipalIsotope()->getAtomicMass()), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");
        fixedMods.push_back(&tempVar4);

        Modification tempVar5("ProtCmod", "", "", "", motif, "C-terminal.", ChemicalFormula::ParseFormula("H"), std::make_optional(PeriodicTable::GetElement(1)->getPrincipalIsotope()->getAtomicMass()), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");
        fixedMods.push_back(&tempVar5);

        std::vector<Modification*> vM;
        auto ok = prot->Digest(digestionParams, fixedMods, vM);

        Assert::AreEqual(1, (int)ok.size());

        std::string s= "[:pepNmod on M]M[:resMod on M][:ProtCmod on M]";
        Assert::AreEqual(s, ok.front()->getFullSequence());

        std::string s2 = "[H]M[H][H]";
        Assert::AreEqual(s2, ok.front()->getSequenceWithChemicalFormulas());
        Assert::AreEqual(5 * PeriodicTable::GetElement("H")->getPrincipalIsotope()->getAtomicMass() +
			 Residue::ResidueMonoisotopicMass['M'] + PeriodicTable::GetElement("O")->getPrincipalIsotope()->getAtomicMass(), 
			 ok.back()->getMonoisotopicMass(), 1e-9);

	delete digestionParams;
        delete prot;
    }

    void TestProteinDigestion::TestDigestIndices()
    {
        ModificationMotif *motifN;
        ModificationMotif::TryGetMotif("N", &motifN);
        ModificationMotif *motifR;
        ModificationMotif::TryGetMotif("R", &motifR);

        Modification *modN = new Modification("myMod", "", "myModType", "", motifN, "Anywhere.", nullptr, std::make_optional(10), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");

        Modification *modR = new Modification("myMod", "", "myModType", "", motifR, "Anywhere.", nullptr, std::make_optional(10), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");

        std::unordered_map<int, std::vector<Modification*>> modDict =
        {
            {
                2, {modN}
            },
            {
                8, {modR}
            }
        };

        auto prot = new Protein("MNNNNKRRRRR", "", "", std::vector<std::tuple<std::string, std::string>>(), modDict, std::vector<ProteolysisProduct*>(), "", "", true, false, std::vector<DatabaseReference*>(), std::vector<SequenceVariation*>(), std::vector<SequenceVariation*>(), "", std::vector<DisulfideBond*>(), std::vector<SpliceSite*>(), "");

        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 5, std::numeric_limits<int>::max(), 1024, InitiatorMethionineBehavior::Retain, 2, CleavageSpecificity::Full, FragmentationTerminus::Both);

        std::vector<Modification *> vM1, vM2;
        auto digestedList = prot->Digest(digestionParams, vM1, vM2);
        auto ok1 = digestedList[1];
        auto ok2 = digestedList[3];

        Assert::AreEqual(1, ok1->getNumMods());
        auto mymap = ok1->getAllModsOneIsNterminus();
        Assert::IsTrue(mymap.find(3) != mymap.end());
        Assert::AreEqual(1, ok2->getNumMods());
        auto mymap2 = ok2->getAllModsOneIsNterminus();
        Assert::IsTrue(mymap2.find(3) != mymap.end() );

	delete digestionParams;
        delete prot;
        delete modR;
        delete modN;
    }

#ifdef LATER

    void TestProteinDigestion::TestDigestDecoy()
    {
        ModificationMotif motifN;
        ModificationMotif::TryGetMotif("N", motifN);
        ModificationMotif motifR;
        ModificationMotif::TryGetMotif("R", motifR);
        Modification *modN = new Modification("myMod", "", "myModType", "", motifN, "Anywhere.", nullptr, std::make_optional(10), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");
        Modification *modR = new Modification("myMod", "", "myModType", "", motifR, "Anywhere.", nullptr, std::make_optional(10), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");
        std::unordered_map<int, std::vector<Modification*>> modDict =
        {
            {
                2, {modN}
            },
            {
                8, {modR}
            }
        };
        auto prot = new Protein("MNNNNKRRRRR", "", "", std::vector<std::tuple<std::string, std::string>>(), modDict, std::vector<ProteolysisProduct>(), "", "", true, false, std::vector<DatabaseReference>(), std::vector<SequenceVariation>(), std::vector<SequenceVariation>(), "", std::vector<DisulfideBond>(), std::vector<SpliceSite>(), "");

        DigestionParams *digestionParams = new DigestionParams("trypsin", 2, 5, std::numeric_limits<int>::max(), 1024, InitiatorMethionineBehavior::Retain, 2, CleavageSpecificity::Full, FragmentationTerminus::Both);

        auto digestedList = prot->Digest(digestionParams, std::vector<Modification*>(), std::vector<Modification*>()).ToList();
        auto ok1 = digestedList[1];
        auto ok2 = digestedList[3];

        Assert::AreEqual(1, ok1.NumMods);
        Assert::IsTrue(ok1.AllModsOneIsNterminus->ContainsKey(3));
        Assert::AreEqual(1, ok2.NumMods);
        Assert::IsTrue(ok2.AllModsOneIsNterminus->ContainsKey(3));

        prot = new Protein("MNNNNKRRRRR", "", "", std::vector<std::tuple<std::string, std::string>>(), modDict);
        ok1 = prot->Digest(digestionParams, std::vector<Modification*>(), std::vector<Modification*>()).front();
        ok2 = prot->Digest(digestionParams, std::vector<Modification*>(), std::vector<Modification*>()).back();

        Assert::AreEqual(0, ok1.NumMods);
        Assert::IsFalse(ok1.AllModsOneIsNterminus::Any());
        Assert::AreEqual(2, ok2.NumMods);
        Assert::IsTrue(ok2.AllModsOneIsNterminus::Any());

	delete digestionParams;
        delete prot;
        delete modR;
        delete modN;
    }

    void TestProteinDigestion::TestGoodPeptideWithLength()
    {
        auto prot = new Protein("MNNNKQQQQMNNNKQQQQ", "");

        DigestionParams *digestionParams = new DigestionParams("trypsin", 0, 1, std::numeric_limits<int>::max(), 1024, InitiatorMethionineBehavior::Retain, 2, CleavageSpecificity::Full, FragmentationTerminus::Both);
        auto ye = prot->Digest(digestionParams, std::vector<Modification*>(), std::vector<Modification*>()).ToList();
        digestionParams = new DigestionParams("trypsin", 0, 5, std::numeric_limits<int>::max(), 1024, InitiatorMethionineBehavior::Retain, 2, CleavageSpecificity::Full, FragmentationTerminus::Both);
        auto ye1 = prot->Digest(digestionParams, std::vector<Modification*>(), std::vector<Modification*>()).ToList();
        digestionParams = new DigestionParams("trypsin", 0, 1, 5, 1024, InitiatorMethionineBehavior::Retain, 2, CleavageSpecificity::Full, FragmentationTerminus::Both);
        auto ye2 = prot->Digest(digestionParams, std::vector<Modification*>(), std::vector<Modification*>()).ToList();
        digestionParams = new DigestionParams("trypsin", 0, 5, 8, 1024, InitiatorMethionineBehavior::Retain, 2, CleavageSpecificity::Full, FragmentationTerminus::Both);
        auto ye3 = prot->Digest(digestionParams, std::vector<Modification*>(), std::vector<Modification*>()).ToList();
        Assert::AreEqual(3, ye.size());
        Assert::AreEqual(2, ye1.size());
        Assert::AreEqual(2, ye2.size());
        Assert::AreEqual(1, ye3.size());

	delete digestionParams;
        delete prot;
    }

    void TestProteinDigestion::Test_ProteinDigest()
    {
        DigestionParams *d = new DigestionParams("trypsin", 0, 5, std::numeric_limits<int>::max(), 1024, InitiatorMethionineBehavior::Retain, 2, CleavageSpecificity::Full, FragmentationTerminus::Both);
        ModificationMotif motif;
        ModificationMotif::TryGetMotif("D", motif);
        Modification *mod = new Modification("mod1", "", "mt", "", motif, "Anywhere.", nullptr, std::make_optional(10), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");

        std::unordered_map<int, std::vector<Modification*>> oneBasedModification =
        {
            {
                3, {mod}
            }
        };

        Protein *prot1 = new Protein("MEDEEK", "prot1", "", std::vector<std::tuple<std::string, std::string>>(), oneBasedModification, std::vector<ProteolysisProduct>(), "", "", false, false, std::vector<DatabaseReference>(), std::vector<SequenceVariation>(), std::vector<SequenceVariation>(), "", std::vector<DisulfideBond>(), std::vector<SpliceSite>(), "");

        auto pep1 = prot1->Digest(d, std::vector<Modification*>(), std::vector<Modification*>()).front();
        auto pep2 = prot1->Digest(d, std::vector<Modification*>(), std::vector<Modification*>()).back();

        Assert::AreEqual("MEDEEK", pep1->FullSequence);
        Assert::AreEqual("MED[mt:mod1 on D]EEK", pep2->FullSequence);

        delete prot1;
        delete mod;
	delete d;
    }

    void TestProteinDigestion::TestReadPeptideFromString()
    {
        // set up the test

        ModificationMotif target;
        ModificationMotif::TryGetMotif("T", target);

        Modification *carbamidomethylOnC = new Modification("Carbamidomethyl on C", "", "Common Fixed", "", target, "Unassigned.", ChemicalFormula::ParseFormula("C2H3NO"), std::nullopt, std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");
        std::string sequence = "HQVC[Common Fixed:Carbamidomethyl on C]TPGGTTIAGLC[Common Fixed:Carbamidomethyl on C]VMEEK";

        // parse the peptide from the string
        PeptideWithSetModifications *peptide = new PeptideWithSetModifications(sequence, std::unordered_map<std::string, Modification*>
        {
            {carbamidomethylOnC->getIdWithMotif(), carbamidomethylOnC}
        });

        // test base sequence and full sequence
        Assert::That(peptide->getBaseSequence() == "HQVCTPGGTTIAGLCVMEEK");
        Assert::That(peptide->getFullSequence() == sequence);

        // test peptide mass
        Assert::That(std::round(peptide->getMonoisotopicMass() * std::pow(10, 5)) / std::pow(10, 5) == 2187.01225);

        // test mods (correct id, correct number of mods, correct location of mods)
        Assert::That(peptide->getAllModsOneIsNterminus().First()->Value->IdWithMotif == "Carbamidomethyl on C");
        Assert::That(peptide->getAllModsOneIsNterminus().size() == 2);
        Assert::That((std::unordered_set<int>(peptide->getAllModsOneIsNterminus().Keys))->SetEquals(std::unordered_set<int> {5, 16}));

        // calculate fragments. just check that they exist and it doesn't crash
        std::vector<Product*> theoreticalFragments = peptide->Fragment(DissociationType::HCD, FragmentationTerminus::Both).ToList();
        Assert::That(theoreticalFragments.size() > 0);

        delete peptide;
	delete carbamidomethylOnC;
    }
#endif
}
