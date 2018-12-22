#pragma once

#include "ISpectrum.h"
#include "../MzLibUtil/DoubleRange.h"
#include "IPeak.h"
#include <vector>
#include <functional>
#include <optional>
#include <type_traits>

// Copyright 2016 Stefan Solnts// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work copyright 2016 Stefan Solntsev
//
// This file (Spectrum.cs) is part of MassSpectrometry.
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

using namespace MathNet::Numerics::Statistics;
using namespace MzLibUtil;

namespace Spectra {
    /// <summary>
    /// Spectrum that is defined by its arrays
    /// </summary>
    /// <typeparam name="TPeak"></typeparam>
    template<typename TPeak>
    class Spectrum : public ISpectrum<TPeak> {
        static_assert(std::is_base_of<IPeak, TPeak>::value, L"TPeak must inherit from IPeak");

    private:
        std::vector<double> privateXArray;
        std::vector<double> privateYArray;

//        #region Private Fields

        std::vector<TPeak> peakList;
        std::optional<int> indexOfpeakWithHighestY;
        std::optional<double> sumOfAllY;

//        #endregion Private Fields

//        #region Protected Constructors

    protected:
        Spectrum(std::vector<double> &x, std::vector<double> &y, bool shouldCopy) {
            if (shouldCopy) {
                setXArray(std::vector<double>(x.size()));
                setYArray(std::vector<double>(y.size()));
                Array::Copy(x, getXArray(), x.size());
                Array::Copy(y, getYArray(), y.size());
            }
            else {
                setXArray(x);
                setYArray(y);
            }
            peakList = std::vector<TPeak>(getSize());
        }

        Spectrum(std::vector<std::vector<double>> &xy) {
            auto count = (xy.size() == 0 ? 0 : xy[0].size());

            setXArray(std::vector<double>(count));
            setYArray(std::vector<double>(count));
            Buffer::BlockCopy(xy, 0, getXArray(), 0, sizeof(double) * count);
            Buffer::BlockCopy(xy, sizeof(double) * count, getYArray(), 0, sizeof(double) * count);
            peakList = std::vector<TPeak>(getSize());
        }

//        #endregion Protected Constructors

//        #region Public Properties

    public:
        std::vector<double> getXArray() const override {
            return privateXArray;
        }
        void setXArray(const std::vector<double> &value) override {
            privateXArray = value;
        }
        std::vector<double> getYArray() const override {
            return privateYArray;
        }
        void setYArray(const std::vector<double> &value) override {
            privateYArray = value;
        }
        double getFirstX() const override {
            return getXArray()[0];
        }

        double getLastX() const override {
            return getXArray()[getSize() - 1];
        }

        int getSize() const override {
            return getXArray().size();
        }

        int getIndexOfPeakWithHighesetY() const {
            if (!indexOfpeakWithHighestY.HasValue) {
                indexOfpeakWithHighestY = std::make_optional(Array::IndexOf(getYArray(), getYArray().Max()));
            }
            return indexOfpeakWithHighestY.Value;
        }

        double getYofPeakWithHighestY() const override {
            return getYArray()[getIndexOfPeakWithHighesetY()];
        }

        double getXofPeakWithHighestY() const override {
            return getXArray()[getIndexOfPeakWithHighesetY()];
        }

        double getSumOfAllY() const override {
            if (!sumOfAllY.HasValue) {
                sumOfAllY = getYArray().Sum();
            }
            return sumOfAllY.Value;
        }

        DoubleRange *getRange() const override {
            return new DoubleRange(getFirstX(), getLastX());
        }

//        #endregion Public Properties

//        #region Public Methods

        void ReplaceXbyApplyingFunction(std::function<double(IPeak*)> convertor) override {
            for (int i = 0; i < getSize(); i++) {
                getXArray()[i] = convertor(GetPeak(i));
            }
            peakList = std::vector<TPeak>(getSize());
        }

        std::vector<std::vector<double>> CopyTo2DArray() override {
//C# TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper class reproduces the rectangular array initialization that is automatic in C#:
//ORIGINAL LINE: double[,] data = new double[2, Size];
            std::vector<std::vector<double>> data = RectangularVectors::ReturnRectangularDoubleVector(2, getSize());
            constexpr int size = sizeof(double);
            Buffer::BlockCopy(getXArray(), 0, data, 0, size * getSize());
            Buffer::BlockCopy(getYArray(), 0, data, size * getSize(), size * getSize());
            return data;
        }

        int GetClosestPeakIndex(double x) override {
            int index = Array::BinarySearch(getXArray(), x);
            if (index >= 0) {
                return index;
            }
            index = ~index;

            if (index >= getSize()) {
                return index - 1;
            }
            if (index == 0) {
                return index;
            }

            if (x - getXArray()[index - 1] > getXArray()[index] - x) {
                return index;
            }
            return index - 1;
        }

        double GetClosestPeakXvalue(double x) override {
            return getXArray()[GetClosestPeakIndex(x)];
        }

        int NumPeaksWithinRange(double minX, double maxX) override {
            int startingIndex = Array::BinarySearch(getXArray(), minX);
            if (startingIndex < 0) {
                startingIndex = ~startingIndex;
            }
            if (startingIndex >= getSize()) {
                return 0;
            }
            int endIndex = Array::BinarySearch(getXArray(), maxX);
            if (endIndex < 0) {
                endIndex = ~endIndex;
            }
            if (endIndex == 0) {
                return 0;
            }

            return endIndex - startingIndex;
        }

        std::vector<TPeak> FilterByNumberOfMostIntense(int topNPeaks) override {
            auto quantile = 1.0 - static_cast<double>(topNPeaks) / getSize();
            quantile = std::max(0, quantile);
            quantile = std::min(1, quantile);
            double cutoffYvalue = getYArray().Quantile(quantile);

            for (int i = 0; i < getSize(); i++) {
                if (getYArray()[i] >= cutoffYvalue) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                    yield return GetPeak(i);
                }
            }
        }

        std::vector<TPeak> Extract(DoubleRange *xRange) override {
            return Extract(xRange->Minimum, xRange->Maximum);
        }

        std::vector<TPeak> Extract(double minX, double maxX) override {
            int ind = Array::BinarySearch(getXArray(), minX);
            if (ind < 0) {
                ind = ~ind;
            }
            while (ind < getSize() && getXArray()[ind] <= maxX) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                yield return GetPeak(ind);
                ind++;
            }
        }

        std::vector<int> ExtractIndices(double minX, double maxX) {
            int ind = Array::BinarySearch(getXArray(), minX);
            if (ind < 0) {
                ind = ~ind;
            }
            while (ind < getSize() && getXArray()[ind] <= maxX) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                yield return ind;
                ind++;
            }
        }

        std::vector<TPeak> FilterByY(double minY, double maxY) override {
            for (int i = 0; i < getSize(); i++) {
                if (getYArray()[i] >= minY && getYArray()[i] <= maxY) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                    yield return GetPeak(i);
                }
            }
        }

        std::vector<TPeak> FilterByY(DoubleRange *yRange) override {
            return FilterByY(yRange->Minimum, yRange->Maximum);
        }

//        #endregion Public Methods

//        #region Protected Methods

    protected:
        virtual TPeak GeneratePeak(int index) = 0;

        TPeak GetPeak(int index) {
            if (peakList[index] == nullptr) {
                peakList[index] = GeneratePeak(index);
            }
            return peakList[index];
        }

//        #endregion Protected Methods
    };
}
