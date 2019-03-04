#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cmath>
#include <tuple>
#include "tangible_filesystem.h"

// opyright 2016 Stefan Solntsev
//
// This file (ChemicalFormula.cs) is part of Chemistry Library.
//
// Chemistry Library is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Chemistry Library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with Chemistry Library. If not, see <http://www.gnu.org/licenses/>

using namespace Chemistry;
using namespace MzLibUtil;
using namespace NUnit::Framework;
using namespace Proteomics;
using namespace UsefulProteomicsDatabases;

namespace Test {
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [TestFixture] public class DatabaseLoaderTests
    class DatabaseLoaderTests {
//        #region Public Methods

    public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public static void LoadModWithNl()
        static void LoadModWithNl();

        void TestUpdateUnimod();

        void TestUpdatePsiMod();

        void TestUpdateElements();

        void TestUpdateUniprot();

        void FilesEqualHash();

        void FilesLoading();

        void SampleModFileLoading();

        void SampleModFileLoadingFail1();

        void SampleModFileLoadingFail2();

        void SampleModFileLoadingFail3();

        void SampleModFileLoadingFail4();

        void SampleModFileLoadingFail5();

        void SampleModFileLoadingFail6();

        void CompactFormReading();

        void CompactFormReading2();

        void Modification_read_write_into_proteinDb();

        void DoNotWriteSameModTwiceAndDoNotWriteInHeaderSinceDifferent();

        void DoNotWriteSameModTwiceButWriteInHeaderSinceDifferent();

    };
}
