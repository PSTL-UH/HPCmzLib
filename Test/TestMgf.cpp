#include "TestMgf.h"
#include "../MassSpectrometry/Enums/Polarity.h"

using namespace IO::Mgf;


#include "../UsefulProteomicsDatabases/PeriodicTableLoader.h"
#include "MzLibAssert.h"

int main ( int argc, char **argv )
{

    int i=0;
    std::cout << i << ". PeriodicTableLoader" << std::endl;    
    const std::string elfile="elements.dat";
    const std::string &elr=elfile;
    //UsefulProteomicsDatabases::PeriodicTableLoader::Load (elr);
    Chemistry::PeriodicTable::Load (elr);

    std::cout << ++i << ".  TestLoadMgf" << std::endl;    
    Test::TestMgf::TestLoadMgf();

    return 0;
}

namespace Test
{

    void TestMgf::TestLoadMgf()
    {
        std::string testdir=std::experimental::filesystem::current_path().string();

        try {
            Mgf::LoadAllStaticData(testdir + "/ThereIsNothingHerePleaseDoNotGenerateThisFile.mgf");
            Assert::IsTrue(false);
        }
        catch (...) {
        }

        Mgf *a = Mgf::LoadAllStaticData(testdir +  "/tester.mgf");
        auto ya = a->GetOneBasedScan(14);
        Assert::AreEqual(192, ya->getMassSpectrum()->getSize());
        Assert::AreEqual(2, ya->getMsnOrder());
        Assert::AreEqual(14, ya->getOneBasedScanNumber());
        //Assert::AreEqual(MassSpectrometry::Polarity::Positive, ya->getPolarity());
        Assert::AreEqual(0.26666666666666666, ya->getRetentionTime());
        Assert::AreEqual(571.806916, ya->getIsolationMz().value());
        Assert::AreEqual(571.806916, ya->getSelectedIonMZ().value());
        Assert::AreEqual(2, ya->getSelectedIonChargeStateGuess().value());
        Assert::AreEqual(571.806916, ya->getSelectedIonMonoisotopicGuessMz().value());
        Assert::AreEqual(1294963.5999999996, ya->getTotalIonCurrent());
        Assert::AreEqual(110.0719, ya->getScanWindowRange()->getMinimum());
        Assert::AreEqual(1038.8018, ya->getScanWindowRange()->getMaximum());
        auto ya2 = a->GetOneBasedScan(20)->getMassSpectrum();
        Assert::AreEqual(165, ya2->getSize());
        auto ya3 = a->GetOneBasedScan(2)->getMassSpectrum();
        Assert::AreEqual(551, ya3->getSize());
    }
}
