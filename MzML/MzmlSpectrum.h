#pragma once

#include "../MassSpectrometry/MzSpectra/MzSpectrum.h"
#include <vector>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace IO { namespace MzML { class MzmlPeak; } }

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work copyright 2016 Stefan Solntsev
//
// This file (DefaultMzSpectrum.cs) is part of MassSpectrometry.
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

using namespace MassSpectrometry;

namespace IO {
    namespace MzML {
        class MzmlMzSpectrum : public MzSpectrum<MzmlPeak*> {
    //        #region Public Constructors

        public:
            MzmlMzSpectrum(std::vector<double> &mz, std::vector<double> &intensities, bool shouldCopy);

    //        #endregion Public Constructors

    //        #region Protected Methods

        protected:
            MzmlPeak *GeneratePeak(int index) override;

    //        #endregion Protected Methods
        };
    }
}
