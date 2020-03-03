#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include "stringhelper.h"
#include "tangible_filesystem.h"

#include "../Chemistry/Chemistry.h"
using namespace Chemistry;

#include "../FlashLFQ/FlashLFQ.h"
using namespace FlashLFQ;

#include "../MassSpectrometry/MassSpectrometry.h"
using namespace MassSpectrometry;

#include "MzLibUtil.h"
using namespace MzLibUtil;

#include "../UsefulProteomicsDatabases/UsefulProteomicsDatabases.h"
using namespace UsefulProteomicsDatabases;

namespace Test
{
    class TestFlashLFQ
    {
    public:
        static void TestFlashLfq();
        static void TestFlashLfqNormalization();
        static void TestFlashLfqMergeResults();
        static void TestFlashLfqAdvancedProteinQuant();
    };
}
