#pragma once

#include "../Enums/Polarity.h"
#include "../Enums/MzAnalyzerType.h"
#include "../MzSpectra/IMzSpectrum.h"
#include <string>
#include <vector>
#include <type_traits>
#include "Nullable.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
//namespace MzLibUtil { class MzRange; }

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
#include "../../MzLibUtil/MzLibUtil.h"
using namespace MzLibUtil;

namespace MassSpectrometry {
    template<typename TSpectrum>
    //C# TO C++ CONVERTER TODO TASK: C++ does not allow specifying covariance
    // or contravariance in a generic type list:
    //ORIGINAL LINE: public interface IMsDataScan<out TSpectrum> where TSpectrum : IMzSpectrum<IMzPeak>
    class IMsDataScan
    {
#ifndef NDEBUG
        static_assert(std::is_base_of<IMzSpectrum<IMzPeak>, TSpectrum>::value, "IMsDataScan: TSpectrum must inherit from IMzSpectrum<IMzPeak>");
#endif

    public:
        virtual TSpectrum getMassSpectrum() const = 0;
        virtual int getOneBasedScanNumber() const = 0;
        virtual int getMsnOrder() const = 0;
        virtual double getRetentionTime() const = 0;
        virtual MzRange *getScanWindowRange() const = 0;
        virtual std::string getScanFilter() const = 0;
        virtual std::string getNativeId() const = 0;
        virtual bool getIsCentroid() const = 0;
        virtual double getTotalIonCurrent() const = 0;
        virtual MassSpectrometry::Polarity getPolarity() const = 0;
        virtual MZAnalyzerType getMzAnalyzer() const = 0;
        virtual Nullable<double> getInjectionTime() const = 0;
        virtual std::vector<std::vector<double>> getNoiseData() const = 0;

        virtual std::vector<unsigned char> Get64BitNoiseDataMass() = 0;
        virtual std::vector<unsigned char> Get64BitNoiseDataNoise() = 0;
        virtual std::vector<unsigned char> Get64BitNoiseDataBaseline() = 0;

    };
}
