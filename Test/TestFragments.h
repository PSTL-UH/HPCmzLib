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

#include "../Chemistry/Chemistry.h"
using namespace Chemistry;

#include "../MassSpectrometry/MassSpectrometry.h"
using namespace MassSpectrometry;

#include "MzLibUtil.h"
using namespace MzLibUtil;

#include "../Proteomics/AminoAcidPolymer/Fragment.h"
#include "../Proteomics/AminoAcidPolymer/AminoAcidPolymer.h"
#include "../Proteomics/AminoAcidPolymer/Peptide.h"
#include "../Proteomics/AminoAcidPolymer/ChemicalFormulaModification.h"
#include "../Proteomics/AminoAcidPolymer/ChemicalFormulaTerminus.h"
using namespace Proteomics;
using namespace Proteomics::AminoAcidPolymer;

#include "../Proteomics/Fragmentation/Fragmentation.h"
using namespace Proteomics::Fragmentation;

#include "../Proteomics/ProteolyticDigestion/ProteinDigestion.h"
using namespace Proteomics::ProteolyticDigestion;

namespace Test
{
    class TestFragments final
    {

    public:
        static void FragmentNumberToHigh();

        static void FragmentName();

        static void FragmentAllBIons();

        static void FragmentAnotherTest();

        static void TestDissociationProductTypes(DissociationType dissociationType, std::vector<ProductType> &expectedProductTypes);

        static void FragmentNTermModTest();

        static void FragmentModifications();

        static void ChemicalFormulaFragment();

        static void TestGetSiteDeterminingFragments();

        static void TestFormulaTerminusMods();

        static void CleavageIndicesTest();

        static void TestGetIonCapFailFail();

        static void TestGetTerminusFail();

        static void Test_GetTheoreticalFragments_UnmodifiedPeptide();

        static void Test_GetTheoreticalFragments_nTerminalModifiedPeptide();

        static void Test_GetTheoreticalFragments_cTerminalModifiedPeptide();

        static void Test_GetTheoreticalFragments_internallyModifiedPeptide();

        static void Test_GetTheoreticalFragments_nTerminalModifiedPeptide_NeutralLoss();

        static void Test_GetTheoreticalFragments_cTerminalModifiedPeptide_NeutralLoss();

        static void Test_GetTheoreticalFragments_internallyModifiedPeptide_NeutralLoss();

        static void Test_GetTheoreticalFragments_nTerminalModifiedPeptide_NeutralLoss_DissociationTypes_AnyActivationType_and_HCD();

        //there should be no added neutral losses in this case becuase the allowed dissociation type
        // doesn't match the dissociation type used in the experiment
        static void Test_GetTheoreticalFragments_nTerminalModifiedPeptide_NeutralLoss_DissociationTypes_CID_and_HCD(); 

        static void Test_GetTheoreticalFragments_ProductTypeLabel();

        static void Test_Fragment_DiagnosticIons();

        static void Test_Fragment_MolecularIon_NeutralLoss();

        static void Test_Fragment_DiagnosticIons_unmatchedDissociationType();

        static void Test_Fragment_MolecularIon_NeutralLoss_unmatchedDissociationType();

        static void Test_NeutralMassShiftFromProductType();

        static void Test_NeutralMassShiftFromProductType_Exceptions();

        static void Test_CustomDissociationType();

        static void Test_TerminusSpecificProductTypes();

        static void Test_TerminusSpecificProductTypesFromPeptideWithSetMods();

        static void Test_MatchedFragmentIonToString();

        static void Test_CID_Fragmentation_No_Unmodified_B1_ions();

        static void Test_ETD_ECD_EThcD_Fragmentation_No_FragmentsAtProline(DissociationType dissociationType, int fragmentCount);

        static void CheckProlineFragments();

        static void CheckProlineFragments2();

        static void CheckProlineFragments3();

        static void CheckProlineFragments4();

        static void TestFragmentAnnotations();

        static void TestFragmentErrors();

        static void TestFragmentEquality();

        static void TestThatDiagnosticIonsDontDuplicate();
    };
}
