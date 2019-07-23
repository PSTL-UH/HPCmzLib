#include "TestDigestionMotif.h"
#include "../Proteomics/Modifications/Modification.h"
#include "../Proteomics/Protein/Protein.h"
#include "../MzLibUtil/MzLibException.h"

using namespace MzLibUtil;
using namespace NUnit::Framework;
using namespace Proteomics;
using namespace Proteomics::ProteolyticDigestion;
namespace Stopwatch = System::Diagnostics::Stopwatch;

namespace Test
{

System::Diagnostics::Stopwatch *TestDigestionMotif::privateStopwatch;

    Stopwatch *TestDigestionMotif::getStopwatch()
    {
        return privateStopwatch;
    }

    void TestDigestionMotif::setStopwatch(Stopwatch *value)
    {
        privateStopwatch = value;
    }

    void TestDigestionMotif::Setup()
    {
        Stopwatch tempVar();
        setStopwatch(&tempVar);
        getStopwatch()->Start();
    }

    void TestDigestionMotif::TearDown()
    {
        std::cout << StringHelper::formatSimple("Analysis time: {0}h {1}m {2}s", getStopwatch()->Elapsed.Hours, getStopwatch()->Elapsed.Minutes, getStopwatch()->Elapsed.Seconds) << std::endl;
    }

    void TestDigestionMotif::TestParseProtease()
    {
        auto argn = DigestionMotif::ParseDigestionMotifsFromString("|D");
        Assert::AreEqual(argn.size(), 1);

        auto c = argn[0];
        Assert::AreEqual(c->InducingCleavage, "D");
        Assert::AreEqual(c->PreventingCleavage, nullptr);
        Assert::AreEqual(c->CutIndex, 0);

        auto chymotrypsin = DigestionMotif::ParseDigestionMotifsFromString("F[P]|,W[P]|,Y[P]|");
        Assert::AreEqual(chymotrypsin.size(), 3);
    }

    void TestDigestionMotif::TestBasicProtease1()
    {
        auto empty = std::vector<Modification*>();
        DigestionParams *myDigestionParams = new DigestionParams("trypsin", 0, 1, int::MaxValue, 1024, InitiatorMethionineBehavior::Variable, 2, CleavageSpecificity::Full, FragmentationTerminus::Both);

        // create a protein
        Protein *myProtein = new Protein("PROTEIN", "myAccession");

        // digest it into peptides
        auto myPeptides = myProtein->Digest(myDigestionParams, empty, empty).ToList();
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        std::string first = myPeptides.front().ToString();
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        std::string last = myPeptides.back().ToString();

        Assert::AreEqual(first, "PR");
        Assert::AreEqual(last, "OTEIN");

        delete myProtein;
//C# TO C++ CONVERTER TODO TASK: A 'delete myDigestionParams' statement was not added since myDigestionParams was passed to a method or constructor. Handle memory management manually.
    }

    void TestDigestionMotif::TestBasicProtease2()
    {
        auto empty = std::vector<Modification*>();
        DigestionParams *myDigestionParams = new DigestionParams("Lys-C (don't cleave before proline)", 0, 1, int::MaxValue, 1024, InitiatorMethionineBehavior::Variable, 2, CleavageSpecificity::Full, FragmentationTerminus::Both);

        // create a protein
        Protein *myProtein = new Protein("MKPKPKPMKA", "myAccession");

        // digest it into peptides
        auto myPeptides = myProtein->Digest(myDigestionParams, empty, empty).ToList();
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        std::string first = myPeptides.front().ToString();
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        std::string last = myPeptides.back().ToString();

        Assert::AreEqual(first, "MKPKPKPMK");
        Assert::AreEqual(last, "A");

        delete myProtein;
//C# TO C++ CONVERTER TODO TASK: A 'delete myDigestionParams' statement was not added since myDigestionParams was passed to a method or constructor. Handle memory management manually.
    }

    void TestDigestionMotif::TestWildCardExclusion()
    {
        auto empty = std::vector<Modification*>();
        auto digestionmotifs = DigestionMotif::ParseDigestionMotifsFromString("RX{P}|");
        Protease *multiletter = new Protease("multiletter", CleavageSpecificity::Full, "", "", digestionmotifs);
        ProteaseDictionary::getDictionary().emplace(multiletter->getName(), multiletter);

        DigestionParams *myDigestionParams = new DigestionParams("multiletter", 0, 1, int::MaxValue, 1024, InitiatorMethionineBehavior::Variable, 2, CleavageSpecificity::Full, FragmentationTerminus::Both);

        // create a protein
        Protein *myProtein = new Protein("PROPRPPM", "myAccession");

        // digest it into peptides
        auto myPeptides = myProtein->Digest(myDigestionParams, empty, empty).ToList();
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        std::string first = myPeptides.front().ToString();
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        std::string last = myPeptides.back().ToString();

        Assert::AreEqual(first, "PRO");
        Assert::AreEqual(last, "PRPPM");

        delete myProtein;
//C# TO C++ CONVERTER TODO TASK: A 'delete myDigestionParams' statement was not added since myDigestionParams was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete multiletter' statement was not added since multiletter was passed to a method or constructor. Handle memory management manually.
    }

    void TestDigestionMotif::TestMultiLetterProtease()
    {
        auto empty = std::vector<Modification*>();
        DigestionParams *myDigestionParams = new DigestionParams("collagenase", 0, 1, int::MaxValue, 1024, InitiatorMethionineBehavior::Variable, 2, CleavageSpecificity::Full, FragmentationTerminus::Both);

        // create a protein
        Protein *myProtein = new Protein("ABCGPXGPMFKCGPMKK", "myAccession");

        // digest it into peptides
        auto myPeptides = myProtein->Digest(myDigestionParams, empty, empty).ToList();
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        std::string first = myPeptides.front().ToString();
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        std::string last = myPeptides.back().ToString();

        Assert::AreEqual(first, "ABCGPX");
        Assert::AreEqual(last, "GPMFKCGPMKK");

        delete myProtein;
//C# TO C++ CONVERTER TODO TASK: A 'delete myDigestionParams' statement was not added since myDigestionParams was passed to a method or constructor. Handle memory management manually.
    }

    void TestDigestionMotif::TestNTerminusProtease()
    {
        auto empty = std::vector<Modification*>();
        DigestionParams *myDigestionParams = new DigestionParams("Asp-N", 0, 1, int::MaxValue, 1024, InitiatorMethionineBehavior::Variable, 2, CleavageSpecificity::Full, FragmentationTerminus::Both);

        // create a protein
        Protein *myProtein = new Protein("PADDMSKDPDMMAASMDJSSM", "myAccession");

        // digest it into peptides
        auto myPeptides = myProtein->Digest(myDigestionParams, empty, empty).ToList();
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        std::string first = myPeptides.front().ToString();
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        std::string last = myPeptides.back().ToString();

        Assert::AreEqual(first, "PA");
        Assert::AreEqual(last, "DJSSM");

        delete myProtein;
//C# TO C++ CONVERTER TODO TASK: A 'delete myDigestionParams' statement was not added since myDigestionParams was passed to a method or constructor. Handle memory management manually.
    }

    void TestDigestionMotif::TestSyntax()
    {
        Assert::Throws<MzLibException*>([&] ()
        {
            auto protease = DigestionMotif::ParseDigestionMotifsFromString("X[Y,P]");
            Assert::Fail("Exception shold be thrown for incorrect syntax.");
        });
    }
}
