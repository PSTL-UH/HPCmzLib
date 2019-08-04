#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <cmath>
#include <optional>
#include "stringhelper.h"

#include "../Chemistry/Chemistry.h"
using namespace Chemistry;
#include "../MassSpectrometry/MassSpectrometry.h"
using namespace MassSpectrometry;

#include "../Proteomics/AminoAcidPolymer/Fragment.h"
#include "../Proteomics/AminoAcidPolymer/AminoAcidPolymer.h"
#include "../Proteomics/AminoAcidPolymer/Peptide.h"
#include "../Proteomics/AminoAcidPolymer/ChemicalFormulaModification.h"
#include "../Proteomics/AminoAcidPolymer/ChemicalFormulaTerminus.h"
using namespace Proteomics;

#include "../Proteomics/Fragmentation/Fragmentation.h"
using namespace Proteomics::Fragmentation;

#include "../Proteomics/ProteolyticDigestion/ProteinDigestion.h"
using namespace Proteomics::ProteolyticDigestion;

namespace Test
{
    class TestCompactPeptide final
    {
    public:
        static void TestCompactPeptideMasses_UnmodifiedPeptide();

        static void TestCompactPeptideMasses_nTerminalModifiedPeptide();

        static void TestCompactPeptideMasses_cTerminalModifiedPeptide();

        static void TestCompactPeptideMasses_internallyModifiedPeptide();

        static void TestCompactPeptideMasses_nTerminalModifiedPeptide_NeutralLoss();

        static void TestCompactPeptideMasses_cTerminalModifiedPeptide_NeutralLoss();

        static void TestCompactPeptideMasses_internallyModifiedPeptide_NeutralLoss();

        static void TestCompactPeptideMasses_nTerminalModifiedPeptide_NeutralLoss_DissociationTypes_AnyActivationType_and_HCD();

        // there should be no added neutral losses in this case becuase the allowed dissociation type doesn't
        // match the dissociation type used in the experiment
        static void TestCompactPeptideMasses_nTerminalModifiedPeptide_NeutralLoss_DissociationTypes_CID_and_HCD(); 
    };
}
