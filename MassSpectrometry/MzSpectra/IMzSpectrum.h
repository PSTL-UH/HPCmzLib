#pragma once

#include "../../Spectra/Spectrum.h"
#include <vector>
#include <tuple>
#include <type_traits>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
//namespace MzLibUtil { class MzRange; }
//namespace MzLibUtil { class Tolerance; }
//namespace MassSpectrometry { class IsotopicEnvelope; }
#include "IsotopicEnvelope.h"
//namespace MassSpectrometry { class IMzPeak; }
#include "IMzPeak.h"

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work copyright 2016 Stefan Solntsev
//
// This file (IMzSpectrum.cs) is part of MassSpectrometry.
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

#include "../../MzLibUtil/MzLibUtil.h"
using namespace MzLibUtil;
using namespace Spectra;

namespace MassSpectrometry {
    //C# TO C++ CONVERTER TODO TASK: C++ does not allow specifying covariance
    //or contravariance in a generic type list:
    //ORIGINAL LINE: public interface IMzSpectrum<out TPeak>:ISpectrum<TPeak> where TPeak:IMzPeak
//    template<typename TPeak>
//    class IMzSpectrum : public ISpectrum<TPeak>

    template<typename TPeak>
    class IMzSpectrum : public Spectrum<TPeak>  {
#ifndef NDEBUG        
        static_assert(std::is_base_of<IMzPeak, TPeak>::value, "IMzSpectrum: TPeak must inherit from IMzPeak");
#endif
    public:
        IMzSpectrum(std::vector<std::vector<double>> &mzintensities) : Spectrum<TPeak>(mzintensities) {
        }

        IMzSpectrum(std::vector<double> &mz, std::vector<double> &intensities, bool shouldCopy) : Spectrum<TPeak>(mz, intensities, shouldCopy) {
        }

        virtual MzRange *getRange() const = 0;

        virtual std::vector<unsigned char> Get64BitXarray() = 0;

        virtual std::vector<unsigned char> Get64BitYarray() = 0;

        virtual std::vector<IsotopicEnvelope*> Deconvolute(MzRange *range, int maxAssumedChargeState, double deconvolutionTolerancePpm, double intensityRatio) = 0;

        virtual std::vector<std::tuple<std::vector<IMzPeak*>, int>> DeconvoluteOld(MzRange *theRange, int maxAssumedChargeState, Tolerance *massTolerance, double intensityRatio) = 0;

    };
}
