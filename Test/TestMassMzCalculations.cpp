#include "TestMassMzCalculations.h"
#include "../Chemistry/ClassExtensions.h"

using namespace Chemistry;
using namespace NUnit::Framework;
namespace Stopwatch = System::Diagnostics::Stopwatch;

namespace Test
{

System::Diagnostics::Stopwatch *TestMassMzCalculations::privateStopwatch;

    Stopwatch *TestMassMzCalculations::getStopwatch()
    {
        return privateStopwatch;
    }

    void TestMassMzCalculations::setStopwatch(Stopwatch *value)
    {
        privateStopwatch = value;
    }

    void TestMassMzCalculations::Setup()
    {
        Stopwatch tempVar();
        setStopwatch(&tempVar);
        getStopwatch()->Start();
    }

    void TestMassMzCalculations::TearDown()
    {
        std::cout << StringHelper::formatSimple("Analysis time: {0}h {1}m {2}s", getStopwatch()->Elapsed.Hours, getStopwatch()->Elapsed.Minutes, getStopwatch()->Elapsed.Seconds) << std::endl;
    }

    void TestMassMzCalculations::MassToMzToMass()
    {
        ObjectWithMass1000 *a = new ObjectWithMass1000();
        double mz = a->ToMz(2).ToMass(2);
        Assert::AreEqual(1000, mz);

        delete a;
    }

    void TestMassMzCalculations::MassToMzPositiveCharge()
    {
        ObjectWithMass1000 *a = new ObjectWithMass1000();
        double mz = a->ToMz(2);
        Assert::AreEqual(501.00727646687898, mz);

        delete a;
    }

    void TestMassMzCalculations::MassToMzPositiveCharge_plus3()
    {
        ObjectWithMass1000 *a = new ObjectWithMass1000();
        double mz = static_cast<double>(ClassExtensions::RoundedDouble(a->ToMz(3), 9));
        Assert::AreEqual(334.340609800, mz);

        delete a;
    }

    void TestMassMzCalculations::MassToMzNegativeCharge()
    {
        ObjectWithMass1000 *a = new ObjectWithMass1000();
        double mz = a->ToMz(-2);
        Assert::AreEqual(498.99272353312102, mz);

        delete a;
    }

    void TestMassMzCalculations::MzToMassPostitiveCharge()
    {
        double a = 524.3;
        Assert::AreEqual(1046.5854470662418, Chemistry::ClassExtensions::ToMass(a, 2));
    }

    void TestMassMzCalculations::MzToMassNegativeCharge()
    {
        double a = 524.3;
        Assert::AreEqual(1050.614552933758, Chemistry::ClassExtensions::ToMass(a, -2));
    }

    double ObjectWithMass1000::getMonoisotopicMass() const
    {
        return 1000;
    }

    double ObjectWithMass100::getMonoisotopicMass() const
    {
        return 100;
    }

    std::string ObjectWithMass100::ToString()
    {
        return "mass: 100";
    }
}
