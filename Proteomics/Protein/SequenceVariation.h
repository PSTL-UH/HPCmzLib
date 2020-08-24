#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <string>

//namespace Proteomics { class SequenceVariantDescription; }
#include "SequenceVariantDescription.h"

//namespace Proteomics { class Modification; }
#include "../Modifications/Modification.h"

//namespace Proteomics { class ProteolysisProduct; }
#include "ProteolysisProduct.h"

namespace Proteomics {
    class SequenceVariation {
    private:
        int privateOneBasedBeginPosition = 0;
        int privateOneBasedEndPosition = 0;
        std::string privateOriginalSequence;
        std::string privateVariantSequence;
        SequenceVariantDescription *privateDescription;
        std::unordered_map<int, std::vector<Modification*>> privateOneBasedModifications;
        
        /// <summary>
        /// For longer sequence variations, where a range of sequence is replaced. Point mutations should be specified with the same begin and end positions.
        /// </summary>
        /// <param name="OneBasedBeginPosition"></param>
        /// <param name="OneBasedEndPosition"></param>
        /// <param name="OriginalSequence"></param>
        /// <param name="VariantSequence"></param>
        /// <param name="oneBasedModifications"></param>        
    public:
        SequenceVariation(int OneBasedBeginPosition, int OneBasedEndPosition, const std::string &OriginalSequence, const std::string &VariantSequence, const std::string &Description, std::unordered_map<int, std::vector<Modification*>> oneBasedModifications);

        /// </summary>
        /// For variations with only position information (not begin and end).
        /// Sets the end to the end of the original protein sequence to which this variation applies.<summary>
        /// <param name="OneBasedPosition"></param>
        /// <param name="OriginalSequence"></param>
        /// <param name="VariantSequence"></param>
        /// <param name="Description"></param>
        /// <param name="oneBasedModifications"></param>
    SequenceVariation(int OneBasedPosition, const std::string &OriginalSequence, const std::string &VariantSequence, const std::string &Description, std::unordered_map<int, std::vector<Modification*>> oneBasedModifications);

        /// <summary>
        /// Beginning position of original sequence to be replaced
        /// </summary>
        int getOneBasedBeginPosition() const;
        //void setOneBasedBeginPosition(int value);

        /// <summary>
        /// End position of original sequence to be replaced
        /// </summary>
        int getOneBasedEndPosition() const;
        //void setOneBasedEndPosition(int value);

        /// <summary>
        /// Original sequence information (optional)
        /// </summary>
        std::string getOriginalSequence() const;
        //void setOriginalSequence(const std::string &value);

        /// <summary>
        /// Variant sequence information (required)
        /// </summary>
        std::string getVariantSequence() const;
        //void setVariantSequence(const std::string &value);

        /// <summary>
        /// Description of this variation (optional)
        /// </summary>
        SequenceVariantDescription* getDescription() const;
        //void setDescription(const std::string &value);

        /// <summary>
        /// Modifications specifically for this variant
        /// </summary>
        std::unordered_map<int, std::vector<Modification*>> getOneBasedModifications() const;

        bool Equals(SequenceVariation *s);
        int GetHashCode();

        /// <summary>
        /// Returns a simple string represantation of this amino acid change
        /// </summary>
        /// <returns></returns>
        std::string SimpleString();

       /// <summary>
        /// Determines whether this interval overlaps the queried interval
        /// </summary>
        /// <param name="segment"></param>
        /// <returns></returns>
        bool Intersects(SequenceVariation *segment);

        /// <summary>
        /// Determines whether this interval overlaps the queried interval
        /// </summary>
        /// <param name="segment"></param>
        /// <returns></returns>
        bool Intersects(ProteolysisProduct *segment);

        /// <summary>
        /// Determines whether this interval overlaps the queried position
        /// </summary>
        /// <param name="pos"></param>
        /// <returns></returns>
        bool Intersects(int pos);

        /// <summary>
        /// Determines whether this interval includes the queried interval
        /// </summary>
        /// <param name="segment"></param>
        /// <returns></returns>
        bool Includes(SequenceVariation *segment);

         /// <summary>
        /// Determines whether this interval includes the queried interval
        /// </summary>
        /// <param name="segment"></param>
        /// <returns></returns>
        bool Includes(ProteolysisProduct *segment);

        /// <summary>
        /// Determines whether this interval overlaps the queried position
        /// </summary>
        /// <param name="pos"></param>
        /// <returns></returns>
        bool Includes(int pos);        
    };
}
