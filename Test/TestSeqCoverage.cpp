#include "TestSeqCoverage.h"
#include "../Proteomics/Protein/Protein.h"
#include "../Proteomics/Modifications/Modification.h"

using namespace NUnit::Framework;
using namespace Proteomics;
using namespace Proteomics::ProteolyticDigestion;
namespace Stopwatch = System::Diagnostics::Stopwatch;

namespace Test
{

System::Diagnostics::Stopwatch *TestSeqCoverage::privateStopwatch;

    Stopwatch *TestSeqCoverage::getStopwatch()
    {
        return privateStopwatch;
    }

    void TestSeqCoverage::setStopwatch(Stopwatch *value)
    {
        privateStopwatch = value;
    }

    void TestSeqCoverage::Setup()
    {
        Stopwatch tempVar();
        setStopwatch(&tempVar);
        getStopwatch()->Start();
    }

    void TestSeqCoverage::TearDown()
    {
        std::cout << StringHelper::formatSimple("Analysis time: {0}h {1}m {2}s", getStopwatch()->Elapsed.Hours, getStopwatch()->Elapsed.Minutes, getStopwatch()->Elapsed.Seconds) << std::endl;
    }

    void TestSeqCoverage::MultipleProteaseSelectionTest()
    {
        Protein *ParentProtein = new Protein("MOAT", "accession1");
        auto motifList = DigestionMotif::ParseDigestionMotifsFromString("O|,|T");
        auto protease = new Protease("TestProtease1", CleavageSpecificity::Full, "", "", motifList);
        ProteaseDictionary::getDictionary().emplace(protease->getName(), protease);
        DigestionParams *multiProtease = new DigestionParams(protease->getName(), 0, 1, int::MaxValue, 1024, InitiatorMethionineBehavior::Retain, 2, CleavageSpecificity::Full, FragmentationTerminus::Both);
        auto digestedList = ParentProtein->Digest(multiProtease, std::vector<Modification*>(), std::vector<Modification*>()).ToList();
        auto sequences = digestedList.Select([&] (std::any p)
        {
            p::BaseSequence;
        }).ToList();
        Assert::That(sequences.size() == 3);
        Assert::That(std::find(sequences.begin(), sequences.end(), "MO") != sequences.end());
        Assert::That(std::find(sequences.begin(), sequences.end(), "A") != sequences.end());
        Assert::That(std::find(sequences.begin(), sequences.end(), "T") != sequences.end());

//C# TO C++ CONVERTER TODO TASK: A 'delete multiProtease' statement was not added since multiProtease was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete protease' statement was not added since protease was passed to a method or constructor. Handle memory management manually.
        delete ParentProtein;
    }

    void TestSeqCoverage::MultipleProteaseSelectionTestMissedCleavage()
    {
        Protein *ParentProtein = new Protein("MOAT", "accession1");

        auto motifList = DigestionMotif::ParseDigestionMotifsFromString("O|,|T");
        auto protease = new Protease("TestProtease2", CleavageSpecificity::Full, "", "", motifList);
        ProteaseDictionary::getDictionary().emplace(protease->getName(), protease);
        DigestionParams *multiProtease = new DigestionParams(protease->getName(), 1, 1, int::MaxValue, 1024, InitiatorMethionineBehavior::Retain, 2, CleavageSpecificity::Full, FragmentationTerminus::Both);
        auto digestedList = ParentProtein->Digest(multiProtease, std::vector<Modification*>(), std::vector<Modification*>()).ToList();
        auto sequences = digestedList.Select([&] (std::any p)
        {
            p::BaseSequence;
        }).ToList();
        Assert::That(sequences.size() == 5);
        Assert::That(std::find(sequences.begin(), sequences.end(), "MOA") != sequences.end());
        Assert::That(std::find(sequences.begin(), sequences.end(), "AT") != sequences.end());
        Assert::That(std::find(sequences.begin(), sequences.end(), "MO") != sequences.end());
        Assert::That(std::find(sequences.begin(), sequences.end(), "A") != sequences.end());
        Assert::That(std::find(sequences.begin(), sequences.end(), "T") != sequences.end());

//C# TO C++ CONVERTER TODO TASK: A 'delete multiProtease' statement was not added since multiProtease was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete protease' statement was not added since protease was passed to a method or constructor. Handle memory management manually.
        delete ParentProtein;
    }

    void TestSeqCoverage::MultipleProteaseSelectionTestPreventCleavage()
    {
        Protein *ParentProtein = new Protein("MOAT", "accession1");

        auto motifList = DigestionMotif::ParseDigestionMotifsFromString("O[A]|,|T");
        auto protease = new Protease("TestProtease3", CleavageSpecificity::Full, "", "", motifList);
        ProteaseDictionary::getDictionary().emplace(protease->getName(), protease);
        DigestionParams *multiProtease = new DigestionParams(protease->getName(), 0, 1, int::MaxValue, 1024, InitiatorMethionineBehavior::Retain, 2, CleavageSpecificity::Full, FragmentationTerminus::Both);
        auto digestedList = ParentProtein->Digest(multiProtease, std::vector<Modification*>(), std::vector<Modification*>()).ToList();
        auto sequences = digestedList.Select([&] (std::any p)
        {
            p::BaseSequence;
        }).ToList();
        Assert::That(sequences.size() == 2);
        Assert::That(std::find(sequences.begin(), sequences.end(), "MOA") != sequences.end());
        Assert::That(std::find(sequences.begin(), sequences.end(), "T") != sequences.end());

//C# TO C++ CONVERTER TODO TASK: A 'delete multiProtease' statement was not added since multiProtease was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete protease' statement was not added since protease was passed to a method or constructor. Handle memory management manually.
        delete ParentProtein;
    }

    void TestSeqCoverage::ReadCustomFile()
    {
        Protein *ParentProtein = new Protein("OKAREDY", "accession1");
        std::string path = FileSystem::combine(TestContext::CurrentContext->TestDirectory, "DoubleProtease.tsv");
        Assert::That(FileSystem::fileExists(path));

        auto proteaseDict = ProteaseDictionary::LoadProteaseDictionary(path);
        Assert::That(proteaseDict.find("Test1") != proteaseDict.end());
        Assert::That(proteaseDict.find("Test2") != proteaseDict.end());
        Assert::That(proteaseDict.find("Test3") != proteaseDict.end());
        ProteaseDictionary::getDictionary().emplace("Test1", proteaseDict["Test1"]);

        DigestionParams *multiProtease1 = new DigestionParams("Test1", 0, 1, int::MaxValue, 1024, InitiatorMethionineBehavior::Retain, 2, CleavageSpecificity::Full, FragmentationTerminus::Both);
        auto digestedList1 = ParentProtein->Digest(multiProtease1, std::vector<Modification*>(), std::vector<Modification*>()).ToList();
        ProteaseDictionary::getDictionary().erase("Test1");

        auto sequences = digestedList1.Select([&] (std::any p)
        {
            p::BaseSequence;
        }).ToList();
        Assert::That(sequences.size() == 3);
        Assert::That(std::find(sequences.begin(), sequences.end(), "OK") != sequences.end());
        Assert::That(std::find(sequences.begin(), sequences.end(), "A") != sequences.end());
        Assert::That(std::find(sequences.begin(), sequences.end(), "REDY") != sequences.end());

        ProteaseDictionary::getDictionary().emplace("Test2", proteaseDict["Test2"]);
        DigestionParams *multiProtease2 = new DigestionParams("Test2", 0, 1, int::MaxValue, 1024, InitiatorMethionineBehavior::Retain, 2, CleavageSpecificity::Full, FragmentationTerminus::Both);
        auto digestedList2 = ParentProtein->Digest(multiProtease2, std::vector<Modification*>(), std::vector<Modification*>()).ToList();
        ProteaseDictionary::getDictionary().erase("Test2");
        auto sequences2 = digestedList2.Select([&] (std::any p)
        {
            p::BaseSequence;
        }).ToList();
        Assert::That(sequences2.size() == 3);
        Assert::That(std::find(sequences2.begin(), sequences2.end(), "OK") != sequences2.end());
        Assert::That(std::find(sequences2.begin(), sequences2.end(), "ARED") != sequences2.end());
        Assert::That(std::find(sequences2.begin(), sequences2.end(), "Y") != sequences2.end());

        ProteaseDictionary::getDictionary().emplace("Test3", proteaseDict["Test3"]);
        DigestionParams *multiProtease3 = new DigestionParams("Test3", 0, 1, int::MaxValue, 1024, InitiatorMethionineBehavior::Retain, 2, CleavageSpecificity::Full, FragmentationTerminus::Both);
        auto digestedList3 = ParentProtein->Digest(multiProtease3, std::vector<Modification*>(), std::vector<Modification*>()).ToList();
        ProteaseDictionary::getDictionary().erase("Test3");
        auto sequences3 = digestedList3.Select([&] (std::any p)
        {
            p::BaseSequence;
        }).ToList();
        Assert::That(sequences3.size() == 2);
        Assert::That(std::find(sequences3.begin(), sequences3.end(), "OK") != sequences3.end());
        Assert::That(std::find(sequences3.begin(), sequences3.end(), "AREDY") != sequences3.end());

//C# TO C++ CONVERTER TODO TASK: A 'delete multiProtease3' statement was not added since multiProtease3 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete multiProtease2' statement was not added since multiProtease2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete multiProtease1' statement was not added since multiProtease1 was passed to a method or constructor. Handle memory management manually.
        delete ParentProtein;
    }
}
