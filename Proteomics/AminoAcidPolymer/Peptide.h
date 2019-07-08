#pragma once

#include <string>
#include <vector>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
//namespace Proteomics { class AminoAcidPolymer; }
#include "AminoAcidPolymer.h"
//namespace Proteomics { class Residue; }
#include "Residue.h"

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work copyright 2016 Stefan Solntsev
//
// This file (Peptide.cs) is part of Proteomics.
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

    namespace AminoAcidPolymer    {
        class Peptide : public AminoAcidPolymer {
        private:
            int privateStartResidue = 0;
            int privateEndResidue = 0;
            AminoAcidPolymer *privateParent;
            Residue *privatePreviousResidue;
            Residue *privateNextResidue;


        public:
            Peptide();
            
            Peptide(const std::string &sequence);
            
            Peptide(AminoAcidPolymer *aminoAcidPolymer);
            
            /// <summary>
            /// Create a new peptide based on another amino acid polymer
            /// </summary>
            /// <param name="aminoAcidPolymer">The other amino acid polymer to copy</param>
            /// <param name="includeModifications">Whether to copy the modifications to the new peptide</param>
            Peptide(AminoAcidPolymer *aminoAcidPolymer, bool includeModifications);
            
            Peptide(AminoAcidPolymer *aminoAcidPolymer, int firstResidue, int length);
            
            Peptide(AminoAcidPolymer *aminoAcidPolymer, int firstResidue, int length, bool includeModifications);
            
            /// <summary>
            /// The amino acid number this peptide is located in its parent
            /// </summary>
            int getStartResidue() const;
            void setStartResidue(int value);
            
            /// <summary>
            /// The amino acid number this peptide is located in its parent
            /// </summary>
            int getEndResidue() const;
            void setEndResidue(int value);
            
            /// <summary>
            /// The amino acid polymer this peptide came from. Could be null
            /// </summary>
            AminoAcidPolymer *getParent() const;
            void setParent(AminoAcidPolymer *value);
            
            /// <summary>
            /// The preceding amino acid in its parent
            /// </summary>
            Residue *getPreviousResidue() const;
            void setPreviousResidue(Residue *value);
            
            /// <summary>
            /// The next amino acid in its parent
            /// </summary>
            Residue *getNextResidue() const;
            void setNextResidue(Residue *value);
            
            std::vector<Peptide*> GenerateAllModificationCombinations();
            
            Peptide *GetSubPeptide(int firstResidue, int length);
            
        };
    }
}
