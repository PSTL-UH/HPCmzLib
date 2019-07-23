#include "SpectrumProcessingAndFiltering.h"
#include "../MassSpectrometry/FilteringParams.h"
#include "../MassSpectrometry/MsDataFile.h"

using namespace MassSpectrometry;
using namespace NUnit::Framework;

namespace Test
{

    void SpectrumProcessingAndFiltering::TestFilteringPeaksTopN_MultipleWindows(int peaksToKeep, std::optional<int> &windows, int peakCount)
    {
        std::vector<double> mzArray(100);
        std::vector<double> intArray(100);

        Random *r = new Random();

        for (int i = 0; i < 100; i++)
        {
            double randomMz = r->Next(100, 2000);
            double randomInst = r->Next(0, 100);

            mzArray[i] = randomMz;
            intArray[i] = randomInst;
        }

        FilteringParams *f = new FilteringParams(std::make_optional(peaksToKeep), std::nullopt, windows, false, false);

        MsDataFile::WindowModeHelper(intArray, mzArray, f, 100, 2000);

        if (windows)
        {
            Assert::LessOrEqual(static_cast<Decimal>(mzArray.Count()), static_cast<Decimal>(peaksToKeep) * static_cast<Decimal>(windows));
        }
        else
        {
            Assert::LessOrEqual(static_cast<Decimal>(mzArray.Count()), static_cast<Decimal>(peaksToKeep) * static_cast<Decimal>(1.0));
        }

//C# TO C++ CONVERTER TODO TASK: A 'delete f' statement was not added since f was passed to a method or constructor. Handle memory management manually.
        delete r;
    }

    void SpectrumProcessingAndFiltering::TestXcorrFilteringPeaksTopN_MultipleWindows()
    {
        std::vector<double> masses;
        std::vector<double> intensities;

        int startMass = 1;
        int incrementMass = 2;

        double startIntensity = 0.25;
        double incrementIntensity = 0.25;

        for (int i = 0; i < 100; i++)
        {
            masses.push_back(startMass);
            intensities.push_back(startIntensity);
            startMass = startMass + incrementMass;
            startIntensity = startIntensity + incrementIntensity * startMass;
        }

        std::vector<double> mzArray = masses.ToArray();
        std::vector<double> intArray = intensities.ToArray();

        MsDataFile::XCorrPrePreprocessing(intArray, mzArray, 1, 200, 197);

        //first mz rounded to nearest discrete mass bin 1.0005079
        Assert::AreEqual(1.0005079, mzArray[0]);

        //last mz rounded to nearest discrete mass bin 1.0005079
        Assert::AreEqual(std::round(200.10158 * std::pow(10, 5)) / std::pow(10, 5), std::round(mzArray[199] * std::pow(10, 5)) / std::pow(10, 5));

        //peaks within 1.5 thomson of precursor are absent
        Assert::AreEqual(0, intArray[195] + intArray[196] + intArray[197]);

        //not zero intensities
        Assert::AreEqual(94, intArray.Where([&] (std::any i)
        {
            return i > 0;
        }).ToList()->Count);

        //zero intensities
        Assert::AreEqual(106, intArray.Where([&] (std::any i)
        {
            return i == 0;
        }).ToList()->Count);

        //first peak with intensity
        Assert::AreEqual(std::round(11.60174419 * std::pow(10, 5)) / std::pow(10, 5), std::round(intArray[10] * std::pow(10, 5)) / std::pow(10, 5));

        //middle peak with intensity
        Assert::AreEqual(std::round(19.98981657 * std::pow(10, 5)) / std::pow(10, 5), std::round(intArray[100] * std::pow(10, 5)) / std::pow(10, 5));

        //middle peak with 0 intensity
        Assert::AreEqual(0, intArray[101]);

        //last peak with intensity
        Assert::AreEqual(std::round(27.20941558 * std::pow(10, 5)) / std::pow(10, 5), std::round(intArray[198] * std::pow(10, 5)) / std::pow(10, 5));
    }
}
