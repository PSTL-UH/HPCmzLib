#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <tuple>
#include "stringhelper.h"
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

#include "../../Proteomics/Proteomics.h"
using namespace Proteomics;

#include "../../UsefulProteomicsDatabases/UsefulProteomicsDatabases.h"
using namespace UsefulProteomicsDatabases;

namespace Test
{
    class TestProteinReader final
    {
    public:
        static void SetUpModifications();

        static void MergeACoupleProteins();

        static void XmlTest();

        static void DisulfideXmlTest();

        static void XmlTest_2entry();

        static void XmlGzTest();

        static void XmlFunkySequenceTest();

        static void XmlModifiedStartTest();

        static void FastaTest();

        static void BadFastaTest();

        static void Load_fasta_handle_tooHigh_indices();

        static void Read_xml_mod_collision();

        //[TestCase("exclude_me_not", true)]
        static void Read_xml_exclude_mods(const std::string &excludeString, bool isExcluded);

        static void CompareOxidationWithAndWithoutCf();

        static void TestReverseDecoyXML();

        static void TestSlideDecoyXML();

        static void TestReverseDecoyFasta();

        static void TestSlideDecoyFasta();
    };
}
