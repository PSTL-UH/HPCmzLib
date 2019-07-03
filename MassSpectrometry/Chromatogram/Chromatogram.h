#pragma once

#include "ChromatographicPeak.h"
#include "../Enums/SmoothingType.h"
#include "../../Spectra/Spectrum.h"
#include "../../MzLibUtil/DoubleRange.h"
#include "ChromatographicElutionProfile.h"
#include <string>
#include <vector>
#include <type_traits>
#include "stringhelper.h"
#include "Math.h"

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

    template<typename TPeak>
    class AChromatogram : public Spectrum<TPeak> {

#ifndef NDEBUG
        static_assert(std::is_base_of<IPeak, TPeak>::value, "TPeak must inherit from IPeak");
#endif

    protected:
        AChromatogram(std::vector<double> times, std::vector<double> intensities, bool shouldCopy) : Spectrum<TPeak>(times, intensities, shouldCopy) {
        }

        AChromatogram(std::vector<std::vector<double>> timeintensities) : Spectrum<TPeak>(timeintensities) {
        }

        AChromatogram(const AChromatogram<TPeak> &other) : AChromatogram(other.getXArray(), other.getYArray(), true) {
        }

    public:
        double getFirstTime() const {
            return this->getXArray()[0];
        }

        double getLastTime() const {
            return this->getXArray()[this->getSize() - 1];
        }

        std::vector<double> GetTimes() {
            std::vector<double> times = std::vector<double>(this->getSize());
            //Buffer::BlockCopy(this->getXArray(), 0, times, 0, sizeof(double) * this->getSize());
            std::vector<double> d = this->getXArray();
            std::copy(d.begin(), d.begin()+this->getSize(), times.begin());
            return times;
        }

        std::vector<double> GetIntensities() {
            std::vector<double> intensities = std::vector<double>(this->getSize());
            // Buffer::BlockCopy(this->getYArray(), 0, intensities, 0, sizeof(double) * this->getSize());
            std::vector<double> d = this->getYArray();
            std::copy (d.begin(), d.begin()+this->getSize(), intensities.begin() );
            return intensities;
        }

        double GetTime(int index) {
            return this->getXArray()[index];
        }

        double GetIntensity(int index) {
            return this->getYArray()[index];
        }

        //virtual TPeak GetApex(DoubleRange *timeRange) {
        TPeak GetApex(DoubleRange *timeRange) {
            return GetApex(timeRange->getMinimum(), timeRange->getMaximum());
        }

        //virtual TPeak GetApex(double mintime, double maxTime) {
        TPeak GetApex(double mintime, double maxTime) {
            //int index = Array::BinarySearch(this->getXArray(), mintime);
            std::vector<double> d = this->getXArray();
            int index = std::binary_search(d.begin(), d.end(), mintime);
            if (index < 0) {
                index = ~index;
            }

            if (index >= this->getSize()) {
                return this->GetPeak(this->getSize() - 1);
            }

            double maxvalue = -1; // double.negative infinity?
            int apexIndex = index;
            while (index < this->getSize() && this->getXArray()[index] <= maxTime) {
                double intensity = this->getYArray()[index];
                if (intensity > maxvalue) {
                    apexIndex = index;
                    maxvalue = intensity;
                }
                index++;
            }
            return this->GetPeak(apexIndex);
        }

        //virtual ChromatographicElutionProfile<TPeak> *GetElutionProfile(DoubleRange *timeRange) {
        ChromatographicElutionProfile<TPeak> *GetElutionProfile(DoubleRange *timeRange) {
            return GetElutionProfile(timeRange->getMinimum(), timeRange->getMaximum());
        }

        //virtual ChromatographicElutionProfile<TPeak> *GetElutionProfile(double mintime, double maxTime) {
        ChromatographicElutionProfile<TPeak> *GetElutionProfile(double mintime, double maxTime) {
            //int index = Array::BinarySearch(this->getXArray(), mintime);
            std::vector<double> d = this->getXArray();
            int index = std::binary_search(d.begin(), d.end(), mintime);
            if (index < 0) {
                index = ~index;
            }

            std::vector<TPeak> peaks = std::vector<TPeak>();
            while (index < this->getSize() && this->getXArray()[index] <= maxTime) {
                peaks.push_back(this->GetPeak(index));
                index++;
            }
            return new ChromatographicElutionProfile<TPeak>(peaks);
        }

        //virtual TPeak GetApex() {
        TPeak GetApex() {
            return this->GetPeak(this->getIndexOfPeakWithHighesetY().value());
        }

        TPeak FindNearestApex(double rt, int skipablePts) {
            //int index = Array::BinarySearch(this->getXArray(), rt);
            std::vector<double> d = this->getXArray();
            int index = std::binary_search(d.begin(), d.end(), rt);
            if (index < 0) {
                index = ~index;
            }

            if (index >= this->getSize()) {
                index--;
            }

            int bestApex = index;
            double apexValue = this->getYArray()[bestApex];

            int i = index - 1;
            int count = 0;
            while (i >= 0) {
                if (this->getYArray()[i] > apexValue) {
                    bestApex = i;
                    apexValue = this->getYArray()[bestApex];
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
            while (i < this->getSize()) {
                if (this->getYArray()[i] > apexValue) {
                    bestApex = i;
                    apexValue = this->getYArray()[bestApex];
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

            return this->GetPeak(bestApex);
        }

        std::string ToString() {
            return StringHelper::formatSimple("Count = {0:N0} TIC = {1:G4}", this->getSize(),
                                              this->getYArray().Sum());
        }

    };


    class Chromatogram: public AChromatogram<ChromatographicPeak *> {
        using AChromatogram<ChromatographicPeak*>::AChromatogram;
        
    public:
        Chromatogram(std::vector<double> times, std::vector<double> intensities, bool shouldCopy) : AChromatogram<ChromatographicPeak*>(times, intensities, shouldCopy) {
        }

        Chromatogram(std::vector<std::vector<double>> timeintensities) : AChromatogram<ChromatographicPeak*>(timeintensities) {
        }

        Chromatogram(const Chromatogram& other) : AChromatogram<ChromatographicPeak*>(other) {
        }

        Chromatogram *CreateSmoothChromatogram(SmoothingType smoothing, int points) {
            switch (smoothing) {
                case SmoothingType::BoxCar: {
                    //std::vector<double> newTimes = this->getXArray().BoxCarSmooth(points);
                    std::vector<double> newTimes = Math::BoxCarSmooth(this->getXArray(), points);
                    //std::vector<double> newIntensities = this->getYArray().BoxCarSmooth(points);
                    std::vector<double> newIntensities = Math::BoxCarSmooth(this->getYArray(), points);
                    return new Chromatogram(newTimes, newIntensities, false);

                }
                default: {
                    return new Chromatogram( this->getXArray(), this->getYArray(), false);
                }
            }
        }

        
    protected:
        ChromatographicPeak* GeneratePeak(int index) override {
            ChromatographicPeak *cp = new ChromatographicPeak(this->getXArray()[index],
                                                              this->getYArray()[index]);
            return cp;
        }

    };
}
