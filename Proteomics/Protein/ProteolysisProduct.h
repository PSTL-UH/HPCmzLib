#pragma once

#include <string>
#include <optional>

namespace Proteomics {
    class ProteolysisProduct {
    private:
        std::optional<int> privateOneBasedBeginPosition;
        std::optional<int> privateOneBasedEndPosition;
        std::string privateType;


    public:
        ProteolysisProduct(std::optional<int> oneBasedBeginPosition, std::optional<int> oneBasedEndPosition, const std::string &type);

        std::optional<int> getOneBasedBeginPosition() const;
        std::optional<int> getOneBasedEndPosition() const;
        std::string getType() const;

        bool Equals(ProteolysisProduct* obj);

        int GetHashCode();

    };
}
