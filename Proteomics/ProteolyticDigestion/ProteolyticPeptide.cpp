#include "ProteolyticPeptide.h"
#include "../Modifications/Modification.h"
#include "DigestionParams.h"
#include "PeptideWithSetModifications.h"
#include "../Modifications/ModificationLocalization.h"
#include "../Protein/Protein.h"

#include <tuple>

namespace Proteomics
{
    namespace ProteolyticDigestion
    {

        ProteolyticPeptide::ProteolyticPeptide(Proteomics::Protein *protein, int oneBasedStartResidueInProtein, int oneBasedEndResidueInProtein, int missedCleavages, CleavageSpecificity cleavageSpecificityForFdrCategory, const std::string &peptideDescription)
        {
            _protein = protein;
            privateOneBasedStartResidueInProtein = oneBasedStartResidueInProtein;
            privateOneBasedEndResidueInProtein = oneBasedEndResidueInProtein;
            privateMissedCleavages = missedCleavages;
            setCleavageSpecificityForFdrCategory(cleavageSpecificityForFdrCategory);
            setPeptideDescription(peptideDescription);
        }

        int ProteolyticPeptide::getOneBasedStartResidueInProtein() const
        {
            return privateOneBasedStartResidueInProtein;
        }

        int ProteolyticPeptide::getOneBasedEndResidueInProtein() const
        {
            return privateOneBasedEndResidueInProtein;
        }

        int ProteolyticPeptide::getMissedCleavages() const
        {
            return privateMissedCleavages;
        }

        std::string ProteolyticPeptide::getPeptideDescription() const
        {
            return privatePeptideDescription;
        }

        void ProteolyticPeptide::setPeptideDescription(const std::string &value)
        {
            privatePeptideDescription = value;
        }

        CleavageSpecificity ProteolyticPeptide::getCleavageSpecificityForFdrCategory() const
        {
            return privateCleavageSpecificityForFdrCategory;
        }

        void ProteolyticPeptide::setCleavageSpecificityForFdrCategory(CleavageSpecificity value)
        {
            privateCleavageSpecificityForFdrCategory = value;
        }

        int ProteolyticPeptide::getLength()
        {
            return getBaseSequence().length();
        }

        char ProteolyticPeptide::getPreviousAminoAcid() const
        {
#ifdef ORIG
            return getOneBasedStartResidueInProtein() > 1 ? getProtein()[getOneBasedStartResidueInProtein() - 2] : '-';
#endif
            int i = getOneBasedStartResidueInProtein();
            char result = '-';
            if ( i > 1 ) {
                result = getProtein()->getBaseSequence()[i-2];
            }
            return result;
        }

        char ProteolyticPeptide::getNextAminoAcid() const
        {
#ifdef ORIG
            return getOneBasedEndResidueInProtein() < getProtein()->getLength() ? getProtein()[getOneBasedEndResidueInProtein()] : '-';
#endif
            int i = getOneBasedEndResidueInProtein();
            char result = '-';
            if ( i > getProtein()->getLength() ) {
                result = getProtein()->getBaseSequence()[i];
            }
            return result;
        }

        Proteomics::Protein *ProteolyticPeptide::getProtein() const
        {
            return _protein;
        }

        void ProteolyticPeptide::setProtein(Proteomics::Protein *value)
        {
            _protein = value;
        }

        std::string ProteolyticPeptide::getBaseSequence() 
        {
            if (_baseSequence == "")
            {
                _baseSequence = getProtein()->getBaseSequence().substr(getOneBasedStartResidueInProtein() - 1, getOneBasedEndResidueInProtein() - getOneBasedStartResidueInProtein() + 1);
            }
            return _baseSequence;
        }

        char ProteolyticPeptide::operator [](int zeroBasedIndex)
        {
            return getBaseSequence()[zeroBasedIndex];
        }

        std::vector<PeptideWithSetModifications*> ProteolyticPeptide::GetModifiedPeptides(std::vector<Modification*> allKnownFixedModifications, DigestionParams *digestionParams, std::vector<Modification*> variableModifications)
        {
            int peptideLength = getOneBasedEndResidueInProtein() - getOneBasedStartResidueInProtein() + 1;
            int maximumVariableModificationIsoforms = digestionParams->getMaxModificationIsoforms();
            int maxModsForPeptide = digestionParams->getMaxModsForPeptide();
            std::unordered_map<int, std::vector<Modification*>&> twoBasedPossibleVariableAndLocalizeableModifications(peptideLength + 4);
            
            auto pepNTermVariableMods = new std::vector<Modification*>();
            twoBasedPossibleVariableAndLocalizeableModifications.emplace(1, *pepNTermVariableMods);
            
            auto pepCTermVariableMods = new std::vector<Modification*>();
            twoBasedPossibleVariableAndLocalizeableModifications.emplace(peptideLength + 2, *pepCTermVariableMods);

            
            for (auto variableModification : variableModifications)
            {
                // Check if can be a n-term mod
                if (CanBeNTerminalMod(variableModification, peptideLength))
                {
                    pepNTermVariableMods->push_back(variableModification);
                }
                
                for (int r = 0; r < peptideLength; r++)
                {
                    if (ModificationLocalization::ModFits(variableModification, getProtein()->getBaseSequence(), r + 1, peptideLength,
                                                          getOneBasedStartResidueInProtein() + r)                                      &&
                        variableModification->getLocationRestriction() == "Anywhere.")
                    {
                        std::vector<Modification*> residueVariableMods;
                        std::unordered_map<int, std::vector<Modification*>&>::const_iterator twoBasedPossibleVariableAndLocalizeableModifications_iterator = twoBasedPossibleVariableAndLocalizeableModifications.find(r + 2);
                        if (twoBasedPossibleVariableAndLocalizeableModifications_iterator == twoBasedPossibleVariableAndLocalizeableModifications.end())
                        {
                            auto rVarMods = new std::vector<Modification*>();
                            rVarMods->push_back(variableModification);
                            twoBasedPossibleVariableAndLocalizeableModifications.emplace(r + 2, *rVarMods);
                        }
                        else
                        {
                            residueVariableMods = twoBasedPossibleVariableAndLocalizeableModifications_iterator->second;
                            residueVariableMods.push_back(variableModification);
                        }
                    }
                }
                // Check if can be a c-term mod
                if (CanBeCTerminalMod(variableModification, peptideLength))
                {
                    pepCTermVariableMods->push_back(variableModification);
                }
            }
            
            // LOCALIZED MODS
            for (auto kvp : getProtein()->getOneBasedPossibleLocalizedModifications())
            {
                bool inBounds = std::get<0>(kvp) >= getOneBasedStartResidueInProtein() &&
                    std::get<0>(kvp) <= getOneBasedEndResidueInProtein();
                if (!inBounds)
                {
                    continue;
                }
                
                int locInPeptide = std::get<0>(kvp) - getOneBasedStartResidueInProtein() + 1;
                for (Modification *modWithMass : std::get<1>(kvp) )
                {
                    Modification *variableModification = dynamic_cast<Modification*>(modWithMass);
                    if (variableModification != nullptr)
                    {
                        // Check if can be a n-term mod
                        if (locInPeptide == 1 && CanBeNTerminalMod(variableModification, peptideLength) && !getProtein()->getIsDecoy())
                        {
                            pepNTermVariableMods->push_back(variableModification);
                        }
                        
                        int r = locInPeptide - 1;
                        if (r >= 0 && r < peptideLength && (getProtein()->getIsDecoy() ||
                                                            (ModificationLocalization::ModFits(variableModification, getProtein()->getBaseSequence(),
                                                                                               r + 1, peptideLength, getOneBasedStartResidueInProtein() + r) &&
                                                             variableModification->getLocationRestriction() == "Anywhere.")))
                        {
                            std::vector<Modification*> residueVariableMods;
                            std::unordered_map<int, std::vector<Modification*>&>::const_iterator twoBasedPossibleVariableAndLocalizeableModifications_iterator = twoBasedPossibleVariableAndLocalizeableModifications.find(r + 2);
                            if (twoBasedPossibleVariableAndLocalizeableModifications_iterator == twoBasedPossibleVariableAndLocalizeableModifications.end())
                            {
                                auto rVarMods = new std::vector<Modification*>;
                                rVarMods->push_back(variableModification);
                                twoBasedPossibleVariableAndLocalizeableModifications.emplace(r + 2, *rVarMods);
                            }
                            else
                            {
                                residueVariableMods = twoBasedPossibleVariableAndLocalizeableModifications_iterator->second;
                                residueVariableMods.push_back(variableModification);
                            }
                        }
                        
                        // Check if can be a c-term mod
                        if (locInPeptide == peptideLength && CanBeCTerminalMod(variableModification, peptideLength) && !getProtein()->getIsDecoy())
                        {
                            pepCTermVariableMods->push_back(variableModification);
                        }
                    }
                }
            }
            
            int variable_modification_isoforms = 0;
            std::vector<PeptideWithSetModifications*> v;
            
            for (auto kvp : GetVariableModificationPatterns(twoBasedPossibleVariableAndLocalizeableModifications, maxModsForPeptide, peptideLength))
            {
                int numFixedMods = 0;
                for (auto ok : GetFixedModsOneIsNterminus(peptideLength, allKnownFixedModifications))
                {
                    if (kvp.find(std::get<0>(ok)) == kvp.end())
                    {
                        numFixedMods++;
                        kvp.emplace(std::get<0>(ok), std::get<1>(ok));

                    }
                }
                //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                //yield return new PeptideWithSetModifications(getProtein(), digestionParams, getOneBasedStartResidueInProtein(),
                // getOneBasedEndResidueInProtein(), getCleavageSpecificityForFdrCategory(), getPeptideDescription(), getMissedCleavages(), kvp, numFixedMods);
                PeptideWithSetModifications *p = new PeptideWithSetModifications(getProtein(),
                                                                                 digestionParams,
                                                                                 getOneBasedStartResidueInProtein(),
                                                                                 getOneBasedEndResidueInProtein(),
                                                                                 getCleavageSpecificityForFdrCategory(),
                                                                                 getPeptideDescription(),
                                                                                 getMissedCleavages(),
                                                                                 kvp,
                                                                                 numFixedMods);
                v.push_back(p);
                
                variable_modification_isoforms++;
                if (variable_modification_isoforms == maximumVariableModificationIsoforms)
                {
                    //C# TO C++ CONVERTER TODO TASK: C++ does not have an equivalent to the C# 'yield' keyword:
                    // yield break;
                    return v;
                }
            }
            return v;
        }

        bool ProteolyticPeptide::CanBeNTerminalMod(Modification *variableModification, int peptideLength)
        {
            return ModificationLocalization::ModFits(variableModification, getProtein()->getBaseSequence(), 1, peptideLength,
                                                     getOneBasedStartResidueInProtein()) &&
                (variableModification->getLocationRestriction() == "N-terminal." ||
                 variableModification->getLocationRestriction() == "Peptide N-terminal.");
        }

        bool ProteolyticPeptide::CanBeCTerminalMod(Modification *variableModification, int peptideLength)
        {
            return ModificationLocalization::ModFits(variableModification, getProtein()->getBaseSequence(), peptideLength,
                                                     peptideLength, getOneBasedStartResidueInProtein() + peptideLength - 1) &&
                (variableModification->getLocationRestriction() == "C-terminal." ||
                 variableModification->getLocationRestriction() == "Peptide C-terminal.");
        }


        std::vector<std::unordered_map<int, Modification*>> ProteolyticPeptide::GetVariableModificationPatterns(
            std::unordered_map<int, std::vector<Modification*> &> &possibleVariableModifications,
            int maxModsForPeptide, int peptideLength)
        {
            std::vector<std::unordered_map<int, Modification*>> v;
            if (possibleVariableModifications.empty())
            {
                return v;
            }
            else
            {
                std::unordered_map<int, std::vector<Modification*>&> possible_variable_modifications = possibleVariableModifications;

                std::vector<int> base_variable_modification_pattern(peptideLength + 4);
                int totalAvailableMods=0;
                for ( auto b : possible_variable_modifications ) {
                    if ( !b.second.empty() ) {
                        totalAvailableMods += b.second.size();
                    }
                }
                for (int variable_modifications = 0; variable_modifications <= std::min(totalAvailableMods, maxModsForPeptide);
                     variable_modifications++)
                {
                    std::vector<std::tuple<int, std::vector<Modification*>>> possible_variable_modifications_vec;
                    for( auto it : possible_variable_modifications ) {
                        possible_variable_modifications_vec.push_back({it.first, it.second});
                    }
                    for (auto variable_modification_pattern : GetVariableModificationPatterns(possible_variable_modifications_vec,
                                                                   possible_variable_modifications.size() - variable_modifications,
                                                                   base_variable_modification_pattern, 0))
                    {
                        std::unordered_map<int, Modification*> vo = GetNewVariableModificationPattern(variable_modification_pattern,
                                                                                                      possible_variable_modifications_vec);
                        v.push_back (vo);                    
                    }
                }
            }
            return v;
        }

        std::vector<std::vector<int>> ProteolyticPeptide::GetVariableModificationPatterns(
            std::vector<std::tuple<int, std::vector<Modification*>>> possibleVariableModifications,
            int unmodifiedResiduesDesired,
            std::vector<int> &variableModificationPattern,
            int index)
        {
            std::vector<std::vector<int>> v;
            if (index < (int)possibleVariableModifications.size() - 1)
            {
                if (unmodifiedResiduesDesired > 0)
                {
                    variableModificationPattern[std::get<0>(possibleVariableModifications[index])] = 0;
                    for (auto new_variable_modification_pattern : GetVariableModificationPatterns(possibleVariableModifications,
                                                                                                  unmodifiedResiduesDesired - 1,
                                                                                                  variableModificationPattern,
                                                                                                  index + 1))
                    {
                        v.push_back(new_variable_modification_pattern);
                    }
                }
                if (unmodifiedResiduesDesired < (int)possibleVariableModifications.size() - index)
                {
                    for (int i = 1; i <= (int)(std::get<1>(possibleVariableModifications[index]).size()); i++)
                    {
                        variableModificationPattern[std::get<0>(possibleVariableModifications[index])] = i;
                        for (auto new_variable_modification_pattern : GetVariableModificationPatterns(possibleVariableModifications,
                                                                                                      unmodifiedResiduesDesired,
                                                                                                      variableModificationPattern,
                                                                                                      index + 1))
                        {
                            v.push_back(new_variable_modification_pattern);                        }
                    }
                }
            }
            else
            {
                if (unmodifiedResiduesDesired > 0)
                {
                    variableModificationPattern[std::get<0>(possibleVariableModifications[index])] = 0;
                    v.push_back(variableModificationPattern);
                }
                else
                {
                    for (int i = 1; i <= (int)(std::get<1>(possibleVariableModifications[index]).size()); i++)
                    {
                        variableModificationPattern[std::get<0>(possibleVariableModifications[index])] = i;
                        v.push_back(variableModificationPattern);
                    }
                }
            }
            return v;
        }

        std::unordered_map<int, Modification*> ProteolyticPeptide::GetNewVariableModificationPattern(std::vector<int> variableModificationArray,
                                                 std::vector<std::tuple<int, std::vector<Modification*>>> possibleVariableModifications)
        {
            auto modification_pattern = std::unordered_map<int, Modification*>();
            
            for (auto kvp: possibleVariableModifications )
            {
                if (variableModificationArray[std::get<0>(kvp)] > 0)
                {
                    modification_pattern.emplace(std::get<0>(kvp), std::get<1>(kvp)[variableModificationArray[std::get<0>(kvp)] - 1]);
                }
            }

            return modification_pattern;
        }

        std::unordered_map<int, Modification*> ProteolyticPeptide::GetFixedModsOneIsNterminus(
            int peptideLength,
            std::vector<Modification*> &allKnownFixedModifications)
        {
            auto fixedModsOneIsNterminus = std::unordered_map<int, Modification*>(peptideLength + 3);
            for (auto mod : allKnownFixedModifications)
            {
                if (mod->getLocationRestriction() == "N-terminal." || mod->getLocationRestriction() == "Peptide N-terminal.")
                {
                        if (ModificationLocalization::ModFits(mod, getProtein()->getBaseSequence(), 1,
                                                              peptideLength, getOneBasedStartResidueInProtein()))
                        {
                            fixedModsOneIsNterminus[1] = mod;
                        }

                }
                else if (mod->getLocationRestriction() == "Anywhere.")
                {
                        for (int i = 2; i <= peptideLength + 1; i++)
                        {
                            if (ModificationLocalization::ModFits(mod, getProtein()->getBaseSequence(), i - 1,
                                                                  peptideLength, getOneBasedStartResidueInProtein() + i - 2))
                            {
                                fixedModsOneIsNterminus[i] = mod;
                            }
                        }

                }
                else if (mod->getLocationRestriction() == "C-terminal." || mod->getLocationRestriction() == "Peptide C-terminal.")
                {
                        if (ModificationLocalization::ModFits(mod, getProtein()->getBaseSequence(), peptideLength,
                                                              peptideLength, getOneBasedStartResidueInProtein()+peptideLength-1))
                        {
                            fixedModsOneIsNterminus[peptideLength + 2] = mod;
                        }

                }
                else
                {
                    //throw NotSupportedException("This terminus localization is not supported.");
                    throw NotImplementedException("This terminus localization is not supported.");
                }
            }
            return fixedModsOneIsNterminus;
        }
    }
}
