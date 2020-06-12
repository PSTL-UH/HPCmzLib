#include "TestThermo.h"
#include "../MassSpectrometry/MzSpectra/MzSpectrum.h"
#include "../MzLibUtil/MzRange.h"
#include "../MassSpectrometry/Enums/Polarity.h"
#include "../MassSpectrometry/FilteringParams.h"
#include "../MassSpectrometry/MsDataScan.h"
#include "../MassSpectrometry/SummedMsDataFile.h"

using namespace Chemistry;
using namespace IO::MzML;
using namespace IO::Thermo;
using namespace MassSpectrometry;
using namespace MzLibUtil;
using namespace NUnit::Framework;
namespace Stopwatch = System::Diagnostics::Stopwatch;

namespace TestThermo
{

System::Diagnostics::Stopwatch *TestThermo::privateStopwatch;

    Stopwatch *TestThermo::getStopwatch()
    {
        return privateStopwatch;
    }

    void TestThermo::setStopwatch(Stopwatch *value)
    {
        privateStopwatch = value;
    }

    void TestThermo::Setuppp()
    {
        Stopwatch tempVar();
        setStopwatch(&tempVar);
        getStopwatch()->Start();
    }

    void TestThermo::TearDown()
    {
        std::cout << StringHelper::formatSimple("Analysis time: {0}h {1}m {2}s", getStopwatch()->Elapsed.Hours, getStopwatch()->Elapsed.Minutes, getStopwatch()->Elapsed.Seconds) << std::endl;
    }

    void TestThermo::ReadWriteReadEtc(const std::string &infile, const std::string &outfile1, const std::string &outfile2)
    {
        ThermoStaticData *a = ThermoStaticData::LoadAllStaticData(infile);
        MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(a, outfile1, false);
        auto aa = Mzml::LoadAllStaticData(outfile1);
        MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(aa, outfile2, true);
        Mzml::LoadAllStaticData(outfile2);
    }

    void TestThermo::ThermoLoadError()
    {
        Assert::Throws<FileNotFoundException*>([&] ()
        {
            ThermoStaticData::LoadAllStaticData(R"(aaa.RAW)");
        });
    }

    void TestThermo::ThermoReaderNotInstalled()
    {
        bool check = ThermoStaticData::CheckForMsFileReader();
        Assert::IsTrue(check);
    }

    void TestThermo::LoadCompressedMzml()
    {
        ThermoStaticData *a = ThermoStaticData::LoadAllStaticData(R"(small.RAW)");

        Mzml *b = Mzml::LoadAllStaticData(R"(smallCentroid.mzML)");

        Assert::AreEqual(a->getNumSpectra(), b->getNumSpectra());

        Assert::AreEqual(a->GetOneBasedScan(1)->MassSpectrum.XofPeakWithHighestY->Value, b->GetOneBasedScan(1)->MassSpectrum.XofPeakWithHighestY->Value, 1e-8);
        Assert::IsTrue(std::abs((a->GetOneBasedScan(1)->MassSpectrum.YofPeakWithHighestY->Value - b->GetOneBasedScan(1)->MassSpectrum.YofPeakWithHighestY->Value) / b->GetOneBasedScan(1)->MassSpectrum.YofPeakWithHighestY->Value) < 1e-8);

        Assert::AreEqual(a->GetOneBasedScan(2)->MassSpectrum.XofPeakWithHighestY->Value, b->GetOneBasedScan(2)->MassSpectrum.XofPeakWithHighestY, 1e-8);
        Assert::IsTrue(std::abs((a->GetOneBasedScan(2)->MassSpectrum.YofPeakWithHighestY->Value - b->GetOneBasedScan(2)->MassSpectrum.YofPeakWithHighestY->Value) / b->GetOneBasedScan(1)->MassSpectrum.YofPeakWithHighestY->Value) < 1e-8);

        Assert::AreEqual(a->GetOneBasedScan(3)->MassSpectrum.XofPeakWithHighestY->Value, b->GetOneBasedScan(3)->MassSpectrum.XofPeakWithHighestY->Value, 1e-8);
        Assert::IsTrue(std::abs((a->GetOneBasedScan(3)->MassSpectrum.YofPeakWithHighestY->Value - b->GetOneBasedScan(3)->MassSpectrum.YofPeakWithHighestY->Value) / b->GetOneBasedScan(1)->MassSpectrum.YofPeakWithHighestY->Value) < 1e-8);
    }

    void TestThermo::LoadThermoTest2()
    {
        ThermoStaticData *a = ThermoStaticData::LoadAllStaticData(R"(05-13-16_cali_MS_60K-res_MS.raw)");
        Assert::AreEqual(360, a->getNumSpectra());
        Assert::GreaterOrEqual(1000, a->GetOneBasedScan(1)->MassSpectrum.Extract(0, 500).Last().Mz);
        Assert::AreEqual(2, a->GetOneBasedScan(1)->MassSpectrum.FilterByY(5e6, std::numeric_limits<double>::max())->Count());
        auto ye = a->GetOneBasedScan(1)->MassSpectrum.CopyTo2DArray();
        Assert::AreEqual(77561752, a->GetOneBasedScan(1)->getTotalIonCurrent());
        Assert::AreEqual(144, a->GetClosestOneBasedSpectrumNumber(2));

        MzSpectrum *newSpectrum = new MzSpectrum(a->GetOneBasedScan(51)->MassSpectrum.XArray, a->GetOneBasedScan(51)->MassSpectrum.YArray, true);

        Assert::AreEqual(1120, a->GetOneBasedScan(1)->MassSpectrum.Size);

        MzRange tempVar(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max());
        auto newDeconvolution = a->GetOneBasedScan(1)->MassSpectrum.Deconvolute(&tempVar, 1, 10, 1, 4).ToList();

        Assert::IsTrue(newDeconvolution->Any([&] (std::any b)
        {
        delete newSpectrum;
            return std::abs(b::peaks::First().mz::ToMass(b::charge) - 523.257) < 0.001;
        }));

        MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(a, FileSystem::combine(TestContext::CurrentContext->TestDirectory, "convertedThermo.mzML"), false);

        auto sdafaf = a->Deconvolute(std::nullopt, std::nullopt, 1, 30, 10, 3, 10, [&] (std::any b)
        {
            true;
        }).OrderByDescending([&] (std::any b)
        {
            b::NumPeaks;
        }).First();

        Assert::IsTrue(std::abs(262.64 - sdafaf->Mass.ToMz(2)) <= 0.01);

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (ThermoDynamicData dynamicThermo = ThermoDynamicData.InitiateDynamicConnection("TangibleTempVerbatimOpenTag05-13-16_cali_MS_60K-res_MS.rawTangibleTempVerbatimCloseTag"))
        {
            ThermoDynamicData dynamicThermo = ThermoDynamicData::InitiateDynamicConnection(R"(05-13-16_cali_MS_60K-res_MS.raw)");
            Assert::AreEqual(136, dynamicThermo->GetClosestOneBasedSpectrumNumber(1.89));
            dynamicThermo->ClearCachedScans();
        }

        Mzml *readCovertedMzmlFile = Mzml::LoadAllStaticData(FileSystem::combine(TestContext::CurrentContext->TestDirectory, "convertedThermo.mzML"));

        Assert::AreEqual(a->GetAllScansList().front().Polarity, readCovertedMzmlFile->GetAllScansList().front().Polarity);

        delete newSpectrum;
    }

    void TestThermo::WindowFilteringStaticTest()
    {
        //test window number of 1
        ThermoStaticData *a_w = ThermoStaticData::LoadAllStaticData(R"(05-13-16_cali_MS_60K-res_MS.raw)");
        FilteringParams tempVar(std::make_optional(400), std::nullopt, std::make_optional(1), true, true);
        ThermoStaticData *b_w = ThermoStaticData::LoadAllStaticData(R"(05-13-16_cali_MS_60K-res_MS.raw)", &tempVar);
        FilteringParams tempVar2(std::nullopt, std::make_optional(0.001), std::make_optional(1), true, true);
        ThermoStaticData *c_w = ThermoStaticData::LoadAllStaticData(R"(05-13-16_cali_MS_60K-res_MS.raw)", &tempVar2);
        FilteringParams tempVar3(std::make_optional(400), std::make_optional(0.001), std::make_optional(1), true, true);
        ThermoStaticData *d_w = ThermoStaticData::LoadAllStaticData(R"(05-13-16_cali_MS_60K-res_MS.raw)", &tempVar3);
        auto aLen = a_w->GetOneBasedScan(1)->MassSpectrum.Size;
        auto bLen = b_w->GetOneBasedScan(1)->MassSpectrum.Size;
        auto cLen = c_w->GetOneBasedScan(1)->MassSpectrum.Size;
        auto dLen = d_w->GetOneBasedScan(1)->MassSpectrum.Size;
        Assert::AreEqual(std::min(bLen, cLen), dLen);
        auto aLen2 = a_w->GetOneBasedScan(2)->MassSpectrum.Size;
        auto bLen2 = b_w->GetOneBasedScan(2)->MassSpectrum.Size;
        auto cLen2 = c_w->GetOneBasedScan(2)->MassSpectrum.Size;
        auto dLen2 = d_w->GetOneBasedScan(2)->MassSpectrum.Size;
        Assert::AreEqual(std::min(bLen2, cLen2), dLen2);
        auto aLen3 = a_w->GetOneBasedScan(3)->MassSpectrum.Size;
        auto bLen3 = b_w->GetOneBasedScan(3)->MassSpectrum.Size;
        auto cLen3 = c_w->GetOneBasedScan(3)->MassSpectrum.Size;
        auto dLen3 = d_w->GetOneBasedScan(3)->MassSpectrum.Size;
        Assert::AreEqual(std::min(bLen3, cLen3), dLen3);
    }

    void TestThermo::MultiWindowFiltering()
    {
        //tests for filtering with window
        FilteringParams tempVar(std::nullopt, std::nullopt, std::make_optional(1), true, true);
        ThermoStaticData *a_w = ThermoStaticData::LoadAllStaticData(R"(05-13-16_cali_MS_60K-res_MS.raw)", &tempVar);
        Assert::AreEqual(1120, a_w->GetOneBasedScan(1)->MassSpectrum.Size);
        //number of 2
        FilteringParams tempVar2(std::make_optional(200), std::nullopt, std::make_optional(3), true, true);
        ThermoStaticData *b_w = ThermoStaticData::LoadAllStaticData(R"(05-13-16_cali_MS_60K-res_MS.raw)", &tempVar2);
        Assert::AreEqual(600, b_w->GetOneBasedScan(1)->MassSpectrum.Size);
        //number of 4
        FilteringParams tempVar3(std::make_optional(200), std::nullopt, std::make_optional(4), true, true);
        ThermoStaticData *c_w = ThermoStaticData::LoadAllStaticData(R"(05-13-16_cali_MS_60K-res_MS.raw)", &tempVar3);
        Assert::AreEqual(742, c_w->GetOneBasedScan(1)->MassSpectrum.Size);
        //number of 6, which doesn't divide 1120
        FilteringParams tempVar4(std::make_optional(150), std::nullopt, std::make_optional(6), true, true);
        ThermoStaticData *d_w = ThermoStaticData::LoadAllStaticData(R"(05-13-16_cali_MS_60K-res_MS.raw)", &tempVar4);
        Assert::AreEqual(775, d_w->GetOneBasedScan(1)->MassSpectrum.Size);
    }

    void TestThermo::LoadThermoFiltered()
    {
        ThermoStaticData *a = ThermoStaticData::LoadAllStaticData(R"(05-13-16_cali_MS_60K-res_MS.raw)");
        FilteringParams tempVar(std::make_optional(400), std::nullopt, std::nullopt, true, true);
        ThermoStaticData *b = ThermoStaticData::LoadAllStaticData(R"(05-13-16_cali_MS_60K-res_MS.raw)", &tempVar);
        FilteringParams tempVar2(std::nullopt, std::make_optional(0.001), std::nullopt, true, true);
        ThermoStaticData *c = ThermoStaticData::LoadAllStaticData(R"(05-13-16_cali_MS_60K-res_MS.raw)", &tempVar2);
        FilteringParams tempVar3(std::make_optional(400), std::make_optional(0.001), std::nullopt, true, true);
        ThermoStaticData *d = ThermoStaticData::LoadAllStaticData(R"(05-13-16_cali_MS_60K-res_MS.raw)", &tempVar3);

        auto aLen = a->GetOneBasedScan(1)->MassSpectrum.Size;
        auto bLen = b->GetOneBasedScan(1)->MassSpectrum.Size;
        auto cLen = c->GetOneBasedScan(1)->MassSpectrum.Size;
        auto dLen = d->GetOneBasedScan(1)->MassSpectrum.Size;

        Assert::AreEqual(std::min(bLen, cLen), dLen);
    }

    void TestThermo::LoadThermoFiltered2()
    {
        ThermoStaticData *a = ThermoStaticData::LoadAllStaticData(R"(small.raw)");
        FilteringParams tempVar(std::make_optional(40), std::nullopt, std::nullopt, true, true);
        ThermoStaticData *b = ThermoStaticData::LoadAllStaticData(R"(small.raw)", &tempVar);
        FilteringParams tempVar2(std::nullopt, std::make_optional(0.1), std::nullopt, true, true);
        ThermoStaticData *c = ThermoStaticData::LoadAllStaticData(R"(small.raw)", &tempVar2);
        FilteringParams tempVar3(std::make_optional(40), std::make_optional(0.1), std::nullopt, true, true);
        ThermoStaticData *d = ThermoStaticData::LoadAllStaticData(R"(small.raw)", &tempVar3);

        auto aLen = a->GetOneBasedScan(1)->MassSpectrum.Size;
        auto bLen = b->GetOneBasedScan(1)->MassSpectrum.Size;
        auto cLen = c->GetOneBasedScan(1)->MassSpectrum.Size;
        auto dLen = d->GetOneBasedScan(1)->MassSpectrum.Size;

        Assert::AreEqual(std::min(bLen, cLen), dLen);

        auto aLen2 = a->GetOneBasedScan(2)->MassSpectrum.Size;
        auto bLen2 = b->GetOneBasedScan(2)->MassSpectrum.Size;
        auto cLen2 = c->GetOneBasedScan(2)->MassSpectrum.Size;
        auto dLen2 = d->GetOneBasedScan(2)->MassSpectrum.Size;

        Assert::AreEqual(std::min(bLen2, cLen2), dLen2);

        auto aLen3 = a->GetOneBasedScan(3)->MassSpectrum.Size;
        auto bLen3 = b->GetOneBasedScan(3)->MassSpectrum.Size;
        auto cLen3 = c->GetOneBasedScan(3)->MassSpectrum.Size;
        auto dLen3 = d->GetOneBasedScan(3)->MassSpectrum.Size;

        Assert::AreEqual(std::min(bLen3, cLen3), dLen3);
    }

    void TestThermo::LoadThermoTest3()
    {
        ThermoStaticData *a = ThermoStaticData::LoadAllStaticData(R"(small.RAW)");

        Assert::IsTrue(a->GetAllScansList().Where([&] (std::any eb)
        {
            return eb::MsnOrder > 1;
        })->Count() > 0);

        Assert::IsTrue(a->GetAllScansList().Where([&] (std::any eb)
        {
            return eb->MsnOrder == 1;
        })->Count() > 0);

        Assert::IsFalse(a->ThermoGlobalParams.MonoisotopicselectionEnabled);

        auto hehe = a->GetAllScansList().First([&] (std::any b)
        {
            return b::MsnOrder > 1;
        });

        auto prec = a->GetOneBasedScan(hehe->OneBasedPrecursorScanNumber->Value);

        Assert::IsNull(hehe->SelectedIonChargeStateGuess);

        Assert::IsNull(hehe->SelectedIonIntensity);

        hehe->ComputeSelectedPeakIntensity(prec->MassSpectrum);

        Assert::AreEqual(1017759, hehe->SelectedIonIntensity, 1);

        Assert::IsNull(hehe->SelectedIonMonoisotopicGuessIntensity);

        hehe->ComputeMonoisotopicPeakIntensity(prec->MassSpectrum);

        Assert::AreEqual(1017759, hehe->SelectedIonMonoisotopicGuessIntensity, 1);
    }

    void TestThermo::ThermoSpectrumTest()
    {
        std::vector<double> mz = {1};
        std::vector<double> intensity = {1};
        MzSpectrum *s1 = new MzSpectrum(mz, intensity, false);
        MzSpectrum *s2 = new MzSpectrum(mz, intensity, false);
        s1->ReplaceXbyApplyingFunction([&] (a)
        {
            4;
        });
        Assert::AreEqual(4, s2->getXArray()[0]);

        delete s2;
        delete s1;
    }

    void TestThermo::ThermoDynamicTest()
    {
        ThermoDynamicData *dynamicThermo = ThermoDynamicData::InitiateDynamicConnection(R"(testFileWMS2.raw)");
        auto ms1scan = dynamicThermo->GetOneBasedScan(1);
        MsDataScan *ms2scan = dynamicThermo->GetOneBasedScan(651);
        Assert::That(ms1scan->getOneBasedScanNumber() == 1);
        Assert::That(ms2scan->getOneBasedScanNumber() == 651);
        Assert::That(std::round(ms2scan->getRetentionTime() * std::pow(10, 2)) / std::pow(10, 2) == 12.16);
        Assert::That(ms2scan->getOneBasedPrecursorScanNumber() == 650);
        Assert::That(ms2scan->getSelectedIonMZ() == 442.67);
        auto t = dynamicThermo->ThermoGlobalParams.MsOrderByScan;
        Assert::That(t[0] == 1);
        Assert::That(t[5] == 1);
        Assert::That(t[649] == 1);
        Assert::That(t[650] == 2);
        Assert::That(!t->Where([&] (std::any v)
        {
            return v == 0;
        }).Any());
    }

    void TestThermo::TestSummedMsDataFile()
    {
        ThermoStaticData *rawFile = ThermoStaticData::LoadAllStaticData(R"(05-13-16_cali_MS_60K-res_MS.raw)");

        // 3 scans

        SummedMsDataFile *summed3 = new SummedMsDataFile(rawFile, 3, 10);

        Assert::AreEqual(rawFile->getNumSpectra() - 2, summed3->getNumSpectra());

        auto resultingTic = summed3->GetOneBasedScan(1)->getTotalIonCurrent();
        auto mySummedTic = rawFile->GetOneBasedScan(1)->MassSpectrum.SumOfAllY + rawFile->GetOneBasedScan(2)->MassSpectrum.SumOfAllY + rawFile->GetOneBasedScan(3)->MassSpectrum.SumOfAllY;
        auto instrumentSummedTic = rawFile->GetOneBasedScan(1)->getTotalIonCurrent() + rawFile->GetOneBasedScan(2)->getTotalIonCurrent() + rawFile->GetOneBasedScan(3)->getTotalIonCurrent();

        // Tics are approximately what they should be
        Assert::IsTrue(std::abs(resultingTic - mySummedTic) / mySummedTic < 1e-4);
        Assert::IsTrue(std::abs(resultingTic - instrumentSummedTic) / instrumentSummedTic < 1e-1);

        // Equal to representative
        Assert::AreEqual(summed3->GetOneBasedScan(1)->getRetentionTime(), rawFile->GetOneBasedScan(2)->getRetentionTime());

        Assert::IsTrue(summed3->GetOneBasedScan(1)->MassSpectrum.Size <= rawFile->GetOneBasedScan(1)->MassSpectrum.Size + rawFile->GetOneBasedScan(2)->MassSpectrum.Size + rawFile->GetOneBasedScan(3)->MassSpectrum.Size);
        Assert::IsTrue(summed3->GetOneBasedScan(1)->MassSpectrum.Size >= rawFile->GetOneBasedScan(1)->MassSpectrum.Size);
        Assert::IsTrue(summed3->GetOneBasedScan(1)->MassSpectrum.Size >= rawFile->GetOneBasedScan(2)->MassSpectrum.Size);
        Assert::IsTrue(summed3->GetOneBasedScan(1)->MassSpectrum.Size >= rawFile->GetOneBasedScan(3)->MassSpectrum.Size);

        Assert::IsTrue(summed3->GetOneBasedScan(1)->MassSpectrum->YofPeakWithHighestY == rawFile->GetOneBasedScan(1)->MassSpectrum.YofPeakWithHighestY + rawFile->GetOneBasedScan(2)->MassSpectrum.YofPeakWithHighestY + rawFile->GetOneBasedScan(3)->MassSpectrum.YofPeakWithHighestY);

        // Interval of 893-899 mz

        Assert::AreEqual(2, rawFile->GetOneBasedScan(1)->MassSpectrum.NumPeaksWithinRange(893, 899));
        Assert::AreEqual(2, rawFile->GetOneBasedScan(2)->MassSpectrum.NumPeaksWithinRange(893, 899));
        Assert::AreEqual(1, rawFile->GetOneBasedScan(3)->MassSpectrum.NumPeaksWithinRange(893, 899));

        // One peak persists across the three scans! So instead of 5 see three peaks in summed
        Assert::AreEqual(3, summed3->GetOneBasedScan(1)->MassSpectrum.NumPeaksWithinRange(893, 899));

        Assert::AreEqual(summed3->GetOneBasedScan(1)->MassSpectrum.FirstX, std::min(std::min(rawFile->GetOneBasedScan(1)->MassSpectrum.FirstX->Value, rawFile->GetOneBasedScan(2)->MassSpectrum.FirstX->Value), rawFile->GetOneBasedScan(3)->MassSpectrum.FirstX->Value));

        Assert::AreEqual(summed3->GetOneBasedScan(1)->MassSpectrum.LastX, std::max(std::max(rawFile->GetOneBasedScan(1)->MassSpectrum.LastX->Value, rawFile->GetOneBasedScan(2)->MassSpectrum.LastX->Value), rawFile->GetOneBasedScan(3)->MassSpectrum.LastX->Value));

        // 5 scans
        SummedMsDataFile *summed5 = new SummedMsDataFile(rawFile, 5, 10);

        Assert::AreEqual(rawFile->getNumSpectra() - 4, summed5->getNumSpectra());

        MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(summed5, "testSummed.mzML", false);

        auto ok = Mzml::LoadAllStaticData("testSummed.mzML");

        MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(ok, "testSummed2.mzML", false);

        Mzml::LoadAllStaticData("testSummed2.mzML");

//C# TO C++ CONVERTER TODO TASK: A 'delete summed5' statement was not added since summed5 was passed to a method or constructor. Handle memory management manually.
        delete summed3;
    }

    void TestThermo::WriteIndexedMzmlFromThermoTest()
    {
        auto smallThermo = ThermoStaticData::LoadAllStaticData(R"(small.raw)");
        MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(smallThermo, FileSystem::combine(TestContext::CurrentContext->TestDirectory, "Hi.mzML"), true);
        auto smallMzml = Mzml::LoadAllStaticData(R"(Hi.mzML)");
        Assert::AreEqual(smallMzml->getNumSpectra(), 48);
        Assert::AreEqual(smallMzml->GetOneBasedScan(8)->getOneBasedScanNumber(), 8);
        Assert::AreEqual(smallThermo->GetOneBasedScan(5)->getRetentionTime(), smallMzml->GetOneBasedScan(5)->getRetentionTime());
    }

    void TestThermo::Setup()
    {
        Environment::CurrentDirectory = TestContext::CurrentContext->TestDirectory;
    }
}
