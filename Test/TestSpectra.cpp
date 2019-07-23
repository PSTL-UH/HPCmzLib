#include "TestSpectra.h"
#include "../MassSpectrometry/MzSpectra/MzSpectrum.h"
#include "../MzLibUtil/MzRange.h"
#include "../MzLibUtil/PpmTolerance.h"
#include "../MzLibUtil/Tolerance.h"
#include "../MzLibUtil/DoubleRange.h"

using namespace MassSpectrometry;
using namespace MzLibUtil;
using namespace NUnit::Framework;
namespace Stopwatch = System::Diagnostics::Stopwatch;

namespace Test
{

System::Diagnostics::Stopwatch *TestSpectra::privateStopwatch;

    Stopwatch *TestSpectra::getStopwatch()
    {
        return privateStopwatch;
    }

    void TestSpectra::setStopwatch(Stopwatch *value)
    {
        privateStopwatch = value;
    }

    void TestSpectra::Setuppp()
    {
        Stopwatch tempVar();
        setStopwatch(&tempVar);
        getStopwatch()->Start();
    }

    void TestSpectra::TearDown()
    {
        std::cout << StringHelper::formatSimple("Analysis time: {0}h {1}m {2}s", getStopwatch()->Elapsed.Hours, getStopwatch()->Elapsed.Minutes, getStopwatch()->Elapsed.Seconds) << std::endl;
    }

    void TestSpectra::Setup()
    {
        std::vector<double> mz = {328.73795, 329.23935, 447.73849, 448.23987, 482.23792, 482.57089, 482.90393, 500.95358, 501.28732, 501.62131, 611.99377, 612.32806, 612.66187, 722.85217, 723.35345};
        std::vector<double> intensities = {81007096.0, 28604418.0, 78353512.0, 39291696.0, 122781408.0, 94147520.0, 44238040.0, 71198680.0, 54184096.0, 21975364.0, 44514172.0, 43061628.0, 23599424.0, 56022696.0, 41019144.0};

        _mzSpectrumA = new MzSpectrum(mz, intensities, false);
    }

    void TestSpectra::SpectrumCount()
    {
        Assert::AreEqual(15, _mzSpectrumA->getSize());
    }

    void TestSpectra::SpectrumFirstMZ()
    {
        Assert::AreEqual(328.73795, _mzSpectrumA->getFirstX());
    }

    void TestSpectra::SpectrumLastMZ()
    {
        Assert::AreEqual(723.35345, _mzSpectrumA->getLastX());
    }

    void TestSpectra::SpectrumBasePeakIntensity()
    {
        double basePeakIntensity = _mzSpectrumA->getYofPeakWithHighestY().value();

        Assert::AreEqual(122781408.0, basePeakIntensity);
    }

    void TestSpectra::SpectrumTIC()
    {
        double tic = _mzSpectrumA->getSumOfAllY();

        Assert::AreEqual(843998894.0, tic);
    }

    void TestSpectra::SpectrumGetIntensityFirst()
    {
        Assert::AreEqual(81007096.0, _mzSpectrumA->getYArray()[0]);
    }

    void TestSpectra::SpectrumGetIntensityRandom()
    {
        Assert::AreEqual(44238040.0, _mzSpectrumA->getYArray()[6]);
    }

    void TestSpectra::SpectrumGetMassFirst()
    {
        Assert::AreEqual(328.73795, _mzSpectrumA->getFirstX());
    }

    void TestSpectra::SpectrumGetMassRandom()
    {
        Assert::AreEqual(482.90393, _mzSpectrumA->getXArray()[6]);
    }

    void TestSpectra::SpectrumContainsPeak()
    {
        Assert::IsTrue(_mzSpectrumA->getSize() > 0);
    }

    void TestSpectra::SpectrumContainsPeakInRange()
    {
        Assert::AreEqual(1, _mzSpectrumA->NumPeaksWithinRange(448.23987 - 0.001, 448.23987 + 0.001));
    }

    void TestSpectra::SpectrumContainsPeakInRangeEnd()
    {
        Assert::AreEqual(0, _mzSpectrumA->NumPeaksWithinRange(448.23987 - 0.001, 448.23987));
    }

    void TestSpectra::SpectrumContainsPeakInRangeStart()
    {
        Assert::AreEqual(1, _mzSpectrumA->NumPeaksWithinRange(448.23987, 448.23987 + 0.001));
    }

    void TestSpectra::SpectrumContainsPeakInRangeStartEnd()
    {
        Assert::AreEqual(0, _mzSpectrumA->NumPeaksWithinRange(448.23987, 448.23987));
    }

    void TestSpectra::SpectrumDoesntContainPeakInRange()
    {
        Assert::AreEqual(0, _mzSpectrumA->NumPeaksWithinRange(603.4243 - 0.001, 603.4243 + 0.001));
    }

    void TestSpectra::SpectrumMassRange()
    {
        MzRange *range = new MzRange(328.73795, 723.35345);

        Assert::AreEqual(0, _mzSpectrumA->getRange()->Minimum - range->Minimum, 1e-9);
        Assert::AreEqual(0, _mzSpectrumA->getRange()->Maximum - range->Maximum, 1e-9);

        delete range;
    }

    void TestSpectra::SpectrumFilterCount()
    {
        auto filteredMzSpectrum = _mzSpectrumA->FilterByY(28604417, 28604419);

        Assert::AreEqual(1, filteredMzSpectrum.size()());
    }

    void TestSpectra::FilterByNumberOfMostIntenseTest()
    {
        Assert::AreEqual(5, _mzSpectrumA->FilterByNumberOfMostIntense(5).size()());
    }

    void TestSpectra::FilterByNumberOfMostIntenseRobTest()
    {
        std::vector<double> x = {50, 60, 70, 147.0764, 257.1244, 258.127, 275.135};
        std::vector<double> y = {1, 1, 1, 1, 1, 1, 1};
        MzSpectrum *spectrum = new MzSpectrum(x, y, false);
        Assert::AreEqual(7, spectrum->FilterByNumberOfMostIntense(200).size()());

        delete spectrum;
    }

    void TestSpectra::GetBasePeak()
    {
        Assert::AreEqual(122781408.0, _mzSpectrumA->getYofPeakWithHighestY());
    }

    void TestSpectra::GetClosestPeak()
    {
        Assert::AreEqual(448.23987, _mzSpectrumA->GetClosestPeakXvalue(448));
        Assert::AreEqual(447.73849, _mzSpectrumA->GetClosestPeakXvalue(447.9));
    }

    void TestSpectra::Extract()
    {
        Assert::AreEqual(3, _mzSpectrumA->Extract(500, 600).size()());
    }

    void TestSpectra::CorrectOrder()
    {
        _mzSpectrumA = new MzSpectrum({5, 6, 7}, {1, 2, 3}, false);
        Assert::IsTrue(_mzSpectrumA->FilterByNumberOfMostIntense(2).front().Mz < _mzSpectrumA->FilterByNumberOfMostIntense(2).ToList()[1].Mz);
    }

    void TestSpectra::TestFunctionToX()
    {
        _mzSpectrumA->ReplaceXbyApplyingFunction([&] (std::any b)
        {
            -1;
        });
        Assert::AreEqual(-1, _mzSpectrumA->getXArray()[0]);
    }

    void TestSpectra::TestGetClosestPeakXValue()
    {
        Assert::AreEqual(447.73849, _mzSpectrumA->GetClosestPeakXvalue(447.73849));
        Assert::AreEqual(447.73849, _mzSpectrumA->GetClosestPeakXvalue(447));
        MzSpectrum tempVar(new double[0], new double[0], false);
        Assert::IsNull((&tempVar)->GetClosestPeakXvalue(1));
    }

    void TestSpectra::TestDotProduct()
    {
        std::vector<double> array1 = {1};
        std::vector<double> array2 = {2};
        std::vector<double> array3 = {1, 2};
        std::vector<double> array4 = {1, 1};

        MzSpectrum *spec1 = new MzSpectrum(array1, array1, false);
        MzSpectrum *spec2 = new MzSpectrum(array2, array1, false);
        MzSpectrum *spec3 = new MzSpectrum(array3, array4, false);
        Tolerance *tolerance = new PpmTolerance(10);

        Assert::AreEqual(spec1->CalculateDotProductSimilarity(spec3, tolerance), spec3->CalculateDotProductSimilarity(spec1, tolerance)); //comparison side shouldn't matter
        Assert::AreEqual(spec1->CalculateDotProductSimilarity(spec2, tolerance), 0); //orthogonal spectra give a score of zero
        Assert::AreEqual(spec2->CalculateDotProductSimilarity(spec2, tolerance), 1); //identical spectra give a score of 1
        Assert::IsTrue(tolerance->Within(spec3->CalculateDotProductSimilarity(spec2, tolerance), std::cos(M_PI / 4)));

//C# TO C++ CONVERTER TODO TASK: A 'delete tolerance' statement was not added since tolerance was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete spec3' statement was not added since spec3 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete spec2' statement was not added since spec2 was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete spec1' statement was not added since spec1 was passed to a method or constructor. Handle memory management manually.
    }

    void TestSpectra::TestNumPeaksWithinRange()
    {
        std::vector<double> xArray = {1, 2, 3, 4, 5, 6, 7};
        std::vector<double> yArray = {1, 2, 1, 5, 1, 2, 1};

        auto thisSpectrum = new MzSpectrum(xArray, yArray, false);

        Assert::AreEqual(7, thisSpectrum->NumPeaksWithinRange(std::numeric_limits<double>::lowest(), std::numeric_limits<double>::max()));

        Assert::AreEqual(6, thisSpectrum->NumPeaksWithinRange(1, 7));

        Assert::AreEqual(0, thisSpectrum->NumPeaksWithinRange(1, 1));

        Assert::AreEqual(1, thisSpectrum->NumPeaksWithinRange(1, 2));

        Assert::AreEqual(2, thisSpectrum->NumPeaksWithinRange(0.001, 2.999));

        Assert::AreEqual(1, thisSpectrum->NumPeaksWithinRange(0, 1.5));

        Assert::AreEqual(1, thisSpectrum->NumPeaksWithinRange(6.5, 8));

        Assert::AreEqual(2, thisSpectrum->NumPeaksWithinRange(3, 5));

        Assert::AreEqual(2, thisSpectrum->NumPeaksWithinRange(3.5, 5.5));

        Assert::AreEqual(1, thisSpectrum->NumPeaksWithinRange(7, 8));

        Assert::AreEqual(0, thisSpectrum->NumPeaksWithinRange(8, 9));

        Assert::AreEqual(0, thisSpectrum->NumPeaksWithinRange(-2, -1));

//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
        Assert::AreEqual("[1 to 7] m/z (Peaks 7)", thisSpectrum->ToString());

        //Assert.AreEqual(7, thisSpectrum.FilterByNumberOfMostIntense(7).Size);
        //Assert.AreEqual(1, thisSpectrum.FilterByNumberOfMostIntense(1).Size);
        //Assert.AreEqual(4, thisSpectrum.FilterByNumberOfMostIntense(1).FirstX);

        //Assert.AreEqual(2, thisSpectrum.FilterByNumberOfMostIntense(3).FirstX);

        //Assert.AreEqual(0, thisSpectrum.FilterByNumberOfMostIntense(0).Size);

        //Assert.AreEqual(2, thisSpectrum.WithRangeRemoved(2, 6).Size);
        //Assert.AreEqual(0, thisSpectrum.WithRangeRemoved(0, 100).Size);

        //Assert.AreEqual(6, thisSpectrum.WithRangeRemoved(7, 100).Size);

        //Assert.AreEqual(1, thisSpectrum.WithRangeRemoved(new DoubleRange(double.MinValue, 6)).Size);

        std::vector<DoubleRange*> xRanges =
        {
            new DoubleRange(2, 5),
            new DoubleRange(3, 6)
        };
        //Assert.AreEqual(2, thisSpectrum.WithRangesRemoved(xRanges).Size);

        //Assert.AreEqual(3, thisSpectrum.Extract(new DoubleRange(4.5, 10)).Size);

        //Assert.AreEqual(2, thisSpectrum.FilterByY(new DoubleRange(1.5, 2.5)).Size);

        //Assert.AreEqual(3, thisSpectrum.FilterByY(1.5, double.MaxValue).Size);

        //Assert.AreEqual(2, thisSpectrum.ApplyFunctionToX(b => b * 2).FirstX);

        Assert::AreEqual(1, thisSpectrum->GetClosestPeakXvalue(-100));

        Assert::AreEqual(7, thisSpectrum->GetClosestPeakXvalue(6.6));

        Assert::AreEqual(7, thisSpectrum->GetClosestPeakXvalue(7));

        Assert::AreEqual(7, thisSpectrum->GetClosestPeakXvalue(8));

        delete thisSpectrum;
    }
}
