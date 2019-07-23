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
        std::string baseAcc = StringHelper::startsWith(protein->getAccession(), "DECOY_") ?
            StringHelper::formatSimple("{0}_{1}", accSplit[0], accSplit[1]) : accSplit[0];
        return baseAcc + (appliedSequenceVariations.empty() ||
                          appliedSequenceVariations.size() == 0 ? "" :
                          StringHelper::formatSimple("_{0}", CombineSimpleStrings(appliedSequenceVariations)));
    }

    bool VariantApplication::IsSequenceVariantModification(SequenceVariation *appliedVariant, int variantProteinIndex)
    {
        return appliedVariant != nullptr && appliedVariant->Includes(variantProteinIndex);
    }

    int VariantApplication::RestoreModificationIndex(Protein *protein, int variantProteinIndex)
    {
#ifdef ORIG
        return variantProteinIndex - protein->getAppliedSequenceVariations().Where([&] (std::any v)
        {
            return v::OneBasedEndPosition < variantProteinIndex;
        }).Sum([&] (std::any v)
        {
            return v::VariantSequence->Length - v::OriginalSequence->Length;
        });
#endif
        std::vector<SequenceVariation*> v1;
        for ( auto v: protein->getAppliedSequenceVariations() ) {
            if ( v->getOneBasedEndPosition() < variantProteinIndex ) {
                v1.push_back (v);
            }
        }
        int sum =0;
        for ( auto v : v1 ) {
            sum += v->getVariantSequence().length() - v->getOriginalSequence().length();
        }
        return sum;
    }

    std::string VariantApplication::CombineSimpleStrings(std::vector<SequenceVariation*> &variations)
    {
#ifdef ORIG
        return variations.empty() || variations.size() == 0? "" : std::string::Join("_", variations.Select([&] (std::any v)
        {
            v::SimpleString();
        }));
#endif
        std::string s;
        for ( auto v = variations.begin(); v != variations.end(); v++ ) {
            SequenceVariation *vv= *v;
            if ( std::next(v) == variations.end() ) {
                s += vv->SimpleString();
            }
            else {
                s += vv->SimpleString() + "_";
            }
        }
        return variations.empty() || variations.size() == 0? "" : s;
    }

    std::string VariantApplication::CombineDescriptions(std::vector<SequenceVariation*> &variations)
    {
#ifdef ORIG
        return variations.empty() || variations.size() == 0 ? "" : std::string::Join(", variant:", variations.Select([&] (std::any d)
        {
            d::Description;
        }));
#endif
        std::string s;
        for ( auto d = variations.begin(); d != variations.end(); d++ ) {
            SequenceVariation *vv= *d;
            if ( std::next(d) == variations.end() ) {
                s += vv->getDescription()->getDescription();
            }
            else {
                s += vv->getDescription()->getDescription() + ", variant:";
            }
        }
        return variations.empty() || variations.size() == 0? "" : s;
    }


    std::vector<Protein*> VariantApplication::ApplyVariants(Protein *protein, std::vector<SequenceVariation*> &sequenceVariations, int maxAllowedVariantsForCombinitorics, int minAlleleDepth)
    {
#ifdef ORIG
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
#endif
        std::sort(sequenceVariations.begin(), sequenceVariations.end(), [&] (SequenceVariation* a, SequenceVariation* b) {
                return a->SimpleString() > b->SimpleString();
            });
        std::vector<SequenceVariation*> CopyOfsequenceVariations = sequenceVariations;
        std::vector<SequenceVariation*>::iterator ip;
        ip = std::unique(CopyOfsequenceVariations.begin(), CopyOfsequenceVariations.end(), [&] (SequenceVariation* a, SequenceVariation* b){
            return a->SimpleString() == b->SimpleString();
            });
        CopyOfsequenceVariations.resize(std::distance(CopyOfsequenceVariations.begin(), ip));   

        std::vector<SequenceVariation*> uniqueEffectsToApply;
        for ( auto v :  CopyOfsequenceVariations ) {
            if ( v->getDescription()->getGenotypes().size() > 0 ) {
                uniqueEffectsToApply.push_back(v);
            }
        }
        std::sort(uniqueEffectsToApply.begin(), uniqueEffectsToApply.end(), [&] (SequenceVariation* a, SequenceVariation* b){
                return a->getOneBasedBeginPosition() > b->getOneBasedBeginPosition();
            });
        
        
        Protein *proteinCopy = new Protein(protein->getBaseSequence(), protein, std::vector<SequenceVariation *>(),
                                           protein->getProteolysisProducts(), protein->getOneBasedPossibleLocalizedModifications(), "");

        // If there aren't any variants to apply, just return the base protein
        if (uniqueEffectsToApply.empty())
        {
            delete proteinCopy;
            return std::vector<Protein*> {proteinCopy};
        }

#ifdef ORIG
        std::unordered_set<std::string> individuals = std::unordered_set<std::string>(uniqueEffectsToApply.SelectMany([&] (std::any v)
        {
            v::Description->Genotypes->Keys;
        }));
#endif
        std::unordered_set<std::string> individuals;
        for ( auto v : uniqueEffectsToApply  ) {
            std::unordered_map<std::string, std::vector<std::string>> geno = v->getDescription()->getGenotypes();
            for ( auto g = geno.begin(); g != geno.end(); g++ ) {
                std::vector<std::string> s = g->second;
                for ( auto thisstring: s ) {
                    individuals.insert(thisstring);
                }
            }
        }
        
        std::vector<Protein*> variantProteins;

        // loop through genotypes for each sample/individual (e.g. tumor and normal)
        for (auto individual : individuals)
        {
#ifdef ORIG
            bool tooManyHeterozygousVariants = uniqueEffectsToApply.size()([&] (std::any v)
            {
                v::Description->Heterozygous[individual];
            }) > maxAllowedVariantsForCombinitorics;
#endif
            int count =0;
            for ( auto v : uniqueEffectsToApply  ) {
                if ( v->getDescription()->getHeterozygous()[individual] ) {
                    count++;
                }
            }
            bool tooManyHeterozygousVariants = count > maxAllowedVariantsForCombinitorics;


            std::vector<Protein*> newVariantProteins = {proteinCopy};
            for (auto variant : uniqueEffectsToApply)
            {
#ifdef ORIG
                bool variantAlleleIsInTheGenotype = variant->getDescription()->getGenotypes()[individual]->Contains(std::to_string(variant->getDescription()->getAlleleIndex())); // should catch the case where it's -1 if the INFO isn't from SnpEff
#endif
                bool variantAlleleIsInTheGenotype = false;
                std::vector<std::string> svector = variant->getDescription()->getGenotypes()[individual];
                std::string singleitem = std::to_string(variant->getDescription()->getAlleleIndex());
                for ( auto s: svector ) {
                    if ( s.find(singleitem) != std::string::npos ) {
                        variantAlleleIsInTheGenotype = true;
                        break;
                    }
                }

                if (!variantAlleleIsInTheGenotype)
                {
                    continue;
                }
#ifdef ORIG
                bool isHomozygousAlternate = variant->getDescription()->getHomozygous()[individual] && variant->getDescription()->getGenotypes()[individual]->All([&] (std::any d)
                {
                delete proteinCopy;
                    return d == std::to_string(variant->getDescription()->getAlleleIndex());
                });
                // note this isn't a great test for homozygosity, since the genotype could be 1/2 and this would still
                //return true. But currently, alleles 1 and 2 will be included as separate variants, so this is fine for now.
#endif
                bool isHomozygousAlternate =  variant->getDescription()->getHomozygous()[individual];
                // std::vector<std::string> svector = variant->getDescription()->getGenotypes()[individual];
                for ( auto d : svector ) {
                    if ( d != std::to_string(variant->getDescription()->getAlleleIndex()) ) {
                        isHomozygousAlternate = false;
                        break;
                    }
                }
                
#ifdef ORIG
                int depthRef;
                bool isDeepReferenceAllele = int::TryParse(variant->getDescription()->getAlleleDepths()[individual][0], depthRef) &&
                    depthRef >= minAlleleDepth;

                int depthAlt;
                bool isDeepAlternateAllele = int::TryParse(variant->getDescription()->getAlleleDepths()[individual][variant->getDescription()->getAlleleIndex()], depthAlt) &&
                    depthAlt >= minAlleleDepth;
#endif
                std::string s1 = variant->getDescription()->getAlleleDepths()[individual][0];
                bool isDeepReferenceAllele=false;
                try {
                    int depthRef = std::stoi(s1);
                    if ( depthRef >= minAlleleDepth ) {
                        isDeepReferenceAllele = true;
                    }                          
                }
                catch(std::invalid_argument& e) {
                    //don't do anything.
                }

                std::string s2 = variant->getDescription()->getAlleleDepths()[individual][variant->getDescription()->getAlleleIndex()];
                bool isDeepAlternateAllele = false;
                try {
                    int depthAlt = std::stoi(s2);
                    if (  depthAlt >= minAlleleDepth ) {
                        isDeepAlternateAllele = true;
                    }
                }
                catch(std::invalid_argument& e) {
                    //don't do anything.
                }
                                  
                // homozygous alternate
                if (isHomozygousAlternate && isDeepAlternateAllele)
                {
#ifdef ORIG
                    newVariantProteins = newVariantProteins.Select([&] (std::any p)
                    {
                        ApplySingleVariant(variant, p, individual);
                    }).ToList();
#endif
                    for ( auto p : newVariantProteins ) {
                        newVariantProteins.push_back( ApplySingleVariant(variant, p, individual));
                    }
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
#ifdef ORIG
                        newVariantProteins = newVariantProteins.Select([&] (std::any p)
                        {
                            ApplySingleVariant(variant, p, individual);
                        }).ToList();
#endif
                        for ( auto p : newVariantProteins ) {
                            newVariantProteins.push_back( ApplySingleVariant(variant, p, individual));
                        }
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
#ifdef ORIG
                            if (variant->getDescription()->getGenotypes()[individual]->Contains("0"))
                            {
                                combinitoricProteins.push_back(ppp);
                            }
#endif
                            std::vector<std::string> genotypes = variant->getDescription()->getGenotypes()[individual];
                            for ( auto genotype : genotypes ) {
                                if ( genotype.find("0" ) != std::string::npos ) {
                                    combinitoricProteins.push_back(ppp);                                    
                                }
                            }
                            
                            // alternate allele (replace all, since in heterozygous with two alternates,
                            // both alternates are included)
                            combinitoricProteins.push_back(ApplySingleVariant(variant, ppp, individual));
                        }
                        else if (isDeepAlternateAllele && maxAllowedVariantsForCombinitorics > 0)
                        {
                            combinitoricProteins.push_back(ApplySingleVariant(variant, ppp, individual));
                        }
#ifdef ORIG
                        // C++ this looks like an exact duplicate of the if statement above. Skipping.
                        else if (variant->getDescription()->getGenotypes()[individual]->Contains("0"))
                        {
                            combinitoricProteins.push_back(ppp);
                        }
#endif
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

#ifdef ORIG
        return variantProteins.GroupBy([&] (std::any x)
        {
            x::BaseSequence;
        })->Select([&] (std::any x)
        {
            x::First();
        }).ToList();
#endif
        std::sort(variantProteins.begin(), variantProteins.end(), [&] (Protein* a, Protein* b) {
                return a->getBaseSequence() > b->getBaseSequence();
            });
        std::vector<Protein*>::iterator it;
        it = std::unique(variantProteins.begin(), variantProteins.end(), [&] (Protein* a, Protein* b){
            return a->getBaseSequence() == b->getBaseSequence();
            });
        variantProteins.resize(std::distance(variantProteins.begin(), it));   

        return variantProteins;
        
        
    }

    Protein *VariantApplication::ApplySingleVariant(SequenceVariation *variantGettingApplied, Protein *protein, const std::string &individual)
    {
        std::string seqBefore = protein->getBaseSequence().substr(0, variantGettingApplied->getOneBasedBeginPosition() - 1);
        std::string seqVariant = variantGettingApplied->getVariantSequence();
        int afterIdx = variantGettingApplied->getOneBasedBeginPosition() + variantGettingApplied->getOriginalSequence().length() - 1;

        SequenceVariation *variantAfterApplication = new SequenceVariation(variantGettingApplied->getOneBasedBeginPosition(),
              variantGettingApplied->getOneBasedBeginPosition() + variantGettingApplied->getVariantSequence().length() - 1,
              variantGettingApplied->getOriginalSequence(),
              variantGettingApplied->getVariantSequence(),
              variantGettingApplied->getDescription()->getDescription(),
              variantGettingApplied->getOneBasedModifications());
#ifdef ORIG
//              variantGettingApplied->getOneBasedModifications().ToDictionary([&] (std::any kv)
//        {
//            kv::Key;
//        }, [&] (std::any kv)
//        {
//            kv->Value;
//        });
#endif
        // check to see if there is incomplete indel overlap, which would lead to weird variant sequences
        // complete overlap is okay, since it will be overwritten; this can happen if there are two alternate alleles,
        //    e.g. reference sequence is wrong at that point
 
#ifdef ORIG
        bool intersectsAppliedRegionIncompletely = protein->getAppliedSequenceVariations().Any([&] (std::any x)
        {
            // C++: not sure why the converter added this delete statement, I do not see anything related
            //     to it in the original C# code.
            // delete variantAfterApplication;
            return variantGettingApplied->Intersects(x) && !variantGettingApplied->Includes(x);
        });
#endif        
        bool intersectsAppliedRegionIncompletely = false;
        for ( auto x: protein->getAppliedSequenceVariations() ) {
            if ( variantGettingApplied->Intersects(x) && !variantGettingApplied->Includes(x) ) {
                intersectsAppliedRegionIncompletely = true;
                break;
            }
        }
        std::vector<SequenceVariation*> appliedVariations = {variantAfterApplication};
        std::string seqAfter = "";
        if (intersectsAppliedRegionIncompletely)
        {
            // use original protein sequence for the remaining sequence
            seqAfter = protein->getBaseSequence().length() - afterIdx <= 0 ? "" :
                protein->getNonVariantProtein()->getBaseSequence().substr(afterIdx);
        }
        else
        {
            // use this variant protein sequence for the remaining sequence
            seqAfter = protein->getBaseSequence().length() - afterIdx <= 0 ? "" :
                protein->getBaseSequence().substr(afterIdx);
#ifdef ORIG
            appliedVariations = appliedVariations.Concat(protein->getAppliedSequenceVariations().Where([&] (std::any x)
            {
                !variantGettingApplied->Includes(x);
            }))->ToList();
#endif
            for ( auto x : protein->getAppliedSequenceVariations() ) {
                if (  !variantGettingApplied->Includes(x) ) {
                    appliedVariations.push_back(x);
                }
            }
        }
#ifdef ORIG
        std::string variantSequence = (seqBefore + seqVariant + seqAfter).Split('*')[0]; // there may be a stop gained
#endif
        std::string variantSequence = (StringHelper::split((seqBefore + seqVariant + seqAfter), '*'))[0];
        
        // adjust indices
        std::vector<Proteomics::ProteolysisProduct*> tmp = protein->getProteolysisProducts();
        std::vector<Proteomics::ProteolysisProduct*> &t = tmp;
        std::vector<ProteolysisProduct*> adjustedProteolysisProducts = AdjustProteolysisProductIndices(variantGettingApplied,
                                                                                                       variantSequence,
                                                                                                       protein, t);
        std::unordered_map<int, std::vector<Modification*>> adjustedModifications = AdjustModificationIndices(variantGettingApplied,
                                                                                                              variantSequence,
                                                                                                              protein);
        std::vector<SequenceVariation*> adjustedAppliedVariations = AdjustSequenceVariationIndices(variantGettingApplied,
                                                                                                   variantSequence,
                                                                                                   appliedVariations);
        
        delete variantAfterApplication;
        return new Protein(variantSequence, protein, adjustedAppliedVariations, adjustedProteolysisProducts,
                           adjustedModifications, individual);
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
#ifdef ORIG
            int addedIdx = alreadyAppliedVariations.Where([&] (std::any applied)
            {
                return applied::OneBasedEndPosition < v->getOneBasedBeginPosition();
            }).Sum([&] (std::any applied)
            {
                return applied::VariantSequence->Length - applied::OriginalSequence->Length;
            });
#endif
            int addedIdx=0;
            for ( auto applied: alreadyAppliedVariations ) {
                if (applied->getOneBasedEndPosition() < v->getOneBasedBeginPosition() ) {
                    addedIdx += (applied->getVariantSequence().length() - applied->getOriginalSequence().length());
                }
            }
            
            // variant was entirely before the one being applied (shouldn't happen because of order of applying variants)
            // or it's the current variation
            if (v->getDescription()->Equals(variantGettingApplied->getDescription()) ||
                v->getOneBasedEndPosition() - addedIdx < variantGettingApplied->getOneBasedBeginPosition())
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
                if (begin > (int) variantAppliedProteinSequence.length())
                {
                    continue; // cut out by a stop gain
                }
                int end = v->getOneBasedEndPosition() + sequenceLengthChange - overlap;
                if (end > (int) variantAppliedProteinSequence.length())
                {
                    end = variantAppliedProteinSequence.length(); // end shortened by a stop gain
                }
#ifdef ORIG
//                SequenceVariation tempVar(begin, end, v->getOriginalSequence(), v->getVariantSequence(), v->getDescription()->getDescription(), v->getOneBasedModifications().ToDictionary([&] (std::any kv)
//                {
//                    kv::Key;
//                }, [&] (std::any kv)
//                {
//                    kv->Value;
//                }));
#endif
                SequenceVariation tempVar(begin, end, v->getOriginalSequence(), v->getVariantSequence(), v->getDescription()->getDescription(), v->getOneBasedModifications());
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
#ifdef ORIG
//      for (ProteolysisProduct *p : proteolysisProducts.Where([&] (std::any p)
//      {
//          return p->getOneBasedEndPosition() && p->getOneBasedBeginPosition();
//      }))
#endif
        for (ProteolysisProduct *p : proteolysisProducts )  {
            if ( p->getOneBasedEndPosition().has_value() && p->getOneBasedBeginPosition().has_value() )
            {
                // proteolysis product is entirely before the variant
                if (variant->getOneBasedBeginPosition() > p->getOneBasedEndPosition().value())
                {
                    products.push_back(p);
                }
                // proteolysis product straddles the variant, but the cleavage site(s) are still intact; the ends aren't considered cleavage sites
                else if ((p->getOneBasedBeginPosition().value() < variant->getOneBasedBeginPosition() ||
                          p->getOneBasedBeginPosition().value() == 1 ||
                          p->getOneBasedBeginPosition().value() == 2) &&
                         (p->getOneBasedEndPosition().value() > variant->getOneBasedEndPosition() ||
                          p->getOneBasedEndPosition().value() == (int)protein->getNonVariantProtein()->getBaseSequence().length()))
                {
                    if (StringHelper::endsWith(variant->getVariantSequence(), "*"))
                    {
                        ProteolysisProduct tempVar(p->getOneBasedBeginPosition(), std::make_optional(variantAppliedProteinSequence.length()), p->getType());
                        products.push_back(&tempVar);
                    }
                    else if (p->getOneBasedEndPosition().value() + sequenceLengthChange <= (int)variantAppliedProteinSequence.length())
                    {
                        ProteolysisProduct tempVar2(p->getOneBasedBeginPosition(), p->getOneBasedEndPosition().value() + sequenceLengthChange,
                                                    p->getType());
                        products.push_back(&tempVar2);
                    }
                    else
                    {
                        // cleavage site is not intact
                    }
                }
                // proteolysis product is after the variant and there is no stop gain
                else if (p->getOneBasedBeginPosition().value() > variant->getOneBasedEndPosition() &&
                         p->getOneBasedBeginPosition().value() + sequenceLengthChange <= (int)variantAppliedProteinSequence.length() &&
                         p->getOneBasedEndPosition().value() + sequenceLengthChange <= (int)variantAppliedProteinSequence.length() &&
                         !StringHelper::endsWith(variant->getVariantSequence(), "*"))
                {
                    ProteolysisProduct tempVar3(p->getOneBasedBeginPosition().value() + sequenceLengthChange,
                                                p->getOneBasedEndPosition().value() + sequenceLengthChange, p->getType());
                    products.push_back(&tempVar3);
                }
                else // sequence variant conflicts with proteolysis cleavage site (cleavage site was lost)
                {
                    continue;
                }
            }
        }
        return products;
    }

    std::unordered_map<int, std::vector<Modification*>> VariantApplication::AdjustModificationIndices(SequenceVariation *variant,
                                                                                                      const std::string &variantAppliedProteinSequence,
                                                                                                      Protein *protein)
    {
        std::unordered_map<int, std::vector<Modification*>> modificationDictionary = protein->getOneBasedPossibleLocalizedModifications();
        std::unordered_map<int, std::vector<Modification*>> variantModificationDictionary = variant->getOneBasedModifications();
        std::unordered_map<int, std::vector<Modification*>> mods;
        int sequenceLengthChange = variant->getVariantSequence().length() - variant->getOriginalSequence().length();

        // change modification indices for variant sequence
        if (!modificationDictionary.empty())
        {
            for (auto kv = modificationDictionary.begin(); kv !=modificationDictionary.end(); kv++ )
            {
                if (kv->first > (int)variantAppliedProteinSequence.length())
                {
                    continue; // it was cut out by a stop gain
                }
                // mod is before the variant
                else if (kv->first < variant->getOneBasedBeginPosition())
                {
                    mods.emplace(kv->first, kv->second);
                }
                // mod is after the variant and not affected by a stop gain
                else if (variant->getOneBasedEndPosition() < kv->first &&
                         kv->first + sequenceLengthChange <= (int) variantAppliedProteinSequence.length())
                {
                    mods.emplace(kv->first + sequenceLengthChange, kv->second);
                }
                else // sequence variant conflicts with modification site (modification site substitution)
                {
                    continue;
                }
            }
        }

        // sequence variant modifications are indexed to the variant sequence
        //    NOTE: this code assumes variants are added from end to beginning of protein, so that previously added
        //          variant mods are adjusted above
        if (!variantModificationDictionary.empty())
        {
            for (auto kv =variantModificationDictionary.begin();  kv !=variantModificationDictionary.end(); kv++)
            {
                std::vector<Modification*> modsAtPos;
                std::unordered_map<int, std::vector<Modification*>>::const_iterator mods_iterator = mods.find(kv->first);
                if (mods_iterator != mods.end())
                {
                    modsAtPos = mods_iterator->second;
#ifdef ORIG
                    modsAtPos->AddRange(kv->second);
                    // C++ Skipping converting this line for now, since I do not see
                    // any whay this is actually beeing used, not just in the C++ code,
                    // but also in the original C# code.
#endif
                    
                }
                else
                {
                    modsAtPos = mods_iterator->second;
                    mods.emplace(kv->first, kv->second);
                }
            }
        }

        return mods;
    }
}
