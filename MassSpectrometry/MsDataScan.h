#pragma once

#include "Enums/Polarity.h"
#include "Enums/MzAnalyzerType.h"
#include "Enums/DissociationType.h"
#include <string>
#include <vector>
#include <functional>
#include <optional>
#include "stringhelper.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace MassSpectrometry { class MzSpectrum; }
namespace MzLibUtil { class MzRange; }
namespace MassSpectrometry { class IsotopicEnvelope; }
namespace MassSpectrometry { class MzPeak; }

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

namespace MassSpectrometry
{
    class MsDataScan
    {
    private:
        MzSpectrum *privateMassSpectrum;
        int privateOneBasedScanNumber = 0;
        int privateMsnOrder = 0;
        double privateRetentionTime = 0;
        MassSpectrometry::Polarity privatePolarity = static_cast<MassSpectrometry::Polarity>(0);
        MZAnalyzerType privateMzAnalyzer = static_cast<MZAnalyzerType>(0);
        MzRange *privateScanWindowRange;
        std::string privateScanFilter;
        std::string privateNativeId;
        bool privateIsCentroid = false;
        double privateTotalIonCurrent = 0;
        std::optional<double> privateInjectionTime;
        std::vector<std::vector<double>> privateNoiseData;
        std::optional<double> privateIsolationMz;
        std::optional<int> privateSelectedIonChargeStateGuess;
        std::optional<double> privateSelectedIonIntensity;
        std::optional<double> privateSelectedIonMZ;
        std::optional<MassSpectrometry::DissociationType> privateDissociationType;
        std::optional<double> privateIsolationWidth;
        std::optional<int> privateOneBasedPrecursorScanNumber;
        std::optional<double> privateSelectedIonMonoisotopicGuessIntensity;
        std::optional<double> privateSelectedIonMonoisotopicGuessMz;

    public:
        virtual ~MsDataScan()
        {
            delete isolationRange;
        }

        MsDataScan(MzSpectrum *massSpectrum, int oneBasedScanNumber, int msnOrder, bool isCentroid, MassSpectrometry::Polarity polarity, double retentionTime, MzRange *scanWindowRange, const std::string &scanFilter, MZAnalyzerType mzAnalyzer, double totalIonCurrent, std::optional<double> &injectionTime, std::vector<std::vector<double>> &noiseData, const std::string &nativeId, std::optional<double> &selectedIonMz = std::nullopt, std::optional<int> &selectedIonChargeStateGuess = std::nullopt, std::optional<double> &selectedIonIntensity = std::nullopt, std::optional<double> &isolationMZ = std::nullopt, std::optional<double> &isolationWidth = std::nullopt, std::optional<MassSpectrometry::DissociationType> &dissociationType = std::nullopt, std::optional<int> &oneBasedPrecursorScanNumber = std::nullopt, std::optional<double> &selectedIonMonoisotopicGuessMz = std::nullopt);

        /// <summary>
        /// The mass spectrum associated with the scan
        /// </summary>
        MzSpectrum *getMassSpectrum() const;
        void setMassSpectrum(MzSpectrum *value);

        int getOneBasedScanNumber() const;
        int getMsnOrder() const;
        double getRetentionTime() const;
        MassSpectrometry::Polarity getPolarity() const;
        MZAnalyzerType getMzAnalyzer() const;
        MzRange *getScanWindowRange() const;
        std::string getScanFilter() const;
        std::string getNativeId() const;
        bool getIsCentroid() const;
        double getTotalIonCurrent() const;
        std::optional<double> getInjectionTime() const;
        std::vector<std::vector<double>> getNoiseData() const;

        //MSn properties, all are nullable for MS1s, but MS1s are checked by evaluating if MsnOrder==1
        std::optional<double> getIsolationMz() const;
        void setIsolationMz(const std::optional<double> &value);

        std::optional<int> getSelectedIonChargeStateGuess() const;
        std::optional<double> getSelectedIonIntensity() const;
        void setSelectedIonIntensity(const std::optional<double> &value);
        std::optional<double> getSelectedIonMZ() const;
        void setSelectedIonMZ(const std::optional<double> &value);
        std::optional<MassSpectrometry::DissociationType> getDissociationType() const;
        std::optional<double> getIsolationWidth() const;
        std::optional<int> getOneBasedPrecursorScanNumber() const;
        void setOneBasedPrecursorScanNumber(const std::optional<int> &value);
        std::optional<double> getSelectedIonMonoisotopicGuessIntensity() const;
        void setSelectedIonMonoisotopicGuessIntensity(const std::optional<double> &value);
        std::optional<double> getSelectedIonMonoisotopicGuessMz() const;
        void setSelectedIonMonoisotopicGuessMz(const std::optional<double> &value);

    private:
        MzRange *isolationRange;

    public:
        MzRange *getIsolationRange() const;

        std::string ToString() override;

        std::vector<unsigned char> Get64BitNoiseDataMass();

        std::vector<unsigned char> Get64BitNoiseDataNoise();

        std::vector<unsigned char> Get64BitNoiseDataBaseline();

        std::vector<IsotopicEnvelope*> GetIsolatedMassesAndCharges(MzSpectrum *precursorSpectrum, int minAssumedChargeState, int maxAssumedChargeState, double deconvolutionTolerancePpm, double intensityRatio);

        void TransformMzs(std::function<double(MzPeak*)> convertorForSpectrum, std::function<double(MzPeak*)> convertorForPrecursor);

        void RefineSelectedMzAndIntensity(MzSpectrum *precursorSpectrum);

        void ComputeSelectedPeakIntensity(MzSpectrum *precursorSpectrum);

        void ComputeMonoisotopicPeakIntensity(MzSpectrum *precursorSpectrum);

        void setOneBasedPrecursorScanNumber(int value);

    private:
        std::vector<double> GetNoiseDataMass(std::vector<std::vector<double>> &noiseData);

        std::vector<double> GetNoiseDataNoise(std::vector<std::vector<double>> &noiseData);

        std::vector<double> GetNoiseDataBaseline(std::vector<std::vector<double>> &noiseData);
    };
}
