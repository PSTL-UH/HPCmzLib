#include "TestDatabaseLoaders.h"
#include "../../Proteomics/Modifications/Modification.h"
#include "../../UsefulProteomicsDatabases/PtmListLoader.h"
#include "../../UsefulProteomicsDatabases/DecoyType.h"
#include "../../UsefulProteomicsDatabases/ProteinDbLoader.h"
#include "../../UsefulProteomicsDatabases/Loaders.h"
#include "../../Chemistry/PeriodicTable.h"
#include "../../UsefulProteomicsDatabases/Generated/UsefulProteomicsDatabases.Generated.oboTerm.h"
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
using namespace NUnit::Framework;
using namespace Proteomics;
using namespace UsefulProteomicsDatabases;
namespace Stopwatch = System::Diagnostics::Stopwatch;

namespace Test
{

System::Diagnostics::Stopwatch *TestDatabaseLoaders::privateStopwatch;

    Stopwatch *TestDatabaseLoaders::getStopwatch()
    {
        return privateStopwatch;
    }

    void TestDatabaseLoaders::setStopwatch(Stopwatch *value)
    {
        privateStopwatch = value;
    }

    void TestDatabaseLoaders::Setuppp()
    {
        Stopwatch tempVar();
        setStopwatch(&tempVar);
        getStopwatch()->Start();
    }

    void TestDatabaseLoaders::TearDown()
    {
        std::cout << StringHelper::formatSimple("Analysis time: {0}h {1}m {2}s", getStopwatch()->Elapsed.Hours, getStopwatch()->Elapsed.Minutes, getStopwatch()->Elapsed.Seconds) << std::endl;
    }

    void TestDatabaseLoaders::LoadModWithNl()
    {
        std::vector<(Modification, string)> errors;
        auto hah = dynamic_cast<Modification*>(PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", "cfInNL.txt"), errors).front());
        int count = 0;
        for (auto item : hah->getNeutralLosses())
        {
            for (auto loos : item.Value)
            {
                count++;
            }
        }

        Assert::AreEqual(2, count);
    }

    void TestDatabaseLoaders::LoadOriginalMismatchedModifications()
    {
        std::unordered_map<string, Modification> unknownModifications;
        auto protein = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", "oblm.xml"), true, DecoyType::Reverse, std::vector<Modification>(), false, std::vector<std::string>(), unknownModifications);
        Assert::AreEqual(0, protein[0]->getOneBasedPossibleLocalizedModifications().size());
        auto variant = protein[0]->GetVariantProteins()[0];
        protein[0]->getNonVariantProtein().RestoreUnfilteredModifications();
        Assert::AreEqual(1, protein[0]->getNonVariantProtein().getOneBasedPossibleLocalizedModifications().size());
    }

    void TestDatabaseLoaders::TestUpdateUnimod()
    {
        auto unimodLocation = FileSystem::combine(TestContext::CurrentContext->TestDirectory, "unimod_tables.xml");
        Loaders::UpdateUnimod(unimodLocation);
        Loaders::UpdateUnimod(unimodLocation);
    }

    void TestDatabaseLoaders::TestUpdatePsiMod()
    {
        auto psimodLocation = FileSystem::combine(TestContext::CurrentContext->TestDirectory, "lal.xml");
        Loaders::UpdatePsiMod(psimodLocation);
        Loaders::UpdatePsiMod(psimodLocation);
    }

    void TestDatabaseLoaders::TestUpdateElements()
    {
        auto elementLocation = FileSystem::combine(TestContext::CurrentContext->TestDirectory, "lal.dat");
        Loaders::UpdateElements(elementLocation);
        Loaders::UpdateElements(elementLocation);
        Assert::IsTrue(PeriodicTable::ValidateAbundances(1e-15));
        Assert::IsTrue(PeriodicTable::ValidateAverageMasses(1e-2));
    }

    void TestDatabaseLoaders::TestUpdateUniprot()
    {
        auto uniprotLocation = FileSystem::combine(TestContext::CurrentContext->TestDirectory, "ptmlist.txt");
        Loaders::UpdateUniprot(uniprotLocation);
        Loaders::UpdateUniprot(uniprotLocation);
    }

    void TestDatabaseLoaders::FilesEqualHash()
    {
        auto fake = FileSystem::combine(TestContext::CurrentContext->TestDirectory, "fake.txt");
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (StreamWriter file = new StreamWriter(fake))
        {
            StreamWriter file = StreamWriter(fake);
            file.WriteLine("fake");
        }
        Loaders::UpdateUniprot(fake);
        fake = FileSystem::combine(TestContext::CurrentContext->TestDirectory, "fake1.txt");
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (StreamWriter file = new StreamWriter(fake))
        {
            StreamWriter file = StreamWriter(fake);
            file.WriteLine("fake");
        }
        Loaders::UpdateUnimod(fake);
        fake = FileSystem::combine(TestContext::CurrentContext->TestDirectory, "fake2.txt");
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (StreamWriter file = new StreamWriter(fake))
        {
            StreamWriter file = StreamWriter(fake);
            file.WriteLine("fake");
        }
        Loaders::UpdatePsiMod(fake);
        fake = FileSystem::combine(TestContext::CurrentContext->TestDirectory, "fake3.txt");
//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (StreamWriter file = new StreamWriter(fake))
        {
            StreamWriter file = StreamWriter(fake);
            file.WriteLine("fake");
        }
        Loaders::UpdateElements(fake);
    }

    void TestDatabaseLoaders::FilesLoading()
    {
        Loaders::LoadElements(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "elements2.dat"));

        auto unimodMods = Loaders::LoadUnimod(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "unimod_tables2.xml")).ToList();
        Assert::AreEqual(2642, unimodMods.size()); // UniMod PTM list may be updated at some point, causing the unit test to fail

        std::vector<Modification*> myList = unimodMods.Where([&] (std::any m)
        {
            m::OriginalId->Equals("HexNAc(2)");
        }).ToList();

        Modification *testMod = myList.front();
        int neutralLossCount = 0;
        if (testMod->getNeutralLosses().size() != 0)
        {
            for (auto item : testMod->getNeutralLosses())
            {
                for (auto loss : item.Value)
                {
                    neutralLossCount++;
                }
            }
        }

        Assert::AreEqual(2, neutralLossCount);
        auto psiModDeserialized = Loaders::LoadPsiMod(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "PSI-MOD.obo2.xml"));

        // N6,N6,N6-trimethyllysine
        auto trimethylLysine = psiModDeserialized->getItems().OfType<UsefulProteomicsDatabases::Generated::oboTerm*>().First([&] (std::any b)
        {
            b::id->Equals("MOD:00083");
        });
        Assert::AreEqual("1+", trimethylLysine->xref_analog.First([&] (std::any b)
        {
            b::dbname->Equals("FormalCharge");
        }).name);

        // Phosphoserine
        Assert::IsFalse(psiModDeserialized->getItems().OfType<UsefulProteomicsDatabases::Generated::oboTerm*>().First([&] (std::any b)
        {
            b::id->Equals("MOD:00046");
        }).xref_analog.Any([&] (std::any b)
        {
            b::dbname->Equals("FormalCharge");
        }));

        std::unordered_map<std::string, int> formalChargesDictionary = Loaders::GetFormalChargesDictionary(psiModDeserialized);

        auto uniprotPtms = Loaders::LoadUniprot(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "ptmlist2.txt"), formalChargesDictionary).ToList();
        Assert::AreEqual(340, uniprotPtms.size()()); // UniProt PTM list may be updated at some point, causing the unit test to fail

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (StreamWriter w = new StreamWriter(Path.Combine(TestContext.CurrentContext.TestDirectory, "test.txt")))
        {
            StreamWriter w = StreamWriter(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "test.txt"));
            for (auto nice : uniprotPtms)
            {
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
                w.WriteLine(nice.ToString());
                w.WriteLine("//");
            }
            for (auto nice : unimodMods)
            {
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
                w.WriteLine(nice.ToString());
                w.WriteLine("//");
            }
        }

        std::vector<(Modification, string)> errors;
        auto sampleModList = PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "test.txt"), errors).ToList();

        Assert::AreEqual(2982, sampleModList.size()());

        std::vector<Modification*> myOtherList;
        for (auto mod : sampleModList)
        {
            if (mod->getIdWithMotif() != "" && mod->getIdWithMotif().find("Acetyl") != std::string::npos)
            {
                myOtherList.push_back(mod);
            }
        }

        auto thisMod = myOtherList.front();
        Assert::IsTrue(thisMod->MonoisotopicMass > 42);
        Assert::IsTrue(thisMod->MonoisotopicMass < 43);
    }

    void TestDatabaseLoaders::SampleLoadModWithLongMotif()
    {
        ModificationMotif motif;
        ModificationMotif::TryGetMotif("msgRgk", motif);
        Modification *testMod = new Modification("Asymmetric dimethylarginine", "", "Test", "", motif, "Anywhere.", nullptr, std::make_optional(100.0), std::unordered_map<std::string, std::vector<std::string>>(), std::unordered_map<std::string, std::vector<std::string>>(), std::vector<std::string>(), std::unordered_map<DissociationType, std::vector<double>>(), std::unordered_map<DissociationType, std::vector<double>>(), "");
        std::vector<Modification*> allKnownMods = {testMod};

        Assert::That(testMod->getValidModification());
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::That(testMod->getTarget()->ToString() == "msgRgk");

        std::unordered_map<string, Modification> unk;
        Protein *protein = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", "modified_start.xml"), true, DecoyType::None, allKnownMods, false, std::vector<std::string>(), unk).front();

        Assert::That(StringHelper::startsWith(protein->getBaseSequence(), "MSGRGK"));
        Assert::That(protein->getOneBasedPossibleLocalizedModifications().size() == 1);
        Assert::That(protein->getOneBasedPossibleLocalizedModifications().First()->Value->First() == testMod);

//C# TO C++ CONVERTER TODO TASK: A 'delete testMod' statement was not added since testMod was passed to a method or constructor. Handle memory management manually.
    }

    void TestDatabaseLoaders::SampleModFileLoading()
    {
        std::vector<(Modification, string)> errors;
        PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", "sampleModFile.txt"), errors);
    }

    void TestDatabaseLoaders::SampleModFileLoadingFail1()
    {
        std::vector<(Modification, string)> errors;
        auto b = PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", "sampleModFileFail1.txt"), errors);
        Assert::AreEqual(0, b.size()());
    }

    void TestDatabaseLoaders::SampleModFileLoadingFail2()
    {
        std::vector<(Modification, string)> errors;
        auto b = PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", "sampleModFileFail2.txt"), errors);
        Assert::AreEqual(0, b.size()());
    }

    void TestDatabaseLoaders::SampleModFileLoadingFail3()
    {
        Assert::That([&] ()
        {
            std::vector<(Modification, string)> errors;
            PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", "sampleModFileFail3.txt"), errors).ToList();
        }, Throws::TypeOf<MzLibException*>().With::Property("Message").EqualTo("Input string for chemical formula was in an incorrect format: $%&$%"));
    }

    void TestDatabaseLoaders::SampleModFileLoadingFail4()
    {
        Assert::That([&] ()
        {
            std::vector<(Modification, string)> errors;
            PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", "m.txt"), errors).ToList();
        }, Throws::TypeOf<MzLibException*>().With::Property("Message").EqualTo("0 or 238.229666 is not a valid monoisotopic mass"));
    }

    void TestDatabaseLoaders::SampleModFileLoadingFail5()
    {
        std::vector<(Modification, string)> errors;
        auto b = PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", "sampleModFileFail5.txt"), errors);
        Assert::AreEqual(0, b.size()());
    }

    void TestDatabaseLoaders::SampleModFileLoadingFail6()
    {
        std::vector<(Modification, string)> errors;
        auto b = PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", "sampleModFileFail5.txt"), errors);
        Assert::AreEqual(0, b.size()());
    }

    void TestDatabaseLoaders::CompactFormReading()
    {
        std::vector<(Modification, string)> errors;
        Assert::AreEqual(2, PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", "sampleModFileDouble.txt"), errors).size()());
    }

    void TestDatabaseLoaders::CompactFormReading2()
    {
        std::vector<(Modification, string)> errors;
        Assert::AreEqual(2, PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", "sampleModFileDouble2.txt"), errors).size()());
    }

    void TestDatabaseLoaders::Modification_read_write_into_proteinDb()
    {
        Loaders::LoadElements(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "elements2.dat"));
        std::vector<(Modification, string)> errors;
        auto sampleModList = PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", "z.txt"), errors).ToList();
        Assert::AreEqual(1, sampleModList.OfType<Modification*>()->Count());
        Protein *protein = new Protein("MCSSSSSSSSSS", "accession", "organism", std::vector<std::tuple<std::string, std::string>>(), std::unordered_map<int, std::vector<Modification*>>
        {
            {2, sampleModList.OfType<Modification*>().ToList()}
        },
        nullptr, "name", "full_name", false, false, std::vector<DatabaseReference*>(), std::vector<SequenceVariation*>(), disulfideBonds: std::vector<DisulfideBond*>());
        Assert::AreEqual(1, protein->getOneBasedPossibleLocalizedModifications()[2].OfType<Modification*>()->Count());
        ProteinDbWriter::WriteXmlDatabase(std::unordered_map<std::string, std::unordered_set<std::tuple<int, Modification*>>>(), {protein}, FileSystem::combine(TestContext::CurrentContext->TestDirectory, "test_modifications_with_proteins.xml"));
        Dictionary<std::string, Modification*> um;
        std::vector<Protein*> new_proteins = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "test_modifications_with_proteins.xml"), true, DecoyType::None, std::vector<Modification*>(), false, std::vector<std::string>(), um);
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
        Assert::AreEqual(1, ProteinDbLoader::GetPtmListFromProteinXml(FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(test_modifications_with_proteins.xml)")).size());
        Assert::True(ProteinDbLoader::GetPtmListFromProteinXml(FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(test_modifications_with_proteins.xml)"))[0] == new_proteins[0]->getOneBasedPossibleLocalizedModifications().SelectMany([&] (std::any kv)
        {
            kv->Value;
        }).First());

        //But that we can still read modifications from other protein XMLs that exist
        Assert::AreEqual(0, ProteinDbLoader::GetPtmListFromProteinXml(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", "xml.xml")).size());

        // Check that Modifications were saved after last load
        auto b = ProteinDbLoader::GetPtmListFromProteinXml(FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(test_modifications_with_proteins.xml)"));
        Assert::AreEqual(1, b.size());

        auto c = ProteinDbLoader::GetPtmListFromProteinXml(FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(test_modifications_with_proteins.xml)"))[0];
        auto d = new_proteins[0]->getOneBasedPossibleLocalizedModifications().SelectMany([&] (std::any kv)
        {
            kv->Value;
        }).First();

        Assert::IsTrue(c->Equals(d));

        //But that we can still read modifications from other protein XMLs that exist
        Assert::AreEqual(0, ProteinDbLoader::GetPtmListFromProteinXml(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", "xml.xml")).size());

//C# TO C++ CONVERTER TODO TASK: A 'delete d' statement was not added since d was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete protein' statement was not added since protein was passed to a method or constructor. Handle memory management manually.
    }

    void TestDatabaseLoaders::Test_MetaMorpheusStyleProteinDatabaseWriteAndREad()
    {
        std::string proteinDbFilePath = FileSystem::combine(TestContext::CurrentContext->TestDirectory, "TestProteinSplitAcrossFiles.xml");

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
        Loaders::LoadElements(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "elements2.dat"));
        std::vector<(Modification, string)> errors;
        auto sampleModList = PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", "z.txt"), errors).ToList();
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
        auto newModResEntries = ProteinDbWriter::WriteXmlDatabase(dictWithThisMod, std::vector<Protein*> {protein}, FileSystem::combine(TestContext::CurrentContext->TestDirectory, "test_modifications_with_proteins3.xml"));
        Assert::AreEqual(0, newModResEntries.size());
        Dictionary<std::string, Modification*> um;
        std::vector<Protein*> new_proteins = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "test_modifications_with_proteins3.xml"), true, DecoyType::None, std::vector<Modification*>(), false, std::vector<std::string>(), um);
        Assert::AreEqual(1, new_proteins.size());
        Assert::AreEqual(1, new_proteins[0]->getOneBasedPossibleLocalizedModifications().size());
        Assert::AreEqual(1, new_proteins[0]->getOneBasedPossibleLocalizedModifications().SelectMany([&] (std::any kv)
        {
            kv->Value;
        })->Count());

//C# TO C++ CONVERTER TODO TASK: A 'delete newMod' statement was not added since newMod was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete protein' statement was not added since protein was passed to a method or constructor. Handle memory management manually.
    }

    void TestDatabaseLoaders::TestWritePtmWithNeutralLoss()
    {
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

        ProteinDbWriter::WriteXmlDatabase(std::unordered_map<std::string, std::unordered_set<std::tuple<int, Modification*>>>(), {protein}, FileSystem::combine(TestContext::CurrentContext->TestDirectory, filename));

        // with passed-in mods
        Dictionary<std::string, Modification*> um;
        std::vector<Protein*> new_proteins = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, filename), true, DecoyType::None, {m}, false, std::vector<std::string>(), um);
        Assert::That(new_proteins.front().OneBasedPossibleLocalizedModifications::First()->Value->First().NeutralLosses.First()->Value->Count == 2);

        // should be able to read mod from top of database...
        new_proteins = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, filename), true, DecoyType::None, std::vector<Modification*>(), false, std::vector<std::string>(), um);
        Assert::That(new_proteins.front().OneBasedPossibleLocalizedModifications::First()->Value->First().NeutralLosses.First()->Value->Count == 2);

//C# TO C++ CONVERTER TODO TASK: A 'delete protein' statement was not added since protein was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete m' statement was not added since m was passed to a method or constructor. Handle memory management manually.
    }

    void TestDatabaseLoaders::TestWritePtmWithDiagnosticIons()
    {
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

        ProteinDbWriter::WriteXmlDatabase(std::unordered_map<std::string, std::unordered_set<std::tuple<int, Modification*>>>(), {protein}, FileSystem::combine(TestContext::CurrentContext->TestDirectory, filename));

        // with passed-in mods
        Dictionary<std::string, Modification*> um;
        std::vector<Protein*> new_proteins = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, filename), true, DecoyType::None, {m}, false, std::vector<std::string>(), um);
        Assert::That(new_proteins.front().OneBasedPossibleLocalizedModifications::First()->Value->First().DiagnosticIons.First()->Value->Count == 2);

        // should be able to read mod from top of database...
        new_proteins = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, filename), true, DecoyType::None, std::vector<Modification*>(), false, std::vector<std::string>(), um);
        Assert::That(new_proteins.front().OneBasedPossibleLocalizedModifications::First()->Value->First().DiagnosticIons.First()->Value->Count == 2);

//C# TO C++ CONVERTER TODO TASK: A 'delete protein' statement was not added since protein was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete m' statement was not added since m was passed to a method or constructor. Handle memory management manually.
    }

    void TestDatabaseLoaders::TestWritePtmWithNeutralLossAndDiagnosticIons()
    {
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

        ProteinDbWriter::WriteXmlDatabase(std::unordered_map<std::string, std::unordered_set<std::tuple<int, Modification*>>>(), {protein}, FileSystem::combine(TestContext::CurrentContext->TestDirectory, filename));

        // with passed-in mods
        Dictionary<std::string, Modification*> um;
        std::vector<Protein*> new_proteins = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, filename), true, DecoyType::None, {m}, false, std::vector<std::string>(), um);
        Assert::That(new_proteins.front().OneBasedPossibleLocalizedModifications::First()->Value->First().NeutralLosses.First()->Value->Count == 2);
        Assert::That(new_proteins.front().OneBasedPossibleLocalizedModifications::First()->Value->First().DiagnosticIons.First()->Value->Count == 2);

        // should be able to read mod from top of database...
        new_proteins = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, filename), true, DecoyType::None, std::vector<Modification*>(), false, std::vector<std::string>(), um);
        Assert::That(new_proteins.front().OneBasedPossibleLocalizedModifications::First()->Value->First().NeutralLosses.First()->Value->Count == 2);
        Assert::That(new_proteins.front().OneBasedPossibleLocalizedModifications::First()->Value->First().DiagnosticIons.First()->Value->Count == 2);

//C# TO C++ CONVERTER TODO TASK: A 'delete protein' statement was not added since protein was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete m' statement was not added since m was passed to a method or constructor. Handle memory management manually.
    }
}
