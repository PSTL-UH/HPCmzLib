#include "TestTolerance.h"
#include "../MzLibUtil/AbsoluteTolerance.h"
#include "../MzLibUtil/Tolerance.h"
#include "../MzLibUtil/PpmTolerance.h"

using namespace MzLibUtil;
using namespace NUnit::Framework;

namespace Test {

    void MassToleranceTestFixture::MassToleranceConstructorDaValue() {
        auto tol = new AbsoluteTolerance(10);

        Assert::AreEqual(10, tol->getValue());

        delete tol;
    }

    void MassToleranceTestFixture::MassToleranceImplicitValue() {
        auto tol = Tolerance::ParseToleranceString(L"10 ppm");

        Assert::AreEqual(10, tol->getValue());

        Assert::AreEqual(1 + 1e-5, tol->GetMaximumValue(1));
        Assert::AreEqual(1 - 1e-5, tol->GetMinimumValue(1));
    }

    void MassToleranceTestFixture::ToleranceWithin1() {
        auto tol = new PpmTolerance(10);

        Assert::IsTrue(tol->Within(500, 500.005));

        delete tol;
    }

    void MassToleranceTestFixture::ToleranceNewTest() {
        auto tol = new AbsoluteTolerance(1);
        Assert::AreEqual(4, tol->GetRange(5)->Minimum);
        Assert::AreEqual(6, tol->GetRange(5)->Maximum);

        delete tol;
    }

    void MassToleranceTestFixture::ToleranceMinMaxTest() {
        auto tol = new AbsoluteTolerance(1);
        Assert::AreEqual(2, tol->GetMaximumValue(1));
        Assert::AreEqual(0, tol->GetMinimumValue(1));

        delete tol;
    }

    void MassToleranceTestFixture::TolerancePPMGetRange() {
        auto tol = new PpmTolerance(1);
        Assert::AreEqual(20, tol->GetRange(1e7)->getWidth());

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
        Assert::AreEqual(L"±1.0000 PPM", tol->ToString());

        delete tol;
    }
}
