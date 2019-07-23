#pragma once

#include "../MassSpectrometry/Enums/DissociationType.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <tuple>
#include <optional>
#include "stringhelper.h"

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

using namespace Chemistry;
using namespace MassSpectrometry;
using namespace MzLibUtil;
using namespace NUnit::Framework;
using namespace Proteomics;
using namespace Proteomics::AminoAcidPolymer;
using namespace Proteomics::Fragmentation;
using namespace Proteomics::ProteolyticDigestion;
namespace Stopwatch = System::Diagnostics::Stopwatch;

namespace Test
{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [TestFixture] public sealed class TestFragments
    class TestFragments final
    {
    private:
        static Stopwatch *privateStopwatch;

        Peptide *_mockPeptideEveryAminoAcid;
    public:
        virtual ~TestFragments()
        {
            delete _mockPeptideEveryAminoAcid;
        }

    private:
        static Stopwatch *getStopwatch();
        static void setStopwatch(Stopwatch *value);

    public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [SetUp] public static void Setup()
        static void Setup();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [TearDown] public static void TearDown()
        static void TearDown();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [SetUp] public void SetUp()
        void SetUp();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void FragmentNumberToHigh()
        void FragmentNumberToHigh();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void FragmentName()
        void FragmentName();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void FragmentAllBIons()
        void FragmentAllBIons();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void FragmentAnotherTest()
        void FragmentAnotherTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test][TestCase(DissociationType.HCD, new[] { ProductType.b, ProductType.y })][TestCase(DissociationType.ECD, new[] { ProductType.c, ProductType.y, ProductType.zDot })][TestCase(DissociationType.ETD, new[] { ProductType.c, ProductType.y, ProductType.zDot })][TestCase(DissociationType.EThcD, new[] { ProductType.b, ProductType.y })][TestCase(DissociationType.AnyActivationType, new[] { ProductType.b, ProductType.y })] public void TestDissociationProductTypes(DissociationType dissociationType, IEnumerable<ProductType> expectedProductTypes)
        void TestDissociationProductTypes(DissociationType dissociationType, std::vector<ProductType> &expectedProductTypes);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void FragmentNTermModTest()
        void FragmentNTermModTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void FragmentModifications()
        void FragmentModifications();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void ChemicalFormulaFragment()
        void ChemicalFormulaFragment();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void TestGetSiteDeterminingFragments()
        void TestGetSiteDeterminingFragments();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void TestFormulaTerminusMods()
        void TestFormulaTerminusMods();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void CleavageIndicesTest()
        void CleavageIndicesTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void TestGetIonCapFailFail()
        void TestGetIonCapFailFail();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void TestGetTerminusFail()
        void TestGetTerminusFail();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void Test_GetTheoreticalFragments_UnmodifiedPeptide()
        static void Test_GetTheoreticalFragments_UnmodifiedPeptide();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void Test_GetTheoreticalFragments_nTerminalModifiedPeptide()
        static void Test_GetTheoreticalFragments_nTerminalModifiedPeptide();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void Test_GetTheoreticalFragments_cTerminalModifiedPeptide()
        static void Test_GetTheoreticalFragments_cTerminalModifiedPeptide();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void Test_GetTheoreticalFragments_internallyModifiedPeptide()
        static void Test_GetTheoreticalFragments_internallyModifiedPeptide();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void Test_GetTheoreticalFragments_nTerminalModifiedPeptide_NeutralLoss()
        static void Test_GetTheoreticalFragments_nTerminalModifiedPeptide_NeutralLoss();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void Test_GetTheoreticalFragments_cTerminalModifiedPeptide_NeutralLoss()
        static void Test_GetTheoreticalFragments_cTerminalModifiedPeptide_NeutralLoss();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void Test_GetTheoreticalFragments_internallyModifiedPeptide_NeutralLoss()
        static void Test_GetTheoreticalFragments_internallyModifiedPeptide_NeutralLoss();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void Test_GetTheoreticalFragments_nTerminalModifiedPeptide_NeutralLoss_DissociationTypes_AnyActivationType_and_HCD()
        static void Test_GetTheoreticalFragments_nTerminalModifiedPeptide_NeutralLoss_DissociationTypes_AnyActivationType_and_HCD();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void Test_GetTheoreticalFragments_nTerminalModifiedPeptide_NeutralLoss_DissociationTypes_CID_and_HCD()
        static void Test_GetTheoreticalFragments_nTerminalModifiedPeptide_NeutralLoss_DissociationTypes_CID_and_HCD(); //there should be no added neutral losses in this case becuase the allowed dissociation type doesn't match the dissociation type used in the experiment

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void Test_GetTheoreticalFragments_ProductTypeLabel()
        static void Test_GetTheoreticalFragments_ProductTypeLabel();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void Test_Fragment_DiagnosticIons()
        static void Test_Fragment_DiagnosticIons();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void Test_Fragment_MolecularIon_NeutralLoss()
        static void Test_Fragment_MolecularIon_NeutralLoss();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void Test_Fragment_DiagnosticIons_unmatchedDissociationType()
        static void Test_Fragment_DiagnosticIons_unmatchedDissociationType();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void Test_Fragment_MolecularIon_NeutralLoss_unmatchedDissociationType()
        static void Test_Fragment_MolecularIon_NeutralLoss_unmatchedDissociationType();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void Test_NeutralMassShiftFromProductType()
        static void Test_NeutralMassShiftFromProductType();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void Test_NeutralMassShiftFromProductType_Exceptions()
        static void Test_NeutralMassShiftFromProductType_Exceptions();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void Test_CustomDissociationType()
        static void Test_CustomDissociationType();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void Test_TerminusSpecificProductTypes()
        static void Test_TerminusSpecificProductTypes();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void Test_TerminusSpecificProductTypesFromPeptideWithSetMods()
        static void Test_TerminusSpecificProductTypesFromPeptideWithSetMods();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void Test_MatchedFragmentIonToString()
        static void Test_MatchedFragmentIonToString();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void Test_CID_Fragmentation_No_Unmodified_B1_ions()
        static void Test_CID_Fragmentation_No_Unmodified_B1_ions();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test][TestCase(DissociationType.HCD, 12)][TestCase(DissociationType.ETD, 17)][TestCase(DissociationType.ECD, 17)][TestCase(DissociationType.EThcD, 23)] public static void Test_ETD_ECD_EThcD_Fragmentation_No_FragmentsAtProline(DissociationType dissociationType, int fragmentCount)
        static void Test_ETD_ECD_EThcD_Fragmentation_No_FragmentsAtProline(DissociationType dissociationType, int fragmentCount);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void CheckProlineFragments()
        static void CheckProlineFragments();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void CheckProlineFragments2()
        static void CheckProlineFragments2();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void CheckProlineFragments3()
        static void CheckProlineFragments3();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void CheckProlineFragments4()
        static void CheckProlineFragments4();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestFragmentAnnotations()
        static void TestFragmentAnnotations();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestFragmentErrors()
        static void TestFragmentErrors();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestFragmentEquality()
        static void TestFragmentEquality();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestThatDiagnosticIonsDontDuplicate()
        static void TestThatDiagnosticIonsDontDuplicate();
    };
}
