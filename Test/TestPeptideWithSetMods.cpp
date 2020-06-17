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

	std::cout << ++i << ". TestPeptideWithSetMods::TestDifferentProteaseEquals\n";
	Test::TestPeptideWithSetMods::TestDifferentProteaseEquals();

	// Two commented out functions fail when trying to make a PeptideWithSetModifications object
//	std::cout << ++i << ". TestPeptideWithSetMods::TestCTermAndLastSideChainModParsing" << std::endl;
//	Test::TestPeptideWithSetMods::TestCTermAndLastSideChainModParsing();

	std::cout << ++i << ". TestPeptideWithSetMods::TestSemiFewCleavages\n";
	Test::TestPeptideWithSetMods::TestSemiFewCleavages();

//	std::cout << ++i << ". TestPeptideWithSetMods::TestHardToParseModifiedSequence" << std::endl;
//	Test::TestPeptideWithSetMods::TestHardToParseModifiedSequence();

	std::cout << ++i << ". TestPeptideWithSetMods::TestSingleProteases\n";
	Test::TestPeptideWithSetMods::TestSemiFewCleavages();

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

		for (auto i : temp)
			for (auto j : i)
				if (j != nullptr)
					delete j;
	}

	void TestPeptideWithSetMods::TestSemiFewCleavages()
	{
		Protein *protein = new Protein("MQLLRCFSIFSVIASVLAQELTTICEQIPSPTLESTPYSLSTTTILANGKAMQGVFEYYKSVTFVSNCGSHPSTTSKGSPINTQYVF", "P32781");
		DigestionParams *nParams = new DigestionParams("trypsin", 2, 7, 50, 1024, InitiatorMethionineBehavior::Variable, 2, CleavageSpecificity::Semi, FragmentationTerminus::N);
		DigestionParams *cParams = new DigestionParams("trypsin", 2, 7, 50, 1024, InitiatorMethionineBehavior::Variable, 2, CleavageSpecificity::Semi, FragmentationTerminus::C);


		//Unit test is not crashing
		std::vector<std::vector<Modification*>> temp;

		for (int i = 0; i < 8; i++) {
			std::vector<Modification*> tempt;
			temp.push_back(tempt);
		}

		std::vector<PeptideWithSetModifications*> vectorToTransfer = protein->Digest(nParams, temp[0], temp[1]);
		std::list<PeptideWithSetModifications*> list(vectorToTransfer.begin(), vectorToTransfer.end());

		for (auto i : vectorToTransfer)
			if (i != nullptr)
				delete i;
		vectorToTransfer = protein->Digest(cParams, temp[0], temp[1]);
		list = std::list<PeptideWithSetModifications*>(vectorToTransfer.begin(), vectorToTransfer.end());	


		Protein *protein2 = new Protein("MQFSTVASVAFVALANFVAAESAAAISQITDGQIQATTTATTEATTTAAPSSTVETVSPSSTETISQQTENGAAKAAVGMGAGALAAAAMLL", "P43497");

		for (auto i : vectorToTransfer)
			if (i != nullptr)
				delete i;
		vectorToTransfer = protein2->Digest(nParams, temp[4], temp[5]);
		list = std::list<PeptideWithSetModifications*>(vectorToTransfer.begin(), vectorToTransfer.end());

		for (auto i : vectorToTransfer)
			if (i != nullptr)
				delete i;
		vectorToTransfer = protein2->Digest(cParams, temp[6], temp[7]);
		list = std::list<PeptideWithSetModifications*>(vectorToTransfer.begin(), vectorToTransfer.end());	




		delete protein2;
		delete protein;
		delete cParams;
		delete nParams;

		for (auto i : temp)
			for (auto j : i)
				if (j != nullptr)
					delete j;

		for (auto i : vectorToTransfer)
			if (i != nullptr)
				delete i;
	}

#ifdef LATER
	void TestPeptideWithSetMods::TestNonAndSemiSpecificDigests()
	{
		std::vector<std::vector<Modification*>> initTempsForModificationPtr;
		unsigned short counterFor_initTempsForModificationPtr = 0;

		Protein *fiveCleavages = new Protein("MAAKCCKDDKEEKFFKGG", "fiveCleavages"); //protein with 5 K's
		std::vector<std::tuple<std::string, FragmentationTerminus>> trypticSequencesInducingClevage = {std::tuple<std::string, FragmentationTerminus>("K",FragmentationTerminus::C)};
		std::vector<std::tuple<std::string, FragmentationTerminus>> trypticSequencesPreventingClevage;

		//make two identical proteases, but one is fully specific and one is semi specific

		auto motifList = DigestionMotif::ParseDigestionMotifsFromString("K|");
		Protease *trypsinForTestNonAndSemiSpecificDigests = new Protease("trypsinForTestNonAndSemiSpecificDigests", CleavageSpecificity::Full, "asdf", "asdf", motifList);
		Protease *semiTrypsinForTestNonAndSemiSpecificDigests = new Protease("semitrypsinForTestNonAndSemiSpecificDigests", CleavageSpecificity::Semi, "asdf", "asdf", motifList);

		//add these made up proteases to the dictionary
		ProteaseDictionary::getDictionary().emplace(trypsinForTestNonAndSemiSpecificDigests->getName(), trypsinForTestNonAndSemiSpecificDigests);
		ProteaseDictionary::getDictionary().emplace(semiTrypsinForTestNonAndSemiSpecificDigests->getName(), semiTrypsinForTestNonAndSemiSpecificDigests);

		//Digest with the full
		DigestionParams *fullyDigestParams = new DigestionParams(trypsinForTestNonAndSemiSpecificDigests->getName(), 3, 2);
		initTempsForModificationPtr.push_back(std::vector<Modification*>());
		initTempsForModificationPtr.push_back(std::vector<Modification*>());
		std::vector<PeptideWithSetModifications*> fiveCleavageProductsTrypsin = fiveCleavages->Digest(fullyDigestParams, initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 0], initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 1]);
		counterFor_initTempsForModificationPtr += 2;
		Assert::AreEqual(22, fiveCleavageProductsTrypsin.size());

		//digests with the semi (variable methionine)
		DigestionParams *semiDigestionParams = new DigestionParams(semiTrypsinForTestNonAndSemiSpecificDigests->getName(), 3, 2);
		initTempsForModificationPtr.push_back(std::vector<Modification*>());
		initTempsForModificationPtr.push_back(std::vector<Modification*>());
		std::vector<PeptideWithSetModifications*> fiveCleavageProductsSemiTrypsinVector = fiveCleavages->Digest(semiDigestionParams, initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 0], initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 1]);
		std::list<PeptideWithSetModifications*> fiveCleavageProductsSemiTrypsin(fiveCleavageProductsSemiTrypsinVector.begin(), fiveCleavageProductsSemiTrypsinVector.end());
		counterFor_initTempsForModificationPtr += 2;

		//This is a partial list of the full peptides. From this, we can GENERATE every possible semi that we would expect to see
		std::vector<std::string> expectedProductsSemiFiveCleavages = {"MAAKCCKDDKEEK", "AAKCCKDDKEEK", "CCKDDKEEKFFK", "DDKEEKFFKGG", "EEKFFKGG", "FFKGG", "AAK", "AAKCCK", "AAKCCKDDK"};

#ifdef LATER
		//Check that, when we digested with semi, we made all possible semi sequences, labeled full and semi correctly, and have no duplicates
		for (auto s : expectedProductsSemiFiveCleavages) //foreach precursor peptide
		{
			for (int i = 0; i < s.length() - semiDigestionParams->getMinPeptideLength(); i++) //cleave it to be semi
			{
				std::string sToFind = s.substr(i); //get a peptide from this precursor (fixed C)
				/*
				auto peps = fiveCleavageProductsSemiTrypsin.Where([&] (std::any x)
						{
						x::BaseSequence->Equals(sToFind);
						})->ToArray(); //find the peptide in the digested list
						*/
				std::vector<FlashLFQ::Identification> peps;

				for (int i = 0; i < fiveCleavageProductsTrypsin.size(); i++) {
					
				}
				
				Assert::IsTrue(peps.size() == 1); //There should be exactly one! More than that means there are duplicates, fewer means we didn't generate it!
				auto pep = peps[0]; //get that single peptide
				//if it's a full sequence (cleaved at both indexes (including termini))
				if ((pep.BaseSequence[0] == pep.BaseSequence[1] || pep.BaseSequence[0] == 'M') && (pep.BaseSequence[pep.BaseSequence->Length - 1] == 'K' || (pep.BaseSequence[pep.BaseSequence->Length - 1] == 'G' && pep.BaseSequence[pep.BaseSequence->Length - 2] == 'G')))
				{
					Assert::IsTrue(pep.CleavageSpecificityForFdrCategory == CleavageSpecificity::Full);
				}
				else
				{
					Assert::IsTrue(pep.CleavageSpecificityForFdrCategory == CleavageSpecificity::Semi);
				}
				//try to remake the pwsm with unknown specificity... was it assigned the correct specificity?
				PeptideWithSetModifications *pwsmRemake = new PeptideWithSetModifications(fiveCleavages, semiDigestionParams, pep.OneBasedStartResidueInProtein, pep.OneBasedEndResidueInProtein, CleavageSpecificity::Unknown, "", 3, pep.AllModsOneIsNterminus, 0);
				Assert::IsTrue(pwsmRemake->getCleavageSpecificityForFdrCategory() == pep.CleavageSpecificityForFdrCategory);

				//Repeat the above going from the other direction (fixed N)
				sToFind = s.substr(0, semiDigestionParams->getMinPeptideLength() + i); //get a peptide from this precursor (fixed N)
				peps = fiveCleavageProductsSemiTrypsin.Where([&] (std::any x)
						{
						x::BaseSequence->Equals(sToFind);
						})->ToArray(); //find the peptide in the digested list
				Assert::IsTrue(peps.size() == 1); //There should be exactly one! More than that means there are duplicates, fewer means we didn't generate it!
				pep = peps[0]; //get that single peptide
				//if it's a full sequence (cleaved at both indexes (including termini))
				if ((pep.BaseSequence[0] == pep.BaseSequence[1] || pep.BaseSequence[0] == 'M') && pep.BaseSequence::Last() == 'K')
				{
					Assert::IsTrue(pep.CleavageSpecificityForFdrCategory == CleavageSpecificity::Full);
				}
				else
				{
					Assert::IsTrue(pep.CleavageSpecificityForFdrCategory == CleavageSpecificity::Semi);
				}
				//try to remake the pwsm with unknown specificity... was it assigned the correct specificity?
				pwsmRemake = new PeptideWithSetModifications(fiveCleavages, semiDigestionParams, pep.OneBasedStartResidueInProtein, pep.OneBasedEndResidueInProtein, CleavageSpecificity::Unknown, "", 3, pep.AllModsOneIsNterminus, 0);
				Assert::IsTrue(pwsmRemake->getCleavageSpecificityForFdrCategory() == pep.CleavageSpecificityForFdrCategory);

				delete pwsmRemake;
			}
		}
#endif
		//confirm there were 85 peptides generated by the semi
		Assert::AreEqual(85, fiveCleavageProductsSemiTrypsin.size());

		//The rest of the tests are less intense
		//check semi when methionine is cleaved
		DigestionParams *semiCleaveDigestionParams = new DigestionParams(semiTrypsinForTestNonAndSemiSpecificDigests->getName(), 3, 2, INT_MAX, 1024, InitiatorMethionineBehavior::Cleave, 2, CleavageSpecificity::Full, FragmentationTerminus::Both);
		initTempsForModificationPtr.push_back(std::vector<Proteomics::Modification*>());
		initTempsForModificationPtr.push_back(std::vector<Proteomics::Modification*>());
		auto fiveCleavageProductsSemiTrypsinCleaveVector = std::vector<PeptideWithSetModifications*>(fiveCleavages->Digest(semiCleaveDigestionParams, initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 0], initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 1]));
		auto fiveCleavageProductsSemiTrypsinCleave = std::list<PeptideWithSetModifications*>(fiveCleavageProductsSemiTrypsinCleaveVector.begin(), fiveCleavageProductsSemiTrypsinCleaveVector.end());
		counterFor_initTempsForModificationPtr += 2;
#ifdef LATER
		int numVariableWithMet = fiveCleavageProductsSemiTrypsin.Where([&] (std::any x)
				{
				//C# TO C++ CONVERTER TODO TASK: A 'delete semiCleaveDigestionParams' statement was not added since semiCleaveDigestionParams was passed to a method or constructor. Handle memory management manually.
				//C# TO C++ CONVERTER TODO TASK: A 'delete semiDigestionParams' statement was not added since semiDigestionParams was passed to a method or constructor. Handle memory management manually.
				//C# TO C++ CONVERTER TODO TASK: A 'delete fullyDigestParams' statement was not added since fullyDigestParams was passed to a method or constructor. Handle memory management manually.
				//C# TO C++ CONVERTER TODO TASK: A 'delete semiTrypsinForTestNonAndSemiSpecificDigests' statement was not added since semiTrypsinForTestNonAndSemiSpecificDigests was passed to a method or constructor. Handle memory management manually.
				//C# TO C++ CONVERTER TODO TASK: A 'delete trypsinForTestNonAndSemiSpecificDigests' statement was not added since trypsinForTestNonAndSemiSpecificDigests was passed to a method or constructor. Handle memory management manually.
				//C# TO C++ CONVERTER TODO TASK: A 'delete fiveCleavages' statement was not added since fiveCleavages was passed to a method or constructor. Handle memory management manually.
				return x::BaseSequence[0] == 'M';
				})->Count(); //how many had methionine in the variable digestion?

		Assert::AreEqual(fiveCleavageProductsSemiTrypsin.size(), fiveCleavageProductsSemiTrypsinCleave.size() + numVariableWithMet); //there should be the same number of sequences as before, minus the amount of methionine peptides

#endif
		//check semi when methionine is retained
		DigestionParams *semiRetainDigestionParams = new DigestionParams(semiTrypsinForTestNonAndSemiSpecificDigests->getName(), 3, 2, INT_MAX, 1024, InitiatorMethionineBehavior::Retain, 2, CleavageSpecificity::Full, FragmentationTerminus::Both);

		initTempsForModificationPtr.push_back(std::vector<Proteomics::Modification*>());
		initTempsForModificationPtr.push_back(std::vector<Proteomics::Modification*>());
		auto fiveCleavageProductsSemiTrypsinRetainVector = fiveCleavages->Digest(semiRetainDigestionParams, initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 0], initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 1]);
		counterFor_initTempsForModificationPtr += 2;
		auto fiveCleavageProductsSemiTrypsinRetain = std::list<Modification*>(fiveCleavageProductsSemiTrypsinRetainVector.begin(), fiveCleavageProductsSemiTrypsinVector.end());
#ifdef LATER

		int numNotRetained = fiveCleavageProductsSemiTrypsin.Where([&] (std::any x)
				{
				//C# TO C++ CONVERTER TODO TASK: A 'delete semiRetainDigestionParams' statement was not added since semiRetainDigestionParams was passed to a method or constructor. Handle memory management manually.
				//C# TO C++ CONVERTER TODO TASK: A 'delete semiCleaveDigestionParams' statement was not added since semiCleaveDigestionParams was passed to a method or constructor. Handle memory management manually.
				//C# TO C++ CONVERTER TODO TASK: A 'delete semiDigestionParams' statement was not added since semiDigestionParams was passed to a method or constructor. Handle memory management manually.
				//C# TO C++ CONVERTER TODO TASK: A 'delete fullyDigestParams' statement was not added since fullyDigestParams was passed to a method or constructor. Handle memory management manually.
				//C# TO C++ CONVERTER TODO TASK: A 'delete semiTrypsinForTestNonAndSemiSpecificDigests' statement was not added since semiTrypsinForTestNonAndSemiSpecificDigests was passed to a method or constructor. Handle memory management manually.
				//C# TO C++ CONVERTER TODO TASK: A 'delete trypsinForTestNonAndSemiSpecificDigests' statement was not added since trypsinForTestNonAndSemiSpecificDigests was passed to a method or constructor. Handle memory management manually.
				//C# TO C++ CONVERTER TODO TASK: A 'delete fiveCleavages' statement was not added since fiveCleavages was passed to a method or constructor. Handle memory management manually.
				return x::BaseSequence[0] == 'A' && x::BaseSequence[1] == 'A' && (x::BaseSequence[x::BaseSequence->Length - 1] != 'K' && !(x::BaseSequence[x::BaseSequence->Length - 1] == 'G' && x::BaseSequence[x::BaseSequence->Length - 2] == 'G'));
				})->Count();
		Assert::AreEqual(fiveCleavageProductsSemiTrypsinRetain.size() + numNotRetained, fiveCleavageProductsSemiTrypsin.size()); //there should be the same number of sequences as before, minus the amount of cleaved peptides
#endif

		//Check the speedy semi-specific search (the previous ones were the slow classic)
		//Fixed N
		DigestionParams *modernSemiDigestionParamsN = new DigestionParams(trypsinForTestNonAndSemiSpecificDigests->getName(), 3, 2, INT_MAX, 1024, InitiatorMethionineBehavior::Variable, 2, CleavageSpecificity::Semi, FragmentationTerminus::N);
		initTempsForModificationPtr.push_back(std::vector<Modification*>());
		initTempsForModificationPtr.push_back(std::vector<Modification*>());
		auto fiveCleavageProductsModernSemiTrypsinNVector = fiveCleavages->Digest(modernSemiDigestionParamsN, initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 0], initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 1]);
		auto fiveCleavageProductsModernSemiTrypsinN = std::list<Modification*> (fiveCleavageProductsModernSemiTrypsinNVector.begin(), fiveCleavageProductsModernSemiTrypsinNVector.end());
		counterFor_initTempsForModificationPtr += 2;
		Assert::AreEqual(7, fiveCleavageProductsModernSemiTrypsinN.size());

		//Fixed C
		DigestionParams *modernSemiDigestionParamsC = new DigestionParams(trypsinForTestNonAndSemiSpecificDigests->getName(), 3, 2, INT_MAX, 1024, InitiatorMethionineBehavior::Variable, 2, CleavageSpecificity::Semi, FragmentationTerminus::C);
		initTempsForModificationPtr.push_back(std::vector<Modification*>());
		initTempsForModificationPtr.push_back(std::vector<Modification*>());
		auto fiveCleavageProductsModernSemiTrypsinCVector = fiveCleavages->Digest(modernSemiDigestionParamsC, initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 0], initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 1]);
		counterFor_initTempsForModificationPtr += 2;
		auto fiveCleavageProductsModernSemiTrypsinC = std::list<Modification*> (fiveCleavageProductsModernSemiTrypsinCVector.begin(), fiveCleavageProductsModernSemiTrypsinCVector.end());
		Assert::AreEqual(6, fiveCleavageProductsModernSemiTrypsinC.size());

		//test the maxPeptideLength for both singleN and SingleC (variable methionine)
		//Single N max peptide length
		auto modernNonSpecificN = new DigestionParams("singleN", 4, 2, 4, 1024, InitiatorMethionineBehavior::Variable, 2, CleavageSpecificity::None, FragmentationTerminus::N);

		initTempsForModificationPtr.push_back(std::vector<Modification*>());
		initTempsForModificationPtr.push_back(std::vector<Modification*>());
		auto fiveCleavageProductsModernNonSpecificNVector = fiveCleavages->Digest(modernNonSpecificN, initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 0], initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 1]);
		counterFor_initTempsForModificationPtr += 2;
		auto fiveCleavageProductsModernNonSpecificN = std::list<Modification*> (fiveCleavageProductsModernNonSpecificNVector.begin(), fiveCleavageProductsModernNonSpecificNVector.end());
		Assert::AreEqual(17, fiveCleavageProductsModernNonSpecificN.size());

#ifdef LATER
		for (auto pep : fiveCleavageProductsModernNonSpecificN)
		{
			Assert::IsTrue(pep.BaseSequence->Length <= 4 && pep.BaseSequence->Length >= 2);
		}
#endif
		//Single C max peptide length
		auto modernNonSpecificC = new DigestionParams("singleC", 4, 2, 4, 1024, InitiatorMethionineBehavior::Variable, 2, CleavageSpecificity::None, FragmentationTerminus::C);

		initTempsForModificationPtr.push_back(std::vector<Modification*>());
		initTempsForModificationPtr.push_back(std::vector<Modification*>());
		auto fiveCleavageProductsModernNonSpecificCVector = fiveCleavages->Digest(modernNonSpecificC, initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 0], initTempsForModificationPtr[counterFor_initTempsForModificationPtr + 1]);
		counterFor_initTempsForModificationPtr += 2;

		auto fiveCleavageProductsModernNonSpecificC = std::list(fiveCleavageProductsModernNonSpecificCVector.begin(), fiveCleavageProductsModernNonSpecificCVector.end());

		Assert::AreEqual(17, fiveCleavageProductsModernNonSpecificC.size());

#ifdef LATER
		for (auto pep : fiveCleavageProductsModernNonSpecificC)
		{
			Assert::IsTrue(pep.BaseSequence->Length <= 4 && pep.BaseSequence->Length >= 2);
		}
#endif

		//test speedy nonspecific with variable methionine
		TestSingleProteases(fiveCleavages, InitiatorMethionineBehavior::Variable, FragmentationTerminus::N, 17);
		TestSingleProteases(fiveCleavages, InitiatorMethionineBehavior::Variable, FragmentationTerminus::C, 17);

		//test speedy nonspecific with cleaved methionine
		TestSingleProteases(fiveCleavages, InitiatorMethionineBehavior::Cleave, FragmentationTerminus::N, 16);
		TestSingleProteases(fiveCleavages, InitiatorMethionineBehavior::Cleave, FragmentationTerminus::C, 16);

		//test speedy nonspecific with retained methionine
		TestSingleProteases(fiveCleavages, InitiatorMethionineBehavior::Retain, FragmentationTerminus::N, 17);
		TestSingleProteases(fiveCleavages, InitiatorMethionineBehavior::Retain, FragmentationTerminus::C, 17);

		//C# TO C++ CONVERTER TODO TASK: A 'delete modernNonSpecificC' statement was not added since modernNonSpecificC was passed to a method or constructor. Handle memory management manually.
		//C# TO C++ CONVERTER TODO TASK: A 'delete modernNonSpecificN' statement was not added since modernNonSpecificN was passed to a method or constructor. Handle memory management manually.
		//C# TO C++ CONVERTER TODO TASK: A 'delete modernSemiDigestionParamsC' statement was not added since modernSemiDigestionParamsC was passed to a method or constructor. Handle memory management manually.
		//C# TO C++ CONVERTER TODO TASK: A 'delete modernSemiDigestionParamsN' statement was not added since modernSemiDigestionParamsN was passed to a method or constructor. Handle memory management manually.
		//C# TO C++ CONVERTER TODO TASK: A 'delete semiRetainDigestionParams' statement was not added since semiRetainDigestionParams was passed to a method or constructor. Handle memory management manually.
		//C# TO C++ CONVERTER TODO TASK: A 'delete semiCleaveDigestionParams' statement was not added since semiCleaveDigestionParams was passed to a method or constructor. Handle memory management manually.
		//C# TO C++ CONVERTER TODO TASK: A 'delete semiDigestionParams' statement was not added since semiDigestionParams was passed to a method or constructor. Handle memory management manually.
		//C# TO C++ CONVERTER TODO TASK: A 'delete fullyDigestParams' statement was not added since fullyDigestParams was passed to a method or constructor. Handle memory management manually.
		//C# TO C++ CONVERTER TODO TASK: A 'delete semiTrypsinForTestNonAndSemiSpecificDigests' statement was not added since semiTrypsinForTestNonAndSemiSpecificDigests was passed to a method or constructor. Handle memory management manually.
		//C# TO C++ CONVERTER TODO TASK: A 'delete trypsinForTestNonAndSemiSpecificDigests' statement was not added since trypsinForTestNonAndSemiSpecificDigests was passed to a method or constructor. Handle memory management manually.
		//C# TO C++ CONVERTER TODO TASK: A 'delete fiveCleavages' statement was not added since fiveCleavages was passed to a method or constructor. Handle memory management manually.


		for (auto i : initTempsForModificationPtr)
			for (auto j : i)
				if (j != nullptr)
					delete j;
	}
#endif
	void TestPeptideWithSetMods::TestSingleProteases(Protein *protein, InitiatorMethionineBehavior initiatorMethionineBehavior, FragmentationTerminus fragmentationTerminus, int numSequencesExpected)
	{
		std::string protease = FragmentationTerminus::N == fragmentationTerminus ? "singleN" : "singleC";
		DigestionParams *digestionParams = new DigestionParams(protease, 50, 2, INT_MAX, 1024, initiatorMethionineBehavior, 2, CleavageSpecificity::None, fragmentationTerminus);

		std::vector<Proteomics::Modification*> temp1, temp2;
		auto products = protein->Digest(digestionParams, temp1, temp2);
		Assert::AreEqual(numSequencesExpected, products.size());

		if (digestionParams != nullptr)
			delete digestionParams;

		for (auto i : temp1)
			if (i != nullptr)
				delete i;

		for (auto i : temp2)
			if (i != nullptr)
				delete i;
	}

	void TestPeptideWithSetMods::TestHardToParseModifiedSequence()
	{
		std::string fullSequence = "PE[Metal:Cation:Fe[III] on X]PTIDE";

		ModificationMotif **motif;
		ModificationMotif::TryGetMotif("X", motif);

		Modification *mod = new Modification("Cation:Fe[III]", "", "Metal", "", *motif, "Anywhere.");

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
		delete mod;

		if (*motif != nullptr)
			delete *motif;

		for (auto i : values) 
			if (i != nullptr)
				delete i;

		for (auto i : annotatedMod) 
			if (i.second != nullptr)
				delete i.second;		

		for (auto i : mods)
			if (i.second != nullptr)
				delete i.second;
	}

	void TestPeptideWithSetMods::TestCTermAndLastSideChainModParsing()
	{
		std::string fullSequence = "PEPTIDE[Mod:MyMod on E][PeptideCTermMod:MyCTermMod on E]";

		ModificationMotif **motif;
		ModificationMotif::TryGetMotif("E", motif);

		Modification *mod = new Modification("MyMod", "", "Mod", "", &**motif, "Anywhere.");

		Modification *cTermMod = new Modification("MyCTermMod", "", "PeptideCTermMod", "", &**motif, "Peptide C-terminal.");

		std::unordered_map<std::string, Modification*> mods =
		{
			{"MyMod on E", mod},
			{"MyCTermMod on E", cTermMod}
		};

		PeptideWithSetModifications *pep = new PeptideWithSetModifications(fullSequence, mods);

		Assert::IsTrue(pep->getAllModsOneIsNterminus().size() == 2);

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
		delete cTermMod;
		delete mod;

		if (*motif != nullptr)
			delete *motif;

		for (auto i : mods)
			if (i.second != nullptr)
				delete i.second;

		for (auto i : val)
			if (i != nullptr)
				delete i;
	}
}
