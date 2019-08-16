#include "MzSpectrum.h"
#include "MzPeak.h"
#include "../../Chemistry/ChemicalFormula.h"
#include "../../Chemistry/IsotopicDistribution.h"
#include "../../MzLibUtil/MzRange.h"
#include "IsotopicEnvelope.h"
#include "../../Chemistry/ClassExtensions.h"
#include "../../MzLibUtil/DoubleRange.h"
#include "../../MzLibUtil/Tolerance.h"

#include "Sort.h"
#include "Math.h"
#include "RectangularVectors.h"

//using namespace Chemistry;
//using namespace MathNet::Numerics::Statistics;
//using namespace MzLibUtil;

namespace MassSpectrometry
{
    static constexpr int numAveraginesToGenerate = 1500;

    //std::vector<std::vector<double>> MzSpectrum::allMasses = std::vector<std::vector<double>>(numAveraginesToGenerate);
    //std::vector<std::vector<double>> MzSpectrum::allIntensities = std::vector<std::vector<double>>(numAveraginesToGenerate);
    //std::vector<double> MzSpectrum::mostIntenseMasses = std::vector<double>(numAveraginesToGenerate);
    //std::vector<double> MzSpectrum::diffToMonoisotopic = std::vector<double>(numAveraginesToGenerate);

    std::vector<std::vector<double>> MzSpectrum::allMasses;
    std::vector<std::vector<double>> MzSpectrum::allIntensities;
    std::vector<double> MzSpectrum::mostIntenseMasses;
    std::vector<double> MzSpectrum::diffToMonoisotopic;

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
        

        if ( allMasses.empty() ) {
            allMasses.resize(numAveraginesToGenerate);
        }
        if ( allIntensities.empty() ) {
            allIntensities.resize(numAveraginesToGenerate);
        }
        if ( mostIntenseMasses.empty() ) {
            mostIntenseMasses.resize(numAveraginesToGenerate);
        }
        if ( diffToMonoisotopic.empty() ) {
            diffToMonoisotopic.resize(numAveraginesToGenerate);
        }

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
                auto masses = ye->getMasses();
                auto intensities = ye->getIntensities();
#ifdef ORIG
                Array::Sort(intensities, masses);
                Array::Reverse(intensities);
                Array::Reverse(masses);
#endif
                Sort::SortPairs ( intensities, masses, intensities.size() );
                std::reverse (intensities.begin(), intensities.end());
                std::reverse (masses.begin(), masses.end() );

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
#ifdef ORIG
        Buffer::BlockCopy(mzintensities, 0, getXArray(), 0, sizeof(double) * count);
        Buffer::BlockCopy(mzintensities, sizeof(double) * count, getYArray(), 0, sizeof(double) * count);
#endif
        std::copy (mzintensities[0].begin(), mzintensities[0].end(), privateXArray.begin());
        std::copy (mzintensities[1].begin(), mzintensities[1].end(), privateYArray.begin()  );
        peakList = std::vector<MzPeak*>(getSize());
    }

    MzSpectrum::MzSpectrum(std::vector<double> &mz, std::vector<double> &intensities, bool shouldCopy)
    {
        if (shouldCopy)
        {
            setXArray(std::vector<double>(mz.size()));
            setYArray(std::vector<double>(intensities.size()));

#ifdef ORIG
            Array::Copy(mz, getXArray(), mz.size());
            Array::Copy(intensities, getYArray(), intensities.size());
#endif
            std::copy (mz.begin(), mz.end(), privateXArray.begin());
            std::copy (intensities.begin(), intensities.end(), privateYArray.begin()  );
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

    std::optional<int> MzSpectrum::getIndexOfPeakWithHighesetY() 
    {
        if (getSize() == 0)
        {
            return std::nullopt;
        }
        if (!indexOfpeakWithHighestY.has_value())
        {
            //indexOfpeakWithHighestY = std::make_optional(Array::IndexOf(getYArray(), getYArray().Max()));
            auto maxval = std::max_element(getYArray().begin(), getYArray().end() );
            indexOfpeakWithHighestY = std::make_optional(std::distance(getYArray().begin(), maxval ));
        }
        return std::make_optional(indexOfpeakWithHighestY.value());
    }

    std::optional<double> MzSpectrum::getYofPeakWithHighestY() 
    {
        if (getSize() == 0)
        {
            return std::nullopt;
        }
        int index = getIndexOfPeakWithHighesetY().value();
        return std::make_optional(getYArray()[index]);
    }

    std::optional<double> MzSpectrum::getXofPeakWithHighestY() 
    {
        if (getSize() == 0)
        {
            return std::nullopt;
        }
        int index = getIndexOfPeakWithHighesetY().value();
        return std::make_optional(getXArray()[index]);
    }

    double MzSpectrum::getSumOfAllY() 
    {
        if (!sumOfAllY.has_value() )
        {
#ifdef ORIG
            sumOfAllY = getYArray().Sum();
#endif
            double sum = 0.0;
            for ( auto y : getYArray() ) {
                sum +=  y;
            }
            sumOfAllY = std::make_optional ( sum );
        }
        return sumOfAllY.value();
    }

    std::vector<unsigned char> MzSpectrum::Get64Bitarray(std::vector<double> array_Renamed)
    {
      std::vector<unsigned char> ok;
            for (double okk : array_Renamed) {
                unsigned char* ptr = (unsigned char *)(&okk);
                for ( int i=0; i< (int)sizeof(double); i++ ){
                    ok.push_back(*ptr);
                    ptr++;
                }
            }
            return ok;
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

    std::vector<IsotopicEnvelope*> MzSpectrum::Deconvolute(MzRange *theRange,
                                                           int minAssumedChargeState,
                                                           int maxAssumedChargeState,
                                                           double deconvolutionTolerancePpm,
                                                           double intensityRatioLimit)
    {
        auto isolatedMassesAndCharges = std::vector<IsotopicEnvelope*>();
        if (getSize() == 0)  {
            //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
            //yield break;
            return isolatedMassesAndCharges;
        }
        

        for (auto candidateForMostIntensePeak : ExtractIndices(theRange->getMinimum(), theRange->getMaximum()))
        {
            IsotopicEnvelope *bestIsotopeEnvelopeForThisPeak = nullptr;

            auto candidateForMostIntensePeakMz = getXArray()[candidateForMostIntensePeak];
            //Console.WriteLine("candidateForMostIntensePeakMz: " + candidateForMostIntensePeakMz);
            auto candidateForMostIntensePeakIntensity = getYArray()[candidateForMostIntensePeak];

            for (int chargeState = minAssumedChargeState; chargeState <= maxAssumedChargeState; chargeState++)
            {
                //Console.WriteLine(" chargeState: " + chargeState);
                auto testMostIntenseMass = Chemistry::ClassExtensions::ToMass(candidateForMostIntensePeakMz, chargeState);

                //auto massIndex = Array::BinarySearch(mostIntenseMasses, testMostIntenseMass);
                int massIndex = std::binary_search(mostIntenseMasses.begin(), mostIntenseMasses.end(),
                                                   testMostIntenseMass);
                if (massIndex < 0) {
                    massIndex = ~massIndex;
                }
                if (massIndex == (int) mostIntenseMasses.size()) {
                    //Console.WriteLine("Breaking  because mass is too high: " + testMostIntenseMass);
                    break;
                }
                //Console.WriteLine("  massIndex: " + massIndex);

                std::vector<std::tuple<double, double>> listOfPeaks = {std::make_tuple(candidateForMostIntensePeakMz, candidateForMostIntensePeakIntensity)};

#ifdef ORG
                // Code generated by C#to C++ convertor below is weird.
                // auto listOfRatios = std::vector<std::vector<std::vector<double>>>(massIndex) / candidateForMostIntensePeakIntensity };
               // Here is the original line from C#
               // var listOfRatios = new List<double> { allIntensities[massIndex][0] / candidateForMostIntensePeakIntensity };
            
#endif
            auto listOfRatios = std::vector<double>{allIntensities[massIndex][0] / candidateForMostIntensePeakIntensity };
                // Assuming the test peak is most intense...
                // Try to find the rest of the isotopes!

                double differenceBetweenTheorAndActual = testMostIntenseMass - mostIntenseMasses[massIndex];
                double totalIntensity = candidateForMostIntensePeakIntensity;
                for (int indexToLookAt=1; indexToLookAt<(int) allIntensities[massIndex].size(); indexToLookAt++) {
                    //Console.WriteLine("   indexToLookAt: " + indexToLookAt);
                    double theorMassThatTryingToFind = allMasses[massIndex][indexToLookAt] + differenceBetweenTheorAndActual;
                    //Console.WriteLine("   theorMassThatTryingToFind: " + theorMassThatTryingToFind);
                    //Console.WriteLine("   theorMassThatTryingToFind.ToMz(chargeState): " + theorMassThatTryingToFind.ToMz(chargeState));
                    auto closestPeakToTheorMass = GetClosestPeakIndex(Chemistry::ClassExtensions::ToMz(theorMassThatTryingToFind, chargeState));
                    auto closestPeakmz = getXArray()[closestPeakToTheorMass.value()];
                    //Console.WriteLine("   closestPeakmz: " + closestPeakmz);
                    auto closestPeakIntensity = getYArray()[closestPeakToTheorMass.value()];
                    if (std::abs(Chemistry::ClassExtensions::ToMass(closestPeakmz, chargeState) - theorMassThatTryingToFind) / theorMassThatTryingToFind * 1e6 <= deconvolutionTolerancePpm
                        && Peak2satisfiesRatio(allIntensities[massIndex][0], allIntensities[massIndex][indexToLookAt], candidateForMostIntensePeakIntensity, closestPeakIntensity, intensityRatioLimit)
                        && (std::find(listOfPeaks.begin(), listOfPeaks.end(), std::make_tuple(closestPeakmz, closestPeakIntensity)) == listOfPeaks.end()))
                    {
                        //Found a match to an isotope peak for this charge state!
                        //Console.WriteLine(" *   Found a match to an isotope peak for this charge state!");
                        //Console.WriteLine(" *   chargeState: " + chargeState);
                        //Console.WriteLine(" *   closestPeakmz: " + closestPeakmz);
                        listOfPeaks.push_back(std::make_tuple(closestPeakmz, closestPeakIntensity));
                        totalIntensity += closestPeakIntensity;
                        listOfRatios.push_back(allIntensities[massIndex][indexToLookAt] / closestPeakIntensity);
                    }
                    else
                    {
                        break;
                    }
                }

                // Optimized for proteoforms!!
                auto extrapolatedMonoisotopicMass = testMostIntenseMass - diffToMonoisotopic[massIndex];
                double lM = std::numeric_limits<double>::max();
#ifdef ORIG
                auto lowestMass = listOfPeaks.Min([&] (std::any b)
                {
                    b::Item1;
                }).ToMass(chargeState); // But may actually observe this small peak
#endif
                std::for_each(listOfPeaks.begin(), listOfPeaks.end(), [&] (std::tuple<double, double> b) {
                        double b1 = std::get<0>(b);
                         if ( b1< lM ) {
                             lM = b1;
                }});
                double lowestMass = Chemistry::ClassExtensions::ToMass(lM, chargeState);
                
                auto monoisotopicMass = std::abs(extrapolatedMonoisotopicMass - lowestMass) < 0.5 ? lowestMass : extrapolatedMonoisotopicMass;

                IsotopicEnvelope *test = new IsotopicEnvelope(listOfPeaks, monoisotopicMass,
                                                              chargeState, totalIntensity,
                                                              Math::StandardDeviation(listOfRatios),
                                                              massIndex);

                if (listOfPeaks.size() >= 2 && ScoreIsotopeEnvelope(test) >
                    ScoreIsotopeEnvelope(bestIsotopeEnvelopeForThisPeak))
                {
                    //Console.WriteLine("Better charge state is " + test.charge);
                    //Console.WriteLine("peaks: " + string.Join(",", listOfPeaks.Select(b => b.Item1)));
                    bestIsotopeEnvelopeForThisPeak = test;
                }

                //C# TO C++ CONVERTER TODO TASK: A 'delete test' statement was not added since
                //est was passed to a method or constructor. Handle memory management manually.
            }

            if (bestIsotopeEnvelopeForThisPeak != nullptr && bestIsotopeEnvelopeForThisPeak->peaks.size() >= 2)
            {
                isolatedMassesAndCharges.push_back(bestIsotopeEnvelopeForThisPeak);
            }
        }
#ifdef ORIG
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
            
#endif
            std::unordered_set<double> seen = std::unordered_set<double>();
            std::vector<IsotopicEnvelope*> y;
            std::sort(isolatedMassesAndCharges.begin(), isolatedMassesAndCharges.end(), [&] ( IsotopicEnvelope *lhs, IsotopicEnvelope *rhs) {
                    return (ScoreIsotopeEnvelope(lhs) < ScoreIsotopeEnvelope(rhs));
            });
            for (IsotopicEnvelope* ok : isolatedMassesAndCharges ) {
                bool found =false;
                for ( auto p : ok->peaks ) {
                    if (seen.find(std::get<0>(p)) == seen.end()) {
                        found = true;
                        break;
                    }
                }
                if ( found ) {
                    continue;
                }
                for ( auto p: ok->peaks ) {
                    seen.insert(std::get<0>(p));
                }
                //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                y.push_back(ok);
            }
            return y;
        }

    std::vector<int> MzSpectrum::ExtractIndices(double minX, double maxX)
    {
        std::vector<int> v;
# ifdef ORIG
        int ind = Array::BinarySearch(getXArray(), minX);
#endif
        int ind = std::binary_search (getXArray().begin(), getXArray().end(), minX);
        if (ind < 0)
        {
            ind = ~ind;
        }
        while (ind < getSize() && getXArray()[ind] <= maxX)
        {
            //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
            //yield return ind;
            v.push_back(ind);
            ind++;
        }
        return v;
    }

    std::optional<int> MzSpectrum::GetClosestPeakIndex(double x)
    {
        if (getSize() == 0)
        {
            return std::nullopt;
        }
#ifdef ORIG
        int index = Array::BinarySearch(getXArray(), x);
#endif
        int index = std::binary_search(getXArray().begin(), getXArray().end(), x);
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
        //C# TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper
        // class reproduces the rectangular array initialization that is automatic in C#:
        //ORIGINAL LINE: double[,] data = new double[2, Size];
        std::vector<std::vector<double>> data = RectangularVectors::ReturnRectangularDoubleVector(2, getSize());
        //constexpr int size = sizeof(double);
#ifdef ORIG
        Buffer::BlockCopy(getXArray(), 0, data, 0, size * getSize());
        Buffer::BlockCopy(getYArray(), 0, data, size * getSize(), size * getSize());
#endif
        std::copy(data[0].begin(), data[0].begin()+this->getSize(), this->getXArray().begin());
        std::copy(data[1].begin(), data[1].begin()+this->getSize(), this->getYArray().begin());
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
        //int startingIndex = Array::BinarySearch(getXArray(), minX);
        int startingIndex = std::binary_search(getXArray().begin(), getXArray().end(), minX);
        if (startingIndex < 0)
        {
            startingIndex = ~startingIndex;
        }
        if (startingIndex >= getSize())
        {
            return 0;
        }
        //int endIndex = Array::BinarySearch(getXArray(), maxX);
        int endIndex = std::binary_search(getXArray().begin(), getXArray().end(), maxX);
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
        std::vector<MzPeak*> v;
        auto quantile = 1.0 - static_cast<double>(topNPeaks) / getSize();
        quantile = std::max((double) 0.0, quantile);
        quantile = std::min((double) 1.0 , quantile);
        //double cutoffYvalue = getYArray().Quantile(quantile);
        double cutoffYvalue = Math::Quantile(getYArray(), quantile);

        for (int i = 0; i < getSize(); i++)
        {
            if (getYArray()[i] >= cutoffYvalue)
            {
                //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                //yield return GetPeak(i);
                v.push_back(GetPeak(i));
            }
        }
        return v;
    }

    std::vector<MzPeak*> MzSpectrum::Extract(DoubleRange *xRange)
    {
        return Extract(xRange->getMinimum(), xRange->getMaximum());
    }

    std::vector<MzPeak*> MzSpectrum::Extract(double minX, double maxX)
    {
        std::vector<MzPeak*> v;
        //int ind = Array::BinarySearch(getXArray(), minX);
        int ind = std::binary_search(getXArray().begin(), getXArray().end(), minX);

        if (ind < 0)
        {
            ind = ~ind;
        }
        while (ind < getSize() && getXArray()[ind] <= maxX)
        {
            //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
            //yield return GetPeak(ind);
            v.push_back(GetPeak(ind));
            ind++;
        }
        return v;
    }

    std::vector<MzPeak*> MzSpectrum::FilterByY(double minY, double maxY)
    {
        std::vector<MzPeak*> v;        
        for (int i = 0; i < getSize(); i++)
        {
            if (getYArray()[i] >= minY && getYArray()[i] <= maxY)
            {
                //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                //yield return GetPeak(i);
                v.push_back(GetPeak(i));
            }
        }
        return v;
    }

    std::vector<MzPeak*> MzSpectrum::FilterByY(DoubleRange *yRange)
    {
        return FilterByY(yRange->getMinimum(), yRange->getMaximum());
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
        while (i != (int) mz1.size() && j != (int)mz2.size())
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
        for (; i < (int) mz1.size(); i++)
        {
            vector1.push_back(intensity1[i]);
            vector2.push_back(0);
        }
        for (; j < (int) mz2.size(); j++)
        {
            vector1.push_back(0);
            vector2.push_back(intensity2[j]);
        }

        //numerator of dot product
        double numerator = 0;
        for (i = 0; i < (int) vector1.size(); i++)
        {
            numerator += vector1[i] * vector2[i];
        }
        
        //denominator of dot product
#ifdef ORIG
        double denominator = std::sqrt(vector1.Sum([&] (std::any x)
        {
            return x * x;
        })) * std::sqrt(vector2.Sum([&] (std::any x)
        {
            return x * x;
        }));
#endif
        double d1 = 0.0;
        for ( auto x : vector1 ) {
            d1 += x*x;
        }
        double d2 = 0.0;
        for ( auto x : vector2 ) {
            d2 += x*x;
        }
        double denominator = std::sqrt(d1) * std::sqrt(d2);
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
