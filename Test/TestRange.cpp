#include "TestRange.h"
#include "../MzLibUtil/DoubleRange.h"
#include "../MzLibUtil/AbsoluteTolerance.h"
#include "../MzLibUtil/PpmTolerance.h"

using namespace MzLibUtil;
using namespace NUnit::Framework;

namespace Test {

    void RangeTest::RangeSubRange() {
        auto a = new DoubleRange(5, 7);
        auto b = new DoubleRange(0, 10);

        Assert::IsTrue(a->IsSubRange(b));

//C# TO C++ CONVERTER TODO TASK: A 'delete b' statement was not added since b was passed to a method or constructor. Handle memory management manually.
        delete a;
    }

    void RangeTest::RangeSubRangeReverseIsFalse() {
        auto a = new DoubleRange(5, 7);
        auto b = new DoubleRange(0, 10);

        Assert::IsFalse(b->IsSubRange(a));

        delete b;
//C# TO C++ CONVERTER TODO TASK: A 'delete a' statement was not added since a was passed to a method or constructor. Handle memory management manually.
    }

    void RangeTest::RangeOverlappingIsFalse() {
        auto range1 = new DoubleRange(5, 10);
        auto range2 = new DoubleRange(15, 20);

        Assert::IsFalse(range1->IsOverlapping(range2));

//C# TO C++ CONVERTER TODO TASK: A 'delete range2' statement was not added since range2 was passed to a method or constructor. Handle memory management manually.
        delete range1;
    }

    void RangeTest::RangeOverlappingIsFalseReverse() {
        auto range1 = new DoubleRange(5, 10);
        auto range2 = new DoubleRange(15, 20);

        Assert::IsFalse(range2->IsOverlapping(range1));

        delete range2;
//C# TO C++ CONVERTER TODO TASK: A 'delete range1' statement was not added since range1 was passed to a method or constructor. Handle memory management manually.
    }

    void RangeTest::RangeOverlappingIsTrue() {
        auto range1 = new DoubleRange(5, 10);
        auto range2 = new DoubleRange(7, 12);

        Assert::IsTrue(range1->IsOverlapping(range2));

//C# TO C++ CONVERTER TODO TASK: A 'delete range2' statement was not added since range2 was passed to a method or constructor. Handle memory management manually.
        delete range1;
    }

    void RangeTest::RangeOverlappingIsTrueReverse() {
        auto range1 = new DoubleRange(5, 10);
        auto range2 = new DoubleRange(7, 12);

        Assert::IsTrue(range2->IsOverlapping(range1));

        delete range2;
//C# TO C++ CONVERTER TODO TASK: A 'delete range1' statement was not added since range1 was passed to a method or constructor. Handle memory management manually.
    }

    void RangeTest::RangeOverlappingIsTrueLarger() {
        auto range1 = new DoubleRange(0, 10);
        auto range2 = new DoubleRange(3, 7);

        Assert::IsTrue(range1->IsOverlapping(range2));

//C# TO C++ CONVERTER TODO TASK: A 'delete range2' statement was not added since range2 was passed to a method or constructor. Handle memory management manually.
        delete range1;
    }

    void RangeTest::RangeOverlappingIsTrueSmaller() {
        auto range1 = new DoubleRange(0, 10);
        auto range2 = new DoubleRange(3, 7);

        Assert::IsTrue(range2->IsOverlapping(range1));

        delete range2;
//C# TO C++ CONVERTER TODO TASK: A 'delete range1' statement was not added since range1 was passed to a method or constructor. Handle memory management manually.
    }

    void RangeTest::RangeOverlappingIsTrueItSelf() {
        auto range1 = new DoubleRange(0, 10);

        Assert::IsTrue(range1->IsOverlapping(range1));

//C# TO C++ CONVERTER TODO TASK: A 'delete range1' statement was not added since range1 was passed to a method or constructor. Handle memory management manually.
    }

    void RangeTest::RangeDoesContainItem() {
        auto range1 = new DoubleRange(3, 10);

        Assert::IsTrue(range1->Contains(5));

        delete range1;
    }

    void RangeTest::RangeDoesnotContainItemHigher() {
        auto range1 = new DoubleRange(3, 10);

        Assert::IsFalse(range1->Contains(12));

        delete range1;
    }

    void RangeTest::RangeDoesnotContainItemLower() {
        auto range1 = new DoubleRange(3, 10);

        Assert::IsFalse(range1->Contains(1));

        delete range1;
    }

    void RangeTest::RangeDoesContainItemLowerBounds() {
        auto range1 = new DoubleRange(3, 10);

        Assert::IsTrue(range1->Contains(3));

        delete range1;
    }

    void RangeTest::RangeDoesContainItemUpperBounds() {
        auto range1 = new DoubleRange(3, 10);

        Assert::IsTrue(range1->Contains(10));

        delete range1;
    }

    void RangeTest::RangeCompareToBelow() {
        auto range = new DoubleRange(3, 10);
        int value = 1;

        int comp = range->CompareTo(value);

        Assert::AreEqual(-1, comp);

        delete range;
    }

    void RangeTest::RangeCompareToWithin() {
        auto range = new DoubleRange(3, 10);
        int value = 5;

        int comp = range->CompareTo(value);

        Assert::AreEqual(0, comp);

        delete range;
    }

    void RangeTest::RangeCompareToAbove() {
        auto range = new DoubleRange(3, 10);
        int value = 12;

        int comp = range->CompareTo(value);

        Assert::AreEqual(1, comp);

        delete range;
    }

    void RangeTest::RangesAreEquivalentNotReference() {
        auto range1 = new DoubleRange(3, 10);
        auto range2 = new DoubleRange(3, 10);

        Assert::AreNotSame(range1, range2);

//C# TO C++ CONVERTER TODO TASK: A 'delete range2' statement was not added since range2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete range1' statement was not added since range1 was passed to a method or constructor. Handle memory management manually.
    }

    void RangeTest::MassRangeFromDAWidth() {
        AbsoluteTolerance tempVar(4);
        auto range1 = (&tempVar)->GetRange(10);

        Assert::AreEqual(8, range1->Width);
    }

    void RangeTest::MassRangeFromDAMean() {
        AbsoluteTolerance tempVar(4);
        auto range1 = (&tempVar)->GetRange(10);

        Assert::AreEqual(10, range1->Mean);
    }

    void RangeTest::MassRangeFromDAMin() {
        AbsoluteTolerance tempVar(4);
        auto range1 = (&tempVar)->GetRange(10);

        Assert::AreEqual(6, range1->Minimum);
    }

    void RangeTest::MassRangeFromDAMax() {
        AbsoluteTolerance tempVar(4);
        auto range1 = (&tempVar)->GetRange(10);

        Assert::AreEqual(14, range1->Maximum);
    }

    void RangeTest::MassRangeFromDANegative() {
        AbsoluteTolerance tempVar(4);
        auto range1 = (&tempVar)->GetRange(10);
        AbsoluteTolerance tempVar2(-4);
        auto range2 = (&tempVar2)->GetRange(10);

        Assert::AreEqual(0, range1->Minimum - range2->Minimum, 1e-9);
        Assert::AreEqual(0, range1->Maximum - range2->Maximum, 1e-9);
    }

    void RangeTest::RangeFromRange() {
        AbsoluteTolerance tempVar(4);
        auto range1 = (&tempVar)->GetRange(10);
        auto range2 = new DoubleRange(range1);
        Assert::AreEqual(0, range1->Minimum - range2->Minimum, 1e-9);
        Assert::AreEqual(0, range1->Maximum - range2->Maximum, 1e-9);

        delete range2;
    }

    void RangeTest::SuperRange() {
        AbsoluteTolerance tempVar(4);
        auto range1 = (&tempVar)->GetRange(10);
        AbsoluteTolerance tempVar2(3);
        auto range2 = (&tempVar2)->GetRange(10);
        Assert::IsTrue(range1->IsSuperRange(range2));
    }

    void RangeTest::TestDoubleRangeStuff() {
        DoubleRange tempVar(1000000 - 1, 1000000 + 1);
        DoubleRange *range1 = new DoubleRange(&tempVar);
        PpmTolerance tempVar2(1);
        DoubleRange *range2 = (&tempVar2)->GetRange(1000000);

        Assert::AreEqual(0, range1->Minimum - range2->Minimum, 1e-9);
        Assert::AreEqual(0, range1->Maximum - range2->Maximum, 1e-9);
//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
        Assert::AreEqual(L"[999999;1000001]", range1->ToString());

        delete range1;
    }
}
