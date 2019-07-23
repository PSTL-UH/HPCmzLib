#include "TestMsDataFile.h"
#include "../MassSpectrometry/MzSpectra/MzSpectrum.h"
#include "FakeMsDataFile.h"
#include "../UsefulProteomicsDatabases/Loaders.h"
#include "../MassSpectrometry/MsDataScan.h"
#include "../MassSpectrometry/Enums/MzAnalyzerType.h"
#include "../MassSpectrometry/Enums/Polarity.h"
#include "../MzLibUtil/MzRange.h"
#include "../MassSpectrometry/Enums/DissociationType.h"
#include "../Chemistry/ChemicalFormula.h"
#include "../Chemistry/IsotopicDistribution.h"

using namespace Chemistry;
using namespace MassSpectrometry;
using namespace MzLibUtil;
using namespace NUnit::Framework;
using namespace Proteomics::AminoAcidPolymer;
namespace Stopwatch = System::Diagnostics::Stopwatch;

namespace Test
{

System::Diagnostics::Stopwatch *TestMsDataFile::privateStopwatch;

    Stopwatch *TestMsDataFile::getStopwatch()
    {
        return privateStopwatch;
    }

    void TestMsDataFile::setStopwatch(Stopwatch *value)
    {
        privateStopwatch = value;
    }

    void TestMsDataFile::Setup()
    {
        Environment::CurrentDirectory = TestContext::CurrentContext->TestDirectory;

        UsefulProteomicsDatabases::Loaders::LoadElements(R"(elements.dat)");

        std::vector<double> mz = {328.73795, 329.23935, 447.73849, 448.23987, 482.23792, 482.57089, 482.90393, 500.95358, 501.28732, 501.62131, 611.99377, 612.32806, 612.66187, 722.85217, 723.35345};
        std::vector<double> intensities = {81007096.0, 28604418.0, 78353512.0, 39291696.0, 122781408.0, 94147520.0, 44238040.0, 71198680.0, 54184096.0, 21975364.0, 44514172.0, 43061628.0, 23599424.0, 56022696.0, 41019144.0};

        _mzSpectrumA = new MzSpectrum(mz, intensities, false);

        auto peptide = new Peptide("KQEEQMETEQQNKDEGK");

        MzSpectrum *MS1 = CreateSpectrum(peptide->GetChemicalFormula(), 300, 2000, 1);
        MzSpectrum *MS2 = CreateMS2spectrum(peptide->Fragment(FragmentTypes::b | FragmentTypes::y, true), 100, 1500);

        std::vector<MsDataScan*> Scans(2);
        MzRange tempVar(300, 2000);
        Scans[0] = new MsDataScan(MS1, 1, 1, false, Polarity::Positive, 1.0, &tempVar, "first spectrum", MZAnalyzerType::Unknown, MS1->getSumOfAllY(), std::make_optional(1), std::vector<std::vector<double>>(), "scan=1");

        MzRange tempVar2(100, 1500);
        Scans[1] = new MsDataScan(MS2, 2, 2, false, Polarity::Positive, 2.0, &tempVar2, "second spectrum", MZAnalyzerType::Unknown, MS2->getSumOfAllY(), std::make_optional(1), std::vector<std::vector<double>>(), "scan=2", std::make_optional(693.9892), std::make_optional(3), std::make_optional(.3872), std::make_optional(693.99), std::make_optional(1), std::make_optional(DissociationType::Unknown), std::make_optional(1), std::make_optional(693.6550));

        myMsDataFile = new FakeMsDataFile(Scans);

        delete peptide;
    }

    void TestMsDataFile::Setuppp()
    {
        Stopwatch tempVar();
        setStopwatch(&tempVar);
        getStopwatch()->Start();
    }

    void TestMsDataFile::TearDown()
    {
        std::cout << StringHelper::formatSimple("Analysis time: {0}h {1}m {2}s", getStopwatch()->Elapsed.Hours, getStopwatch()->Elapsed.Minutes, getStopwatch()->Elapsed.Seconds) << std::endl;
    }

    void TestMsDataFile::SpectrumCount()
    {
        Assert::AreEqual(15, _mzSpectrumA->getSize());
    }

    void TestMsDataFile::SpectrumFirstMZ()
    {
        Assert::AreEqual(328.73795, _mzSpectrumA->getFirstX());
    }

    void TestMsDataFile::SpectrumLastMZ()
    {
        Assert::AreEqual(723.35345, _mzSpectrumA->getLastX());
    }

    void TestMsDataFile::DataFileTest()
    {
        MzRange tempVar(300, 1000);
        MsDataScan *theSpectrum = new MsDataScan(_mzSpectrumA, 1, 1, true, Polarity::Positive, 1, &tempVar, "fake scan filter", MZAnalyzerType::Unknown, _mzSpectrumA->getSumOfAllY(), std::make_optional(1), std::vector<std::vector<double>>(), "scan=1");

        std::vector<MsDataScan*> theList(1);

        theList[0] = theSpectrum;

        FakeMsDataFile *thefile = new FakeMsDataFile(theList);

        auto theOneBasedScan = thefile->GetOneBasedScan(1);

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual("Scan #1", theOneBasedScan->ToString());

        Assert::AreEqual(15, theOneBasedScan->MassSpectrum.Size);
        Assert::AreEqual(15, theOneBasedScan->MassSpectrum.Size);

        Assert::AreEqual(1, thefile->getNumSpectra());
        Assert::AreEqual(1, thefile->getNumSpectra());

        Assert::IsTrue(thefile->GetOneBasedScan(1)->getIsCentroid());

        for (auto ok : thefile)
        {
            Assert::AreEqual(300, ok->ScanWindowRange.Minimum, 1e-9);
            Assert::AreEqual(1000, ok->ScanWindowRange.Maximum, 1e-9);
        }

        int ok1 = 0;
        for (auto i : thefile->GetMsScansInTimeRange(0, 2))
        {
            ok1 += 1;
        }

        Assert::AreEqual(1, ok1);

        int ok2 = 0;
        for (auto i : thefile->GetMsScansInTimeRange(2, 4))
        {
            ok2 += 1;
        }

        Assert::AreEqual(0, ok2);

        int ok3 = 0;
        for (auto i : thefile->GetMsScansInTimeRange(-4, -2))
        {
            ok3 += 1;
        }

        Assert::AreEqual(0, ok3);

        delete thefile;
        delete theSpectrum;
    }

    void TestMsDataFile::TestAMoreRealFile()
    {
        auto theScan = myMsDataFile->GetOneBasedScan(2);
        Assert::AreEqual(1, theScan->getIsolationRange()->getWidth());
        Assert::AreEqual(DissociationType::Unknown, theScan->getDissociationType());
        Assert::AreEqual(693.99, theScan->getIsolationMz());
        Assert::AreEqual(1, theScan->getIsolationRange()->Maximum - theScan->getIsolationRange()->Minimum);
        Assert::AreEqual(1, theScan->getOneBasedPrecursorScanNumber());
        Assert::AreEqual(3, theScan->getSelectedIonChargeStateGuess().value());

        auto precursorScan = myMsDataFile->GetOneBasedScan(theScan->getOneBasedPrecursorScanNumber().value());
        theScan->RefineSelectedMzAndIntensity(precursorScan->MassSpectrum);
        Assert::AreEqual(.32872, theScan->getSelectedIonIntensity(), 0.01);
        Assert::AreEqual(693.9892, theScan->getSelectedIonMZ(), 0.01);
        Assert::AreEqual(693.655, theScan->getSelectedIonMonoisotopicGuessMz(), 0.001);

        Assert::AreNotEqual(0, myMsDataFile->GetOneBasedScan(2)->MassSpectrum.FirstX);

        Assert::AreEqual(myMsDataFile->GetOneBasedScan(2)->MassSpectrum.CopyTo2DArray()[0][0], myMsDataFile->GetOneBasedScan(2)->MassSpectrum.FirstX);

        Assert::AreNotEqual(0, myMsDataFile->GetOneBasedScan(2)->MassSpectrum.LastX);

        theScan->ComputeMonoisotopicPeakIntensity(precursorScan->MassSpectrum);

        theScan->TransformMzs([&] (std::any b)
        {
            0;
        }, [&] (std::any b)
        {
            0;
        });

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual("Scan #2", myMsDataFile->GetOneBasedScan(2)->ToString());

        Assert::AreEqual(0, myMsDataFile->GetOneBasedScan(2)->MassSpectrum.FirstX);
        Assert::AreEqual(0, myMsDataFile->GetOneBasedScan(2)->MassSpectrum.LastX);
        Assert::AreEqual(0, theScan->getSelectedIonMZ());

        std::vector<MsDataScan*> a = myMsDataFile->GetAllScansList();
        for (auto b : a)
        {
            Assert::IsFalse(b->getIsCentroid());
        }
        for (auto b : myMsDataFile)
        {
            Assert::AreEqual(Polarity::Positive, b->Polarity);
        }
    }

    MzSpectrum *TestMsDataFile::CreateMS2spectrum(std::vector<Fragment*> &fragments, int v1, int v2)
    {
        std::vector<double> allMasses;
        std::vector<double> allIntensities;
        for (auto f : fragments)
        {
            auto spec = CreateSpectrum(f->getThisChemicalFormula(), v1, v2, 2);
            for (int i = 0; i < spec->getSize(); i++)
            {
                allMasses.push_back(spec->getXArray()[i]);
                allIntensities.push_back(spec->getYArray()[i]);
            }
        }
        auto allMassesArray = allMasses.ToArray();
        auto allIntensitiessArray = allIntensities.ToArray();

        Array::Sort(allMassesArray, allIntensitiessArray);
        return new MzSpectrum(allMassesArray, allIntensitiessArray, false);
    }

    MzSpectrum *TestMsDataFile::CreateSpectrum(ChemicalFormula *f, double lowerBound, double upperBound, int minCharge)
    {
        IsotopicDistribution *isodist = IsotopicDistribution::GetDistribution(f, 0.1, 0.001);
        MzSpectrum *notActuallyMzS = new MzSpectrum(isodist->getMasses().ToArray(), isodist->getIntensities().ToArray(), false);

        notActuallyMzS->ReplaceXbyApplyingFunction([&] (std::any b)
        {
            b::Mz::ToMz(1);
        });

        std::vector<double> allMasses;
        std::vector<double> allIntensitiess;

//C# TO C++ CONVERTER TODO TASK: Comparisons involving nullable type instances will need to be rewritten since comparison rules are different between C++ optional and System.Nullable:
        while (notActuallyMzS->getFirstX() > lowerBound)
        {
            for (int i = 0; i < notActuallyMzS->getSize(); i++)
            {
                if (notActuallyMzS->getXArray()[i] > lowerBound && notActuallyMzS->getXArray()[i] < upperBound)
                {
                    allMasses.push_back(notActuallyMzS->getXArray()[i]);
                    allIntensitiess.push_back(notActuallyMzS->getYArray()[i]);
                }
            }
            minCharge += 1;
            notActuallyMzS = new MzSpectrum(isodist->getMasses().ToArray(), isodist->getIntensities().ToArray(), false);
            notActuallyMzS->ReplaceXbyApplyingFunction([&] (std::any s)
            {
                s::Mz::ToMz(minCharge);
            });
        }

        auto allMassesArray = allMasses.ToArray();
        auto allIntensitiessArray = allIntensitiess.ToArray();

        Array::Sort(allMassesArray, allIntensitiessArray);

        delete notActuallyMzS;
        return new MzSpectrum(allMassesArray, allIntensitiessArray, false);
    }
}
