#pragma once

#include <string>

namespace Proteomics {
    class DisulfideBond {
    private:
        int privateOneBasedBeginPosition = 0;
        int privateOneBasedEndPosition = 0;
        std::wstring privateDescription;

//        #region Public Constructors

    public:
        DisulfideBond(int OneBasedBeginPosition, int OneBasedEndPosition, const std::wstring &Description);

        /// For interchain disulfide bonds, sets begin and end to the same position.
        DisulfideBond(int OneBasedPosition, const std::wstring &Description);

//        #endregion Public Constructors

//        #region Public Properties

        /// <summary>
        /// Beginning position of disulfide bond
        /// </summary>
        int getOneBasedBeginPosition() const;
        void setOneBasedBeginPosition(int value);

        /// <summary>
        /// End position of disulfide bond
        /// </summary>
        int getOneBasedEndPosition() const;
        void setOneBasedEndPosition(int value);

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
