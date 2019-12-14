#include "SpectraFileInfo.h"

namespace FlashLFQ
{

    SpectraFileInfo::SpectraFileInfo(const std::string &fullFilePathWithExtension, const std::string &condition, int biorep, int techrep, int fraction) : FullFilePathWithExtension(fullFilePathWithExtension), FilenameWithoutExtension(System::IO::Path::GetFileNameWithoutExtension(this->FullFilePathWithExtension)), Condition(condition), BiologicalReplicate(biorep), Fraction(fraction), TechnicalReplicate(techrep)
    {
    }

    bool SpectraFileInfo::Equals(std::any obj)
    {
        return __super::Equals(obj) && (std::any_cast<SpectraFileInfo*>(obj))->FullFilePathWithExtension == this->FullFilePathWithExtension;
    }

    int SpectraFileInfo::GetHashCode()
    {
        return FullFilePathWithExtension.GetHashCode();
    }
}
