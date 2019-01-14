#include "SequenceVariation.h"
#include "stringhelper.h"

namespace Proteomics {

    SequenceVariation::SequenceVariation(int OneBasedBeginPosition, int OneBasedEndPosition, const std::string &OriginalSequence, const std::string &VariantSequence, const std::string &Description) {
        this->setOneBasedBeginPosition(OneBasedBeginPosition);
        this->setOneBasedEndPosition(OneBasedEndPosition);
        this->setOriginalSequence(OriginalSequence);
        this->setVariantSequence(VariantSequence);
        this->setDescription(Description);
    }

    SequenceVariation::SequenceVariation(int OneBasedPosition, const std::string &OriginalSequence, const std::string &VariantSequence, const std::string &Description) : SequenceVariation(OneBasedPosition, OneBasedPosition, OriginalSequence, VariantSequence, Description) {
    }

    int SequenceVariation::getOneBasedBeginPosition() const {
        return privateOneBasedBeginPosition;
    }

    void SequenceVariation::setOneBasedBeginPosition(int value) {
        privateOneBasedBeginPosition = value;
    }

    int SequenceVariation::getOneBasedEndPosition() const {
        return privateOneBasedEndPosition;
    }

    void SequenceVariation::setOneBasedEndPosition(int value) {
        privateOneBasedEndPosition = value;
    }

    std::string SequenceVariation::getOriginalSequence() const {
        return privateOriginalSequence;
    }

    void SequenceVariation::setOriginalSequence(const std::string &value) {
        privateOriginalSequence = value;
    }

    std::string SequenceVariation::getVariantSequence() const {
        return privateVariantSequence;
    }

    void SequenceVariation::setVariantSequence(const std::string &value) {
        privateVariantSequence = value;
    }

    std::string SequenceVariation::getDescription() const {
        return privateDescription;
    }

    void SequenceVariation::setDescription(const std::string &value) {
        privateDescription = value;
    }

    bool SequenceVariation::Equals(SequenceVariation *s ) {
//        SequenceVariation *s = dynamic_cast<SequenceVariation*>(obj);
        return s != nullptr && getOneBasedBeginPosition() == s->getOneBasedBeginPosition() && getOneBasedEndPosition() == s->getOneBasedEndPosition() && getOriginalSequence() == s->getOriginalSequence() && getVariantSequence() == s->getVariantSequence() && getDescription() == s->getDescription();
    }

    int SequenceVariation::GetHashCode() {
        return StringHelper::GetHashCode(std::to_string(getOneBasedBeginPosition())) ^ StringHelper::GetHashCode(std::to_string(getOneBasedEndPosition())) ^ StringHelper::GetHashCode(getOriginalSequence()) ^ StringHelper::GetHashCode(getVariantSequence()) ^ StringHelper::GetHashCode(getDescription());
    }
}
