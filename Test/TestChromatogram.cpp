#include "TestChromatogram.h"
#include "../MassSpectrometry/Chromatogram/Chromatogram.h"
#include "../MassSpectrometry/Enums/SmoothingType.h"
#include "../MzLibUtil/DoubleRange.h"
#include "../MassSpectrometry/Chromatogram/ChromatographicPeak.h"

using namespace MassSpectrometry;
using namespace MzLibUtil;

#include "../UsefulProteomicsDatabases/PeriodicTableLoader.h"
#include "Assert.h"

int main ( int argc, char **argv )
{

    int i=0;
    std::cout << i << ". PeriodicTableLoader" << std::endl;    
    const std::string elfile="elements.dat";
    const std::string &elr=elfile;
    //UsefulProteomicsDatabases::PeriodicTableLoader::Load (elr);
    Chemistry::PeriodicTable::Load (elr);

    std::cout << ++i << ".  ChromatogramTest" << std::endl;    
    Test::TestChromatogram::ChromatogramTest();
    
    std::cout << ++i << ".  TestGetApex" << std::endl;    
    Test::TestChromatogram::TestGetApex();

    std::cout << ++i << ".  AnotherChromatogramTest" << std::endl;    
    Test::TestChromatogram::AnotherChromatogramTest();

    return 0;
}


namespace Test
{

    void TestChromatogram::ChromatogramTest()
    {
        Chromatogram *a = new Chromatogram({1, 2, 3, 4, 5}, {1, 2, 6, 4, 2}, false);
#ifdef LATER
        //BoxCar Smoothing is not implemented correctly in the C++ version for now
        auto b = a->CreateSmoothChromatogram(SmoothingType::BoxCar, 4);
        Assert::IsTrue(b->GetTimes().SequenceEqual(std::vector<double> {2, 3, 4}));
        Assert::IsTrue(b->GetIntensities().SequenceEqual(std::vector<double> {3, 4, 4}));
#endif
        
        Chromatogram *d = new Chromatogram({1, 2, 3, 4, 5, 6, 7, 8, 9}, {10, 0, 2, 6, 2, 0, 1, 10, 1}, false);
        // Finds the APEX! Not nearest peak!
        Assert::AreEqual(6, d->FindNearestApex(5.9, 1)->getIntensity());
        Assert::AreEqual(10, d->FindNearestApex(6.1, 1)->getIntensity());

        DoubleRange tempVar(3, 7);
        auto elutionProfile = d->GetElutionProfile(&tempVar);

        Assert::AreEqual(5, elutionProfile->getCount());
        Assert::AreEqual(9.5, elutionProfile->TrapezoidalArea());

        Assert::AreEqual(2, elutionProfile->getStartPeak()->getIntensity());
        Assert::AreEqual(3, elutionProfile->getStartPeak()->getTime());
        Assert::AreEqual(7, elutionProfile->getEndPeak()->getTime());

        auto thePeak = new ChromatographicPeak(1, 10);
        Assert::AreEqual(1, thePeak->getTime());
        Assert::AreEqual(10, thePeak->getIntensity());

        std::string s1 = "(1, 10)";
        Assert::AreEqual(s1, thePeak->ToString());

        DoubleRange tempVar2(6.5, 6.5);
        auto elutionProfileEmpty = d->GetElutionProfile(&tempVar2);
        Assert::AreEqual(0, elutionProfileEmpty->TrapezoidalArea());
        Assert::AreEqual(0, elutionProfileEmpty->getSummedArea());

        std::string s2 = "Count = 9 TIC = 32";
        Assert::AreEqual(s2, d->ToString());
        Assert::AreEqual(10, d->GetApex()->getIntensity());
        Assert::AreEqual(1, d->GetApex()->getTime());

        delete thePeak;
        delete d;
        delete a;
    }

    void TestChromatogram::TestGetApex()
    {
        Chromatogram *d = new Chromatogram({1, 2, 3, 4, 5, 6, 7, 8, 9}, {10, 0, 2, 6, 2, 0, 1, 10, 1}, false);
        DoubleRange tempVar(2, 6);
        Assert::AreEqual(6, d->GetApex(&tempVar)->getY());

        delete d;
    }

    void TestChromatogram::AnotherChromatogramTest()
    {
        std::vector<std::vector<double>> timeintensities =
        {
            {1, 2, 3, 4},
            {5, 6, 7, 8}
        };
        Chromatogram *a = new Chromatogram(timeintensities);
        Assert::AreEqual(1, a->getFirstTime());
        Assert::AreEqual(4, a->getLastTime());
        Assert::AreEqual(3, a->GetTime(2));
        Assert::AreEqual(8, a->GetIntensity(3));
        Assert::AreEqual(6, a->GetApex(1.5, 2.5)->getIntensity());
        Assert::AreEqual(6, a->GetApex(1.5, 2.5)->getIntensity());
        Assert::AreEqual(4, a->GetApex(4, 5)->getX());

        Assert::AreEqual(6, a->CreateSmoothChromatogram(SmoothingType::None, -10)->GetApex(1.5, 2.5)->getIntensity());

        Assert::AreEqual(8, a->FindNearestApex(10, 1)->getY());

        Assert::AreEqual(4, a->GetApex(5, 6)->getX());

        delete a;
    }
}
