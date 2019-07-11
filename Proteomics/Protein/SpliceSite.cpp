#include "SpliceSite.h"
#include "stringhelper.h"

namespace Proteomics
{

    SpliceSite::SpliceSite(int oneBasedBegin, int oneBasedEnd, const std::string &description)
    {
        privateOneBasedBeginPosition = oneBasedBegin;
        privateOneBasedEndPosition = oneBasedEnd;
        //privateDescription = (description != nullptr) ? description : "";
        privateDescription = description;
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

    bool SpliceSite::Equals(SpliceSite *s)
    {
        return s != nullptr &&
            s->getOneBasedBeginPosition() == getOneBasedBeginPosition() &&
            s->getOneBasedEndPosition() == getOneBasedEndPosition()
            && s->getDescription() == getDescription();
    }

    int SpliceSite::GetHashCode()
    {
        return StringHelper::GetHashCode(std::to_string(getOneBasedBeginPosition())) ^
            StringHelper::GetHashCode(std::to_string(getOneBasedEndPosition())) ^
            StringHelper::GetHashCode(getDescription()); // null handled in constructor
    }
}
