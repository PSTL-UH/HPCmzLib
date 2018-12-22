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

//        #region Private Fields

        MzRange *isolationRange;

//        #endregion Private Fields

//        #region Protected Constructors

    public:
        virtual ~MsDataScanWithPrecursor() {
            delete isolationRange;
        }

    protected:
        MsDataScanWithPrecursor(TSpectrum massSpectrum, int ScanNumber, int MsnOrder, bool isCentroid, MassSpectrometry::Polarity Polarity, double RetentionTime, MzRange *MzRange, const std::wstring &ScanFilter, MZAnalyzerType MzAnalyzer, double TotalIonCurrent, double selectedIonMZ, std::optional<int> &selectedIonChargeStateGuess, std::optional<double> &selectedIonIntensity, std::optional<double> &isolationMZ, std::optional<double> &isolationWidth, MassSpectrometry::DissociationType dissociationType, std::optional<int> &oneBasedPrecursorScanNumber, std::optional<double> &selectedIonMonoisotopicGuessMz, std::optional<double> &injectionTime, std::vector<std::vector<double>> &noiseData, const std::wstring &nativeId) : MsDataScan<TSpectrum>(massSpectrum, ScanNumber, MsnOrder, isCentroid, Polarity, RetentionTime, MzRange, ScanFilter, MzAnalyzer, TotalIonCurrent, injectionTime, noiseData, nativeId) {
            this->OneBasedPrecursorScanNumber = oneBasedPrecursorScanNumber;

            this->setIsolationMz(isolationMZ);
            this->IsolationWidth = isolationWidth;

            this->DissociationType = dissociationType;

            this->setSelectedIonMZ(selectedIonMZ);
            this->setSelectedIonIntensity(selectedIonIntensity);
            this->SelectedIonChargeStateGuess = selectedIonChargeStateGuess;
            this->setSelectedIonMonoisotopicGuessMz(selectedIonMonoisotopicGuessMz);
        }

//        #endregion Protected Constructors

//        #region Public Properties

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

//        #endregion Public Properties

//        #region Public Methods

        std::vector<IsotopicEnvelope*> GetIsolatedMassesAndCharges(IMzSpectrum<IMzPeak*> *precursorSpectrum, int maxAssumedChargeState, double deconvolutionTolerancePpm, double intensityRatio) override {
            if (getIsolationRange() == nullptr) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                yield break;
            }

            for (auto haha : precursorSpectrum->Deconvolute(new MzRange(getIsolationRange()->Minimum - 8.5, getIsolationRange()->Maximum + 8.5), maxAssumedChargeState, deconvolutionTolerancePpm, intensityRatio).Where([&] (std::any b) {
                b::peaks::Any([&] (std::any cc) {
                isolationRange->Contains(cc::Item1);
                });
            })) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                yield return haha;
            }
        }

        void TransformMzs(std::function<double(IPeak*)> convertorForSpectrum, std::function<double(IPeak*)> convertorForPrecursor) override {
            getMassSpectrum()->ReplaceXbyApplyingFunction(convertorForSpectrum);
            MzPeak tempVar(getSelectedIonMZ(), getSelectedIonIntensity().Value);
            this->setSelectedIonMZ(convertorForPrecursor(&tempVar));
            if (getSelectedIonMonoisotopicGuessMz().HasValue) {
                MzPeak tempVar2(getSelectedIonMonoisotopicGuessMz().Value, getSelectedIonMonoisotopicGuessIntensity().Value);
                this->setSelectedIonMonoisotopicGuessMz(convertorForPrecursor(&tempVar2));
            }
            if (getIsolationMz().HasValue) {
                MzPeak tempVar3(getIsolationMz().Value, getSelectedIonIntensity().Value);
                this->setIsolationMz(convertorForPrecursor(&tempVar3));
            }

            // Will need to recompute this...
            isolationRange = nullptr;
        }

        void RefineSelectedMzAndIntensity(IMzSpectrum<IMzPeak*> *precursorSpectrum) override {
            if (getIsolationMz().HasValue) {
                auto thePeak = precursorSpectrum->GetClosestPeakIndex(getIsolationMz().Value);
                setSelectedIonIntensity(precursorSpectrum->YArray[thePeak]);
                setSelectedIonMZ(precursorSpectrum->XArray[thePeak]);
            }
        }

        void ComputeSelectedPeakIntensity(IMzSpectrum<IMzPeak*> *precursorSpectrum) override {
            auto thePeak = precursorSpectrum->GetClosestPeakIndex(getSelectedIonMZ());
            setSelectedIonIntensity(precursorSpectrum->YArray[thePeak]);
            setSelectedIonMZ(precursorSpectrum->XArray[thePeak]);
        }

        void ComputeMonoisotopicPeakIntensity(IMzSpectrum<IMzPeak*> *precursorSpectrum) override {
            auto thePeak = precursorSpectrum->GetClosestPeakIndex(getSelectedIonMonoisotopicGuessMz().Value);
            setSelectedIonMonoisotopicGuessIntensity(precursorSpectrum->YArray[thePeak]);
            setSelectedIonMonoisotopicGuessMz(precursorSpectrum->XArray[thePeak]);
        }

        std::vector<std::tuple<std::vector<IMzPeak*>, int>> GetIsolatedMassesAndChargesOld(IMzSpectrum<IMzPeak*> *precursorSpectrum, int maxAssumedChargeState, Tolerance *massTolerance, double intensityRatio) override {
            if (getIsolationRange() == nullptr) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                yield break;
            }

            for (auto haha : precursorSpectrum->DeconvoluteOld(new MzRange(getIsolationRange()->Minimum - 8.5, getIsolationRange()->Maximum + 8.5), maxAssumedChargeState, massTolerance, intensityRatio).Where([&] (std::any b) {
                b::Item1->Any([&] (std::any cc) {
                isolationRange->Contains(cc::Mz);
                });
            })) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                yield return haha;
            }
        }

//        #endregion Public Methods
    };
}
