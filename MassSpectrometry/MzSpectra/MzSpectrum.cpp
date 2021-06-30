/* -*- Mode: C; c-basic-offset:4 ; -*- */
/*
 * Copyright (c) 2019-2020 University of Houston. All rights reserved.
 * $COPYRIGHT$
 *
 * Additional copyrights may follow
 *
 */
#include "MzSpectrum.h"
#include "MzPeak.h"
#include "../../Chemistry/ChemicalFormula.h"
#include "../../Chemistry/IsotopicDistribution.h"
#include "../../MzLibUtil/MzRange.h"
#include "IsotopicEnvelope.h"
#include "../../Chemistry/ClassExtensions.h"
#include "../../MzLibUtil/DoubleRange.h"
#include "../../MzLibUtil/Tolerance.h"

#include "Search.h"

#include "Sort.h"
#include "MzLibMath.h"
#include "RectangularVectors.h"

namespace MassSpectrometry
{
    static constexpr int numAveraginesToGenerate = 1500;

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
        privateXArraysize = value.size();
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

        std::copy (mzintensities[0].begin(), mzintensities[0].end(), privateXArray.begin());
        std::copy (mzintensities[1].begin(), mzintensities[1].end(), privateYArray.begin()  );
        peakList = std::vector<MzPeak*>(privateXArray.size());
    }

    MzSpectrum::MzSpectrum(std::vector<double> &mz, std::vector<double> &intensities, bool shouldCopy)
    {
        if (shouldCopy)
        {
            privateXArray.resize(mz.size());
            privateYArray.resize(intensities.size());
            privateXArraysize = mz.size();
            
            std::copy (mz.begin(), mz.end(), privateXArray.begin());
            std::copy (intensities.begin(), intensities.end(), privateYArray.begin()  );
        }
        else
        {
            privateXArray = mz;
            privateXArraysize = mz.size();
            
            privateYArray = intensities;
        }
        peakList = std::vector<MzPeak*>(privateXArray.size());
    }

    MzRange *MzSpectrum::getRange() const
    {
        if (privateXArraysize == 0)
        {
            return nullptr;
        }
        return new MzRange(getFirstX().value(), getLastX().value());
    }

    std::optional<double> MzSpectrum::getFirstX() const
    {
        if (privateXArraysize == 0)
        {
            return std::nullopt;
        }
        return std::make_optional(privateXArray[0]);
    }

    std::optional<double> MzSpectrum::getLastX() const
    {
        if (privateXArraysize == 0)
        {
            return std::nullopt;
        }
        return std::make_optional(privateXArray[privateXArraysize - 1]);
    }

    int MzSpectrum::getSize() const
    {
        return privateXArraysize;
    }

    std::optional<int> MzSpectrum::getIndexOfPeakWithHighesetY() 
    {
        if ( privateXArraysize == 0)
        {
            return std::nullopt;
        }
        if (!indexOfpeakWithHighestY.has_value())
        {
            auto maxval = std::max_element(privateYArray.begin(), privateYArray.end() );
            indexOfpeakWithHighestY = std::make_optional(std::distance(privateYArray.begin(), maxval ));
        }
        return indexOfpeakWithHighestY;
    }

    std::optional<double> MzSpectrum::getYofPeakWithHighestY() 
    {
        if (privateXArraysize == 0)
        {
            return std::nullopt;
        }
        int index = getIndexOfPeakWithHighesetY().value();
        return std::make_optional(privateYArray[index]);
    }

    std::optional<double> MzSpectrum::getXofPeakWithHighestY() 
    {
        if (privateXArraysize == 0)
        {
            return std::nullopt;
        }
        int index = getIndexOfPeakWithHighesetY().value();
        return std::make_optional(privateXArray[index]);
    }

    double MzSpectrum::getSumOfAllY() 
    {
        if (!sumOfAllY.has_value() )
        {
            double sum = 0.0;
            for ( auto y : privateYArray ) {
                sum +=  y;
            }
            sumOfAllY = std::make_optional ( sum );
        }
        return sumOfAllY.value();
    }

    std::vector<unsigned char> MzSpectrum::Get64Bitarray(std::vector<double> &array_Renamed)
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
        return Get64Bitarray(privateYArray);
    }

    std::vector<unsigned char> MzSpectrum::Get64BitXarray()
    {
        return Get64Bitarray(privateXArray);
    }

    std::string MzSpectrum::ToString()
    {
        return StringHelper::formatSimple("{0} (Peaks {1})", getRange()->ToString(), getSize());
    }

    std::vector<IsotopicEnvelope*> MzSpectrum::Deconvolute(MzRange *theRange,
                                                           int minAssumedChargeState,
                                                           int maxAssumedChargeState,
                                                           double deconvolutionTolerancePpm,
                                                           double intensityRatioLimit)
    {
        std::vector<IsotopicEnvelope*> isolatedMassesAndCharges; 
        if (privateXArraysize == 0)  {
            return isolatedMassesAndCharges;
        }

        auto indices = ExtractIndices(theRange->getMinimum(), theRange->getMaximum());
        for (auto candidateForMostIntensePeak : indices)
        {
            IsotopicEnvelope *bestIsotopeEnvelopeForThisPeak = nullptr;
            
            auto candidateForMostIntensePeakMz = privateXArray[candidateForMostIntensePeak];
            auto candidateForMostIntensePeakIntensity = privateYArray[candidateForMostIntensePeak];

            for (int chargeState = minAssumedChargeState; chargeState <= maxAssumedChargeState; chargeState++)
            {
                auto testMostIntenseMass = Chemistry::ClassExtensions::ToMass(candidateForMostIntensePeakMz, chargeState);
                int massIndex = BinarySearch(mostIntenseMasses, testMostIntenseMass);

                if (massIndex < 0) {
                    massIndex = ~massIndex;
                }
                if (massIndex == (int) mostIntenseMasses.size()) {
                    break;
                }
                
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
                for (int indexToLookAt=1; indexToLookAt < (int) allIntensities[massIndex].size(); indexToLookAt++) {
                    double theorMassThatTryingToFind = allMasses[massIndex][indexToLookAt] + differenceBetweenTheorAndActual;
                    auto closestPeakToTheorMass = GetClosestPeakIndex(Chemistry::ClassExtensions::ToMz(theorMassThatTryingToFind, chargeState));
                    auto closestPeakmz = privateXArray[closestPeakToTheorMass.value()];
                    
                    auto closestPeakIntensity = privateYArray[closestPeakToTheorMass.value()];
                    if (std::abs(Chemistry::ClassExtensions::ToMass(closestPeakmz, chargeState) - theorMassThatTryingToFind) / theorMassThatTryingToFind * 1e6 <= deconvolutionTolerancePpm
                        && Peak2satisfiesRatio(allIntensities[massIndex][0], allIntensities[massIndex][indexToLookAt], candidateForMostIntensePeakIntensity, closestPeakIntensity, intensityRatioLimit)
                        && (std::find(listOfPeaks.begin(), listOfPeaks.end(), std::make_tuple(closestPeakmz, closestPeakIntensity)) == listOfPeaks.end()))
                    {
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
                    if ( bestIsotopeEnvelopeForThisPeak != nullptr ) {
                        delete bestIsotopeEnvelopeForThisPeak;
                    }
                    bestIsotopeEnvelopeForThisPeak = test;
                }
                else {
                    delete test;
                }
            }

            if (bestIsotopeEnvelopeForThisPeak != nullptr && bestIsotopeEnvelopeForThisPeak->peaks.size() >= 2)
            {
                isolatedMassesAndCharges.push_back(bestIsotopeEnvelopeForThisPeak);
            }
            else {
                if ( bestIsotopeEnvelopeForThisPeak != nullptr ) {
                    delete bestIsotopeEnvelopeForThisPeak;
                }
            }
        }

        std::unordered_set<double> seen;
        std::vector<IsotopicEnvelope*> y;
        std::sort(isolatedMassesAndCharges.begin(), isolatedMassesAndCharges.end(), [&] ( IsotopicEnvelope *lhs, IsotopicEnvelope *rhs) {
                return (ScoreIsotopeEnvelope(lhs) > ScoreIsotopeEnvelope(rhs));
            });
        for (IsotopicEnvelope* ok : isolatedMassesAndCharges ) {
            bool found = false;
            for ( auto p : ok->peaks ) {
                if (seen.find(std::get<0>(p)) != seen.end()) {
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
            y.push_back(ok);
        }
        return y;
    }

    std::vector<int> MzSpectrum::ExtractIndices(double minX, double maxX)
    {
        std::vector<int> v;
        int ind = BinarySearch(privateXArray, minX);
        if (ind < 0)
        {
            ind = ~ind;
        }
        while (ind < privateXArraysize && privateXArray[ind] <= maxX)
        {
            v.push_back(ind);
            ind++;
        }
        return v;
    }

    std::optional<int> MzSpectrum::GetClosestPeakIndex(double x)
    {
        if ( privateXArraysize == 0)
        {
            return std::nullopt;
        }
        int index = BinarySearch(privateXArray, x);
        if (index >= 0)
        {
            return std::make_optional(index);
        }
        index = ~index;

        if (index >= privateXArraysize )
        {
            return std::make_optional(index - 1);
        }
        if (index == 0)
        {
            return std::make_optional(index);
        }

        if (x - privateXArray[index - 1] > privateXArray[index] - x)
        {
            return std::make_optional(index);
        }
        return std::make_optional(index - 1);
    }

    void MzSpectrum::ReplaceXbyApplyingFunction(std::function<double(MzPeak*)> convertor)
    {
        for (int i = 0; i < privateXArraysize; i++)
        {
            privateXArray[i] = convertor(GetPeak(i));
        }
        peakList = std::vector<MzPeak*>(privateXArraysize );
    }

    std::vector<std::vector<double>> MzSpectrum::CopyTo2DArray()
    {
        std::vector<std::vector<double>> data = RectangularVectors::ReturnRectangularDoubleVector(2, privateXArraysize );
        std::copy(data[0].begin(), data[0].begin()+this->privateXArraysize, this->privateXArray.begin());
        std::copy(data[1].begin(), data[1].begin()+this->privateXArraysize, this->privateYArray.begin());
        return data;
    }

    std::optional<double> MzSpectrum::GetClosestPeakXvalue(double x)
    {
        if ( privateXArraysize == 0)
        {
            return std::nullopt;
        }
        return std::make_optional(privateXArray[GetClosestPeakIndex(x).value()]);
    }

    int MzSpectrum::NumPeaksWithinRange(double minX, double maxX)
    {
        int startingIndex = BinarySearch(privateXArray, minX);
        if (startingIndex < 0)
        {
            startingIndex = ~startingIndex;
        }

        if (startingIndex >= privateXArraysize)
        {
            return 0;
        }

        int endIndex = BinarySearch(privateXArray, maxX);
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
        double quantile = 1.0 - static_cast<double>(topNPeaks) / privateXArraysize ;
        quantile = std::max((double) 0.0, quantile);
        quantile = std::min((double) 1.0 , quantile);
        double cutoffYvalue = Math::Quantile(privateYArray, quantile);
        for (int i = 0; i < privateXArraysize; i++)
        {
            if (privateYArray[i] >= cutoffYvalue)
            {
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
        int ind = BinarySearch(privateXArray, minX);

        if (ind < 0)
        {
            ind = ~ind;
        }
        while (ind < privateXArraysize && privateXArray[ind] <= maxX)
        {
            //yield return GetPeak(ind);
            v.push_back(GetPeak(ind));
            ind++;
        }
        return v;
    }

    std::vector<MzPeak*> MzSpectrum::FilterByY(double minY, double maxY)
    {
        std::vector<MzPeak*> v;        
        for (int i = 0; i < privateXArraysize; i++)
        {
            if (privateYArray[i] >= minY && privateYArray[i] <= maxY)
            {
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
        std::vector<double> mz1 = privateXArray;
        std::vector<double> intensity1 = privateYArray;
        
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

    bool MzSpectrum::Peak2satisfiesRatio(double peak1theorIntensity, double peak2theorIntensity, double peak1intensity,
                                         double peak2intensity, double intensityRatio)
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
        return new MzPeak(privateXArray[index], privateYArray[index]);
    }
}
