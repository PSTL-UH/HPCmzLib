#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <cmath>
#include <optional>
#include "stringhelper.h"

using namespace Chemistry;
using namespace MassSpectrometry;
using namespace NUnit::Framework;
using namespace Proteomics;
using namespace Proteomics::Fragmentation;
using namespace Proteomics::ProteolyticDigestion;
namespace Stopwatch = System::Diagnostics::Stopwatch;

namespace Test
{
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [TestFixture] public sealed class TestCompactPeptide
    class TestCompactPeptide final
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
//ORIGINAL LINE: [Test] public static void TestCompactPeptideMasses_UnmodifiedPeptide()
        static void TestCompactPeptideMasses_UnmodifiedPeptide();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestCompactPeptideMasses_nTerminalModifiedPeptide()
        static void TestCompactPeptideMasses_nTerminalModifiedPeptide();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestCompactPeptideMasses_cTerminalModifiedPeptide()
        static void TestCompactPeptideMasses_cTerminalModifiedPeptide();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestCompactPeptideMasses_internallyModifiedPeptide()
        static void TestCompactPeptideMasses_internallyModifiedPeptide();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestCompactPeptideMasses_nTerminalModifiedPeptide_NeutralLoss()
        static void TestCompactPeptideMasses_nTerminalModifiedPeptide_NeutralLoss();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestCompactPeptideMasses_cTerminalModifiedPeptide_NeutralLoss()
        static void TestCompactPeptideMasses_cTerminalModifiedPeptide_NeutralLoss();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestCompactPeptideMasses_internallyModifiedPeptide_NeutralLoss()
        static void TestCompactPeptideMasses_internallyModifiedPeptide_NeutralLoss();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestCompactPeptideMasses_nTerminalModifiedPeptide_NeutralLoss_DissociationTypes_AnyActivationType_and_HCD()
        static void TestCompactPeptideMasses_nTerminalModifiedPeptide_NeutralLoss_DissociationTypes_AnyActivationType_and_HCD();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestCompactPeptideMasses_nTerminalModifiedPeptide_NeutralLoss_DissociationTypes_CID_and_HCD()
        static void TestCompactPeptideMasses_nTerminalModifiedPeptide_NeutralLoss_DissociationTypes_CID_and_HCD(); //there should be no added neutral losses in this case becuase the allowed dissociation type doesn't match the dissociation type used in the experiment
    };
}
