#include "ProteolysisProduct.h"

namespace Proteomics {

    ProteolysisProduct::ProteolysisProduct(Nullable<int> oneBasedBeginPosition, Nullable<int> oneBasedEndPosition, const std::string &type) {
        OneBasedBeginPosition = oneBasedBeginPosition;
        OneBasedEndPosition = oneBasedEndPosition;
        Type = type;
    }

    Nullable<int> ProteolysisProduct::getOneBasedBeginPosition() const {
        return privateOneBasedBeginPosition;
    }

    Nullable<int> ProteolysisProduct::getOneBasedEndPosition() const {
        return privateOneBasedEndPosition;
    }

    std::string ProteolysisProduct::getType() const {
        return privateType;
    }

    bool ProteolysisProduct::Equals(std::any obj) {
        return dynamic_cast<ProteolysisProduct*>(obj) != nullptr && (dynamic_cast<ProteolysisProduct*>(obj))->getOneBasedBeginPosition() == getOneBasedBeginPosition() && (dynamic_cast<ProteolysisProduct*>(obj))->getOneBasedEndPosition() == getOneBasedEndPosition() && (dynamic_cast<ProteolysisProduct*>(obj))->getType() == getType();
    }

    int ProteolysisProduct::GetHashCode() {
        return getOneBasedBeginPosition().GetHashCode() ^ getOneBasedEndPosition().GetHashCode() ^ getType().GetHashCode();
    }
}
