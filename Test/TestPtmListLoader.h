#pragma once

#include <string>
#include <vector>
#include <iostream>
#include "stringhelper.h"
#include "tangible_filesystem.h"

#include "MzLibUtil.h"
using namespace MzLibUtil;

#include "../Proteomics/Proteomics.h"
using namespace Proteomics;

#include "../UsefulProteomicsDatabases/UsefulProteomicsDatabases.h"
using namespace UsefulProteomicsDatabases;

namespace Test
{
    class TestPtmListLoader final
    {
    public:
        static void SampleModFileLoading();

        static void Test_ReadAllModsFromFile(const std::string filename, int modCount);

        static void Test_ModsFromFileAreSorted(const std::string filename);

        static void Test_ModsWithComments();

        static void SampleModFileLoadingFail1General(const std::string filename);

        static void PTMListLoader_ModWithComments_Equals_ModWithoutComments();

        static void SampleModFileLoadingFail3General(const std::string filename, const std::string errorMessage);

        static void CompactFormReadingGeneral(const std::string filename);

        static void TestReadingInvalidModifications();

        static void TestReadingIdWithMotif();

        static void TestInvalidModTypeError();
    };
}
