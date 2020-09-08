#include "TestPeptideWithSetMods.h"
#include "../Proteomics/Protein/Protein.h"
#include "../Proteomics/Modifications/Modification.h"
#include "../Proteomics/Modifications/ModificationMotif.h"
#include <bits/stdc++.h>
#include "../include/Assert.h"
#include "../UsefulProteomicsDatabases/PeriodicTableLoader.h"
#include "../Proteomics/Proteomics.h"
#include "../include/Sort.h"
#include "../FlashLFQ/Identification.h"

using namespace Proteomics;
using namespace Proteomics::Fragmentation;
using namespace Proteomics::ProteolyticDigestion;

int main () {
	int i=0;
	std::cout << i << ". PeriodicTableLoader" << std::endl;    
	const std::string elfile="elements.dat";
	const std::string &elr=elfile;
	Chemistry::PeriodicTable::Load (elr);
	//	UsefulProteomicsDatabases::PeriodicTableLoader::Load (elr);

	std::cout << ++i << ". TestDifferentProteaseEquals\n";
	Test::TestPeptideWithSetMods::TestDifferentProteaseEquals();

	std::cout << ++i << ". TestCTermAndLastSideChainModParsing" << std::endl;
	Test::TestPeptideWithSetMods::TestCTermAndLastSideChainModParsing();

	std::cout << ++i << ". TestSemiFewCleavages\n";
	Test::TestPeptideWithSetMods::TestSemiFewCleavages();

	std::cout << ++i << ". TestHardToParseModifiedSequence" << std::endl;
	Test::TestPeptideWithSetMods::TestHardToParseModifiedSequence();

	std::cout << ++i << ". TestSingleProteases\n";
	Test::TestPeptideWithSetMods::TestSemiFewCleavages();

	std::cout << ++i << ". TestNonAndSemiSpecificDigests\n";
	Test::TestPeptideWithSetMods::TestNonAndSemiSpecificDigests();

	return 0;
}

namespace Test
{
	void TestPeptideWithSetMods::TestDifferentProteaseEquals()
	{
		Protein *myProtein = new Protein("Sequence", "accession");

		DigestionParams *digest1 = new DigestionParams("trypsin", 0, 7, INT_MAX, 1024, InitiatorMethionineBehavior::Retain, 2, CleavageSpecificity::Full, FragmentationTerminus::Both);
		DigestionParams *digest2 = new DigestionParams("Lys-C (cleave before proline)", 0, 7, INT_MAX, 1024, InitiatorMethionineBehavior::Retain, 2, CleavageSpecificity::Full, FragmentationTerminus::Both);

		std::vector<std::vector<Modification*>> temp;

		for (int i = 0; i < 4; i++)
			temp.push_back(std::vector<Modification*>());

		std::vector<PeptideWithSetModifications*> pep1Front = (myProtein->Digest(digest1, temp[0], temp[1]));
		std::vector<PeptideWithSetModifications*> pep2Front = (myProtein->Digest(digest2, temp[2], temp[3]));
		PeptideWithSetModifications *pep1, *pep2;

		if (pep1Front.size() > 0)
			pep1 = pep1Front[0];
		else
			pep1 = nullptr;

		if (pep2Front.size() > 0)
			pep2 = pep2Front[0];
		else
			pep2 = nullptr;

		if (pep1 != nullptr || pep2 != nullptr) {
			Assert::IsTrue(pep1->getFullSequence() == pep2->getFullSequence());
			Assert::IsTrue(pep1->getProtein() == pep2->getProtein());
			Assert::IsTrue(!(pep1->getDigestionParams()->getProtease() == pep2->getDigestionParams()->getProtease()));
			Assert::IsTrue(!(pep1 == pep2));
			Assert::IsTrue(!(pep1->GetHashCode() == pep2->GetHashCode()));
		} else 
			std::cout << "\n\n\nError with test:\n"
				<< "Variable pep1 or pep2 couldn't get initialized by object defined from Protein class\n"
				<< "Object used function Digest from Protein class and failed initializing either pep1 or pep2\n"
				<< "Boolean tests skipped are:\n\n"
				<< "getFullSequence\n"
				<< "getProtein\n"
				<< "getProtease\n"
				<< "peptide equivilancy\n"
				<< "GetHashCode\n\n\n";

		for (auto i : pep1Front)
			if (i != nullptr)
				delete i;

		for (auto i : pep2Front)
			if (i != nullptr)
				delete i;

		delete digest1;
		delete digest2;
		delete myProtein;

	}

	void TestPeptideWithSetMods::TestSemiFewCleavages()
	{
		Protein *protein = new Protein("MQLLRCFSIFSVIASVLAQELTTICEQIPSPTLESTPYSLSTTTILANGKAMQGVFEYYKSVTFVSNCGSHPSTTSKGSPINTQYVF", "P32781");
		DigestionParams *nParams = new DigestionParams("trypsin", 2, 7, 50, 1024, InitiatorMethionineBehavior::Variable, 2, CleavageSpecificity::Semi, FragmentationTerminus::N);
		DigestionParams *cParams = new DigestionParams("trypsin", 2, 7, 50, 1024, InitiatorMethionineBehavior::Variable, 2, CleavageSpecificity::Semi, FragmentationTerminus::C);


		//Unit test is not crashing
		std::vector<std::vector<Modification*>> temp;

		for (int i = 0; i < 8; i++) {
			auto tempt = new std::vector<Modification*>;
			temp.push_back(*tempt);
		}

		std::vector<PeptideWithSetModifications*> vectorToTransfer = protein->Digest(nParams, temp[0], temp[1]);
		for (auto i : vectorToTransfer)
			if (i != nullptr)
				delete i;
		vectorToTransfer = protein->Digest(cParams, temp[0], temp[1]);

		Protein *protein2 = new Protein("MQFSTVASVAFVALANFVAAESAAAISQITDGQIQATTTATTEATTTAAPSSTVETVSPSSTETISQQTENGAAKAAVGMGAGALAAAAMLL", "P43497");

		for (auto i : vectorToTransfer)
			if (i != nullptr)
				delete i;
		vectorToTransfer = protein2->Digest(nParams, temp[4], temp[5]);
		for (auto i : vectorToTransfer)
			if (i != nullptr)
				delete i;
		vectorToTransfer = protein2->Digest(cParams, temp[6], temp[7]);
		for (auto i : vectorToTransfer)
			if (i != nullptr)
				delete i;

		delete protein2;
		delete protein;
		delete cParams;
		delete nParams;

	}

	void TestPeptideWithSetMods::TestNonAndSemiSpecificDigests()
	{
		std::vector<std::vector<Modification*>> initTempsForModificationPtr;
		unsigned short counterFor_initTempsForModificationPtr = 0;

		Protein *fiveCleavages = new Protein("MAAKCCKDDKEEKFFKGG", "fiveCleavages"); //protein with 5 K's
		std::vector<std::tuple<std::string, FragmentationTerminus>> trypticSequencesInducingClevage =
                    {std::tuple<std::string, FragmentationTerminus>("K",FragmentationTerminus::C)};
		std::vector<std::tuple<std::string, FragmentationTerminus>> trypticSequencesPreventingClevage;

		//make two identical proteases, but one is fully specific and one is semi specific
		auto motifList = DigestionMotif::ParseDigestionMotifsFromString("K|");
		Protease *trypsinForTestNonAndSemiSpecificDigests = new Protease("trypsinForTestNonAndSemiSpecificDigests",
                                                                                 CleavageSpecificity::Full, "asdf", "asdf", motifList);
		Protease *semiTrypsinForTestNonAndSemiSpecificDigests = new Protease("semitrypsinForTestNonAndSemiSpecificDigests",
                                                                                     CleavageSpecificity::Semi, "asdf", "asdf", motifList);

		//add these made up proteases to the dictionary
		ProteaseDictionary::insert(trypsinForTestNonAndSemiSpecificDigests->getName(),
                                           trypsinForTestNonAndSemiSpecificDigests);
		ProteaseDictionary::insert(semiTrypsinForTestNonAndSemiSpecificDigests->getName(),
                                           semiTrypsinForTestNonAndSemiSpecificDigests);
                
		//Digest with the full
		DigestionParams *fullyDigestParams = new DigestionParams(trypsinForTestNonAndSemiSpecificDigests->getName(), 3, 2);
		initTempsForModificationPtr.push_back(std::vector<Modification*>());
		initTempsForModificationPtr.push_back(std::vector<Modification*>());
		std::vector<PeptideWithSetModifications*> fiveCleavageProductsTrypsin = fiveCleavages->Digest(
                    fullyDigestParams,
                    initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 0],
                    initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 1]);

		counterFor_initTempsForModificationPtr += 2;
		Assert::AreEqual(22, (int)fiveCleavageProductsTrypsin.size());
                
		//digests with the semi (variable methionine)
		DigestionParams *semiDigestionParams = new DigestionParams(semiTrypsinForTestNonAndSemiSpecificDigests->getName(), 3, 2);
		initTempsForModificationPtr.push_back(std::vector<Modification*>());
		initTempsForModificationPtr.push_back(std::vector<Modification*>());
		std::vector<PeptideWithSetModifications*> fiveCleavageProductsSemiTrypsin = fiveCleavages->Digest(
                    semiDigestionParams,
                    initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 0],
                    initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 1]);
		counterFor_initTempsForModificationPtr += 2;

		//This is a partial list of the full peptides. From this, we can GENERATE every possible semi that we would expect to see
		std::vector<std::string> expectedProductsSemiFiveCleavages = {"MAAKCCKDDKEEK", "AAKCCKDDKEEK", "CCKDDKEEKFFK", "DDKEEKFFKGG",
                                                                              "EEKFFKGG", "FFKGG", "AAK", "AAKCCK", "AAKCCKDDK"};

		//Check that, when we digested with semi, we made all possible semi sequences, labeled full and semi correctly,
                //and have no duplicates
                int mycounter = -1;
		for (auto s : expectedProductsSemiFiveCleavages) //foreach precursor peptide
		{
                    mycounter++;
			for (int i = 0; i < s.length() - semiDigestionParams->getMinPeptideLength(); i++) //cleave it to be semi
			{
				std::string sToFind = s.substr(i); //get a peptide from this precursor (fixed C)
				/*
				   auto peps = fiveCleavageProductsSemiTrypsin.Where([&] (std::any x)
				   {
				   x::BaseSequence->Equals(sToFind);
				   })->ToArray(); //find the peptide in the digested list
				   */
				std::vector<PeptideWithSetModifications*> peps;

				for (auto ii : fiveCleavageProductsSemiTrypsin) {
                                    if(ii->getBaseSequence() == sToFind)
						peps.push_back(ii);
				}

                                //There should be exactly one! More than that means there are duplicates, fewer means we didn't generate it!
				Assert::IsTrue((int)peps.size() == 1);

				auto pep = peps[0]; //get that single peptide
				//if it's a full sequence (cleaved at both indexes (including termini))
				if ((pep->getBaseSequence()[0] == pep->getBaseSequence()[1] ||
                                     pep->getBaseSequence()[0] == 'M') &&
                                    (pep->getBaseSequence()[pep->getBaseSequence().size() - 1] == 'K' ||
                                     (pep->getBaseSequence()[pep->getBaseSequence().size() - 1] == 'G' &&
                                      pep->getBaseSequence()[pep->getBaseSequence().size() - 2] == 'G')))
				{
					Assert::IsTrue(pep->getCleavageSpecificityForFdrCategory() == CleavageSpecificity::Full);
				}
				else
				{
					Assert::IsTrue(pep->getCleavageSpecificityForFdrCategory() == CleavageSpecificity::Semi);
				}
				//try to remake the pwsm with unknown specificity... was it assigned the correct specificity?
				//lvalue conversion
				std::unordered_map<int, Modification*> tempOneModsOneIsNterminus1 = pep->getAllModsOneIsNterminus();
				PeptideWithSetModifications *pwsmRemake = new PeptideWithSetModifications(fiveCleavages, semiDigestionParams,
                                                                                                          pep->getOneBasedStartResidueInProtein(),
                                                                                                          pep->getOneBasedEndResidueInProtein(),
                                                                                                          CleavageSpecificity::Unknown, "", 3,
                                                                                                          tempOneModsOneIsNterminus1, 0);
				Assert::IsTrue(pwsmRemake->getCleavageSpecificityForFdrCategory() == pep->getCleavageSpecificityForFdrCategory());

				//Repeat the above going from the other direction (fixed N)
				sToFind = s.substr(0, semiDigestionParams->getMinPeptideLength() + i); //get a peptide from this precursor (fixed N)
				/*
				   peps = fiveCleavageProductsSemiTrypsin.Where([&] (std::any x)
				   {
				   x::BaseSequence->Equals(sToFind);
				   })->ToArray(); //find the peptide in the digested list*/

				peps.clear();

				for (auto ii : fiveCleavageProductsSemiTrypsin) {
					if (ii->getBaseSequence() == sToFind)
						peps.push_back(ii);
				}
                                
                                //There should be exactly one! More than that means there are duplicates, fewer means we didn't generate it!
                                Assert::IsTrue((int)peps.size() == 1);
                                
				pep = peps[0]; //get that single peptide
				//if it's a full sequence (cleaved at both indexes (including termini))
				if ((pep->getBaseSequence()[0] == pep->getBaseSequence()[1] || pep->getBaseSequence()[0] == 'M') &&
                                    pep->getBaseSequence()[pep->getBaseSequence().size() - 1] == 'K')
				{
					Assert::IsTrue(pep->getCleavageSpecificityForFdrCategory() == CleavageSpecificity::Full);
				}
				else
				{
					Assert::IsTrue(pep->getCleavageSpecificityForFdrCategory() == CleavageSpecificity::Semi);
				}
				//try to remake the pwsm with unknown specificity... was it assigned the correct specificity?
				if (pwsmRemake != nullptr)
					delete pwsmRemake;
				std::unordered_map<int, Modification*> tempOneModsOneIsNterminus2 = pep->getAllModsOneIsNterminus();
				pwsmRemake = new PeptideWithSetModifications(fiveCleavages, semiDigestionParams,
                                                                             pep->getOneBasedStartResidueInProtein(),
                                                                             pep->getOneBasedEndResidueInProtein(),
                                                                             CleavageSpecificity::Unknown, "", 3,
                                                                             tempOneModsOneIsNterminus2, 0);
				Assert::IsTrue(pwsmRemake->getCleavageSpecificityForFdrCategory() == pep->getCleavageSpecificityForFdrCategory());

				delete pwsmRemake;

				for (auto ii : tempOneModsOneIsNterminus1)
					if (ii.second != nullptr)
						delete ii.second;

				for (auto ii : tempOneModsOneIsNterminus2)
					if (ii.second != nullptr)
						delete ii.second;
			}
		}
		//confirm there were 85 peptides generated by the semi
		Assert::AreEqual(85, (int)fiveCleavageProductsSemiTrypsin.size());

		//The rest of the tests are less intense
		//check semi when methionine is cleaved
		DigestionParams *semiCleaveDigestionParams = new DigestionParams(semiTrypsinForTestNonAndSemiSpecificDigests->getName(),
                                                                                 3, 2, INT_MAX, 1024,
                                                                                 InitiatorMethionineBehavior::Cleave, 2,
                                                                                 CleavageSpecificity::Full,
                                                                                 FragmentationTerminus::Both);
		initTempsForModificationPtr.push_back(std::vector<Proteomics::Modification*>());
		initTempsForModificationPtr.push_back(std::vector<Proteomics::Modification*>());
		std::vector<PeptideWithSetModifications*> fiveCleavageProductsSemiTrypsinCleave = fiveCleavages->Digest(
                    semiCleaveDigestionParams,
                    initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 0],
                    initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 1]);
		counterFor_initTempsForModificationPtr += 2;

		/*
		   int numVariableWithMet = fiveCleavageProductsSemiTrypsin.Where([&] (std::any x)
		   {
		return x::BaseSequence[0] == 'M';
		})->Count(); //how many had methionine in the variable digestion?*/

		int numVariableWithMet = 0;

		for (auto i : fiveCleavageProductsSemiTrypsin)
			if (i->getBaseSequence()[0] == 'M')
				numVariableWithMet++;

                //there should be the same number of sequences as before, minus the amount of methionine peptides
		Assert::AreEqual(fiveCleavageProductsSemiTrypsin.size(), fiveCleavageProductsSemiTrypsinCleave.size() + numVariableWithMet); 

		//check semi when methionine is retained
		DigestionParams *semiRetainDigestionParams = new DigestionParams(semiTrypsinForTestNonAndSemiSpecificDigests->getName(),
                                                                                 3, 2, INT_MAX, 1024,
                                                                                 InitiatorMethionineBehavior::Retain, 2,
                                                                                 CleavageSpecificity::Full,
                                                                                 FragmentationTerminus::Both);

		initTempsForModificationPtr.push_back(std::vector<Proteomics::Modification*>());
		initTempsForModificationPtr.push_back(std::vector<Proteomics::Modification*>());
		std::vector<PeptideWithSetModifications*> fiveCleavageProductsSemiTrypsinRetain = fiveCleavages->Digest(
                    semiRetainDigestionParams,
                    initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 0],
                    initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 1]);
		counterFor_initTempsForModificationPtr += 2;

		/*
		   int numNotRetained = fiveCleavageProductsSemiTrypsin.Where([&] (std::any x)
		   {
                   return i->getBaseSequence()[0] == 'A' && i->getBaseSequence()[1] == 'A' && 
                   (i->getBaseSequence()[i->getBaseSequence().size() - 1] != 'K' && 
                   !(i->getBaseSequence()[i->getBaseSequence().size() - 1] == 'G' && 
                   i->getBaseSequence()[i->getBaseSequence().size() - 2] == 'G'));
                   })->Count();
                */
                
		int numNotRetained = 0;
		for (auto i : fiveCleavageProductsSemiTrypsin) {
			if (i->getBaseSequence()[0] == 'A' && i->getBaseSequence()[1] == 'A' &&
                            (i->getBaseSequence()[i->getBaseSequence().size() - 1] != 'K'    &&
                             !(i->getBaseSequence()[i->getBaseSequence().size() - 1] == 'G'  &&
                               i->getBaseSequence()[i->getBaseSequence().size() - 2] == 'G'))) 
				numNotRetained++;
		}

                //there should be the same number of sequences as before, minus the amount of cleaved peptides
		Assert::AreEqual(fiveCleavageProductsSemiTrypsinRetain.size() + numNotRetained, fiveCleavageProductsSemiTrypsin.size());

		//Check the speedy semi-specific search (the previous ones were the slow classic)
		//Fixed N
		DigestionParams *modernSemiDigestionParamsN = new DigestionParams(trypsinForTestNonAndSemiSpecificDigests->getName(),
                                                                                  3, 2, INT_MAX, 1024,
                                                                                  InitiatorMethionineBehavior::Variable, 2,
                                                                                  CleavageSpecificity::Semi, FragmentationTerminus::N);
		initTempsForModificationPtr.push_back(std::vector<Modification*>());
		initTempsForModificationPtr.push_back(std::vector<Modification*>());
		std::vector<PeptideWithSetModifications*> fiveCleavageProductsModernSemiTrypsinN = fiveCleavages->Digest(
                    modernSemiDigestionParamsN,
                    initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 0],
                    initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 1]);
		counterFor_initTempsForModificationPtr += 2;
		Assert::AreEqual(7, (int)fiveCleavageProductsModernSemiTrypsinN.size());

		//Fixed C
		DigestionParams *modernSemiDigestionParamsC = new DigestionParams(trypsinForTestNonAndSemiSpecificDigests->getName(),
                                                                                  3, 2, INT_MAX, 1024,
                                                                                  InitiatorMethionineBehavior::Variable, 2,
                                                                                  CleavageSpecificity::Semi, FragmentationTerminus::C);
		initTempsForModificationPtr.push_back(std::vector<Modification*>());
		initTempsForModificationPtr.push_back(std::vector<Modification*>());
		std::vector<PeptideWithSetModifications*> fiveCleavageProductsModernSemiTrypsinC = fiveCleavages->Digest(
                    modernSemiDigestionParamsC,
                    initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 0],
                    initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 1]);
		counterFor_initTempsForModificationPtr += 2;
		Assert::AreEqual(6, (int)fiveCleavageProductsModernSemiTrypsinC.size());

		//test the maxPeptideLength for both singleN and SingleC (variable methionine)
		//Single N max peptide length
		auto modernNonSpecificN = new DigestionParams("singleN", 4, 2, 4, 1024, InitiatorMethionineBehavior::Variable, 2,
                                                              CleavageSpecificity::None, FragmentationTerminus::N);

		initTempsForModificationPtr.push_back(std::vector<Modification*>());
		initTempsForModificationPtr.push_back(std::vector<Modification*>());
		std::vector<PeptideWithSetModifications*> fiveCleavageProductsModernNonSpecificN = fiveCleavages->Digest(
                    modernNonSpecificN,
                    initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 0],
                    initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 1]);
		counterFor_initTempsForModificationPtr += 2;
		Assert::AreEqual(17, (int)fiveCleavageProductsModernNonSpecificN.size());

		for (auto pep : fiveCleavageProductsModernNonSpecificN)
		{
                    Assert::IsTrue((int)pep->getBaseSequence().size() <= 4 && (int)pep->getBaseSequence().size() >= 2);
		}
		//Single C max peptide length
		auto modernNonSpecificC = new DigestionParams("singleC", 4, 2, 4, 1024,
                                                              InitiatorMethionineBehavior::Variable, 2,
                                                              CleavageSpecificity::None, FragmentationTerminus::C);

		initTempsForModificationPtr.push_back(std::vector<Modification*>());
		initTempsForModificationPtr.push_back(std::vector<Modification*>());
		std::vector<PeptideWithSetModifications*> fiveCleavageProductsModernNonSpecificC = fiveCleavages->Digest(
                    modernNonSpecificC,
                    initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 0],
                    initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 1]);
		counterFor_initTempsForModificationPtr += 2;

		Assert::AreEqual(17, (int)fiveCleavageProductsModernNonSpecificC.size());

		for (auto pep : fiveCleavageProductsModernNonSpecificC)
		{
                    Assert::IsTrue((int)pep->getBaseSequence().size() <= 4 && (int)pep->getBaseSequence().size() >= 2);
		}

		//test speedy nonspecific with variable methionine
		TestSingleProteases(fiveCleavages, InitiatorMethionineBehavior::Variable, FragmentationTerminus::N, 17);
		TestSingleProteases(fiveCleavages, InitiatorMethionineBehavior::Variable, FragmentationTerminus::C, 17);

		//test speedy nonspecific with cleaved methionine
		TestSingleProteases(fiveCleavages, InitiatorMethionineBehavior::Cleave, FragmentationTerminus::N, 16);
		TestSingleProteases(fiveCleavages, InitiatorMethionineBehavior::Cleave, FragmentationTerminus::C, 16);

		//test speedy nonspecific with retained methionine
		TestSingleProteases(fiveCleavages, InitiatorMethionineBehavior::Retain, FragmentationTerminus::N, 17);
		TestSingleProteases(fiveCleavages, InitiatorMethionineBehavior::Retain, FragmentationTerminus::C, 17);


		for (auto i : initTempsForModificationPtr)
			for (auto j : i)
				if (j != nullptr)
					delete j;

		//for (auto i : fiveCleavageProductsTrypsin)
		//	if (i != nullptr)
		//		delete i;

		for (auto i : fiveCleavageProductsSemiTrypsin)
			if (i != nullptr)
				delete i;

		for (auto i : fiveCleavageProductsSemiTrypsinCleave)
			if (i != nullptr)
				delete i;

		for (auto i : fiveCleavageProductsSemiTrypsinRetain)
			if (i != nullptr)
				delete i;

		for (auto i : fiveCleavageProductsModernSemiTrypsinN)
			if (i != nullptr)
				delete i;

		for (auto i : fiveCleavageProductsModernSemiTrypsinC)
			if (i != nullptr)
				delete i;

		for (auto i : fiveCleavageProductsModernNonSpecificN)
			if (i != nullptr)
				delete i;

		for (auto i : fiveCleavageProductsModernNonSpecificC)
			if (i != nullptr)
				delete i;

		delete fiveCleavages;
		delete trypsinForTestNonAndSemiSpecificDigests;
		delete fullyDigestParams;
		delete semiTrypsinForTestNonAndSemiSpecificDigests;
		delete semiDigestionParams;
		delete semiCleaveDigestionParams;
		delete semiRetainDigestionParams;
		delete modernSemiDigestionParamsN;
		delete modernSemiDigestionParamsC;
		delete modernNonSpecificN;
		delete modernNonSpecificC;
	}

	void TestPeptideWithSetMods::TestSingleProteases(Protein *protein, InitiatorMethionineBehavior initiatorMethionineBehavior, FragmentationTerminus fragmentationTerminus, int numSequencesExpected)
	{
		std::string protease = FragmentationTerminus::N == fragmentationTerminus ? "singleN" : "singleC";
		DigestionParams *digestionParams = new DigestionParams(protease, 50, 2, INT_MAX, 1024, initiatorMethionineBehavior, 2, CleavageSpecificity::None, fragmentationTerminus);

		std::vector<Proteomics::Modification*> temp1, temp2;
		auto products = protein->Digest(digestionParams, temp1, temp2);
		Assert::AreEqual(numSequencesExpected, (int)products.size());

		if (digestionParams != nullptr)
			delete digestionParams;

	}

	void TestPeptideWithSetMods::TestHardToParseModifiedSequence()
	{
		std::string fullSequence = "PE[Metal:Cation:Fe[III] on X]PTIDE";

		ModificationMotif *motif;
		ModificationMotif::TryGetMotif("X", &motif);

		Modification *mod = new Modification("Cation:Fe[III]", "", "Metal", "", motif, "Anywhere.");

		std::unordered_map<std::string, Modification*> mods =
		{
			{"Cation:Fe[III] on X", mod}
		};

		PeptideWithSetModifications *pep = new PeptideWithSetModifications(fullSequence, mods);

		Assert::IsTrue(pep->getAllModsOneIsNterminus().size() == 1);
		std::unordered_map<int, Proteomics::Modification*> annotatedMod = pep->getAllModsOneIsNterminus();
		std::vector<int> keys;
		keys.reserve(annotatedMod.size());
		std::vector<Proteomics::Modification*> values;
		values.reserve(annotatedMod.size());
		for (auto i : annotatedMod) {
			keys.push_back(i.first);
			values.push_back(i.second);
		}

		for (int i = 0; i < keys.size(); i++) {
			Assert::IsTrue(keys[i] == 3);
		}

		for (int i = 0; i < values.size(); i++) {
			Assert::IsTrue(values[i]->getIdWithMotif() == "Cation:Fe[III] on X");
			Assert::IsTrue(values[i]->getOriginalId() == "Cation:Fe[III]");
			Assert::IsTrue(values[i]->getModificationType() == "Metal");
		}


		fullSequence = "[Metal:Cation:Fe[III] on X]PE[Metal:Cation:Fe[III] on X]PTIDE[Metal:Cation:Fe[III] on X]";
		delete pep;
		pep = new PeptideWithSetModifications(fullSequence, mods);
		Assert::IsTrue(pep->getAllModsOneIsNterminus().size() == 3);	
		//line replaced with below line Assert::IsTrue(pep->getAllModsOneIsNterminus().Keys->ToList()->SequenceEqual(std::vector<int> {1, 3, 8}));
		Assert::SequenceEqual(keys ,std::vector<int> {1, 3, 8});

		delete pep;
                delete motif;

		for (auto i : values) 
			if (i != nullptr)
				delete i;

	}

	void TestPeptideWithSetMods::TestCTermAndLastSideChainModParsing()
	{
		std::string fullSequence = "PEPTIDE[Mod:MyMod on E][PeptideCTermMod:MyCTermMod on E]";

		ModificationMotif *motif;
		ModificationMotif::TryGetMotif("E", &motif);

		Modification *mod = new Modification("MyMod", "", "Mod", "", motif, "Anywhere.");

		Modification *cTermMod = new Modification("MyCTermMod", "", "PeptideCTermMod", "", motif, "Peptide C-terminal.");

		std::unordered_map<std::string, Modification*> mods =
		{
			{"MyMod on E", mod},
			{"MyCTermMod on E", cTermMod}
		};

		PeptideWithSetModifications *pep = new PeptideWithSetModifications(fullSequence, mods);

		Assert::IsTrue( pep->getAllModsOneIsNterminus().size() == 2);

		std::unordered_map<int, Proteomics::Modification*> map = pep->getAllModsOneIsNterminus();
		std::vector<int> keys;
		keys.reserve(map.size());
		std::vector<Proteomics::Modification*> val;
		val.reserve(map.size());

		for(auto i : map) {
			keys.push_back(i.first);
			val.push_back(i.second);
		}

		Assert::SequenceEqual(keys, std::vector<int> {8, 9});

		delete pep;
                delete motif;

		for (auto i : val)
			if (i != nullptr)
				delete i;
	}
}
