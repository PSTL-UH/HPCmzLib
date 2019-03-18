#pragma once

#include "IMzSpectrum.h"
#include "../../Spectra/Spectrum.h"
#include "../../MzLibUtil/MzRange.h"
#include "IsotopicEnvelope.h"
#include "../../Chemistry/ClassExtensions.h"
#include "IMzPeak.h"
#include "../../MzLibUtil/Tolerance.h"
#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <tuple>
#include <type_traits>
#include "stringhelper.h"
#include "floating_point_to_integer.h"

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work copyright 2016 Stefan Solntsev
//
// This file (MzSpectrum.cs) is part of MassSpectrometry.
//
// MassSpectrometry is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MassSpectrometry is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with MassSpectrometry. If not, see <http://www.gnu.org/licenses/>.

using namespace Chemistry;
using namespace MzLibUtil;
using namespace Spectra;

namespace MassSpectrometry {
    template<typename TPeak>
    class MzSpectrum : public Spectrum<TPeak>, public IMzSpectrum<TPeak> {
        static_assert(std::is_base_of<IMzPeak, TPeak>::value, L"TPeak must inherit from IMzPeak");

    private:
        static constexpr int numAveraginesToGenerate = 1500;
//C# TO C++ CONVERTER TODO TASK: Native C++ does not allow initialization of static non-const/integral fields in their declarations - choose the conversion option for separate .h and .cpp files:
        static std::vector<std::vector<double>> const allMasses = std::vector<std::vector<double>>(numAveraginesToGenerate);
//C# TO C++ CONVERTER TODO TASK: Native C++ does not allow initialization of static non-const/integral fields in their declarations - choose the conversion option for separate .h and .cpp files:
        static std::vector<std::vector<double>> const allIntensities = std::vector<std::vector<double>>(numAveraginesToGenerate);
//C# TO C++ CONVERTER TODO TASK: Native C++ does not allow initialization of static non-const/integral fields in their declarations - choose the conversion option for separate .h and .cpp files:
        static std::vector<double> const mostIntenseMasses = std::vector<double>(numAveraginesToGenerate);
//C# TO C++ CONVERTER TODO TASK: Native C++ does not allow initialization of static non-const/integral fields in their declarations - choose the conversion option for separate .h and .cpp files:
        static std::vector<double> const diffToMonoisotopic = std::vector<double>(numAveraginesToGenerate);

//C# TO C++ CONVERTER TODO TASK: Native C++ does not allow initialization of static non-const/integral fields in their declarations - choose the conversion option for separate .h and .cpp files:
        static std::vector<double> const mms = {1.0029, 2.0052, 3.0077, 4.01, 5.012, 6.0139, 7.0154, 8.0164};

//C# TO C++ CONVERTER TODO TASK: Native C++ does not allow initialization of static non-const/integral fields in their declarations - choose the conversion option for separate .h and .cpp files:
        static const std::vector<std::tuple<double, std::vector<double>>> intensityFractions = std::vector<std::tuple<double, std::vector<double>>>();


    private:
        class StaticConstructor {
        public:
            StaticConstructor();
        };

    private:
        static MzSpectrum::StaticConstructor staticConstructor;

    protected:
        MzSpectrum(std::vector<std::vector<double>> &mzintensities) : Spectrum<TPeak>(mzintensities) {
        }

        MzSpectrum(std::vector<double> &mz, std::vector<double> &intensities, bool shouldCopy) : Spectrum<TPeak>(mz, intensities, shouldCopy) {
        }

    public:
        MzRange *getRange() const override {
            return new MzRange(getFirstX(), getLastX());
        }

        static std::vector<unsigned char> Get64Bitarray(std::vector<double> &array_Renamed) {
            auto mem = new MemoryStream();
            for (auto okk : array_Renamed) {
                std::vector<unsigned char> ok = BitConverter::GetBytes(okk);
                mem->Write(ok, 0, ok.size());
            }
            mem->Position = 0;

            delete mem;
            return mem->ToArray();
        }

        std::vector<unsigned char> Get64BitYarray() override {
            return Get64Bitarray(getYArray());
        }

        std::vector<unsigned char> Get64BitXarray() override {
            return Get64Bitarray(getXArray());
        }

        std::string ToString() override {
            return StringHelper::formatSimple(L"{0} (Peaks {1})", getRange(), getSize());
        }

        // Mass tolerance must account for different isotope spacing!
        std::vector<IsotopicEnvelope*> Deconvolute(MzRange *theRange, int maxAssumedChargeState, double deconvolutionTolerancePpm, double intensityRatioLimit) override {
            auto isolatedMassesAndCharges = std::vector<IsotopicEnvelope*>();

            for (auto candidateForMostIntensePeak : ExtractIndices(theRange->Minimum, theRange->Maximum)) {
                IsotopicEnvelope *bestIsotopeEnvelopeForThisPeak = nullptr;

                auto candidateForMostIntensePeakMz = getXArray()[candidateForMostIntensePeak];
                //Console.WriteLine("candidateForMostIntensePeakMz: " + candidateForMostIntensePeakMz);
                auto candidateForMostIntensePeakIntensity = getYArray()[candidateForMostIntensePeak];

                for (int chargeState = 1; chargeState <= maxAssumedChargeState; chargeState++) {
                    //Console.WriteLine(" chargeState: " + chargeState);
                    auto testMostIntenseMass = Chemistry::ClassExtensions::ToMass(candidateForMostIntensePeakMz, chargeState);

                    auto massIndex = Array::BinarySearch(mostIntenseMasses, testMostIntenseMass);
                    if (massIndex < 0) {
                        massIndex = ~massIndex;
                    }
                    if (massIndex == mostIntenseMasses.size()) {
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
                    for (int indexToLookAt = 1; indexToLookAt < allIntensities[massIndex].size(); indexToLookAt++) {
                        //Console.WriteLine("   indexToLookAt: " + indexToLookAt);
                        double theorMassThatTryingToFind = allMasses[massIndex][indexToLookAt] + differenceBetweenTheorAndActual;
                        //Console.WriteLine("   theorMassThatTryingToFind: " + theorMassThatTryingToFind);
                        //Console.WriteLine("   theorMassThatTryingToFind.ToMz(chargeState): " + theorMassThatTryingToFind.ToMz(chargeState));
                        auto closestPeakToTheorMass = GetClosestPeakIndex(Chemistry::ClassExtensions::ToMz(theorMassThatTryingToFind, chargeState));
                        auto closestPeakmz = getXArray()[closestPeakToTheorMass];
                        //Console.WriteLine("   closestPeakmz: " + closestPeakmz);
                        auto closestPeakIntensity = getYArray()[closestPeakToTheorMass];
                        if (std::abs(Chemistry::ClassExtensions::ToMass(closestPeakmz, chargeState) - theorMassThatTryingToFind) / theorMassThatTryingToFind * 1e6 <= deconvolutionTolerancePpm && Peak2satisfiesRatio(allIntensities[massIndex][0], allIntensities[massIndex][indexToLookAt], candidateForMostIntensePeakIntensity, closestPeakIntensity, intensityRatioLimit) && !std::find(listOfPeaks.begin(), listOfPeaks.end(), (closestPeakmz, closestPeakIntensity)) != listOfPeaks.end())) {
                            //Found a match to an isotope peak for this charge state!
                            //Console.WriteLine(" *   Found a match to an isotope peak for this charge state!");
                            //Console.WriteLine(" *   chargeState: " + chargeState);
                            //Console.WriteLine(" *   closestPeakmz: " + closestPeakmz);
                            listOfPeaks.push_back((closestPeakmz, closestPeakIntensity));
                            totalIntensity += closestPeakIntensity;
                            listOfRatios.push_back(allIntensities[massIndex][indexToLookAt] / closestPeakIntensity);
                        }
                        else {
                            break;
                        }
                    }

                    auto extrapolatedMonoisotopicMass = testMostIntenseMass - diffToMonoisotopic[massIndex]; // Optimized for proteoforms!!
                    auto lowestMass = listOfPeaks.Min([&] (std::any b) {
                        b::Item1;
                    }).ToMass(chargeState); // But may actually observe this small peak
                    auto monoisotopicMass = std::abs(extrapolatedMonoisotopicMass - lowestMass) < 0.5 ? lowestMass : extrapolatedMonoisotopicMass;

                    IsotopicEnvelope *test = new IsotopicEnvelope(listOfPeaks, monoisotopicMass, chargeState, totalIntensity, MathNet::Numerics::Statistics::Statistics::StandardDeviation(listOfRatios), massIndex);

                    if (listOfPeaks.size() >= 2 && ScoreIsotopeEnvelope(test) > ScoreIsotopeEnvelope(bestIsotopeEnvelopeForThisPeak)) {
                        //Console.WriteLine("Better charge state is " + test.charge);
                        //Console.WriteLine("peaks: " + string.Join(",", listOfPeaks.Select(b => b.Item1)));
                        bestIsotopeEnvelopeForThisPeak = test;
                    }

//C# TO C++ CONVERTER TODO TASK: A 'delete test' statement was not added since test was passed to a method or constructor. Handle memory management manually.
                }

                if (bestIsotopeEnvelopeForThisPeak != nullptr && bestIsotopeEnvelopeForThisPeak->peaks.size() >= 2) {
                    isolatedMassesAndCharges.push_back(bestIsotopeEnvelopeForThisPeak);
                }
            }

            std::unordered_set<double> seen = std::unordered_set<double>();
            for (auto ok : isolatedMassesAndCharges.OrderByDescending([&] (std::any b) {
                ScoreIsotopeEnvelope(b);
            })) {
                if (seen.Overlaps(ok::peaks->Select([&] (std::any b) {
                    b::Item1;
                }))) {
                    continue;
                }
                for (auto ah : ok::peaks->Select([&] (std::any b) {
                    b::Item1;
                })) {
                    seen.insert(ah);
                }
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                yield return ok;
            }
        }

        std::vector<std::tuple<std::vector<IMzPeak*>, int>> DeconvoluteOld(MzRange *theRange, int maxAssumedChargeState, Tolerance *massTolerance, double intensityRatio) override {
            auto isolatedMassesAndCharges = std::vector<std::tuple<std::vector<IMzPeak*>, int>>();

            for (auto peak : Extract(theRange)) {
                // Always assume the current peak is a monoisotopic peak!

                std::vector<IMzPeak*> bestListOfPeaks = std::vector<IMzPeak*>();
                int bestChargeState = 1;
                for (int chargeState = 1; chargeState <= maxAssumedChargeState; chargeState++) {
                    auto listOfPeaksForThisChargeState = std::vector<IMzPeak*> {peak};
                    auto mMass = Chemistry::ClassExtensions::ToMass(peak->getMz(), chargeState);
                    for (int mm = 1; mm <= mms.size(); mm++) {
                        double diffToNextMmPeak = mms[mm - 1];
                        double theorMass = mMass + diffToNextMmPeak;
                        auto closestpeak = GetPeak(GetClosestPeakIndex(Chemistry::ClassExtensions::ToMz(theorMass, chargeState)));
                        if (massTolerance->Within(Chemistry::ClassExtensions::ToMass(closestpeak->getMz(), chargeState), theorMass) && SatisfiesRatios(mMass, mm, peak, closestpeak, intensityRatio)) {
                            // Found a match to an isotope peak for this charge state!
                            listOfPeaksForThisChargeState.push_back(closestpeak);
                        }
                        else {
                            break;
                        }
                    }
                    if (listOfPeaksForThisChargeState.size() >= bestListOfPeaks.size()) {
                        bestListOfPeaks = listOfPeaksForThisChargeState;
                        bestChargeState = chargeState;
                    }
                }
                if (bestListOfPeaks.size() >= 2) {
                    isolatedMassesAndCharges.push_back(std::tuple<std::vector<IMzPeak*>, int>(bestListOfPeaks, bestChargeState));
                }
            }

            std::vector<double> seen = std::vector<double>();
            while (isolatedMassesAndCharges.Any()) {
                // Pick longest
                auto longest = isolatedMassesAndCharges.OrderByDescending([&] (std::any b) {
                    b::Item1->Count;
                }).First();
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                yield return longest;
                isolatedMassesAndCharges.Remove(longest);
                isolatedMassesAndCharges.RemoveAll([&] (std::any b) {
                    b::Item1->Intersect(longest->Item1)->Any();
                });
            }
        }


    private:
        double ScoreIsotopeEnvelope(IsotopicEnvelope *b) {
            if (b == nullptr) {
                return 0;
            }
            return b->totalIntensity / std::pow(b->stDev, 0.13) * std::pow(b->peaks.size(), 0.4) / std::pow(b->charge, 0.06);
        }

        bool Peak2satisfiesRatio(double peak1theorIntensity, double peak2theorIntensity, double peak1intensity, double peak2intensity, double intensityRatio) {
            auto comparedShouldBe = peak1intensity / peak1theorIntensity * peak2theorIntensity;

            if (peak2intensity < comparedShouldBe / intensityRatio || peak2intensity > comparedShouldBe * intensityRatio) {
                return false;
            }

            return true;
        }

        bool SatisfiesRatios(double mMass, int mm, IMzPeak *ye, IMzPeak *closestpeak, double intensityRatio) {
            double bestDiff = std::numeric_limits<double>::max();
            std::vector<double> bestFracList;
            for (int i = 0; i < intensityFractions.size(); i++) {
                auto diff = std::abs(mMass - std::get<0>(intensityFractions[i]));
                if (diff < bestDiff) {
                    bestDiff = diff;
                    bestFracList = std::get<1>(intensityFractions[i]);
                }
            }
            if (bestFracList.empty() || bestFracList.size() <= mm) {
                return false;
            }

            auto theMM = bestFracList[0];
            auto theCompared = bestFracList[mm];

            auto comparedShouldBe = ye->getIntensity() / theMM * theCompared;

            if (closestpeak->getIntensity() < comparedShouldBe / intensityRatio || closestpeak->getIntensity() > comparedShouldBe * intensityRatio) {
                return false;
            }

            return true;
        }

    };
}
