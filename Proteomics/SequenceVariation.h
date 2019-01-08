#pragma once

#include <string>

namespace Proteomics {
    class SequenceVariation {
    private:
        int privateOneBasedBeginPosition = 0;
        int privateOneBasedEndPosition = 0;
        std::string privateOriginalSequence;
        std::string privateVariantSequence;
        std::string privateDescription;

        /// <summary>
        /// For longer sequence variations, where a range of sequence is replaced. Point mutations should be specified with the same begin and end positions.
        /// </summary>
        /// <param name="OneBasedBeginPosition"></param>
        /// <param name="OneBasedEndPosition"></param>
        /// <param name="OriginalSequence"></param>
        /// <param name="VariantSequence"></param>
    public:
        SequenceVariation(int OneBasedBeginPosition, int OneBasedEndPosition, const std::string &OriginalSequence, const std::string &VariantSequence, const std::string &Description);

        /// <summary>
        /// For point mutations. Sets begin and end to the same position.
        /// </summary>
        /// <param name="OneBasedPosition"></param>
        /// <param name="OriginalSequence"></param>
        /// <param name="VariantSequence"></param>
        /// <param name="Description"></param>
        SequenceVariation(int OneBasedPosition, const std::string &OriginalSequence, const std::string &VariantSequence, const std::string &Description);

        /// <summary>
        /// Beginning position of original sequence to be replaced
        /// </summary>
        int getOneBasedBeginPosition() const;
        void setOneBasedBeginPosition(int value);

        /// <summary>
        /// End position of original sequence to be replaced
        /// </summary>
        int getOneBasedEndPosition() const;
        void setOneBasedEndPosition(int value);

        /// <summary>
        /// Original sequence information (optional)
        /// </summary>
        std::string getOriginalSequence() const;
        void setOriginalSequence(const std::string &value);

        /// <summary>
        /// Variant sequence information (required)
        /// </summary>
        std::string getVariantSequence() const;
        void setVariantSequence(const std::string &value);

        /// <summary>
        /// Description of this variation (optional)
        /// </summary>
        std::string getDescription() const;
        void setDescription(const std::string &value);

        bool Equals(std::any obj) override;

        int GetHashCode() override;

    };
}
