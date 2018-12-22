#include "TestThermo.h"
#include "../MzLibUtil/MzLibException.h"
#include "../MzLibUtil/MzRange.h"
#include "../MassSpectrometry/Enums/Polarity.h"
#include "../MassSpectrometry/SummedMsDataFile.h"

using namespace Chemistry;
using namespace IO::MzML;
using namespace IO::Thermo;
using namespace MassSpectrometry;
using namespace MzLibUtil;
using namespace NUnit::Framework;

namespace TestThermo {

    void TestThermo::ReadWriteReadEtc() {
    {
            ThermoStaticData *a = ThermoStaticData::LoadAllStaticData(LR"(testFileWMS2.raw)");

            MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(a, L"a.mzML", false);

            auto aa = Mzml::LoadAllStaticData(L"a.mzML");

            MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(aa, L"aa.mzML", true);

            Mzml::LoadAllStaticData(L"aa.mzML");
    } {
            ThermoStaticData *a = ThermoStaticData::LoadAllStaticData(LR"(small.raw)");

            MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(a, L"a.mzML", false);

            auto aa = Mzml::LoadAllStaticData(L"a.mzML");

            MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(aa, L"aa.mzML", true);

            Mzml::LoadAllStaticData(L"aa.mzML");
        } {
            ThermoStaticData *a = ThermoStaticData::LoadAllStaticData(LR"(05-13-16_cali_MS_60K-res_MS.raw)");

            MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(a, L"a.mzML", false);

            auto aa = Mzml::LoadAllStaticData(L"a.mzML");

            MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(aa, L"aa.mzML", true);

            Mzml::LoadAllStaticData(L"aa.mzML");
        }
    }

    void TestThermo::ThermoLoadError() {
        Assert::Throws<MzLibException*>([&] () {
            ThermoStaticData::LoadAllStaticData(LR"(aaa.RAW)");
        });
    }

    void TestThermo::LoadCompressedMzml() {
        ThermoStaticData *a = ThermoStaticData::LoadAllStaticData(LR"(small.RAW)");

        Mzml *b = Mzml::LoadAllStaticData(LR"(smallCentroid.mzML)");

        Assert::AreEqual(a->getNumSpectra(), b->getNumSpectra());

        Assert::AreEqual(a->GetOneBasedScan(1)->MassSpectrum.XofPeakWithHighestY, b->GetOneBasedScan(1)->MassSpectrum.XofPeakWithHighestY, 1e-8);
        Assert::IsTrue(std::abs((a->GetOneBasedScan(1)->MassSpectrum.YofPeakWithHighestY - b->GetOneBasedScan(1)->MassSpectrum.YofPeakWithHighestY) / b->GetOneBasedScan(1)->MassSpectrum.YofPeakWithHighestY) < 1e-8);

        Assert::AreEqual(a->GetOneBasedScan(2)->MassSpectrum.XofPeakWithHighestY, b->GetOneBasedScan(2)->MassSpectrum.XofPeakWithHighestY, 1e-8);
        Assert::IsTrue(std::abs((a->GetOneBasedScan(2)->MassSpectrum.YofPeakWithHighestY - b->GetOneBasedScan(2)->MassSpectrum.YofPeakWithHighestY) / b->GetOneBasedScan(1)->MassSpectrum.YofPeakWithHighestY) < 1e-8);

        Assert::AreEqual(a->GetOneBasedScan(3)->MassSpectrum.XofPeakWithHighestY, b->GetOneBasedScan(3)->MassSpectrum.XofPeakWithHighestY, 1e-8);
        Assert::IsTrue(std::abs((a->GetOneBasedScan(3)->MassSpectrum.YofPeakWithHighestY - b->GetOneBasedScan(3)->MassSpectrum.YofPeakWithHighestY) / b->GetOneBasedScan(1)->MassSpectrum.YofPeakWithHighestY) < 1e-8);
    }

    void TestThermo::LoadThermoTest2() {
        ThermoStaticData *a = ThermoStaticData::LoadAllStaticData(LR"(05-13-16_cali_MS_60K-res_MS.raw)");
        Assert::AreEqual(360, a->getNumSpectra());
        Assert::GreaterOrEqual(1000, a->GetOneBasedScan(1)->MassSpectrum.Extract(0, 500).Last().X);
        Assert::AreEqual(2, a->GetOneBasedScan(1)->MassSpectrum.FilterByY(5e6, std::numeric_limits<double>::max())->Count());
        auto ye = a->GetOneBasedScan(1)->MassSpectrum.CopyTo2DArray();
        Assert::AreEqual(77561752, a->GetOneBasedScan(1)->TotalIonCurrent);
        Assert::AreEqual(144, a->GetClosestOneBasedSpectrumNumber(2));

        auto newSpectrum = new ThermoSpectrum(a->GetOneBasedScan(51)->MassSpectrum);

        Assert::AreEqual(1120, a->GetOneBasedScan(1)->MassSpectrum.Size);

        MzRange tempVar(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max());
        auto newDeconvolution = a->GetOneBasedScan(1)->MassSpectrum.Deconvolute(&tempVar, 10, 1, 4).ToList();

        Assert::IsTrue(newDeconvolution->Any([&] (std::any b) {
        delete newSpectrum;
            return std::abs(b::peaks::First().Item1->ToMass(b::charge) - 523.257) < 0.001;
        }));

        MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(a, FileSystem::combine(TestContext::CurrentContext->TestDirectory, L"convertedThermo.mzML"), false);

        auto sdafaf = a->Deconvolute(std::nullopt, std::nullopt, 30, 10, 3, 10, [&] (std::any b) {
            true;
        }).OrderByDescending([&] (std::any b) {
            b::NumPeaks;
        }).First();

        Assert::IsTrue(std::abs(262.64 - sdafaf->Mass.ToMz(2)) <= 0.01);

//C# TO C++ CONVERTER NOTE: The following 'using' block is replaced by its C++ equivalent:
//ORIGINAL LINE: using (ThermoDynamicData dynamicThermo = ThermoDynamicData.InitiateDynamicConnection("TangibleTempVerbatimOpenTag05-13-16_cali_MS_60K-res_MS.rawTangibleTempVerbatimCloseTag"))
        {
            ThermoDynamicData dynamicThermo = ThermoDynamicData::InitiateDynamicConnection(LR"(05-13-16_cali_MS_60K-res_MS.raw)");
            Assert::AreEqual(136, dynamicThermo->GetClosestOneBasedSpectrumNumber(1.89));
            dynamicThermo->ClearCachedScans();
        }

        Mzml *readCovertedMzmlFile = Mzml::LoadAllStaticData(FileSystem::combine(TestContext::CurrentContext->TestDirectory, L"convertedThermo.mzML"));

        Assert::AreEqual(a->front().Polarity, readCovertedMzmlFile->front().Polarity);

        delete newSpectrum;
    }

    void TestThermo::LoadThermoFiltered() {
        ThermoStaticData *a = ThermoStaticData::LoadAllStaticData(LR"(05-13-16_cali_MS_60K-res_MS.raw)");
        ThermoStaticData *b = ThermoStaticData::LoadAllStaticData(LR"(05-13-16_cali_MS_60K-res_MS.raw)", std::make_optional(400), , true);
        ThermoStaticData *c = ThermoStaticData::LoadAllStaticData(LR"(05-13-16_cali_MS_60K-res_MS.raw)", , std::make_optional(0.001), true);
        ThermoStaticData *d = ThermoStaticData::LoadAllStaticData(LR"(05-13-16_cali_MS_60K-res_MS.raw)", std::make_optional(400), std::make_optional(0.001), true);

        auto aLen = a->GetOneBasedScan(1)->MassSpectrum.Size;
        auto bLen = b->GetOneBasedScan(1)->MassSpectrum.Size;
        auto cLen = c->GetOneBasedScan(1)->MassSpectrum.Size;
        auto dLen = d->GetOneBasedScan(1)->MassSpectrum.Size;

        Assert::AreEqual(std::min(bLen, cLen), dLen);
    }

    void TestThermo::LoadThermoFiltered2() {
        ThermoStaticData *a = ThermoStaticData::LoadAllStaticData(LR"(small.raw)");
        ThermoStaticData *b = ThermoStaticData::LoadAllStaticData(LR"(small.raw)", std::make_optional(40), , true, true);
        ThermoStaticData *c = ThermoStaticData::LoadAllStaticData(LR"(small.raw)", , std::make_optional(0.1), true, true);
        ThermoStaticData *d = ThermoStaticData::LoadAllStaticData(LR"(small.raw)", std::make_optional(40), std::make_optional(0.1), true, true);

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

    void TestThermo::LoadThermoTest3() {
        ThermoStaticData *a = ThermoStaticData::LoadAllStaticData(LR"(small.RAW)");

        Assert::IsTrue(a->Where([&] (std::any eb) {
            return eb::MsnOrder > 1;
        })->Count() > 0);

        Assert::IsTrue(a->Where([&] (std::any eb) {
            return eb->MsnOrder == 1;
        })->Count() > 0);

        Assert::IsFalse(a->getThermoGlobalParams()->getMonoisotopicselectionEnabled());

        auto hehe = dynamic_cast<ThermoScanWithPrecursor*>(a->First([&] (std::any b) {
            return b::MsnOrder > 1;
        }));

        auto prec = a->GetOneBasedScan(hehe->getOneBasedPrecursorScanNumber().Value);

        Assert::IsNull(hehe->getSelectedIonChargeStateGuess());

        Assert::IsNull(hehe->getSelectedIonIntensity());

        hehe->ComputeSelectedPeakIntensity(prec->MassSpectrum);

        Assert::AreEqual(1017759, hehe->getSelectedIonIntensity(), 1);

        Assert::IsNull(hehe->getSelectedIonMonoisotopicGuessIntensity());

        hehe->ComputeMonoisotopicPeakIntensity(prec->MassSpectrum);

        Assert::AreEqual(1017759, hehe->getSelectedIonMonoisotopicGuessIntensity(), 1);
    }

    void TestThermo::ThermoSpectrumTest() {
        std::vector<double> mz = {1};
        std::vector<double> intensity = {1};
        ThermoSpectrum *s1 = new ThermoSpectrum(mz, intensity, false);
        ThermoSpectrum *s2 = new ThermoSpectrum(mz, intensity, false);
        s1->ReplaceXbyApplyingFunction([&] (a) {
            4;
        });
        Assert::AreEqual(4, s2->getXArray()[0]);

        delete s2;
        delete s1;
    }

    void TestThermo::ThermoDynamicTest() {
        ThermoDynamicData *dynamicThermo = ThermoDynamicData::InitiateDynamicConnection(LR"(testFileWMS2.raw)");
        auto ms1scan = dynamicThermo->GetOneBasedScan(1);
        ThermoScanWithPrecursor *ms2scan = dynamic_cast<ThermoScanWithPrecursor*>(dynamicThermo->GetOneBasedScan(651));
        Assert::That(ms1scan->OneBasedScanNumber == 1);
        Assert::That(ms2scan->getOneBasedScanNumber() == 651);
        Assert::That(std::round(ms2scan->getRetentionTime() * std::pow(10, 2)) / std::pow(10, 2) == 12.16);
        Assert::That(ms2scan->getOneBasedPrecursorScanNumber() == 650);
        Assert::That(ms2scan->getSelectedIonMZ() == 442.67);
        auto t = dynamicThermo->getThermoGlobalParams()->msOrderByScan;
        Assert::That(t[0] == 1);
        Assert::That(t[5] == 1);
        Assert::That(t[649] == 1);
        Assert::That(t[650] == 2);
        Assert::That(!t.Where([&] (std::any v) {
            return v == 0;
        }).Any());
    }

    void TestThermo::TestSummedMsDataFile() {
        ThermoStaticData *rawFile = ThermoStaticData::LoadAllStaticData(LR"(05-13-16_cali_MS_60K-res_MS.raw)");

        // 3 scans

        SummedMsDataFile *summed3 = new SummedMsDataFile(rawFile, 3, 10);

        Assert::AreEqual(rawFile->getNumSpectra() - 2, summed3->getNumSpectra());

        auto resultingTic = summed3->GetOneBasedScan(1)->getTotalIonCurrent();
        auto mySummedTic = rawFile->GetOneBasedScan(1)->MassSpectrum.SumOfAllY + rawFile->GetOneBasedScan(2)->MassSpectrum.SumOfAllY + rawFile->GetOneBasedScan(3)->MassSpectrum.SumOfAllY;
        auto instrumentSummedTic = rawFile->GetOneBasedScan(1)->TotalIonCurrent + rawFile->GetOneBasedScan(2)->TotalIonCurrent + rawFile->GetOneBasedScan(3)->TotalIonCurrent;

        // Tics are approximately what they should be
        Assert::IsTrue(std::abs(resultingTic - mySummedTic) / mySummedTic < 1e-4);
        Assert::IsTrue(std::abs(resultingTic - instrumentSummedTic) / instrumentSummedTic < 1e-1);

        // Equal to representative
        Assert::AreEqual(summed3->GetOneBasedScan(1)->getRetentionTime(), rawFile->GetOneBasedScan(2)->RetentionTime);

        Assert::IsTrue(summed3->GetOneBasedScan(1)->getMassSpectrum()->Size <= rawFile->GetOneBasedScan(1)->MassSpectrum.Size + rawFile->GetOneBasedScan(2)->MassSpectrum.Size + rawFile->GetOneBasedScan(3)->MassSpectrum.Size);
        Assert::IsTrue(summed3->GetOneBasedScan(1)->getMassSpectrum()->Size >= rawFile->GetOneBasedScan(1)->MassSpectrum.Size);
        Assert::IsTrue(summed3->GetOneBasedScan(1)->getMassSpectrum()->Size >= rawFile->GetOneBasedScan(2)->MassSpectrum.Size);
        Assert::IsTrue(summed3->GetOneBasedScan(1)->getMassSpectrum()->Size >= rawFile->GetOneBasedScan(3)->MassSpectrum.Size);

        Assert::IsTrue(summed3->GetOneBasedScan(1)->getMassSpectrum()->YofPeakWithHighestY == rawFile->GetOneBasedScan(1)->MassSpectrum.YofPeakWithHighestY + rawFile->GetOneBasedScan(2)->MassSpectrum.YofPeakWithHighestY + rawFile->GetOneBasedScan(3)->MassSpectrum.YofPeakWithHighestY);

        // Interval of 893-899 mz

        Assert::AreEqual(2, rawFile->GetOneBasedScan(1)->MassSpectrum.NumPeaksWithinRange(893, 899));
        Assert::AreEqual(2, rawFile->GetOneBasedScan(2)->MassSpectrum.NumPeaksWithinRange(893, 899));
        Assert::AreEqual(1, rawFile->GetOneBasedScan(3)->MassSpectrum.NumPeaksWithinRange(893, 899));

        // One peak persists across the three scans! So instead of 5 see three peaks in summed
        Assert::AreEqual(3, summed3->GetOneBasedScan(1)->getMassSpectrum()->NumPeaksWithinRange(893, 899));

        Assert::AreEqual(summed3->GetOneBasedScan(1)->getMassSpectrum()->FirstX, std::min(std::min(rawFile->GetOneBasedScan(1)->MassSpectrum.FirstX, rawFile->GetOneBasedScan(2)->MassSpectrum.FirstX), rawFile->GetOneBasedScan(3)->MassSpectrum.FirstX));

        Assert::AreEqual(summed3->GetOneBasedScan(1)->getMassSpectrum()->LastX, std::max(std::max(rawFile->GetOneBasedScan(1)->MassSpectrum.LastX, rawFile->GetOneBasedScan(2)->MassSpectrum.LastX), rawFile->GetOneBasedScan(3)->MassSpectrum.LastX));

        // 5 scans
        SummedMsDataFile *summed5 = new SummedMsDataFile(rawFile, 5, 10);

        Assert::AreEqual(rawFile->getNumSpectra() - 4, summed5->getNumSpectra());

        MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(summed5, L"testSummed.mzML", false);

        auto ok = Mzml::LoadAllStaticData(L"testSummed.mzML");

        MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(ok, L"testSummed2.mzML", false);

        Mzml::LoadAllStaticData(L"testSummed2.mzML");

//C# TO C++ CONVERTER TODO TASK: A 'delete summed5' statement was not added since summed5 was passed to a method or constructor. Handle memory management manually.
        delete summed3;
    }

    void TestThermo::WriteIndexedMzmlFromThermoTest() {
        auto smallThermo = ThermoStaticData::LoadAllStaticData(LR"(small.raw)");
        MzmlMethods::CreateAndWriteMyMzmlWithCalibratedSpectra(smallThermo, FileSystem::combine(TestContext::CurrentContext->TestDirectory, L"Hi.mzML"), true);
        auto smallMzml = Mzml::LoadAllStaticData(LR"(hi.mzML)");
        Assert::AreEqual(smallMzml->getNumSpectra(), 48);
        Assert::AreEqual(smallMzml->GetOneBasedScan(8)->OneBasedScanNumber, 8);
        Assert::AreEqual(smallThermo->GetOneBasedScan(5)->RetentionTime, smallMzml->GetOneBasedScan(5)->RetentionTime);
    }

    void TestThermo::Setup() {
        Environment::CurrentDirectory = TestContext::CurrentContext->TestDirectory;
    }
}
