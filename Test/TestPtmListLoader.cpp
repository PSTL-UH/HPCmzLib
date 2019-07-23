#include "TestPtmListLoader.h"
#include "../UsefulProteomicsDatabases/PtmListLoader.h"
#include "../Proteomics/Modifications/Modification.h"
#include "../MzLibUtil/MzLibException.h"

using namespace MzLibUtil;
using namespace NUnit::Framework;
using namespace Proteomics;
using namespace UsefulProteomicsDatabases;
namespace Stopwatch = System::Diagnostics::Stopwatch;

namespace Test
{

System::Diagnostics::Stopwatch *TestPtmListLoader::privateStopwatch;

    Stopwatch *TestPtmListLoader::getStopwatch()
    {
        return privateStopwatch;
    }

    void TestPtmListLoader::setStopwatch(Stopwatch *value)
    {
        privateStopwatch = value;
    }

    void TestPtmListLoader::Setuppp()
    {
        Stopwatch tempVar();
        setStopwatch(&tempVar);
        getStopwatch()->Start();
    }

    void TestPtmListLoader::TearDown()
    {
        std::cout << StringHelper::formatSimple("Analysis time: {0}h {1}m {2}s", getStopwatch()->Elapsed.Hours, getStopwatch()->Elapsed.Minutes, getStopwatch()->Elapsed.Seconds) << std::endl;
    }

    void TestPtmListLoader::SampleModFileLoading()
    {
        std::vector<(Modification, string)> errors;
        PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", "sampleModFile.txt"), errors);
    }

    void TestPtmListLoader::Test_ReadAllModsFromFile(const std::string &filename, int modCount)
    {
        std::string testModificationsFileLocation = FileSystem::combine(TestContext::CurrentContext->TestDirectory, "ModificationTests", filename);
        std::vector<(Modification, string)> errors;
        auto a = PtmListLoader::ReadModsFromFile(testModificationsFileLocation, errors);
        Assert::AreEqual(modCount, a->Count());
    }

    void TestPtmListLoader::Test_ModsFromFileAreSorted(const std::string &filename)
    {
        std::string testModificationsFileLocation = FileSystem::combine(TestContext::CurrentContext->TestDirectory, "ModificationTests", filename);
        std::vector<(Modification, string)> errors;
        auto a = PtmListLoader::ReadModsFromFile(testModificationsFileLocation, errors);

        std::string id1 = a->First().IdWithMotif;
        for (std::string modId : a->Select([&] (std::any m)
        {
            m::IdWithMotif;
        }))
        {
            Assert::GreaterOrEqual(modId, id1);
        }
    }

    void TestPtmListLoader::Test_ModsWithComments()
    {
        std::string testModificationsFileLocation = FileSystem::combine(TestContext::CurrentContext->TestDirectory, "ModificationTests", R"(ModsWithComments.txt)");
        std::vector<(Modification, string)> errors;
        auto a = PtmListLoader::ReadModsFromFile(testModificationsFileLocation, errors).ToList();
        Assert::AreEqual(4, a->Select([&] (std::any m)
        {
            m::IdWithMotif;
        }).ToList()->Count);

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual("Deamidation on N", a[0].IdWithMotif.ToString());
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual("Sodium on D", a[2].IdWithMotif.ToString()); //this has trailing whitespace that shouldn't be in the name

        //Make sure comments are okay on DR key and that key value pairs are still split correctly
        Modification *someMod = a[2];
        Modification *test = someMod;
        auto residValueTest = test->getDatabaseReference().First()->Value->First();
        auto residKeyTest = test->getDatabaseReference().First().Key;
        Assert::AreEqual("RESID", residKeyTest);
        Assert::AreEqual("AA0441", residValueTest);
    }

    void TestPtmListLoader::SampleModFileLoadingFail1General(const std::string &filename)
    {
        std::vector<(Modification, string)> errors;
        auto a = PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", filename), errors).ToList();
        Assert::AreEqual(0, a->Count);
    }

    void TestPtmListLoader::PTMListLoader_ModWithComments_Equals_ModWithoutComments()
    {
        std::vector<(Modification, string)> errors;
        auto a = PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", "SampleMod_Comments.txt"), errors).ToList();
        std::vector<(Modification, string)> errors2;
        auto b = PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", "SampleMod_NoComments.txt"), errors2).ToList();
        Assert::IsTrue(a->First()->Equals(b->First()));
    }

    void TestPtmListLoader::SampleModFileLoadingFail3General(const std::string &filename, const std::string &errorMessage)
    {
        Assert::That([&] ()
        {
            std::vector<(Modification, string)> errors;
            PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", filename), errors).ToList();
        }, Throws::TypeOf<MzLibException*>().With::Property("Message").EqualTo(errorMessage));
    }

    void TestPtmListLoader::CompactFormReadingGeneral(const std::string &filename)
    {
        std::vector<(Modification, string)> errors;
        Assert::AreEqual(2, PtmListLoader::ReadModsFromFile(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DatabaseTests", filename), errors).size()());
    }

    void TestPtmListLoader::TestReadingInvalidModifications()
    {
        std::string modText = std::string("ID   mod\r\nMT   type\r\nPP   Anywhere.\r\nTG   X\r\nCF   H1\r\n") + R"(//)";
        std::vector<(Modification, string)> errors1;
        auto mods = PtmListLoader::ReadModsFromString(modText, errors1);
        Assert::AreEqual(1, mods->Count());
        Assert::AreEqual(0, errors1->Count);

        modText = std::string("ID   mod\r\nMT   type\r\nPP   Anywhere.\r\nTG   X\r\n") + R"(//)"; // no monoisotopic mass, so invalid
        std::vector<(Modification, string)> errors2;
        mods = PtmListLoader::ReadModsFromString(modText, errors2);
        Assert::AreEqual(0, mods->Count());
        Assert::AreEqual(1, errors2->Count);
        Assert::IsFalse(errors2::Single().Item1->ValidModification);
        Assert::IsTrue(errors2::Single().Item2->Split({"\r\n"}, StringSplitOptions::None)->Any([&] (std::any x)
        {
            x->StartsWith("#");
        })); // has an error comment
    }

    void TestPtmListLoader::TestReadingIdWithMotif()
    {
        std::string modText = std::string("ID   Detached EVK or XleDK\r\nPP   Peptide N-terminal.\r\nTG   evkX or vekX or ldkX or dlkX or idkX or dikX\r\nMT   Detached\r\nNL   C16H28N4O5\r\nCF   C16H28N4O5\r\n") + R"(//)";

        std::string path = FileSystem::combine(TestContext::CurrentContext->TestDirectory, "detacher.txt");
        File::WriteAllLines(path, std::vector<std::string> {modText});

        std::vector<(Modification, string)> errors;
        auto mods = PtmListLoader::ReadModsFromFile(path, errors).ToList();
        auto motifs = mods->Select([&] (std::any p)
        {
            p::Target->ToString();
        }).Distinct().ToList();
        auto ids = mods->Select([&] (std::any p)
        {
            p::IdWithMotif;
        }).Distinct().ToList();

        Assert::That(mods->Count == 6);
        Assert::That(motifs->Count == 6);
        Assert::That(ids->Count == 6);
    }

    void TestPtmListLoader::TestInvalidModTypeError()
    {
        std::string mod = "ID   Deamidation\r\nTG   N or Q\r\nPP   Anywhere.\r\nMT   Mod:\r\nCF   H-1 N-1 O1\r\n//";
        std::string filepath = FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(TestInvalidModTypeError\ptmlist.txt)");
        FileSystem::createDirectory(Directory::GetParent(filepath)->FullName);
        File::WriteAllLines(filepath, std::vector<std::string> {mod});

        std::vector<(Modification, string)> warnings;
        auto ptms = PtmListLoader::ReadModsFromFile(filepath, warnings).ToList();
        Assert::That(ptms->Count == 0);
        Assert::That(warnings->Count == 2);

        Assert::That(warnings::First().Item2->Contains("Modification type cannot contain ':'!"));
    }
}
