#include "SpliceSite.h"

namespace Proteomics
{

    SpliceSite::SpliceSite(int oneBasedBegin, int oneBasedEnd, const std::string &description)
    {
        OneBasedBeginPosition = oneBasedBegin;
        OneBasedEndPosition = oneBasedEnd;
        Description = (description != nullptr) ? description : "";
    }

    SpliceSite::SpliceSite(int oneBasedPosition, const std::string &description) : SpliceSite(oneBasedPosition, oneBasedPosition, description)
    {
    }

    int SpliceSite::getOneBasedBeginPosition() const
    {
        return privateOneBasedBeginPosition;
    }

    int SpliceSite::getOneBasedEndPosition() const
    {
        return privateOneBasedEndPosition;
    }

    std::string SpliceSite::getDescription() const
    {
        return privateDescription;
    }

    bool SpliceSite::Equals(std::any obj)
    {
        SpliceSite *s = dynamic_cast<SpliceSite*>(obj);
        return s != nullptr && s->getOneBasedBeginPosition() == getOneBasedBeginPosition() && s->getOneBasedEndPosition() == getOneBasedEndPosition() && s->getDescription() == getDescription();
    }

    int SpliceSite::GetHashCode()
    {
        return getOneBasedBeginPosition().GetHashCode() ^ getOneBasedEndPosition().GetHashCode() ^ getDescription().GetHashCode(); // null handled in constructor
    }
}
