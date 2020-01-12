#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace FlashLFQ { class SpectraFileInfo; }
namespace FlashLFQ { class Peptide; }
namespace FlashLFQ { class ProteinGroup; }
namespace FlashLFQ { class ChromatographicPeak; }


namespace FlashLFQ
{
    class FlashLfqResults
    {
    public:
        //C# TO C++ CONVERTER WARNING: C++ has no equivalent to a 'readonly' collection
        // which allows modification of internal state:
        //ORIGINAL LINE: public readonly List<SpectraFileInfo> SpectraFiles;
        std::vector<SpectraFileInfo*> SpectraFiles;

        //ORIGINAL LINE: public readonly Dictionary<string, Peptide> PeptideModifiedSequences;
        std::unordered_map<std::string, Peptide*> PeptideModifiedSequences;

        //ORIGINAL LINE: public readonly Dictionary<string, ProteinGroup> ProteinGroups;
        std::unordered_map<std::string, ProteinGroup*> ProteinGroups;
        
        //ORIGINAL LINE: public readonly Dictionary<SpectraFileInfo, List<ChromatographicPeak>> Peaks;
        std::unordered_map<SpectraFileInfo*, std::vector<ChromatographicPeak*>> Peaks;

        FlashLfqResults(std::vector<SpectraFileInfo*> &spectraFiles);

        void MergeResultsWith(FlashLfqResults *mergeFrom);

        void CalculatePeptideResults();

        void CalculateProteinResultsTop3();

        void WriteResults(const std::string &peaksOutputPath, const std::string &modPeptideOutputPath,
                          const std::string &proteinOutputPath);
    };
}
