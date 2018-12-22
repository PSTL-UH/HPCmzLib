#include "MassTestFixture.h"
#include "../Chemistry/ClassExtensions.h"

using namespace Chemistry;
using namespace NUnit::Framework;

namespace Test {

    void MassTestFixture::MassToMzToMass() {
        ObjectWithMass1000 *a = new ObjectWithMass1000();
        double mz = a->ToMz(2).ToMass(2);
        Assert::AreEqual(1000, mz);

        delete a;
    }

    void MassTestFixture::MassToMzPositiveCharge() {
        ObjectWithMass1000 *a = new ObjectWithMass1000();
        double mz = a->ToMz(2);
        Assert::AreEqual(501.00727646687898, mz);

        delete a;
    }

    void MassTestFixture::MassToMzNegativeCharge() {
        ObjectWithMass1000 *a = new ObjectWithMass1000();
        double mz = a->ToMz(-2);
        Assert::AreEqual(498.99272353312102, mz);

        delete a;
    }

    void MassTestFixture::MzToMassPostitiveCharge() {
        double a = 524.3;
        Assert::AreEqual(1046.5854470662418, Chemistry::ClassExtensions::ToMass(a, 2));
    }

    void MassTestFixture::MzToMassNegativeCharge() {
        double a = 524.3;
        Assert::AreEqual(1050.614552933758, Chemistry::ClassExtensions::ToMass(a, -2));
    }

    double ObjectWithMass1000::getMonoisotopicMass() const {
        return 1000;
    }

    double ObjectWithMass100::getMonoisotopicMass() const {
        return 100;
    }

    std::wstring ObjectWithMass100::ToString() {
        return L"mass: 100";
    }
}
