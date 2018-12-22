#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <tuple>
#include "tangible_filesystem.h"

using namespace NUnit::Framework;
using namespace Proteomics;
using namespace UsefulProteomicsDatabases;

namespace Test {
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [TestFixture] internal class TestProteomicsReadWrite
    class TestProteomicsReadWrite {
//        #region Public Methods

    public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void Test_read_write_read_xml()
        void Test_read_write_read_xml();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void Test_read_Ensembl_pepAllFasta()
        void Test_read_Ensembl_pepAllFasta();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void Test_read_write_read_fasta()
        void Test_read_write_read_fasta();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void Test_accession_regex_weird()
        void Test_accession_regex_weird();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void Test_write_with_custom_mods()
        void Test_write_with_custom_mods();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void Test_getptms_from_mzLibxml_without_prep()
        void Test_getptms_from_mzLibxml_without_prep();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void AnotherTest()
        void AnotherTest();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void TestEmptyProteins()
        void TestEmptyProteins();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void TestFullProteinReadWrite()
        void TestFullProteinReadWrite();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void TestReadWriteSeqVars()
        void TestReadWriteSeqVars();

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Test] public void TestReadWriteSeqVars2()
        void TestReadWriteSeqVars2();

//        #endregion Public Methods
    };
}
