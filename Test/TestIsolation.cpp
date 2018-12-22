#include "TestIsolation.h"
#include "../UsefulProteomicsDatabases/Loaders.h"
#include "../Proteomics/Peptide.h"
#include "../Chemistry/IsotopicDistribution.h"
#include "../MassSpectrometry/Enums/MzAnalyzerType.h"
#include "../MassSpectrometry/Enums/Polarity.h"
#include "../MzLibUtil/MzRange.h"
#include "../MassSpectrometry/Enums/DissociationType.h"
#include "FakeMsDataFile.h"
#include "../MassSpectrometry/DataScan/IMsDataScanWithPrecursor.h"
#include "../MzLibUtil/Tolerance.h"

using namespace Chemistry;
using namespace IO::MzML;
using namespace MassSpectrometry;
using namespace MzLibUtil;
using namespace NUnit::Framework;
using namespace Proteomics;

namespace Test {

    void TestIsolation::Setup() {
        Environment::CurrentDirectory = TestContext::CurrentContext->TestDirectory;

        UsefulProteomicsDatabases::Loaders::LoadElements(LR"(elements.dat)");
    }

    void TestIsolation::TestCoIsolation() {
        Peptide *pep1 = new Peptide(L"AAAAAA");
        Peptide *pep2 = new Peptide(L"AAA[H]AAA");

        auto dist1 = IsotopicDistribution::GetDistribution(pep1->GetChemicalFormula(), 0.1, 0.01);

        auto dist2 = IsotopicDistribution::GetDistribution(pep2->GetChemicalFormula(), 0.1, 0.01);

        std::vector<IMzmlScan*> Scans(2);
        std::vector<double> ms1intensities = {0.8, 0.8, 0.2, 0.02, 0.2, 0.02};
        std::vector<double> ms1mzs = dist1->getMasses().Concat(dist2->getMasses())->OrderBy([&] (std::any b) {
        delete pep2;
        delete pep1;
            return b;
        })->Select([&] (std::any b) {
            b::ToMz(1);
        })->ToArray();

        double selectedIonMz = ms1mzs[1];

        MzmlMzSpectrum *MS1 = new MzmlMzSpectrum(ms1mzs, ms1intensities, false);

        MzRange tempVar(300, 2000);
        Scans[0] = new MzmlScan(1, MS1, 1, false, Polarity::Positive, 1.0, &tempVar, L"first spectrum", MZAnalyzerType::Unknown, MS1->getSumOfAllY(), std::nullopt, L"");

        // Horrible fragmentation, but we don't care about this!
        std::vector<double> ms2intensities = {1000};
        std::vector<double> ms2mzs = {1000};
        MzmlMzSpectrum *MS2 = new MzmlMzSpectrum(ms2mzs, ms2intensities, false);
        double isolationMZ = selectedIonMz;
        MzRange tempVar2(100, 1500);
        Scans[1] = new MzmlScanWithPrecursor(2, MS2, 2, false, Polarity::Positive, 2.0, &tempVar2, L"second spectrum", MZAnalyzerType::Unknown, MS2->getSumOfAllY(), selectedIonMz, std::nullopt, std::nullopt, std::make_optional(isolationMZ), std::make_optional(2.5), DissociationType::HCD, std::make_optional(1), std::nullopt, std::nullopt, L"");

        auto myMsDataFile = new FakeMsDataFile(Scans);

        auto cool = dynamic_cast<IMsDataScanWithPrecursor<MzmlMzSpectrum*>*>(myMsDataFile->back());

        int maxAssumedChargeState = 1;
        Tolerance *massTolerance = Tolerance::ParseToleranceString(L"10 PPM");

        auto isolatedMasses = cool->GetIsolatedMassesAndCharges(myMsDataFile->GetOneBasedScan(cool->getOneBasedPrecursorScanNumber().Value)->MassSpectrum, maxAssumedChargeState, 10, 5).ToList();

        Assert::AreEqual(2, isolatedMasses->Count);
        Assert::AreEqual(2, isolatedMasses->Count([&] (std::any b) {
        delete myMsDataFile;
//C# TO C++ CONVERTER TODO TASK: A 'delete MS2' statement was not added since MS2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete MS1' statement was not added since MS1 was passed to a method or constructor. Handle memory management manually.
        delete pep2;
        delete pep1;
            return b->charge == 1;
        }));
        Assert::AreEqual(pep1->getMonoisotopicMass(), isolatedMasses->Select([&] (std::any b) {
            b::peaks::First().Item1->ToMass(b::charge);
        }).Min(), 1e-9);
        Assert::AreEqual(pep2->getMonoisotopicMass(), isolatedMasses->Select([&] (std::any b) {
            b::peaks::First().Item1->ToMass(b::charge);
        }).Max(), 1e-9);

        delete myMsDataFile;
//C# TO C++ CONVERTER TODO TASK: A 'delete MS2' statement was not added since MS2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete MS1' statement was not added since MS1 was passed to a method or constructor. Handle memory management manually.
        delete pep2;
        delete pep1;
    }

    void TestIsolation::TestCoIsolationDifferentCharges() {
        Peptide *pep1 = new Peptide(L"AAAAAA");
        Peptide *pep2 = new Peptide(L"AAAAAAA[H21]AAAAA");

        auto dist1 = IsotopicDistribution::GetDistribution(pep1->GetChemicalFormula(), 0.1, 0.01);

        auto dist2 = IsotopicDistribution::GetDistribution(pep2->GetChemicalFormula(), 0.1, 0.01);

        std::vector<IMzmlScan*> Scans(2);
        std::vector<double> ms1intensities = {0.8, 0.8, 0.2, 0.02, 0.2, 0.02};
        std::vector<double> ms1mzs = dist1->getMasses().Select([&] (std::any b) {
            b::ToMz(1);
        }).Concat(dist2->getMasses().Select([&] (std::any b) {
            b::ToMz(2);
        }))->OrderBy([&] (std::any b) {
        delete pep2;
        delete pep1;
            return b;
        })->ToArray();

        double selectedIonMz = ms1mzs[1];

        MzmlMzSpectrum *MS1 = new MzmlMzSpectrum(ms1mzs, ms1intensities, false);

        MzRange tempVar(300, 2000);
        Scans[0] = new MzmlScan(1, MS1, 1, false, Polarity::Positive, 1.0, &tempVar, L"first spectrum", MZAnalyzerType::Unknown, MS1->getSumOfAllY(), std::nullopt, L"");

        // Horrible fragmentation, but we don't care about this!
        std::vector<double> ms2intensities = {1000};
        std::vector<double> ms2mzs = {1000};
        MzmlMzSpectrum *MS2 = new MzmlMzSpectrum(ms2mzs, ms2intensities, false);
        double isolationMZ = selectedIonMz;
        MzRange tempVar2(100, 1500);
        Scans[1] = new MzmlScanWithPrecursor(2, MS2, 2, false, Polarity::Positive, 2.0, &tempVar2, L"second spectrum", MZAnalyzerType::Unknown, MS2->getSumOfAllY(), selectedIonMz, std::nullopt, std::nullopt, std::make_optional(isolationMZ), std::make_optional(2.5), DissociationType::HCD, std::make_optional(1), std::nullopt, std::nullopt, L"");

        auto myMsDataFile = new FakeMsDataFile(Scans);

        auto cool = dynamic_cast<IMsDataScanWithPrecursor<MzmlMzSpectrum*>*>(myMsDataFile->back());

        int maxAssumedChargeState = 2;
        Tolerance *massTolerance = Tolerance::ParseToleranceString(L"10 PPM");

        auto isolatedMasses = cool->GetIsolatedMassesAndCharges(myMsDataFile->GetOneBasedScan(cool->getOneBasedPrecursorScanNumber().Value)->MassSpectrum, maxAssumedChargeState, 10, 5).ToList();

        Assert::AreEqual(2, isolatedMasses->Count);
        Assert::AreEqual(1, isolatedMasses->Count([&] (std::any b) {
        delete myMsDataFile;
//C# TO C++ CONVERTER TODO TASK: A 'delete MS2' statement was not added since MS2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete MS1' statement was not added since MS1 was passed to a method or constructor. Handle memory management manually.
        delete pep2;
        delete pep1;
            return b->charge == 1;
        }));
        Assert::AreEqual(1, isolatedMasses->Count([&] (std::any b) {
        delete myMsDataFile;
//C# TO C++ CONVERTER TODO TASK: A 'delete MS2' statement was not added since MS2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete MS1' statement was not added since MS1 was passed to a method or constructor. Handle memory management manually.
        delete pep2;
        delete pep1;
            return b->charge == 2;
        }));
        Assert::AreEqual(pep1->getMonoisotopicMass(), isolatedMasses->Select([&] (std::any b) {
            b::peaks::First().Item1->ToMass(b::charge);
        }).Min(), 1e-9);
        Assert::AreEqual(pep2->getMonoisotopicMass(), isolatedMasses->Select([&] (std::any b) {
            b::peaks::First().Item1->ToMass(b::charge);
        }).Max(), 1e-9);

        delete myMsDataFile;
//C# TO C++ CONVERTER TODO TASK: A 'delete MS2' statement was not added since MS2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete MS1' statement was not added since MS1 was passed to a method or constructor. Handle memory management manually.
        delete pep2;
        delete pep1;
    }
}
