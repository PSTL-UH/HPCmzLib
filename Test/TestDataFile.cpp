#include "TestDataFile.h"
#include "FakeMsDataFile.h"
#include "../UsefulProteomicsDatabases/Loaders.h"
#include "../Proteomics/Peptide.h"
#include "../Proteomics/FragmentTypes.h"
#include "../MassSpectrometry/Enums/MzAnalyzerType.h"
#include "../MassSpectrometry/Enums/Polarity.h"
#include "../MzLibUtil/MzRange.h"
#include "../MassSpectrometry/Enums/DissociationType.h"
#include "../MassSpectrometry/DataScan/IMsDataScanWithPrecursor.h"
#include "../MassSpectrometry/MzSpectra/IMzPeak.h"
#include "../MassSpectrometry/MzSpectra/IMzSpectrum.h"
#include "../MassSpectrometry/DataScan/IMsDataScan.h"
#include "../Proteomics/Fragment.h"
#include "../Chemistry/ChemicalFormula.h"
#include "../Chemistry/IsotopicDistribution.h"

using namespace Chemistry;
using namespace IO::MzML;
using namespace MassSpectrometry;
using namespace MzLibUtil;
using namespace NUnit::Framework;
using namespace Proteomics;

namespace Test {

    void TestDataFile::Setup() {
        Environment::CurrentDirectory = TestContext::CurrentContext->TestDirectory;

        UsefulProteomicsDatabases::Loaders::LoadElements(LR"(elements.dat)");

        std::vector<double> mz = {328.73795, 329.23935, 447.73849, 448.23987, 482.23792, 482.57089, 482.90393, 500.95358, 501.28732, 501.62131, 611.99377, 612.32806, 612.66187, 722.85217, 723.35345};
        std::vector<double> intensities = {81007096.0, 28604418.0, 78353512.0, 39291696.0, 122781408.0, 94147520.0, 44238040.0, 71198680.0, 54184096.0, 21975364.0, 44514172.0, 43061628.0, 23599424.0, 56022696.0, 41019144.0};

        _mzSpectrumA = new MzmlMzSpectrum(mz, intensities, false);

        auto peptide = new Peptide(L"KQEEQMETEQQNKDEGK");

        MzmlMzSpectrum *MS1 = CreateSpectrum(peptide->GetChemicalFormula(), 300, 2000, 1);
        MzmlMzSpectrum *MS2 = CreateMS2spectrum(peptide->Fragment(FragmentTypes::b | FragmentTypes::y, true), 100, 1500);

        std::vector<IMzmlScan*> Scans(2);
        MzRange tempVar(300, 2000);
        Scans[0] = new MzmlScan(1, MS1, 1, false, Polarity::Positive, 1.0, &tempVar, L"first spectrum", MZAnalyzerType::Unknown, MS1->getSumOfAllY(), std::make_optional(1), L"scan=1");

        MzRange tempVar2(100, 1500);
        Scans[1] = new MzmlScanWithPrecursor(2, MS2, 2, false, Polarity::Positive, 2.0, &tempVar2, L"second spectrum", MZAnalyzerType::Unknown, MS2->getSumOfAllY(), 693.9892, std::make_optional(3), std::make_optional(.3872), std::make_optional(693.99), std::make_optional(1), DissociationType::Unknown, std::make_optional(1), std::make_optional(693.6550), std::make_optional(1), L"scan=2");

        myMsDataFile = new FakeMsDataFile(Scans);

        delete peptide;
    }

    void TestDataFile::SpectrumCount() {
        Assert::AreEqual(15, _mzSpectrumA->getSize());
    }

    void TestDataFile::SpectrumFirstMZ() {
        Assert::AreEqual(328.73795, _mzSpectrumA->getFirstX());
    }

    void TestDataFile::SpectrumLastMZ() {
        Assert::AreEqual(723.35345, _mzSpectrumA->getLastX());
    }

    void TestDataFile::DataFileTest() {
        MzRange tempVar(300, 1000);
        MzmlScan *theSpectrum = new MzmlScan(1, _mzSpectrumA, 1, true, Polarity::Positive, 1, &tempVar, L"fake scan filter", MZAnalyzerType::Unknown, _mzSpectrumA->getSumOfAllY(), std::make_optional(1), L"scan=1");

        std::vector<MzmlScan*> theList(1);

        theList[0] = theSpectrum;

        FakeMsDataFile *thefile = new FakeMsDataFile(theList);

        auto theOneBasedScan = thefile->GetOneBasedScan(1);

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
        Assert::AreEqual(L"Scan #1", theOneBasedScan->ToString());

        Assert::AreEqual(15, theOneBasedScan->MassSpectrum.Size);
        Assert::AreEqual(15, theOneBasedScan->MassSpectrum.Size);

        Assert::AreEqual(1, thefile->getNumSpectra());
        Assert::AreEqual(1, thefile->getNumSpectra());

        Assert::IsTrue(thefile->GetOneBasedScan(1)->IsCentroid);

        for (auto ok : thefile) {
            Assert::AreEqual(300, ok->ScanWindowRange.Minimum, 1e-9);
            Assert::AreEqual(1000, ok->ScanWindowRange.Maximum, 1e-9);
        }

        int ok1 = 0;
        for (auto i : thefile->GetMsScansInTimeRange(0, 2)) {
            ok1 += 1;
        }

        Assert::AreEqual(1, ok1);

        int ok2 = 0;
        for (auto i : thefile->GetMsScansInTimeRange(2, 4)) {
            ok2 += 1;
        }

        Assert::AreEqual(0, ok2);

        int ok3 = 0;
        for (auto i : thefile->GetMsScansInTimeRange(-4, -2)) {
            ok3 += 1;
        }

        Assert::AreEqual(0, ok3);

        delete thefile;
        delete theSpectrum;
    }

    void TestDataFile::TestAMoreRealFile() {
        auto theScan = dynamic_cast<IMsDataScanWithPrecursor<IMzSpectrum<IMzPeak*>*>*>(myMsDataFile->GetOneBasedScan(2));
        Assert::AreEqual(1, theScan->getIsolationRange()->getWidth());
        Assert::AreEqual(DissociationType::Unknown, theScan->getDissociationType());
        Assert::AreEqual(693.99, theScan->getIsolationMz());
        Assert::AreEqual(1, theScan->getIsolationRange()->Maximum - theScan->getIsolationRange()->Minimum);
        Assert::AreEqual(1, theScan->getOneBasedPrecursorScanNumber());
        Assert::AreEqual(3, theScan->getSelectedIonChargeStateGuess().Value);
        //Assert.IsNull(theScan.SelectedIonGuessIntensity);
        auto precursorScan = myMsDataFile->GetOneBasedScan(theScan->getOneBasedPrecursorScanNumber().Value);
        theScan->RefineSelectedMzAndIntensity(precursorScan->MassSpectrum);
        Assert::AreEqual(.32872, theScan->getSelectedIonIntensity(), 0.01);
        Assert::AreEqual(693.9892, theScan->getSelectedIonMZ(), 0.01);
        Assert::AreEqual(693.655, theScan->getSelectedIonMonoisotopicGuessMz(), 0.001);

        Assert::AreNotEqual(0, myMsDataFile->GetOneBasedScan(2)->MassSpectrum.FirstX);

        Assert::AreEqual(myMsDataFile->GetOneBasedScan(2)->MassSpectrum.CopyTo2DArray()[0][0], myMsDataFile->GetOneBasedScan(2)->MassSpectrum.FirstX);

        Assert::AreNotEqual(0, myMsDataFile->GetOneBasedScan(2)->MassSpectrum.LastX);

        theScan->ComputeMonoisotopicPeakIntensity(precursorScan->MassSpectrum);

        theScan->TransformMzs([&] (std::any b) {
            0;
        }, [&] (std::any b) {
            0;
        });

//C# TO C++ CONVERTER TODO TASK: There is no native C++ equivalent to 'ToString':
        Assert::AreEqual(L"Scan #2", myMsDataFile->GetOneBasedScan(2)->ToString());

        Assert::AreEqual(0, myMsDataFile->GetOneBasedScan(2)->MassSpectrum.FirstX);
        Assert::AreEqual(0, myMsDataFile->GetOneBasedScan(2)->MassSpectrum.LastX);
        Assert::AreEqual(0, theScan->getSelectedIonMZ());

        System::Collections::IEnumerable *a = myMsDataFile;
        for (auto b : a) {
            Assert::IsFalse((dynamic_cast<IMsDataScan<IMzSpectrum<IMzPeak*>*>*>(b))->getIsCentroid());
        }
        for (auto b : myMsDataFile) {
            Assert::AreEqual(Polarity::Positive, b->Polarity);
        }
    }

    MzmlMzSpectrum *TestDataFile::CreateMS2spectrum(std::vector<Fragment*> &fragments, int v1, int v2) {
        std::vector<double> allMasses;
        std::vector<double> allIntensities;
        for (auto f : fragments) {
            auto spec = CreateSpectrum(f->getThisChemicalFormula(), v1, v2, 2);
            for (int i = 0; i < spec->getSize(); i++) {
                allMasses.push_back(spec->getXArray()[i]);
                allIntensities.push_back(spec->getYArray()[i]);
            }
        }
        auto allMassesArray = allMasses.ToArray();
        auto allIntensitiessArray = allIntensities.ToArray();

        Array::Sort(allMassesArray, allIntensitiessArray);
        return new MzmlMzSpectrum(allMassesArray, allIntensitiessArray, false);
    }

    MzmlMzSpectrum *TestDataFile::CreateSpectrum(ChemicalFormula *f, double lowerBound, double upperBound, int minCharge) {
        IsotopicDistribution *isodist = IsotopicDistribution::GetDistribution(f, 0.1, 0.001);
        MzmlMzSpectrum *notActuallyMzS = new MzmlMzSpectrum(isodist->getMasses().ToArray(), isodist->getIntensities().ToArray(), false);

        notActuallyMzS->ReplaceXbyApplyingFunction([&] (std::any b) {
            b::X::ToMz(1);
        });

        std::vector<double> allMasses;
        std::vector<double> allIntensitiess;

        while (notActuallyMzS->getFirstX() > lowerBound) {
            for (int i = 0; i < notActuallyMzS->getSize(); i++) {
                if (notActuallyMzS->getXArray()[i] > lowerBound && notActuallyMzS->getXArray()[i] < upperBound) {
                    allMasses.push_back(notActuallyMzS->getXArray()[i]);
                    allIntensitiess.push_back(notActuallyMzS->getYArray()[i]);
                }
            }
            minCharge += 1;
            notActuallyMzS = new MzmlMzSpectrum(isodist->getMasses().ToArray(), isodist->getIntensities().ToArray(), false);
            notActuallyMzS->ReplaceXbyApplyingFunction([&] (std::any s) {
                s::X::ToMz(minCharge);
            });
        }

        auto allMassesArray = allMasses.ToArray();
        auto allIntensitiessArray = allIntensitiess.ToArray();

        Array::Sort(allMassesArray, allIntensitiessArray);

        delete notActuallyMzS;
        return new MzmlMzSpectrum(allMassesArray, allIntensitiessArray, false);
    }
}
