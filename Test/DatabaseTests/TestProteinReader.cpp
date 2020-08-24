#include "TestProteinReader.h"
#include "../../Proteomics/Modifications/Modification.h"
#include "../../UsefulProteomicsDatabases/Loaders.h"
#include "../../Proteomics/Modifications/ModificationMotif.h"
#include "../../Proteomics/Protein/DatabaseReference.h"
#include "../../Proteomics/Protein/Protein.h"
#include "../../Proteomics/Protein/ProteolysisProduct.h"
#include "../../Proteomics/Protein/SequenceVariation.h"
#include "../../UsefulProteomicsDatabases/ProteinDbLoader.h"
#include "../../UsefulProteomicsDatabases/DecoyType.h"
#include "../../UsefulProteomicsDatabases/PtmListLoader.h"
#include "../../include/Assert.h"

using namespace Proteomics;
using namespace UsefulProteomicsDatabases;

int main ( int argc, char **argv )
{
	int i=0;
	std::cout << i << ". PeriodicTableLoader" << std::endl;
	const std::string elfile="elements.dat";
	const std::string &elr=elfile;
	UsefulProteomicsDatabases::PeriodicTableLoader::Load (elr);

	std::cout << ++i << ". SetUpModifications" << std::endl;
	Test::TestProteinReader::SetUpModifications();

	std::cout << ++i << ". MergeACoupleProteins" << std::endl;
	Test::TestProteinReader::MergeACoupleProteins();

	std::cout << ++i << ". XmlTest" << std::endl;
	Test::TestProteinReader::XmlTest();
#ifdef LATER
	std::cout << ++i << ". DisulfideXmlTest" << std::endl;
	Test::TestProteinReader::DisulfideXmlTest();

	std::cout << ++i << ". XmlTest_2entry" << std::endl;
	Test::TestProteinReader::XmlTest_2entry();

	std::cout << ++i << ". XmlGzTest" << std::endl;
	Test::TestProteinReader::XmlGzTest();

	std::cout << ++i << ". XmlFunkySequenceTest"  << std::endl;
	Test::TestProteinReader::XmlFunkySequenceTest();

	std::cout << ++i << ". XmlModifiedStartTest"  << std::endl;
	Test::TestProteinReader::XmlModifiedStartTest();

	std::cout << ++i << ". FastaTest" << std::endl;
	Test::TestProteinReader::FastaTest();

	std::cout << ++i << ". BadFastaTest"  << std::endl;
	Test::TestProteinReader::BadFastaTest();

	std::cout << ++i << ". Load_fasta_handle_tooHigh_indices"  << std::endl;
	Test::TestProteinReader::Load_fasta_handle_tooHigh_indices();

	std::cout << ++i << ". Read_xml_mod_collision"  << std::endl;
	Test::TestProteinReader::Read_xml_mod_collision();

	std::cout << ++i << ". Read_xml_exclude_mods"  << std::endl;
	std::string excludedMod = ". ". ; bool isExcluded = false; 
	Test::TestProteinReader::Read_xml_exclude_mods(excludedMod, isExcluded);

	std::cout << ++i << ". CompareOxidationWithAndWithoutCf"  << std::endl;
	Test::TestProteinReader::CompareOxidationWithAndWithoutCf();

	std::cout << ++i << ". TestReverseDecoyXML"  << std::endl;
	Test::TestProteinReader::TestReverseDecoyXML();

	std::cout << ++i << ". TestSlideDecoyXML"  << std::endl;
	Test::TestProteinReader::TestSlideDecoyXML();

	std::cout << ++i << ". TestReverseDecoyFasta"  << std::endl;
	Test::TestProteinReader::TestReverseDecoyFasta();

	std::cout << ++i << ". TestSlideDecoyFasta"  << std::endl;
	Test::TestProteinReader::TestSlideDecoyFasta();

	std::cout << ++i << ". " << std::endl;


	std::cout << ++i << ". " << std::endl;
#endif

}

namespace Test
{
	TestProteinReader::UniProtPtms = std::vector<Modification*>();
	void TestProteinReader::SetUpModifications()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		auto psiModDeserialized = Loaders::LoadPsiMod(testdir + "/PSI-MOD.obo2.xml");
		std::unordered_map<std::string, int> formalChargesDictionary = Loaders::GetFormalChargesDictionary(psiModDeserialized);
		UniProtPtms = Loaders::LoadUniprot(testdir + "/ptmlist2.txt", formalChargesDictionary);
	}

	void TestProteinReader::MergeACoupleProteins()
	{
		ModificationMotif *motif;
		ModificationMotif::TryGetMotif("A", &motif);
		std::vector<std::tuple<std::string, std::string>> geneNames;
		geneNames.push_back(std::tuple<std::string, std::string>("gene", "name"));
		std::vector<DatabaseReference*> databaseReferences; 
		std::vector<std::tuple<std::string, std::string>> tempVectorOfTupleStringStrings;
		tempVectorOfTupleStringStrings.push_back(std::tuple<std::string, std::string>("type", "property"));
		databaseReferences.push_back(new DatabaseReference("ref",
					"id",
					tempVectorOfTupleStringStrings)); 
		std::vector<SequenceVariation*> sequenceVariations;
		sequenceVariations.push_back(new SequenceVariation(1, 
					2, 
					"A", 
					"B", 
					"var",
					std::unordered_map<int, std::vector<Modification*>>()));
		std::vector<ProteolysisProduct*> proteolysisProducts;
		proteolysisProducts.push_back(new ProteolysisProduct(std::make_optional(1), 
					std::make_optional(2), 
					"prod"));
		std::unordered_map<int, std::vector<Modification*>> oneBasedModifications;
		std::vector<Modification*> tempModificationVector;
		tempModificationVector.push_back(new Modification("mod",
					"",
					"type",
					"",
					motif,
					"Anywhere.",
					nullptr,
					std::make_optional(1)));
		oneBasedModifications.insert(std::pair<int, std::vector<Modification*>>(1, tempModificationVector));
		Protein *p = new Protein("ASEQUENCE", 
				"id",
				"",
				geneNames,
				oneBasedModifications,
				proteolysisProducts,
				"name", 
				"full_name", 
				false,
				false, 
				databaseReferences,
				sequenceVariations);

		std::vector<DatabaseReference*> databaseReferences2;
		databaseReferences2.push_back(new DatabaseReference("ref", 
					"id", 
					tempVectorOfTupleStringStrings));
				std::vector<SequenceVariation*> sequenceVariations2;
				sequenceVariations2.push_back(new SequenceVariation(1, 
						2, 
						"A", 
						"B", 
						"var",
						std::unordered_map<int, std::vector<Modification*>>()));
				std::vector<ProteolysisProduct*> proteolysisProducts2;
				proteolysisProducts2.push_back(new ProteolysisProduct(std::make_optional(1),
						std::make_optional(2),
						"prod"));
				std::unordered_map<int, std::vector<Modification*>> oneBasedModifications2;
				std::vector<Modification*> tempModificationVector2;
				tempModificationVector2.push_back(new Modification("mod", 
						"", 
						"type", 
						"", 
						motif, 
						"Anywhere.", 
						nullptr, 
						std::make_optional(10)));
				oneBasedModifications2.insert(std::pair<int, std::vector<Modification*>>(1, tempModificationVector2)); 
				Protein *p2 = new Protein("ASEQUENCE", 
						"id",
						"",
						geneNames,
						oneBasedModifications2,
						proteolysisProducts2,
						"name",
						"full_name", 
						false,
						false,
						databaseReferences2,
						sequenceVariations2);

				std::vector<Protein*> tempProteinVector;
				tempProteinVector.push_back(p);
				tempProteinVector.push_back(p2);
				std::vector<Protein*> merged = ProteinDbLoader::MergeProteins(tempProteinVector);
				Assert::AreEqual(1, merged.size());
				Assert::AreEqual(1, merged[0]->getDatabaseReferences().size());
				Assert::AreEqual(1, merged[0]->getGeneNames().size());
				Assert::AreEqual(1, merged[0]->getSequenceVariations().size());
				Assert::AreEqual(1, merged[0]->getProteolysisProducts().size());
				Assert::AreNotEqual(p->getOneBasedPossibleLocalizedModifications().begin()->second[0], p2->getOneBasedPossibleLocalizedModifications().begin()->second[0]);
				Assert::AreEqual(1, merged[0]->getOneBasedPossibleLocalizedModifications().size());
				Assert::AreEqual(2, merged[0]->getOneBasedPossibleLocalizedModifications().begin()->second.size());

				//C# TO C++ CONVERTER TODO TASK: A 'delete p2' statement was not added since p2 was passed to a method or constructor. Handle memory management manually.
				//C# TO C++ CONVERTER TODO TASK: A 'delete p' statement was not added since p was passed to a method or constructor. Handle memory management manually.
				delete p;
				delete p2;
	}
	
	void TestProteinReader::XmlTest()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		std::unordered_map<std::string, Modification*> un;
		std::vector<std::string> tempStringVector;
		std::vector<Modification*> UniProtPtms;
		std::vector<Protein*> ok = ProteinDbLoader::LoadProteinXML(testdir + "/xml.xml", 
				true, 
				DecoyType::Reverse, 
				UniProtPtms, 
				false, 
				tempStringVector, 
				un);
#ifdef LATER
		Assert::AreEqual('M', ok[0][0]);
		Assert::AreEqual('M', ok[1][0]);
#endif
		Assert::AreEqual("P62805|H4_HUMAN|Histone H4", ok[0]->getFullDescription());
		Assert::AreEqual("DECOY_P62805|H4_HUMAN|Histone H4", ok[1]->getFullDescription());

#ifdef LATER 
		Assert::AreEqual("ENST00000244537", ok[0]->getDatabaseReferences().First([&] (std::any dbRef)
					{
					return dbRef->Type == "Ensembl";
					}).Id);
		Assert::AreEqual("protein sequence ID", ok[0]->getDatabaseReferences().First([&] (std::any dbRef)
					{
					return dbRef->Type == "Ensembl";
					}).Properties->First().Item1);
		Assert::AreEqual("ENSP00000244537", ok[0]->getDatabaseReferences().First([&] (std::any dbRef)
					{
					return dbRef->Type == "Ensembl";
					}).Properties->First().Item2);
#endif


		Assert::AreEqual(42, ok[0]->getGeneNames().size());

#ifdef LATER
		Assert::AreEqual(14, ok[0]->getGeneNames().Where([&] (std::any t)
					{
					return t->Item1 == "primary";
					}).size());
		Assert::AreEqual("HIST1H4A", ok[0]->getGeneNames().Where([&] (std::any t)
					{
					return t->Item1 == "primary";
					}).First().Item2);
		Assert::AreEqual(23, ok[0]->getDatabaseReferences().size()([&] (std::any dbRef)
					{
					return dbRef->Type == "Ensembl";
					}));
#endif

		Assert::AreEqual(0, ok[0]->getDisulfideBonds().size());
		Assert::AreEqual(1, ok[0]->getSequenceVariations().size());
		Assert::AreEqual(1, ok[1]->getSequenceVariations().size()); // decoys get the same sequence variations
		Assert::AreEqual(64, ok[0]->getSequenceVariations()[0]->getOneBasedBeginPosition());
		Assert::AreEqual(64, ok[0]->getSequenceVariations()[0]->getOneBasedEndPosition());
		Assert::AreEqual(103 - 64 + 2, ok[1]->getSequenceVariations()[0]->getOneBasedBeginPosition());
		Assert::AreEqual(103 - 64 + 2, ok[1]->getSequenceVariations()[0]->getOneBasedEndPosition());
		Assert::AreNotEqual(ok[0]->getSequenceVariations()[0]->getDescription(), ok[1]->getSequenceVariations()[0]->getDescription()); //decoys and target variations don't have the same desc.
		Assert::AreEqual("Homo sapiens", ok[1]->getOrganism());
	}

#ifdef LATER
	void TestProteinReader::DisulfideXmlTest()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		Dictionary<std::string, Modification*> un;
		auto ok = ProteinDbLoader::LoadProteinXML(testdir + "/disulfidetests.xml", true, DecoyType::Reverse, UniProtPtms, false, std::vector<std::string>(), un);

		Assert::AreEqual('M', ok[0][0]);
		Assert::AreEqual('M', ok[1][0]);

		Assert::AreEqual(3, ok[0]->getDisulfideBonds().size());
		Assert::AreEqual('C', ok[0]->getBaseSequence()[ok[0]->getDisulfideBonds()[0].getOneBasedBeginPosition() - 1]);
		Assert::AreEqual('C', ok[0]->getBaseSequence()[ok[0]->getDisulfideBonds()[0].getOneBasedEndPosition() - 1]);
		Assert::AreEqual(31, ok[0]->getDisulfideBonds()[0].getOneBasedBeginPosition());
		Assert::AreEqual(94, ok[0]->getDisulfideBonds()[0].getOneBasedEndPosition());
		Assert::AreEqual(93, ok[0]->getDisulfideBonds().ElementAt(2).getOneBasedBeginPosition());
		Assert::AreEqual(93, ok[0]->getDisulfideBonds().ElementAt(2).getOneBasedEndPosition());

		Assert::AreEqual(3, ok[1]->getDisulfideBonds().size());
		Assert::AreEqual('C', ok[1]->getBaseSequence()[ok[1]->getDisulfideBonds()[0].getOneBasedBeginPosition() - 1]);
		Assert::AreEqual('C', ok[1]->getBaseSequence()[ok[1]->getDisulfideBonds()[0].getOneBasedEndPosition() - 1]);
		Assert::AreEqual(16, ok[1]->getDisulfideBonds()[0].getOneBasedBeginPosition());
		Assert::AreEqual(79, ok[1]->getDisulfideBonds()[0].getOneBasedEndPosition());
		Assert::AreEqual(17, ok[1]->getDisulfideBonds().ElementAt(2).getOneBasedBeginPosition());
		Assert::AreEqual(17, ok[1]->getDisulfideBonds().ElementAt(2).getOneBasedEndPosition());
		Assert::AreNotEqual(ok[0]->getDisulfideBonds()[0].getDescription(), ok[1]->getDisulfideBonds()[0].getDescription()); //decoys and target disulfide bonds don't have the same desc.
	}

	void TestProteinReader::XmlTest_2entry()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		std::unordered_map<std::string, Modification*> un;
		auto ok = ProteinDbLoader::LoadProteinXML(testdir + "/xml2.xml", true, DecoyType::Reverse, UniProtPtms, false, std::vector<std::string>(), un);

#ifdef LATER 
		// proteolysis products check
		Assert::True(ok.All([&] (std::any p)
					{
					p::ProteolysisProducts::All([&] (std::any d)
							{
							return d-.getOneBasedBeginPosition == nullptr || d:.getOneBasedBeginPosition > 0;
							});
					}));
		Assert::True(ok.All([&] (std::any p)
					{
					p::ProteolysisProducts::All([&] (std::any d)
							{
							return d-.getOneBasedEndPosition == nullptr || d:.getOneBasedEndPosition <= p->Length;
							});
					}));
#endif 

		// base sequence check
#ifdef LATER
		Assert::False(ok.All([&] (std::any p)
					{
					p::BaseSequence->Contains(" ");
					}));
		Assert::False(ok.All([&] (std::any p)
					{
					p::BaseSequence->Contains("\t");
					}));
		Assert::False(ok.All([&] (std::any p)
					{
					p::BaseSequence->Contains("\n");
					}));
#endif

		// GoTerm checks
#ifdef LATER 
		std::vector<Protein*> targets = ok.Where([&] (std::any p)
				{
				!p::IsDecoy;
				}).ToList();
		Assert::AreEqual(2, targets.size());
		Assert::AreEqual(1, targets[0]->getDatabaseReferences().size()([&] (std::any dbRef)
					{
					return dbRef->Type == "EnsemblFungi";
					}));
		Assert::AreEqual(1, targets[1]->getDatabaseReferences().size()([&] (std::any dbRef)
					{
					return dbRef->Type == "EnsemblFungi";
					}));
#endif
	}

	void TestProteinReader::XmlGzTest()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		std::unordered_map<std::string, Modification*> un;
		auto ok = ProteinDbLoader::LoadProteinXML(testdir + "/xml.xml.gz", true, DecoyType::Reverse, UniProtPtms, false, std::vector<std::string>(), un);

		Assert::AreEqual('M', ok[0][0]);
		Assert::AreEqual('M', ok[1][0]);

		Assert::AreEqual("P62805|H4_HUMAN|Histone H4", ok[0]->getFul.getDescription());
		Assert::AreEqual("DECOY_P62805|H4_HUMAN|Histone H4", ok[1]->getFul.getDescription());

#ifdef LATER
		Assert::AreEqual("ENST00000244537", ok[0]->getDatabaseReferences().First([&] (std::any dbRef)
					{
					return dbRef->Type == "Ensembl";
					}).Id);
		Assert::AreEqual("protein sequence ID", ok[0]->getDatabaseReferences().First([&] (std::any dbRef)
					{
					return dbRef->Type == "Ensembl";
					}).Properties->First().Item1);
		Assert::AreEqual("ENSP00000244537", ok[0]->getDatabaseReferences().First([&] (std::any dbRef)
					{
					return dbRef->Type == "Ensembl";
					}).Properties->First().Item2);
#endif
		Assert::AreEqual(42, ok[0]->getGeneNames().size());

#ifdef LATER
		Assert::AreEqual(14, ok[0]->getGeneNames().Where([&] (std::any t)
					{
					return t->Item1 == "primary";
					}).size());
		Assert::AreEqual("HIST1H4A", ok[0]->getGeneNames().Where([&] (std::any t)
					{
					return t->Item1 == "primary";
					}).First().Item2);
		Assert::AreEqual(23, ok[0]->getDatabaseReferences().size()([&] (std::any dbRef)
					{
					return dbRef->Type == "Ensembl";
					}));
#endif
	}

	void TestProteinReader::XmlFunkySequenceTest()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		std::unordered_map<std::string, Modification*> un;
		auto ok = ProteinDbLoader::LoadProteinXML(testdir + "/fake_h4.xml", true, DecoyType::Reverse, UniProtPtms, false, std::vector<std::string>(), un);

		Assert::AreEqual("S", ok[0]->getBaseSequence()->substr(0, 1));
		Assert::AreEqual("G", ok[1]->getBaseSequence()->substr(0, 1));

		Assert::AreEqual('S', ok[0][0]);
		Assert::AreEqual('G', ok[1][0]);
	}

	void TestProteinReader::XmlModifiedStartTest()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		std::unordered_map<std::string, Modification*> un;
		auto ok = ProteinDbLoader::LoadProteinXML(testdir + "/modified_start.xml", true, DecoyType::Reverse, UniProtPtms, false, std::vector<std::string>(), un);

		Assert::AreEqual("M", ok[0]->getBaseSequence()->substr(0, 1)); //the original protein sequence in the original order starts with 'M'
		Assert::AreEqual("M", ok[1]->getBaseSequence()->substr(0, 1)); //the decoy protein sequence in the reverse order from the original still starts with 'M'
		Assert::AreEqual(1, ok[1]->getOneBasedPossibleLocalizedModifications()[1].size()); //the initial methionine of the decoy still has the mod that it's supposed to have.
	}

	void TestProteinReader::FastaTest()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		std::vector<std::string> a;
		std::vector<Protein*> prots = ProteinDbLoader::LoadProteinFasta(testdir + "/fasta.fasta", true, DecoyType::Reverse, false, ProteinDbLoader::UniprotAccessionRegex, ProteinDbLoader::UniprotFullNameRegex, ProteinDbLoader::UniprotNameRegex, ProteinDbLoader::UniprotGeneNameRegex, ProteinDbLoader::UniprotOrganismRegex, a);

		Assert::AreEqual("P62805", prots[0]->getAccession());
		Assert::AreEqual("H4_HUMAN", prots[0]->getName());
		Assert::AreEqual("Histone H4", prots[0]->getFullName());
		Assert::AreEqual("HIST1H4A", std::get<0>(prots[0]->getGeneNames()));
		Assert::AreEqual("Homo sapiens", prots[0]->getOrganism());
	}

	void TestProteinReader::BadFastaTest()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		std::vector<std::string> a;
		ProteinDbLoader::LoadProteinFasta(testdir + "/bad4.fasta", true, DecoyType::Reverse, false, ProteinDbLoader::UniprotAccessionRegex, ProteinDbLoader::UniprotFullNameRegex, ProteinDbLoader::UniprotAccessionRegex, ProteinDbLoader::UniprotGeneNameRegex, ProteinDbLoader::UniprotOrganismRegex, a);
		Assert::AreEqual(1, a.size());
		std::vector<std::string> b;
		ProteinDbLoader::LoadProteinFasta(testdir + "/bad3.fasta", true, DecoyType::Reverse, false, ProteinDbLoader::UniprotAccessionRegex, ProteinDbLoader::UniprotFullNameRegex, ProteinDbLoader::UniprotAccessionRegex, ProteinDbLoader::UniprotGeneNameRegex, ProteinDbLoader::UniprotOrganismRegex, b);
		Assert::AreEqual(2, b.size());
		std::vector<std::string> c;
		ProteinDbLoader::LoadProteinFasta(testdir + "/blank.fasta", true, DecoyType::Reverse, false, ProteinDbLoader::UniprotAccessionRegex, ProteinDbLoader::UniprotFullNameRegex, ProteinDbLoader::UniprotAccessionRegex, ProteinDbLoader::UniprotGeneNameRegex, ProteinDbLoader::UniprotOrganismRegex, c);
		Assert::AreEqual(1, c.size());
	}

	void TestProteinReader::Load_fasta_handle_tooHigh_indices()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		std::vector<std::string> a;
		auto p = ProteinDbLoader::LoadProteinFasta(testdir + "/bad.fasta", true, DecoyType::Reverse, false, ProteinDbLoader::UniprotAccessionRegex, ProteinDbLoader::UniprotFullNameRegex, ProteinDbLoader::UniprotAccessionRegex, ProteinDbLoader::UniprotGeneNameRegex, ProteinDbLoader::UniprotOrganismRegex, a);
	}

	void TestProteinReader::Read_xml_mod_collision()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		ModificationMotif *motif;
		ModificationMotif::TryGetMotif("S", &motif);
		std::vector<Modification*> nice;	
		nice.push_back(new Modification("N-acetylserine", 
					"", 
					"one", 
					"", 
					motif, 
					"Anywhere.", 
					nullptr, 
					std::make_optional(1), 
					std::unordered_map<std::string, std::vector<std::string>>(),
					std::unordered_map<std::string, std::vector<std::string>>(), 
					std::vector<std::string>(), 
					std::unordered_map<DissociationType, std::vector<double>>(), 
					std::unordered_map<DissociationType, std::vector<double>>(), 
					""));
		nice.push_back(new Modification("N-acetylserine", 
					"", 
					"two", 
					"", 
					motif,
					"Anywhere.", 
					nullptr, 
					std::make_optional(1),
					std::unordered_map<std::string, std::vector<std::string>>(), 
					std::unordered_map<std::string, std::vector<std::string>>(), 
					std::vector<std::string>(),
					std::unordered_map<DissociationType, std::vector<double>>(),
					std::unordered_map<DissociationType, std::vector<double>>(), 
					""));

		std::unordered_map<std::string, Modification*> un;
		std::vector<std::string> tempStringVector;
		auto ok = ProteinDbLoader::LoadProteinXML(testdir + "/xml.xml", 
				true,
				DecoyType::Reverse,
				UniProtPtms.Concat(nice),
				false,
				tempStringVector,
				un);

#ifdef LATER
		Assert::True(ok[0]->getOneBasedPossibleLocalizedModifications().Any([&] (std::any kv)
					{
					return kv->Value.size > 1;
					}));

		std::vector<std::string> myOriginalIds = ok[0]->getOneBasedPossibleLocalizedModifications()[2]->Select([&] (std::any i)
				{
				i::OriginalId;
				}).ToList();

		Assert::True(std::find(myOriginalIds.begin(), myOriginalIds.end(), "N-acetylserine") != myOriginalIds.end());
#endif
	}

	void TestProteinReader::Read_xml_exclude_mods(const std::string &excludeString, bool isExcluded)
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		ModificationMotif *motif;
		ModificationMotif::TryGetMotif("X", &motif);

		std::vector<Modification*> nice;	
		nice.push_back(new Modification("N-acetylserine", 
					"", 
					"exclude_me", 
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
					""));
		nice.push_back(new Modification("N-acetylserine", 
					"",
					"exclude_me_not",
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
					""));

		Assert::IsTrue(nice[0]->getValidModification());

		std::unordered_map<std::string, Modification*> un;
		std::vector<std::string> tempStringVector;
		tempStringVector.push_back(excludeString);
		auto ok2 = ProteinDbLoader::LoadProteinXML(testdir + "/xml.xml", 
				true,
				DecoyType::Reverse,
				nice,
				false,
				tempStringVector,
				un);

#ifdef LATER
		std::vector<std::string> modTypes;
		for (auto entry : ok2[0]->getOneBasedPossibleLocalizedModifications())
		{
			modTypes.AddRange(entry.second->Select([&] (std::any m)
						{
						m::ModificationType;
						}).ToList()->Distinct());
		}
		Assert::AreEqual(isExcluded, std::find(modTypes.begin(), modTypes.end(), "exclude_me") != modTypes.end());
		Assert::AreEqual(!isExcluded, std::find(modTypes.begin(), modTypes.end(), "exclude_me_not") != modTypes.end());
#endif
	}

	void TestProteinReader::CompareOxidationWithAndWithoutCf()
	{
		std::string aString = R"(ID   Methionine (R)-sulfoxide
AC   PTM-0480
FT   MOD_RES
TG   Methionine.
PA   Amino acid side chain.
PP   Anywhere.
CF   O1
MM   15.994915
MA   16.00
LC   Intracellular localisation.
TR   Eukaryota; taxId:2759 (Eukaryota).
KW   Oxidation.
DR   RESID; AA0581.
DR   PSI-MOD; MOD:00720.
//)";
		std::vector<(Modification, string)> errorsA;
		auto a = PtmListLoader::ReadModsFromString(aString, errorsA).front();

		std::string bString = R"(ID   Oxidation of M
TG   M
PP   Anywhere.
MT   Common Variable
CF   O1
//)";
		std::vector<(Modification, string)> errorsB;
		auto b = PtmListLoader::ReadModsFromString(bString, errorsB).front();

		Assert::IsTrue(std::abs(static_cast<double>((dynamic_cast<Modification*>(a))->getMonoisotopicMass()) - static_cast<double>((dynamic_cast<Modification*>(b))->getMonoisotopicMass())) < 1e-6);
		Assert::IsTrue(std::abs(static_cast<double>((dynamic_cast<Modification*>(a))->getMonoisotopicMass()) - static_cast<double>((dynamic_cast<Modification*>(b))->getMonoisotopicMass())) > 1e-7);
	}

	void TestProteinReader::TestReverseDecoyXML()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		auto nice = std::vector<Modification*>();
		Dictionary<std::string, Modification*> un;
		auto ok2 = ProteinDbLoader::LoadProteinXML(testdir + "/disulfidetests.xml", true, DecoyType::Reverse, nice, false, std::vector<std::string> {"exclude_me"}, un);

		Assert::AreEqual("MALLVHFLPLLALLALWEPKPTQAFVKQHLCGPHLVEALYLVCGERGFFYTPKSRREVEDPQVEQLELGGSPGDLQTLALEVARQKRGIVDQCCTSICSLYQLENYCN", ok2[0]->getBaseSequence());
		Assert::AreEqual("MNCYNELQYLSCISTCCQDVIGRKQRAVELALTQLDGPSGGLELQEVQPDEVERRSKPTYFFGREGCVLYLAEVLHPGCLHQKVFAQTPKPEWLALLALLPLFHVLLA", ok2[1]->getBaseSequence());
		Assert::AreEqual(ok2[0]->getDisulfideBonds().size(), ok2[1]->getDisulfideBonds().size());
		Assert::AreEqual(ok2[0]->getProteolysisProducts().size(), ok2[1]->getProteolysisProducts().size());
		for (auto bond : ok2[0]->getDisulfideBonds())
		{
			Assert::AreEqual(ok2[0]->getBaseSequence()[bond->getOneBasedBeginPosition() - 1], 'C');
			Assert::AreEqual(ok2[0]->getBaseSequence()[bond->getOneBasedEndPosition() - 1], 'C');
		}
		for (auto bond : ok2[1]->getDisulfideBonds())
		{
			Assert::AreEqual(ok2[1]->getBaseSequence()[bond->getOneBasedBeginPosition() - 1], 'C');
			Assert::AreEqual(ok2[1]->getBaseSequence()[bond->getOneBasedEndPosition() - 1], 'C');
		}
	}

	void TestProteinReader::TestSlideDecoyXML()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		auto nice = std::vector<Modification*>();
		Dictionary<std::string, Modification*> un;
		auto ok2 = ProteinDbLoader::LoadProteinXML(testdir + "/disulfidetests.xml", true, DecoyType::Slide, nice, false, std::vector<std::string> {"exclude_me"}, un);

		Assert::AreEqual("MALLVHFLPLLALLALWEPKPTQAFVKQHLCGPHLVEALYLVCGERGFFYTPKSRREVEDPQVEQLELGGSPGDLQTLALEVARQKRGIVDQCCTSICSLYQLENYCN", ok2[0]->getBaseSequence());
		Assert::AreEqual("MTKAEVLQLLAGLHLVHALYAVLGVRFFPYLPLSARWVPDPQQEFLKLHGCPPDLQELLLLVCREKGGFVTQKCRSECELPQVEQYENGCSNGLLYTSAIETACQDRI", ok2[1]->getBaseSequence());
		Assert::AreEqual(ok2[0]->getDisulfideBonds().size(), ok2[1]->getDisulfideBonds().size());
		Assert::AreEqual(ok2[0]->getProteolysisProducts().size(), ok2[1]->getProteolysisProducts().size());
		for (int i = 0; i < ok2[0]->getProteolysisProducts().size(); i++)
		{
			Assert::AreEqual(ok2[0]->getProteolysisProducts()[i].getOneBasedBeginPosition(), ok2[1]->getProteolysisProducts()[i].getOneBasedBeginPosition());
			Assert::AreEqual(ok2[0]->getProteolysisProducts()[i].getOneBasedEndPosition(), ok2[1]->getProteolysisProducts()[i].getOneBasedEndPosition());
		}
		for (auto bond : ok2[0]->getDisulfideBonds())
		{
			Assert::AreEqual(ok2[0]->getBaseSequence()[bond->getOneBasedBeginPosition() - 1], 'C');
			Assert::AreEqual(ok2[0]->getBaseSequence()[bond->getOneBasedEndPosition() - 1], 'C');
		}
		for (auto bond : ok2[1]->getDisulfideBonds())
		{
			Assert::AreEqual(ok2[1]->getBaseSequence()[bond->getOneBasedBeginPosition() - 1], 'C');
			Assert::AreEqual(ok2[1]->getBaseSequence()[bond->getOneBasedEndPosition() - 1], 'C');
		}
	}

	void TestProteinReader::TestReverseDecoyFasta()
	{
		std::string testdir=std::experimental::filesystem::current_path().string();
		std::vector<std::string> a;
		std::vector<Protein*> prots = ProteinDbLoader::LoadProteinFasta(testdir + "/fasta.fasta", true, DecoyType::Reverse, false, ProteinDbLoader::UniprotAccessionRegex, ProteinDbLoader::UniprotFullNameRegex, ProteinDbLoader::UniprotAccessionRegex, ProteinDbLoader::UniprotGeneNameRegex, ProteinDbLoader::UniprotOrganismRegex, a);

		Assert::AreEqual("MSGRGKGGKGLGKGGAKRHRKVLRDNIQGITKPAIRRLARRGGVKRISGLIYEETRGVLKVFLENVIRDAVTYTEHAKRKTVTAMDVVYALKRQGRTLYGFGG", prots[0]->getBaseSequence());
		Assert::AreEqual("MGGFGYLTRGQRKLAYVVDMATVTKRKAHETYTVADRIVNELFVKLVGRTEEYILGSIRKVGGRRALRRIAPKTIGQINDRLVKRHRKAGGKGLGKGGKGRGS", prots[1]->getBaseSequence());
	}

	void TestProteinReader::TestSlideDecoyFasta()
	{

		std::string testdir=std::experimental::filesystem::current_path().string();
		std::vector<std::string> a;
		std::vector<Protein*> prots = ProteinDbLoader::LoadProteinFasta(testdir + "/fasta.fasta", true, DecoyType::Slide, false, ProteinDbLoader::UniprotAccessionRegex, ProteinDbLoader::UniprotFullNameRegex, ProteinDbLoader::UniprotAccessionRegex, ProteinDbLoader::UniprotGeneNameRegex, ProteinDbLoader::UniprotOrganismRegex, a);

		Assert::AreEqual("MSGRGKGGKGLGKGGAKRHRKVLRDNIQGITKPAIRRLARRGGVKRISGLIYEETRGVLKVFLENVIRDAVTYTEHAKRKTVTAMDVVYALKRQGRTLYGFGG", prots[0]->getBaseSequence());
		Assert::AreEqual("MVRRRNAQGIGKGAGRKLRRSGGVGRGSKLLYKEGRKVHKKFLEDVIRGATTPTIHRKAKRVGAKDIVGAIKEQTRGLLGVGLGNFIYDTVGYRELAYRVTMT", prots[1]->getBaseSequence());
	}

#endif
}
