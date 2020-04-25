#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <tuple>
#include "stringhelper.h"
#include "tangible_filesystem.h"

// Copyright 2016 Stefan Solntsev
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


#include "../../Chemistry/Chemistry.h"
using namespace Chemistry;

#include "../../MassSpectrometry/MassSpectrometry.h"
using namespace MassSpectrometry;

#include "MzLibUtil.h"
using namespace MzLibUtil;

#include "../../Proteomics/Proteomics.h"
using namespace Proteomics;

#include "../../UsefulProteomicsDatabases/UsefulProteomicsDatabases.h"
using namespace UsefulProteomicsDatabases;

namespace Test
{
    class TestDatabaseLoaders
    {
    public:
        static void LoadModWithNl();

        static void LoadOriginalMismatchedModifications();

        static void TestUpdateUnimod();

        static void TestUpdatePsiMod();

        static void TestUpdateElements();

        static void TestUpdateUniprot();

        static void FilesEqualHash();

        static void FilesLoading(); //delete mzLib\Test\bin\x64\Debug to update your local unimod list

        static void SampleLoadModWithLongMotif();

        static void SampleModFileLoading();

        static void SampleModFileLoadingFail1();

        static void SampleModFileLoadingFail2();

        static void SampleModFileLoadingFail3();

        static void SampleModFileLoadingFail4();

        static void SampleModFileLoadingFail5();

        static void SampleModFileLoadingFail6();

        static void CompactFormReading();

        static void CompactFormReading2();

        static void Modification_read_write_into_proteinDb();

        static void Test_MetaMorpheusStyleProteinDatabaseWriteAndREad();

        static void DoNotWriteSameModTwiceAndDoNotWriteInHeaderSinceDifferent();

        static void TestWritePtmWithNeutralLoss();

        static void TestWritePtmWithDiagnosticIons();

        static void TestWritePtmWithNeutralLossAndDiagnosticIons();
    };
}
