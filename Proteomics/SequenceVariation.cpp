#include "SequenceVariation.h"

namespace Proteomics {

    SequenceVariation::SequenceVariation(int OneBasedBeginPosition, int OneBasedEndPosition, const std::wstring &OriginalSequence, const std::wstring &VariantSequence, const std::wstring &Description) {
        this->setOneBasedBeginPosition(OneBasedBeginPosition);
        this->setOneBasedEndPosition(OneBasedEndPosition);
        this->setOriginalSequence(OriginalSequence);
        this->setVariantSequence(VariantSequence);
        this->setDescription(Description);
    }

    SequenceVariation::SequenceVariation(int OneBasedPosition, const std::wstring &OriginalSequence, const std::wstring &VariantSequence, const std::wstring &Description) : SequenceVariation(OneBasedPosition, OneBasedPosition, OriginalSequence, VariantSequence, Description) {
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

    std::wstring SequenceVariation::getOriginalSequence() const {
        return privateOriginalSequence;
    }

    void SequenceVariation::setOriginalSequence(const std::wstring &value) {
        privateOriginalSequence = value;
    }

    std::wstring SequenceVariation::getVariantSequence() const {
        return privateVariantSequence;
    }

    void SequenceVariation::setVariantSequence(const std::wstring &value) {
        privateVariantSequence = value;
    }

    std::wstring SequenceVariation::getDescription() const {
        return privateDescription;
    }

    void SequenceVariation::setDescription(const std::wstring &value) {
        privateDescription = value;
    }

    bool SequenceVariation::Equals(std::any obj) {
        SequenceVariation *s = dynamic_cast<SequenceVariation*>(obj);
        return s != nullptr && getOneBasedBeginPosition() == s->getOneBasedBeginPosition() && getOneBasedEndPosition() == s->getOneBasedEndPosition() && getOriginalSequence() == s->getOriginalSequence() && getVariantSequence() == s->getVariantSequence() && getDescription() == s->getDescription();
    }

    int SequenceVariation::GetHashCode() {
        return getOneBasedBeginPosition().GetHashCode() ^ getOneBasedEndPosition().GetHashCode() ^ getOriginalSequence().GetHashCode() ^ getVariantSequence().GetHashCode() ^ getDescription().GetHashCode();
    }
}
