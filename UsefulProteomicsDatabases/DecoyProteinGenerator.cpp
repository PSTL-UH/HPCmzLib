#include "DecoyProteinGenerator.h"
#include "../Proteomics/Protein/Protein.h"
#include "../Proteomics/Protein/SequenceVariation.h"
#include "../Proteomics/Modifications/Modification.h"

using namespace Proteomics;

namespace UsefulProteomicsDatabases
{

    std::vector<Protein*> DecoyProteinGenerator::GenerateDecoys(std::vector<Protein*> &proteins,
                                                                DecoyType decoyType, int maxThreads)
    {
        if (decoyType == DecoyType::None)
        {
            return std::vector<Protein*>();
        }
        else if (decoyType == DecoyType::Reverse)
        {
            return GenerateReverseDecoys(proteins, maxThreads);
        }
        else if (decoyType == DecoyType::Slide)
        {
            return GenerateSlideDecoys(proteins, maxThreads);
        }
        else
        {
            //throw std::invalid_argument("Decoy type " + decoyType.ToString() + " is not implemented.");
            throw std::invalid_argument("Decoy type is not implemented.");
        }
    }

    std::vector<Protein*> DecoyProteinGenerator::GenerateReverseDecoys(std::vector<Protein*> &proteins, int maxThreads)
    {
        std::vector<Protein*> decoyProteins;
        //ParallelOptions *tempVar = new ParallelOptions();
        //tempVar->MaxDegreeOfParallelism = maxThreads;
        //Parallel::ForEach(proteins, tempVar, [&] (std::any protein)
        for ( auto protein : proteins )
        {
            // reverse sequence
            // Do not include the initiator methionine in reversal!!!
            auto sequenceArray = protein->getBaseSequence();
            bool startsWithM = protein->getBaseSequence()[0] == 'M';            
            if ( startsWithM )
            {
                //Array::Reverse(sequenceArray, 1, protein->getBaseSequence().length() - 1);
                std::reverse((sequenceArray.begin()+1), sequenceArray.end() );
            }
            else
            {
                //Array::Reverse(sequenceArray);
                std::reverse (sequenceArray.begin(), sequenceArray.end() );
            }
            std::string reversedSequence(sequenceArray);
    
            // reverse nonvariant sequence
            // Do not include the initiator methionine in reversal!!!
            auto nonVariantSequenceArray = protein->getNonVariantProtein()->getBaseSequence();
            if (protein->getNonVariantProtein()->getBaseSequence()[0] == 'M' )
            {
                //Array::Reverse(nonVariantSequenceArray, 1,
                //       protein->getNonVariantProtein()->getBaseSequence().length()- 1);
                std::reverse((nonVariantSequenceArray.begin()+1), nonVariantSequenceArray.end() );
            }
            else
            {
                std::reverse(nonVariantSequenceArray.begin(), nonVariantSequenceArray.end() );
            }
            std::string reversedNonVariantSequence(nonVariantSequenceArray);
    
            // reverse modifications
            std::unordered_map<int, std::vector<Modification*>> decoyModifications;
            if (startsWithM)
            {
                decoyModifications = std::unordered_map<int, std::vector<Modification*>>(protein->getOneBasedPossibleLocalizedModifications().size());
                for (auto kvp : protein->getOneBasedPossibleLocalizedModifications())
                {
                    if (kvp.first > 1)
                    {
                        decoyModifications.emplace(protein->getBaseSequence().length() - kvp.first + 2, kvp.second);
                    }
                    else if (kvp.first == 1)
                    {
                        decoyModifications.emplace(1, kvp.second);
                    }
                }
            }
            else
            {
                decoyModifications = std::unordered_map<int, std::vector<Modification*>>(protein->getOneBasedPossibleLocalizedModifications().size());
                for (auto kvp : protein->getOneBasedPossibleLocalizedModifications())
                {
                    decoyModifications.emplace(protein->getBaseSequence().length() - kvp.first + 1, kvp.second);
                }
            }
    
            // reverse proteolysis products
            std::vector<ProteolysisProduct*> decoyPP;
            for (ProteolysisProduct *pp : protein->getProteolysisProducts())
            {
                // maintain lengths and approx position
                if (startsWithM)
                {
                    ProteolysisProduct tempVar2(
                        pp->getOneBasedBeginPosition(),
                        pp->getOneBasedEndPosition(),
                        StringHelper::formatSimple("DECOY {0}", pp->getType()));
                    decoyPP.push_back(&tempVar2);
                }
                else
                {
                    ProteolysisProduct tempVar3(
                        protein->getBaseSequence().length() - pp->getOneBasedEndPosition().value() + 1,
                        protein->getBaseSequence().length() - pp->getOneBasedBeginPosition().value() + 1,
                        StringHelper::formatSimple("DECOY {0}", pp->getType()));
                    decoyPP.push_back(&tempVar3);
                }
            }
    
            std::vector<DisulfideBond*> decoyDisulfides;
            for (DisulfideBond *disulfideBond : protein->getDisulfideBonds())
            {
                // maintain the cysteine localizations
                if (startsWithM)
                {
                    DisulfideBond tempVar4(
                        disulfideBond->getOneBasedBeginPosition() == 1 ? 1 :
                        protein->getBaseSequence().length() - disulfideBond->getOneBasedEndPosition() + 2,
                        protein->getBaseSequence().length() - disulfideBond->getOneBasedBeginPosition()+ 2,
                        StringHelper::formatSimple("DECOY {0}", disulfideBond->getDescription()));
                    decoyDisulfides.push_back(&tempVar4);
                }
                else
                {
                    DisulfideBond tempVar5(
                        protein->getBaseSequence().length() - disulfideBond->getOneBasedEndPosition() + 1,
                        protein->getBaseSequence().length() - disulfideBond->getOneBasedBeginPosition() + 1,
                        StringHelper::formatSimple("DECOY {0}", disulfideBond->getDescription()));
                    decoyDisulfides.push_back(&tempVar5);
                }
            }
    
            // reverse splice sites
            std::vector<SpliceSite*> spliceSites;
            for (SpliceSite *spliceSite : protein->getSpliceSites())
            {
                // maintain the starting methionine localization
                if (startsWithM && spliceSite->getOneBasedBeginPosition() == 1 &&
                    spliceSite->getOneBasedEndPosition() == 1)
                {
                    SpliceSite tempVar6(1, 1, StringHelper::formatSimple("DECOY {0}", spliceSite->getDescription()));
                    spliceSites.push_back(&tempVar6);
                }
                // maintain length, can't maintain localization to starting methionine in this case
                else if (startsWithM && spliceSite->getOneBasedBeginPosition() == 1)
                {
                    int end = protein->getBaseSequence().length() - spliceSite->getOneBasedBeginPosition() + 1;
                    int begin = end - spliceSite->getOneBasedEndPosition() + spliceSite->getOneBasedBeginPosition();
                    SpliceSite tempVar7(begin, end, StringHelper::formatSimple("DECOY {0}", spliceSite->getDescription()));
                    spliceSites.push_back(&tempVar7);
                }
                else if (startsWithM)
                {
                    SpliceSite tempVar8(protein->getBaseSequence().length() - spliceSite->getOneBasedEndPosition() + 2,
                                        protein->getBaseSequence().length() - spliceSite->getOneBasedBeginPosition() + 2,
                                        StringHelper::formatSimple("DECOY {0}", spliceSite->getDescription()));
                    spliceSites.push_back(&tempVar8);
                }
                // maintain length and localization
                else
                {
                    SpliceSite tempVar9(protein->getBaseSequence().length() - spliceSite->getOneBasedEndPosition() + 1,
                                        protein->getBaseSequence().length() - spliceSite->getOneBasedBeginPosition() + 1,
                                        StringHelper::formatSimple("DECOY {0}", spliceSite->getDescription()));
                    spliceSites.push_back(&tempVar9);
                }
            }
    
            auto tmp = protein->getSequenceVariations();
            std::vector<SequenceVariation*> decoyVariations = ReverseSequenceVariations(tmp, protein->getNonVariantProtein(),
                                                                                        reversedNonVariantSequence);
            auto tmp2 =                 protein->getAppliedSequenceVariations();
            std::vector<SequenceVariation*> decoyAppliedVariations = ReverseSequenceVariations(tmp2, protein, reversedSequence);
    
            auto decoyProtein = new Protein(reversedSequence, "DECOY_" + protein->getAccession(),
                                            protein->getOrganism(), protein->getGeneNames(),
                                            decoyModifications, decoyPP, protein->getName(), protein->getFullName(), true,
                                            protein->getIsContaminant(),
                                            std::vector<Proteomics::DatabaseReference*>(), decoyVariations,
                                            decoyAppliedVariations, protein->getSampleNameForVariants(),
                                            decoyDisulfides, spliceSites, protein->getDatabaseFilePath());
    
            {
                //std::lock_guard<std::mutex> lock(decoyProteins);
                decoyProteins.push_back(decoyProtein);
            }

            //C# TO C++ CONVERTER TODO TASK: A 'delete decoyProtein' statement was not added since
            //decoyProtein was passed to a method or constructor. Handle memory management manually.
        }

    //C# TO C++ CONVERTER TODO TASK: A 'delete tempVar' statement was not added since tempVar was
    //passed to a method or constructor. Handle memory management manually.
    return decoyProteins;
    }

    std::vector<SequenceVariation*> DecoyProteinGenerator::ReverseSequenceVariations(std::vector<SequenceVariation*> &forwardVariants,
                                                                                     Protein *protein, const std::string &reversedSequence)
    {
        std::vector<SequenceVariation*> decoyVariations;
        for (auto sv : forwardVariants)
        {
            // place reversed modifications (referencing variant sequence location)
            std::unordered_map<int, std::vector<Modification*>> decoyVariantModifications(sv->getOneBasedModifications().size());
            int variantSeqLength = protein->getBaseSequence().length() + sv->getVariantSequence().length() -
                sv->getOriginalSequence().length();
            bool startsWithM = protein->getBaseSequence()[0] == 'M';
            for (auto kvp : sv->getOneBasedModifications())
            {
                if (startsWithM && kvp.first > 1)
                {
                    decoyVariantModifications.emplace(variantSeqLength - kvp.first + 2, kvp.second);
                }
                else if (sv->getVariantSequence()[0] == 'M' && kvp.first == 1)
                {
                    decoyVariantModifications.emplace(1, kvp.second);
                }
                else if (kvp.first == 1)
                {
                    decoyVariantModifications.emplace(protein->getBaseSequence().length(), kvp.second);
                }
                else
                {
                    decoyVariantModifications.emplace(variantSeqLength - kvp.first + 1, kvp.second);
                }
            }

            // reverse sequence variant
            auto originalArray = sv->getOriginalSequence();
            auto variationArray = sv->getVariantSequence();
            int decoyEnd = protein->getBaseSequence().length() - sv->getOneBasedBeginPosition() + 2 +
                static_cast<int>(sv->getOneBasedEndPosition() == reversedSequence.length()) -
                static_cast<int>(sv->getOneBasedBeginPosition() == 1);
            int decoyBegin = decoyEnd - originalArray.size() + 1;
            //Array::Reverse(originalArray);
            //Array::Reverse(variationArray);
            std::reverse(originalArray.begin(), originalArray.end());
            std::reverse(variationArray.begin(), variationArray.end());
            
            // start loss, so the variant is at the end
            bool originalInitMet = sv->getOneBasedBeginPosition() == 1 && sv->getOriginalSequence()[0] == 'M';
            bool variantInitMet = sv->getOneBasedBeginPosition() == 1 && sv->getVariantSequence()[0] == 'M';
            bool startLoss = originalInitMet && !variantInitMet;
            if (startLoss)
            {
                SequenceVariation tempVar(protein->getBaseSequence().length() - sv->getOneBasedEndPosition() + 2,
                                          protein->getBaseSequence().length(),
                                          originalArray.substr(0, originalArray.size() - 1),
                                          variationArray,
                                          "DECOY VARIANT: " + sv->getDescription()->getDescription(),
                                          decoyVariantModifications);
                decoyVariations.push_back(&tempVar);
            }
            // both start with M, but there's more
            else if (sv->getVariantSequence()[0] == 'M' && sv->getOneBasedBeginPosition() == 1 &&
                     (sv->getOriginalSequence().length() > 1 || sv->getVariantSequence().length() > 1))
            {
                std::string original = originalArray.substr(0, originalArray.size() - 1);
                std::string variant = variationArray.substr(0, variationArray.size() - 1);
                SequenceVariation tempVar2(protein->getBaseSequence().length() - sv->getOneBasedEndPosition() + 2,
                                           protein->getBaseSequence().length(), original, variant,
                                           "DECOY VARIANT: " + sv->getDescription()->getDescription(),
                                           decoyVariantModifications);
                decoyVariations.push_back(&tempVar2);
            }
            // gained an initiating methionine
            else if (sv->getVariantSequence()[0] == 'M' && sv->getOneBasedBeginPosition() == 1)
            {
                SequenceVariation tempVar3(1, 1, originalArray, variationArray,
                                           "DECOY VARIANT: " + sv->getDescription()->getDescription(),
                                           decoyVariantModifications);
                decoyVariations.push_back(&tempVar3);
            }
            // starting methionine, but no variations on it
            else if (startsWithM)
            {
                SequenceVariation tempVar4(protein->getBaseSequence().length() - sv->getOneBasedEndPosition() + 2,
                                           protein->getBaseSequence().length() - sv->getOneBasedBeginPosition() + 2,
                                           originalArray, variationArray,
                                           "DECOY VARIANT: " + sv->getDescription()->getDescription(),
                                           decoyVariantModifications);
                decoyVariations.push_back(&tempVar4);
            }
            // no starting methionine
            else
            {
                SequenceVariation tempVar5(protein->getBaseSequence().length() - sv->getOneBasedEndPosition() + 1,
                                           protein->getBaseSequence().length() - sv->getOneBasedBeginPosition() + 1,
                                           originalArray, variationArray,
                                           "DECOY VARIANT: " + sv->getDescription()->getDescription(), decoyVariantModifications);
                decoyVariations.push_back(&tempVar5);
            }
        }
        return decoyVariations;
    }

    std::vector<Protein*> DecoyProteinGenerator::GenerateSlideDecoys(std::vector<Protein*> &proteins, int maxThreads)
    {
        std::vector<Protein*> decoyProteins;
        //ParallelOptions *tempVar = new ParallelOptions();
        //tempVar->MaxDegreeOfParallelism = maxThreads;
        //Parallel::ForEach(proteins, tempVar, [&] (std::any protein)
        for ( auto protein : proteins ) 
        {
            std::unordered_map<int, std::vector<Modification*>> decoyModifications;
            int numSlides = 20;
            auto sequenceArrayUnslided = protein->getBaseSequence();
            auto sequenceArraySlided = protein->getBaseSequence();
            decoyModifications = std::unordered_map<int, std::vector<Modification*>>();
            std::vector<DisulfideBond*> decoy_disulfides_slide;
            std::vector<SpliceSite*> spliceSitesSlide;
            if (protein->getBaseSequence()[0] == 'M' )
            {
                // Do not include the initiator methionine in shuffle!!!
                if (numSlides % sequenceArraySlided.size() - 1 == 0)
                {
                    numSlides++;
                }
                for (int i = 1; i < sequenceArraySlided.size(); i++)
                {
                    sequenceArraySlided[i] = sequenceArrayUnslided[GetOldShuffleIndex(i, numSlides, protein->getBaseSequence().length(),
                                                                                      true)];
                }
    
                decoyModifications = std::unordered_map<int, std::vector<Modification*>>(protein->getOneBasedPossibleLocalizedModifications().size());
                for (auto kvp : protein->getOneBasedPossibleLocalizedModifications())
                {
                    if (kvp.first > 1)
                    {
                        decoyModifications.emplace(GetOldShuffleIndex(kvp.first - 1, numSlides, protein->getBaseSequence().length(), true) + 1,
                                                   kvp.second);
                    }
                    else if (kvp.first == 1)
                    {
                        decoyModifications.emplace(1, kvp.second);
                    }
                }
            }
            else
            {
                if (numSlides % sequenceArraySlided.empty())
                {
                    numSlides++;
                }
                for (int i = 0; i < sequenceArraySlided.size(); i++)
                {
                    sequenceArraySlided[i] = sequenceArrayUnslided[GetOldShuffleIndex(i, numSlides, protein->getBaseSequence().length(), false)];
                }
                decoyModifications = std::unordered_map<int, std::vector<Modification*>>(protein->getOneBasedPossibleLocalizedModifications().size());
                for (auto kvp : protein->getOneBasedPossibleLocalizedModifications())
                {
                    decoyModifications.emplace(GetOldShuffleIndex(kvp.first - 1, numSlides, protein->getBaseSequence().length(), false) + 1, kvp.second);
                }
            }
            auto slided_sequence(sequenceArraySlided);
    
            std::vector<ProteolysisProduct*> decoyPPSlide;
            //can't keep all aa like you can with reverse, just keep it the same length
            for (ProteolysisProduct *pp : protein->getProteolysisProducts()) 
            {
                decoyPPSlide.push_back(pp);
            }
            for (DisulfideBond *disulfideBond : protein->getDisulfideBonds()) //these actually need the same cysteines...
            {
                DisulfideBond tempVar2(GetOldShuffleIndex(disulfideBond->getOneBasedBeginPosition() - 1, numSlides,
                                                          slided_sequence.length(), false) + 1,
                                       GetOldShuffleIndex(disulfideBond->getOneBasedEndPosition() - 1, numSlides,
                                                          slided_sequence.length(), false) + 1,
                                       "DECOY DISULFIDE BOND: " + disulfideBond->getDescription());
                decoy_disulfides_slide.push_back(&tempVar2);
            }
            for (SpliceSite *spliceSite : protein->getSpliceSites()) //these actually need the same cysteines...
            {
                SpliceSite tempVar3(GetOldShuffleIndex(spliceSite->getOneBasedBeginPosition() - 1, numSlides,
                                                       slided_sequence.length(), false) + 1,
                                    GetOldShuffleIndex(spliceSite->getOneBasedEndPosition() - 1, numSlides,
                                                       slided_sequence.length(), false) + 1,
                                    "DECOY SPLICE SITE: " + spliceSite->getDescription());
                spliceSitesSlide.push_back(&tempVar3);
            }
            std::vector<SequenceVariation*> decoyVariationsSlide;
            for (SequenceVariation *sv : protein->getSequenceVariations()) //No idea what's going on here. Review is appreciated.
            {
                auto originalArrayUnshuffled = sv->getOriginalSequence();
                auto variationArrayUnslided = sv->getVariantSequence();
                if (sv->getOneBasedBeginPosition() == 1)
                {
                    bool origInitM = sv->getOriginalSequence()[0] == 'M';
                    bool varInitM = sv->getVariantSequence()[0] == 'M';
                    if (origInitM && !varInitM)
                    {
                        SequenceVariation tempVar4(
                            1, "M", "",
                            "DECOY VARIANT: Initiator Methionine Change in " + sv->getDescription()->getDescription(),
                            std::unordered_map<int, std::vector<Modification*>>()); // LAST ARGUMENT ADDED BY EDGAR
                        decoyVariationsSlide.push_back(&tempVar4);
                    }
                    originalArrayUnshuffled = sv->getOriginalSequence().substr(static_cast<int>(origInitM));
                    variationArrayUnslided = sv->getVariantSequence().substr(static_cast<int>(varInitM));
                }
                int decoy_end = protein->getBaseSequence().length() - sv->getOneBasedBeginPosition() + 2 +
                    static_cast<int>(sv->getOneBasedEndPosition() == slided_sequence.size()) -
                    static_cast<int>(sv->getOneBasedBeginPosition() == 1);
                int decoy_begin = decoy_end - originalArrayUnshuffled.size() + 1;
                auto  originalArraySlided = sv->getOriginalSequence();
                auto variationArraySlided = sv->getVariantSequence();
    
                if (numSlides % originalArraySlided.empty())
                {
                    numSlides++;
                }
                for (int i = 0; i < originalArraySlided.size(); i++)
                {
                    originalArraySlided[i] = originalArrayUnshuffled[GetOldShuffleIndex(i, numSlides, originalArrayUnshuffled.size(),
                                                                                        false)];
                }
    
                if (numSlides % variationArraySlided.empty())
                {
                    numSlides++;
                }
                for (int i = 0; i < variationArraySlided.size(); i++)
                {
                    variationArraySlided[i] = variationArrayUnslided[GetOldShuffleIndex(i, numSlides, variationArrayUnslided.size(), false)];
                }
    
                SequenceVariation tempVar5(decoy_begin, decoy_end, originalArraySlided,
                                           variationArraySlided,
                                           "DECOY VARIANT: " + sv->getDescription()->getDescription(),
                                           std::unordered_map<int, std::vector<Modification*>>()); // LAST ARGUMENT ADDED BY EDGAR
                decoyVariationsSlide.push_back(&tempVar5);
            }
            auto decoyProteinSlide = new Protein(slided_sequence, "DECOY_" + protein->getAccession(),
                                                 protein->getOrganism(), protein->getGeneNames(),
                                                 decoyModifications, decoyPPSlide, protein->getName(),
                                                 protein->getFullName(), true, protein->getIsContaminant(),
                                                 std::vector<Proteomics::DatabaseReference*>(),
                                                 decoyVariationsSlide,
                                                 std::vector<Proteomics::SequenceVariation*>(),
                                                 protein->getSampleNameForVariants(),
                                                 decoy_disulfides_slide, spliceSitesSlide,
                                                 protein->getDatabaseFilePath());
            {
                // std::lock_guard<std::mutex> lock(decoyProteins);
                decoyProteins.push_back(decoyProteinSlide);
            }

            //C# TO C++ CONVERTER TODO TASK: A 'delete decoyProteinSlide' statement was not added since
            //decoyProteinSlide was passed to a method or constructor. Handle memory management manually.
        }

        //C# TO C++ CONVERTER TODO TASK: A 'delete tempVar' statement was not added since tempVar
        //was passed to a method or constructor. Handle memory management manually.
        return decoyProteins;
    }

    int DecoyProteinGenerator::GetOldShuffleIndex(int i, int numSlides, int sequenceLength, bool methioninePresent)
    {
        if (methioninePresent)
        {
            i--;
            sequenceLength--;
        }
        bool positiveDirection = i % 2 == 0;
        int oldIndex = i;

        if (positiveDirection)
        {
            oldIndex += numSlides;
        }
        else
        {
            oldIndex -= numSlides;
        }

        while (true)
        {
            if (oldIndex < 0)
            {
                positiveDirection = true;
            }
            else if (oldIndex >= sequenceLength)
            {
                positiveDirection = false;
            }
            else
            {
                return methioninePresent ? oldIndex + 1 : oldIndex;
            }

            if (positiveDirection)
            {
                oldIndex = (oldIndex * -1) - 1;
            }
            else
            {
                oldIndex = (sequenceLength * 2) - oldIndex - 1;
            }
        }
    }
}
