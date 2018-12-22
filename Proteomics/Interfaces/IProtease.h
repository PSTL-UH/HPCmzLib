#pragma once

#include <string>
#include <vector>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Proteomics { class AminoAcidPolymer; }

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work copyright 2016 Stefan Solntsev
//
// This file (IProtease.cs) is part of Proteomics.
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
    /// <summary>
    /// A proteolyic enzyme that cuts amino acids at specific residues.
    /// </summary>
    class IProtease {
//        #region Public Methods

        /// <summary>
        /// Finds the indicies of where this protease would cut in
        /// the given amino acid sequence
        /// </summary>
        /// <param name="aminoAcidSequence">The Amino Acid Polymer to cut</param>
        /// <returns>A set of the 1-based indicies to cut at</returns>
    public:
        virtual std::vector<int> GetDigestionSites(const std::wstring &aminoAcidSequence) = 0;

        virtual std::vector<int> GetDigestionSites(AminoAcidPolymer *aminoAcidSequence) = 0;

        virtual int MissedCleavages(const std::wstring &sequence) = 0;

        virtual int MissedCleavages(AminoAcidPolymer *aminoAcidSequence) = 0;

//        #endregion Public Methods
    };
}
