#include "TestRangeAndTolerances.h"
#include "../MzLibUtil/DoubleRange.h"
#include "../MzLibUtil/AbsoluteTolerance.h"
#include "../MzLibUtil/Tolerance.h"
#include "../MzLibUtil/PpmTolerance.h"

using namespace MzLibUtil;
using namespace NUnit::Framework;
namespace Stopwatch = System::Diagnostics::Stopwatch;

namespace Test
{

System::Diagnostics::Stopwatch *TestRangeAndTolerances::privateStopwatch;

    Stopwatch *TestRangeAndTolerances::getStopwatch()
    {
        return privateStopwatch;
    }

    void TestRangeAndTolerances::setStopwatch(Stopwatch *value)
    {
        privateStopwatch = value;
    }

    void TestRangeAndTolerances::Setuppp()
    {
        Stopwatch tempVar();
        setStopwatch(&tempVar);
        getStopwatch()->Start();
    }

    void TestRangeAndTolerances::TearDown()
    {
        std::cout << StringHelper::formatSimple("Analysis time: {0}h {1}m {2}s", getStopwatch()->Elapsed.Hours, getStopwatch()->Elapsed.Minutes, getStopwatch()->Elapsed.Seconds) << std::endl;
    }

    void TestRangeAndTolerances::RangeSubRange()
    {
        auto a = new DoubleRange(5, 7);
        auto b = new DoubleRange(0, 10);

        Assert::IsTrue(a->IsSubRange(b));

//C# TO C++ CONVERTER TODO TASK: A 'delete b' statement was not added since b was passed to a method or constructor. Handle memory management manually.
        delete a;
    }

    void TestRangeAndTolerances::RangeSubRangeReverseIsFalse()
    {
        auto a = new DoubleRange(5, 7);
        auto b = new DoubleRange(0, 10);

        Assert::IsFalse(b->IsSubRange(a));

        delete b;
//C# TO C++ CONVERTER TODO TASK: A 'delete a' statement was not added since a was passed to a method or constructor. Handle memory management manually.
    }

    void TestRangeAndTolerances::RangeOverlappingIsFalse()
    {
        auto range1 = new DoubleRange(5, 10);
        auto range2 = new DoubleRange(15, 20);

        Assert::IsFalse(range1->IsOverlapping(range2));

//C# TO C++ CONVERTER TODO TASK: A 'delete range2' statement was not added since range2 was passed to a method or constructor. Handle memory management manually.
        delete range1;
    }

    void TestRangeAndTolerances::RangeOverlappingIsFalseReverse()
    {
        auto range1 = new DoubleRange(5, 10);
        auto range2 = new DoubleRange(15, 20);

        Assert::IsFalse(range2->IsOverlapping(range1));

        delete range2;
//C# TO C++ CONVERTER TODO TASK: A 'delete range1' statement was not added since range1 was passed to a method or constructor. Handle memory management manually.
    }

    void TestRangeAndTolerances::RangeOverlappingIsTrue()
    {
        auto range1 = new DoubleRange(5, 10);
        auto range2 = new DoubleRange(7, 12);

        Assert::IsTrue(range1->IsOverlapping(range2));

//C# TO C++ CONVERTER TODO TASK: A 'delete range2' statement was not added since range2 was passed to a method or constructor. Handle memory management manually.
        delete range1;
    }

    void TestRangeAndTolerances::RangeOverlappingIsTrueReverse()
    {
        auto range1 = new DoubleRange(5, 10);
        auto range2 = new DoubleRange(7, 12);

        Assert::IsTrue(range2->IsOverlapping(range1));

        delete range2;
//C# TO C++ CONVERTER TODO TASK: A 'delete range1' statement was not added since range1 was passed to a method or constructor. Handle memory management manually.
    }

    void TestRangeAndTolerances::RangeOverlappingIsTrueLarger()
    {
        auto range1 = new DoubleRange(0, 10);
        auto range2 = new DoubleRange(3, 7);

        Assert::IsTrue(range1->IsOverlapping(range2));

//C# TO C++ CONVERTER TODO TASK: A 'delete range2' statement was not added since range2 was passed to a method or constructor. Handle memory management manually.
        delete range1;
    }

    void TestRangeAndTolerances::RangeOverlappingIsTrueSmaller()
    {
        auto range1 = new DoubleRange(0, 10);
        auto range2 = new DoubleRange(3, 7);

        Assert::IsTrue(range2->IsOverlapping(range1));

        delete range2;
//C# TO C++ CONVERTER TODO TASK: A 'delete range1' statement was not added since range1 was passed to a method or constructor. Handle memory management manually.
    }

    void TestRangeAndTolerances::RangeOverlappingIsTrueItSelf()
    {
        auto range1 = new DoubleRange(0, 10);

        Assert::IsTrue(range1->IsOverlapping(range1));

//C# TO C++ CONVERTER TODO TASK: A 'delete range1' statement was not added since range1 was passed to a method or constructor. Handle memory management manually.
    }

    void TestRangeAndTolerances::RangeDoesContainItem()
    {
        auto range1 = new DoubleRange(3, 10);

        Assert::IsTrue(range1->Contains(5));

        delete range1;
    }

    void TestRangeAndTolerances::RangeDoesnotContainItemHigher()
    {
        auto range1 = new DoubleRange(3, 10);

        Assert::IsFalse(range1->Contains(12));

        delete range1;
    }

    void TestRangeAndTolerances::RangeDoesnotContainItemLower()
    {
        auto range1 = new DoubleRange(3, 10);

        Assert::IsFalse(range1->Contains(1));

        delete range1;
    }

    void TestRangeAndTolerances::RangeDoesContainItemLowerBounds()
    {
        auto range1 = new DoubleRange(3, 10);

        Assert::IsTrue(range1->Contains(3));

        delete range1;
    }

    void TestRangeAndTolerances::RangeDoesContainItemUpperBounds()
    {
        auto range1 = new DoubleRange(3, 10);

        Assert::IsTrue(range1->Contains(10));

        delete range1;
    }

    void TestRangeAndTolerances::RangeCompareToBelow()
    {
        auto range = new DoubleRange(3, 10);
        int value = 1;

        int comp = range->CompareTo(value);

        Assert::AreEqual(-1, comp);

        delete range;
    }

    void TestRangeAndTolerances::RangeCompareToWithin()
    {
        auto range = new DoubleRange(3, 10);
        int value = 5;

        int comp = range->CompareTo(value);

        Assert::AreEqual(0, comp);

        delete range;
    }

    void TestRangeAndTolerances::RangeCompareToAbove()
    {
        auto range = new DoubleRange(3, 10);
        int value = 12;

        int comp = range->CompareTo(value);

        Assert::AreEqual(1, comp);

        delete range;
    }

    void TestRangeAndTolerances::RangesAreEquivalentNotReference()
    {
        auto range1 = new DoubleRange(3, 10);
        auto range2 = new DoubleRange(3, 10);

        Assert::AreNotSame(range1, range2);

//C# TO C++ CONVERTER TODO TASK: A 'delete range2' statement was not added since range2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete range1' statement was not added since range1 was passed to a method or constructor. Handle memory management manually.
    }

    void TestRangeAndTolerances::ToleranceParseAndWithin()
    {
        std::string tol = "4 Absolute";
        auto range1 = new AbsoluteTolerance(4);
        auto range2 = Tolerance::ParseToleranceString(tol);
        Assert::AreEqual(range1->getValue(), range2->getValue());
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual(range1->getValue(), Tolerance::ParseToleranceString(range2->ToString())->getValue());

        Assert::IsTrue(range1->Within(3.9, 0));
        Assert::IsTrue(range1->Within(4, 0));
        Assert::IsFalse(range1->Within(4.1, 0));

        Assert::IsTrue(range1->Within(0, 3.9));
        Assert::IsTrue(range1->Within(0, 4));
        Assert::IsFalse(range1->Within(0, 4.1));

        delete range1;
    }

    void TestRangeAndTolerances::MassRangeFromDAWidth()
    {
        AbsoluteTolerance tempVar(4);
        auto range1 = (&tempVar)->GetRange(10);

        Assert::AreEqual(8, range1->Width);
    }

    void TestRangeAndTolerances::MassRangeFromDAMean()
    {
        AbsoluteTolerance tempVar(4);
        auto range1 = (&tempVar)->GetRange(10);

        Assert::AreEqual(10, range1->Mean);
    }

    void TestRangeAndTolerances::MassRangeFromDAMin()
    {
        AbsoluteTolerance tempVar(4);
        auto range1 = (&tempVar)->GetRange(10);

        Assert::AreEqual(6, range1->Minimum);
    }

    void TestRangeAndTolerances::MassRangeFromDAMax()
    {
        AbsoluteTolerance tempVar(4);
        auto range1 = (&tempVar)->GetRange(10);

        Assert::AreEqual(14, range1->Maximum);
    }

    void TestRangeAndTolerances::MassRangeFromDANegative()
    {
        AbsoluteTolerance tempVar(4);
        auto range1 = (&tempVar)->GetRange(10);
        AbsoluteTolerance tempVar2(-4);
        auto range2 = (&tempVar2)->GetRange(10);

        Assert::AreEqual(0, range1->Minimum - range2->Minimum, 1e-9);
        Assert::AreEqual(0, range1->Maximum - range2->Maximum, 1e-9);
    }

    void TestRangeAndTolerances::RangeFromRange()
    {
        AbsoluteTolerance tempVar(4);
        auto range1 = (&tempVar)->GetRange(10);
        auto range2 = new DoubleRange(range1);
        Assert::AreEqual(0, range1->Minimum - range2->Minimum, 1e-9);
        Assert::AreEqual(0, range1->Maximum - range2->Maximum, 1e-9);

        delete range2;
    }

    void TestRangeAndTolerances::SuperRange()
    {
        AbsoluteTolerance tempVar(4);
        auto range1 = (&tempVar)->GetRange(10);
        AbsoluteTolerance tempVar2(3);
        auto range2 = (&tempVar2)->GetRange(10);
        Assert::IsTrue(range1->IsSuperRange(range2));
    }

    void TestRangeAndTolerances::TestDoubleRangeStuff()
    {
        DoubleRange tempVar(1000000 - 1, 1000000 + 1);
        DoubleRange *range1 = new DoubleRange(&tempVar);
        PpmTolerance tempVar2(1);
        DoubleRange *range2 = (&tempVar2)->GetRange(1000000);

        Assert::AreEqual(0, range1->Minimum - range2->Minimum, 1e-9);
        Assert::AreEqual(0, range1->Maximum - range2->Maximum, 1e-9);
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual("[999999;1000001]", range1->ToString());

        delete range1;
    }

    void TestRangeAndTolerances::MassToleranceConstructorDaValue()
    {
        auto tol = new AbsoluteTolerance(10);

        Assert::AreEqual(10, tol->getValue());

        delete tol;
    }

    void TestRangeAndTolerances::MassToleranceImplicitValue()
    {
        auto tol = Tolerance::ParseToleranceString("10 ppm");

        Assert::AreEqual(10, tol->getValue());

        Assert::AreEqual(1 + 1e-5, tol->GetMaximumValue(1));
        Assert::AreEqual(1 - 1e-5, tol->GetMinimumValue(1));
    }

    void TestRangeAndTolerances::ToleranceWithin1()
    {
        auto tol = new PpmTolerance(10);

        Assert::IsTrue(tol->Within(500, 500.005));

        delete tol;
    }

    void TestRangeAndTolerances::ToleranceNewTest()
    {
        auto tol = new AbsoluteTolerance(1);
        Assert::AreEqual(4, tol->GetRange(5)->Minimum);
        Assert::AreEqual(6, tol->GetRange(5)->Maximum);

        delete tol;
    }

    void TestRangeAndTolerances::ToleranceMinMaxTest()
    {
        auto tol = new AbsoluteTolerance(1);
        Assert::AreEqual(2, tol->GetMaximumValue(1));
        Assert::AreEqual(0, tol->GetMinimumValue(1));

        delete tol;
    }

    void TestRangeAndTolerances::TolerancePPMGetRange()
    {
        auto tol = new PpmTolerance(1);
        Assert::AreEqual(20, tol->GetRange(1e7)->getWidth());

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual("±1.0000 PPM", tol->ToString());

        delete tol;
    }
}
