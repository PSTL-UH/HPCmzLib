#pragma once

#include "IMsDataScan.h"
#include "../Enums/DissociationType.h"
#include <vector>
#include <tuple>
#include <optional>
#include <type_traits>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace MzLibUtil { class MzRange; }
namespace MassSpectrometry { class IMzPeak; }
namespace MassSpectrometry { template<typename TPeak>class IMzSpectrum; }
namespace MassSpectrometry { class IsotopicEnvelope; }
namespace MzLibUtil { class Tolerance; }
namespace Spectra { class IPeak; }

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work Copyright 2016 Stefan Solntsev
//
// This file (IMsDataScan.cs) is part of MassSpectrometry.
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
//C# TO C++ CONVERTER TODO TASK: C++ does not allow specifying covariance or contravariance in a generic type list:
//ORIGINAL LINE: public interface IMsDataScanWithPrecursor<out TSpectrum> : IMsDataScan<TSpectrum> where TSpectrum : IMzSpectrum<IMzPeak>
    class IMsDataScanWithPrecursor : public IMsDataScan<TSpectrum>
    {
    static_assert(std::is_base_of<IMzSpectrum<IMzPeak>, TSpectrum>::value, L"TSpectrum must inherit from IMzSpectrum<IMzPeak>");

    public:
        virtual std::optional<int> getOneBasedPrecursorScanNumber() const = 0;

        virtual double getSelectedIonMZ() const = 0;
        virtual std::optional<double> getSelectedIonIntensity() const = 0;
        virtual std::optional<int> getSelectedIonChargeStateGuess() const = 0;
        virtual std::optional<double> getSelectedIonMonoisotopicGuessMz() const = 0;
        virtual std::optional<double> getSelectedIonMonoisotopicGuessIntensity() const = 0;

        virtual MassSpectrometry::DissociationType getDissociationType() const = 0;

        virtual std::optional<double> getIsolationMz() const = 0;
        virtual MzRange *getIsolationRange() const = 0;

        /// <summary>
        /// Use to set value of SelectedIonIntensity based on SelectedIonMZ
        /// </summary>
        /// <param name="precursorSpectrum"></param>
        virtual void ComputeSelectedPeakIntensity(IMzSpectrum<IMzPeak*> *precursorSpectrum) = 0;

        /// <summary>
        /// Used to set refine value of SelectedIonMZ and SelectedIonIntensity
        /// </summary>
        /// <param name="precursorSpectrum"></param>
        virtual void RefineSelectedMzAndIntensity(IMzSpectrum<IMzPeak*> *precursorSpectrum) = 0;

        virtual std::vector<IsotopicEnvelope*> GetIsolatedMassesAndCharges(IMzSpectrum<IMzPeak*> *precursorSpectrum, int maxAssumedChargeState, double deconvolutionTolerancePpm, double intensityRatio) = 0;

        virtual std::vector<std::tuple<std::vector<IMzPeak*>, int>> GetIsolatedMassesAndChargesOld(IMzSpectrum<IMzPeak*> *precursorSpectrum, int maxAssumedChargeState, Tolerance *massTolerance, double intensityRatio) = 0;

        virtual void ComputeMonoisotopicPeakIntensity(IMzSpectrum<IMzPeak*> *precursorSpectrum) = 0;

        virtual void TransformMzs(std::function<double(IPeak*)> convertorForSpectrum, std::function<double(IPeak*)> convertorForPrecursor) = 0;

    };
}
