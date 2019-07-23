#include "TestMgf.h"
#include "../MassSpectrometry/Enums/Polarity.h"

using namespace IO::Mgf;
using namespace NUnit::Framework;
namespace Stopwatch = System::Diagnostics::Stopwatch;

namespace Test
{

System::Diagnostics::Stopwatch *TestMgf::privateStopwatch;

    Stopwatch *TestMgf::getStopwatch()
    {
        return privateStopwatch;
    }

    void TestMgf::setStopwatch(Stopwatch *value)
    {
        privateStopwatch = value;
    }

    void TestMgf::Setuppp()
    {
        Stopwatch tempVar();
        setStopwatch(&tempVar);
        getStopwatch()->Start();
    }

    void TestMgf::TearDown()
    {
        std::cout << StringHelper::formatSimple("Analysis time: {0}h {1}m {2}s", getStopwatch()->Elapsed.Hours, getStopwatch()->Elapsed.Minutes, getStopwatch()->Elapsed.Seconds) << std::endl;
    }

    void TestMgf::TestLoadMgf()
    {
        try
        {
            Mgf::LoadAllStaticData(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "ThereIsNothingHerePleaseDoNotGenerateThisFile.mgf"));
            Assert::IsTrue(false);
        }
        catch (...)
        {
            //woohoo, there was an exception!
        }
        Mgf *a = Mgf::LoadAllStaticData(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "tester.mgf"));
        auto ya = a->GetOneBasedScan(14);
        Assert::AreEqual(192, ya->MassSpectrum.Size);
        Assert::AreEqual(2, ya->MsnOrder);
        Assert::AreEqual(14, ya->OneBasedScanNumber);
        Assert::AreEqual(MassSpectrometry::Polarity::Positive, ya->Polarity);
        Assert::AreEqual(0.26666666666666666, ya->RetentionTime);
        Assert::AreEqual(571.806916, ya->IsolationMz);
        Assert::AreEqual(571.806916, ya->SelectedIonMZ);
        Assert::AreEqual(2, ya->SelectedIonChargeStateGuess);
        Assert::AreEqual(571.806916, ya->SelectedIonMonoisotopicGuessMz);
        Assert::AreEqual(1294963.5999999996, ya->TotalIonCurrent);
        Assert::AreEqual(110.0719, ya->ScanWindowRange.Minimum);
        Assert::AreEqual(1038.8018, ya->ScanWindowRange.Maximum);
        auto ya2 = a->GetOneBasedScan(20)->MassSpectrum;
        Assert::AreEqual(165, ya2->Size);
        auto ya3 = a->GetOneBasedScan(2)->MassSpectrum;
        Assert::AreEqual(551, ya3->Size);
    }
}
