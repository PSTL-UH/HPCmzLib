#pragma once

#include <vector>
#include <optional>
#include <type_traits>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace MassSpectrometry { class SourceFile; }
namespace MassSpectrometry { class DeconvolutionFeatureWithMassesAndScans; }

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work Copyright 2016 Stefan Solntsev
//
// This file (IMsDataFile.cs) is part of MassSpectrometry.
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


namespace MassSpectrometry {
    template<typename TScan>
//C# TO C++ CONVERTER TODO TASK: C++ does not allow specifying covariance or contravariance in a generic type list:
//ORIGINAL LINE: public interface IMsDataFile<out TScan> : IEnumerable<TScan> where TScan : IMsDataScan<IMzSpectrum<IMzPeak>>
    class IMsDataFile : public std::vector<TScan>
    {
    static_assert(std::is_base_of<IMsDataScan<IMzSpectrum<IMzPeak>>, TScan>::value, L"TScan must inherit from IMsDataScan<IMzSpectrum<IMzPeak>>");
//        #region Public Properties

    public:
        virtual int getNumSpectra() const = 0;
        virtual MassSpectrometry::SourceFile *getSourceFile() const = 0;

//        #endregion Public Properties

//        #region Public Methods

        virtual TScan GetOneBasedScan(int oneBasedScanNumber) = 0;

        virtual std::vector<DeconvolutionFeatureWithMassesAndScans*> Deconvolute(std::optional<int> &minScan, std::optional<int> &maxScan, int maxAssumedChargeState, double deconvolutionTolerancePpm, double intensityRatio, double aggregationTolerancePpm, std::function<bool(TScan)> scanFilterFunc) = 0;

        virtual std::vector<TScan> GetMsScansInTimeRange(double firstRT, double lastRT) = 0;

        virtual int GetClosestOneBasedSpectrumNumber(double retentionTime) = 0;

//        #endregion Public Methods
    };
}
