#pragma once

#include <string>

namespace Proteomics {
    class SequenceVariation {
    private:
        int privateOneBasedBeginPosition = 0;
        int privateOneBasedEndPosition = 0;
        std::wstring privateOriginalSequence;
        std::wstring privateVariantSequence;
        std::wstring privateDescription;

//        #region Public Constructors

        /// <summary>
        /// For longer sequence variations, where a range of sequence is replaced. Point mutations should be specified with the same begin and end positions.
        /// </summary>
        /// <param name="OneBasedBeginPosition"></param>
        /// <param name="OneBasedEndPosition"></param>
        /// <param name="OriginalSequence"></param>
        /// <param name="VariantSequence"></param>
    public:
        SequenceVariation(int OneBasedBeginPosition, int OneBasedEndPosition, const std::wstring &OriginalSequence, const std::wstring &VariantSequence, const std::wstring &Description);

        /// <summary>
        /// For point mutations. Sets begin and end to the same position.
        /// </summary>
        /// <param name="OneBasedPosition"></param>
        /// <param name="OriginalSequence"></param>
        /// <param name="VariantSequence"></param>
        /// <param name="Description"></param>
        SequenceVariation(int OneBasedPosition, const std::wstring &OriginalSequence, const std::wstring &VariantSequence, const std::wstring &Description);

//        #endregion Public Constructors

//        #region Public Properties

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
        std::wstring getOriginalSequence() const;
        void setOriginalSequence(const std::wstring &value);

        /// <summary>
        /// Variant sequence information (required)
        /// </summary>
        std::wstring getVariantSequence() const;
        void setVariantSequence(const std::wstring &value);

        /// <summary>
        /// Description of this variation (optional)
        /// </summary>
        std::wstring getDescription() const;
        void setDescription(const std::wstring &value);

//        #endregion Public Properties

//        #region Public Methods

        bool Equals(std::any obj) override;

        int GetHashCode() override;

//        #endregion Public Methods
    };
}
