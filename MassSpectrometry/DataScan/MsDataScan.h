#pragma once

#include "IMsDataScan.h"
#include "../Enums/Polarity.h"
#include "../Enums/MzAnalyzerType.h"
#include "../../MzLibUtil/MzRange.h"
#include "../MzSpectra/IMzPeak.h"
#include "../MzSpectra/MzSpectrum.h"
#include <string>
#include <vector>
#include <optional>
#include <type_traits>
#include "stringhelper.h"

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

namespace MassSpectrometry {
    template<typename TSpectrum>
    class MsDataScan : public IMsDataScan<TSpectrum> {
        static_assert(std::is_base_of<IMzSpectrum<IMzPeak>, TSpectrum>::value, L"TSpectrum must inherit from IMzSpectrum<IMzPeak>");

    private:
        TSpectrum privateMassSpectrum;
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

    public:
        MsDataScan(TSpectrum massSpectrum, int oneBasedScanNumber, int msnOrder, bool isCentroid, MassSpectrometry::Polarity polarity, double retentionTime, MzRange *scanWindowRange, const std::string &scanFilter, MZAnalyzerType mzAnalyzer, double totalIonCurrent, std::optional<double> &injectionTime, std::vector<std::vector<double>> &noiseData, const std::string &nativeId) {
            OneBasedScanNumber = oneBasedScanNumber;
            MsnOrder = msnOrder;
            IsCentroid = isCentroid;
            Polarity = polarity;
            RetentionTime = retentionTime;
            ScanWindowRange = scanWindowRange;
            ScanFilter = scanFilter;
            MzAnalyzer = mzAnalyzer;
            TotalIonCurrent = totalIonCurrent;
            InjectionTime = injectionTime;
            NoiseData = noiseData;
            setMassSpectrum(massSpectrum);
            NativeId = nativeId;
        }

        /// <summary>
        /// The mass spectrum associated with the scan
        /// </summary>
        TSpectrum getMassSpectrum() const override {
            return privateMassSpectrum;
        }
        void setMassSpectrum(TSpectrum value) override {
            privateMassSpectrum = value;
        }

        int getOneBasedScanNumber() const override {
            return privateOneBasedScanNumber;
        }

        int getMsnOrder() const override {
            return privateMsnOrder;
        }

        double getRetentionTime() const override {
            return privateRetentionTime;
        }

        MassSpectrometry::Polarity getPolarity() const override {
            return privatePolarity;
        }

        MZAnalyzerType getMzAnalyzer() const override {
            return privateMzAnalyzer;
        }

        MzRange *getScanWindowRange() const override {
            return privateScanWindowRange;
        }

        std::string getScanFilter() const override {
            return privateScanFilter;
        }

        std::string getNativeId() const override {
            return privateNativeId;
        }

        bool getIsCentroid() const override {
            return privateIsCentroid;
        }

        double getTotalIonCurrent() const override {
            return privateTotalIonCurrent;
        }

        std::optional<double> getInjectionTime() const override {
            return privateInjectionTime;
        }
        std::vector<std::vector<double>> getNoiseData() const override {
            return privateNoiseData;
        }

        std::string ToString() override {
            return StringHelper::formatSimple(L"Scan #{0}", getOneBasedScanNumber());
        }

        std::vector<unsigned char> Get64BitNoiseDataMass() override {
            return MzSpectrum<IMzPeak*>::Get64Bitarray(GetNoiseDataMass(getNoiseData()));
        }

        std::vector<unsigned char> Get64BitNoiseDataNoise() override {
            return MzSpectrum<IMzPeak*>::Get64Bitarray(GetNoiseDataNoise(getNoiseData()));
        }

        std::vector<unsigned char> Get64BitNoiseDataBaseline() override {
            return MzSpectrum<IMzPeak*>::Get64Bitarray(GetNoiseDataBaseline(getNoiseData()));
        }

    private:
        std::vector<double> GetNoiseDataMass(std::vector<std::vector<double>> &noiseData) {
            for (int i = 0; i < noiseData.size() / 3; i++) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                yield return noiseData[0][i];
            }
        }

        std::vector<double> GetNoiseDataNoise(std::vector<std::vector<double>> &noiseData) {
            for (int i = 0; i < noiseData.size() / 3; i++) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                yield return noiseData[1][i];
            }
        }

        std::vector<double> GetNoiseDataBaseline(std::vector<std::vector<double>> &noiseData) {
            for (int i = 0; i < noiseData.size() / 3; i++) {
//C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                yield return noiseData[2][i];
            }
        }

    };
}
