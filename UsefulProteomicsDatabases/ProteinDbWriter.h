#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <any>
#include <tuple>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Proteomics { class Modification; }
namespace Proteomics { class Protein; }
namespace Proteomics { class SequenceVariation; }

using namespace Proteomics;

namespace UsefulProteomicsDatabases
{
    class ProteinDbWriter
    {
        /// <summary>
        /// Writes a protein database in mzLibProteinDb format, with additional modifications from the AdditionalModsToAddToProteins list.
        /// </summary>
        /// <param name="additionalModsToAddToProteins"></param>
        /// <param name="proteinList"></param>
        /// <param name="outputFileName"></param>
        /// <returns>The new "modified residue" entries that are added due to being in the Mods dictionary</returns>
    public:
        static std::unordered_map<std::string, int> WriteXmlDatabase(std::unordered_map<std::string, std::unordered_set<std::tuple<int, Modification*>>> &additionalModsToAddToProteins, std::vector<Protein*> &proteinList, const std::string &outputFileName);

        static void WriteFastaDatabase(std::vector<Protein*> &proteinList, const std::string &outputFileName, const std::string &delimeter);

    private:
        static std::unordered_map<int, std::unordered_set<std::string>> GetModsForThisProtein(Protein *protein, SequenceVariation *seqvar, std::unordered_map<std::string, std::unordered_set<std::tuple<int, Modification*>>> &additionalModsToAddToProteins, std::unordered_map<std::string, int> &newModResEntries);
    };
}
