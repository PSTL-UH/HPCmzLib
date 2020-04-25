#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
#include <tuple>
#include <optional>
#include "stringhelper.h"
#include "tangible_filesystem.h"

#include "../../MassSpectrometry/MassSpectrometry.h"
using namespace MassSpectrometry;

#include "../../Proteomics/Proteomics.h"
using namespace Proteomics;

#include "../../UsefulProteomicsDatabases/UsefulProteomicsDatabases.h"
using namespace UsefulProteomicsDatabases;

namespace Test
{
    class TestProteomicsReadWrite
    {
    public:
        static void ReadXmlNulls();

        static void Test_readUniProtXML_writeProteinXml();

        static void Test_read_Ensembl_pepAllFasta();

        static void FastaTest();

        static void Test_read_write_read_fasta();

        static void Test_read_xml_write_read_fasta();

        static void Test_accession_regex_weird();

        static void Test_write_with_custom_mods();

        static void AnotherTest();

        static void TestEmptyProteins();

        static void TestFullProteinReadWrite();

        static void TestReadWriteSeqVars();

        static void TestReadWriteSeqVars2();

        static void TestModificationGeneralToString();

        static void TestModificationGeneral_Equals();

        static void Test_CustumPrunedDatabaseWriteAndRead();
    };
}
