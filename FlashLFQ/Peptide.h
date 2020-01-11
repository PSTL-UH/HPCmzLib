#pragma once

#include "DetectionType.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <any>
#include "stringbuilder.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace FlashLFQ { class SpectraFileInfo; }
namespace FlashLFQ { class ProteinGroup; }


namespace FlashLFQ
{
    class Peptide
    {
    public:
        const std::string Sequence;
    private:
        std::unordered_map<SpectraFileInfo*, double> intensities;
        std::unordered_map<SpectraFileInfo*, DetectionType> detectionTypes;
    public:
        std::unordered_set<ProteinGroup*> proteinGroups;
        const bool UseForProteinQuant;

        Peptide(const std::string &sequence, bool useForProteinQuant);

        static std::string TabSeparatedHeader(std::vector<SpectraFileInfo*> &rawFiles);

        double GetIntensity(SpectraFileInfo *fileInfo);

        void SetIntensity(SpectraFileInfo *fileInfo, double intensity);

        DetectionType GetDetectionType(SpectraFileInfo *fileInfo);

        void SetDetectionType(SpectraFileInfo *fileInfo, DetectionType detectionType);

        std::string ToString(std::vector<SpectraFileInfo*> &rawFiles);

        bool Equals(std::any obj);

        int GetHashCode();
    };
}
