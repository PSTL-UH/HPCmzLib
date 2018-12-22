#pragma once

#include <string>
#include "Nullable.h"

namespace Proteomics {
    class ProteolysisProduct {
    private:
        Nullable<int> privateOneBasedBeginPosition;
        Nullable<int> privateOneBasedEndPosition;
        std::wstring privateType;

//        #region Public Constructors

    public:
        ProteolysisProduct(Nullable<int> oneBasedBeginPosition, Nullable<int> oneBasedEndPosition, const std::wstring &type);

//        #endregion Public Constructors

//        #region Public Properties

        Nullable<int> getOneBasedBeginPosition() const;
        Nullable<int> getOneBasedEndPosition() const;
        std::wstring getType() const;

//        #endregion Public Properties

//        #region Public Methods

        bool Equals(std::any obj) override;

        int GetHashCode() override;

//        #endregion Public Methods
    };
}
