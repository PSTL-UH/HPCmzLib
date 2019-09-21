#include "DecoyProteinGenerator.h"
#include "../Proteomics/Protein/Protein.h"
#include "../Proteomics/Protein/SequenceVariation.h"
#include "../Proteomics/Modifications/Modification.h"

using namespace Proteomics;

namespace UsefulProteomicsDatabases
{

    std::vector<Protein*> DecoyProteinGenerator::GenerateDecoys(std::vector<Protein*> &proteins, DecoyType decoyType, int maxThreads)
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
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
            throw std::invalid_argument("Decoy type " + decoyType.ToString() + " is not implemented.");
        }
    }

    std::vector<Protein*> DecoyProteinGenerator::GenerateReverseDecoys(std::vector<Protein*> &proteins, int maxThreads)
    {
        std::vector<Protein*> decoyProteins;
        ParallelOptions *tempVar = new ParallelOptions();
        tempVar->MaxDegreeOfParallelism = maxThreads;
        Parallel::ForEach(proteins, tempVar, [&] (std::any protein)
        {
            // reverse sequence
            // Do not include the initiator methionine in reversal!!!
            std::vector<char> sequenceArray = protein::BaseSequence::ToCharArray();
            bool startsWithM = protein::BaseSequence->StartsWith("M", StringComparison::Ordinal);
            if (startsWithM)
            {
                Array::Reverse(sequenceArray, 1, protein::BaseSequence->Length - 1);
            }
            else
            {
                Array::Reverse(sequenceArray);
            }
            std::string reversedSequence = std::string(sequenceArray);
    
            // reverse nonvariant sequence
            // Do not include the initiator methionine in reversal!!!
            std::vector<char> nonVariantSequenceArray = protein::NonVariantProtein::BaseSequence::ToCharArray();
            if (protein::NonVariantProtein::BaseSequence->StartsWith("M", StringComparison::Ordinal))
            {
                Array::Reverse(nonVariantSequenceArray, 1, protein::NonVariantProtein::BaseSequence->Length - 1);
            }
            else
            {
                Array::Reverse(nonVariantSequenceArray);
            }
            std::string reversedNonVariantSequence = std::string(nonVariantSequenceArray);
    
            // reverse modifications
            std::unordered_map<int, std::vector<Modification*>> decoyModifications;
            if (startsWithM)
            {
                decoyModifications = std::unordered_map<int, std::vector<Modification*>>(protein::OneBasedPossibleLocalizedModifications->Count);
                for (auto kvp : protein::OneBasedPossibleLocalizedModifications)
                {
                    if (kvp->Key > 1)
                    {
                        decoyModifications.emplace(protein::BaseSequence->Length - kvp->Key + 2, kvp->Value);
                    }
                    else if (kvp->Key == 1)
                    {
                        decoyModifications.emplace(1, kvp->Value);
                    }
                }
            }
            else
            {
                decoyModifications = std::unordered_map<int, std::vector<Modification*>>(protein::OneBasedPossibleLocalizedModifications->Count);
                for (auto kvp : protein::OneBasedPossibleLocalizedModifications)
                {
                    decoyModifications.emplace(protein::BaseSequence->Length - kvp->Key + 1, kvp->Value);
                }
            }
    
            // reverse proteolysis products
            std::vector<ProteolysisProduct*> decoyPP;
            for (ProteolysisProduct *pp : protein::ProteolysisProducts)
            {
                // maintain lengths and approx position
                if (startsWithM)
                {
                    ProteolysisProduct tempVar2(pp->getOneBasedBeginPosition(), pp->getOneBasedEndPosition(), StringHelper::formatSimple("DECOY {0}", pp->getType()));
                    decoyPP.push_back(&tempVar2);
                }
                else
                {
                    ProteolysisProduct tempVar3(protein::BaseSequence->Length - pp->getOneBasedEndPosition() + 1, protein::BaseSequence->Length - pp->getOneBasedBeginPosition() + 1, StringHelper::formatSimple("DECOY {0}", pp->getType()));
                    decoyPP.push_back(&tempVar3);
                }
            }
    
            std::vector<DisulfideBond*> decoyDisulfides;
            for (DisulfideBond *disulfideBond : protein::DisulfideBonds)
            {
                // maintain the cysteine localizations
                if (startsWithM)
                {
                    DisulfideBond tempVar4(disulfideBond->getOneBasedBeginPosition() == 1 ? 1 : protein::BaseSequence->Length - disulfideBond->getOneBasedEndPosition() + 2, protein::BaseSequence->Length - disulfideBond->getOneBasedBeginPosition() + 2, StringHelper::formatSimple("DECOY {0}", disulfideBond->getDescription()));
                    decoyDisulfides.push_back(&tempVar4);
                }
                else
                {
                    DisulfideBond tempVar5(protein::BaseSequence->Length - disulfideBond->getOneBasedEndPosition() + 1, protein::BaseSequence->Length - disulfideBond->getOneBasedBeginPosition() + 1, StringHelper::formatSimple("DECOY {0}", disulfideBond->getDescription()));
                    decoyDisulfides.push_back(&tempVar5);
                }
            }
    
            // reverse splice sites
            std::vector<SpliceSite*> spliceSites;
            for (SpliceSite *spliceSite : protein::SpliceSites)
            {
                // maintain the starting methionine localization
                if (startsWithM && spliceSite->getOneBasedBeginPosition() == 1 && spliceSite->getOneBasedEndPosition() == 1)
                {
                    SpliceSite tempVar6(1, 1, StringHelper::formatSimple("DECOY {0}", spliceSite->getDescription()));
                    spliceSites.push_back(&tempVar6);
                }
                // maintain length, can't maintain localization to starting methionine in this case
                else if (startsWithM && spliceSite->getOneBasedBeginPosition() == 1)
                {
                    int end = protein::BaseSequence->Length - spliceSite->getOneBasedBeginPosition() + 1;
                    int begin = end - spliceSite->getOneBasedEndPosition() + spliceSite->getOneBasedBeginPosition();
                    SpliceSite tempVar7(begin, end, StringHelper::formatSimple("DECOY {0}", spliceSite->getDescription()));
                    spliceSites.push_back(&tempVar7);
                }
                else if (startsWithM)
                {
                    SpliceSite tempVar8(protein::BaseSequence->Length - spliceSite->getOneBasedEndPosition() + 2, protein::BaseSequence->Length - spliceSite->getOneBasedBeginPosition() + 2, StringHelper::formatSimple("DECOY {0}", spliceSite->getDescription()));
                    spliceSites.push_back(&tempVar8);
                }
                // maintain length and localization
                else
                {
                    SpliceSite tempVar9(protein::BaseSequence->Length - spliceSite->getOneBasedEndPosition() + 1, protein::BaseSequence->Length - spliceSite->getOneBasedBeginPosition() + 1, StringHelper::formatSimple("DECOY {0}", spliceSite->getDescription()));
                    spliceSites.push_back(&tempVar9);
                }
            }
    
            std::vector<SequenceVariation*> decoyVariations = ReverseSequenceVariations(protein::SequenceVariations, protein::NonVariantProtein, reversedNonVariantSequence);
            std::vector<SequenceVariation*> decoyAppliedVariations = ReverseSequenceVariations(protein::AppliedSequenceVariations, protein, reversedSequence);
    
            auto decoyProtein = new Protein(reversedSequence, "DECOY_" + protein::Accession, protein::Organism, protein::GeneNames::ToList(), decoyModifications, decoyPP, protein->Name, protein->FullName, true, protein::IsContaminant, nullptr, decoyVariations, decoyAppliedVariations, protein::SampleNameForVariants, decoyDisulfides, spliceSites, protein::DatabaseFilePath);
    
            {
                std::lock_guard<std::mutex> lock(decoyProteins);
                decoyProteins.push_back(decoyProtein);
            }

//C# TO C++ CONVERTER TODO TASK: A 'delete decoyProtein' statement was not added since decoyProtein was passed to a method or constructor. Handle memory management manually.
        });

//C# TO C++ CONVERTER TODO TASK: A 'delete tempVar' statement was not added since tempVar was passed to a method or constructor. Handle memory management manually.
        return decoyProteins;
    }

    std::vector<SequenceVariation*> DecoyProteinGenerator::ReverseSequenceVariations(std::vector<SequenceVariation*> &forwardVariants, Protein *protein, const std::string &reversedSequence)
    {
        std::vector<SequenceVariation*> decoyVariations;
        for (auto sv : forwardVariants)
        {
            // place reversed modifications (referencing variant sequence location)
            std::unordered_map<int, std::vector<Modification*>> decoyVariantModifications(sv->getOneBasedModifications().size());
            int variantSeqLength = protein->getBaseSequence().length() + sv->getVariantSequence().length() - sv->getOriginalSequence().length();
            bool startsWithM = protein->getBaseSequence().StartsWith("M", StringComparison::Ordinal);
            for (auto kvp : sv->getOneBasedModifications())
            {
                if (startsWithM && kvp.Key > 1)
                {
                    decoyVariantModifications.emplace(variantSeqLength - kvp.Key + 2, kvp.Value);
                }
                else if (sv->getVariantSequence().StartsWith("M", StringComparison::Ordinal) && kvp.Key == 1)
                {
                    decoyVariantModifications.emplace(1, kvp.Value);
                }
                else if (kvp.Key == 1)
                {
                    decoyVariantModifications.emplace(protein->getBaseSequence().length(), kvp.Value);
                }
                else
                {
                    decoyVariantModifications.emplace(variantSeqLength - kvp.Key + 1, kvp.Value);
                }
            }

            // reverse sequence variant
            std::vector<char> originalArray = sv->getOriginalSequence().ToArray();
            std::vector<char> variationArray = sv->getVariantSequence().ToArray();
            int decoyEnd = protein->getBaseSequence().length() - sv->getOneBasedBeginPosition() + 2 + static_cast<int>(sv->getOneBasedEndPosition() == reversedSequence.length()) - static_cast<int>(sv->getOneBasedBeginPosition() == 1);
            int decoyBegin = decoyEnd - originalArray.size() + 1;
            Array::Reverse(originalArray);
            Array::Reverse(variationArray);

            // start loss, so the variant is at the end
            bool originalInitMet = sv->getOneBasedBeginPosition() == 1 && sv->getOriginalSequence().StartsWith("M", StringComparison::Ordinal);
            bool variantInitMet = sv->getOneBasedBeginPosition() == 1 && sv->getVariantSequence().StartsWith("M", StringComparison::Ordinal);
            bool startLoss = originalInitMet && !variantInitMet;
            if (startLoss)
            {
                SequenceVariation tempVar(protein->getBaseSequence().length() - sv->getOneBasedEndPosition() + 2, protein->getBaseSequence().length(), (new std::string(originalArray))->substr(0, originalArray.size() - 1), new std::string(variationArray), "DECOY VARIANT: " + sv->getDescription(), decoyVariantModifications);
                decoyVariations.push_back(&tempVar);
            }
            // both start with M, but there's more
            else if (sv->getVariantSequence().StartsWith("M", StringComparison::Ordinal) && sv->getOneBasedBeginPosition() == 1 && (sv->getOriginalSequence().length() > 1 || sv->getVariantSequence().length() > 1))
            {
                std::string original = (std::string(originalArray))->substr(0, originalArray.size() - 1);
                std::string variant = (std::string(variationArray))->substr(0, variationArray.size() - 1);
                SequenceVariation tempVar2(protein->getBaseSequence().length() - sv->getOneBasedEndPosition() + 2, protein->getBaseSequence().length(), original, variant, "DECOY VARIANT: " + sv->getDescription(), decoyVariantModifications);
                decoyVariations.push_back(&tempVar2);
            }
            // gained an initiating methionine
            else if (sv->getVariantSequence().StartsWith("M", StringComparison::Ordinal) && sv->getOneBasedBeginPosition() == 1)
            {
                SequenceVariation tempVar3(1, 1, new std::string(originalArray), new std::string(variationArray), "DECOY VARIANT: " + sv->getDescription(), decoyVariantModifications);
                decoyVariations.push_back(&tempVar3);
            }
            // starting methionine, but no variations on it
            else if (startsWithM)
            {
                SequenceVariation tempVar4(protein->getBaseSequence().length() - sv->getOneBasedEndPosition() + 2, protein->getBaseSequence().length() - sv->getOneBasedBeginPosition() + 2, new std::string(originalArray), new std::string(variationArray), "DECOY VARIANT: " + sv->getDescription(), decoyVariantModifications);
                decoyVariations.push_back(&tempVar4);
            }
            // no starting methionine
            else
            {
                SequenceVariation tempVar5(protein->getBaseSequence().length() - sv->getOneBasedEndPosition() + 1, protein->getBaseSequence().length() - sv->getOneBasedBeginPosition() + 1, new std::string(originalArray), new std::string(variationArray), "DECOY VARIANT: " + sv->getDescription(), decoyVariantModifications);
                decoyVariations.push_back(&tempVar5);
            }
        }
        return decoyVariations;
    }

    std::vector<Protein*> DecoyProteinGenerator::GenerateSlideDecoys(std::vector<Protein*> &proteins, int maxThreads)
    {
        std::vector<Protein*> decoyProteins;
        ParallelOptions *tempVar = new ParallelOptions();
        tempVar->MaxDegreeOfParallelism = maxThreads;
        Parallel::ForEach(proteins, tempVar, [&] (std::any protein)
        {
            std::unordered_map<int, std::vector<Modification*>> decoyModifications;
            int numSlides = 20;
            std::vector<char> sequenceArrayUnslided = protein::BaseSequence::ToCharArray();
            std::vector<char> sequenceArraySlided = protein::BaseSequence::ToCharArray();
            decoyModifications = std::unordered_map<int, std::vector<Modification*>>();
            std::vector<DisulfideBond*> decoy_disulfides_slide;
            std::vector<SpliceSite*> spliceSitesSlide;
            if (protein::BaseSequence->StartsWith("M", StringComparison::Ordinal))
            {
                // Do not include the initiator methionine in shuffle!!!
                if (numSlides % sequenceArraySlided.size() - 1 == 0)
                {
                    numSlides++;
                }
                for (int i = 1; i < sequenceArraySlided.size(); i++)
                {
                    sequenceArraySlided[i] = sequenceArrayUnslided[GetOldShuffleIndex(i, numSlides, protein::BaseSequence->Length, true)];
                }
    
                decoyModifications = std::unordered_map<int, std::vector<Modification*>>(protein::OneBasedPossibleLocalizedModifications->Count);
                for (auto kvp : protein::OneBasedPossibleLocalizedModifications)
                {
                    if (kvp->Key > 1)
                    {
                        decoyModifications.emplace(GetOldShuffleIndex(kvp->Key - 1, numSlides, protein::BaseSequence->Length, true) + 1, kvp->Value);
                    }
                    else if (kvp->Key == 1)
                    {
                        decoyModifications.emplace(1, kvp->Value);
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
                    sequenceArraySlided[i] = sequenceArrayUnslided[GetOldShuffleIndex(i, numSlides, protein::BaseSequence->Length, false)];
                }
                decoyModifications = std::unordered_map<int, std::vector<Modification*>>(protein::OneBasedPossibleLocalizedModifications->Count);
                for (auto kvp : protein::OneBasedPossibleLocalizedModifications)
                {
                    decoyModifications.emplace(GetOldShuffleIndex(kvp->Key - 1, numSlides, protein::BaseSequence->Length, false) + 1, kvp->Value);
                }
            }
            auto slided_sequence = std::string(sequenceArraySlided);
    
            std::vector<ProteolysisProduct*> decoyPPSlide;
            for (ProteolysisProduct *pp : protein::ProteolysisProducts) //can't keep all aa like you can with reverse, just keep it the same length
            {
                decoyPPSlide.push_back(pp);
            }
            for (DisulfideBond *disulfideBond : protein::DisulfideBonds) //these actually need the same cysteines...
            {
                DisulfideBond tempVar2(GetOldShuffleIndex(disulfideBond->getOneBasedBeginPosition() - 1, numSlides, slided_sequence.length(), false) + 1, GetOldShuffleIndex(disulfideBond->getOneBasedEndPosition() - 1, numSlides, slided_sequence.length(), false) + 1, "DECOY DISULFIDE BOND: " + disulfideBond->getDescription());
                decoy_disulfides_slide.push_back(&tempVar2);
            }
            for (SpliceSite *spliceSite : protein::SpliceSites) //these actually need the same cysteines...
            {
                SpliceSite tempVar3(GetOldShuffleIndex(spliceSite->getOneBasedBeginPosition() - 1, numSlides, slided_sequence.length(), false) + 1, GetOldShuffleIndex(spliceSite->getOneBasedEndPosition() - 1, numSlides, slided_sequence.length(), false) + 1, "DECOY SPLICE SITE: " + spliceSite->getDescription());
                spliceSitesSlide.push_back(&tempVar3);
            }
            std::vector<SequenceVariation*> decoyVariationsSlide;
            for (SequenceVariation *sv : protein::SequenceVariations) //No idea what's going on here. Review is appreciated.
            {
                std::vector<char> originalArrayUnshuffled = sv->getOriginalSequence().ToArray();
                std::vector<char> variationArrayUnslided = sv->getVariantSequence().ToArray();
                if (sv->getOneBasedBeginPosition() == 1)
                {
                    bool origInitM = sv->getOriginalSequence().StartsWith("M", StringComparison::Ordinal);
                    bool varInitM = sv->getVariantSequence().StartsWith("M", StringComparison::Ordinal);
                    if (origInitM && !varInitM)
                    {
                        SequenceVariation tempVar4(1, "M", "", "DECOY VARIANT: Initiator Methionine Change in " + sv->getDescription());
                        decoyVariationsSlide.push_back(&tempVar4);
                    }
                    originalArrayUnshuffled = sv->getOriginalSequence().substr(static_cast<int>(origInitM))->ToArray();
                    variationArrayUnslided = sv->getVariantSequence().substr(static_cast<int>(varInitM))->ToArray();
                }
                int decoy_end = protein::BaseSequence->Length - sv->getOneBasedBeginPosition() + 2 + static_cast<int>(sv->getOneBasedEndPosition() == slided_sequence.length()) - static_cast<int>(sv->getOneBasedBeginPosition() == 1);
                int decoy_begin = decoy_end - originalArrayUnshuffled.size() + 1;
                std::vector<char> originalArraySlided = sv->getOriginalSequence().ToArray();
                std::vector<char> variationArraySlided = sv->getVariantSequence().ToArray();
    
                if (numSlides % originalArraySlided.empty())
                {
                    numSlides++;
                }
                for (int i = 0; i < originalArraySlided.size(); i++)
                {
                    originalArraySlided[i] = originalArrayUnshuffled[GetOldShuffleIndex(i, numSlides, originalArrayUnshuffled.size(), false)];
                }
    
                if (numSlides % variationArraySlided.empty())
                {
                    numSlides++;
                }
                for (int i = 0; i < variationArraySlided.size(); i++)
                {
                    variationArraySlided[i] = variationArrayUnslided[GetOldShuffleIndex(i, numSlides, variationArrayUnslided.size(), false)];
                }
    
                SequenceVariation tempVar5(decoy_begin, decoy_end, new std::string(originalArraySlided), new std::string(variationArraySlided), "DECOY VARIANT: " + sv->getDescription());
                decoyVariationsSlide.push_back(&tempVar5);
            }
            auto decoyProteinSlide = new Protein(slided_sequence, "DECOY_" + protein::Accession, protein::Organism, protein::GeneNames::ToList(), decoyModifications, decoyPPSlide, protein->Name, protein->FullName, true, protein::IsContaminant, nullptr, decoyVariationsSlide, nullptr, protein::SampleNameForVariants, decoy_disulfides_slide, spliceSitesSlide, protein::DatabaseFilePath);
            {
                std::lock_guard<std::mutex> lock(decoyProteins);
                decoyProteins.push_back(decoyProteinSlide);
            }

//C# TO C++ CONVERTER TODO TASK: A 'delete decoyProteinSlide' statement was not added since decoyProteinSlide was passed to a method or constructor. Handle memory management manually.
        });

//C# TO C++ CONVERTER TODO TASK: A 'delete tempVar' statement was not added since tempVar was passed to a method or constructor. Handle memory management manually.
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
