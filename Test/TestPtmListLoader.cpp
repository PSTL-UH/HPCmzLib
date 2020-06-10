#include "TestPtmListLoader.h"
#include "../UsefulProteomicsDatabases/PtmListLoader.h"
#include "../Proteomics/Modifications/Modification.h"
#include "../MzLibUtil/MzLibException.h"

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
    
    std::cout << ++i << ". SampleModFileLoading" << std::endl;    
    Test::TestPtmListLoader::SampleModFileLoading();
     
    //[TestCase("CommonArtifacts.txt", 33)]
    //[TestCase("CommonBiological.txt", 35)] 
    std::cout << ++i << ". Test_ReadAllModsFromFile (CommonArtifacts.txt)" << std::endl;    
    Test::TestPtmListLoader::Test_ReadAllModsFromFile("CommonArtifacts.txt", 33);

    std::cout << ++i << ". Test_ReadAllModsFromFile (CommonBiological.txt)" << std::endl;    
    Test::TestPtmListLoader::Test_ReadAllModsFromFile("CommonBiological.txt", 35);
    
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
    
#ifdef LATER
    //Testcase throws exception

    //[TestCase("sampleModFileFail3.txt", "Input string for chemical formula was in an incorrect format")]
    //[TestCase("m.txt", "0 or 238.229666 is not a valid monoisotopic mass")] 
    std::cout << ++i << ". SampleModFileLoadingFail3General (sampleModFileFail3.txt)" << std::endl;    
    Test::TestPtmListLoader::SampleModFileLoadingFail3General("sampleModFileFail3.txt",
                                                              "Input string for chemical formula was in an incorrect format");

    std::cout << ++i << ". SampleModFileLoadingFail3General (m.txt)" << std::endl;    
    Test::TestPtmListLoader::SampleModFileLoadingFail3General("m.txt", "0 or 238.229666 is not a valid monoisotopic mass");
#endif    

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

    void TestPtmListLoader::Test_ModsFromFileAreSorted(const std::string filename)
    {
        std::string testdir=std::experimental::filesystem::current_path().string();
        std::string testModificationsFileLocation = testdir + "/ModificationTests/" + filename;
        std::vector<std::tuple<Modification*, std::string>> errors;
        auto a = PtmListLoader::ReadModsFromFile(testModificationsFileLocation, errors);

        std::string id1 = a.front()->getIdWithMotif();
#ifdef ORIG
        for (std::string modId : a->Select([&] (std::any m)
        {
            m::IdWithMotif;
        }))
        {
            Assert::GreaterOrEqual(modId, id1);
        }
#endif
        for ( auto m : a ) {
            std::string modId = m->getIdWithMotif();
            Assert::IsTrue ( modId >= id1 );
        }
        
    }

    void TestPtmListLoader::Test_ModsWithComments()
    {
        std::string testdir=std::experimental::filesystem::current_path().string();
        std::string testModificationsFileLocation = testdir + "/ModificationTests/ModsWithComments.txt";
        std::vector<std::tuple<Modification*, std::string>> errors;
        auto a = PtmListLoader::ReadModsFromFile(testModificationsFileLocation, errors);

#ifdef ORIG
        Assert::AreEqual(4, a->Select([&] (std::any m)
        {
            m::IdWithMotif;
        }).ToList()->Count);
#endif
        Assert::AreEqual(4, (int)a.size());

        std::string s0 = "Deamidation on N";
        Assert::AreEqual(s0, a[0]->getIdWithMotif());
        std::string s1 = "Sodium on D";
        Assert::AreEqual(s1, a[2]->getIdWithMotif()); //this has trailing whitespace that shouldn't be in the name

        //Make sure comments are okay on DR key and that key value pairs are still split correctly
        Modification *someMod = a[2];
        Modification *test = someMod;
        std::string residValueTest = std::get<1>(*(test->getDatabaseReference().begin()) ).front();
        std::string residKeyTest = std::get<0>(*(test->getDatabaseReference().begin()));

        std::string s2 = "RESID";
        Assert::AreEqual(s2, residKeyTest);
        std::string s3 = "AA0441";
        Assert::AreEqual(s3, residValueTest);
    }

    void TestPtmListLoader::SampleModFileLoadingFail1General(const std::string filename)
    {
        std::string testdir=std::experimental::filesystem::current_path().string();
        std::vector<std::tuple<Modification*, std::string>> errors;
        auto a = PtmListLoader::ReadModsFromFile(testdir + "/DatabaseTests/" + filename, errors);
        Assert::AreEqual(0, (int)a.size());
    }

    void TestPtmListLoader::PTMListLoader_ModWithComments_Equals_ModWithoutComments()
    {
        std::string testdir=std::experimental::filesystem::current_path().string();
        std::vector<std::tuple<Modification*, std::string>> errors;
        auto a = PtmListLoader::ReadModsFromFile(testdir + "/DatabaseTests/SampleMod_Comments.txt", errors);
        std::vector<std::tuple<Modification*, std::string>> errors2;
        auto b = PtmListLoader::ReadModsFromFile(testdir + "/DatabaseTests/SampleMod_NoComments.txt", errors2);
        Assert::IsTrue(a.front()->Equals(b.front()));
    }

#ifdef LATER
    void TestPtmListLoader::SampleModFileLoadingFail3General(const std::string filename, const std::string errorMessage)
    {
        std::string testdir=std::experimental::filesystem::current_path().string();
        Assert::IsTrue([&] ()
        {
            std::vector<std::tuple<Modification*, std::string>> errors;
            PtmListLoader::ReadModsFromFile(testdir + "/DatabaseTests/" + filename, errors);//.ToList();
        }, Throws::TypeOf<MzLibException*>().With::Property("Message").EqualTo(errorMessage));
    }
#endif
    
    void TestPtmListLoader::CompactFormReadingGeneral(const std::string filename)
    {
        std::string testdir=std::experimental::filesystem::current_path().string();
        std::vector<std::tuple<Modification*, std::string>> errors;
        Assert::AreEqual(2, (int)PtmListLoader::ReadModsFromFile(testdir + "/DatabaseTests/" + filename, errors).size());
    }

    void TestPtmListLoader::TestReadingInvalidModifications()
    {
        std::string testdir=std::experimental::filesystem::current_path().string();
        std::string modText = "ID   mod\r\nMT   type\r\nPP   Anywhere.\r\nTG   X\r\nCF   H1\r\n//";
        std::vector<std::tuple<Modification*, std::string>> errors1;
        auto mods = PtmListLoader::ReadModsFromString(modText, errors1);
        Assert::AreEqual(1, (int)mods.size());
        Assert::AreEqual(0, (int)errors1.size());

        modText = "ID   mod\r\nMT   type\r\nPP   Anywhere.\r\nTG   X\r\n//"; // no monoisotopic mass, so invalid
        std::vector<std::tuple<Modification*, std::string>> errors2;
        mods = PtmListLoader::ReadModsFromString(modText, errors2);
        Assert::AreEqual(0, (int)mods.size());
        Assert::AreEqual(1, (int)errors2.size());
        //Assert::IsFalse(errors2::Single().Item1->ValidModification);
        for ( auto i: errors2 ) {
            Assert::IsFalse(std::get<0>(i)->getValidModification());
        }

        //Assert::IsTrue(errors2::Single().Item2->Split({"\r\n"}, StringSplitOptions::None)->Any([&] (std::any x)
        // {
        //    x->StartsWith("#");
        //})); // has an error comment
        int count = 0;
        for ( auto i : errors2 ) {
            std::string del = "\r\n";
            std::vector<std::string> v = StringHelper::split(std::get<1>(i), del);
            for ( auto q: v )  {
                std::string del2 = "#";
                if ( StringHelper::startsWith(q, del2)) {
                    count++;
                    break;
                }
            }            
        }
        Assert::IsTrue( count == 1);
    }

    void TestPtmListLoader::TestReadingIdWithMotif()
    {
        std::string testdir=std::experimental::filesystem::current_path().string();
        std::string modText = "ID   Detached EVK or XleDK\r\nPP   Peptide N-terminal.\r\nTG   evkX or vekX or ldkX or dlkX or idkX or dikX\r\nMT   Detached\r\nNL   C16H28N4O5\r\nCF   C16H28N4O5\r\n//";

        std::string path = testdir + "/detacher.txt";

        //File::WriteAllLines(path, tmpvec);
        std::ofstream output(path);
        if (output.is_open() ) {
            output << modText;
        }
        output.close();
        
        std::vector<std::tuple<Modification*, std::string>> errors;
        auto mods = PtmListLoader::ReadModsFromFile(path, errors);
        Assert::IsTrue(mods.size() == 6);

#ifdef ORIG
        auto motifs = mods->Select([&] (std::any p)
        {
            p::Target->ToString();
        }).Distinct().ToList();
#endif
        std::vector<std::string> motifs;
        for ( auto p : mods ) {
            std::string s = p->getTarget()->ToString();
            bool found = false;
            for ( auto q: motifs)  {
                if ( q == s ) {
                    found = true;
                    break;
                }
            }
            if ( !found ) {
                motifs.push_back(s);
            }
        }
        Assert::IsTrue(motifs.size() == 6);

#ifdef ORIG
        auto ids = mods->Select([&] (std::any p)
        {
            p::IdWithMotif;
        }).Distinct().ToList();
#endif
        std::vector<std::string> ids;
        for ( auto p: mods ) {
            std::string s = p->getIdWithMotif();
            bool found = false;
            for ( auto q: ids ) {
                if ( q == s ) {
                    found = true;
                    break;
                }
            }
            if ( !found ) {
                ids.push_back(s);
            }
        }
        Assert::IsTrue(ids.size() == 6);

        std::experimental::filesystem::remove(path);
    }

    void TestPtmListLoader::TestInvalidModTypeError()
    {
        std::string testdir=std::experimental::filesystem::current_path().string();
        std::string mod = "ID   Deamidation\r\nTG   N or Q\r\nPP   Anywhere.\r\nMT   Mod:\r\nCF   H-1 N-1 O1\r\n//";
        std::string filepath = testdir + "/ptmlist.txt";

        //File::WriteAllLines(filepath, tmpvec);
        std::ofstream output(filepath);
        if ( output.is_open() ) {
            output << mod;
        }
        output.close();
        
        std::vector<std::tuple<Modification*, std::string>> warnings;
        auto ptms = PtmListLoader::ReadModsFromFile(filepath, warnings);
        Assert::IsTrue(ptms.size() == 0);
        Assert::IsTrue(warnings.size() == 2);

        //Assert::IsTrue(warnings::First().Item2->Contains("Modification type cannot contain ':'!"));
        std::string warn = std::get<1>(warnings.front());
        Assert::IsTrue (warn.find("Modification type cannot contain ':'!") != std::string::npos);

        std::experimental::filesystem::remove(filepath);
    }
}
