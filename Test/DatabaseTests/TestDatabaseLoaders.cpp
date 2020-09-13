#include "TestDatabaseLoaders.h"
#include "../../Proteomics/Modifications/Modification.h"
#include "../../UsefulProteomicsDatabases/PtmListLoader.h"
#include "../../UsefulProteomicsDatabases/DecoyType.h"
#include "../../UsefulProteomicsDatabases/ProteinDbLoader.h"
#include "../../UsefulProteomicsDatabases/Loaders.h"
#include "../../Chemistry/PeriodicTable.h"
#include "../../Proteomics/Modifications/ModificationMotif.h"
#include "../../Proteomics/Protein/Protein.h"
#include "../../MzLibUtil/MzLibException.h"
#include "../../Proteomics/Protein/DatabaseReference.h"
#include "../../Proteomics/Protein/DisulfideBond.h"
#include "../../Proteomics/Protein/SequenceVariation.h"
#include "../../UsefulProteomicsDatabases/ProteinDbWriter.h"
#include "../../MassSpectrometry/Enums/DissociationType.h"

using namespace Chemistry;
using namespace MassSpectrometry;
using namespace MzLibUtil;
using namespace Proteomics;
using namespace UsefulProteomicsDatabases;


#include "MzLibAssert.h"
#include <experimental/filesystem>
#include <fstream>
#include <iostream>

int main ( int argc, char **argv )
{
	int i=0;
	std::cout << i << ". PeriodicTableLoader" << std::endl;
	const std::string elfile="elements.dat";
	const std::string &elr=elfile;
	UsefulProteomicsDatabases::PeriodicTableLoader::Load (elr);
	
	std::cout << ++i << ". LoadModWithNl" << std::endl;
	Test::TestDatabaseLoaders::LoadModWithNl();

	std::cout << ++i << ". LoadOriginalMismatchedModifications" << std::endl;
	Test::TestDatabaseLoaders::LoadOriginalMismatchedModifications();

	std::cout << ++i << ". TestUpdateUnimod" << std::endl;
	Test::TestDatabaseLoaders::TestUpdateUnimod();

	std::cout << ++i << ". TestUpdatePsiMod" << std::endl;
	Test::TestDatabaseLoaders::TestUpdatePsiMod();

	std::cout << ++i << ". TestUpdateElements" << std::endl;
	Test::TestDatabaseLoaders::TestUpdateElements();
	
	std::cout << ++i << ". TestUpdateUniprot" << std::endl;
	Test::TestDatabaseLoaders::TestUpdateUniprot();

	std::cout << ++i << ". FilesEqualHash" << std::endl;
	Test::TestDatabaseLoaders::FilesEqualHash();
/*
	std::cout << ++i << ". FilesLoading" << std::endl;
	Test::TestDatabaseLoaders::FilesLoading();
*/
	std::cout << ++i << ". SampleLoadModWithLongMotif" << std::endl;
	Test::TestDatabaseLoaders::SampleLoadModWithLongMotif();

	std::cout << ++i << ". SampleModFileLoading" << std::endl;
	Test::TestDatabaseLoaders::SampleModFileLoading();

	std::cout << ++i << ". SampleModFileLoadingFail1" << std::endl;
	Test::TestDatabaseLoaders::SampleModFileLoadingFail1();

	std::cout << ++i << ". SampleModFileLoadingFail2" << std::endl;
	Test::TestDatabaseLoaders::SampleModFileLoadingFail2();
#ifdef LATER
	std::cout << ++i << ". SampleModFileLoadingFail3" << std::endl;
	Test::TestDatabaseLoaders::SampleModFileLoadingFail3();

	std::cout << ++i << ". SampleModFileLoadingFail4" << std::endl;
	Test::TestDatabaseLoaders::SampleModFileLoadingFail4();
#endif
	std::cout << ++i << ". SampleModFileLoadingFail5" << std::endl;
	Test::TestDatabaseLoaders::SampleModFileLoadingFail5();

	std::cout << ++i << ". SampleModFileLoadingFail6" << std::endl;
	Test::TestDatabaseLoaders::SampleModFileLoadingFail6();

	std::cout << ++i << ". CompactFormReading" << std::endl;
	Test::TestDatabaseLoaders::CompactFormReading();

	std::cout << ++i << ". CompactFormReading2" << std::endl;
	Test::TestDatabaseLoaders::CompactFormReading2();
	
	std::cout << ++i << ". Test_MetaMorpheusStyleProteinDatabaseWriteAndREad" << std::endl;
	Test::TestDatabaseLoaders::Test_MetaMorpheusStyleProteinDatabaseWriteAndREad();

	std::cout << ++i << ". DoNotWriteSameModTwiceAndDoNotWriteInHeaderSinceDifferent" << std::endl;
	Test::TestDatabaseLoaders::DoNotWriteSameModTwiceAndDoNotWriteInHeaderSinceDifferent();

	std::cout << ++i << ". TestWritePtmWithNeutralLoss" << std::endl;
	Test::TestDatabaseLoaders::TestWritePtmWithNeutralLoss();

	std::cout << ++i << ". TestWritePtmWithDiagnosticIons" << std::endl;
	Test::TestDatabaseLoaders::TestWritePtmWithDiagnosticIons();
	
	std::cout << ++i << ". TestWritePtmWithNeutralLossAndDiagnosticIons" << std::endl;
	Test::TestDatabaseLoaders::TestWritePtmWithNeutralLossAndDiagnosticIons();
	
	std::cout << ++i << ". Modification_read_write_into_proteinDb" << std::endl;
	Test::TestDatabaseLoaders::Modification_read_write_into_proteinDb();

	return 0;
}

namespace Test
{
	void TestDatabaseLoaders::LoadModWithNl()
	{
		std::string testdir = std::experimental::filesystem::current_path().string();
		std::vector<std::tuple<Modification*, std::string>> errors;
		Modification* hah = dynamic_cast<Modification*>(PtmListLoader::ReadModsFromFile(testdir + "/cfInNL.txt", errors).front());

#ifdef ORIG
		int count = 0;
		for (auto item : hah->getNeutralLosses())
		{
			for (auto loos : std::get<1>(item))
			{
				count++;
			}
		}

		Assert::AreEqual(2, count);
#endif

		Assert::AreEqual(2, hah->getNeutralLosses().begin()->second.size());
	}

	void TestDatabaseLoaders::LoadOriginalMismatchedModifications()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		std::unordered_map<std::string, Modification*> unknownModifications;
		std::vector<Modification*> tempMods;
		std::vector<std::string> tempStringVector;
		std::vector<Protein*> protein = ProteinDbLoader::LoadProteinXML(testdir + "/oblm.xml", 
				true, 
				DecoyType::Reverse,
				tempMods, 
				false,
				tempStringVector,
				unknownModifications);
		Assert::AreEqual(0, (int)protein[0]->getOneBasedPossibleLocalizedModifications().size());
		auto variant = protein[0]->GetVariantProteins()[0];
		protein[0]->getNonVariantProtein()->RestoreUnfilteredModifications();
		Assert::AreEqual(1, (int)protein[0]->getNonVariantProtein()->getOneBasedPossibleLocalizedModifications().size());

		for (auto i : tempMods)
			delete i;

		for (auto i : protein)
			delete i;
	}

	void TestDatabaseLoaders::TestUpdateUnimod()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		auto unimodLocation = testdir + "/unimod_tables.xml";
		Loaders::UpdateUnimod(unimodLocation);
		Loaders::UpdateUnimod(unimodLocation);
	}

	void TestDatabaseLoaders::TestUpdatePsiMod()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		auto psimodLocation = testdir + "/lal.xml";
		Loaders::UpdatePsiMod(psimodLocation);
		Loaders::UpdatePsiMod(psimodLocation);
	}

	void TestDatabaseLoaders::TestUpdateElements()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		auto elementLocation = testdir + "/lal.dat";
		Loaders::UpdateElements(elementLocation);
		Loaders::UpdateElements(elementLocation);
		Assert::IsTrue(PeriodicTable::ValidateAbundances(1e-15));
		Assert::IsTrue(PeriodicTable::ValidateAverageMasses(1e-2));
	}

	void TestDatabaseLoaders::TestUpdateUniprot()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		auto uniprotLocation = testdir + "/ptmlist.txt";
		Loaders::UpdateUniprot(uniprotLocation);
		Loaders::UpdateUniprot(uniprotLocation);
	}

	void TestDatabaseLoaders::FilesEqualHash()
	{
#ifdef ORIG		
		std::string testdir=std::experimental::filesystem::current_path().string();
		auto fake = testdir + "/fake.txt";
		StreamWriter file = StreamWriter(fake);
		file.WriteLine("fake");

		Loaders::UpdateUniprot(fake);
		fake = testdir + "/fake1.txt";
		StreamWriter file2 = StreamWriter(fake);
		file2.WriteLine("fake");

		Loaders::UpdateUnimod(fake);
		fake = testdir + "/fake2.txt";

		StreamWriter file3 = StreamWriter(fake);
		file3.WriteLine("fake");

		Loaders::UpdatePsiMod(fake);
		fake = testdir + "/fake3.txt";
		StreamWriter file = StreamWriter(fake);
		file.WriteLine("fake");
		Loaders::UpdateElements(fake);
#endif
		std::string testdir = std::experimental::filesystem::current_path().string();
		std::string fake = testdir + "fake.txt";

		std::ofstream file(fake);
		file << "fake\n";
		Loaders::UpdateUniprot(fake);
		fake = testdir + "/fake1.txt";

		std::ofstream file2(fake);
		file2 << "fake\n";
		Loaders::UpdateUnimod(fake);
		fake = testdir + "/fake2.txt";

		std::ofstream file3(fake);
		file3 << "fake\n";
		Loaders::UpdateUnimod(fake);
		fake = testdir + "/fake3.txt";

		std::ofstream file4(fake);
		file4 << "fake\n";
		Loaders::UpdateElements(fake);

		file.close();
		file2.close();
		file3.close();
		file4.close();
	}

	void TestDatabaseLoaders::FilesLoading()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		Loaders::LoadElements(testdir + "/elements.dat");

		auto unimodMods = Loaders::LoadUnimod(testdir + "/unimod_tables.xml");//.ToList();
		// UniMod PTM list may be updated at some point, causing the unit test to fail
		Assert::AreEqual(2677, (int)unimodMods.size()); 

#ifdef ORIG
		std::vector<Modification*> myList = unimodMods.Where([&] (std::any m)
				{
				m::OriginalId->Equals("HexNAc(2)");
				}).ToList();
#endif

		std::vector<Modification*> myList;
		for ( auto m: unimodMods ) {
			if ( m->getOriginalId() == "HexNAc(2)" ) {
				myList.push_back(m);
			}
		}

		Modification *testMod = myList.front();
		int neutralLossCount = 0;
		if (testMod->getNeutralLosses().size() != 0)
		{
			for (auto item : testMod->getNeutralLosses())
			{
				for (auto loss : std::get<1>(item))
				{
					neutralLossCount++;
				}
			}
		}

		Assert::AreEqual(2, neutralLossCount);

		auto psiModDeserialized = Loaders::LoadPsiMod(testdir + "/PSI-MOD.obo.xml");

#ifdef ORIG
		// N6,N6,N6-trimethyllysine
		auto trimethylLysine = psiModDeserialized->getItems().OfType<UsefulProteomicsDatabases::Generated::oboTerm*>().First([&] (std::any b)
				{
				b::id->Equals("MOD:00083");
				});
		Assert::AreEqual("1+", trimethylLysine->xref_analog.First([&] (std::any b)
					{
					b::dbname->Equals("FormalCharge");
					}).name);
#endif
		for ( auto  b : psiModDeserialized->term() ){
			if ( b.id().get() == "MOD:00083" ) {
				for ( auto c: b.xref_analog() ) {
					if ( c.dbname().get() == "FormalCharge" ) {
						std::string s = "1+";
						std::string s2 = c.name().get();
						Assert::AreEqual (s, s2 );
						break;
					}
				}
				break;
			}
		}

#ifdef ORIG
		// Phosphoserine
		Assert::IsFalse(psiModDeserialized->getItems().OfType<UsefulProteomicsDatabases::Generated::oboTerm*>().First([&] (std::any b)
					{
					b::id->Equals("MOD:00046");
					}).xref_analog.Any([&] (std::any b)
						{
						b::dbname->Equals("FormalCharge");
						}));

#endif        
		for ( auto  b : psiModDeserialized->term() ){
			if ( b.id().get() == "MOD:00046" ) {
				bool found = false;
				for ( auto c: b.xref_analog() ) {
					if ( c.dbname().get() == "FormalCharge" ) {
						found = true;
						break;
					}
				}
				Assert::IsFalse(found);
				break;
			}
		}


		std::unordered_map<std::string, int> formalChargesDictionary = Loaders::GetFormalChargesDictionary(psiModDeserialized);

		auto uniprotPtms = Loaders::LoadUniprot(testdir + "/ptmlist.txt", formalChargesDictionary);//.ToList();
		// UniProt PTM list may be updated at some point, causing the unit test to fail
		Assert::AreEqual(346, (int)uniprotPtms.size()); 

		std::ofstream w;
		w.open(testdir + "/test.txt");
		for (auto nice : uniprotPtms)
		{
			w << nice->ToString() << std::endl;
			w << "//" << std::endl;
		}
		for (auto nice : unimodMods)
		{
			w << nice->ToString() << std::endl;
			w << "//" << std::endl;
		}
		w.close();

		std::vector<std::tuple<Modification*, std::string>> errors;
		auto sampleModList = PtmListLoader::ReadModsFromFile(testdir + "/test.txt", errors);

		Assert::AreEqual(3023, (int)sampleModList.size());

		std::vector<Modification*> myOtherList;
		for (auto mod : sampleModList)
		{
			if (mod->getIdWithMotif() != "" && mod->getIdWithMotif().find("Acetyl") != std::string::npos)
			{
				myOtherList.push_back(mod);
			}
		}

		auto thisMod = myOtherList.front();
		Assert::IsTrue(thisMod->getMonoisotopicMass().value() > 42);
		Assert::IsTrue(thisMod->getMonoisotopicMass().value() < 43);
		std::experimental::filesystem::remove("test.txt");
	}

	void TestDatabaseLoaders::SampleLoadModWithLongMotif()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		ModificationMotif *motif;
		ModificationMotif::TryGetMotif("msgRgk", &motif);
		Modification *testMod = new Modification("Asymmetric dimethylarginine", 
				"", 
				"Test", 
				"", 
				motif, 
				"Anywhere.", 
				nullptr, 
				std::optional<double>(100.0));

		std::vector<Modification*> allKnownMods = {testMod};

		Assert::IsTrue(testMod->getValidModification());

		Assert::AreEqual(testMod->getTarget()->ToString(), "msgRgk");

		std::unordered_map<std::string, Modification*> unknownModifications;
		std::vector<std::string> modTypesToExclude;

		std::vector<Protein*> protein = ProteinDbLoader::LoadProteinXML(testdir + "/modified_start.xml",
				true,
				DecoyType::None,
				allKnownMods,
				false,
				modTypesToExclude,
				unknownModifications,
				1,
				1,
				1);

		bool startsWith = true;
		std::string baseSequence = protein[0]->getBaseSequence();
		std::string startsWithStr = "MSGRGK";
		for (int i = 0; i < 6; i++) {	
			if (baseSequence[i] != startsWithStr[i])
				startsWith = false;
		}

		Assert::IsTrue(startsWith);
		Assert::AreEqual(protein[0]->getOneBasedPossibleLocalizedModifications().size(), 1);
		Assert::AreEqual(protein[0]->getOneBasedPossibleLocalizedModifications().begin()->second[0], testMod);

		delete motif;

		for (auto i : allKnownMods)
			delete i;

		for (auto i : protein)
			delete i;

	}

	void TestDatabaseLoaders::SampleModFileLoading()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		std::vector<std::tuple<Modification*, std::string>> errors;
		PtmListLoader::ReadModsFromFile(testdir + "/sampleModFile.txt", errors);
	}

	void TestDatabaseLoaders::SampleModFileLoadingFail1()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		std::vector<std::tuple<Modification*, std::string>> errors;
		auto b = PtmListLoader::ReadModsFromFile(testdir + "/sampleModFileFail1.txt", errors);
		Assert::AreEqual(0,b.size());
	}

	void TestDatabaseLoaders::SampleModFileLoadingFail2()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		std::vector<std::tuple<Modification*, std::string>> errors;
		auto b = PtmListLoader::ReadModsFromFile(testdir + "/sampleModFileFail2.txt", errors);

		Assert::AreEqual(0, b.size());
	}

#ifdef LATER
	void TestDatabaseLoaders::SampleModFileLoadingFail3()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
#ifdef ORIG
		Assert::That([&] ()
				{
				std::vector<std::tuple<Modification*, std::string>> errors;
				PtmListLoader::ReadModsFromFile(testdir + "/sampleModFileFail2.txt", errors).ToList();
				}, Throws::TypeOf<MzLibException*>().With::Property("Message").EqualTo("Input string for chemical formula was in an incorrect format: $%&$%"));
#endif
			
	}

	void TestDatabaseLoaders::SampleModFileLoadingFail4()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
#ifdef ORIG
		Assert::That([&] ()
				{
				std::vector<std::tuple<Modification*, std::string>> errors;
				PtmListLoader::ReadModsFromFile(testdir + "/sampleModFileFail2.txt", errors).ToList();
				}, Throws::TypeOf<MzLibException*>().With::Property("Message").EqualTo("0 or 238.229666 is not a valid monoisotopic mass"));
#endif
	}
#endif
	void TestDatabaseLoaders::SampleModFileLoadingFail5()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		std::vector<std::tuple<Modification*, std::string>> errors;
		auto b = PtmListLoader::ReadModsFromFile(testdir + "/sampleModFileFail2.txt", errors);
		Assert::AreEqual(0, b.size());
	}

	void TestDatabaseLoaders::SampleModFileLoadingFail6()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		std::vector<std::tuple<Modification*, std::string>> errors;
		auto b = PtmListLoader::ReadModsFromFile(testdir + "/sampleModFileFail2.txt", errors);
		Assert::AreEqual(0, b.size());
	}

	void TestDatabaseLoaders::CompactFormReading()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		std::vector<std::tuple<Modification*, std::string>> errors;
		Assert::AreEqual(2, PtmListLoader::ReadModsFromFile(testdir + "/sampleModFileDouble.txt", errors).size());
	}

	void TestDatabaseLoaders::CompactFormReading2()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		std::vector<std::tuple<Modification*, std::string>> errors;
		Assert::AreEqual(2, PtmListLoader::ReadModsFromFile(testdir + "/sampleModFileDouble2.txt", errors).size());
	}

	void TestDatabaseLoaders::Modification_read_write_into_proteinDb()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		Loaders::LoadElements(testdir + "/elements.dat");
		std::vector<std::tuple<Modification*, std::string>> errors;
		std::vector<Modification*> sampleModList = PtmListLoader::ReadModsFromFile(testdir + "/z.txt", errors);
#ifdef ORIG
		Assert::AreEqual(1, sampleModList.OfType<Modification*>()->Count());
#endif
		std::unordered_map<int, std::vector<Modification*>> tempMapIntVectorMods;
		tempMapIntVectorMods.insert(std::pair<int, std::vector<Modification*>>(2, sampleModList));
		Assert::AreEqual(1, sampleModList.size());
		Protein *protein = new Protein("MCSSSSSSSSSS", 
				"accession", 
				"organism", 
				std::vector<std::tuple<std::string, std::string>>(), 
				tempMapIntVectorMods,
				std::vector<ProteolysisProduct*>(), 
				"name", 
				"full_name");
#ifdef ORIG
		Assert::AreEqual(1, protein->getOneBasedPossibleLocalizedModifications()[2].OfType<Modification*>()->Count());
#endif
		Assert::AreEqual(1, protein->getOneBasedPossibleLocalizedModifications().at(2).size());

		std::vector<Protein*> tempProteinVector;
		tempProteinVector.push_back(protein);
		std::unordered_map<std::string, UsefulProteomicsDatabases::ModDbTuple_set> tempWriteXMlDatabase;
		ProteinDbWriter::WriteXmlDatabase(tempWriteXMlDatabase, 
				tempProteinVector, 
				testdir + "/test_modifications_with_proteins.xml");

		std::unordered_map<std::string, Modification*> um;
		std::vector<Modification*> tempModificationVector;
		std::vector<std::string> tempStringVector;
		std::vector<Protein*> new_proteins = ProteinDbLoader::LoadProteinXML(testdir + "/test_modifications_with_proteins.xml", 
				true, 
				DecoyType::None, 
				tempModificationVector, 
				false, 
				tempStringVector, 
				um);

		Assert::AreEqual(1, new_proteins.size());
		Assert::AreEqual(1, new_proteins[0]->getOneBasedPossibleLocalizedModifications().size());
#ifdef ORIG
		Assert::AreEqual(1, new_proteins[0]->getOneBasedPossibleLocalizedModifications().SelectMany([&] (std::any kv)
					{
					kv->Value;
					})->Count());
		Assert::AreEqual("Type", new_proteins[0]->getOneBasedPossibleLocalizedModifications().SelectMany([&] (std::any kv)
					{
					kv->Value;
					}).OfType<Modification*>().First().ModificationType);
		Assert::AreEqual("Palmitoylation on C", new_proteins[0]->getOneBasedPossibleLocalizedModifications()[2][0].getIdWithMotif());
		Assert::AreEqual(1, new_proteins[0]->getOneBasedPossibleLocalizedModifications()[2].OfType<Modification*>()->Count());
#endif
		std::vector<Modification*> countModificationsVector;
		for (auto kv : new_proteins[0]->getOneBasedPossibleLocalizedModifications())
			for (auto i : kv.second)
				countModificationsVector.push_back(i);
		
		Assert::AreEqual(1, countModificationsVector.size());
		Assert::AreEqual("Type", countModificationsVector[0]->getModificationType());
		Assert::AreEqual("Palmitoylation on C", new_proteins[0]->getOneBasedPossibleLocalizedModifications().at(2)[0]->getIdWithMotif());
		Assert::AreEqual(1, new_proteins[0]->getOneBasedPossibleLocalizedModifications().at(2).size());

		// Check that Modifications were saved after last load
		Assert::AreEqual(1, ProteinDbLoader::GetPtmListFromProteinXml(testdir + "/test_modifications_with_proteins.xml").size());
#ifdef ORIG
		Assert::True(ProteinDbLoader::GetPtmListFromProteinXml(testdir + R"(test_modifications_with_proteins.xml)"))[0] == new_proteins[0]->getOneBasedPossibleLocalizedModifications().SelectMany([&] (std::any kv)
				{
				kv->Value;
				}).First());
#endif
		Assert::IsTrue(ProteinDbLoader::GetPtmListFromProteinXml(testdir + "/test_modifications_with_proteins.xml")[0]->Equals(new_proteins[0]->getOneBasedPossibleLocalizedModifications().begin()->second[0]));

		//But that we can still read modifications from other protein XMLs that exist
		Assert::AreEqual(0, ProteinDbLoader::GetPtmListFromProteinXml(testdir + "/xml.xml").size());

		// Check that Modifications were saved after last load
		auto b = ProteinDbLoader::GetPtmListFromProteinXml(testdir + "/test_modifications_with_proteins.xml");
		Assert::AreEqual(1, b.size());

		auto c = ProteinDbLoader::GetPtmListFromProteinXml(testdir + "/test_modifications_with_proteins.xml")[0];
#ifdef ORIG
		auto d = new_proteins[0]->getOneBasedPossibleLocalizedModifications().SelectMany([&] (std::any kv)
				{
				kv->Value;
				}).First();
#endif
		countModificationsVector.clear();

		for (auto kv : new_proteins[0]->getOneBasedPossibleLocalizedModifications())
			for (auto i : kv.second)
				countModificationsVector.push_back(i);

#ifdef ORIG
		Assert::IsTrue(c == countModificationsVector);
#endif
		Assert::IsTrue(c[0].Equals(countModificationsVector[0]));

		//But that we can still read modifications from other protein XMLs that exist
		Assert::AreEqual(0, ProteinDbLoader::GetPtmListFromProteinXml(testdir + "/xml.xml").size());

		delete protein;
	}

	void TestDatabaseLoaders::Test_MetaMorpheusStyleProteinDatabaseWriteAndREad()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		std::string proteinDbFilePath = testdir + "/TestProteinSplitAcrossFiles.xml";

		ModificationMotif *motif;
		ModificationMotif::TryGetMotif("D", &motif);
		Modification *mod = new Modification("mod1", 
				"", 
				"mt", 
				"", 
				motif, 
				"Anywhere.", 
				nullptr, 
				std::make_optional(10), 
				std::unordered_map<std::string, std::vector<std::string>>(), 
				std::unordered_map<std::string, std::vector<std::string>>(), 
				std::vector<std::string>(), 
				std::unordered_map<DissociationType, std::vector<double>>(), 
				std::unordered_map<DissociationType, std::vector<double>>(), 
				"");

		std::unordered_map<int, std::vector<Modification*>> oneBasedModification;
		std::vector<Modification*> tempModificationVector;
		tempModificationVector.push_back(mod);
		oneBasedModification.insert(std::pair<int, std::vector<Modification*>>(3,tempModificationVector));

		Protein *prot1 = new Protein("MEDEEK", 
				"prot1", 
				"", 
				std::vector<std::tuple<std::string, std::string>>(), 
				oneBasedModification, 
				std::vector<ProteolysisProduct*>(), 
				"", 
				"", 
				false, 
				false, 
				std::vector<DatabaseReference*>(), 
				std::vector<SequenceVariation*>(), 
				std::vector<SequenceVariation*>(), 
				"", 
				std::vector<DisulfideBond*>(), 
				std::vector<SpliceSite*>(), 
				"");

		std::vector<Protein*> proteinList;
		proteinList.push_back(prot1);
		std::unordered_map<std::string, UsefulProteomicsDatabases::ModDbTuple_set> tempWriteXMlDatabase;
		ProteinDbWriter::WriteXmlDatabase(tempWriteXMlDatabase, proteinList, proteinDbFilePath);
#ifdef ORIG
		// SHANE: Potential oversite
		auto lines = File::ReadAllLines(proteinDbFilePath);
#endif
		std::unordered_map<std::string, Modification*> um;
		std::vector<Modification*> tempModificationVector2;
		std::vector<std::string> tempStringVector;
		std::vector<Protein*> newProteinList = ProteinDbLoader::LoadProteinXML(proteinDbFilePath, 
				true, 
				DecoyType::Reverse, 
				tempModificationVector2, 
				false,
				tempStringVector,
				um,
				-1);

		delete prot1;
		delete mod;
	}

	void TestDatabaseLoaders::DoNotWriteSameModTwiceAndDoNotWriteInHeaderSinceDifferent()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		Loaders::LoadElements(testdir + "/elements.dat");
		std::vector<std::tuple<Modification*, std::string>> errors;
		std::vector<Modification*> sampleModList = PtmListLoader::ReadModsFromFile(testdir + "/z.txt", errors);
		std::unordered_map<int, std::vector<Modification*>> tempMapIntVectorMods;
		tempMapIntVectorMods.insert(std::pair<int, std::vector<Modification*>>(2, sampleModList));
		Protein *protein = new Protein("MCSSSSSSSSSS", 
				"accession", 
				"organism", 
				std::vector<std::tuple<std::string, std::string>>(), 
				tempMapIntVectorMods,
				std::vector<ProteolysisProduct*>(),
				"name", 
				"full_name", 
				false, 
				false);
#ifdef ORIG
		Assert::AreEqual(1, protein->getOneBasedPossibleLocalizedModifications()[2].OfType<Modification*>()->Count());
#endif
		Assert::AreEqual(1, protein->getOneBasedPossibleLocalizedModifications()[2].size());

		std::unordered_map<std::string, UsefulProteomicsDatabases::ModDbTuple_set> dictWithThisMod;

		UsefulProteomicsDatabases::ModDbTuple_set value;

		auto modReadFromFile = sampleModList[0];
		ModificationMotif *motif;
		ModificationMotif::TryGetMotif("C", &motif);
		Modification *newMod = new Modification("Palmitoylation of C", 
				"", 
				"Type", 
				"MOD_RES", 
				motif, 
				"Anywhere.", 
				modReadFromFile->getChemicalFormula(), 
				modReadFromFile->getMonoisotopicMass(), 
				std::unordered_map<std::string, std::vector<std::string>>(), 
				std::unordered_map<std::string, std::vector<std::string>>(), 
				std::vector<std::string>(), 
				std::unordered_map<DissociationType, std::vector<double>>(), 
				std::unordered_map<DissociationType, std::vector<double>>(), 
				"E:\\GitClones\\mzLib\\Test\\bin\\x64\\Debug\\DatabaseTests\\z.txt");

		Assert::IsTrue(newMod->Equals(sampleModList.front()));

		// Assert::AreEqual(newMod, sampleModList.front());
		// Assert::AreEqual(sampleModList.front(), newMod);

		value.insert(std::pair<int, Modification*>(2, newMod));

		dictWithThisMod.emplace("accession", value);
		std::vector<Protein*> tempProteinVector;
		tempProteinVector.push_back(protein);
		auto newModResEntries = ProteinDbWriter::WriteXmlDatabase(dictWithThisMod, tempProteinVector, testdir + "/test_modifications_with_proteins3.xml");
		Assert::AreEqual(0, newModResEntries.size());
		std::unordered_map<std::string, Modification*> um;
		std::vector<Modification*> tempModificationVector;
		std::vector<std::string> tempStringVector;
		std::vector<Protein*> new_proteins = ProteinDbLoader::LoadProteinXML(testdir + "/test_modifications_with_proteins3.xml", 
				true, 
				DecoyType::None, 
				tempModificationVector, 
				false, 
				tempStringVector, 
				um);

		Assert::AreEqual(1, new_proteins.size());
		Assert::AreEqual(1, new_proteins[0]->getOneBasedPossibleLocalizedModifications().size());
#ifdef ORIG
		Assert::AreEqual(1, new_proteins[0]->getOneBasedPossibleLocalizedModifications().SelectMany([&] (std::any kv)
					{
					kv->Value;
					})->Count());
#endif
		std::vector<std::vector<Modification*>> vals;
		for (auto kv : new_proteins[0]->getOneBasedPossibleLocalizedModifications()) {
			vals.push_back(kv.second);
		}

		Assert::AreEqual(1, vals.size());

		delete newMod;
		delete protein;
	}

	void TestDatabaseLoaders::TestWritePtmWithNeutralLoss()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		std::string filename = "test_neutral_loss_mod.xml";
		std::unordered_map<int, std::vector<Modification*>> mods;

		ModificationMotif *motif;
		ModificationMotif::TryGetMotif("T", &motif);
		std::unordered_map<DissociationType, std::vector<double>> tempMapDisVectorDouble1;
		tempMapDisVectorDouble1.insert(std::pair<DissociationType, std::vector<double>> (DissociationType::HCD, {80.0, 0}));
		tempMapDisVectorDouble1.insert(std::pair<DissociationType, std::vector<double>> (DissociationType::ETD, {70.0, 0}));
		Modification *m = new Modification("Phospho", 
				"", 
				"Test", 
				"", 
				motif, 
				"Anywhere.", 
				nullptr, 
				std::make_optional(80.0), 
				std::unordered_map<std::string, std::vector<std::string>>(), 
				std::unordered_map<std::string, std::vector<std::string>>(), 
				std::vector<std::string>(),
				tempMapDisVectorDouble1,
				std::unordered_map<DissociationType, std::vector<double>>(), 
				"");
#ifdef ORIG
		Assert::That(m->getValidModification());
#endif
		Assert::IsTrue(m->getValidModification());

		mods.emplace(4, std::vector<Modification*> {m});

		Protein *protein = new Protein("PEPTIDE", 
				"accession", 
				"", 
				std::vector<std::tuple<std::string, std::string>>(), 
				mods, 
				std::vector<ProteolysisProduct*>(), 
				"", 
				"", 
				false, 
				false, 
				std::vector<DatabaseReference*>(), 
				std::vector<SequenceVariation*>(), 
				std::vector<SequenceVariation*>(), 
				"", 
				std::vector<DisulfideBond*>(), 
				std::vector<SpliceSite*>(), 
				"");
#ifdef ORIG
		Assert::That(protein->getOneBasedPossibleLocalizedModifications().size() == 1);
		Assert::That(protein->getOneBasedPossibleLocalizedModifications().First()->Value->First().NeutralLosses.First()->Value->Count == 2);
#endif
		Assert::AreEqual(protein->getOneBasedPossibleLocalizedModifications().begin()->second[0]->getNeutralLosses().begin()->second.size(), 2);

		std::vector<Protein*> tempProteinVector;
		tempProteinVector.push_back(protein);
		std::unordered_map<std::string, UsefulProteomicsDatabases::ModDbTuple_set> tempWriteXMlDatabase;
		ProteinDbWriter::WriteXmlDatabase(tempWriteXMlDatabase, tempProteinVector, testdir + "/" + filename);

		// with passed-in mods
		std::unordered_map<std::string, Modification*> um;
		std::vector<Modification*> tempModificationVector;
		tempModificationVector.push_back(m);
		std::vector<std::string> tempStringVector;
		std::vector<Protein*> new_proteins = ProteinDbLoader::LoadProteinXML(testdir + "/" + filename, 
				true, 
				DecoyType::None, tempModificationVector, 
				false, 
				tempStringVector, 
				um);
#ifdef ORIG
		Assert::That(new_proteins.front().OneBasedPossibleLocalizedModifications::First()->Value->First().NeutralLosses.First()->Value->Count == 2);
#endif
		Assert::AreEqual(new_proteins[0]->getOneBasedPossibleLocalizedModifications().begin()->second[0]->getNeutralLosses().begin()->second.size(), 2);
// should be able to read mod from top of database...
		std::vector<Modification*> tempModificationVector2;
		tempStringVector.clear();
		new_proteins = ProteinDbLoader::LoadProteinXML(testdir + "/" + filename, 
				true, 
				DecoyType::None, 
				tempModificationVector2, 
				false, 
				tempStringVector, 
				um);
#ifdef ORIG
		Assert::That(new_proteins.front().OneBasedPossibleLocalizedModifications::First()->Value->First().NeutralLosses.First()->Value->Count == 2);
#endif
		Assert::AreEqual(new_proteins[0]->getOneBasedPossibleLocalizedModifications().begin()->second[0]->getNeutralLosses().begin()->second.size(), 2);

		delete protein;
		delete m;
	}

	void TestDatabaseLoaders::TestWritePtmWithDiagnosticIons()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		std::string filename = "test_diagnostic_ion_mod.xml";
		std::unordered_map<int, std::vector<Modification*>> mods;

		ModificationMotif *motif;
		ModificationMotif::TryGetMotif("T", &motif);

		std::unordered_map<DissociationType, std::vector<double>> tempMapDisVectorDouble1;
		tempMapDisVectorDouble1.insert(std::pair<DissociationType, std::vector<double>>(DissociationType::HCD, std::vector<double> {80.0, 0}));
		tempMapDisVectorDouble1.insert(std::pair<DissociationType, std::vector<double>>(DissociationType::ETD, std::vector<double> {70.0, 0}));

		Modification *m = new Modification("Phospho", 
				"", 
				"Test", 
				"", 
				motif, 
				"Anywhere.", 
				nullptr, 
				std::make_optional(80.0), 
				std::unordered_map<std::string, std::vector<std::string>>(), 
				std::unordered_map<std::string, std::vector<std::string>>(), 
				std::vector<std::string>(), 
				std::unordered_map<DissociationType, std::vector<double>>(),
				tempMapDisVectorDouble1,
				"");
#ifdef ORIG
		Assert::That(m->getValidModification());
#endif
		Assert::IsTrue(m->getValidModification());

		mods.emplace(4, std::vector<Modification*> {m});

		Protein *protein = new Protein("PEPTIDE", 
				"accession", 
				"", 
				std::vector<std::tuple<std::string, std::string>>(), 
				mods, 
				std::vector<ProteolysisProduct*>(), 
				"", 
				"", 
				false, 
				false, 
				std::vector<DatabaseReference*>(), 
				std::vector<SequenceVariation*>(), 
				std::vector<SequenceVariation*>(), 
				"", 
				std::vector<DisulfideBond*>(), 
				std::vector<SpliceSite*>(), 
				"");
#ifdef ORIG
		Assert::That(protein->getOneBasedPossibleLocalizedModifications().size() == 1);
		Assert::That(protein->getOneBasedPossibleLocalizedModifications().First()->Value->First().DiagnosticIons.First()->Value->Count == 2);
#endif
		Assert::AreEqual(protein->getOneBasedPossibleLocalizedModifications().size(), 1);
		Assert::AreEqual(protein->getOneBasedPossibleLocalizedModifications().begin()->second[0]->getDiagnosticIons().begin()->second.size(), 2);

		std::unordered_map<std::string, UsefulProteomicsDatabases::ModDbTuple_set> tempWriteXMlDatabase;
		std::vector<Protein*> tempProteinVector;
		tempProteinVector.push_back(protein);
		ProteinDbWriter::WriteXmlDatabase(tempWriteXMlDatabase, tempProteinVector, testdir + "/" + filename);

		// with passed-in mods
		std::unordered_map<std::string, Modification*> um;
		std::vector<Modification*> tempModificationVector;
		tempModificationVector.push_back(m);
		std::vector<std::string> tempStringVector;
		std::vector<Protein*> new_proteins = ProteinDbLoader::LoadProteinXML(testdir + "/" + filename,
				true, 
				DecoyType::None, 
				tempModificationVector, 
				false, 
				tempStringVector, 
				um);
#ifdef ORIG
		Assert::That(new_proteins.front().OneBasedPossibleLocalizedModifications::First()->Value->First().DiagnosticIons.First()->Value->Count == 2);
#endif
		Assert::AreEqual(new_proteins[0]->getOneBasedPossibleLocalizedModifications().begin()->second[0]->getDiagnosticIons().begin()->second.size(), 2);

		// should be able to read mod from top of database...
		std::vector<Modification*> tempModificationVector2;
		tempStringVector.clear();
		new_proteins = ProteinDbLoader::LoadProteinXML(testdir + "/" + filename, 
				true, 
				DecoyType::None, 
				tempModificationVector2, 
				false, 
				tempStringVector, 
				um);
#ifdef ORIG
		Assert::That(new_proteins.front().OneBasedPossibleLocalizedModifications::First()->Value->First().DiagnosticIons.First()->Value->Count == 2);
#endif
		Assert::AreEqual(new_proteins[0]->getOneBasedPossibleLocalizedModifications().begin()->second[0]->getDiagnosticIons().begin()->second.size(), 2);

		delete protein;
		delete m;
	}

	void TestDatabaseLoaders::TestWritePtmWithNeutralLossAndDiagnosticIons()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		std::string filename = "test_neutral_loss_diagnostic_ion_mod.xml";
		std::unordered_map<int, std::vector<Modification*>> mods;

		ModificationMotif *motif;
		ModificationMotif::TryGetMotif("T", &motif);

		std::unordered_map<DissociationType, std::vector<double>> tempMapDisVectorDouble1, tempMapDisVectorDouble2;
		tempMapDisVectorDouble1.insert(std::pair<DissociationType, std::vector<double>> (DissociationType::HCD, {80.0, 0.0}));
		tempMapDisVectorDouble1.insert(std::pair<DissociationType, std::vector<double>> (DissociationType::ETD, {70.0, 0.0}));
		tempMapDisVectorDouble2.insert(std::pair<DissociationType, std::vector<double>> (DissociationType::CID, {60.0, 0.0}));
		tempMapDisVectorDouble2.insert(std::pair<DissociationType, std::vector<double>> (DissociationType::EThcD, {40.0, 0.0}));
#ifdef ORIG
		Modification *m = new Modification("Phospho", "", "Test", "", *motif, "Anywhere.", nullptr, std::make_optional(80.0), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>
				{
				{
				DissociationType::HCD, {80.0, 0}
				},
				{
				DissociationType::ETD, {70.0, 0}
				}
				},
				std::unordered_map<DissociationType, std::vector<double>>
				{
				{
				DissociationType::CID, {60.0, 0}
				},
				{
				DissociationType::EThcD, {40.0, 0}
				}
				},
				"");
		Assert::That(m->getValidModification());
#endif

		Modification *m = new Modification(std::string("Phospho"), 
				std::string(""), 
				std::string("Test"), 
				std::string(""), 
				motif, 
				std::string("Anywhere."), 
				nullptr, 
				std::make_optional(80.0), 
				std::unordered_map<std::string, std::vector<std::string>>(), 
				std::unordered_map<std::string, std::vector<std::string>>(), 
				std::vector<std::string>(), 
				tempMapDisVectorDouble1,
				tempMapDisVectorDouble2,
				std::string(""));
		
		Assert::IsTrue(m->getValidModification());

		mods.emplace(4, std::vector<Modification*> {m});

		Protein *protein = new Protein("PEPTIDE", 
				"accession", 
				"", 
				std::vector<std::tuple<std::string, std::string>>(), 
				mods, 
				std::vector<ProteolysisProduct*>(), 
				"", 
				"", 
				false, 
				false, 
				std::vector<DatabaseReference*>(), 
				std::vector<SequenceVariation*>(), 
				std::vector<SequenceVariation*>(), 
				"", 
				std::vector<DisulfideBond*>(), 
				std::vector<SpliceSite*>(), 
				"");

#ifdef ORIG
		Assert::That(protein->getOneBasedPossibleLocalizedModifications().size() == 1);
		Assert::That(protein->getOneBasedPossibleLocalizedModifications().First()->Value->First().NeutralLosses.First()->Value->Count == 2);
#endif
		Assert::AreEqual(protein->getOneBasedPossibleLocalizedModifications().size(), 1);
		Assert::AreEqual(protein->getOneBasedPossibleLocalizedModifications().begin()->second[0]->getNeutralLosses().begin()->second.size(), 2);

		std::unordered_map<std::string, UsefulProteomicsDatabases::ModDbTuple_set> tempWriteXMlDatabase;
		std::vector<Protein*> tempVectorOfProteins;
		tempVectorOfProteins.push_back(protein);
		ProteinDbWriter::WriteXmlDatabase(tempWriteXMlDatabase, tempVectorOfProteins, testdir + "/" + filename);

		// with passed-in mods
		std::unordered_map<std::string, Modification*> um;
		std::vector<Modification*> tempVectorOfMods;
		tempVectorOfMods.push_back(m);
		std::vector<std::string> tempStringVector;
		std::vector<Protein*> new_proteins = ProteinDbLoader::LoadProteinXML(testdir + "/" + filename, true,
				DecoyType::None, tempVectorOfMods, false,
				tempStringVector, um);
#ifdef ORIG
		Assert::That(new_proteins.front().OneBasedPossibleLocalizedModifications::First()->Value->First().NeutralLosses.First()->Value->Count == 2);
		Assert::That(new_proteins.front().OneBasedPossibleLocalizedModifications::First()->Value->First().DiagnosticIons.First()->Value->Count == 2);
#endif


		Assert::AreEqual(new_proteins[0]->getOneBasedPossibleLocalizedModifications().begin()->second[0]->getNeutralLosses().begin()->second.size(), 2);
		Assert::AreEqual(new_proteins[0]->getOneBasedPossibleLocalizedModifications().begin()->second[0]->getDiagnosticIons().begin()->second.size(), 2);
		// should be able to read mod from top of database...

		for (auto i : new_proteins)
			delete i;
		tempStringVector.clear();

		std::vector<Modification*> tempVectorOfMods2;
		new_proteins = ProteinDbLoader::LoadProteinXML(testdir + "/" + filename, true, DecoyType::None, tempVectorOfMods2, false, tempStringVector, um);
#ifdef ORIG
		Assert::That(new_proteins.front().OneBasedPossibleLocalizedModifications::First()->Value->First().NeutralLosses.First()->Value->Count == 2);
		Assert::That(new_proteins.front().OneBasedPossibleLocalizedModifications::First()->Value->First().DiagnosticIons.First()->Value->Count == 2);
#endif
		Assert::AreEqual(new_proteins[0]->getOneBasedPossibleLocalizedModifications().begin()->second[0]->getNeutralLosses().begin()->second.size(), 2);
		Assert::AreEqual(new_proteins[0]->getOneBasedPossibleLocalizedModifications().begin()->second[0]->getDiagnosticIons().begin()->second.size(), 2);

		for (auto i : new_proteins)
			delete i;
		delete protein;
		delete m;
	}
}
