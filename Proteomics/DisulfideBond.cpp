#include "DisulfideBond.h"

namespace Proteomics {

    DisulfideBond::DisulfideBond(int OneBasedBeginPosition, int OneBasedEndPosition, const std::string &Description) {
        this->setOneBasedBeginPosition(OneBasedBeginPosition);
        this->setOneBasedEndPosition(OneBasedEndPosition);
        this->setDescription(Description);
    }

    DisulfideBond::DisulfideBond(int OneBasedPosition, const std::string &Description) : DisulfideBond(OneBasedPosition, OneBasedPosition, Description) {
    }

    int DisulfideBond::getOneBasedBeginPosition() const {
        return privateOneBasedBeginPosition;
    }

    void DisulfideBond::setOneBasedBeginPosition(int value) {
        privateOneBasedBeginPosition = value;
    }

    int DisulfideBond::getOneBasedEndPosition() const {
        return privateOneBasedEndPosition;
    }

    void DisulfideBond::setOneBasedEndPosition(int value) {
        privateOneBasedEndPosition = value;
    }

    std::string DisulfideBond::getDescription() const {
        return privateDescription;
    }

    void DisulfideBond::setDescription(const std::string &value) {
        privateDescription = value;
    }

    bool DisulfideBond::Equals(std::any obj) {
        DisulfideBond *bond = dynamic_cast<DisulfideBond*>(obj);
        return bond != nullptr && bond->getOneBasedBeginPosition() == getOneBasedBeginPosition() && bond->getOneBasedEndPosition() == getOneBasedEndPosition() && bond->getDescription() == getDescription();
    }

    int DisulfideBond::GetHashCode() {
        return getOneBasedBeginPosition() ^ getOneBasedEndPosition() ^ getDescription().GetHashCode();
    }
}
