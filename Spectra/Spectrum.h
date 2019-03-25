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

//using namespace MathNet::Numerics::Statistics;
#include "RectangularVectors.h"
#include "MzLibUtil.h"
using namespace MzLibUtil;
#include "Math.h"

namespace Spectra {
    /// <summary>
    /// Spectrum that is defined by its arrays
    /// </summary>
    /// <typeparam name="TPeak"></typeparam>
    template<typename TPeak>
    class Spectrum : public ISpectrum<TPeak> {
#ifndef NDEBUG
        static_assert(std::is_base_of<IPeak, TPeak>::value, "TPeak must inherit from IPeak");
#endif
        
    private:
        std::vector<double> privateXArray;
        std::vector<double> privateYArray;
        
        std::vector<TPeak> peakList;
        mutable std::optional<int> indexOfpeakWithHighestY;
        std::optional<double> sumOfAllY;

    protected:
        Spectrum(std::vector<double> x, std::vector<double> y, bool shouldCopy) {
            if (shouldCopy) {
                setXArray(std::vector<double>(x.size()));
                setYArray(std::vector<double>(y.size()));
                // Array::Copy(x, getXArray(), x.size());
                // Array::Copy(y, getYArray(), y.size());
                std::copy (x.begin(), x.end(), privateXArray.begin());
                std::copy (y.begin(), y.end(), privateYArray.begin());
            }
            else {
                setXArray(x);
                setYArray(y);
            }
            peakList = std::vector<TPeak>(getSize());
        }

        Spectrum(std::vector<std::vector<double>> xy) {
            auto count = (xy.size() == 0 ? 0 : xy[1].size());

            setXArray(std::vector<double>(count));
            setYArray(std::vector<double>(count));
            // Buffer::BlockCopy(xy, 0, getXArray(), 0, sizeof(double) * count);
            // Buffer::BlockCopy(xy, sizeof(double)*count, getYArray(), 0, sizeof(double)*count);
            std::copy (xy[0].begin(), xy[0].end(), privateXArray.begin()); 
            std::copy (xy[1].begin(), xy[1].end(), privateYArray.begin()); 
            peakList = std::vector<TPeak>(getSize());
        }

    public:
        std::vector<double> getXArray() const override {
            return privateXArray;
        }
        void setXArray(const std::vector<double> &value)  {
            privateXArray = value;
        }
        std::vector<double> getYArray() const override {
            return privateYArray;
        }
        void setYArray(const std::vector<double> &value)  {
            privateYArray = value;
        }
        double getFirstX() const override {
            return privateXArray[0];
        }

        double getLastX() const override {
            return privateXArray[getSize() - 1];
        }

        int getSize() const override {
            return privateXArray.size();
        }

        std::optional<int> getIndexOfPeakWithHighesetY()  {
            if (!indexOfpeakWithHighestY.has_value()) {
                //indexOfpeakWithHighestY = std::make_optional(Array::IndexOf(getYArray(), getYArray().Max()));
                int index = std::distance(privateYArray.begin(), std::max_element(privateYArray.begin(), privateYArray.end()));
                indexOfpeakWithHighestY = std::make_optional(index);
                return indexOfpeakWithHighestY;
            }
            return std::nullopt;
        }

        //double getYofPeakWithHighestY() const override {
        double getYofPeakWithHighestY() override {
            // return getYArray()[getIndexOfPeakWithHighesetY()];
            if ( getIndexOfPeakWithHighesetY().has_value() ) {
                return getYArray()[getIndexOfPeakWithHighesetY().value()];
            }
            return -1.0;        
        }

        //double getXofPeakWithHighestY() const override {
        double getXofPeakWithHighestY() override {
            //return getXArray()[getIndexOfPeakWithHighesetY()];
            if ( getIndexOfPeakWithHighesetY().has_value() ) {
                return getXArray()[getIndexOfPeakWithHighesetY().value()];
            }
            return -1.0;        
        }

        double getSumOfAllY() {
            if (!sumOfAllY.has_value()) {
                // sumOfAllY = privateYArray.Sum();
                double s = 0.0;
                std::for_each(privateYArray.begin(), privateYArray.end(), [&] (double a) {
                        s += a;
                    });
                sumOfAllY = std::make_optional(s);
            }
            return sumOfAllY.value();
        }

        DoubleRange *getRange() const override {
            return new DoubleRange(getFirstX(), getLastX());
        }

        void ReplaceXbyApplyingFunction(std::function<double(IPeak *)> convertor) override {
            for (int i = 0; i < getSize(); i++) {
                TPeak t = GetPeak(i);
                getXArray()[i] = convertor(&t);
            }
            peakList = std::vector<TPeak>(getSize());
        }

        std::vector<std::vector<double>> CopyTo2DArray() override {
            //C# TO C++ CONVERTER NOTE: The following call to the 'RectangularVectors' helper
            // class reproduces the rectangular array initialization that is automatic in C#:
            //ORIGINAL LINE: double[,] data = new double[2, Size];
            std::vector<std::vector<double>> data = RectangularVectors::ReturnRectangularDoubleVector(2, getSize());
            // Buffer::BlockCopy(getXArray(), 0, data, 0, size * getSize());
            // Buffer::BlockCopy(getYArray(), 0, data, size * getSize(), size * getSize());
            std::copy(data[0].begin(), data[0].begin()+getSize(), privateXArray.begin());
            std::copy(data[1].begin(), data[1].begin()+getSize(), privateYArray.begin());
            return data;
        }

        int GetClosestPeakIndex(double x) override {
            // int index = Array::BinarySearch(getXArray(), x);
            int index = std::binary_search(privateXArray.begin(), privateXArray.end(), x);
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

            if (x - privateXArray[index - 1] > privateXArray[index] - x) {
                return index;
            }
            return index - 1;
        }

        double GetClosestPeakXvalue(double x) override {
            return getXArray()[GetClosestPeakIndex(x)];
        }

        int NumPeaksWithinRange(double minX, double maxX) override {
            // int startingIndex = Array::BinarySearch(getXArray(), minX);
            int startingIndex = std::binary_search(privateXArray.begin(), privateXArray.end(), minX);
            if (startingIndex < 0) {
                startingIndex = ~startingIndex;
            }
            if (startingIndex >= getSize()) {
                return 0;
            }
            // int endIndex = Array::BinarySearch(getXArray(), maxX);
            int endIndex = std::binary_search(privateXArray.begin(), privateXArray.end(), maxX);
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
            quantile = std::max((double)0.0, quantile);
            quantile = std::min((double)1.0, quantile);
            //double cutoffYvalue = getYArray().Quantile(quantile);
            double cutoffYvalue = Math::Quantile(getYArray(), quantile);
            std::vector<TPeak> t;
            
            for (int i = 0; i < getSize(); i++) {
                if (getYArray()[i] >= cutoffYvalue) {
                    //yield return GetPeak(i);
                    t.push_back (GetPeak(i));
                }
            }
            return t;
        }

        std::vector<TPeak> Extract(DoubleRange *xRange) override {
            return Extract(xRange->getMinimum(), xRange->getMaximum());
        }

        std::vector<TPeak> Extract(double minX, double maxX) override {
            // int ind = Array::BinarySearch(getXArray(), minX);
            int ind = std::binary_search(privateXArray.begin(), privateXArray.end(), minX);
            if (ind < 0) {
                ind = ~ind;
            }
            std::vector<TPeak> tt;
            while (ind < getSize() && privateXArray[ind] <= maxX) {
                //yield return GetPeak(ind);
                tt.push_back (GetPeak(ind));
                ind++;
            }
            return tt;
        }

        std::vector<int> ExtractIndices(double minX, double maxX) {
            // int ind = Array::BinarySearch(getXArray(), minX);
            int ind = std::binary_search(privateXArray.begin(), privateXArray.end(), minX);
            if (ind < 0) {
                ind = ~ind;
            }
            std::vector<int> it;
            while (ind < getSize() && privateXArray[ind] <= maxX) {
                //yield return ind;
                it.push_back (ind);
                ind++;
            }
            return it;
        }

        std::vector<TPeak> FilterByY(double minY, double maxY) override {
            std::vector<TPeak> t;
            for (int i = 0; i < getSize(); i++) {
                if (getYArray()[i] >= minY && privateYArray[i] <= maxY) {
                    // yield return GetPeak(i);
                    t.push_back (GetPeak(i));
                }
            }
            return t;
        }

        std::vector<TPeak> FilterByY(DoubleRange *yRange) override {
            return FilterByY(yRange->getMinimum(), yRange->getMaximum());
        }

    protected:
        virtual TPeak GeneratePeak(int index) = 0;

        TPeak GetPeak(int index) {
            if (peakList[index].getX() ==  (double)0 && peakList[index].getY() == (double)0 ) {
                peakList[index] = GeneratePeak(index);
            }
            return peakList[index];
        }

    };
}
