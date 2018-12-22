#pragma once

#include <string>
#include <vector>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Proteomics { class AminoAcidPolymer; }

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work copyright 2016 Stefan Solntsev
//
// This file (AminoAcidPolymerExtensions.cs) is part of Proteomics.
//
// Proteomics is free software: you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Proteomics is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with Proteomics. If not, see <http://www.gnu.org/licenses/>.


namespace Proteomics {
    class AminoAcidPolymerExtensions final {
//        #region Public Methods

    public:
        static double GetSequenceCoverageFraction(AminoAcidPolymer *baseSequence, std::vector<AminoAcidPolymer*> &sequences);

        static double GetSequenceCoverageFraction(AminoAcidPolymer *baseSequence, std::vector<AminoAcidPolymer*> &sequences, bool useLeucineSequence);

        static std::vector<int> GetSequenceCoverage(AminoAcidPolymer *baseSequence, std::vector<AminoAcidPolymer*> &sequences);

        static std::vector<int> GetSequenceCoverage(AminoAcidPolymer *baseSequence, std::vector<AminoAcidPolymer*> &allPolymers, bool useLeucineSequence);

//        #endregion Public Methods
    };
}
