#pragma once

#include "ChromatographicPeak.h"
#include "../Enums/SmoothingType.h"
#include "../../Spectra/Spectrum.h"
#include "../../MzLibUtil/DoubleRange.h"
#include "ChromatographicElutionProfile.h"
#include <string>
#include <vector>
#include <type_traits>

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work Copyright 2016 Stefan Solntsev
//
// This file (Chromatogram.cs) is part of MassSpectrometry.
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

using namespace MzLibUtil;
using namespace Spectra;

namespace MassSpectrometry {
    template<>
    class Chromatogram<void> : public Chromatogram<ChromatographicPeak*> {
//        #region Public Constructors

    public:
        Chromatogram(std::vector<double> &times, std::vector<double> &intensities, bool shouldCopy) : Chromatogram<ChromatographicPeak>(times, intensities, shouldCopy) {
        }

        Chromatogram(std::vector<std::vector<double>> &timeintensities) : Chromatogram<ChromatographicPeak>(timeintensities) {
        }

        Chromatogram(const Chromatogram<void> &other) : Chromatogram<ChromatographicPeak>(other) {
        }

//        #endregion Public Constructors

//        #region Public Methods

        Chromatogram<void> *CreateSmoothChromatogram(SmoothingType smoothing, int points) {
            switch (smoothing) {
                case SmoothingType::BoxCar: {
                    std::vector<double> newTimes = getXArray().BoxCarSmooth(points);
                    std::vector<double> newIntensities = getYArray().BoxCarSmooth(points);
                    return new Chromatogram(newTimes, newIntensities, false);

                }
                default:
                    return new Chromatogram(this);
            }
        }

//        #endregion Public Methods

//        #region Protected Methods

    protected:
        ChromatographicPeak *GeneratePeak(int index) override {
            return new ChromatographicPeak(getXArray()[index], getYArray()[index]);
        }

//        #endregion Protected Methods
    };

    template<typename TPeak>
    class Chromatogram : public Spectrum<TPeak> {
        static_assert(std::is_base_of<IPeak, TPeak>::value, L"TPeak must inherit from IPeak");

//        #region Protected Constructors

    protected:
        Chromatogram(std::vector<double> &times, std::vector<double> &intensities, bool shouldCopy) : Spectrum<TPeak>(times, intensities, shouldCopy) {
        }

        Chromatogram(std::vector<std::vector<double>> &timeintensities) : Spectrum<TPeak>(timeintensities) {
        }

        Chromatogram(const Chromatogram<TPeak> &other) : Chromatogram(other->getXArray(), other->getYArray(), true) {
        }

//        #endregion Protected Constructors

//        #region Public Properties

    public:
        double getFirstTime() const {
            return getXArray()[0];
        }

        double getLastTime() const {
            return getXArray()[getSize() - 1];
        }

//        #endregion Public Properties

//        #region Public Methods

        std::vector<double> GetTimes() {
            std::vector<double> times = std::vector<double>(getSize());
            Buffer::BlockCopy(getXArray(), 0, times, 0, sizeof(double) * getSize());
            return times;
        }

        std::vector<double> GetIntensities() {
            std::vector<double> intensities = std::vector<double>(getSize());
            Buffer::BlockCopy(getYArray(), 0, intensities, 0, sizeof(double) * getSize());
            return intensities;
        }

        double GetTime(int index) {
            return getXArray()[index];
        }

        double GetIntensity(int index) {
            return getYArray()[index];
        }

        virtual TPeak GetApex(DoubleRange *timeRange) {
            return GetApex(timeRange->Minimum, timeRange->Maximum);
        }

        virtual TPeak GetApex(double mintime, double maxTime) {
            int index = Array::BinarySearch(getXArray(), mintime);
            if (index < 0) {
                index = ~index;
            }

            if (index >= getSize()) {
                return GetPeak(getSize() - 1);
            }

            double maxvalue = -1; // double.negative infinity?
            int apexIndex = index;
            while (index < getSize() && getXArray()[index] <= maxTime) {
                double intensity = getYArray()[index];
                if (intensity > maxvalue) {
                    apexIndex = index;
                    maxvalue = intensity;
                }
                index++;
            }
            return GetPeak(apexIndex);
        }

        virtual ChromatographicElutionProfile<TPeak> *GetElutionProfile(DoubleRange *timeRange) {
            return GetElutionProfile(timeRange->Minimum, timeRange->Maximum);
        }

        virtual ChromatographicElutionProfile<TPeak> *GetElutionProfile(double mintime, double maxTime) {
            int index = Array::BinarySearch(getXArray(), mintime);
            if (index < 0) {
                index = ~index;
            }

            std::vector<TPeak> peaks = std::vector<TPeak>();
            while (index < getSize() && getXArray()[index] <= maxTime) {
                peaks.push_back(GetPeak(index));
                index++;
            }
            return new ChromatographicElutionProfile<TPeak>(peaks);
        }

        virtual TPeak GetApex() {
            return GetPeak(getIndexOfPeakWithHighesetY());
        }

        TPeak FindNearestApex(double rt, int skipablePts) {
            int index = Array::BinarySearch(getXArray(), rt);
            if (index < 0) {
                index = ~index;
            }

            if (index >= getSize()) {
                index--;
            }

            int bestApex = index;
            double apexValue = getYArray()[bestApex];

            int i = index - 1;
            int count = 0;
            while (i >= 0) {
                if (getYArray()[i] > apexValue) {
                    bestApex = i;
                    apexValue = getYArray()[bestApex];
                    count = 0;
                }
                else {
                    count++;
                    if (count >= skipablePts) {
                        break;
                    }
                }
                i--;
            }

            i = index + 1;
            count = 0;
            while (i < getSize()) {
                if (getYArray()[i] > apexValue) {
                    bestApex = i;
                    apexValue = getYArray()[bestApex];
                    count = 0;
                }
                else {
                    count++;
                    if (count >= skipablePts) {
                        break;
                    }
                }
                i++;
            }

            return GetPeak(bestApex);
        }

        std::wstring ToString() override {
            return std::wstring::Format(L"Count = {0:N0} TIC = {1:G4}", getSize(), getYArray().Sum());
        }

//        #endregion Public Methods
    };
}
