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

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Proteomics { class Modification; }

using namespace NUnit::Framework;
using namespace Proteomics;
using namespace Proteomics::ProteolyticDigestion;
using namespace UsefulProteomicsDatabases;
namespace Stopwatch = System::Diagnostics::Stopwatch;

namespace Test
{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [TestFixture] public class TestVariantProtein
    class TestVariantProtein
    {
    private:
        static Stopwatch *privateStopwatch;

        static std::vector<Modification*> UniProtPtms;
        static Stopwatch *getStopwatch();
        static void setStopwatch(Stopwatch *value);

    public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [OneTimeSetUp] public static void SetUpModifications()
        static void SetUpModifications();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [SetUp] public static void Setuppp()
        static void Setuppp();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [TearDown] public static void TearDown()
        static void TearDown();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void VariantProtein()
        static void VariantProtein();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void VariantXml()
        void VariantXml();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void SeqVarXmlTest()
        static void SeqVarXmlTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test][TestCase("oblm1.xml", 1, 1)][TestCase("oblm2.xml", 3, 4)][TestCase("oblm3.xml", 3, 5)] public static void LoadSeqVarModifications(string databaseName, int modIdx, int reversedModIdx)
        static void LoadSeqVarModifications(const std::string &databaseName, int modIdx, int reversedModIdx);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [TestCase("ranges1.xml", 1, 2, 5, 6)][TestCase("ranges2.xml", 1, 1, 5, 5)] public static void ReverseDecoyProteolysisProducts(string databaseName, int beginIdx, int reversedBeginIdx, int endIdx, int reversedEndIdx)
        static void ReverseDecoyProteolysisProducts(const std::string &databaseName, int beginIdx, int reversedBeginIdx, int endIdx, int reversedEndIdx);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [TestCase("bonds1.xml", 2, 3, "DICPCP", 4, 5)][TestCase("bonds2.xml", 2, 4, "MDICPC", 4, 6)] public static void ReverseDecoyDisulfideBonds(string databaseName, int beginIdx, int reversedBeginIdx, string reversedSequence, int endIdx, int reversedEndIdx)
        static void ReverseDecoyDisulfideBonds(const std::string &databaseName, int beginIdx, int reversedBeginIdx, const std::string &reversedSequence, int endIdx, int reversedEndIdx);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test][TestCase("splices1.xml", 2, 4, 3, 5)][TestCase("splices2.xml", 2, 5, 3, 6)][TestCase("splices3.xml", 2, 5, 2, 5)][TestCase("splices4.xml", 2, 6, 2, 6)][TestCase("splices5.xml", 1, 6, 1, 6)][TestCase("splices6.xml", 1, 1, 1, 1)][TestCase("splices7.xml", 1, 5, 2, 6)][TestCase("splices8.xml", 1, 5, 2, 6)] public static void ReverseDecoySpliceSites(string databaseName, int beginIdx, int reversedBeginIdx, int endIdx, int reversedEndIdx)
        static void ReverseDecoySpliceSites(const std::string &databaseName, int beginIdx, int reversedBeginIdx, int endIdx, int reversedEndIdx);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test][TestCase("HomozygousHLA.xml", 1, 18)][TestCase("HomozygousHLA.xml", 10, 17)] public static void HomozygousVariantsAtVariedDepths(string filename, int minVariantDepth, int appliedCount)
        static void HomozygousVariantsAtVariedDepths(const std::string &filename, int minVariantDepth, int appliedCount);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void AppliedVariants()
        static void AppliedVariants();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void StopGained()
        static void StopGained();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void MultipleAlternateAlleles()
        static void MultipleAlternateAlleles();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void MultipleAlternateFrameshifts()
        static void MultipleAlternateFrameshifts();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void VariantSymbolWeirdnessXml()
        void VariantSymbolWeirdnessXml();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void VariantSymbolWeirdness2Xml()
        void VariantSymbolWeirdness2Xml();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void IndelDecoyError()
        void IndelDecoyError();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public void IndelDecoyVariants()
        void IndelDecoyVariants();
    };
}
