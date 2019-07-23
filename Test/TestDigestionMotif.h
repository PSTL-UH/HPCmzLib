#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "stringhelper.h"

#include "MzLibUtil.h"
using namespace MzLibUtil;

#include "../Proteomics/Proteomics.h"
using namespace Proteomics;
using namespace Proteomics::ProteolyticDigestion;

namespace Test
{
    class TestDigestionMotif  {

    public:

        static void TestParseProtease();
        static void TestBasicProtease1();
        static void TestBasicProtease2();
        static void TestWildCardExclusion();
        static void TestMultiLetterProtease();
        static void TestNTerminusProtease();
        static void TestSyntax();
    };
}
