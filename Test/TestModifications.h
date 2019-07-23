#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work copyright 2016 Stefan Solntsev
//
// This file (TestFragments.cs) is part of Proteomics.
//
// Proteomics is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Proteomics is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with Proteomics. If not, see <http://www.gnu.org/licenses/>.


#include "../Chemistry/Chemistry.h"
using namespace Chemistry;

#include "../MzLibUtil/MzLibUtil.h"
using namespace MzLibUtil;

#include "../Proteomics/Proteomics.h"
using namespace Proteomics;

//#include "../UsefulProteomicsDatabases/UsefulProteomicsDatabases.h"
//using namespace UsefulProteomicsDatabases;

namespace Test {
    class TestModifications final {

    public:
        static void Test_modificationsHashCode();

        static void Test_ModificationWithNoMassWritten();

        static void NameAndSites();

        static void ModificationEquality();

        static void ModificationSitesTest();

        static void Sites();

        static void ModificationCollectionTest();

        static void ModificationCollectionTest2();

        static void ModificationWithMultiplePossibilitiesTest();

        static void ModificationSitesTest55();

        static void ChemicalFormulaModificaiton();

        static void ModificationCollectionScrambledEquals();

        static void Test_modification_hash_set();

        static void Test_modification2_hash_set();

        static void Test_modification3_hash_set();

        static void TestInvalidModificationHash();

        static void TestFragmentationNoMod();

        static void TestFragmentationModNoNeutralLoss();

        static void Test_FragmentationModNeutralLoss();

        static void Test_FragmentationTwoModNeutralLoss();

        static void Test_FragmentationTwoModNeutralLossTwoFragTypes();
        
        static void TestCompactPeptideSerialization();

        static void TestSerializationPeptideFromString();

        static void TestSerializationPeptideFromProtein();

        static void TestSerializationPeptideFromProteinWithMod();

        static void TestFragmentNterminalModifiedPeptide();

        static void TestFragmentCTerminalModifiedPeptide();
    };
}
