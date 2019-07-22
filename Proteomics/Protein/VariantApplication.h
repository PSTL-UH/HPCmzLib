#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "stringhelper.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
//namespace Proteomics { class Protein; }
#include "Protein.h"

//namespace Proteomics { class SequenceVariation; }
#include "SequenceVariation.h"

//namespace Proteomics { class ProteolysisProduct; }
#include "ProteolysisProduct.h"

//namespace Proteomics { class Modification; }
#include "../Modifications/Modification.h"


namespace Proteomics
{
    class VariantApplication final
    {
        /// <summary>
        /// Gets the accession for a protein with applied variations
        /// </summary>
        /// <param name="protein"></param>
        /// <param name="sequenceVariation"></param>
    public:
        static std::string GetAccession(Protein *protein, std::vector<SequenceVariation*> &appliedSequenceVariations);

        /// <summary>
        /// Determines if the modification falls on a variant amino acid
        /// </summary>
        /// <param name="protein"></param>
        /// <param name=""></param>
        /// <returns></returns>
        static bool IsSequenceVariantModification(SequenceVariation *appliedVariant, int variantProteinIndex);

        /// <summary>
        /// Restores modification index on a variant protein to the index on the nonvariant protein,
        /// or if it falls on a variant, this restores the position on the protein with only that variant
        /// </summary>
        /// <param name="variantProteinIndex"></param>
        /// <param name="modification"></param>
        /// <returns></returns>
        static int RestoreModificationIndex(Protein *protein, int variantProteinIndex);

        /// <summary>
        /// Format string to append to accession
        /// </summary>
        /// <param name="variations"></param>
        /// <returns></returns>
        static std::string CombineSimpleStrings(std::vector<SequenceVariation*> &variations);

        /// <summary>
        /// Format string to append to protein names
        /// </summary>
        /// <param name="variations"></param>
        /// <returns></returns>
        static std::string CombineDescriptions(std::vector<SequenceVariation*> &variations);

        /// <summary>
        /// Applies multiple variant changes to a protein sequence
        /// </summary>
        /// <param name="protein"></param>
        /// <param name="uniqueEffectsToApply"></param>
        /// <returns></returns>
        static std::vector<Protein*> ApplyVariants(Protein *protein, std::vector<SequenceVariation*> &sequenceVariations, int maxAllowedVariantsForCombinitorics, int minAlleleDepth);

        /// <summary>
        /// Applies a single variant to a protein sequence
        /// </summary>
        /// <param name="variantGettingApplied"></param>
        /// <returns></returns>
        static Protein *ApplySingleVariant(SequenceVariation *variantGettingApplied, Protein *protein, const std::string &individual);

        /// <summary>
        /// Adjusts the indices of sequence variations due to applying a single additional variant
        /// </summary>
        /// <param name="variantGettingApplied"></param>
        /// <param name="alreadyAppliedVariations"></param>
        /// <returns></returns>
        static std::vector<SequenceVariation*> AdjustSequenceVariationIndices(SequenceVariation *variantGettingApplied, const std::string &variantAppliedProteinSequence, std::vector<SequenceVariation*> &alreadyAppliedVariations);

        /// <summary>
        /// Eliminates proteolysis products that overlap sequence variations.
        /// Since frameshift indels are written across the remaining sequence,
        /// this eliminates proteolysis products that conflict with large deletions and other structural variations.
        /// </summary>
        /// <param name="variants"></param>
        /// <param name="proteolysisProducts"></param>
        /// <returns></returns>
        static std::vector<ProteolysisProduct*> AdjustProteolysisProductIndices(SequenceVariation *variant, const std::string &variantAppliedProteinSequence, Protein *protein, std::vector<ProteolysisProduct*> &proteolysisProducts);

        /// <summary>
        /// Adjusts modification indices.
        /// </summary>
        /// <param name="variant"></param>
        /// <param name="modificationDictionary"></param>
        /// <returns></returns>
        static std::unordered_map<int, std::vector<Modification*>> AdjustModificationIndices(SequenceVariation *variant, const std::string &variantAppliedProteinSequence, Protein *protein);
    };
}
