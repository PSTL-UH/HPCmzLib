#include "SpectraFileInfo.h"
#include "stringhelper.h"
#include <string>

namespace FlashLFQ
{

    SpectraFileInfo::SpectraFileInfo(const std::string &fullFilePathWithExtension, const std::string &condition, int biorep, int techrep, int fraction) : FullFilePathWithExtension(fullFilePathWithExtension), FilenameWithoutExtension(const_cast<std::string&>(fullFilePathWithExtension).erase (fullFilePathWithExtension.find_last_of("."), std::string::npos)), Condition(condition), BiologicalReplicate(biorep), Fraction(fraction), TechnicalReplicate(techrep)
    {
    }

    bool SpectraFileInfo::Equals(SpectraFileInfo* obj)
    {
        return obj->FullFilePathWithExtension == this->FullFilePathWithExtension;
    }

    int SpectraFileInfo::GetHashCode()
    {
        return StringHelper::GetHashCode(FullFilePathWithExtension);
    }
}
