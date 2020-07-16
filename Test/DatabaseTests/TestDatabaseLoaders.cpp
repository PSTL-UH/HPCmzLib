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


#include "Assert.h"
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

#ifdef LATER
	std::cout << ++i << ". TestUpdatePsiMod" << std::endl;
	Test::TestDatabaseLoaders::TestUpdatePsiMod();

	std::cout << ++i << ". TestUpdateElements" << std::endl;
	Test::TestDatabaseLoaders::TestUpdateElements();
#endif
	std::cout << ++i << ". TestUpdateUniprot" << std::endl;
	Test::TestDatabaseLoaders::TestUpdateUniprot();

	std::cout << ++i << ". FilesEqualHash" << std::endl;
	Test::TestDatabaseLoaders::FilesEqualHash();

#ifdef LATER
	std::cout << ++i << ". FilesLoading" << std::endl;
	Test::TestDatabaseLoaders::FilesLoading();

#endif
	std::cout << ++i << ". SampleLoadModWithLongMotif" << std::endl;
	Test::TestDatabaseLoaders::SampleLoadModWithLongMotif();

#ifdef LATER
	std::cout << ++i << ". SampleModFileLoading" << std::endl;
	Test::TestDatabaseLoaders::SampleModFileLoading();

	std::cout << ++i << ". SampleModFileLoadingFail1" << std::endl;
	Test::TestDatabaseLoaders::SampleModFileLoadingFail1();

	std::cout << ++i << ". SampleModFileLoadingFail2" << std::endl;
	Test::TestDatabaseLoaders::SampleModFileLoadingFail2();

	std::cout << ++i << ". SampleModFileLoadingFail3" << std::endl;
	Test::TestDatabaseLoaders::SampleModFileLoadingFail3();

	std::cout << ++i << ". SampleModFileLoadingFail4" << std::endl;
	Test::TestDatabaseLoaders::SampleModFileLoadingFail4();

	std::cout << ++i << ". SampleModFileLoadingFail5" << std::endl;
	Test::TestDatabaseLoaders::SampleModFileLoadingFail5();

	std::cout << ++i << ". SampleModFileLoadingFail6" << std::endl;
	Test::TestDatabaseLoaders::SampleModFileLoadingFail6();

	std::cout << ++i << ". CompactFormReading" << std::endl;
	Test::TestDatabaseLoaders::CompactFormReading();

	std::cout << ++i << ". CompactFormReading2" << std::endl;
	Test::TestDatabaseLoaders::CompactFormReading2();

	std::cout << ++i << ". Modification_read_write_into_proteinDb" << std::endl;
	Test::TestDatabaseLoaders::Modification_read_write_into_proteinDb();

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
#endif

	return 0;
}

namespace Test
{
	void TestDatabaseLoaders::LoadModWithNl()
	{
		std::string testdir = std::experimental::filesystem::current_path().string();
		std::vector<std::tuple<Modification*, std::string>> errors;
		auto hah = dynamic_cast<Modification*>(PtmListLoader::ReadModsFromFile(testdir + "/cfInNL.txt", errors).front());
		int count = 0;
		for (auto item : hah->getNeutralLosses())
		{
			for (auto loos : std::get<1>(item))
			{
				count++;
			}
		}

		Assert::AreEqual(2, count);
	}

	void TestDatabaseLoaders::LoadOriginalMismatchedModifications()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		std::unordered_map<std::string, Modification*> unknownModifications;
		std::vector<Modification*> tempMods;
		std::vector<std::string> tempStringVector;
		std::vector<Protein*> protein = ProteinDbLoader::LoadProteinXML(testdir + "/oblm.xml", true, DecoyType::Reverse,
				tempMods, false,
				tempStringVector,
				unknownModifications);
		Assert::AreEqual(0, (int)protein[0]->getOneBasedPossibleLocalizedModifications().size());
		auto variant = protein[0]->GetVariantProteins()[0];
		protein[0]->getNonVariantProtein()->RestoreUnfilteredModifications();
		Assert::AreEqual(1, (int)protein[0]->getNonVariantProtein()->getOneBasedPossibleLocalizedModifications().size());	
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

		Assert::IsTrue(testMod->getTarget()->ToString() == "msgRgk");

		std::unordered_map<std::string, Modification*> unknownModifications;
		std::vector<std::string> modTypesToExclude;

		Protein *protein = ProteinDbLoader::LoadProteinXML(testdir + "/modified_start.xml",
				true,
				DecoyType::None,
				allKnownMods,
				false,
				modTypesToExclude,
				unknownModifications,
				1,
				1,
				1)[0];

		bool startsWith = true;
		std::string baseSequence = protein->getBaseSequence();
		std::string startsWithStr = "MSGRGK";
		for (int i = 0; i < 6; i++) {	
			if (baseSequence[i] != startsWithStr[i])
				startsWith = false;
		}

		Assert::IsTrue(startsWith);
		Assert::IsTrue(protein->getOneBasedPossibleLocalizedModifications().size() == 1);
		Assert::IsTrue(protein->getOneBasedPossibleLocalizedModifications().begin()->second[0] == testMod);

		delete motif;
		delete protein;
		
		for (auto i : allKnownMods)
			delete i;

	}
	
	void TestDatabaseLoaders::SampleModFileLoading()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		std::vector<std::tuple<Modification*, std::string>> errors;
		PtmListLoader::ReadModsFromFile(testdir + "/DatabaseTests" + "/sampleModFile.txt", errors);
	}

	void TestDatabaseLoaders::SampleModFileLoadingFail1()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		std::vector<std::tuple<Modification*, std::string>> errors;
		auto b = PtmListLoader::ReadModsFromFile(testdir + "/DatabaseTests" + "/sampleModFileFail1.txt", errors);
		Assert::AreEqual(0, b.size());
	}

	void TestDatabaseLoaders::SampleModFileLoadingFail2()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		std::vector<std::tuple<Modification*, std::string>> errors;
		auto b = PtmListLoader::ReadModsFromFile(testdir + "/DatabaseTests" + "/sampleModFileFail2.txt", errors);
		Assert::AreEqual(0, b.size());
	}

#ifdef LATER
	void TestDatabaseLoaders::SampleModFileLoadingFail3()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		Assert::That([&] ()
				{
				std::vector<std::tuple<Modification*, std::string>> errors;
				PtmListLoader::ReadModsFromFile(testdir + "DatabaseTests", "sampleModFileFail3.txt"), errors).ToList();
				}, Throws::TypeOf<MzLibException*>().With::Property("Message").EqualTo("Input string for chemical formula was in an incorrect format: $%&$%"));
	}

	void TestDatabaseLoaders::SampleModFileLoadingFail4()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		Assert::That([&] ()
				{
				std::vector<std::tuple<Modification*, std::string>> errors;
				PtmListLoader::ReadModsFromFile(testdir + "DatabaseTests", "m.txt"), errors).ToList();
				}, Throws::TypeOf<MzLibException*>().With::Property("Message").EqualTo("0 or 238.229666 is not a valid monoisotopic mass"));
	}

	void TestDatabaseLoaders::SampleModFileLoadingFail5()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		std::vector<std::tuple<Modification*, std::string>> errors;
		auto b = PtmListLoader::ReadModsFromFile(testdir + "DatabaseTests", "sampleModFileFail5.txt"), errors);
		Assert::AreEqual(0, b.size()());
	}

	void TestDatabaseLoaders::SampleModFileLoadingFail6()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		std::vector<std::tuple<Modification*, std::string>> errors;
		auto b = PtmListLoader::ReadModsFromFile(testdir + "DatabaseTests", "sampleModFileFail5.txt"), errors);
		Assert::AreEqual(0, b.size()());
	}

	void TestDatabaseLoaders::CompactFormReading()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		std::vector<std::tuple<Modification*, std::string>> errors;
		Assert::AreEqual(2, PtmListLoader::ReadModsFromFile(testdir + "DatabaseTests", "sampleModFileDouble.txt"), errors).size()());
	}

	void TestDatabaseLoaders::CompactFormReading2()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		std::vector<std::tuple<Modification*, std::string>> errors;
		Assert::AreEqual(2, PtmListLoader::ReadModsFromFile(testdir + "DatabaseTests", "sampleModFileDouble2.txt"), errors).size()());
	}

	void TestDatabaseLoaders::Modification_read_write_into_proteinDb()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		Loaders::LoadElements(testdir + "elements2.dat"));
		std::vector<std::tuple<Modification*, std::string>> errors;
		auto sampleModList = PtmListLoader::ReadModsFromFile(testdir + "DatabaseTests", "z.txt"), errors).ToList();
		Assert::AreEqual(1, sampleModList.OfType<Modification*>()->Count());
		Protein *protein = new Protein("MCSSSSSSSSSS", "accession", "organism", std::vector<std::tuple<std::string, std::string>>(), std::unordered_map<int, std::vector<Modification*>>
				{
				{2, sampleModList.OfType<Modification*>().ToList()}
				},
				nullptr, "name", "full_name", false, false, std::vector<DatabaseReference*>(), std::vector<SequenceVariation*>(), disulfideBonds: std::vector<DisulfideBond*>());
		Assert::AreEqual(1, protein->getOneBasedPossibleLocalizedModifications()[2].OfType<Modification*>()->Count());
		ProteinDbWriter::WriteXmlDatabase(std::unordered_map<std::string, std::unordered_set<std::tuple<int, Modification*>>>(), {protein}, testdir + "test_modifications_with_proteins.xml"));
		Dictionary<std::string, Modification*> um;
		std::vector<Protein*> new_proteins = ProteinDbLoader::LoadProteinXML(testdir + "test_modifications_with_proteins.xml"), true, DecoyType::None, std::vector<Modification*>(), false, std::vector<std::string>(), um);
		Assert::AreEqual(1, new_proteins.size());
		Assert::AreEqual(1, new_proteins[0]->getOneBasedPossibleLocalizedModifications().size());
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

		// Check that Modifications were saved after last load
		Assert::AreEqual(1, ProteinDbLoader::GetPtmListFromProteinXml(testdir + R"(test_modifications_with_proteins.xml)")).size());
		Assert::True(ProteinDbLoader::GetPtmListFromProteinXml(testdir + R"(test_modifications_with_proteins.xml)"))[0] == new_proteins[0]->getOneBasedPossibleLocalizedModifications().SelectMany([&] (std::any kv)
				{
				kv->Value;
				}).First());

		//But that we can still read modifications from other protein XMLs that exist
		Assert::AreEqual(0, ProteinDbLoader::GetPtmListFromProteinXml(testdir + "DatabaseTests", "xml.xml")).size());

		// Check that Modifications were saved after last load
		auto b = ProteinDbLoader::GetPtmListFromProteinXml(testdir + R"(test_modifications_with_proteins.xml)"));
		Assert::AreEqual(1, b.size());

		auto c = ProteinDbLoader::GetPtmListFromProteinXml(testdir + R"(test_modifications_with_proteins.xml)"))[0];
		auto d = new_proteins[0]->getOneBasedPossibleLocalizedModifications().SelectMany([&] (std::any kv)
				{
				kv->Value;
				}).First();

		Assert::IsTrue(c->Equals(d));

		//But that we can still read modifications from other protein XMLs that exist
		Assert::AreEqual(0, ProteinDbLoader::GetPtmListFromProteinXml(testdir + "DatabaseTests", "xml.xml")).size());

		delete d;
		delete protein;
	}

	void TestDatabaseLoaders::Test_MetaMorpheusStyleProteinDatabaseWriteAndREad()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		std::string proteinDbFilePath = testdir + "TestProteinSplitAcrossFiles.xml");

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
		std::vector<Protein*> proteinList = {prot1};
		ProteinDbWriter::WriteXmlDatabase(std::unordered_map<std::string, std::unordered_set<std::tuple<int, Modification*>>>(), proteinList, proteinDbFilePath);

		auto lines = File::ReadAllLines(proteinDbFilePath);
		std::unordered_map<string, Modification> um;
		std::vector<Protein*> newProteinList = ProteinDbLoader::LoadProteinXML(proteinDbFilePath, true, DecoyType::Reverse, std::vector<Modification*>(), false, std::vector<std::string>(), um, -1);

		delete prot1;
		delete mod;
	}

	void TestDatabaseLoaders::DoNotWriteSameModTwiceAndDoNotWriteInHeaderSinceDifferent()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		Loaders::LoadElements(testdir + "elements2.dat"));
		std::vector<std::tuple<Modification*, std::string>> errors;
		auto sampleModList = PtmListLoader::ReadModsFromFile(testdir + "DatabaseTests", "z.txt"), errors).ToList();
		Protein *protein = new Protein("MCSSSSSSSSSS", "accession", "organism", std::vector<std::tuple<std::string, std::string>>(), std::unordered_map<int, std::vector<Modification*>>
				{
				{2, sampleModList.OfType<Modification*>().ToList()}
				},
				nullptr, "name", "full_name", false, false, std::vector<DatabaseReference*>(), std::vector<SequenceVariation*>(), disulfideBonds: std::vector<DisulfideBond*>());
		Assert::AreEqual(1, protein->getOneBasedPossibleLocalizedModifications()[2].OfType<Modification*>()->Count());

		std::unordered_map<std::string, std::unordered_set<std::tuple<int, Modification*>>> dictWithThisMod;

		std::unordered_set<std::tuple<int, Modification*>> value;

		auto modReadFromFile = dynamic_cast<Modification*>(sampleModList.front());
		ModificationMotif motif;
		ModificationMotif::TryGetMotif("C", motif);
		Modification *newMod = new Modification("Palmitoylation of C", "", "Type", "MOD_RES", motif, "Anywhere.", modReadFromFile->getChemicalFormula(), modReadFromFile->getMonoisotopicMass(), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "E:\\GitClones\\mzLib\\Test\\bin\\x64\\Debug\\DatabaseTests\\z.txt");

		Assert::IsTrue(newMod->Equals(sampleModList.front()));

		Assert::AreEqual(newMod, sampleModList.front());
		Assert::AreEqual(sampleModList.front(), newMod);

		value.insert(std::tuple<int, Modification*>(2, newMod));

		dictWithThisMod.emplace("accession", value);
		auto newModResEntries = ProteinDbWriter::WriteXmlDatabase(dictWithThisMod, std::vector<Protein*> {protein}, testdir + "test_modifications_with_proteins3.xml"));
		Assert::AreEqual(0, newModResEntries.size());
		Dictionary<std::string, Modification*> um;
		std::vector<Protein*> new_proteins = ProteinDbLoader::LoadProteinXML(testdir + "test_modifications_with_proteins3.xml"), true, DecoyType::None, std::vector<Modification*>(), false, std::vector<std::string>(), um);
		Assert::AreEqual(1, new_proteins.size());
		Assert::AreEqual(1, new_proteins[0]->getOneBasedPossibleLocalizedModifications().size());
		Assert::AreEqual(1, new_proteins[0]->getOneBasedPossibleLocalizedModifications().SelectMany([&] (std::any kv)
					{
					kv->Value;
					})->Count());

		delete newMod;
		delete protein;
	}

	void TestDatabaseLoaders::TestWritePtmWithNeutralLoss()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		std::string filename = "test_neutral_loss_mod.xml";
		std::unordered_map<int, std::vector<Modification*>> mods;

		ModificationMotif motif;
		ModificationMotif::TryGetMotif("T", motif);
		Modification *m = new Modification("Phospho", "", "Test", "", motif, "Anywhere.", nullptr, std::make_optional(80.0), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>
				{
				{
				DissociationType::HCD, {80.0, 0}
				},
				{
				DissociationType::ETD, {70.0, 0}
				}
				},
				std::unordered_map<DissociationType, std::vector<double>>(), "");
		Assert::That(m->getValidModification());

		mods.emplace(4, std::vector<Modification*> {m});

		Protein *protein = new Protein("PEPTIDE", "accession", "", std::vector<std::tuple<std::string, std::string>>(), mods, std::vector<ProteolysisProduct>(), "", "", false, false, std::vector<DatabaseReference>(), std::vector<SequenceVariation>(), std::vector<SequenceVariation>(), "", std::vector<DisulfideBond>(), std::vector<SpliceSite>(), "");
		Assert::That(protein->getOneBasedPossibleLocalizedModifications().size() == 1);
		Assert::That(protein->getOneBasedPossibleLocalizedModifications().First()->Value->First().NeutralLosses.First()->Value->Count == 2);

		ProteinDbWriter::WriteXmlDatabase(std::unordered_map<std::string, std::unordered_set<std::tuple<int, Modification*>>>(), {protein}, testdir + filename));

		// with passed-in mods
		Dictionary<std::string, Modification*> um;
		std::vector<Protein*> new_proteins = ProteinDbLoader::LoadProteinXML(testdir + filename), true, DecoyType::None, {m}, false, std::vector<std::string>(), um);
		Assert::That(new_proteins.front().OneBasedPossibleLocalizedModifications::First()->Value->First().NeutralLosses.First()->Value->Count == 2);

		// should be able to read mod from top of database...
		new_proteins = ProteinDbLoader::LoadProteinXML(testdir + filename), true, DecoyType::None, std::vector<Modification*>(), false, std::vector<std::string>(), um);
		Assert::That(new_proteins.front().OneBasedPossibleLocalizedModifications::First()->Value->First().NeutralLosses.First()->Value->Count == 2);

		delete protein;
		delete m;
	}

	void TestDatabaseLoaders::TestWritePtmWithDiagnosticIons()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		std::string filename = "test_diagnostic_ion_mod.xml";
		std::unordered_map<int, std::vector<Modification*>> mods;

		ModificationMotif motif;
		ModificationMotif::TryGetMotif("T", motif);
		Modification *m = new Modification("Phospho", "", "Test", "", motif, "Anywhere.", nullptr, std::make_optional(80.0), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>
				{
				{
				DissociationType::HCD, {80.0, 0}
				},
				{
				DissociationType::ETD, {70.0, 0}
				}
				},
				"");
		Assert::That(m->getValidModification());

		mods.emplace(4, std::vector<Modification*> {m});

		Protein *protein = new Protein("PEPTIDE", "accession", "", std::vector<std::tuple<std::string, std::string>>(), mods, std::vector<ProteolysisProduct>(), "", "", false, false, std::vector<DatabaseReference>(), std::vector<SequenceVariation>(), std::vector<SequenceVariation>(), "", std::vector<DisulfideBond>(), std::vector<SpliceSite>(), "");
		Assert::That(protein->getOneBasedPossibleLocalizedModifications().size() == 1);
		Assert::That(protein->getOneBasedPossibleLocalizedModifications().First()->Value->First().DiagnosticIons.First()->Value->Count == 2);

		ProteinDbWriter::WriteXmlDatabase(std::unordered_map<std::string, std::unordered_set<std::tuple<int, Modification*>>>(), {protein}, testdir + filename));

		// with passed-in mods
		Dictionary<std::string, Modification*> um;
		std::vector<Protein*> new_proteins = ProteinDbLoader::LoadProteinXML(testdir + filename), true, DecoyType::None, {m}, false, std::vector<std::string>(), um);
		Assert::That(new_proteins.front().OneBasedPossibleLocalizedModifications::First()->Value->First().DiagnosticIons.First()->Value->Count == 2);

		// should be able to read mod from top of database...
		new_proteins = ProteinDbLoader::LoadProteinXML(testdir + filename), true, DecoyType::None, std::vector<Modification*>(), false, std::vector<std::string>(), um);
		Assert::That(new_proteins.front().OneBasedPossibleLocalizedModifications::First()->Value->First().DiagnosticIons.First()->Value->Count == 2);

		delete protein;
		delete m;
	}

	void TestDatabaseLoaders::TestWritePtmWithNeutralLossAndDiagnosticIons()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		std::string filename = "test_neutral_loss_diagnostic_ion_mod.xml";
		std::unordered_map<int, std::vector<Modification*>> mods;

		ModificationMotif motif;
		ModificationMotif::TryGetMotif("T", motif);
		Modification *m = new Modification("Phospho", "", "Test", "", motif, "Anywhere.", nullptr, std::make_optional(80.0), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>
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

		mods.emplace(4, std::vector<Modification*> {m});

		Protein *protein = new Protein("PEPTIDE", "accession", "", std::vector<std::tuple<std::string, std::string>>(), mods, std::vector<ProteolysisProduct>(), "", "", false, false, std::vector<DatabaseReference>(), std::vector<SequenceVariation>(), std::vector<SequenceVariation>(), "", std::vector<DisulfideBond>(), std::vector<SpliceSite>(), "");
		Assert::That(protein->getOneBasedPossibleLocalizedModifications().size() == 1);
		Assert::That(protein->getOneBasedPossibleLocalizedModifications().First()->Value->First().NeutralLosses.First()->Value->Count == 2);

		ProteinDbWriter::WriteXmlDatabase(std::unordered_map<std::string, std::unordered_set<std::tuple<int, Modification*>>>(), {protein}, testdir + filename));

		// with passed-in mods
		Dictionary<std::string, Modification*> um;
		std::vector<Protein*> new_proteins = ProteinDbLoader::LoadProteinXML(testdir + "/" + filename, true,
				DecoyType::None, {m}, false,
				std::vector<std::string>(), um);
		Assert::That(new_proteins.front().OneBasedPossibleLocalizedModifications::First()->Value->First().NeutralLosses.First()->Value->Count == 2);
		Assert::That(new_proteins.front().OneBasedPossibleLocalizedModifications::First()->Value->First().DiagnosticIons.First()->Value->Count == 2);

		// should be able to read mod from top of database...
		new_proteins = ProteinDbLoader::LoadProteinXML(testdir + "/" + filename, true, DecoyType::None, std::vector<Modification*>(), false, std::vector<std::string>(), um);
		Assert::That(new_proteins.front().OneBasedPossibleLocalizedModifications::First()->Value->First().NeutralLosses.First()->Value->Count == 2);
		Assert::That(new_proteins.front().OneBasedPossibleLocalizedModifications::First()->Value->First().DiagnosticIons.First()->Value->Count == 2);

		delete protein;
		delete m;
	}
#endif
}
