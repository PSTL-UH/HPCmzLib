#include "ProteolysisProduct.h"
#include "stringhelper.h"

namespace Proteomics {

    ProteolysisProduct::ProteolysisProduct(Nullable<int> oneBasedBeginPosition, Nullable<int> oneBasedEndPosition, const std::string &type) {
        privateOneBasedBeginPosition = oneBasedBeginPosition;
        privateOneBasedEndPosition = oneBasedEndPosition;
        privateType = type;
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

    bool ProteolysisProduct::Equals(ProteolysisProduct* obj) {
        return dynamic_cast<ProteolysisProduct*>(obj) != nullptr &&
            (dynamic_cast<ProteolysisProduct*>(obj))->getOneBasedBeginPosition() == getOneBasedBeginPosition() &&
            (dynamic_cast<ProteolysisProduct*>(obj))->getOneBasedEndPosition() == getOneBasedEndPosition() &&
            (dynamic_cast<ProteolysisProduct*>(obj))->getType() == getType();
    }

    int ProteolysisProduct::GetHashCode() {
        int hash1=0;
        Nullable<int> i1 = getOneBasedBeginPosition();      
        if ( i1.HasValue() ) {
            hash1 = StringHelper::GetHashCode(std::to_string(i1.GetValueOrDefault()));
        }
        int hash2=0;
        Nullable<int> i2 = getOneBasedEndPosition();      
        if ( i2.HasValue() ) {
            hash2 = StringHelper::GetHashCode(std::to_string(i2.GetValueOrDefault()));
        }

        return hash1 ^ hash2 ^ StringHelper::GetHashCode(getType());
    }
}
