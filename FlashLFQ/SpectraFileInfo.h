#pragma once

#include <string>
#include <any>

namespace FlashLFQ
{
    class SpectraFileInfo
    {
    public:
        const std::string FullFilePathWithExtension;
        const std::string FilenameWithoutExtension;
        const std::string Condition; // condition/biorep/techrep/fraction info
        const int BiologicalReplicate;
        const int Fraction;
        const int TechnicalReplicate;

        SpectraFileInfo(const std::string &fullFilePathWithExtension, const std::string &condition, int biorep, int techrep, int fraction);

        // files are considered the same if the absolute file path is the same
        bool Equals(std::any obj) override;

        int GetHashCode() override;
    };
}
