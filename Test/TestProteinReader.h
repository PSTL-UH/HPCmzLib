#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cmath>
#include <tuple>
#include <optional>
#include "tangible_filesystem.h"

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

using namespace NUnit::Framework;
using namespace Proteomics;
using namespace UsefulProteomicsDatabases;

namespace Test {
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [TestFixture] public static class TestProteinReader
    class TestProteinReader final {
//        #region Public Methods

    public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void Compare_protein_properties()
        static void Compare_protein_properties();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void Merge_a_couple_proteins()
        static void Merge_a_couple_proteins();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void XmlTest()
        static void XmlTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void SeqVarXmlTest()
        static void SeqVarXmlTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void DisulfideXmlTest()
        static void DisulfideXmlTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void XmlTest_2entry()
        static void XmlTest_2entry();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void XmlGzTest()
        static void XmlGzTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void XmlFunkySequenceTest()
        static void XmlFunkySequenceTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void XmlModifiedStartTest()
        static void XmlModifiedStartTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void FastaTest()
        static void FastaTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void Load_fasta_handle_tooHigh_indices()
        static void Load_fasta_handle_tooHigh_indices();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void Read_xml_mod_collision()
        static void Read_xml_mod_collision();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void Read_xml_exclude_mods()
        static void Read_xml_exclude_mods();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void CompareOxidationWithAndWithoutCf()
        static void CompareOxidationWithAndWithoutCf();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void TestKeywordAugmentation()
        static void TestKeywordAugmentation();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void TestReverseDecoyXML()
        static void TestReverseDecoyXML();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void TestSlideDecoyXML()
        static void TestSlideDecoyXML();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void TestReverseDecoyFasta()
        static void TestReverseDecoyFasta();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void TestSlideDecoyFasta()
        static void TestSlideDecoyFasta();

//        #endregion Public Methods
    };
}
