#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "SpectraFileInfo.h"
#include "Peptide.h"
#include "ProteinGroup.h"
#include "ChromatographicPeak.h"


namespace FlashLFQ
{
    class FlashLfqResults
    {
    public:
        std::vector<SpectraFileInfo*> SpectraFiles;
        std::unordered_map<std::string, Peptide*> PeptideModifiedSequences;
        std::unordered_map<std::string, ProteinGroup*> ProteinGroups;
        std::unordered_map<SpectraFileInfo*, std::vector<ChromatographicPeak*>> Peaks;

        FlashLfqResults(std::vector<SpectraFileInfo*> &spectraFiles);

        void MergeResultsWith(FlashLfqResults *mergeFrom);

        void CalculatePeptideResults();

        void CalculateProteinResultsTop3();

        void WriteResults(const std::string &peaksOutputPath, const std::string &modPeptideOutputPath,
                          const std::string &proteinOutputPath);
    };
}
