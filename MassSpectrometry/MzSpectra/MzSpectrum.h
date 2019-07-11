#pragma once

#include <string>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <cmath>
#include <functional>
#include <optional>
#include "stringhelper.h"
#include "floating_point_to_integer.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
//namespace MassSpectrometry { class MzPeak; }
#include "MzPeak.h"
//namespace MassSpectrometry { class IsotopicEnvelope; }
#include "IsotopicEnvelope.h"
//namespace MzLibUtil { class MzRange; }
//namespace MzLibUtil { class DoubleRange; }
//namespace MzLibUtil { class Tolerance; }
#include "MzLibUtil.h"
using namespace MzLibUtil;

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

#include "../../Chemistry/Chemistry.h"
using namespace Chemistry;

//using namespace MathNet::Numerics::Statistics;

namespace MassSpectrometry
{
    class MzSpectrum
    {
    private:
        std::vector<double> privateXArray;
        std::vector<double> privateYArray;

        //static constexpr int numAveraginesToGenerate = 1500;
        static std::vector<std::vector<double>> allMasses;
        static std::vector<std::vector<double>> allIntensities;
        static std::vector<double> mostIntenseMasses;
        static std::vector<double> diffToMonoisotopic;

        std::vector<MzPeak*> peakList;
        std::optional<int> indexOfpeakWithHighestY;
        std::optional<double> sumOfAllY;


    public:
        std::vector<double> getXArray() const;
        void setXArray(const std::vector<double> &value);
        std::vector<double> getYArray() const;
        void setYArray(const std::vector<double> &value);

    private:
        class StaticConstructor
        {
        public:
            StaticConstructor();
        };

    private:
        static MzSpectrum::StaticConstructor staticConstructor;


    public:
        MzSpectrum(std::vector<std::vector<double>> &mzintensities);

        MzSpectrum(std::vector<double> &mz, std::vector<double> &intensities, bool shouldCopy);

        MzRange *getRange() const;

        std::optional<double> getFirstX() const;

        std::optional<double> getLastX() const;

        int getSize() const;

        std::optional<int> getIndexOfPeakWithHighesetY() const;

        std::optional<double> getYofPeakWithHighestY() const;

        std::optional<double> getXofPeakWithHighestY() const;

        double getSumOfAllY() const;

        static std::vector<unsigned char> Get64Bitarray(std::vector<double> array);

        std::vector<unsigned char> Get64BitYarray();

        std::vector<unsigned char> Get64BitXarray();

        std::string ToString();

        // Mass tolerance must account for different isotope spacing!
        std::vector<IsotopicEnvelope*> Deconvolute(MzRange *theRange, int minAssumedChargeState, int maxAssumedChargeState, double deconvolutionTolerancePpm, double intensityRatioLimit);

        std::vector<int> ExtractIndices(double minX, double maxX);

        std::optional<int> GetClosestPeakIndex(double x);

        void ReplaceXbyApplyingFunction(std::function<double(MzPeak*)> convertor);

        virtual std::vector<std::vector<double>> CopyTo2DArray();

        std::optional<double> GetClosestPeakXvalue(double x);

        int NumPeaksWithinRange(double minX, double maxX);

        std::vector<MzPeak*> FilterByNumberOfMostIntense(int topNPeaks);

        std::vector<MzPeak*> Extract(DoubleRange *xRange);

        std::vector<MzPeak*> Extract(double minX, double maxX);

        std::vector<MzPeak*> FilterByY(double minY, double maxY);

        std::vector<MzPeak*> FilterByY(DoubleRange *yRange);

        double CalculateDotProductSimilarity(MzSpectrum *spectrumToCompare, Tolerance *tolerance);

    private:
        double ScoreIsotopeEnvelope(IsotopicEnvelope *b);

        bool Peak2satisfiesRatio(double peak1theorIntensity, double peak2theorIntensity, double peak1intensity, double peak2intensity, double intensityRatio);

        MzPeak *GetPeak(int index);

        MzPeak *GeneratePeak(int index);
    };
}
