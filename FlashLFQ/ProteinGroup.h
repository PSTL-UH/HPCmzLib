#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <any>
#include "stringbuilder.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace FlashLFQ { class SpectraFileInfo; }


namespace FlashLFQ
{
    class ProteinGroup
    {
    public:
        const std::string ProteinGroupName;
        const std::string GeneName;
        const std::string Organism;
    private:
        std::unordered_map<SpectraFileInfo*, double> intensities;

    public:
        ProteinGroup(const std::string &proteinGroupName, const std::string &geneName, const std::string &organism);

        double GetIntensity(SpectraFileInfo *fileInfo);

        void SetIntensity(SpectraFileInfo *fileInfo, double intensity);

        static std::string TabSeparatedHeader(std::vector<SpectraFileInfo*> &rawFiles);

        std::string ToString(std::vector<SpectraFileInfo*> &rawFiles);

        bool Equals(std::any obj) override;

        int GetHashCode() override;
    };
}
