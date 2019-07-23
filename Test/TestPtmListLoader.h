#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "stringhelper.h"
#include "tangible_filesystem.h"

using namespace MzLibUtil;
using namespace NUnit::Framework;
using namespace Proteomics;
using namespace UsefulProteomicsDatabases;
namespace Stopwatch = System::Diagnostics::Stopwatch;

namespace Test
{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [TestFixture] public sealed class TestPtmListLoader
    class TestPtmListLoader final
    {
    private:
        static Stopwatch *privateStopwatch;

        static Stopwatch *getStopwatch();
        static void setStopwatch(Stopwatch *value);

    public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [SetUp] public static void Setuppp()
        static void Setuppp();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [TearDown] public static void TearDown()
        static void TearDown();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void SampleModFileLoading()
        static void SampleModFileLoading();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test][TestCase("CommonArtifacts.txt", 33)][TestCase("CommonBiological.txt", 35)] public static void Test_ReadAllModsFromFile(string filename, int modCount)
        static void Test_ReadAllModsFromFile(const std::string &filename, int modCount);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test][TestCase("CommonArtifacts.txt")][TestCase("CommonBiological.txt")] public static void Test_ModsFromFileAreSorted(string filename)
        static void Test_ModsFromFileAreSorted(const std::string &filename);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void Test_ModsWithComments()
        static void Test_ModsWithComments();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test][TestCase("sampleModFileFail1.txt")][TestCase("sampleModFileFail2.txt")][TestCase("sampleModFileFail5.txt")][TestCase("sampleModFileFail6.txt")][TestCase("sampleModFileFail_missingPosition.txt")][TestCase("sampleModFileFail_missingChemicalFormulaAndMonoisotopicMass.txt")] public static void SampleModFileLoadingFail1General(string filename)
        static void SampleModFileLoadingFail1General(const std::string &filename);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void PTMListLoader_ModWithComments_Equals_ModWithoutComments()
        static void PTMListLoader_ModWithComments_Equals_ModWithoutComments();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test][TestCase("sampleModFileFail3.txt", "Input string for chemical formula was in an incorrect format: $%&$%")][TestCase("m.txt", "0 or 238.229666 is not a valid monoisotopic mass")] public static void SampleModFileLoadingFail3General(string filename, string errorMessage)
        static void SampleModFileLoadingFail3General(const std::string &filename, const std::string &errorMessage);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test][TestCase("sampleModFileDouble.txt")][TestCase("sampleModFileDouble2.txt")] public static void CompactFormReadingGeneral(string filename)
        static void CompactFormReadingGeneral(const std::string &filename);

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestReadingInvalidModifications()
        static void TestReadingInvalidModifications();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestReadingIdWithMotif()
        static void TestReadingIdWithMotif();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestInvalidModTypeError()
        static void TestInvalidModTypeError();
    };
}
