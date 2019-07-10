#include "MzSpectrum.h"
//#include "MzPeak.h"
//#include "../../Chemistry/ChemicalFormula.h"
//#include "../../Chemistry/IsotopicDistribution.h"
//#include "../../MzLibUtil/MzRange.h"
//#include "IsotopicEnvelope.h"
//#include "../../Chemistry/ClassExtensions.h"
//#include "../../MzLibUtil/DoubleRange.h"
//#include "../../MzLibUtil/Tolerance.h"

//using namespace Chemistry;
//using namespace MathNet::Numerics::Statistics;
//using namespace MzLibUtil;

namespace MassSpectrometry
{
    static constexpr int numAveraginesToGenerate = 1500;

    static std::vector<std::vector<double>> MzSpectrum::allMasses = std::vector<std::vector<double>>(numAveraginesToGenerate);
    static std::vector<std::vector<double>> MzSpectrum::allIntensities = std::vector<std::vector<double>>(numAveraginesToGenerate);
    static std::vector<double> MzSpectrum::mostIntenseMasses = std::vector<double>(numAveraginesToGenerate);
    static std::vector<double> MzSpectrum::diffToMonoisotopic = std::vector<double>(numAveraginesToGenerate);

    std::vector<double> MzSpectrum::getXArray() const
    {
        return privateXArray;
    }

    void MzSpectrum::setXArray(const std::vector<double> &value)
    {
        privateXArray = value;
    }

    std::vector<double> MzSpectrum::getYArray() const
    {
        return privateYArray;
    }

    void MzSpectrum::setYArray(const std::vector<double> &value)
    {
        privateYArray = value;
    }

    MzSpectrum::StaticConstructor::StaticConstructor()
    {
        // AVERAGINE
        constexpr double averageC = 4.9384;
        constexpr double averageH = 7.7583;
        constexpr double averageO = 1.4773;
        constexpr double averageN = 1.3577;
        constexpr double averageS = 0.0417;
        
        constexpr double fineRes = 0.125;
        constexpr double minRes = 1e-8;
        
        for (int i = 0; i < numAveraginesToGenerate; i++)
        {
            double averagineMultiplier = (i + 1) / 2.0;
            //Console.Write("numAveragines = " + numAveragines);
            ChemicalFormula *chemicalFormula = new ChemicalFormula();
            chemicalFormula->Add(PeriodicTable::GetElement("C"), FloatingPointToInteger::ToInt32(averageC * averagineMultiplier));
            chemicalFormula->Add(PeriodicTable::GetElement("H"), FloatingPointToInteger::ToInt32(averageH * averagineMultiplier));
            chemicalFormula->Add(PeriodicTable::GetElement("O"), FloatingPointToInteger::ToInt32(averageO * averagineMultiplier));
            chemicalFormula->Add(PeriodicTable::GetElement("N"), FloatingPointToInteger::ToInt32(averageN * averagineMultiplier));
            chemicalFormula->Add(PeriodicTable::GetElement("S"), FloatingPointToInteger::ToInt32(averageS * averagineMultiplier));
        
            {
                auto chemicalFormulaReg = chemicalFormula;
                IsotopicDistribution *ye = IsotopicDistribution::GetDistribution(chemicalFormulaReg, fineRes, minRes);
                auto masses = ye->getMasses().ToArray();
                auto intensities = ye->getIntensities().ToArray();
                Array::Sort(intensities, masses);
                Array::Reverse(intensities);
                Array::Reverse(masses);
        
                mostIntenseMasses[i] = masses[0];
                diffToMonoisotopic[i] = masses[0] - chemicalFormulaReg->getMonoisotopicMass();
                allMasses[i] = masses;
                allIntensities[i] = intensities;
            }

            delete chemicalFormula;
        }
    }

MzSpectrum::StaticConstructor MzSpectrum::staticConstructor;

    MzSpectrum::MzSpectrum(std::vector<std::vector<double>> &mzintensities)
    {
        auto count = (mzintensities.size() == 0 ? 0 : mzintensities[0].size());

        setXArray(std::vector<double>(count));
        setYArray(std::vector<double>(count));
        Buffer::BlockCopy(mzintensities, 0, getXArray(), 0, sizeof(double) * count);
        Buffer::BlockCopy(mzintensities, sizeof(double) * count, getYArray(), 0, sizeof(double) * count);
        peakList = std::vector<MzPeak*>(getSize());
    }

    MzSpectrum::MzSpectrum(std::vector<double> &mz, std::vector<double> &intensities, bool shouldCopy)
    {
        if (shouldCopy)
        {
            setXArray(std::vector<double>(mz.size()));
            setYArray(std::vector<double>(intensities.size()));
            Array::Copy(mz, getXArray(), mz.size());
            Array::Copy(intensities, getYArray(), intensities.size());
        }
        else
        {
            setXArray(mz);
            setYArray(intensities);
        }
        peakList = std::vector<MzPeak*>(getSize());
    }

    MzRange *MzSpectrum::getRange() const
    {
        if (getSize() == 0)
        {
            return nullptr;
        }
        return new MzRange(getFirstX().value(), getLastX().value());
    }

    std::optional<double> MzSpectrum::getFirstX() const
    {
        if (getSize() == 0)
        {
            return std::nullopt;
        }
        return std::make_optional(getXArray()[0]);
    }

    std::optional<double> MzSpectrum::getLastX() const
    {
        if (getSize() == 0)
        {
            return std::nullopt;
        }
        return std::make_optional(getXArray()[getSize() - 1]);
    }

    int MzSpectrum::getSize() const
    {
        return getXArray().size();
    }

    std::optional<int> MzSpectrum::getIndexOfPeakWithHighesetY() const
    {
        if (getSize() == 0)
        {
            return std::nullopt;
        }
        if (!indexOfpeakWithHighestY)
        {
            indexOfpeakWithHighestY = std::make_optional(Array::IndexOf(getYArray(), getYArray().Max()));
        }
        return std::make_optional(indexOfpeakWithHighestY.value());
    }

    std::optional<double> MzSpectrum::getYofPeakWithHighestY() const
    {
        if (getSize() == 0)
        {
            return std::nullopt;
        }
        return std::make_optional(getYArray()[getIndexOfPeakWithHighesetY().value()]);
    }

    std::optional<double> MzSpectrum::getXofPeakWithHighestY() const
    {
        if (getSize() == 0)
        {
            return std::nullopt;
        }
        return std::make_optional(getXArray()[getIndexOfPeakWithHighesetY().value()]);
    }

    double MzSpectrum::getSumOfAllY() const
    {
        if (!sumOfAllY)
        {
            sumOfAllY = getYArray().Sum();
        }
        return sumOfAllY.value();
    }

    std::vector<unsigned char> MzSpectrum::Get64Bitarray(std::vector<double> &array)
    {
        auto mem = new MemoryStream();
        for (auto okk : array)
        {
            std::vector<unsigned char> ok = BitConverter::GetBytes(okk);
            mem->Write(ok, 0, ok.size());
        }
        mem->Position = 0;

        delete mem;
        return mem->ToArray();
    }

    std::vector<unsigned char> MzSpectrum::Get64BitYarray()
    {
        return Get64Bitarray(getYArray());
    }

    std::vector<unsigned char> MzSpectrum::Get64BitXarray()
    {
        return Get64Bitarray(getXArray());
    }

    std::string MzSpectrum::ToString()
    {
        return StringHelper::formatSimple("{0} (Peaks {1})", getRange(), getSize());
    }

    std::vector<IsotopicEnvelope*> MzSpectrum::Deconvolute(MzRange *theRange, int minAssumedChargeState, int maxAssumedChargeState, double deconvolutionTolerancePpm, double intensityRatioLimit)
    {
        if (getSize() == 0)
        {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
            yield break;
        }

        auto isolatedMassesAndCharges = std::vector<IsotopicEnvelope*>();

        for (auto candidateForMostIntensePeak : ExtractIndices(theRange->Minimum, theRange->Maximum))
        {
            IsotopicEnvelope *bestIsotopeEnvelopeForThisPeak = nullptr;

            auto candidateForMostIntensePeakMz = getXArray()[candidateForMostIntensePeak];
            //Console.WriteLine("candidateForMostIntensePeakMz: " + candidateForMostIntensePeakMz);
            auto candidateForMostIntensePeakIntensity = getYArray()[candidateForMostIntensePeak];

            for (int chargeState = minAssumedChargeState; chargeState <= maxAssumedChargeState; chargeState++)
            {
                //Console.WriteLine(" chargeState: " + chargeState);
                auto testMostIntenseMass = Chemistry::ClassExtensions::ToMass(candidateForMostIntensePeakMz, chargeState);

                auto massIndex = Array::BinarySearch(mostIntenseMasses, testMostIntenseMass);
                if (massIndex < 0)
                {
                    massIndex = ~massIndex;
                }
                if (massIndex == mostIntenseMasses.size())
                {
                    //Console.WriteLine("Breaking  because mass is too high: " + testMostIntenseMass);
                    break;
                }
                //Console.WriteLine("  massIndex: " + massIndex);

                auto listOfPeaks = std::vector<(double, double)*> {(candidateForMostIntensePeakMz, candidateForMostIntensePeakIntensity)};
                auto listOfRatios = std::vector<std::vector<std::vector<double>>>(massIndex) / candidateForMostIntensePeakIntensity };
                // Assuming the test peak is most intense...
                // Try to find the rest of the isotopes!

                double differenceBetweenTheorAndActual = testMostIntenseMass - mostIntenseMasses[massIndex];
                double totalIntensity = candidateForMostIntensePeakIntensity;
                for (int indexToLookAt = 1; indexToLookAt < allIntensities[massIndex].size(); indexToLookAt++)
                {
                    //Console.WriteLine("   indexToLookAt: " + indexToLookAt);
                    double theorMassThatTryingToFind = allMasses[massIndex][indexToLookAt] + differenceBetweenTheorAndActual;
                    //Console.WriteLine("   theorMassThatTryingToFind: " + theorMassThatTryingToFind);
                    //Console.WriteLine("   theorMassThatTryingToFind.ToMz(chargeState): " + theorMassThatTryingToFind.ToMz(chargeState));
                    auto closestPeakToTheorMass = GetClosestPeakIndex(Chemistry::ClassExtensions::ToMz(theorMassThatTryingToFind, chargeState));
                    auto closestPeakmz = getXArray()[closestPeakToTheorMass.value()];
                    //Console.WriteLine("   closestPeakmz: " + closestPeakmz);
                    auto closestPeakIntensity = getYArray()[closestPeakToTheorMass.value()];
                    if (std::abs(Chemistry::ClassExtensions::ToMass(closestPeakmz, chargeState) - theorMassThatTryingToFind) / theorMassThatTryingToFind * 1e6 <= deconvolutionTolerancePpm && Peak2satisfiesRatio(allIntensities[massIndex][0], allIntensities[massIndex][indexToLookAt], candidateForMostIntensePeakIntensity, closestPeakIntensity, intensityRatioLimit) && !std::find(listOfPeaks.begin(), listOfPeaks.end(), (closestPeakmz, closestPeakIntensity)) != listOfPeaks.end()))
                    {
                        //Found a match to an isotope peak for this charge state!
                        //Console.WriteLine(" *   Found a match to an isotope peak for this charge state!");
                        //Console.WriteLine(" *   chargeState: " + chargeState);
                        //Console.WriteLine(" *   closestPeakmz: " + closestPeakmz);
                        listOfPeaks.push_back((closestPeakmz, closestPeakIntensity));
                        totalIntensity += closestPeakIntensity;
                        listOfRatios.push_back(allIntensities[massIndex][indexToLookAt] / closestPeakIntensity);
                    }
                    else
                    {
                        break;
                    }
                }

                auto extrapolatedMonoisotopicMass = testMostIntenseMass - diffToMonoisotopic[massIndex]; // Optimized for proteoforms!!
                auto lowestMass = listOfPeaks.Min([&] (std::any b)
                {
                    b::Item1;
                }).ToMass(chargeState); // But may actually observe this small peak
                auto monoisotopicMass = std::abs(extrapolatedMonoisotopicMass - lowestMass) < 0.5 ? lowestMass : extrapolatedMonoisotopicMass;

                IsotopicEnvelope *test = new IsotopicEnvelope(listOfPeaks, monoisotopicMass, chargeState, totalIntensity, MathNet::Numerics::Statistics::Statistics::StandardDeviation(listOfRatios), massIndex);

                if (listOfPeaks.size() >= 2 && ScoreIsotopeEnvelope(test) > ScoreIsotopeEnvelope(bestIsotopeEnvelopeForThisPeak))
                {
                    //Console.WriteLine("Better charge state is " + test.charge);
                    //Console.WriteLine("peaks: " + string.Join(",", listOfPeaks.Select(b => b.Item1)));
                    bestIsotopeEnvelopeForThisPeak = test;
                }

//C# TO C++ CONVERTER TODO TASK: A 'delete test' statement was not added since test was passed to a method or constructor. Handle memory management manually.
            }

            if (bestIsotopeEnvelopeForThisPeak != nullptr && bestIsotopeEnvelopeForThisPeak->peaks.size() >= 2)
            {
                isolatedMassesAndCharges.push_back(bestIsotopeEnvelopeForThisPeak);
            }
        }

        std::unordered_set<double> seen;
        for (auto ok : isolatedMassesAndCharges.OrderByDescending([&] (std::any b)
        {
            ScoreIsotopeEnvelope(b);
        }))
        {
            if (seen.Overlaps(ok::peaks->Select([&] (std::any b)
            {
                b::mz;
            })))
            {
                continue;
            }
            for (auto ah : ok::peaks->Select([&] (std::any b)
            {
                b::mz;
            }))
            {
                seen.insert(ah);
            }
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
            yield return ok;
        }
    }

    std::vector<int> MzSpectrum::ExtractIndices(double minX, double maxX)
    {
        int ind = Array::BinarySearch(getXArray(), minX);
        if (ind < 0)
        {
            ind = ~ind;
        }
        while (ind < getSize() && getXArray()[ind] <= maxX)
        {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
            yield return ind;
            ind++;
        }
    }

    std::optional<int> MzSpectrum::GetClosestPeakIndex(double x)
    {
        if (getSize() == 0)
        {
            return std::nullopt;
        }
        int index = Array::BinarySearch(getXArray(), x);
        if (index >= 0)
        {
            return std::make_optional(index);
        }
        index = ~index;

        if (index >= getSize())
        {
            return std::make_optional(index - 1);
        }
        if (index == 0)
        {
            return std::make_optional(index);
        }

        if (x - getXArray()[index - 1] > getXArray()[index] - x)
        {
            return std::make_optional(index);
        }
        return std::make_optional(index - 1);
    }

    void MzSpectrum::ReplaceXbyApplyingFunction(std::function<double(MzPeak*)> convertor)
    {
        for (int i = 0; i < getSize(); i++)
        {
            getXArray()[i] = convertor(GetPeak(i));
        }
        peakList = std::vector<MzPeak*>(getSize());
    }

    std::vector<std::vector<double>> MzSpectrum::CopyTo2DArray()
    {
//C# TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in C#:
//ORIGINAL LINE: double[,] data = new double[2, Size];
        std::vector<std::vector<double>> data = RectangularVectors::RectangularDoubleVector(2, getSize());
        constexpr int size = sizeof(double);
        Buffer::BlockCopy(getXArray(), 0, data, 0, size * getSize());
        Buffer::BlockCopy(getYArray(), 0, data, size * getSize(), size * getSize());
        return data;
    }

    std::optional<double> MzSpectrum::GetClosestPeakXvalue(double x)
    {
        if (getSize() == 0)
        {
            return std::nullopt;
        }
        return std::make_optional(getXArray()[GetClosestPeakIndex(x).value()]);
    }

    int MzSpectrum::NumPeaksWithinRange(double minX, double maxX)
    {
        int startingIndex = Array::BinarySearch(getXArray(), minX);
        if (startingIndex < 0)
        {
            startingIndex = ~startingIndex;
        }
        if (startingIndex >= getSize())
        {
            return 0;
        }
        int endIndex = Array::BinarySearch(getXArray(), maxX);
        if (endIndex < 0)
        {
            endIndex = ~endIndex;
        }
        if (endIndex == 0)
        {
            return 0;
        }

        return endIndex - startingIndex;
    }

    std::vector<MzPeak*> MzSpectrum::FilterByNumberOfMostIntense(int topNPeaks)
    {
        auto quantile = 1.0 - static_cast<double>(topNPeaks) / getSize();
        quantile = std::max(0, quantile);
        quantile = std::min(1, quantile);
        double cutoffYvalue = getYArray().Quantile(quantile);

        for (int i = 0; i < getSize(); i++)
        {
            if (getYArray()[i] >= cutoffYvalue)
            {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                yield return GetPeak(i);
            }
        }
    }

    std::vector<MzPeak*> MzSpectrum::Extract(DoubleRange *xRange)
    {
        return Extract(xRange->Minimum, xRange->Maximum);
    }

    std::vector<MzPeak*> MzSpectrum::Extract(double minX, double maxX)
    {
        int ind = Array::BinarySearch(getXArray(), minX);
        if (ind < 0)
        {
            ind = ~ind;
        }
        while (ind < getSize() && getXArray()[ind] <= maxX)
        {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
            yield return GetPeak(ind);
            ind++;
        }
    }

    std::vector<MzPeak*> MzSpectrum::FilterByY(double minY, double maxY)
    {
        for (int i = 0; i < getSize(); i++)
        {
            if (getYArray()[i] >= minY && getYArray()[i] <= maxY)
            {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                yield return GetPeak(i);
            }
        }
    }

    std::vector<MzPeak*> MzSpectrum::FilterByY(DoubleRange *yRange)
    {
        return FilterByY(yRange->Minimum, yRange->Maximum);
    }

    double MzSpectrum::CalculateDotProductSimilarity(MzSpectrum *spectrumToCompare, Tolerance *tolerance)
    {
        //get arrays of m/zs and intensities
        std::vector<double> mz1 = getXArray();
        std::vector<double> intensity1 = getYArray();

        std::vector<double> mz2 = spectrumToCompare->getXArray();
        std::vector<double> intensity2 = spectrumToCompare->getYArray();

        //convert spectra to vectors
        std::vector<double> vector1;
        std::vector<double> vector2;
        int i = 0; //iterate through mz1
        int j = 0; //iterate through mz2

        //find where peaks match
        while (i != mz1.size() && j != mz2.size())
        {
            double one = mz1[i];
            double two = mz2[j];
            if (tolerance->Within(one, two)) //if match
            {
                vector1.push_back(intensity1[i]);
                vector2.push_back(intensity2[j]);
                i++;
                j++;
            }
            else if (one > two)
            {
                vector1.push_back(0);
                vector2.push_back(intensity2[j]);
                j++;
            }
            else //two>one
            {
                vector1.push_back(intensity1[i]);
                vector2.push_back(0);
                i++;
            }
        }
        //wrap up leftover peaks
        for (; i < mz1.size(); i++)
        {
            vector1.push_back(intensity1[i]);
            vector2.push_back(0);
        }
        for (; j < mz2.size(); j++)
        {
            vector1.push_back(0);
            vector2.push_back(intensity2[j]);
        }

        //numerator of dot product
        double numerator = 0;
        for (i = 0; i < vector1.size(); i++)
        {
            numerator += vector1[i] * vector2[i];
        }

        //denominator of dot product
        double denominator = std::sqrt(vector1.Sum([&] (std::any x)
        {
            return x * x;
        })) * std::sqrt(vector2.Sum([&] (std::any x)
        {
            return x * x;
        }));

        //return dot product
        return numerator / denominator;
    }

    double MzSpectrum::ScoreIsotopeEnvelope(IsotopicEnvelope *b)
    {
        if (b == nullptr)
        {
            return 0;
        }
        return b->totalIntensity / std::pow(b->stDev, 0.13) * std::pow(b->peaks.size(), 0.4) / std::pow(b->charge, 0.06);
    }

    bool MzSpectrum::Peak2satisfiesRatio(double peak1theorIntensity, double peak2theorIntensity, double peak1intensity, double peak2intensity, double intensityRatio)
    {
        auto comparedShouldBe = peak1intensity / peak1theorIntensity * peak2theorIntensity;

        if (peak2intensity < comparedShouldBe / intensityRatio || peak2intensity > comparedShouldBe * intensityRatio)
        {
            return false;
        }
        return true;
    }

    MzPeak *MzSpectrum::GetPeak(int index)
    {
        if (peakList[index] == nullptr)
        {
            peakList[index] = GeneratePeak(index);
        }
        return peakList[index];
    }

    MzPeak *MzSpectrum::GeneratePeak(int index)
    {
        return new MzPeak(getXArray()[index], getYArray()[index]);
    }
}
