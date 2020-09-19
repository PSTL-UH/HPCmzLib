#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <tuple>
#include "../include/stringhelper.h"
#include "../Proteomics/Proteomics.h"

using namespace Proteomics;
using namespace Proteomics::Fragmentation;
using namespace Proteomics::ProteolyticDigestion;

namespace Test
{
    class TestPeptideWithSetMods final
    {
    public:
        /// <summary>
        /// The purpose of this test is to ensure that two peptides digested from two different proteases are not equal even
        /// if their sequences are equal
        /// This is important for multiprotease parsimony in MetaMorpheus
        /// </summary>
        static void TestDifferentProteaseEquals();

        static void TestSemiFewCleavages();

        static void TestNonAndSemiSpecificDigests();

    private:
        static void TestSingleProteases(Protein *protein, InitiatorMethionineBehavior initiatorMethionineBehavior,
                                        FragmentationTerminus fragmentationTerminus, int numSequencesExpected);

    public:
        static void TestHardToParseModifiedSequence();

        static void TestCTermAndLastSideChainModParsing();
    };
}
