#pragma once

#include "../Chemistry/Interfaces/IHasMass.h"
#include "FragmentTypes.h"
#include "Terminus.h"
#include "ModificationSites.h"
#include <string>
#include <unordered_set>
#include <vector>
#include <set>
#include <limits>
#include <any>
#include <type_traits>
#include "stringhelper.h"
#include "stringbuilder.h"

#include "Residue.h"
namespace Proteomics { namespace AminoAcidPolymer { class Fragment; } }
#include "DigestionPoint.h"
#include "IProtease.h"
#include "OldSchoolModification.h"

// Copyright 2012, 2013, 2014 Derek J. Bailey
// Modified work copyright 2016 Stefan Solntsev
//
// This file (AminoAcidPolymer.cs) is part of Proteomics.
//
// Proteomics is free software: you can redistribute it and/or modify i
// under the terms of the GNU Lesser General Public License as publishe
// by the Free Software Foundation, either version 3 of the License, o
// (at your option) any later version
//
// Proteomics is distributed in the hope that it will be useful, but WITHOU
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY o
// FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Publi
// License for more details
//
// You should have received a copy of the GNU Lesser General Publi
// License along with Proteomics. If not, see <http://www.gnu.org/licenses/>

#include "../../Chemistry/Chemistry.h"
using namespace Chemistry;
#include "MzLibUtil.h"
using namespace MzLibUtil;

namespace Proteomics
{
    namespace AminoAcidPolymer
    {
        /// <summary>
        /// A linear polymer of amino acids
        /// </summary>
        //    class AminoAcidPolymer : public IEquatable<AminoAcidPolymer*>,
        //                             public IHasMass {
        class AminoAcidPolymer : public IHasMass {
        private:
            int privateLength = 0;
            double privateMonoisotopicMass = 0;
            
            /// <summary>
            /// The C-terminus chemical formula cap. This is different from the C-Terminus
            ///  modification.
            /// </summary>
            IHasChemicalFormula *_cTerminus=nullptr;

            /// <summary>
            /// The N-terminus chemical formula cap. This is different from the N-Terminus modification.
            /// </summary>
            IHasChemicalFormula *_nTerminus=nullptr;

            /// <summary>
            /// All of the modifications indexed by position from N to C. This array is 2 bigger than
            /// the amino acid array
            /// as index 0 and Count - 1 represent the N and C terminus, respectively
            /// </summary>
            std::vector<IHasMass*> _modifications;
            
            /// <summary>
            /// All of the amino acid residues indexed by position from N to C.
            /// </summary>
            std::vector<Residue*> residues;
            
        public:
            virtual ~AminoAcidPolymer() {
                if ( _cTerminus != nullptr ) {
                    delete _cTerminus;
                }
                if ( _nTerminus != nullptr ) {
                    delete _nTerminus;
                }
            }
            
        protected:
            AminoAcidPolymer();
            
            AminoAcidPolymer(const std::string &sequence);
            
            AminoAcidPolymer(const std::string &sequence, IHasChemicalFormula *nTerm, IHasChemicalFormula *cTerm);
            
            AminoAcidPolymer(AminoAcidPolymer *aminoAcidPolymer, bool includeModifications);
            
            AminoAcidPolymer(AminoAcidPolymer *aminoAcidPolymer, int firstResidue, int length,
                             bool includeModifications);
            
        public:
            //  ReadOnlyCollection<IHasMass*> *getModifications() const;
            std::vector<IHasMass*> *getModifications() const;

            /// <summary>
            /// Gets or sets the C terminus of this amino acid polymer
            /// </summary>
            IHasChemicalFormula *getCTerminus() const;
            void setCTerminus(IHasChemicalFormula *value);
            
            /// <summary>
            /// Gets or sets the N terminus of this amino acid polymer
            /// </summary>
            IHasChemicalFormula *getNTerminus() const;
            void setNTerminus(IHasChemicalFormula *value);
            
            /// <summary>
            /// Gets the number of amino acids in this amino acid polymer
            /// </summary>
            int getLength() const;
            void setLength(int value);

            /// <summary>
            /// The total monoisotopic mass of this peptide and all of its modifications
            /// </summary>
            double getMonoisotopicMass() const override;
            //  void setMonoisotopicMass(double value) override;
            void setMonoisotopicMass(double value);

            /// <summary>
            /// Returns the amino acid sequence with all isoleucines (I) replaced with leucines (L);
            /// </summary>
            /// <returns>The amino acid sequence with all I's into L's</returns>
            virtual std::string getBaseLeucineSequence() const;
            
            /// <summary>
            /// Gets the base amino acid sequence
            /// </summary>
            std::string getBaseSequence() const;
            
            /// <summary>
            /// Gets or sets the modification of the C terminus on this amino acid polymer
            /// </summary>
            IHasMass *getCTerminusModification() const;
            void setCTerminusModification(IHasMass *value);
            
            /// <summary>
            /// Gets or sets the modification of the C terminus on this amino acid polymer
            /// </summary>
            IHasMass *getNTerminusModification() const;
            void setNTerminusModification(IHasMass *value);
            
            /// <summary>
            /// Returns all fragments that are present in either fragmentation of A or B, but not in both
            /// </summary>
            static std::vector<Proteomics::AminoAcidPolymer::Fragment*> GetSiteDeterminingFragments(AminoAcidPolymer *peptideA,
                                                                          AminoAcidPolymer *peptideB, FragmentTypes types);
            
            /// <summary>
            /// Gets the digestion points (starting index and length) of a amino acid sequence
            /// </summary>
            /// <param name="sequence">The sequence to cleave</param>
            /// <param name="proteases">The proteases to cleave with</param>
            /// <param name="maxMissedCleavages">The maximum number of missed clevages to allow</param>
            /// <param name="minLength">The minimum amino acid length of the peptides</param>
            /// <param name="maxLength">The maximum amino acid length of the peptides</param>
            /// <param name="methionineInitiator"></param>
            /// <param name="semiDigestion"></param>
            /// <returns>A collection of clevage points and the length of the cut (Item1 = index, Item2 = length)
            /// </returns>
            static std::vector<DigestionPointAndLength*> GetDigestionPointsAndLengths(const std::string &sequence,
                        std::vector<IProtease*> &proteases, int maxMissedCleavages, int minLength, int maxLength,
                        bool methionineInitiator, bool semiDigestion);

            static std::vector<int> GetCleavageIndexes(const std::string &sequence,
                                                       std::vector<IProtease*> &proteases);

            /// <summary>
            /// Gets the location of all the possible cleavage points for a given sequence and set of proteases
            /// </summary>
            /// <param name="sequence">The sequence to determine the cleavage points for</param>
            /// <param name="proteases">The proteases to cleave with</param>
            /// <param name="includeTermini">Include the N and C terminus (-1 and Length + 1)</param>
            /// <returns>A collection of all the sites where the proteases would cleave</returns>
            static std::vector<int> GetCleavageIndexes(const std::string &sequence,
                                                       std::vector<IProtease*> &proteases,
                                                       bool includeTermini);
            
            static std::vector<std::string> Digest(const std::string &sequence, std::vector<IProtease*> &proteases,
                                                   int maxMissedCleavages, int minLength, int maxLength,
                                                   bool methionineInitiator, bool semiDigestion);
            
            static std::vector<std::string> Digest(AminoAcidPolymer *sequence, IProtease *protease);
            
            static std::vector<std::string> Digest(AminoAcidPolymer *polymer, IProtease *protease,
                                                   int maxMissedCleavages, int minLength, int maxLength,
                                                   bool methionineInitiator, bool semiDigestion);

            Residue *GetResidue(int position);

            /// <summary>
            /// Checks if an amino acid residue with the value of 'residue' is contained in this polymer
            /// </summary>
            /// <param name="residue">The character code for the amino acid residue</param>
            /// <returns>True if any amino acid residue is the same as the specified character</returns>
            bool Contains(char residue);
            
            /// <summary>
            /// Checks if the amino acid residue is contained in this polymer
            /// </summary>
            /// <param name="residue">The residue to check for</param>
            /// <returns>True if the polymer contains the specified residue, False otherwise</returns>
            bool Contains(Residue *residue);
            
            std::string _getString ( IHasMass *mod );
            std::string GetSequenceWithModifications();
            
            std::string GetSequenceWithModifications(bool leucineSequence);
            
            /// <summary>
            /// Gets the total number of amino acid residues in this amino acid polymer
            /// </summary>
            /// <returns>The number of amino acid residues</returns>
            int ResidueCount();
            
            int ResidueCount(Residue *aminoAcid);
            
            /// <summary>
            /// Gets the number of amino acids residues in this amino acid polymer that
            /// has the specified residue letter
            /// </summary>
            /// <param name="residueLetter">The residue letter to search for</param>
            /// <returns>The number of amino acid residues that have the same letter in this polymer</returns>
            int ResidueCount(char residueLetter);
            
            int ResidueCount(char residueLetter, int index, int length);
            
            int ResidueCount(Residue *aminoAcid, int index, int length);
            
            int ElementCountWithIsotopes(const std::string &element);
            
            int SpecificIsotopeCount(Isotope *isotope);
            
            /// <summary>
            /// Calculates the fragments that are different between this and another aminoacidpolymer
            /// </summary>
            /// <param name="other"></param>
            /// <param name="type"></param>
            /// <returns></returns>
            std::vector<Proteomics::AminoAcidPolymer::Fragment*> GetSiteDeterminingFragments(AminoAcidPolymer *other,
                                                                           FragmentTypes type);
            
            std::vector<Proteomics::AminoAcidPolymer::Fragment*> Fragment(FragmentTypes types);
            
            /// <summary>
            /// Calculates all the fragments of the types you specify
            /// </summary>
            /// <param name="types"></param>
            /// <param name="calculateChemicalFormula"></param>
            /// <returns></returns>
            std::vector<Proteomics::AminoAcidPolymer::Fragment*> Fragment(FragmentTypes types,
                                                                          bool calculateChemicalFormula);
            
            std::vector<Proteomics::AminoAcidPolymer::Fragment*> Fragment(FragmentTypes types, int number);
            
            std::vector<Proteomics::AminoAcidPolymer::Fragment*> Fragment(FragmentTypes types, int number,
                                                        bool calculateChemicalFormula);
            
            std::vector<Proteomics::AminoAcidPolymer::Fragment*> Fragment(FragmentTypes types, int minIndex,
                                                                          int maxIndex);
            
            std::vector<Proteomics::AminoAcidPolymer::Fragment*> Fragment(FragmentTypes types, int minIndex,
                                                                          int maxIndex, bool calculateChemicalFormula);

            bool ContainsModifications();

            template<typename T>
            std::unordered_set<T> GetUniqueModifications()  {
                //static_assert(std::is_base_of<IHasMass, T>::value, "T must inherit from IHasMass");
                
                std::unordered_set<T> uniqueMods;

                if (_modifications.empty()) {
                    return uniqueMods;
                }
                
                for (auto mod : _modifications) {
                    if (dynamic_cast<T>(mod) != nullptr) {
                        uniqueMods.insert(static_cast<T>(mod));
                    }
                }
                return uniqueMods;
            }


            /// <summary>
            /// Counts the total number of modifications on this polymer that are not null
            /// </summary>
            /// <returns>The number of modifications</returns>
            int ModificationCount();

            /// <summary>
            /// Get the modification at the given residue number
            /// </summary>
            /// <param name="residueNumber">The amino acid residue number</param>
            /// <returns>The modification at the site, null if there isn't any modification present</returns>
            IHasMass *GetModification(int residueNumber) const;
            
            /// <summary>
            /// Sets the modification at the terminus of this amino acid polymer
            /// </summary>
            /// <param name="modification">The modification to set</param>
            /// <param name="terminus">The termini to set the mod at</param>
            virtual void SetModification(IHasMass *modification, Terminus terminus);
            
            /// <summary>
            /// Sets the modification at specific sites on this amino acid polymer
            /// </summary>
            /// <param name="modification">The modification to set</param>
            /// <param name="sites">The sites to set the modification at</param>
            /// <returns>The number of modifications added to this amino acid polymer</returns>
            virtual int SetModification(IHasMass *modification, ModificationSites sites);
            
            /// <summary>
            /// Sets the modification at specific sites on this amino acid polymer
            /// </summary>
            /// <param name="modification">The modification to set</param>
            /// <param name="letter">The residue character to set the modification at</param>
            /// <returns>The number of modifications added to this amino acid polymer</returns>
            virtual int SetModification(IHasMass *modification, char letter);
            
            /// <summary>
            /// Sets the modification at specific sites on this amino acid polymer
            /// </summary>
            /// <param name="modification">The modification to set</param>
            /// <param name="residue">The residue to set the modification at</param>
            /// <returns>The number of modifications added to this amino acid polymer</returns>
            virtual int SetModification(IHasMass *modification, Residue *residue);
            
            /// <summary>
            /// Sets the modification at specific sites on this amino acid polymer
            /// </summary>
            /// <param name="modification">The modification to set</param>
            /// <param name="residueNumber">The residue number to set the modification at</param>
            virtual void SetModification(IHasMass *modification, int residueNumber);
            
            void SetModifications(std::vector<OldSchoolModification*> &modifications);
            
            void SetModification(OldSchoolModification *mod);

            /// <summary>
            ///
            /// </summary>
            /// <param name="mod"></param>
            /// <param name="residueNumbers">(1-based) residue number</param>
            void SetModification(IHasMass *mod, std::vector<int> &residueNumbers);
            
            /// <summary>
            /// Replaces all instances of the old modification with the new modification in this polymer
            /// </summary>
            /// <param name="oldMod">The modification to remove</param>
            /// <param name="newMod">The modification to replace it with</param>
            /// <returns>The number of modifications added to this amino acid polymer</returns>
            virtual int ReplaceModification(IHasMass *oldMod, IHasMass *newMod);
            
            /// <summary>
            /// Adds the modification at the terminus of this amino acid polymer, combining modifications if
            /// a modification is already present
            /// </summary>
            /// <param name="modification">The modification to set</param>
            /// <param name="terminus">The termini to set the mod at</param>
            virtual int AddModification(IHasMass *modification, Terminus terminus);
            
            virtual int AddModification(OldSchoolModification *modification);
            
            virtual int AddModification(IHasMass *modification, ModificationSites sites);

            /// <summary>
            /// Adds the modification at specific sites on this amino acid polymer, combining modifications if
            /// a modification is already present
            /// </summary>
            /// <param name="modification">The modification to set</param>
            /// <param name="location">The location to set the modification at</param>
            virtual void AddModification(IHasMass *modification, int location);
            
            /// <summary>
            /// Clears the modification set at the terminus of this amino acid polymer back
            /// to the default C or N modifications.
            /// </summary>
            /// <param name="terminus">The termini to clear the mod at</param>
            void ClearModifications(Terminus terminus);
            
            /// <summary>
            /// Clear the modifications from the specified sites(s)
            /// </summary>
            /// <param name="sites">The sites to remove modifications from</param>
            void ClearModifications(ModificationSites sites);
            
            /// <summary>
            /// Clear all modifications from this amino acid polymer.
            /// Includes N and C terminus modifications.
            /// </summary>
            void ClearModifications();
            
            /// <summary>
            /// Removes the specified mod from all locations on this polymer
            /// </summary>
            /// <param name="mod">The modification to remove from this polymer</param>
            void ClearModifications(IHasMass *mod);
            
            /// <summary>
            /// Gets the chemical formula of this amino acid polymer.
            /// </summary>
            /// <returns></returns>
            ChemicalFormula *GetChemicalFormula();
            
            // std::string ToString() override;
            std::string ToString();
            
            // int GetHashCode() override;
            int GetHashCode();
            
            // bool Equals(std::any obj) override;
            // bool Equals(AminoAcidPolymer *other) override;
            bool Equals(AminoAcidPolymer *other);
                        
        private:
            void ReplaceTerminus(IHasChemicalFormula **terminus, IHasChemicalFormula *value);
            
            /// <summary>
            /// Replaces a modification (if present) at the specific index in the residue (0-based for N and C termini)
            /// </summary>
            /// <param name="index">The residue index to replace at</param>
            /// <param name="mod">The modification to replace with</param>
            void ReplaceMod(int index, IHasMass *mod);
            
            /// <summary>
            /// Parses a string sequence of amino acids characters into a peptide object
            /// </summary>
            /// <param name="sequence"></param>
            /// <returns></returns>
            void ParseSequence(const std::string &sequence);
            
        private:
            class ModWithOnlyMass : public IHasMass {
            
                 private:
                      const double mass;
            
                 public:
                      ModWithOnlyMass(double mass);
            
                      double getMonoisotopicMass() const override;
            
                      std::string ToString();
            };  
        };
    }
}
