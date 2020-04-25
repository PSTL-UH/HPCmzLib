#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <any>
#include <tuple>
#include "stringhelper.h"
#include "tangible_filesystem.h"

#include "../../Proteomics/Proteomics.h"
using namespace Proteomics;
using namespace Proteomics::ProteolyticDigestion;

#include "../../UsefulProteomicsDatabases/UsefulProteomicsDatabases.h"
using namespace UsefulProteomicsDatabases;

namespace Test
{
    class TestVariantProtein
    {
    public:
        static void SetUpModifications();

        static void VariantProtein();

        static void VariantXml();

        static void SeqVarXmlTest();

        static void LoadSeqVarModifications(const std::string &databaseName, int modIdx, int reversedModIdx);

        static void ReverseDecoyProteolysisProducts(const std::string &databaseName, int beginIdx, int reversedBeginIdx, int endIdx, int reversedEndIdx);

        static void ReverseDecoyDisulfideBonds(const std::string &databaseName, int beginIdx, int reversedBeginIdx, const std::string &reversedSequence, int endIdx, int reversedEndIdx);

        static void ReverseDecoySpliceSites(const std::string &databaseName, int beginIdx, int reversedBeginIdx, int endIdx, int reversedEndIdx);

        static void HomozygousVariantsAtVariedDepths(const std::string &filename, int minVariantDepth, int appliedCount);

        static void AppliedVariants();

        static void StopGained();

        static void MultipleAlternateAlleles();

        static void MultipleAlternateFrameshifts();

        static void VariantSymbolWeirdnessXml();

        static void VariantSymbolWeirdness2Xml();

        static void IndelDecoyError();

        static void IndelDecoyVariants();
    };
}
