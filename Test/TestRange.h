﻿#pragma once

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work Copyright 2016 Stefan Solntsev
//
// This file (TestRange.cs) is part of MassSpectrometry.Tests.
//
// MassSpectrometry.Tests is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MassSpectrometry.Tests is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with MassSpectrometry.Tests. If not, see <http://www.gnu.org/licenses/>.

using namespace MzLibUtil;
using namespace NUnit::Framework;

namespace Test {
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [TestFixture] public sealed class RangeTest
    class RangeTest final {
//        #region Public Methods

    public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void RangeSubRange()
        void RangeSubRange();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void RangeSubRangeReverseIsFalse()
        void RangeSubRangeReverseIsFalse();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void RangeOverlappingIsFalse()
        void RangeOverlappingIsFalse();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void RangeOverlappingIsFalseReverse()
        void RangeOverlappingIsFalseReverse();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void RangeOverlappingIsTrue()
        void RangeOverlappingIsTrue();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void RangeOverlappingIsTrueReverse()
        void RangeOverlappingIsTrueReverse();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void RangeOverlappingIsTrueLarger()
        void RangeOverlappingIsTrueLarger();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void RangeOverlappingIsTrueSmaller()
        void RangeOverlappingIsTrueSmaller();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void RangeOverlappingIsTrueItSelf()
        void RangeOverlappingIsTrueItSelf();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void RangeDoesContainItem()
        void RangeDoesContainItem();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void RangeDoesnotContainItemHigher()
        void RangeDoesnotContainItemHigher();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void RangeDoesnotContainItemLower()
        void RangeDoesnotContainItemLower();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void RangeDoesContainItemLowerBounds()
        void RangeDoesContainItemLowerBounds();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void RangeDoesContainItemUpperBounds()
        void RangeDoesContainItemUpperBounds();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void RangeCompareToBelow()
        void RangeCompareToBelow();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void RangeCompareToWithin()
        void RangeCompareToWithin();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void RangeCompareToAbove()
        void RangeCompareToAbove();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void RangesAreEquivalentNotReference()
        void RangesAreEquivalentNotReference();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void MassRangeFromDAWidth()
        void MassRangeFromDAWidth();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void MassRangeFromDAMean()
        void MassRangeFromDAMean();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void MassRangeFromDAMin()
        void MassRangeFromDAMin();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void MassRangeFromDAMax()
        void MassRangeFromDAMax();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void MassRangeFromDANegative()
        void MassRangeFromDANegative();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void RangeFromRange()
        void RangeFromRange();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void SuperRange()
        void SuperRange();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void TestDoubleRangeStuff()
        void TestDoubleRangeStuff();

//        #endregion Public Methods
    };
}
