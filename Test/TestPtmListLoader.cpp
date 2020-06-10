#include "TestPtmListLoader.h"
#include "../UsefulProteomicsDatabases/PtmListLoader.h"
#include "../Proteomics/Modifications/Modification.h"
#include "../MzLibUtil/MzLibException.h"

using namespace MzLibUtil;
using namespace Proteomics;
using namespace UsefulProteomicsDatabases;

#include "Assert.h"
#include <experimental/filesystem>

int main ( int argc, char **argv )
{
    int i=0;
    
    std::cout << i << ". PeriodicTableLoader" << std::endl;    
    const std::string elfile="elements.dat";
    const std::string &elr=elfile;
    UsefulProteomicsDatabases::PeriodicTableLoader::Load (elr);
    
    std::cout << ++i << ". SampleModFileLoading" << std::endl;    
    Test::TestPtmListLoader::SampleModFileLoading();
     
    //[TestCase("CommonArtifacts.txt", 33)]
    //[TestCase("CommonBiological.txt", 35)] 
    std::cout << ++i << ". Test_ReadAllModsFromFile (CommonArtifacts.txt)" << std::endl;    
    Test::TestPtmListLoader::Test_ReadAllModsFromFile("CommonArtifacts.txt", 33);

    std::cout << ++i << ". Test_ReadAllModsFromFile (CommonBiological.txt)" << std::endl;    
    Test::TestPtmListLoader::Test_ReadAllModsFromFile("CommonBiological.txt", 35);
    
#ifdef LATER
    //[TestCase("CommonArtifacts.txt")]
    //[TestCase("CommonBiological.txt")] 
    std::cout << ++i << ". Test_ModsFromFileAreSorted (CommonArtifacts.txt) " << std::endl;    
    Test::TestPtmListLoader::Test_ModsFromFileAreSorted("CommonArtifacts.txt");

    std::cout << ++i << ". Test_ModsFromFileAreSorted (CommonBiological.txt) " << std::endl;    
    Test::TestPtmListLoader::Test_ModsFromFileAreSorted("CommonBiological.txt");
    
    std::cout << ++i << ". Test_ModsWithComments" << std::endl;    
    Test::TestPtmListLoader::Test_ModsWithComments();
    
    //[TestCase("sampleModFileFail1.txt")]
    //[TestCase("sampleModFileFail2.txt")]
    //[TestCase("sampleModFileFail5.txt")]
    //[TestCase("sampleModFileFail6.txt")]
    //[TestCase("sampleModFileFail_missingPosition.txt")]
    //[TestCase("sampleModFileFail_missingChemicalFormulaAndMonoisotopicMass.txt")] 
    std::cout << ++i << ". SampleModFileLoadingFail1General (sampleModFileFail1.txt)" << std::endl;    
    Test::TestPtmListLoader::SampleModFileLoadingFail1General("sampleModFileFail1.txt");

    std::cout << ++i << ". SampleModFileLoadingFail1General (sampleModFileFail2.txt)" << std::endl;    
    Test::TestPtmListLoader::SampleModFileLoadingFail1General("sampleModFileFail2.txt");

    std::cout << ++i << ". SampleModFileLoadingFail1General (sampleModFileFail5.txt)" << std::endl;    
    Test::TestPtmListLoader::SampleModFileLoadingFail1General("sampleModFileFail5.txt");

    std::cout << ++i << ". SampleModFileLoadingFail1General (sampleModFileFail6.txt)" << std::endl;    
    Test::TestPtmListLoader::SampleModFileLoadingFail1General("sampleModFileFail6.txt");

    std::cout << ++i << ". SampleModFileLoadingFail1General (sampleModFileFail_missingPosition.txt)" << std::endl;    
    Test::TestPtmListLoader::SampleModFileLoadingFail1General("sampleModFileFail_missingPosition.txt");

    std::cout << ++i << ". SampleModFileLoadingFail1General (sampleModFileFail_missingChemicalFormulaAndMonoisotopicMass.txt)" << std::endl;    
    Test::TestPtmListLoader::SampleModFileLoadingFail1General("sampleModFileFail_missingChemicalFormulaAndMonoisotopicMass.txt");

    
    std::cout << ++i << ". PTMListLoader_ModWithComments_Equals_ModWithoutComments" << std::endl;    
    Test::TestPtmListLoader::PTMListLoader_ModWithComments_Equals_ModWithoutComments();
    
    //[TestCase("sampleModFileFail3.txt", "Input string for chemical formula was in an incorrect format")]
    //[TestCase("m.txt", "0 or 238.229666 is not a valid monoisotopic mass")] 
    std::cout << ++i << ". SampleModFileLoadingFail3General (sampleModFileFail3.txt)" << std::endl;    
    Test::TestPtmListLoader::SampleModFileLoadingFail3General("sampleModFileFail3.txt",
                                                              "Input string for chemical formula was in an incorrect format");

    std::cout << ++i << ". SampleModFileLoadingFail3General (m.txt)" << std::endl;    
    Test::TestPtmListLoader::SampleModFileLoadingFail3General("m.txt", "0 or 238.229666 is not a valid monoisotopic mass");
    
    //[TestCase("sampleModFileDouble.txt")]
    //[TestCase("sampleModFileDouble2.txt")] 
    std::cout << ++i << ". CompactFormReadingGeneral (sampleModFileDouble.txt)" << std::endl;    
    Test::TestPtmListLoader::CompactFormReadingGeneral("sampleModFileDouble.txt");

    std::cout << ++i << ". CompactFormReadingGeneral (sampleModFileDouble2.txt)" << std::endl;    
    Test::TestPtmListLoader::CompactFormReadingGeneral("sampleModFileDouble2.txt");
        
    std::cout << ++i << ". TestReadingInvalidModifications" << std::endl;    
    Test::TestPtmListLoader::TestReadingInvalidModifications();
    
    std::cout << ++i << ". TestReadingIdWithMotif" << std::endl;    
    Test::TestPtmListLoader::TestReadingIdWithMotif();
    
    std::cout << ++i << ". TestInvalidModTypeError" << std::endl;    
    Test::TestPtmListLoader::TestInvalidModTypeError();
#endif    
    return 0;
}

namespace Test
{

    void TestPtmListLoader::SampleModFileLoading()
    {
        std::vector<std::tuple<Modification*, std::string>> errors;
        std::string testdir=std::experimental::filesystem::current_path().string();
        PtmListLoader::ReadModsFromFile(testdir + "/DatabaseTests/sampleModFile.txt", errors);
    }

    void TestPtmListLoader::Test_ReadAllModsFromFile(const std::string filename, int modCount)
    {
        std::string testdir=std::experimental::filesystem::current_path().string();
        std::string testModificationsFileLocation = testdir +  "/ModificationTests/" + filename;
        std::vector<std::tuple<Modification*, std::string>> errors;
        auto a = PtmListLoader::ReadModsFromFile(testModificationsFileLocation, errors);
        Assert::AreEqual(modCount, (int)a.size());
    }

#ifdef LATER
    void TestPtmListLoader::Test_ModsFromFileAreSorted(const std::string filename)
    {
        std::string testdir=std::experimental::filesystem::current_path().string();
        std::string testModificationsFileLocation = testdir + "/ModificationTests/" + filename;
        std::vector<std::tuple<Modification*, std::string>> errors;
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
        std::string testdir=std::experimental::filesystem::current_path().string();
        std::string testModificationsFileLocation = testdir + "/ModificationTests/ModsWithComments.txt";
        std::vector<std::tuple<Modification*, std::string>> errors;
        auto a = PtmListLoader::ReadModsFromFile(testModificationsFileLocation, errors).ToList();
        Assert::AreEqual(4, a->Select([&] (std::any m)
        {
            m::IdWithMotif;
        }).ToList()->Count);


        Assert::AreEqual("Deamidation on N", a[0].IdWithMotif.ToString());
        Assert::AreEqual("Sodium on D", a[2].IdWithMotif.ToString()); //this has trailing whitespace that shouldn't be in the name

        //Make sure comments are okay on DR key and that key value pairs are still split correctly
        Modification *someMod = a[2];
        Modification *test = someMod;
        auto residValueTest = test->getDatabaseReference().First()->Value->First();
        auto residKeyTest = test->getDatabaseReference().First().Key;
        Assert::AreEqual("RESID", residKeyTest);
        Assert::AreEqual("AA0441", residValueTest);
    }

    void TestPtmListLoader::SampleModFileLoadingFail1General(const std::string filename)
    {
        std::string testdir=std::experimental::filesystem::current_path().string();
        std::vector<std::tuple<Modification*, std::string>> errors;
        auto a = PtmListLoader::ReadModsFromFile(testdir + "/DatabaseTests/" + filename, errors); //.ToList();
        Assert::AreEqual(0, a->Count);
    }

    void TestPtmListLoader::PTMListLoader_ModWithComments_Equals_ModWithoutComments()
    {
        std::string testdir=std::experimental::filesystem::current_path().string();
        std::vector<std::tuple<Modification*, std::string>> errors;
        auto a = PtmListLoader::ReadModsFromFile(testdir + "/DatabaseTests/SampleMod_Comments.txt", errors);//.ToList();
        std::vector<std::tuple<Modification*, std::string>> errors2;
        auto b = PtmListLoader::ReadModsFromFile(testdir + "/DatabaseTests/SampleMod_NoComments.txt", errors2);//.ToList();
        Assert::IsTrue(a->First()->Equals(b->First()));
    }

    void TestPtmListLoader::SampleModFileLoadingFail3General(const std::string filename, const std::string errorMessage)
    {
        std::string testdir=std::experimental::filesystem::current_path().string();
        Assert::IsTrue([&] ()
        {
            std::vector<std::tuple<Modification*, std::string>> errors;
            PtmListLoader::ReadModsFromFile(testdir + "/DatabaseTests/" + filename, errors);//.ToList();
        }, Throws::TypeOf<MzLibException*>().With::Property("Message").EqualTo(errorMessage));
    }

    void TestPtmListLoader::CompactFormReadingGeneral(const std::string &filename)
    {
        std::string testdir=std::experimental::filesystem::current_path().string();
        std::vector<std::tuple<Modification*, std::string>> errors;
        Assert::AreEqual(2, PtmListLoader::ReadModsFromFile(testdir + "/DatabaseTests/" + filename), errors).size());
    }

    void TestPtmListLoader::TestReadingInvalidModifications()
    {
        std::string testdir=std::experimental::filesystem::current_path().string();
        std::string modText = std::string("ID   mod\r\nMT   type\r\nPP   Anywhere.\r\nTG   X\r\nCF   H1\r\n") + R"(//)";
        std::vector<std::tuple<Modification*, std::string>> errors1;
        auto mods = PtmListLoader::ReadModsFromString(modText, errors1);
        Assert::AreEqual(1, mods->Count());
        Assert::AreEqual(0, errors1->Count);

        modText = std::string("ID   mod\r\nMT   type\r\nPP   Anywhere.\r\nTG   X\r\n") + R"(//)"; // no monoisotopic mass, so invalid
        std::vector<std::tuple<Modification*, std::string>> errors2;
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
        std::string testdir=std::experimental::filesystem::current_path().string();
        std::string modText = "ID   Detached EVK or XleDK\r\nPP   Peptide N-terminal.\r\nTG   evkX or vekX or ldkX or dlkX or idkX or dikX\r\nMT   Detached\r\nNL   C16H28N4O5\r\nCF   C16H28N4O5\r\n //)";

        std::string path = testdir + "/detacher.txt";
        std::vector<std::string> tmpvec ={modText};
        File::WriteAllLines(path, tmpvec);

        std::vector<std::tuple<Modification*, std::string>> errors;
        auto mods = PtmListLoader::ReadModsFromFile(path, errors);//.ToList();
        auto motifs = mods->Select([&] (std::any p)
        {
            p::Target->ToString();
        }).Distinct().ToList();
        auto ids = mods->Select([&] (std::any p)
        {
            p::IdWithMotif;
        }).Distinct().ToList();

        Assert::IsTrue(mods->Count == 6);
        Assert::IsTrue(motifs->Count == 6);
        Assert::IsTrue(ids->Count == 6);
    }

    void TestPtmListLoader::TestInvalidModTypeError()
    {
        std::string testdir=std::experimental::filesystem::current_path().string();
        std::string mod = "ID   Deamidation\r\nTG   N or Q\r\nPP   Anywhere.\r\nMT   Mod:\r\nCF   H-1 N-1 O1\r\n//";
        std::string filepath = testdir + "/TestInvalidModTypeError/ptmlist.txt";
        FileSystem::createDirectory(Directory::GetParent(filepath)->FullName);
        std::vector<std::string> tmpvec = {mod};
        File::WriteAllLines(filepath, tmpvec);

        std::vector<std::tuple<Modification*, std::string>> warnings;
        auto ptms = PtmListLoader::ReadModsFromFile(filepath, warnings);//.ToList();
        Assert::IsTrue(ptms->Count == 0);
        Assert::IsTrue(warnings->Count == 2);

        Assert::IsTrue(warnings::First().Item2->Contains("Modification type cannot contain ':'!"));
    }
#endif

}
