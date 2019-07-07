#include "VariantApplication.h"
#include "Protein.h"
#include "SequenceVariation.h"
#include "ProteolysisProduct.h"
#include "../Modifications/Modification.h"


namespace Proteomics
{

    std::string VariantApplication::GetAccession(Protein *protein, std::vector<SequenceVariation*> &appliedSequenceVariations)
    {
        std::vector<std::string> accSplit = StringHelper::split(protein->getAccession(), '_');
        std::string baseAcc = StringHelper::startsWith(protein->getAccession(), "DECOY_") ? StringHelper::formatSimple("{0}_{1}", accSplit[0], accSplit[1]) : accSplit[0];
        return baseAcc + (appliedSequenceVariations.empty() || appliedSequenceVariations.size()() == 0 ? "" : StringHelper::formatSimple("_{0}", CombineSimpleStrings(appliedSequenceVariations)));
    }

    bool VariantApplication::IsSequenceVariantModification(SequenceVariation *appliedVariant, int variantProteinIndex)
    {
        return appliedVariant != nullptr && appliedVariant->Includes(variantProteinIndex);
    }

    int VariantApplication::RestoreModificationIndex(Protein *protein, int variantProteinIndex)
    {
        return variantProteinIndex - protein->getAppliedSequenceVariations().Where([&] (std::any v)
        {
            return v::OneBasedEndPosition < variantProteinIndex;
        }).Sum([&] (std::any v)
        {
            return v::VariantSequence->Length - v::OriginalSequence->Length;
        });
    }

    std::string VariantApplication::CombineSimpleStrings(std::vector<SequenceVariation*> &variations)
    {
        return variations.empty() || variations.size()() == 0? "" : std::string::Join("_", variations.Select([&] (std::any v)
        {
            v::SimpleString();
        }));
    }

    std::string VariantApplication::CombineDescriptions(std::vector<SequenceVariation*> &variations)
    {
        return variations.empty() || variations.size()() == 0 ? "" : std::string::Join(", variant:", variations.Select([&] (std::any d)
        {
            d::Description;
        }));
    }

    std::vector<Protein*> VariantApplication::ApplyVariants(Protein *protein, std::vector<SequenceVariation*> &sequenceVariations, int maxAllowedVariantsForCombinitorics, int minAlleleDepth)
    {
        std::vector<SequenceVariation*> uniqueEffectsToApply = sequenceVariations.GroupBy([&] (std::any v)
        {
            v::SimpleString();
        })->Select([&] (std::any x)
        {
            x::First();
        }).Where([&] (std::any v)
        {
            return v::Description->Genotypes->Count > 0;
        }).OrderByDescending([&] (std::any v)
        {
            v::OneBasedBeginPosition;
        }).ToList();

        Protein *proteinCopy = new Protein(protein->getBaseSequence(), protein, std::vector<SequenceVariation>(), protein->getProteolysisProducts(), protein->getOneBasedPossibleLocalizedModifications(), "");

        // If there aren't any variants to apply, just return the base protein
        if (uniqueEffectsToApply.empty())
        {
            delete proteinCopy;
            return std::vector<Protein*> {proteinCopy};
        }

        std::unordered_set<std::string> individuals = std::unordered_set<std::string>(uniqueEffectsToApply.SelectMany([&] (std::any v)
        {
            v::Description->Genotypes->Keys;
        }));
        std::vector<Protein*> variantProteins;

        // loop through genotypes for each sample/individual (e.g. tumor and normal)
        for (auto individual : individuals)
        {
            bool tooManyHeterozygousVariants = uniqueEffectsToApply.size()([&] (std::any v)
            {
                v::Description->Heterozygous[individual];
            }) > maxAllowedVariantsForCombinitorics;
            std::vector<Protein*> newVariantProteins = {proteinCopy};
            for (auto variant : uniqueEffectsToApply)
            {
                bool variantAlleleIsInTheGenotype = variant->getDescription()->getGenotypes()[individual]->Contains(std::to_string(variant->getDescription()->getAlleleIndex())); // should catch the case where it's -1 if the INFO isn't from SnpEff
                if (!variantAlleleIsInTheGenotype)
                {
                    continue;
                }
                bool isHomozygousAlternate = variant->getDescription()->getHomozygous()[individual] && variant->getDescription()->getGenotypes()[individual]->All([&] (std::any d)
                {
                delete proteinCopy;
                    return d == std::to_string(variant->getDescription()->getAlleleIndex());
                }); // note this isn't a great test for homozygosity, since the genotype could be 1/2 and this would still return true. But currently, alleles 1 and 2 will be included as separate variants, so this is fine for now.
                int depthRef;
                bool isDeepReferenceAllele = int::TryParse(variant->getDescription()->getAlleleDepths()[individual][0], depthRef) && depthRef >= minAlleleDepth;
                int depthAlt;
                bool isDeepAlternateAllele = int::TryParse(variant->getDescription()->getAlleleDepths()[individual][variant->getDescription()->getAlleleIndex()], depthAlt) && depthAlt >= minAlleleDepth;

                // homozygous alternate
                if (isHomozygousAlternate && isDeepAlternateAllele)
                {
                    newVariantProteins = newVariantProteins.Select([&] (std::any p)
                    {
                        ApplySingleVariant(variant, p, individual);
                    }).ToList();
                }

                // heterozygous basic
                // first protein with variants contains all homozygous variation, second contains all variations
                else if (variant->getDescription()->getHeterozygous()[individual] && tooManyHeterozygousVariants)
                {
                    if (isDeepAlternateAllele && isDeepReferenceAllele)
                    {
                        if (newVariantProteins.size() == 1 && maxAllowedVariantsForCombinitorics > 0)
                        {
                            Protein *variantProtein = ApplySingleVariant(variant, newVariantProteins[0], individual);
                            newVariantProteins.push_back(variantProtein);
                        }
                        else if (maxAllowedVariantsForCombinitorics > 0)
                        {
                            newVariantProteins[1] = ApplySingleVariant(variant, newVariantProteins[1], individual);
                        }
                        else
                        {
                            // no heterozygous variants
                        }
                    }
                    else if (isDeepAlternateAllele && maxAllowedVariantsForCombinitorics > 0)
                    {
                        newVariantProteins = newVariantProteins.Select([&] (std::any p)
                        {
                            ApplySingleVariant(variant, p, individual);
                        }).ToList();
                    }
                    else
                    {
                        // keep reference only
                    }
                }

                // heterozygous combinitorics
                else if (variant->getDescription()->getHeterozygous()[individual] && isDeepAlternateAllele && !tooManyHeterozygousVariants)
                {
                    std::vector<Protein*> combinitoricProteins;

                    for (auto ppp : newVariantProteins)
                    {
                        if (isDeepAlternateAllele && maxAllowedVariantsForCombinitorics > 0 && isDeepReferenceAllele)
                        {
                            // keep reference allele
                            if (variant->getDescription()->getGenotypes()[individual]->Contains("0"))
                            {
                                combinitoricProteins.push_back(ppp);
                            }

                            // alternate allele (replace all, since in heterozygous with two alternates, both alternates are included)
                            combinitoricProteins.push_back(ApplySingleVariant(variant, ppp, individual));
                        }
                        else if (isDeepAlternateAllele && maxAllowedVariantsForCombinitorics > 0)
                        {
                            combinitoricProteins.push_back(ApplySingleVariant(variant, ppp, individual));
                        }
                        else if (variant->getDescription()->getGenotypes()[individual]->Contains("0"))
                        {
                            combinitoricProteins.push_back(ppp);
                        }
                        else
                        {
                            // must be two alternate alleles with not enough depth
                        }
                    }
                    newVariantProteins = combinitoricProteins;
                }
            }
            variantProteins.insert(variantProteins.end(), newVariantProteins.begin(), newVariantProteins.end());
        }

        delete proteinCopy;
        return variantProteins.GroupBy([&] (std::any x)
        {
            x::BaseSequence;
        })->Select([&] (std::any x)
        {
            x::First();
        }).ToList();

        delete proteinCopy;
    }

    Protein *VariantApplication::ApplySingleVariant(SequenceVariation *variantGettingApplied, Protein *protein, const std::string &individual)
    {
        std::string seqBefore = protein->getBaseSequence().substr(0, variantGettingApplied->getOneBasedBeginPosition() - 1);
        std::string seqVariant = variantGettingApplied->getVariantSequence();
        int afterIdx = variantGettingApplied->getOneBasedBeginPosition() + variantGettingApplied->getOriginalSequence().length() - 1;

        SequenceVariation *variantAfterApplication = new SequenceVariation(variantGettingApplied->getOneBasedBeginPosition(), variantGettingApplied->getOneBasedBeginPosition() + variantGettingApplied->getVariantSequence().length() - 1, variantGettingApplied->getOriginalSequence(), variantGettingApplied->getVariantSequence(), variantGettingApplied->getDescription()->getDescription(), variantGettingApplied->getOneBasedModifications().ToDictionary([&] (std::any kv)
        {
            kv::Key;
        }, [&] (std::any kv)
        {
            kv->Value;
        }));

        // check to see if there is incomplete indel overlap, which would lead to weird variant sequences
        // complete overlap is okay, since it will be overwritten; this can happen if there are two alternate alleles,
        //    e.g. reference sequence is wrong at that point
        bool intersectsAppliedRegionIncompletely = protein->getAppliedSequenceVariations().Any([&] (std::any x)
        {
        delete variantAfterApplication;
            return variantGettingApplied->Intersects(x) && !variantGettingApplied->Includes(x);
        });
        std::vector<SequenceVariation*> appliedVariations = {variantAfterApplication};
        std::string seqAfter = "";
        if (intersectsAppliedRegionIncompletely)
        {
            // use original protein sequence for the remaining sequence
            seqAfter = protein->getBaseSequence().length() - afterIdx <= 0 ? "" : protein->getNonVariantProtein()->getBaseSequence().substr(afterIdx);
        }
        else
        {
            // use this variant protein sequence for the remaining sequence
            seqAfter = protein->getBaseSequence().length() - afterIdx <= 0 ? "" : protein->getBaseSequence().substr(afterIdx);
            appliedVariations = appliedVariations.Concat(protein->getAppliedSequenceVariations().Where([&] (std::any x)
            {
                !variantGettingApplied->Includes(x);
            }))->ToList();
        }
        std::string variantSequence = (seqBefore + seqVariant + seqAfter).Split('*')[0]; // there may be a stop gained

        // adjust indices
        std::vector<ProteolysisProduct*> adjustedProteolysisProducts = AdjustProteolysisProductIndices(variantGettingApplied, variantSequence, protein, protein->getProteolysisProducts());
        std::unordered_map<int, std::vector<Modification*>> adjustedModifications = AdjustModificationIndices(variantGettingApplied, variantSequence, protein);
        std::vector<SequenceVariation*> adjustedAppliedVariations = AdjustSequenceVariationIndices(variantGettingApplied, variantSequence, appliedVariations);

        delete variantAfterApplication;
        return new Protein(variantSequence, protein, adjustedAppliedVariations, adjustedProteolysisProducts, adjustedModifications, individual);
    }

    std::vector<SequenceVariation*> VariantApplication::AdjustSequenceVariationIndices(SequenceVariation *variantGettingApplied, const std::string &variantAppliedProteinSequence, std::vector<SequenceVariation*> &alreadyAppliedVariations)
    {
        std::vector<SequenceVariation*> variations;
        if (alreadyAppliedVariations.empty())
        {
            return variations;
        }
        for (auto v : alreadyAppliedVariations)
        {
            int addedIdx = alreadyAppliedVariations.Where([&] (std::any applied)
            {
                return applied::OneBasedEndPosition < v->getOneBasedBeginPosition();
            }).Sum([&] (std::any applied)
            {
                return applied::VariantSequence->Length - applied::OriginalSequence->Length;
            });

            // variant was entirely before the one being applied (shouldn't happen because of order of applying variants)
            // or it's the current variation
            if (v->getDescription()->Equals(variantGettingApplied->getDescription()) || v->getOneBasedEndPosition() - addedIdx < variantGettingApplied->getOneBasedBeginPosition())
            {
                variations.push_back(v);
            }

            // adjust indices based on new included sequence, minding possible overlaps to be filtered later
            else
            {
                int intersectOneBasedStart = std::max(variantGettingApplied->getOneBasedBeginPosition(), v->getOneBasedBeginPosition());
                int intersectOneBasedEnd = std::min(variantGettingApplied->getOneBasedEndPosition(), v->getOneBasedEndPosition());
                int overlap = intersectOneBasedEnd < intersectOneBasedStart ? 0 : intersectOneBasedEnd - intersectOneBasedStart + 1; // there's some overlap
                int sequenceLengthChange = variantGettingApplied->getVariantSequence().length() - variantGettingApplied->getOriginalSequence().length();
                int begin = v->getOneBasedBeginPosition() + sequenceLengthChange - overlap;
                if (begin > variantAppliedProteinSequence.length())
                {
                    continue; // cut out by a stop gain
                }
                int end = v->getOneBasedEndPosition() + sequenceLengthChange - overlap;
                if (end > variantAppliedProteinSequence.length())
                {
                    end = variantAppliedProteinSequence.length(); // end shortened by a stop gain
                }
                SequenceVariation tempVar(begin, end, v->getOriginalSequence(), v->getVariantSequence(), v->getDescription()->getDescription(), v->getOneBasedModifications().ToDictionary([&] (std::any kv)
                {
                    kv::Key;
                }, [&] (std::any kv)
                {
                    kv->Value;
                }));
                variations.push_back(&tempVar);
            }
        }
        return variations;
    }

    std::vector<ProteolysisProduct*> VariantApplication::AdjustProteolysisProductIndices(SequenceVariation *variant, const std::string &variantAppliedProteinSequence, Protein *protein, std::vector<ProteolysisProduct*> &proteolysisProducts)
    {
        std::vector<ProteolysisProduct*> products;
        if (proteolysisProducts.empty())
        {
            return products;
        }
        int sequenceLengthChange = variant->getVariantSequence().length() - variant->getOriginalSequence().length();
        for (ProteolysisProduct *p : proteolysisProducts.Where([&] (std::any p)
        {
            return p->getOneBasedEndPosition() && p->getOneBasedBeginPosition();
        }))
        {
            // proteolysis product is entirely before the variant
            if (variant->getOneBasedBeginPosition() > p::OneBasedEndPosition)
            {
                products.push_back(p);
            }
            // proteolysis product straddles the variant, but the cleavage site(s) are still intact; the ends aren't considered cleavage sites
            else if ((p::OneBasedBeginPosition < variant->getOneBasedBeginPosition() || p->OneBasedBeginPosition == 1 || p->OneBasedBeginPosition == 2) && (p::OneBasedEndPosition > variant->getOneBasedEndPosition() || p->OneBasedEndPosition == protein->getNonVariantProtein()->getBaseSequence().length()))
            {
                if (StringHelper::endsWith(variant->getVariantSequence(), "*"))
                {
                    ProteolysisProduct tempVar(p::OneBasedBeginPosition, std::make_optional(variantAppliedProteinSequence.length()), p::Type);
                    products.push_back(&tempVar);
                }
                else if (p::OneBasedEndPosition + sequenceLengthChange <= variantAppliedProteinSequence.length())
                {
                    ProteolysisProduct tempVar2(p::OneBasedBeginPosition, p::OneBasedEndPosition + sequenceLengthChange, p::Type);
                    products.push_back(&tempVar2);
                }
                else
                {
                    // cleavage site is not intact
                }
            }
            // proteolysis product is after the variant and there is no stop gain
            else if (p::OneBasedBeginPosition > variant->getOneBasedEndPosition() && p::OneBasedBeginPosition + sequenceLengthChange <= variantAppliedProteinSequence.length() && p::OneBasedEndPosition + sequenceLengthChange <= variantAppliedProteinSequence.length() && !StringHelper::endsWith(variant->getVariantSequence(), "*"))
            {
                ProteolysisProduct tempVar3(p::OneBasedBeginPosition + sequenceLengthChange, p::OneBasedEndPosition + sequenceLengthChange, p::Type);
                products.push_back(&tempVar3);
            }
            else // sequence variant conflicts with proteolysis cleavage site (cleavage site was lost)
            {
                continue;
            }
        }
        return products;
    }

    std::unordered_map<int, std::vector<Modification*>> VariantApplication::AdjustModificationIndices(SequenceVariation *variant, const std::string &variantAppliedProteinSequence, Protein *protein)
    {
        std::unordered_map<int, std::vector<Modification*>> &modificationDictionary = protein->getOneBasedPossibleLocalizedModifications();
        std::unordered_map<int, std::vector<Modification*>> &variantModificationDictionary = variant->getOneBasedModifications();
        std::unordered_map<int, std::vector<Modification*>> mods;
        int sequenceLengthChange = variant->getVariantSequence().length() - variant->getOriginalSequence().length();

        // change modification indices for variant sequence
        if (!modificationDictionary.empty())
        {
            for (auto kv : modificationDictionary)
            {
                if (kv.first > variantAppliedProteinSequence.length())
                {
                    continue; // it was cut out by a stop gain
                }
                // mod is before the variant
                else if (kv.first < variant->getOneBasedBeginPosition())
                {
                    mods.emplace(kv.first, kv.second);
                }
                // mod is after the variant and not affected by a stop gain
                else if (variant->getOneBasedEndPosition() < kv.first && kv.first + sequenceLengthChange <= variantAppliedProteinSequence.length())
                {
                    mods.emplace(kv.first + sequenceLengthChange, kv.second);
                }
                else // sequence variant conflicts with modification site (modification site substitution)
                {
                    continue;
                }
            }
        }

        // sequence variant modifications are indexed to the variant sequence
        //    NOTE: this code assumes variants are added from end to beginning of protein, so that previously added variant mods are adjusted above
        if (!variantModificationDictionary.empty())
        {
            for (auto kv : variantModificationDictionary)
            {
                TValue modsAtPos;
                std::unordered_map<int, std::vector<Modification*>>::const_iterator mods_iterator = mods.find(kv.Key);
                if (mods_iterator != mods.end())
                {
                    modsAtPos = mods_iterator->second;
                    modsAtPos->AddRange(kv.Value);
                }
                else
                {
                    modsAtPos = mods_iterator->second;
                    mods.emplace(kv.Key, kv.Value);
                }
            }
        }

        return mods;
    }
}
