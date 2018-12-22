#pragma once

#include "../MassSpectrometry/MzSpectra/MzSpectrum.h"
#include <vector>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace MassSpectrometry { class MzPeak; }

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work Copyright 2016 Stefan Solntsev
//
// This file (ThermoSpectrum.cs) is part of MassSpecFiles.
//
// MassSpecFiles is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MassSpecFiles is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with MassSpecFiles. If not, see <http://www.gnu.org/licenses/>.

using namespace MassSpectrometry;

namespace IO {
    namespace Thermo {
        /// <summary>
        /// A high resolution spectra from a Thermo raw file
        /// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [Serializable] public sealed class ThermoSpectrum : MzSpectrum<MzPeak>
        class ThermoSpectrum final : public MzSpectrum<MzPeak*> {
    //        #region Public Constructors

        public:
            ThermoSpectrum(std::vector<double> &mz, std::vector<double> &intensity, bool shouldCopy);

            ThermoSpectrum(const ThermoSpectrum &thermoSpectrum);

    //        #endregion Public Constructors

    //        #region Internal Constructors

            ThermoSpectrum(std::vector<std::vector<double>> &peakData);

    //        #endregion Internal Constructors

    //        #region Protected Methods

        protected:
            MzPeak *GeneratePeak(int index) override;

    //        #endregion Protected Methods
        };
    }
}
