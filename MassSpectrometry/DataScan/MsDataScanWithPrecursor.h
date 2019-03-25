#pragma once

#include "IMsDataScanWithPrecursor.h"
#include "MsDataScan.h"
#include "../Enums/DissociationType.h"
#include "../../MzLibUtil/MzRange.h"
#include "../Enums/MzAnalyzerType.h"
#include "../Enums/Polarity.h"
#include "../MzSpectra/IMzPeak.h"
#include "../MzSpectra/IMzSpectrum.h"
#include "../MzSpectra/IsotopicEnvelope.h"
#include "../../Spectra/IPeak.h"
#include "../MzSpectra/MzPeak.h"
#include "../../MzLibUtil/Tolerance.h"
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <tuple>
#include <optional>
#include <type_traits>

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work Copyright 2016 Stefan Solntsev
//
// This file (MsDataScan.cs) is part of MassSpectrometry.
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
    template<typename TSpectrum>
    class MsDataScanWithPrecursor : public MsDataScan<TSpectrum>, public IMsDataScanWithPrecursor<TSpectrum> {
        static_assert(std::is_base_of<IMzSpectrum<IMzPeak>, TSpectrum>::value, L"TSpectrum must inherit from IMzSpectrum<IMzPeak>");

    private:
        std::optional<double> privateIsolationMz;
        std::optional<int> privateSelectedIonChargeStateGuess;
        std::optional<double> privateSelectedIonIntensity;
        double privateSelectedIonMZ = 0;
        MassSpectrometry::DissociationType privateDissociationType = static_cast<MassSpectrometry::DissociationType>(0);
        std::optional<double> privateIsolationWidth;
        std::optional<int> privateOneBasedPrecursorScanNumber;
        std::optional<double> privateSelectedIonMonoisotopicGuessIntensity;
        std::optional<double> privateSelectedIonMonoisotopicGuessMz;

        MzRange *isolationRange;

    public:
        virtual ~MsDataScanWithPrecursor() {
            delete isolationRange;
        }

    protected:
        MsDataScanWithPrecursor(TSpectrum massSpectrum, int ScanNumber, int MsnOrder, bool isCentroid, MassSpectrometry::Polarity Polarity, double RetentionTime, MzRange *MzRange, const std::string &ScanFilter, MZAnalyzerType MzAnalyzer, double TotalIonCurrent, double selectedIonMZ, std::optional<int> &selectedIonChargeStateGuess, std::optional<double> &selectedIonIntensity, std::optional<double> &isolationMZ, std::optional<double> &isolationWidth, MassSpectrometry::DissociationType dissociationType, std::optional<int> &oneBasedPrecursorScanNumber, std::optional<double> &selectedIonMonoisotopicGuessMz, std::optional<double> &injectionTime, std::vector<std::vector<double>> &noiseData, const std::string &nativeId) : MsDataScan<TSpectrum>(massSpectrum, ScanNumber, MsnOrder, isCentroid, Polarity, RetentionTime, MzRange, ScanFilter, MzAnalyzer, TotalIonCurrent, injectionTime, noiseData, nativeId) {
            this->OneBasedPrecursorScanNumber = oneBasedPrecursorScanNumber;

            this->setIsolationMz(isolationMZ);
            this->IsolationWidth = isolationWidth;

            this->DissociationType = dissociationType;

            this->setSelectedIonMZ(selectedIonMZ);
            this->setSelectedIonIntensity(selectedIonIntensity);
            this->SelectedIonChargeStateGuess = selectedIonChargeStateGuess;
            this->setSelectedIonMonoisotopicGuessMz(selectedIonMonoisotopicGuessMz);
        }

    public:
        std::optional<double> getIsolationMz() const override {
            return privateIsolationMz;
        }
        void setIsolationMz(const std::optional<double> &value) override {
            privateIsolationMz = value;
        }
        std::optional<int> getSelectedIonChargeStateGuess() const override {
            return privateSelectedIonChargeStateGuess;
        }
        std::optional<double> getSelectedIonIntensity() const override {
            return privateSelectedIonIntensity;
        }
        void setSelectedIonIntensity(const std::optional<double> &value) override {
            privateSelectedIonIntensity = value;
        }
        double getSelectedIonMZ() const override {
            return privateSelectedIonMZ;
        }
        void setSelectedIonMZ(double value) override {
            privateSelectedIonMZ = value;
        }
        MassSpectrometry::DissociationType getDissociationType() const override {
            return privateDissociationType;
        }
        std::optional<double> getIsolationWidth() const {
            return privateIsolationWidth;
        }
        std::optional<int> getOneBasedPrecursorScanNumber() const override {
            return privateOneBasedPrecursorScanNumber;
        }
        std::optional<double> getSelectedIonMonoisotopicGuessIntensity() const override {
            return privateSelectedIonMonoisotopicGuessIntensity;
        }
        void setSelectedIonMonoisotopicGuessIntensity(const std::optional<double> &value) override {
            privateSelectedIonMonoisotopicGuessIntensity = value;
        }
        std::optional<double> getSelectedIonMonoisotopicGuessMz() const override {
            return privateSelectedIonMonoisotopicGuessMz;
        }
        void setSelectedIonMonoisotopicGuessMz(const std::optional<double> &value) override {
            privateSelectedIonMonoisotopicGuessMz = value;
        }

        MzRange *getIsolationRange() const override {
            if (isolationRange != nullptr) {
                return isolationRange;
            }
            if (getIsolationWidth().HasValue && getIsolationMz().HasValue) {
                isolationRange = new MzRange(getIsolationMz().Value - getIsolationWidth().Value / 2, getIsolationMz().Value + getIsolationWidth().Value / 2);
            }
            return isolationRange;
        }

        std::vector<IsotopicEnvelope*> GetIsolatedMassesAndCharges(IMzSpectrum<IMzPeak*> *precursorSpectrum,
                                                                   int maxAssumedChargeState,
                                                                   double deconvolutionTolerancePpm,
                                                                   double intensityRatio) override {
            std::vector<IsotopicEnvelope*> v;
            if (getIsolationRange() == nullptr) {
                //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                //yield break;
                return v;
            }

            MzRange *m = new MzRange(getIsolationRange()->getMinimum() - 8.5, getIsolationRange()->getMaximum() + 8.5);
            std::vector<IsotopicEnvelope*> vIE = precursorSpectrum->Deconvolute(m, maxAssumedChargeState,
                                                                                deconvolutionTolerancePpm,
                                                                                intensityRatio);
#ifdef ORIG
            for (auto haha : vIE.Where([&] (std::any b) {
                b::peaks::Any([&] (std::any cc) {
                isolationRange->Contains(cc::Item1);
                });
                    })) {
                //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                yield return haha;
            }
        }
#endif
            for (IsotopicEnvelope* haha : vIE ) {
                bool found =false;
                std::for_each (haha->peaks.begin(), haha->peaks.end(), [&] (std::tuple<double, double> cc) {
                        if ( isolationRange->Contains(std::get<0>(cc) )) {
                                found = true;
                        };
                    });
                if ( found ) {
                    //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                    //yield return haha;
                    v.push_back(haha);
                }
            }
            return v;
        }

        void TransformMzs(std::function<double(IPeak*)> convertorForSpectrum, std::function<double(IPeak*)> convertorForPrecursor) override {
            this->getMassSpectrum()->ReplaceXbyApplyingFunction(convertorForSpectrum);
            MzPeak tempVar(getSelectedIonMZ(), getSelectedIonIntensity().Value);
            this->setSelectedIonMZ(convertorForPrecursor(&tempVar));
            if (getSelectedIonMonoisotopicGuessMz().HasValue) {
                MzPeak tempVar2(getSelectedIonMonoisotopicGuessMz().Value, getSelectedIonMonoisotopicGuessIntensity().Value);
                this->setSelectedIonMonoisotopicGuessMz(convertorForPrecursor(&tempVar2));
            }
            if (getIsolationMz().has_value()) {
                MzPeak tempVar3(getIsolationMz().value(), getSelectedIonIntensity().value());
                this->setIsolationMz(convertorForPrecursor(&tempVar3));
            }

            // Will need to recompute this...
            isolationRange = nullptr;
        }

        void RefineSelectedMzAndIntensity(IMzSpectrum<IMzPeak*> *precursorSpectrum) override {
            if (getIsolationMz().has_value()) {
                auto thePeak = precursorSpectrum->GetClosestPeakIndex(getIsolationMz().value());
                setSelectedIonIntensity(precursorSpectrum->getYArray()[thePeak]);
                setSelectedIonMZ(precursorSpectrum->getXArray()[thePeak]);
            }
        }

        void ComputeSelectedPeakIntensity(IMzSpectrum<IMzPeak*> *precursorSpectrum) override {
            auto thePeak = precursorSpectrum->GetClosestPeakIndex(getSelectedIonMZ());
            setSelectedIonIntensity(precursorSpectrum->getYArray()[thePeak]);
            setSelectedIonMZ(precursorSpectrum->getXArray()[thePeak]);
        }

        void ComputeMonoisotopicPeakIntensity(IMzSpectrum<IMzPeak*> *precursorSpectrum) override {
            auto thePeak = precursorSpectrum->GetClosestPeakIndex(getSelectedIonMonoisotopicGuessMz().Value);
            setSelectedIonMonoisotopicGuessIntensity(precursorSpectrum->getYArray()[thePeak]);
            setSelectedIonMonoisotopicGuessMz(precursorSpectrum->getXArray()[thePeak]);
        }

        std::vector<std::tuple<std::vector<IMzPeak*>, int>> GetIsolatedMassesAndChargesOld(IMzSpectrum<IMzPeak*> *precursorSpectrum, int maxAssumedChargeState, Tolerance *massTolerance, double intensityRatio) override {
            std::vector<std::tuple<std::vector<IMzPeak*>, int>> v;
            if (getIsolationRange() == nullptr) {
                //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                //yield break;
                return v;
            }
#ifdef ORIG
            for (auto haha : precursorSpectrum->DeconvoluteOld(new MzRange(getIsolationRange()->Minimum - 8.5, getIsolationRange()->Maximum + 8.5), maxAssumedChargeState, massTolerance, intensityRatio).Where([&] (std::any b) {
                b::Item1->Any([&] (std::any cc) {
                isolationRange->Contains(cc::Mz);
                });
            })) {
                //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                //yield return haha;
                v.push_back (haha);
            }
#endif
            MzRange *m = new MzRange(getIsolationRange()->getMinimum() - 8.5, getIsolationRange()->getMaximum() + 8.5);
            std::vector<std::tuple<std::vector<IMzPeak*>, int>> vtIe = precursorSpectrum->DeconvoluteOld(m,
                                                                                maxAssumedChargeState,
                                                                                massTolerance,
                                                                                intensityRatio);

            for ( std::tuple<std::vector<IMzPeak*>, int> haha : vtIe ) {
                std::vector<IMzPeak*> vIP = std::get<0>(haha);
                bool found =false;
                std::for_each (vIP.begin(), vIP.end(), [&] (IMzPeak* cc) {
                        if ( isolationRange->Contains(cc->getMz()) ) {
                                found = true;
                        };
                    });
                if ( found ) {
                    //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                    //yield return haha;
                    v.push_back(haha);
                }
            }
            return v;
        }

    };
}
