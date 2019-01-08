#pragma once

#include <string>
#include "Nullable.h"

namespace Proteomics {
    class ProteolysisProduct {
    private:
        Nullable<int> privateOneBasedBeginPosition;
        Nullable<int> privateOneBasedEndPosition;
        std::string privateType;


    public:
        ProteolysisProduct(Nullable<int> oneBasedBeginPosition, Nullable<int> oneBasedEndPosition, const std::string &type);

        Nullable<int> getOneBasedBeginPosition() const;
        Nullable<int> getOneBasedEndPosition() const;
        std::string getType() const;

        bool Equals(std::any obj) override;

        int GetHashCode() override;

    };
}
