#include "TestIsolation.h"
#include "../UsefulProteomicsDatabases/Loaders.h"
#include "../Chemistry/IsotopicDistribution.h"
#include "../MassSpectrometry/MsDataScan.h"
#include "../MassSpectrometry/MzSpectra/MzSpectrum.h"
#include "../MassSpectrometry/Enums/MzAnalyzerType.h"
#include "../MassSpectrometry/Enums/Polarity.h"
#include "../MzLibUtil/MzRange.h"
#include "../MassSpectrometry/Enums/DissociationType.h"
#include "FakeMsDataFile.h"
#include "../MzLibUtil/Tolerance.h"

using namespace Chemistry;
using namespace MassSpectrometry;
using namespace MzLibUtil;
using namespace NUnit::Framework;
using namespace Proteomics::AminoAcidPolymer;
namespace Stopwatch = System::Diagnostics::Stopwatch;

namespace Test
{

System::Diagnostics::Stopwatch *TestIsolation::privateStopwatch;

    Stopwatch *TestIsolation::getStopwatch()
    {
        return privateStopwatch;
    }

    void TestIsolation::setStopwatch(Stopwatch *value)
    {
        privateStopwatch = value;
    }

    void TestIsolation::Setup()
    {
        Environment::CurrentDirectory = TestContext::CurrentContext->TestDirectory;

        UsefulProteomicsDatabases::Loaders::LoadElements(R"(elements.dat)");
    }

    void TestIsolation::Setuppp()
    {
        Stopwatch tempVar();
        setStopwatch(&tempVar);
        getStopwatch()->Start();
    }

    void TestIsolation::TearDown()
    {
        std::cout << StringHelper::formatSimple("Analysis time: {0}h {1}m {2}s", getStopwatch()->Elapsed.Hours, getStopwatch()->Elapsed.Minutes, getStopwatch()->Elapsed.Seconds) << std::endl;
    }

    void TestIsolation::TestCoIsolation()
    {
        Peptide *pep1 = new Peptide("AAAAAA");
        Peptide *pep2 = new Peptide("AAA[H]AAA");

        auto dist1 = IsotopicDistribution::GetDistribution(pep1->GetChemicalFormula(), 0.1, 0.01);

        auto dist2 = IsotopicDistribution::GetDistribution(pep2->GetChemicalFormula(), 0.1, 0.01);

        std::vector<MsDataScan*> Scans(2);
        std::vector<double> ms1intensities = {0.8, 0.8, 0.2, 0.02, 0.2, 0.02};
        std::vector<double> ms1mzs = dist1->getMasses().Concat(dist2->getMasses())->OrderBy([&] (std::any b)
        {
        delete pep2;
        delete pep1;
            return b;
        })->Select([&] (std::any b)
        {
            b::ToMz(1);
        })->ToArray();

        double selectedIonMz = ms1mzs[1];

        MzSpectrum *MS1 = new MzSpectrum(ms1mzs, ms1intensities, false);

        MzRange tempVar(300, 2000);
        Scans[0] = new MsDataScan(MS1, 1, 1, false, Polarity::Positive, 1.0, &tempVar, "first spectrum", MZAnalyzerType::Unknown, MS1->getSumOfAllY(), std::nullopt, std::vector<std::vector<double>>(), "");

        // Horrible fragmentation, but we don't care about this!
        std::vector<double> ms2intensities = {1000};
        std::vector<double> ms2mzs = {1000};
        MzSpectrum *MS2 = new MzSpectrum(ms2mzs, ms2intensities, false);
        double isolationMZ = selectedIonMz;
        MzRange tempVar2(100, 1500);
        Scans[1] = new MsDataScan(MS2, 2, 2, false, Polarity::Positive, 2.0, &tempVar2, "second spectrum", MZAnalyzerType::Unknown, MS2->getSumOfAllY(), std::nullopt, std::vector<std::vector<double>>(), "", std::make_optional(selectedIonMz), std::nullopt, std::nullopt, std::make_optional(isolationMZ), std::make_optional(2.5), std::make_optional(DissociationType::HCD), std::make_optional(1), std::nullopt);

        auto myMsDataFile = new FakeMsDataFile(Scans);

        auto cool = myMsDataFile->GetAllScansList().back();

        int maxAssumedChargeState = 1;
        Tolerance *massTolerance = Tolerance::ParseToleranceString("10 PPM");

        auto isolatedMasses = cool->GetIsolatedMassesAndCharges(myMsDataFile->GetOneBasedScan(cool->OneBasedPrecursorScanNumber->Value)->MassSpectrum, 1, maxAssumedChargeState, 10, 5).ToList();

        Assert::AreEqual(2, isolatedMasses->Count);
        Assert::AreEqual(2, isolatedMasses->Count([&] (std::any b)
        {
        delete myMsDataFile;
//C# TO C++ CONVERTER TODO TASK: A 'delete MS2' statement was not added since MS2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete MS1' statement was not added since MS1 was passed to a method or constructor. Handle memory management manually.
        delete pep2;
        delete pep1;
            return b->charge == 1;
        }));
        Assert::AreEqual(pep1->getMonoisotopicMass(), isolatedMasses->Select([&] (std::any b)
        {
            b::peaks::First().Item1->ToMass(b::charge);
        }).Min(), 1e-9);
        Assert::AreEqual(pep2->getMonoisotopicMass(), isolatedMasses->Select([&] (std::any b)
        {
            b::peaks::First().Item1->ToMass(b::charge);
        }).Max(), 1e-9);
        Assert::AreEqual(pep1->getMonoisotopicMass(), isolatedMasses->Select([&] (std::any b)
        {
            b::monoisotopicMass::ToMz(b::charge).ToMass(b::charge);
        }).Min(), 1e-9);
        Assert::AreEqual(pep2->getMonoisotopicMass(), isolatedMasses->Select([&] (std::any b)
        {
            b::monoisotopicMass::ToMz(b::charge).ToMass(b::charge);
        }).Max(), 1e-9);

        delete myMsDataFile;
//C# TO C++ CONVERTER TODO TASK: A 'delete MS2' statement was not added since MS2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete MS1' statement was not added since MS1 was passed to a method or constructor. Handle memory management manually.
        delete pep2;
        delete pep1;
    }

    void TestIsolation::TestCoIsolationDifferentCharges()
    {
        Peptide *pep1 = new Peptide("AAAAAA");
        Peptide *pep2 = new Peptide("AAAAAAA[H21]AAAAA");

        auto dist1 = IsotopicDistribution::GetDistribution(pep1->GetChemicalFormula(), 0.1, 0.01);

        auto dist2 = IsotopicDistribution::GetDistribution(pep2->GetChemicalFormula(), 0.1, 0.01);

        std::vector<MsDataScan*> Scans(2);
        std::vector<double> ms1intensities = {0.8, 0.8, 0.2, 0.02, 0.2, 0.02};
        std::vector<double> ms1mzs = dist1->getMasses().Select([&] (std::any b)
        {
            b::ToMz(1);
        }).Concat(dist2->getMasses().Select([&] (std::any b)
        {
            b::ToMz(2);
        }))->OrderBy([&] (std::any b)
        {
        delete pep2;
        delete pep1;
            return b;
        })->ToArray();

        double selectedIonMz = ms1mzs[1];

        MzSpectrum *MS1 = new MzSpectrum(ms1mzs, ms1intensities, false);

        MzRange tempVar(300, 2000);
        Scans[0] = new MsDataScan(MS1, 1, 1, false, Polarity::Positive, 1.0, &tempVar, "first spectrum", MZAnalyzerType::Unknown, MS1->getSumOfAllY(), std::nullopt, std::vector<std::vector<double>>(), "");

        // Horrible fragmentation, but we don't care about this!
        std::vector<double> ms2intensities = {1000};
        std::vector<double> ms2mzs = {1000};
        MzSpectrum *MS2 = new MzSpectrum(ms2mzs, ms2intensities, false);
        double isolationMZ = selectedIonMz;

        MzRange tempVar2(100, 1500);
        Scans[1] = new MsDataScan(MS2, 2, 2, false, Polarity::Positive, 2.0, &tempVar2, "second spectrum", MZAnalyzerType::Unknown, MS2->getSumOfAllY(), std::nullopt, std::vector<std::vector<double>>(), "", std::make_optional(selectedIonMz), std::nullopt, std::nullopt, std::make_optional(isolationMZ), std::make_optional(2.5), std::make_optional(DissociationType::HCD), std::make_optional(1), std::nullopt);

        auto myMsDataFile = new FakeMsDataFile(Scans);

        auto cool = myMsDataFile->GetAllScansList().back();

        int maxAssumedChargeState = 2;
        Tolerance *massTolerance = Tolerance::ParseToleranceString("10 PPM");

        auto isolatedMasses = cool->GetIsolatedMassesAndCharges(myMsDataFile->GetOneBasedScan(cool->OneBasedPrecursorScanNumber->Value)->MassSpectrum, 1, maxAssumedChargeState, 10, 5).ToList();

        Assert::AreEqual(2, isolatedMasses->Count);
        Assert::AreEqual(1, isolatedMasses->Count([&] (std::any b)
        {
        delete myMsDataFile;
//C# TO C++ CONVERTER TODO TASK: A 'delete MS2' statement was not added since MS2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete MS1' statement was not added since MS1 was passed to a method or constructor. Handle memory management manually.
        delete pep2;
        delete pep1;
            return b->charge == 1;
        }));
        Assert::AreEqual(1, isolatedMasses->Count([&] (std::any b)
        {
        delete myMsDataFile;
//C# TO C++ CONVERTER TODO TASK: A 'delete MS2' statement was not added since MS2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete MS1' statement was not added since MS1 was passed to a method or constructor. Handle memory management manually.
        delete pep2;
        delete pep1;
            return b->charge == 2;
        }));
        Assert::AreEqual(pep1->getMonoisotopicMass(), isolatedMasses->Select([&] (std::any b)
        {
            b::peaks::First().Item1->ToMass(b::charge);
        }).Min(), 1e-9);
        Assert::AreEqual(pep2->getMonoisotopicMass(), isolatedMasses->Select([&] (std::any b)
        {
            b::peaks::First().Item1->ToMass(b::charge);
        }).Max(), 1e-9);

        delete myMsDataFile;
//C# TO C++ CONVERTER TODO TASK: A 'delete MS2' statement was not added since MS2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete MS1' statement was not added since MS1 was passed to a method or constructor. Handle memory management manually.
        delete pep2;
        delete pep1;
    }
}
