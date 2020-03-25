#pragma once

#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>
#include <functional>
#include <optional>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
//namespace MassSpectrometry { class SourceFile; }
#include "SourceFile.h"
//namespace MassSpectrometry { class MsDataScan; }
#include "MsDataScan.h"
//namespace MassSpectrometry { class IFilteringParams; }
#include "IFilteringParams.h"
//namespace MassSpectrometry { class DeconvolutionFeatureWithMassesAndScans; }
#include "DeconvolutionFeatureWithMassesAndScans.h"

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work Copyright 2016 Stefan Solntsev
//
// This file (MsDataFile.cs) is part of MassSpectrometry.
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

#include "MzLibUtil.h"
using namespace MzLibUtil;

namespace MassSpectrometry
{
    /// <summary>
    /// A class for interacting with data collected from a Mass Spectrometer, and stored in a file
    /// </summary>
    class MsDataFile
    {
    private:
        MassSpectrometry::SourceFile *privateSourceFile;

    protected:
        std::vector<MsDataScan*> Scans;

    public:
        MsDataFile(int numSpectra, MassSpectrometry::SourceFile *sourceFile);

        MsDataFile(std::vector<MsDataScan*> &scans, MassSpectrometry::SourceFile *sourceFile);

        MassSpectrometry::SourceFile *getSourceFile() const;

        int getNumSpectra() const;

        virtual std::vector<MsDataScan*> GetAllScansList();

        static int TopNpeakHelper(std::vector<double> &intensities, std::vector<double> &mArray, IFilteringParams *filteringParams);

        
        /// <summary>
        /// This method is designed to break a scan up into windows and take the top N peaks (by intensity)
        /// from each window, then merge the results as the scan's new mass spectrum
        /// </summary>
        /// <param name="intensities"></param>
        /// <param name="mArray"></param>
        /// <param name="filteringParams"></param>
        static void WindowModeHelper(std::vector<double> &intensities, std::vector<double> &mArray, IFilteringParams *filteringParams, double scanRangeMinMz, double scanRangeMaxMz, std::optional<double> WindowMaxNormalizationToValue = std::nullopt);

        static void XCorrPrePreprocessing(std::vector<double> &intensities, std::vector<double> &mArray, double scanRangeMinMz, double scanRangeMaxMz, double precursorMz, double precursorDiscardRange = 1.5, double discreteMassBin = 1.0005079, double percentMaxThreshold = 5);

        virtual std::vector<MsDataScan*> GetMS1Scans();

        virtual MsDataScan *GetOneBasedScan(int scanNumber);

        std::vector<MsDataScan*> GetMsScansInIndexRange(int FirstSpectrumNumber, int LastSpectrumNumber);

        std::vector<MsDataScan*> GetMsScansInTimeRange(double firstRT, double lastRT);

        virtual int GetClosestOneBasedSpectrumNumber(double retentionTime);

        // EG: removed this function from the C++ version.
        //IEnumerator<MsDataScan*> *GetEnumerator();

        std::vector<DeconvolutionFeatureWithMassesAndScans*> Deconvolute(std::optional<int> &minScan, std::optional<int> &maxScan, int minAssumedChargeState, int maxAssumedChargeState, double deconvolutionTolerancePpm, double intensityRatioLimit, double aggregationTolerancePpm, std::function<bool(MsDataScan*)> scanFilterFunc, int maxThreads = -1);

#ifdef NOT_USED
    protected:

//        class ReverseComparer : public IComparer<double>
        class ReverseComparer 
        {
        public:
            int Compare(double x, double y);
        };
#endif
    };
}
