#include "DatabaseLoaderTests.h"
#include "../Proteomics/ModificationWithMassAndCf.h"
#include "../UsefulProteomicsDatabases/PtmListLoader.h"
#include "../UsefulProteomicsDatabases/Loaders.h"
#include "../Chemistry/PeriodicTable.h"
#include "../UsefulProteomicsDatabases/Generated/UsefulProteomicsDatabases.Generated.oboTerm.h"
#include "../Proteomics/ModificationWithMass.h"
#include "../MzLibUtil/MzLibException.h"
#include "../Proteomics/DatabaseReference.h"
#include "../Proteomics/DisulfideBond.h"
#include "../Proteomics/Modification.h"
#include "../Proteomics/Protein.h"
#include "../Proteomics/SequenceVariation.h"
#include "../UsefulProteomicsDatabases/ProteinDbWriter.h"
#include "../UsefulProteomicsDatabases/DecoyType.h"
#include "../UsefulProteomicsDatabases/ProteinDbLoader.h"
#include "../Proteomics/ModificationMotif.h"
#include "../Proteomics/TerminusLocalization.h"

using namespace Chemistry;
using namespace MzLibUtil;
using namespace NUnit::Framework;
using namespace Proteomics;
using namespace UsefulProteomicsDatabases;

namespace Test {

    void DatabaseLoaderTests::LoadModWithNl() {
        auto hah = dynamic_cast<ModificationWithMassAndCf*>(PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "cfInNL.txt")).front());
        Assert::AreEqual(2, hah->neutralLosses.size());
    }

    void DatabaseLoaderTests::TestUpdateUnimod() {
        auto unimodLocation = FileSystem::combine(TestContext::CurrentContext->TestDirectory, "unimod_tables.xml");
        Loaders::UpdateUnimod(unimodLocation);
        Loaders::UpdateUnimod(unimodLocation);
    }

    void DatabaseLoaderTests::TestUpdatePsiMod() {
        auto psimodLocation = FileSystem::combine(TestContext::CurrentContext->TestDirectory, "lal.xml");
        Loaders::UpdatePsiMod(psimodLocation);
        Loaders::UpdatePsiMod(psimodLocation);
    }

    void DatabaseLoaderTests::TestUpdateElements() {
        auto elementLocation = FileSystem::combine(TestContext::CurrentContext->TestDirectory, "lal.dat");
        Loaders::UpdateElements(elementLocation);
        Loaders::UpdateElements(elementLocation);
        Assert::IsTrue(PeriodicTable::ValidateAbundances(1e-15));
        Assert::IsTrue(PeriodicTable::ValidateAverageMasses(1e-2));
    }

    void DatabaseLoaderTests::TestUpdateUniprot() {
        auto uniprotLocation = FileSystem::combine(TestContext::CurrentContext->TestDirectory, "ptmlist.txt");
        Loaders::UpdateUniprot(uniprotLocation);
        Loaders::UpdateUniprot(uniprotLocation);
    }

    void DatabaseLoaderTests::FilesEqualHash() {
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

    void DatabaseLoaderTests::FilesLoading() {
        Loaders::LoadElements(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "elements2.dat"));

        auto unimodMods = Loaders::LoadUnimod(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "unimod_tables2.xml")).ToList();

        auto psiModDeserialized = Loaders::LoadPsiMod(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "PSI-MOD.obo2.xml"));

        // N6,N6,N6-trimethyllysine
        auto trimethylLysine = psiModDeserialized->getItems().OfType<UsefulProteomicsDatabases::Generated::oboTerm*>().First([&] (std::any b) {
            b::id->Equals("MOD:00083");
        });
        Assert::AreEqual("1+", trimethylLysine->xref_analog.First([&] (std::any b) {
            b::dbname->Equals("FormalCharge");
        }).name);

        // Phosphoserine
        Assert::IsFalse(psiModDeserialized->getItems().OfType<UsefulProteomicsDatabases::Generated::oboTerm*>().First([&] (std::any b) {
            b::id->Equals("MOD:00046");
        }).xref_analog.Any([&] (std::any b) {
            b::dbname->Equals("FormalCharge");
        }));

        std::unordered_map<std::string, int> formalChargesDictionary = Loaders::GetFormalChargesDictionary(psiModDeserialized);

        auto uniprotPtms = Loaders::LoadUniprot(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "ptmlist2.txt"), formalChargesDictionary).ToList();

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (StreamWriter w = new StreamWriter(Path.Combine(TestContext.CurrentContext.TestDirectory, "test.txt")))
        {
            StreamWriter w = StreamWriter(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "test.txt"));
            for (auto nice : uniprotPtms) {
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                w.WriteLine(nice.ToString());
                w.WriteLine("//");
            }
            for (auto nice : unimodMods) {
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
                w.WriteLine(nice.ToString());
                w.WriteLine("//");
            }
        }

        auto sampleModList = PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "test.txt")).ToList();

        std::string stringRepresentation = "ID   (3R)-3-hydroxyarginine\r\nMT   UniProt\r\nPP   Anywhere.\r\nDR   RESID; AA0601\r\nDR   PSI-MOD; MOD:01956\r\nDR   UniProt; PTM-0476\r\nTG   R\r\nMM   15.994915\r\nCF   O";
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
        Assert::AreEqual(stringRepresentation, sampleModList.front().ToString());

        // N,N,N-trimethylalanine
        Assert::IsTrue((dynamic_cast<ModificationWithMass*>(sampleModList[156]))->monoisotopicMass > 42);
        Assert::IsTrue((dynamic_cast<ModificationWithMass*>(sampleModList[156]))->monoisotopicMass < 43);
    }

    void DatabaseLoaderTests::SampleModFileLoading() {
        PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "sampleModFile.txt"));
    }

    void DatabaseLoaderTests::SampleModFileLoadingFail1() {
        Assert::That([&] () {
            PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "sampleModFileFail1.txt")).ToList();
        }, Throws::TypeOf<MzLibException*>().With::Property("Message").EqualTo("Could not get motif from NxS"));
    }

    void DatabaseLoaderTests::SampleModFileLoadingFail2() {
        Assert::That([&] () {
            PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "sampleModFileFail2.txt")).ToList();
        }, Throws::TypeOf<MzLibException*>().With::Property("Message").EqualTo("Could not get modification site from Anyplace."));
    }

    void DatabaseLoaderTests::SampleModFileLoadingFail3() {
        Assert::That([&] () {
            PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "sampleModFileFail3.txt")).ToList();
        }, Throws::TypeOf<MzLibException*>().With::Property("Message").EqualTo("Input string for chemical formula was in an incorrect format: $%#$%"));
    }

    void DatabaseLoaderTests::SampleModFileLoadingFail4() {
        Assert::That([&] () {
            PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "m.txt")).ToList();
        }, Throws::TypeOf<MzLibException*>().With::Property("Message").EqualTo("0 or 238.229666 is not a valid monoisotopic mass"));
    }

    void DatabaseLoaderTests::SampleModFileLoadingFail5() {
        Assert::That([&] () {
            PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "sampleModFileFail5.txt")).ToList();
        }, Throws::TypeOf<MzLibException*>().With::Property("Message").EqualTo("id is null"));
    }

    void DatabaseLoaderTests::SampleModFileLoadingFail6() {
        Assert::That([&] () {
            PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "sampleModFileFail6.txt")).ToList();
        }, Throws::TypeOf<MzLibException*>().With::Property("Message").EqualTo("modificationType of lalaMod is null"));
    }

    void DatabaseLoaderTests::CompactFormReading() {
        Assert::AreEqual(2, PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "sampleModFileDouble.txt")).size()());
    }

    void DatabaseLoaderTests::CompactFormReading2() {
        Assert::AreEqual(2, PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "sampleModFileDouble2.txt")).size()());
    }

    void DatabaseLoaderTests::Modification_read_write_into_proteinDb() {
        Loaders::LoadElements(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "elements2.dat"));
        auto sampleModList = PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "z.txt")).ToList();
        Assert::AreEqual(1, sampleModList.OfType<ModificationWithMass*>()->Count());
      `  Protein *protein = new Protein("MCSSSSSSSSSS", "accession", std::vector<std::tuple<std::string, std::string>>(), std::unordered_map<int, std::vector<Modification*>> {
            {2, sampleModList.OfType<Modification*>().ToList()}
        },
        nullptr, "name", "full_name", false, false, std::vector<DatabaseReference*>(), std::vector<SequenceVariation*>(), std::vector<DisulfideBond*>());
        Assert::AreEqual(1, protein->getOneBasedPossibleLocalizedModifications()[2].OfType<ModificationWithMass*>()->Count());
        ProteinDbWriter::WriteXmlDatabase(std::unordered_map<std::string, std::unordered_set<std::tuple<int, Modification*>>>(), {protein}, FileSystem::combine(TestContext::CurrentContext->TestDirectory, "test_modifications_with_proteins.xml"));
        Dictionary<std::string, Modification*> um;
        std::vector<Protein*> new_proteins = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "test_modifications_with_proteins.xml"), true, DecoyType::None, std::vector<Modification*>(), false, std::vector<std::string>(), um);
        Assert::AreEqual(1, new_proteins.size());
        Assert::AreEqual(1, new_proteins[0]->getOneBasedPossibleLocalizedModifications().size());
        Assert::AreEqual(1, new_proteins[0]->getOneBasedPossibleLocalizedModifications().SelectMany([&] (std::any kv) {
            kv->Value;
        })->Count());
        Assert::AreEqual("Type", new_proteins[0]->getOneBasedPossibleLocalizedModifications().SelectMany([&] (std::any kv) {
            kv->Value;
        }).OfType<ModificationWithMass*>().First().modificationType);
        Assert::AreEqual("Palmitoylation of C", new_proteins[0]->getOneBasedPossibleLocalizedModifications()[2][0].id);
        Assert::AreEqual(1, new_proteins[0]->getOneBasedPossibleLocalizedModifications()[2].OfType<ModificationWithMass*>()->Count());

        // Check that Modifications were saved after last load
        Assert::AreEqual(1, ProteinDbLoader::GetPtmListFromProteinXml(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(test_modifications_with_proteins.xml)")).size());
        Assert::True(ProteinDbLoader::GetPtmListFromProteinXml(FileSystem::combine(TestContext::CurrentContext->TestDirectory, LR"(test_modifications_with_proteins.xml)"))[0] == new_proteins[0]->getOneBasedPossibleLocalizedModifications().SelectMany([&] (std::any kv) {
            kv->Value;
        }).First());

        //But that we can still read modifications from other protein XMLs that exist
        Assert::AreEqual(0, ProteinDbLoader::GetPtmListFromProteinXml(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "xml.xml")).size());

//C# TO C++ CONVERTER TODO TASK: A 'delete protein' statement was not added since protein was passed to a method or constructor. Handle memory management manually.
    }

    void DatabaseLoaderTests::DoNotWriteSameModTwiceAndDoNotWriteInHeaderSinceDifferent() {
        Loaders::LoadElements(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "elements2.dat"));
        auto sampleModList = PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "z.txt")).ToList();
        Protein *protein = new Protein("MCSSSSSSSSSS", "accession", std::vector<std::tuple<std::string, std::string>>(), std::unordered_map<int, std::vector<Modification*>> {
            {2, sampleModList.OfType<Modification*>().ToList()}
        },
        nullptr, "name", "full_name", false, false, std::vector<DatabaseReference*>(), std::vector<SequenceVariation*>(), std::vector<DisulfideBond*>());
        Assert::AreEqual(1, protein->getOneBasedPossibleLocalizedModifications()[2].OfType<ModificationWithMass*>()->Count());

        std::unordered_map<std::string, std::unordered_set<std::tuple<int, Modification*>>> dictWithThisMod;

        std::unordered_set<std::tuple<int, Modification*>> value;

        auto modReadFromFile = dynamic_cast<ModificationWithMassAndCf*>(sampleModList.front());
        ModificationMotif motif;
        ModificationMotif::TryGetMotif("C", motif);
        ModificationWithMass *newMod = new ModificationWithMassAndCf("Palmitoylation of C", modReadFromFile->modificationType, motif, TerminusLocalization::Any, modReadFromFile->chemicalFormula, std::make_optional(modReadFromFile->monoisotopicMass), nullptr, nullptr, nullptr);

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
        Assert::AreEqual(1, new_proteins[0]->getOneBasedPossibleLocalizedModifications().SelectMany([&] (std::any kv) {
            kv->Value;
        })->Count());

//C# TO C++ CONVERTER TODO TASK: A 'delete newMod' statement was not added since newMod was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete protein' statement was not added since protein was passed to a method or constructor. Handle memory management manually.
    }

    void DatabaseLoaderTests::DoNotWriteSameModTwiceButWriteInHeaderSinceDifferent() {
        Loaders::LoadElements(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "elements2.dat"));
        auto sampleModList = PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "z.txt")).ToList();
        Protein *protein = new Protein("MCSSSSSSSSSS", "accession", std::vector<std::tuple<std::string, std::string>>(), std::unordered_map<int, std::vector<Modification*>> {
            {2, sampleModList.OfType<Modification*>().ToList()}
        },
        nullptr, "name", "full_name", false, false, std::vector<DatabaseReference*>(), std::vector<SequenceVariation*>(), std::vector<DisulfideBond*>());
        Assert::AreEqual(1, protein->getOneBasedPossibleLocalizedModifications()[2].OfType<ModificationWithMass*>()->Count());

        std::unordered_map<std::string, std::unordered_set<std::tuple<int, Modification*>>> dictWithThisMod;

        std::unordered_set<std::tuple<int, Modification*>> value;

        ModificationMotif motif;
        ModificationMotif::TryGetMotif("C", motif);
        ModificationWithMass *newMod = new ModificationWithMass("Palmitoylation of C", "mt", motif, TerminusLocalization::Any, NAN, nullptr, nullptr);

        Assert::AreNotEqual(newMod, sampleModList.front());

        value.insert(std::tuple<int, Modification*>(2, newMod));

        dictWithThisMod.emplace("accession", value);

        auto newModResEntries = ProteinDbWriter::WriteXmlDatabase(dictWithThisMod, std::vector<Protein*> {protein}, FileSystem::combine(TestContext::CurrentContext->TestDirectory, "test_modifications_with_proteins2.xml"));
        Assert::AreEqual(0, newModResEntries.size());
        Dictionary<std::string, Modification*> um;
        std::vector<Protein*> new_proteins = ProteinDbLoader::LoadProteinXML(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "test_modifications_with_proteins2.xml"), true, DecoyType::None, std::vector<Modification*>(), false, std::vector<std::string>(), um);
        Assert::AreEqual(1, new_proteins.size());
        Assert::AreEqual(1, new_proteins[0]->getOneBasedPossibleLocalizedModifications().size());
        Assert::AreEqual(2, new_proteins[0]->getOneBasedPossibleLocalizedModifications().SelectMany([&] (std::any kv) {
            kv->Value;
        })->Count());

//C# TO C++ CONVERTER TODO TASK: A 'delete newMod' statement was not added since newMod was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete protein' statement was not added since protein was passed to a method or constructor. Handle memory management manually.
    }
}
