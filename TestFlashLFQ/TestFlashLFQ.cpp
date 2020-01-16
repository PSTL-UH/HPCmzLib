﻿#include "TestFlashLFQ.h"
#include "../FlashLFQ/SpectraFileInfo.h"
#include "../FlashLFQ/ProteinGroup.h"
#include "../FlashLFQ/Identification.h"
#include "../FlashLFQ/FlashLfqEngine.h"
#include "../UsefulProteomicsDatabases/Loaders.h"
#include "../MassSpectrometry/MsDataScan.h"
#include "../Chemistry/ChemicalFormula.h"
#include "../Proteomics/AminoAcidPolymer/Peptide.h"
#include "../Chemistry/IsotopicDistribution.h"
#include "../Test/FakeMsDataFile.h"

using namespace Chemistry;
using namespace FlashLFQ;
using namespace MassSpectrometry;
using namespace MzLibUtil;
using namespace NUnit::Framework;
using namespace UsefulProteomicsDatabases;
using ChromatographicPeak = FlashLFQ::ChromatographicPeak;
namespace Stopwatch = System::Diagnostics::Stopwatch;

namespace Test
{

System::Diagnostics::Stopwatch *TestFlashLFQ::privateStopwatch;

    Stopwatch *TestFlashLFQ::getStopwatch()
    {
        return privateStopwatch;
    }

    void TestFlashLFQ::setStopwatch(Stopwatch *value)
    {
        privateStopwatch = value;
    }

    void TestFlashLFQ::Setuppp()
    {
        Stopwatch tempVar();
        setStopwatch(&tempVar);
        getStopwatch()->Start();
    }

    void TestFlashLFQ::TearDown()
    {
        std::cout << StringHelper::formatSimple("Analysis time: {0}h {1}m {2}s", getStopwatch()->Elapsed.Hours, getStopwatch()->Elapsed.Minutes, getStopwatch()->Elapsed.Seconds) << std::endl;
    }

    void TestFlashLFQ::TestFlashLfq()
    {
        // get the raw file paths
        SpectraFileInfo *raw = new SpectraFileInfo(FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(sliced-raw.raw)"), "a", 0, 0, 0);
        SpectraFileInfo *mzml = new SpectraFileInfo(FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(sliced-mzml.mzml)"), "a", 0, 1, 0);

        // create some PSMs
        auto pg = new ProteinGroup("MyProtein", "gene", "org");
        Identification *id1 = new Identification(raw, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.12193, 2, std::vector<ProteinGroup*> {pg});
        Identification *id2 = new Identification(raw, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.05811, 2, std::vector<ProteinGroup*> {pg});
        Identification *id3 = new Identification(mzml, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.12193, 2, std::vector<ProteinGroup*> {pg});
        Identification *id4 = new Identification(mzml, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.05811, 2, std::vector<ProteinGroup*> {pg});

        // create the FlashLFQ engine
        FlashLfqEngine *engine = new FlashLfqEngine({id1, id2, id3, id4}, true, false, false, 10.0, 5.0, 5.0, false, 2, false, true, false, "", 2.5, -1);

        // run the engine
        auto results = engine->Run();

        // check raw results
        Assert::That(results->Peaks[raw].size() == 1);
        Assert::That(results->Peaks[raw].front().Intensity > 0);
        Assert::That(!results->Peaks[raw].front().IsMbrPeak);
        Assert::That(results->PeptideModifiedSequences["EGFQVADGPLYR"]->GetIntensity(raw) > 0);
        Assert::That(results->ProteinGroups["MyProtein"]->GetIntensity(raw) > 0);

        // check mzml results
        Assert::That(results->Peaks[mzml].size() == 1);
        Assert::That(results->Peaks[mzml].front().Intensity > 0);
        Assert::That(!results->Peaks[mzml].front().IsMbrPeak);
        Assert::That(results->PeptideModifiedSequences["EGFQVADGPLYR"]->GetIntensity(mzml) > 0);
        Assert::That(results->ProteinGroups["MyProtein"]->GetIntensity(mzml) > 0);

        // check that condition normalization worked
        int int1 = static_cast<int>(std::round(results->Peaks[mzml].front().Intensity * std::pow(10, 0))) / std::pow(10, 0);
        int int2 = static_cast<int>(std::round(results->Peaks[raw].front().Intensity * std::pow(10, 0))) / std::pow(10, 0);
        Assert::That(int1 == int2);

        // test peak output
        results->WriteResults(FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(peaks.tsv)"), FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(modSeq.tsv)"), FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(protein.tsv)"));

        delete engine;
//C# TO C++ CONVERTER TODO TASK: A 'delete id4' statement was not added since id4 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete id3' statement was not added since id3 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete id2' statement was not added since id2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete id1' statement was not added since id1 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete pg' statement was not added since pg was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete mzml' statement was not added since mzml was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete raw' statement was not added since raw was passed to a method or constructor. Handle memory management manually.
    }

    void TestFlashLFQ::TestFlashLfqNormalization()
    {
        // ********************************* check biorep normalization *********************************
        // get the raw file paths
        SpectraFileInfo *raw = new SpectraFileInfo(FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(sliced-raw.raw)"), "a", 0, 0, 0);
        SpectraFileInfo *mzml = new SpectraFileInfo(FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(sliced-mzml.mzml)"), "a", 1, 0, 0);

        // create some PSMs
        auto pg = new ProteinGroup("MyProtein", "gene", "org");
        Identification *id1 = new Identification(raw, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.12193, 2, std::vector<ProteinGroup*> {pg});
        Identification *id2 = new Identification(mzml, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.12193, 2, std::vector<ProteinGroup*> {pg});

        // create the FlashLFQ engine
        FlashLfqEngine tempVar({id1, id2}, true, false, false, 10.0, 5.0, 5.0, false, 2, false, true, false, "", 2.5, -1);
        auto results = (&tempVar)->Run();

        // check that biorep normalization worked
        int int1 = static_cast<int>(std::round(results->Peaks[mzml].First().Intensity * std::pow(10, 0))) / std::pow(10, 0);
        int int2 = static_cast<int>(std::round(results->Peaks[raw].First().Intensity * std::pow(10, 0))) / std::pow(10, 0);
        Assert::That(int1 > 0);
        Assert::That(int1 == int2);

        // ********************************* check condition normalization *********************************
        raw = new SpectraFileInfo(FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(sliced-raw.raw)"), "a", 0, 0, 0);
        mzml = new SpectraFileInfo(FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(sliced-mzml.mzml)"), "b", 0, 0, 0);

        id1 = new Identification(raw, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.12193, 2, std::vector<ProteinGroup*> {pg});
        id2 = new Identification(mzml, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.12193, 2, std::vector<ProteinGroup*> {pg});

        FlashLfqEngine tempVar2({id1, id2}, true, false, false, 10.0, 5.0, 5.0, false, 2, false, true, false, "", 2.5, -1);
        results = (&tempVar2)->Run();

        int int3 = static_cast<int>(std::round(results->Peaks[mzml].First().Intensity * std::pow(10, 0))) / std::pow(10, 0);
        int int4 = static_cast<int>(std::round(results->Peaks[raw].First().Intensity * std::pow(10, 0))) / std::pow(10, 0);
        Assert::That(int3 > 0);
        Assert::That(int3 == int4);

        // ********************************* check techrep normalization *********************************
        raw = new SpectraFileInfo(FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(sliced-raw.raw)"), "a", 0, 0, 0);
        mzml = new SpectraFileInfo(FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(sliced-mzml.mzml)"), "a", 0, 1, 0);

        id1 = new Identification(raw, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.12193, 2, std::vector<ProteinGroup*> {pg});
        id2 = new Identification(mzml, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.12193, 2, std::vector<ProteinGroup*> {pg});

        FlashLfqEngine tempVar3({id1, id2}, true, false, false, 10.0, 5.0, 5.0, false, 2, false, true, false, "", 2.5, -1);
        results = (&tempVar3)->Run();

        int int5 = static_cast<int>(std::round(results->Peaks[mzml].First().Intensity * std::pow(10, 0))) / std::pow(10, 0);
        int int6 = static_cast<int>(std::round(results->Peaks[raw].First().Intensity * std::pow(10, 0))) / std::pow(10, 0);
        Assert::That(int5 > 0);
        Assert::That(int5 == int6);

        Assert::That(int1 == int3);
        Assert::That(int1 == int5);

        // ********************************* check fraction normalization *********************************
        raw = new SpectraFileInfo(FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(sliced-raw.raw)"), "a", 0, 0, 0);
        auto raw2 = new SpectraFileInfo(FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(sliced-raw.raw)"), "a", 0, 0, 1);
        mzml = new SpectraFileInfo(FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(sliced-mzml.mzml)"), "a", 1, 0, 0);
        auto mzml2 = new SpectraFileInfo(FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(sliced-mzml.mzml)"), "a", 1, 0, 1);

        id1 = new Identification(raw, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.12193, 2, std::vector<ProteinGroup*> {pg});
        id2 = new Identification(raw2, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.12193, 2, std::vector<ProteinGroup*> {pg});
        auto id3 = new Identification(mzml, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.12193, 2, std::vector<ProteinGroup*> {pg});
        auto id4 = new Identification(mzml2, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.12193, 2, std::vector<ProteinGroup*> {pg});

        FlashLfqEngine tempVar4({id1, id2, id3, id4}, true, false, false, 10.0, 5.0, 5.0, false, 2, false, true, false, "", 2.5, -1);
        results = (&tempVar4)->Run();

        int int7 = static_cast<int>(BankersRounding::round(results->PeptideModifiedSequences["EGFQVADGPLYR"].GetIntensity(raw) + results->PeptideModifiedSequences["EGFQVADGPLYR"].GetIntensity(raw2)));
        int int8 = static_cast<int>(BankersRounding::round(results->PeptideModifiedSequences["EGFQVADGPLYR"].GetIntensity(mzml) + results->PeptideModifiedSequences["EGFQVADGPLYR"].GetIntensity(mzml2)));
        Assert::That(int7 > 0);
        Assert::That(int7 == int8);

//C# TO C++ CONVERTER TODO TASK: A 'delete id4' statement was not added since id4 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete id3' statement was not added since id3 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete mzml2' statement was not added since mzml2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete raw2' statement was not added since raw2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete id2' statement was not added since id2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete id1' statement was not added since id1 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete pg' statement was not added since pg was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete mzml' statement was not added since mzml was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete raw' statement was not added since raw was passed to a method or constructor. Handle memory management manually.
    }

    void TestFlashLFQ::TestFlashLfqMergeResults()
    {
        SpectraFileInfo *rawA = new SpectraFileInfo(FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(sliced-raw.raw)"), "a", 0, 0, 0);
        SpectraFileInfo *mzmlA = new SpectraFileInfo(FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(sliced-mzml.mzml)"), "a", 0, 1, 0);

        // create some PSMs
        auto pgA = new ProteinGroup("MyProtein", "gene", "org");
        Identification *id1A = new Identification(rawA, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.12193, 2, std::vector<ProteinGroup*> {pgA});
        Identification *id2A = new Identification(rawA, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.05811, 2, std::vector<ProteinGroup*> {pgA});
        Identification *id3A = new Identification(mzmlA, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.12193, 2, std::vector<ProteinGroup*> {pgA});
        Identification *id4A = new Identification(mzmlA, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.05811, 2, std::vector<ProteinGroup*> {pgA});

        // create the FlashLFQ engine
        FlashLfqEngine *engineA = new FlashLfqEngine(std::vector<Identification*> {id1A, id2A, id3A, id4A});

        // run the engine
        auto resultsA = engineA->Run();

        SpectraFileInfo *rawB = new SpectraFileInfo(FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(sliced-raw.raw)"), "b", 0, 0, 0);
        SpectraFileInfo *mzmlB = new SpectraFileInfo(FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(sliced-mzml.mzml)"), "b", 0, 1, 0);

        // create some PSMs
        auto pgB = new ProteinGroup("MyProtein", "gene", "org");
        Identification *id1 = new Identification(rawB, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.12193, 2, std::vector<ProteinGroup*> {pgB});
        Identification *id2 = new Identification(rawB, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.05811, 2, std::vector<ProteinGroup*> {pgB});
        Identification *id3 = new Identification(mzmlB, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.12193, 2, std::vector<ProteinGroup*> {pgB});
        Identification *id4 = new Identification(mzmlB, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.05811, 2, std::vector<ProteinGroup*> {pgB});

        // create the FlashLFQ engine
        FlashLfqEngine *engineB = new FlashLfqEngine(std::vector<Identification*> {id1, id2, id3, id4});

        // run the engine
        auto resultsB = engineB->Run();

        resultsA->MergeResultsWith(resultsB);
        Assert::AreEqual(4, resultsA->Peaks.size());
        Assert::AreEqual(1, resultsA->PeptideModifiedSequences.size());
        Assert::AreEqual(1, resultsA->ProteinGroups.size());
        Assert::AreEqual(4, resultsA->SpectraFiles.size());

        delete engineB;
//C# TO C++ CONVERTER TODO TASK: A 'delete id4' statement was not added since id4 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete id3' statement was not added since id3 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete id2' statement was not added since id2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete id1' statement was not added since id1 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete pgB' statement was not added since pgB was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete mzmlB' statement was not added since mzmlB was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete rawB' statement was not added since rawB was passed to a method or constructor. Handle memory management manually.
        delete engineA;
//C# TO C++ CONVERTER TODO TASK: A 'delete id4A' statement was not added since id4A was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete id3A' statement was not added since id3A was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete id2A' statement was not added since id2A was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete id1A' statement was not added since id1A was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete pgA' statement was not added since pgA was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete mzmlA' statement was not added since mzmlA was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete rawA' statement was not added since rawA was passed to a method or constructor. Handle memory management manually.
    }

    void TestFlashLFQ::TestFlashLfqAdvancedProteinQuant()
    {
        std::vector<std::string> filesToWrite = {"mzml_1", "mzml_2"};
        std::vector<std::string> pepSequences = {"PEPTIDE", "MYPEPTIDE", "VVVVVPEPTIDE"};
        std::vector<std::vector<double>> amounts =
        {
            {1000000, 1000000, 1000000},
            {2000000, 2000000, 900000}
        };
        Loaders::LoadElements(FileSystem::combine(TestContext::CurrentContext->TestDirectory, R"(elements.dat)"));

        // generate mzml files (3 peptides each)
        for (int f = 0; f < filesToWrite.size(); f++)
        {
            // 1 MS1 scan per peptide
            std::vector<MsDataScan*> scans(3);

            for (int p = 0; p < pepSequences.size(); p++)
            {
                Proteomics::AminoAcidPolymer::Peptide tempVar(pepSequences[p]);
                ChemicalFormula *cf = (&tempVar)->GetChemicalFormula();
                IsotopicDistribution *dist = IsotopicDistribution::GetDistribution(cf, 0.125, 1e-8);
                std::vector<double> mz = dist->getMasses().Select([&] (std::any v)
                {
                    v::ToMz(1);
                })->ToArray();
                FakeMsDataFile tempVar2(scans);
//C# TO C++ CONVERTER TODO TASK: The following lambda expression could not be converted:
                std::vector<double> intensities = dist->getIntensities().Select(v => TangibleLambdaToken698IO::MzML::MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(&tempVar2, FileSystem::combine(TestContext::CurrentContext->TestDirectory, filesToWrite[f] + ".mzML"), false);
            }

        // set up spectra file info
        SpectraFileInfo *file1 = new SpectraFileInfo(FileSystem::combine(TestContext::CurrentContext->TestDirectory, filesToWrite[0] + ".mzML"), "a", 0, 0, 0);
        SpectraFileInfo *file2 = new SpectraFileInfo(FileSystem::combine(TestContext::CurrentContext->TestDirectory, filesToWrite[1] + ".mzML"), "a", 1, 0, 0);

        // create some PSMs
        auto pg = new ProteinGroup("MyProtein", "gene", "org");
        Identification *id1 = new Identification(file1, "PEPTIDE", "PEPTIDE", 799.35996, 1.01, 1, std::vector<ProteinGroup*> {pg});
        Identification *id2 = new Identification(file1, "MYPEPTIDE", "MYPEPTIDE", 1093.46377, 1.11, 1, std::vector<ProteinGroup*> {pg});
        Identification *id3 = new Identification(file1, "VVVVVPEPTIDE", "VVVVVPEPTIDE", 1294.70203, 1.21, 1, std::vector<ProteinGroup*> {pg});

        Identification *id4 = new Identification(file2, "PEPTIDE", "PEPTIDE", 799.35996, 1.01, 1, std::vector<ProteinGroup*> {pg});
        Identification *id5 = new Identification(file2, "MYPEPTIDE", "MYPEPTIDE", 1093.46377, 1.11, 1, std::vector<ProteinGroup*> {pg});
        Identification *id6 = new Identification(file2, "VVVVVPEPTIDE", "VVVVVPEPTIDE", 1294.70203, 1.21, 1, std::vector<ProteinGroup*> {pg});

        // create the FlashLFQ engine
        FlashLfqEngine *engine = new FlashLfqEngine({id1, id2, id3, id4, id5, id6}, false, true, false, 10.0, 5.0, 5.0, false, 2, false, true, false, "", 2.5, -1);

        // run the engine
        auto results = engine->Run();

        // third peptide should be low-weighted
        // protein should be ~sum of first two peptide intensities (a little lower, because some smaller isotope peaks get skipped)
        double file1ProteinIntensity = results->ProteinGroups["MyProtein"]->GetIntensity(file1);
        Assert::That(file1ProteinIntensity < 2e6);
        Assert::That(file1ProteinIntensity > 1e6);

        double file2ProteinIntensity = results->ProteinGroups["MyProtein"]->GetIntensity(file2);
        Assert::That(file2ProteinIntensity < 4e6);
        Assert::That(file2ProteinIntensity > 3e6);

        delete engine;
//C# TO C++ CONVERTER TODO TASK: A 'delete id6' statement was not added since id6 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete id5' statement was not added since id5 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete id4' statement was not added since id4 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete id3' statement was not added since id3 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete id2' statement was not added since id2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete id1' statement was not added since id1 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete pg' statement was not added since pg was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete file2' statement was not added since file2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete file1' statement was not added since file1 was passed to a method or constructor. Handle memory management manually.
        }

//C# TO C++ CONVERTER TODO TASK: Local functions are not converted by C# to C++ Converter:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestFlashLfqMatchBetweenRuns()
//    public static void TestFlashLfqMatchBetweenRuns()
    //        {
    //            List<string> filesToWrite = new List<string> { "mzml_1", "mzml_2" };
    //            List<string> pepSequences = new List<string> { "PEPTIDE", "PEPTIDEV", "PEPTIDEVV", "PEPTIDEVVV", "PEPTIDEVVVV" };
    //            double intensity = 1e6;
    //
    //            double[] file1Rt = new double[] { 1.01, 1.02, 1.03, 1.04, 1.05 };
    //            double[] file2Rt = new double[] { 1.015, 1.030, 1.039, 1.050, 1.065 };
    //
    //            Loaders.LoadElements(Path.Combine(TestContext.CurrentContext.TestDirectory, "TangibleTempVerbatimOpenTagelements.datTangibleTempVerbatimCloseTag"));
    //
    //            // generate mzml files (5 peptides each)
    //            for (int f = 0; f < filesToWrite.Count; f++)
    //            {
    //                // 1 MS1 scan per peptide
    //                MsDataScan[] scans = new MsDataScan[5];
    //
    //                for (int p = 0; p < pepSequences.Count; p++)
    //                {
    //                    ChemicalFormula cf = new Proteomics.AminoAcidPolymer.Peptide(pepSequences[p]).GetChemicalFormula();
    //                    IsotopicDistribution dist = IsotopicDistribution.GetDistribution(cf, 0.125, 1e-8);
    //                    double[] mz = dist.Masses.Select(v => v.ToMz(1)).ToArray();
    //                    double[] intensities = dist.Intensities.Select(v => v * intensity).ToArray();
    //                    double rt;
    //                    if (f == 0)
    //                    {
    //                        rt = file1Rt[p];
    //                    }
    //                    else
    //                    {
    //                        rt = file2Rt[p];
    //                    }
    //
    //                    // add the scan
    //                    scans[p] = new MsDataScan(massSpectrum: new MzSpectrum(mz, intensities, false), oneBasedScanNumber: p + 1, msnOrder: 1, isCentroid: true, polarity: Polarity.Positive, retentionTime: rt, scanWindowRange: new MzRange(400, 1600), scanFilter: "f", mzAnalyzer: MZAnalyzerType.Orbitrap, totalIonCurrent: intensities.Sum(), injectionTime: 1.0, noiseData: nullptr, nativeId: "scan=" + (p + 1));
    //                }
    //
    //                // write the .mzML
    //                IO.MzML.MzmlMethods.CreateAndWriteMyMzmlWithCalibratedSpectra(new FakeMsDataFile(scans), Path.Combine(TestContext.CurrentContext.TestDirectory, filesToWrite[f] + ".mzML"), false);
    //            }
    //
    //            // set up spectra file info
    //            SpectraFileInfo file1 = new SpectraFileInfo(Path.Combine(TestContext.CurrentContext.TestDirectory, filesToWrite[0] + ".mzML"), "a", 0, 0, 0);
    //            SpectraFileInfo file2 = new SpectraFileInfo(Path.Combine(TestContext.CurrentContext.TestDirectory, filesToWrite[1] + ".mzML"), "a", 1, 0, 0);
    //
    //            // create some PSMs
    //            var pg = new ProteinGroup("MyProtein", "gene", "org");
    //            Identification id1 = new Identification(file1, "PEPTIDE", "PEPTIDE", new Proteomics.AminoAcidPolymer.Peptide("PEPTIDE").MonoisotopicMass, file1Rt[0] + 0.001, 1, new List<ProteinGroup> { pg });
    //            Identification id2 = new Identification(file1, "PEPTIDEV", "PEPTIDEV", new Proteomics.AminoAcidPolymer.Peptide("PEPTIDEV").MonoisotopicMass, file1Rt[1] + 0.001, 1, new List<ProteinGroup> { pg });
    //            Identification id3 = new Identification(file1, "PEPTIDEVV", "PEPTIDEVV", new Proteomics.AminoAcidPolymer.Peptide("PEPTIDEVV").MonoisotopicMass, file1Rt[2] + 0.001, 1, new List<ProteinGroup> { pg });
    //            Identification id4 = new Identification(file1, "PEPTIDEVVV", "PEPTIDEVVV", new Proteomics.AminoAcidPolymer.Peptide("PEPTIDEVVV").MonoisotopicMass, file1Rt[3] + 0.001, 1, new List<ProteinGroup> { pg });
    //            Identification id5 = new Identification(file1, "PEPTIDEVVVV", "PEPTIDEVVVV", new Proteomics.AminoAcidPolymer.Peptide("PEPTIDEVVVV").MonoisotopicMass, file1Rt[4] + 0.001, 1, new List<ProteinGroup> { pg });
    //
    //            Identification id6 = new Identification(file2, "PEPTIDE", "PEPTIDE", new Proteomics.AminoAcidPolymer.Peptide("PEPTIDE").MonoisotopicMass, file2Rt[0] + 0.001, 1, new List<ProteinGroup> { pg });
    //            Identification id7 = new Identification(file2, "PEPTIDEV", "PEPTIDEV", new Proteomics.AminoAcidPolymer.Peptide("PEPTIDEV").MonoisotopicMass, file2Rt[1] + 0.001, 1, new List<ProteinGroup> { pg });
    //            // missing ID 8 - MBR feature
    //            Identification id9 = new Identification(file2, "PEPTIDEVVV", "PEPTIDEVVV", new Proteomics.AminoAcidPolymer.Peptide("PEPTIDEVVV").MonoisotopicMass, file2Rt[3] + 0.001, 1, new List<ProteinGroup> { pg });
    //            Identification id10 = new Identification(file2, "PEPTIDEVVVV", "PEPTIDEVVVV", new Proteomics.AminoAcidPolymer.Peptide("PEPTIDEVVVV").MonoisotopicMass, file2Rt[4] + 0.001, 1, new List<ProteinGroup> { pg });
    //
    //            // create the FlashLFQ engine
    //            FlashLfqEngine engine = new FlashLfqEngine(new List<Identification> { id1, id2, id3, id4, id5, id6, id7, id9, id10 }, matchBetweenRuns: true);
    //
    //            // run the engine
    //            var results = engine.Run();
    //
    //            Assert.That(results.Peaks[file2].Count == 5);
    //            Assert.That(results.Peaks[file2].Where(p => p.IsMbrPeak).Count() == 1);
    //
    //            var peak = results.Peaks[file2].Where(p => p.IsMbrPeak).First();
    //            var otherFilePeak = results.Peaks[file1].Where(p => p.Identifications.First().BaseSequence == peak.Identifications.First().BaseSequence).First();
    //
    //            Assert.That(peak.Intensity > 0);
    //            Assert.That(peak.Intensity == otherFilePeak.Intensity);
    //
    //            Assert.That(results.Peaks[file1].Count == 5);
    //            Assert.That(results.Peaks[file1].Where(p => p.IsMbrPeak).Count() == 0);
    //
    //            Assert.That(results.ProteinGroups["MyProtein"].GetIntensity(file1) > 0);
    //            Assert.That(results.ProteinGroups["MyProtein"].GetIntensity(file2) > 0);
    //        }

//C# TO C++ CONVERTER TODO TASK: Local functions are not converted by C# to C++ Converter:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestFlashLfqMatchBetweenRunsProteinQuant()
//    public static void TestFlashLfqMatchBetweenRunsProteinQuant()
    //        {
    //            List<string> filesToWrite = new List<string> { "mzml_1", "mzml_2" };
    //            List<string> pepSequences = new List<string> { "PEPTIDE", "PEPTIDEV", "PEPTIDEVV", "PEPTIDEVVV", "PEPTIDEVVVV" };
    //            double intensity = 1e6;
    //
    //            double[] file1Rt = new double[] { 1.01, 1.02, 1.03, 1.04, 1.05 };
    //            double[] file2Rt = new double[] { 1.015, 1.030, 1.036, 1.050, 1.065 };
    //
    //            Loaders.LoadElements(Path.Combine(TestContext.CurrentContext.TestDirectory, "TangibleTempVerbatimOpenTagelements.datTangibleTempVerbatimCloseTag"));
    //
    //            // generate mzml files (5 peptides each)
    //            for (int f = 0; f < filesToWrite.Count; f++)
    //            {
    //                // 1 MS1 scan per peptide
    //                MsDataScan[] scans = new MsDataScan[5];
    //
    //                for (int p = 0; p < pepSequences.Count; p++)
    //                {
    //                    ChemicalFormula cf = new Proteomics.AminoAcidPolymer.Peptide(pepSequences[p]).GetChemicalFormula();
    //                    IsotopicDistribution dist = IsotopicDistribution.GetDistribution(cf, 0.125, 1e-8);
    //                    double[] mz = dist.Masses.Select(v => v.ToMz(1)).ToArray();
    //                    double[] intensities = dist.Intensities.Select(v => v * intensity).ToArray();
    //                    double rt;
    //                    if (f == 0)
    //                    {
    //                        rt = file1Rt[p];
    //                    }
    //                    else
    //                    {
    //                        rt = file2Rt[p];
    //                    }
    //
    //                    // add the scan
    //                    scans[p] = new MsDataScan(massSpectrum: new MzSpectrum(mz, intensities, false), oneBasedScanNumber: p + 1, msnOrder: 1, isCentroid: true, polarity: Polarity.Positive, retentionTime: rt, scanWindowRange: new MzRange(400, 1600), scanFilter: "f", mzAnalyzer: MZAnalyzerType.Orbitrap, totalIonCurrent: intensities.Sum(), injectionTime: 1.0, noiseData: nullptr, nativeId: "scan=" + (p + 1));
    //                }
    //
    //                // write the .mzML
    //                IO.MzML.MzmlMethods.CreateAndWriteMyMzmlWithCalibratedSpectra(new FakeMsDataFile(scans), Path.Combine(TestContext.CurrentContext.TestDirectory, filesToWrite[f] + ".mzML"), false);
    //            }
    //
    //            // set up spectra file info
    //            SpectraFileInfo file1 = new SpectraFileInfo(Path.Combine(TestContext.CurrentContext.TestDirectory, filesToWrite[0] + ".mzML"), "a", 0, 0, 0);
    //            SpectraFileInfo file2 = new SpectraFileInfo(Path.Combine(TestContext.CurrentContext.TestDirectory, filesToWrite[1] + ".mzML"), "b", 0, 0, 0);
    //
    //            // create some PSMs
    //            var pg = new ProteinGroup("MyProtein", "gene", "org");
    //            var myMbrProteinGroup = new ProteinGroup("MyMbrProtein", "MbrGene", "org");
    //
    //            Identification id1 = new Identification(file1, "PEPTIDE", "PEPTIDE", new Proteomics.AminoAcidPolymer.Peptide("PEPTIDE").MonoisotopicMass, file1Rt[0] + 0.001, 1, new List<ProteinGroup> { pg });
    //            Identification id2 = new Identification(file1, "PEPTIDEV", "PEPTIDEV", new Proteomics.AminoAcidPolymer.Peptide("PEPTIDEV").MonoisotopicMass, file1Rt[1] + 0.001, 1, new List<ProteinGroup> { pg });
    //            Identification id3 = new Identification(file1, "PEPTIDEVV", "PEPTIDEVV", new Proteomics.AminoAcidPolymer.Peptide("PEPTIDEVV").MonoisotopicMass, file1Rt[2] + 0.001, 1, new List<ProteinGroup> { myMbrProteinGroup });
    //            Identification id4 = new Identification(file1, "PEPTIDEVVV", "PEPTIDEVVV", new Proteomics.AminoAcidPolymer.Peptide("PEPTIDEVVV").MonoisotopicMass, file1Rt[3] + 0.001, 1, new List<ProteinGroup> { pg });
    //            Identification id5 = new Identification(file1, "PEPTIDEVVVV", "PEPTIDEVVVV", new Proteomics.AminoAcidPolymer.Peptide("PEPTIDEVVVV").MonoisotopicMass, file1Rt[4] + 0.001, 1, new List<ProteinGroup> { pg });
    //
    //            Identification id6 = new Identification(file2, "PEPTIDE", "PEPTIDE", new Proteomics.AminoAcidPolymer.Peptide("PEPTIDE").MonoisotopicMass, file2Rt[0] + 0.001, 1, new List<ProteinGroup> { pg });
    //            Identification id7 = new Identification(file2, "PEPTIDEV", "PEPTIDEV", new Proteomics.AminoAcidPolymer.Peptide("PEPTIDEV").MonoisotopicMass, file2Rt[1] + 0.001, 1, new List<ProteinGroup> { pg });
    //            // missing ID 8 - MBR feature
    //            Identification id9 = new Identification(file2, "PEPTIDEVVV", "PEPTIDEVVV", new Proteomics.AminoAcidPolymer.Peptide("PEPTIDEVVV").MonoisotopicMass, file2Rt[3] + 0.001, 1, new List<ProteinGroup> { pg });
    //            Identification id10 = new Identification(file2, "PEPTIDEVVVV", "PEPTIDEVVVV", new Proteomics.AminoAcidPolymer.Peptide("PEPTIDEVVVV").MonoisotopicMass, file2Rt[4] + 0.001, 1, new List<ProteinGroup> { pg });
    //
    //            // test with top3 protein quant engine
    //            FlashLfqEngine engine = new FlashLfqEngine(new List<Identification> { id1, id2, id3, id4, id5, id6, id7, id9, id10 }, matchBetweenRuns: true);
    //            var results = engine.Run();
    //
    //            Assert.That(results.ProteinGroups["MyMbrProtein"].GetIntensity(file1) > 0);
    //            Assert.That(results.ProteinGroups["MyMbrProtein"].GetIntensity(file2) == 0);
    //
    //            // test with advanced protein quant engine
    //            engine = new FlashLfqEngine(new List<Identification> { id1, id2, id3, id4, id5, id6, id7, id9, id10 }, matchBetweenRuns: true, advancedProteinQuant: true);
    //            results = engine.Run();
    //
    //            Assert.That(results.ProteinGroups["MyMbrProtein"].GetIntensity(file1) > 0);
    //            Assert.That(results.ProteinGroups["MyMbrProtein"].GetIntensity(file2) == 0);
    //        }

//C# TO C++ CONVERTER TODO TASK: Local functions are not converted by C# to C++ Converter:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestPeakSplittingLeft()
//    public static void TestPeakSplittingLeft()
    //        {
    //            string fileToWrite = "myMzml.mzML";
    //            string peptide = "PEPTIDE";
    //            double intensity = 1e6;
    //
    //            Loaders.LoadElements(Path.Combine(TestContext.CurrentContext.TestDirectory, "TangibleTempVerbatimOpenTagelements.datTangibleTempVerbatimCloseTag"));
    //
    //            // generate mzml file
    //
    //            // 1 MS1 scan per peptide
    //            MsDataScan[] scans = new MsDataScan[10];
    //            double[] intensityMultipliers = { 1, 3, 1, 1, 3, 5, 10, 5, 3, 1 };
    //
    //            for (int s = 0; s < scans.Length; s++)
    //            {
    //                ChemicalFormula cf = new Proteomics.AminoAcidPolymer.Peptide(peptide).GetChemicalFormula();
    //                IsotopicDistribution dist = IsotopicDistribution.GetDistribution(cf, 0.125, 1e-8);
    //                double[] mz = dist.Masses.Select(v => v.ToMz(1)).ToArray();
    //                double[] intensities = dist.Intensities.Select(v => v * intensity * intensityMultipliers[s]).ToArray();
    //
    //                // add the scan
    //                scans[s] = new MsDataScan(massSpectrum: new MzSpectrum(mz, intensities, false), oneBasedScanNumber: s + 1, msnOrder: 1, isCentroid: true, polarity: Polarity.Positive, retentionTime: 1.0 + s / 10.0, scanWindowRange: new MzRange(400, 1600), scanFilter: "f", mzAnalyzer: MZAnalyzerType.Orbitrap, totalIonCurrent: intensities.Sum(), injectionTime: 1.0, noiseData: nullptr, nativeId: "scan=" + (s + 1));
    //            }
    //
    //            // write the .mzML
    //            IO.MzML.MzmlMethods.CreateAndWriteMyMzmlWithCalibratedSpectra(new FakeMsDataFile(scans), Path.Combine(TestContext.CurrentContext.TestDirectory, fileToWrite), false);
    //
    //            // set up spectra file info
    //            SpectraFileInfo file1 = new SpectraFileInfo(Path.Combine(TestContext.CurrentContext.TestDirectory, fileToWrite), "", 0, 0, 0);
    //
    //            // create some PSMs
    //            var pg = new ProteinGroup("MyProtein", "gene", "org");
    //
    //            Identification id1 = new Identification(file1, peptide, peptide, new Proteomics.AminoAcidPolymer.Peptide(peptide).MonoisotopicMass, 1.7 + 0.001, 1, new List<ProteinGroup> { pg });
    //
    //            // create the FlashLFQ engine
    //            FlashLfqEngine engine = new FlashLfqEngine(new List<Identification> { id1 });
    //
    //            // run the engine
    //            var results = engine.Run();
    //            ChromatographicPeak peak = results.Peaks.First().Value.First();
    //
    //            Assert.That(peak.Apex.IndexedPeak.RetentionTime == 1.6);
    //            Assert.That(peak.SplitRT == 1.3);
    //            Assert.That(!peak.IsotopicEnvelopes.Any(p => p.IndexedPeak.RetentionTime < 1.3));
    //            Assert.That(peak.IsotopicEnvelopes.Count == 6);
    //        }

//C# TO C++ CONVERTER TODO TASK: Local functions are not converted by C# to C++ Converter:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestPeakSplittingRight()
//    public static void TestPeakSplittingRight()
    //        {
    //            string fileToWrite = "myMzml.mzML";
    //            string peptide = "PEPTIDE";
    //            double intensity = 1e6;
    //
    //            Loaders.LoadElements(Path.Combine(TestContext.CurrentContext.TestDirectory, "TangibleTempVerbatimOpenTagelements.datTangibleTempVerbatimCloseTag"));
    //
    //            // generate mzml file
    //
    //            // 1 MS1 scan per peptide
    //            MsDataScan[] scans = new MsDataScan[10];
    //            double[] intensityMultipliers = { 1, 3, 5, 10, 5, 3, 1, 1, 3, 1 };
    //
    //            for (int s = 0; s < scans.Length; s++)
    //            {
    //                ChemicalFormula cf = new Proteomics.AminoAcidPolymer.Peptide(peptide).GetChemicalFormula();
    //                IsotopicDistribution dist = IsotopicDistribution.GetDistribution(cf, 0.125, 1e-8);
    //                double[] mz = dist.Masses.Select(v => v.ToMz(1)).ToArray();
    //                double[] intensities = dist.Intensities.Select(v => v * intensity * intensityMultipliers[s]).ToArray();
    //
    //                // add the scan
    //                scans[s] = new MsDataScan(massSpectrum: new MzSpectrum(mz, intensities, false), oneBasedScanNumber: s + 1, msnOrder: 1, isCentroid: true, polarity: Polarity.Positive, retentionTime: 1.0 + s / 10.0, scanWindowRange: new MzRange(400, 1600), scanFilter: "f", mzAnalyzer: MZAnalyzerType.Orbitrap, totalIonCurrent: intensities.Sum(), injectionTime: 1.0, noiseData: nullptr, nativeId: "scan=" + (s + 1));
    //            }
    //
    //            // write the .mzML
    //            IO.MzML.MzmlMethods.CreateAndWriteMyMzmlWithCalibratedSpectra(new FakeMsDataFile(scans), Path.Combine(TestContext.CurrentContext.TestDirectory, fileToWrite), false);
    //
    //            // set up spectra file info
    //            SpectraFileInfo file1 = new SpectraFileInfo(Path.Combine(TestContext.CurrentContext.TestDirectory, fileToWrite), "", 0, 0, 0);
    //
    //            // create some PSMs
    //            var pg = new ProteinGroup("MyProtein", "gene", "org");
    //
    //            Identification id1 = new Identification(file1, peptide, peptide, new Proteomics.AminoAcidPolymer.Peptide(peptide).MonoisotopicMass, 1.3 + 0.001, 1, new List<ProteinGroup> { pg });
    //
    //            // create the FlashLFQ engine
    //            FlashLfqEngine engine = new FlashLfqEngine(new List<Identification> { id1 });
    //
    //            // run the engine
    //            var results = engine.Run();
    //            ChromatographicPeak peak = results.Peaks.First().Value.First();
    //
    //            Assert.That(peak.Apex.IndexedPeak.RetentionTime == 1.3);
    //            Assert.That(peak.SplitRT == 1.6);
    //            Assert.That(!peak.IsotopicEnvelopes.Any(p => p.IndexedPeak.RetentionTime > 1.6));
    //            Assert.That(peak.IsotopicEnvelopes.Count == 6);
    //        }

//C# TO C++ CONVERTER TODO TASK: Local functions are not converted by C# to C++ Converter:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestPeakSplittingRightWithEmptyScan()
//    public static void TestPeakSplittingRightWithEmptyScan()
    //        {
    //            string fileToWrite = "myMzml.mzML";
    //            string peptide = "PEPTIDE";
    //            double intensity = 1e6;
    //
    //            Loaders.LoadElements(Path.Combine(TestContext.CurrentContext.TestDirectory, "TangibleTempVerbatimOpenTagelements.datTangibleTempVerbatimCloseTag"));
    //
    //            // generate mzml file
    //
    //            // 1 MS1 scan per peptide
    //            MsDataScan[] scans = new MsDataScan[10];
    //            double[] intensityMultipliers = { 1, 3, 5, 10, 5, 3, 1, 1, 3, 1 };
    //
    //            for (int s = 0; s < scans.Length; s++)
    //            {
    //                ChemicalFormula cf = new Proteomics.AminoAcidPolymer.Peptide(peptide).GetChemicalFormula();
    //                IsotopicDistribution dist = IsotopicDistribution.GetDistribution(cf, 0.125, 1e-8);
    //                double[] mz = dist.Masses.Select(v => v.ToMz(1)).ToArray();
    //                double[] intensities = dist.Intensities.Select(v => v * intensity * intensityMultipliers[s]).ToArray();
    //
    //                if (s == 7)
    //                {
    //                    mz = new[] { 401.0 };
    //                    intensities = new[] { 1000.0 };
    //                }
    //
    //                // add the scan
    //                scans[s] = new MsDataScan(massSpectrum: new MzSpectrum(mz, intensities, false), oneBasedScanNumber: s + 1, msnOrder: 1, isCentroid: true, polarity: Polarity.Positive, retentionTime: 1.0 + s / 10.0, scanWindowRange: new MzRange(400, 1600), scanFilter: "f", mzAnalyzer: MZAnalyzerType.Orbitrap, totalIonCurrent: intensities.Sum(), injectionTime: 1.0, noiseData: nullptr, nativeId: "scan=" + (s + 1));
    //            }
    //
    //            // write the .mzML
    //            IO.MzML.MzmlMethods.CreateAndWriteMyMzmlWithCalibratedSpectra(new FakeMsDataFile(scans), Path.Combine(TestContext.CurrentContext.TestDirectory, fileToWrite), false);
    //
    //            // set up spectra file info
    //            SpectraFileInfo file1 = new SpectraFileInfo(Path.Combine(TestContext.CurrentContext.TestDirectory, fileToWrite), "", 0, 0, 0);
    //
    //            // create some PSMs
    //            var pg = new ProteinGroup("MyProtein", "gene", "org");
    //
    //            Identification id1 = new Identification(file1, peptide, peptide, new Proteomics.AminoAcidPolymer.Peptide(peptide).MonoisotopicMass, 1.3 + 0.001, 1, new List<ProteinGroup> { pg });
    //
    //            // create the FlashLFQ engine
    //            FlashLfqEngine engine = new FlashLfqEngine(new List<Identification> { id1 });
    //
    //            // run the engine
    //            var results = engine.Run();
    //            ChromatographicPeak peak = results.Peaks.First().Value.First();
    //
    //            Assert.That(peak.Apex.IndexedPeak.RetentionTime == 1.3);
    //            Assert.That(peak.SplitRT == 1.6);
    //            Assert.That(!peak.IsotopicEnvelopes.Any(p => p.IndexedPeak.RetentionTime > 1.6));
    //            Assert.That(peak.IsotopicEnvelopes.Count == 6);
    //        }

//C# TO C++ CONVERTER TODO TASK: Local functions are not converted by C# to C++ Converter:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestPeakSplittingLeftWithEmptyScan()
//    public static void TestPeakSplittingLeftWithEmptyScan()
    //        {
    //            string fileToWrite = "myMzml.mzML";
    //            string peptide = "PEPTIDE";
    //            double intensity = 1e6;
    //
    //            Loaders.LoadElements(Path.Combine(TestContext.CurrentContext.TestDirectory, "TangibleTempVerbatimOpenTagelements.datTangibleTempVerbatimCloseTag"));
    //
    //            // generate mzml file
    //
    //            // 1 MS1 scan per peptide
    //            MsDataScan[] scans = new MsDataScan[10];
    //            double[] intensityMultipliers = { 1, 3, 1, 1, 3, 5, 10, 5, 3, 1 };
    //
    //            for (int s = 0; s < scans.Length; s++)
    //            {
    //                ChemicalFormula cf = new Proteomics.AminoAcidPolymer.Peptide(peptide).GetChemicalFormula();
    //                IsotopicDistribution dist = IsotopicDistribution.GetDistribution(cf, 0.125, 1e-8);
    //                double[] mz = dist.Masses.Select(v => v.ToMz(1)).ToArray();
    //                double[] intensities = dist.Intensities.Select(v => v * intensity * intensityMultipliers[s]).ToArray();
    //
    //                if (s == 2)
    //                {
    //                    mz = new[] { 401.0 };
    //                    intensities = new[] { 1000.0 };
    //                }
    //
    //                // add the scan
    //                scans[s] = new MsDataScan(massSpectrum: new MzSpectrum(mz, intensities, false), oneBasedScanNumber: s + 1, msnOrder: 1, isCentroid: true, polarity: Polarity.Positive, retentionTime: 1.0 + s / 10.0, scanWindowRange: new MzRange(400, 1600), scanFilter: "f", mzAnalyzer: MZAnalyzerType.Orbitrap, totalIonCurrent: intensities.Sum(), injectionTime: 1.0, noiseData: nullptr, nativeId: "scan=" + (s + 1));
    //            }
    //
    //            // write the .mzML
    //            IO.MzML.MzmlMethods.CreateAndWriteMyMzmlWithCalibratedSpectra(new FakeMsDataFile(scans), Path.Combine(TestContext.CurrentContext.TestDirectory, fileToWrite), false);
    //
    //            // set up spectra file info
    //            SpectraFileInfo file1 = new SpectraFileInfo(Path.Combine(TestContext.CurrentContext.TestDirectory, fileToWrite), "", 0, 0, 0);
    //
    //            // create some PSMs
    //            var pg = new ProteinGroup("MyProtein", "gene", "org");
    //
    //            Identification id1 = new Identification(file1, peptide, peptide, new Proteomics.AminoAcidPolymer.Peptide(peptide).MonoisotopicMass, 1.3 + 0.001, 1, new List<ProteinGroup> { pg });
    //
    //            // create the FlashLFQ engine
    //            FlashLfqEngine engine = new FlashLfqEngine(new List<Identification> { id1 });
    //
    //            // run the engine
    //            var results = engine.Run();
    //            ChromatographicPeak peak = results.Peaks.First().Value.First();
    //
    //            Assert.That(peak.Apex.IndexedPeak.RetentionTime == 1.6);
    //            Assert.That(peak.SplitRT == 1.3);
    //            Assert.That(!peak.IsotopicEnvelopes.Any(p => p.IndexedPeak.RetentionTime < 1.3));
    //            Assert.That(peak.IsotopicEnvelopes.Count == 6);
    //        }

//C# TO C++ CONVERTER TODO TASK: Local functions are not converted by C# to C++ Converter:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestToString()
//    public static void TestToString()
    //        {
    //            // many of these are just to check that the ToString methods don't cause crashes
    //            var indexedPeak = new IndexedMassSpectralPeak(1.0, 2.0, 4, 5.0);
    //            Assert.That(indexedPeak.ToString().Equals("1.000; 4"));
    //
    //            var spectraFile = new SpectraFileInfo("myFullPath", "", 0, 0, 0);
    //            string spectraString = spectraFile.ToString();
    //
    //            var proteinGroup = new ProteinGroup("Accession", "Gene", "Organism");
    //            string pgString = proteinGroup.ToString(new List<SpectraFileInfo> { spectraFile });
    //
    //            var identification = new Identification(spectraFile, "PEPTIDE", "PEPTIDE", 1.0, 2.0, 3, new List<ProteinGroup> { proteinGroup });
    //            string idString = identification.ToString();
    //
    //            var chromPeak = new ChromatographicPeak(identification, false, spectraFile);
    //            string chromPeakString = chromPeak.ToString();
    //            chromPeak.CalculateIntensityForThisFeature(true);
    //            string peakAfterCalculatingIntensity = chromPeak.ToString();
    //        }

//C# TO C++ CONVERTER TODO TASK: Local functions are not converted by C# to C++ Converter:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestNotFound()
//    public static void TestNotFound()
    //        {
    //            Peptide p = new Peptide("Seq", true);
    //            var notFound = p.GetDetectionType(new SpectraFileInfo("", "", 0, 0, 0));
    //            Assert.That(notFound == DetectionType.NotDetected);
    //        }

//C# TO C++ CONVERTER TODO TASK: Local functions are not converted by C# to C++ Converter:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestMergePeaks()
//    public static void TestMergePeaks()
    //        {
    //            string fileToWrite = "myMzml.mzML";
    //            string peptide = "PEPTIDE";
    //            double intensity = 1e6;
    //
    //            Loaders.LoadElements(Path.Combine(TestContext.CurrentContext.TestDirectory, "TangibleTempVerbatimOpenTagelements.datTangibleTempVerbatimCloseTag"));
    //
    //            // generate mzml file
    //            MsDataScan[] scans = new MsDataScan[5];
    //            double[] intensityMultipliers = { 1, 3, 1, 1, 1 };
    //
    //            for (int s = 0; s < scans.Length; s++)
    //            {
    //                ChemicalFormula cf = new Proteomics.AminoAcidPolymer.Peptide(peptide).GetChemicalFormula();
    //                IsotopicDistribution dist = IsotopicDistribution.GetDistribution(cf, 0.125, 1e-8);
    //                double[] mz = dist.Masses.Select(v => v.ToMz(1)).ToArray();
    //                double[] intensities = dist.Intensities.Select(v => v * intensity * intensityMultipliers[s]).ToArray();
    //
    //                if (s == 2 || s == 3)
    //                {
    //                    mz = new[] { 401.0 };
    //                    intensities = new[] { 1000.0 };
    //                }
    //
    //                // add the scan
    //                scans[s] = new MsDataScan(massSpectrum: new MzSpectrum(mz, intensities, false), oneBasedScanNumber: s + 1, msnOrder: 1, isCentroid: true, polarity: Polarity.Positive, retentionTime: 1.0 + s / 10.0, scanWindowRange: new MzRange(400, 1600), scanFilter: "f", mzAnalyzer: MZAnalyzerType.Orbitrap, totalIonCurrent: intensities.Sum(), injectionTime: 1.0, noiseData: nullptr, nativeId: "scan=" + (s + 1));
    //            }
    //
    //            // write the .mzML
    //            IO.MzML.MzmlMethods.CreateAndWriteMyMzmlWithCalibratedSpectra(new FakeMsDataFile(scans), Path.Combine(TestContext.CurrentContext.TestDirectory, fileToWrite), false);
    //
    //            // set up spectra file info
    //            SpectraFileInfo file1 = new SpectraFileInfo(Path.Combine(TestContext.CurrentContext.TestDirectory, fileToWrite), "", 0, 0, 0);
    //
    //            // create some PSMs
    //            var pg = new ProteinGroup("MyProtein", "gene", "org");
    //
    //            Identification id1 = new Identification(file1, peptide, peptide, new Proteomics.AminoAcidPolymer.Peptide(peptide).MonoisotopicMass, 1.1 + 0.001, 1, new List<ProteinGroup> { pg });
    //            Identification id2 = new Identification(file1, peptide, peptide, new Proteomics.AminoAcidPolymer.Peptide(peptide).MonoisotopicMass, 1.4 + 0.001, 1, new List<ProteinGroup> { pg });
    //
    //            // create the FlashLFQ engine
    //            FlashLfqEngine engine = new FlashLfqEngine(new List<Identification> { id1, id2 });
    //
    //            // run the engine
    //            var results = engine.Run();
    //            ChromatographicPeak peak = results.Peaks.First().Value.First();
    //
    //            Assert.That(results.Peaks.First().Value.Count == 1);
    //            Assert.That(peak.Apex.IndexedPeak.RetentionTime == 1.1);
    //        }

//C# TO C++ CONVERTER TODO TASK: Local functions are not converted by C# to C++ Converter:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestAmbiguous()
//    public static void TestAmbiguous()
    //        {
    //            // get the raw file paths
    //            SpectraFileInfo mzml = new SpectraFileInfo(Path.Combine(TestContext.CurrentContext.TestDirectory, "TangibleTempVerbatimOpenTagsliced-mzml.mzmlTangibleTempVerbatimCloseTag"), "a", 0, 1, 0);
    //
    //            // create some PSMs
    //            var pg = new ProteinGroup("MyProtein", "gene", "org");
    //            Identification id3 = new Identification(mzml, "EGFQVADGPLRY", "EGFQVADGPLRY", 1350.65681, 94.12193, 2, new List<ProteinGroup> { pg });
    //            Identification id4 = new Identification(mzml, "EGFQVADGPLYR", "EGFQVADGPLYR", 1350.65681, 94.05811, 2, new List<ProteinGroup> { pg });
    //
    //            // create the FlashLFQ engine
    //            FlashLfqEngine engine = new FlashLfqEngine(new List<Identification> { id3, id4 });
    //
    //            // run the engine
    //            var results = engine.Run();
    //
    //            Assert.That(results.Peaks[mzml].Count == 1);
    //            Assert.That(results.Peaks[mzml].First().Intensity > 0);
    //            Assert.That(!results.Peaks[mzml].First().IsMbrPeak);
    //            Assert.That(results.Peaks[mzml].First().NumIdentificationsByFullSeq == 2);
    //            Assert.That(results.PeptideModifiedSequences["EGFQVADGPLYR"].GetIntensity(mzml) == 0);
    //            Assert.That(results.PeptideModifiedSequences["EGFQVADGPLRY"].GetIntensity(mzml) == 0);
    //            Assert.That(results.ProteinGroups["MyProtein"].GetIntensity(mzml) == 0);
    //
    //            // test peak output
    //            results.WriteResults(Path.Combine(TestContext.CurrentContext.TestDirectory, "TangibleTempVerbatimOpenTagpeaks.tsvTangibleTempVerbatimCloseTag"), Path.Combine(TestContext.CurrentContext.TestDirectory, "TangibleTempVerbatimOpenTagmodSeq.tsvTangibleTempVerbatimCloseTag"), Path.Combine(TestContext.CurrentContext.TestDirectory, "TangibleTempVerbatimOpenTagprotein.tsvTangibleTempVerbatimCloseTag"));
    //        }

//C# TO C++ CONVERTER TODO TASK: Local functions are not converted by C# to C++ Converter:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestPeakMerging()
//    public static void TestPeakMerging()
    //        {
    //            string fileToWrite = "myMzml.mzML";
    //            string peptide = "PEPTIDE";
    //            double intensity = 1e6;
    //
    //            Loaders.LoadElements(Path.Combine(TestContext.CurrentContext.TestDirectory, "TangibleTempVerbatimOpenTagelements.datTangibleTempVerbatimCloseTag"));
    //
    //            // generate mzml file
    //
    //            // 1 MS1 scan per peptide
    //            MsDataScan[] scans = new MsDataScan[10];
    //            double[] intensityMultipliers = { 1, 3, 5, 10, 5, 3, 1, 1, 1, 1 };
    //
    //            for (int s = 0; s < scans.Length; s++)
    //            {
    //                ChemicalFormula cf = new Proteomics.AminoAcidPolymer.Peptide(peptide).GetChemicalFormula();
    //                IsotopicDistribution dist = IsotopicDistribution.GetDistribution(cf, 0.125, 1e-8);
    //                double[] mz = dist.Masses.Select(v => v.ToMz(1)).ToArray();
    //                double[] intensities = dist.Intensities.Select(v => v * intensity * intensityMultipliers[s]).ToArray();
    //
    //                if (s == 7 || s == 8)
    //                {
    //                    mz = new[] { 401.0 };
    //                    intensities = new[] { 1000.0 };
    //                }
    //
    //                // add the scan
    //                scans[s] = new MsDataScan(massSpectrum: new MzSpectrum(mz, intensities, false), oneBasedScanNumber: s + 1, msnOrder: 1, isCentroid: true, polarity: Polarity.Positive, retentionTime: 1.0 + s / 10.0, scanWindowRange: new MzRange(400, 1600), scanFilter: "f", mzAnalyzer: MZAnalyzerType.Orbitrap, totalIonCurrent: intensities.Sum(), injectionTime: 1.0, noiseData: nullptr, nativeId: "scan=" + (s + 1));
    //            }
    //
    //            // write the .mzML
    //            IO.MzML.MzmlMethods.CreateAndWriteMyMzmlWithCalibratedSpectra(new FakeMsDataFile(scans), Path.Combine(TestContext.CurrentContext.TestDirectory, fileToWrite), false);
    //
    //            // set up spectra file info
    //            SpectraFileInfo file1 = new SpectraFileInfo(Path.Combine(TestContext.CurrentContext.TestDirectory, fileToWrite), "", 0, 0, 0);
    //
    //            // create some PSMs
    //            var pg = new ProteinGroup("MyProtein", "gene", "org");
    //
    //            Identification id1 = new Identification(file1, peptide, peptide, new Proteomics.AminoAcidPolymer.Peptide(peptide).MonoisotopicMass, 1.3 + 0.001, 1, new List<ProteinGroup> { pg });
    //            Identification id2 = new Identification(file1, peptide, peptide, new Proteomics.AminoAcidPolymer.Peptide(peptide).MonoisotopicMass, 1.9 + 0.001, 1, new List<ProteinGroup> { pg });
    //
    //            // create the FlashLFQ engine
    //            FlashLfqEngine engine = new FlashLfqEngine(new List<Identification> { id1, id2 });
    //
    //            // run the engine
    //            var results = engine.Run();
    //            ChromatographicPeak peak = results.Peaks.First().Value.First();
    //
    //            Assert.That(peak.Apex.IndexedPeak.RetentionTime == 1.3);
    //            Assert.That(peak.IsotopicEnvelopes.Count == 8);
    //            Assert.That(results.Peaks.First().Value.Count == 1);
    //        }

//C# TO C++ CONVERTER TODO TASK: Local functions are not converted by C# to C++ Converter:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [Test] public static void TestMatchBetweenRunsWithNoIdsInCommon()
//    public static void TestMatchBetweenRunsWithNoIdsInCommon()
    //        {
    //            List<string> filesToWrite = new List<string> { "mzml_1", "mzml_2" };
    //            List<string> pepSequences = new List<string> { "PEPTIDE", "PEPTIDEV", "PEPTIDEVV", "PEPTIDEVVV", "PEPTIDEVVVV" };
    //            double intensity = 1e6;
    //
    //            double[] file1Rt = new double[] { 1.01, 1.02, 1.03, 1.04, 1.05 };
    //            double[] file2Rt = new double[] { 1.015, 1.030, 1.036, 1.050, 1.065 };
    //
    //            Loaders.LoadElements(Path.Combine(TestContext.CurrentContext.TestDirectory, "TangibleTempVerbatimOpenTagelements.datTangibleTempVerbatimCloseTag"));
    //
    //            // generate mzml files (5 peptides each)
    //            for (int f = 0; f < filesToWrite.Count; f++)
    //            {
    //                // 1 MS1 scan per peptide
    //                MsDataScan[] scans = new MsDataScan[5];
    //
    //                for (int p = 0; p < pepSequences.Count; p++)
    //                {
    //                    ChemicalFormula cf = new Proteomics.AminoAcidPolymer.Peptide(pepSequences[p]).GetChemicalFormula();
    //                    IsotopicDistribution dist = IsotopicDistribution.GetDistribution(cf, 0.125, 1e-8);
    //                    double[] mz = dist.Masses.Select(v => v.ToMz(1)).ToArray();
    //                    double[] intensities = dist.Intensities.Select(v => v * intensity).ToArray();
    //                    double rt;
    //                    if (f == 0)
    //                    {
    //                        rt = file1Rt[p];
    //                    }
    //                    else
    //                    {
    //                        rt = file2Rt[p];
    //                    }
    //
    //                    // add the scan
    //                    scans[p] = new MsDataScan(massSpectrum: new MzSpectrum(mz, intensities, false), oneBasedScanNumber: p + 1, msnOrder: 1, isCentroid: true, polarity: Polarity.Positive, retentionTime: rt, scanWindowRange: new MzRange(400, 1600), scanFilter: "f", mzAnalyzer: MZAnalyzerType.Orbitrap, totalIonCurrent: intensities.Sum(), injectionTime: 1.0, noiseData: nullptr, nativeId: "scan=" + (p + 1));
    //                }
    //
    //                // write the .mzML
    //                IO.MzML.MzmlMethods.CreateAndWriteMyMzmlWithCalibratedSpectra(new FakeMsDataFile(scans), Path.Combine(TestContext.CurrentContext.TestDirectory, filesToWrite[f] + ".mzML"), false);
    //            }
    //
    //            // set up spectra file info
    //            SpectraFileInfo file1 = new SpectraFileInfo(Path.Combine(TestContext.CurrentContext.TestDirectory, filesToWrite[0] + ".mzML"), "a", 0, 0, 0);
    //            SpectraFileInfo file2 = new SpectraFileInfo(Path.Combine(TestContext.CurrentContext.TestDirectory, filesToWrite[1] + ".mzML"), "a", 1, 0, 0);
    //
    //            // create some PSMs
    //            var pg = new ProteinGroup("MyProtein", "gene", "org");
    //            var myMbrProteinGroup = new ProteinGroup("MyMbrProtein", "MbrGene", "org");
    //
    //            Identification id1 = new Identification(file1, "PEPTIDE", "PEPTIDE", new Proteomics.AminoAcidPolymer.Peptide("PEPTIDE").MonoisotopicMass, file1Rt[0] + 0.001, 1, new List<ProteinGroup> { pg });
    //            Identification id2 = new Identification(file1, "PEPTIDEV", "PEPTIDEV", new Proteomics.AminoAcidPolymer.Peptide("PEPTIDEV").MonoisotopicMass, file1Rt[1] + 0.001, 1, new List<ProteinGroup> { pg });
    //            Identification id3 = new Identification(file1, "PEPTIDEVV", "PEPTIDEVV", new Proteomics.AminoAcidPolymer.Peptide("PEPTIDEVV").MonoisotopicMass, file1Rt[2] + 0.001, 1, new List<ProteinGroup> { myMbrProteinGroup });
    //            Identification id4 = new Identification(file1, "PEPTIDEVVV", "PEPTIDEVVV", new Proteomics.AminoAcidPolymer.Peptide("PEPTIDEVVV").MonoisotopicMass, file1Rt[3] + 0.001, 1, new List<ProteinGroup> { pg });
    //            Identification id5 = new Identification(file1, "PEPTIDEVVVV", "PEPTIDEVVVV", new Proteomics.AminoAcidPolymer.Peptide("PEPTIDEVVVV").MonoisotopicMass, file1Rt[4] + 0.001, 1, new List<ProteinGroup> { pg });
    //
    //            Identification id6 = new Identification(file2, "PEPTIED", "PEPTIED", new Proteomics.AminoAcidPolymer.Peptide("PEPTIED").MonoisotopicMass, file2Rt[0] + 0.001, 1, new List<ProteinGroup> { pg });
    //            Identification id7 = new Identification(file2, "PEPTIEDV", "PEPTIEDV", new Proteomics.AminoAcidPolymer.Peptide("PEPTIEDV").MonoisotopicMass, file2Rt[1] + 0.001, 1, new List<ProteinGroup> { pg });
    //            // missing ID 8 - MBR feature
    //            Identification id9 = new Identification(file2, "PEPTIEDVVV", "PEPTIEDVVV", new Proteomics.AminoAcidPolymer.Peptide("PEPTIEDVVV").MonoisotopicMass, file2Rt[3] + 0.001, 1, new List<ProteinGroup> { pg });
    //            Identification id10 = new Identification(file2, "PEPTIEDVVVV", "PEPTIEDVVVV", new Proteomics.AminoAcidPolymer.Peptide("PEPTIEDVVVV").MonoisotopicMass, file2Rt[4] + 0.001, 1, new List<ProteinGroup> { pg });
    //
    //            FlashLfqEngine engine = new FlashLfqEngine(new List<Identification> { id1, id2, id3, id4, id5, id6, id7, id9, id10 }, matchBetweenRuns: true);
    //            var results = engine.Run();
    //
    //            // no assertions - just don't crash
    //        }
    }