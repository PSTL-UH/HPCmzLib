#pragma once

#include "CleavageSpecificity.h"
#include <string>
#include <unordered_map>
#include <vector>
#include "exceptionhelper.h"

namespace Proteomics { class Protein; }
#include "../Modifications/Modification.h"
#include "DigestionParams.h"


namespace Proteomics { namespace ProteolyticDigestion { class PeptideWithSetModifications; } }


namespace Proteomics
{
    namespace ProteolyticDigestion
    {
        /// <summary>
        /// Product of digesting a protein
        /// Contains methods for modified peptide combinitorics
        /// </summary>
        //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        //ORIGINAL LINE: [Serializable] public class ProteolyticPeptide
        class ProteolyticPeptide
        {
        private:
            int privateOneBasedStartResidueInProtein = 0;
            int privateOneBasedEndResidueInProtein = 0;
            int privateMissedCleavages = 0;
            std::string privatePeptideDescription;
            CleavageSpecificity privateCleavageSpecificityForFdrCategory = static_cast<CleavageSpecificity>(0);

        protected:
            std::string _baseSequence;

        public:
            virtual ~ProteolyticPeptide()
            {
                //delete _protein;
            }

            ProteolyticPeptide(Proteomics::Protein *protein, int oneBasedStartResidueInProtein, int oneBasedEndResidueInProtein, int missedCleavages,
                               CleavageSpecificity cleavageSpecificityForFdrCategory, const std::string &peptideDescription = "");

        private:
            //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
            //ORIGINAL LINE: [NonSerialized] private Protein _protein;
            Proteomics::Protein *_protein; // protein that this peptide is a digestion product of

        public:
            int getOneBasedStartResidueInProtein() const;
            int getOneBasedEndResidueInProtein() const;
            int getMissedCleavages() const;
            std::string getPeptideDescription() const;
            void setPeptideDescription(const std::string &value);
            CleavageSpecificity getCleavageSpecificityForFdrCategory() const;
            void setCleavageSpecificityForFdrCategory(CleavageSpecificity value);
            int getLength();
            
            virtual char getPreviousAminoAcid() const;
            
            virtual char getNextAminoAcid() const;
            
            Proteomics::Protein *getProtein() const;

            std::string getBaseSequence();

            /// <summary>
            /// Gets the peptides for a specific protein interval
            /// </summary>
            /// <param name="interval"></param>
            /// <param name="allKnownFixedModifications"></param>
            /// <param name="digestionParams"></param>
            /// <param name="variableModifications"></param>
            /// <returns></returns>
            std::vector<PeptideWithSetModifications*> GetModifiedPeptides(std::vector<Modification*> allKnownFixedModifications,
                                                                          DigestionParams *digestionParams,
                                                                          std::vector<Modification*> variableModifications);

            
        protected:
            void setProtein(Proteomics::Protein *value);
            
            
            char operator [](int zeroBasedIndex);
            
            
            /// <summary>
            /// Determines whether given modification can be an N-terminal modification
            /// </summary>
            /// <param name="variableModification"></param>
            /// <param name="peptideLength"></param>
            /// <returns></returns>
        private:
            bool CanBeNTerminalMod(Modification *variableModification, int peptideLength);

            /// <summary>
            /// Determines whether given modification can be a C-terminal modification
            /// </summary>
            /// <param name="variableModification"></param>
            /// <param name="peptideLength"></param>
            /// <returns></returns>
            bool CanBeCTerminalMod(Modification *variableModification, int peptideLength);

            static std::vector<std::unordered_map<int, Modification*>> GetVariableModificationPatterns(std::unordered_map<int, std::vector<Modification*>&> &possibleVariableModifications, int maxModsForPeptide, int peptideLength);

            static std::vector<std::vector<int>> GetVariableModificationPatterns(std::vector<std::tuple<int, std::vector<Modification*>>> possibleVariableModifications, int unmodifiedResiduesDesired, std::vector<int> &variableModificationPattern, int index);

            static std::unordered_map<int, Modification*> GetNewVariableModificationPattern(std::vector<int> variableModificationArray, std::vector<std::tuple<int, std::vector<Modification*>>> possibleVariableModifications);

            std::unordered_map<int, Modification*> GetFixedModsOneIsNterminus(int peptideLength, std::vector<Modification*> &allKnownFixedModifications);
        
        };
    }
}
