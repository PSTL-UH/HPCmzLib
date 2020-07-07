#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <cmath>
#include "stringhelper.h"

namespace Test
{
    class TestModFits final
    {
    public:
        static void TestModFitss();

        static void TestAmbiguousModFits(const std::string &proteinSequence, const std::string &motifString, bool result);
    };
}
