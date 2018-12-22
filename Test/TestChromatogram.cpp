#include "TestChromatogram.h"
#include "../MassSpectrometry/Chromatogram/Chromatogram.h"
#include "../MassSpectrometry/Enums/SmoothingType.h"
#include "../MzLibUtil/DoubleRange.h"
#include "../MassSpectrometry/Chromatogram/ChromatographicPeak.h"

using namespace MassSpectrometry;
using namespace MzLibUtil;
using namespace NUnit::Framework;

namespace Test {

    void ChromatogramTestFixture::ChromatogramTest() {
        Chromatogram<void> *a = new Chromatogram({1, 2, 3, 4, 5}, {1, 2, 6, 4, 2}, false);
        auto b = a->CreateSmoothChromatogram(SmoothingType::BoxCar, 4);
        Assert::IsTrue(b->GetTimes().SequenceEqual(std::vector<double> {2, 3, 4}));
        Assert::IsTrue(b->GetIntensities().SequenceEqual(std::vector<double> {3, 4, 4}));

        Chromatogram<void> *d = new Chromatogram({1, 2, 3, 4, 5, 6, 7, 8, 9}, {10, 0, 2, 6, 2, 0, 1, 10, 1}, false);
        // Finds the APEX! Not nearest peak!
        Assert::AreEqual(6, d->FindNearestApex(5.9, 1)->Intensity);
        Assert::AreEqual(10, d->FindNearestApex(6.1, 1)->Intensity);

        DoubleRange tempVar(3, 7);
        auto elutionProfile = d->GetElutionProfile(&tempVar);

        Assert::AreEqual(5, elutionProfile->getCount());
        Assert::AreEqual(9.5, elutionProfile->TrapezoidalArea());

        Assert::AreEqual(2, elutionProfile->getStartPeak()->Intensity);
        Assert::AreEqual(3, elutionProfile->getStartPeak()->Time);
        Assert::AreEqual(7, elutionProfile->getEndPeak()->Time);

        auto thePeak = new ChromatographicPeak(1, 10);
        Assert::AreEqual(1, thePeak->getTime());
        Assert::AreEqual(10, thePeak->getIntensity());
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
        Assert::AreEqual(L"(1, 10)", thePeak->ToString());

        DoubleRange tempVar2(6.5, 6.5);
        auto elutionProfileEmpty = d->GetElutionProfile(&tempVar2);
        Assert::AreEqual(0, elutionProfileEmpty->TrapezoidalArea());
        Assert::AreEqual(0, elutionProfileEmpty->getSummedArea());

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
        Assert::AreEqual(L"Count = 9 TIC = 32", d->ToString());
        Assert::AreEqual(10, d->GetApex()->Intensity);
        Assert::AreEqual(1, d->GetApex()->Time);

        delete thePeak;
        delete d;
        delete a;
    }

    void ChromatogramTestFixture::TestGetApex() {
        Chromatogram<void> *d = new Chromatogram({1, 2, 3, 4, 5, 6, 7, 8, 9}, {10, 0, 2, 6, 2, 0, 1, 10, 1}, false);
        DoubleRange tempVar(2, 6);
        Assert::AreEqual(6, d->GetApex(&tempVar)->Y);

        delete d;
    }

    void ChromatogramTestFixture::AnotherChromatogramTest() {
        std::vector<std::vector<double>> timeintensities = {
            {1, 2, 3, 4}, {
            };
        Chromatogram<void> *a = new Chromatogram(timeintensities);
        Assert::AreEqual(1, a->FirstTime);
        Assert::AreEqual(4, a->LastTime);
        Assert::AreEqual(3, a->GetTime(2));
        Assert::AreEqual(8, a->GetIntensity(3));
        Assert::AreEqual(6, a->GetApex(1.5, 2.5)->Intensity);
        Assert::AreEqual(6, a->GetApex(1.5, 2.5)->Intensity);
        Assert::AreEqual(4, a->GetApex(4, 5)->X);

        Assert::AreEqual(6, a->CreateSmoothChromatogram(SmoothingType::None, -10)->GetApex(1.5, 2.5)->Intensity);

        Assert::AreEqual(8, a->FindNearestApex(10, 1)->Y);

        Assert::AreEqual(4, a->GetApex(5, 6)->X);

        delete a;
    }
}
