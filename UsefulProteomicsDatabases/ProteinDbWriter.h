#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <tuple>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Proteomics { class Modification; }
namespace Proteomics { class Protein; }

using namespace Proteomics;

namespace UsefulProteomicsDatabases {
    class ProteinDbWriter {

        /// <summary>
        /// Writes a protein database in mzLibProteinDb format, with additional modifications from the AdditionalModsToAddToProteins list.
        /// </summary>
        /// <param name="AdditionalModsToAddToProteins"></param>
        /// <param name="proteinList"></param>
        /// <param name="outputFileName"></param>
        /// <returns>The new "modified residue" entries that are added due to being in the Mods dictionary</returns>
    public:
        static std::unordered_map<std::string, int> WriteXmlDatabase(std::unordered_map<std::string, std::unordered_set<std::tuple<int, Modification*>>> &AdditionalModsToAddToProteins, std::vector<Protein*> &proteinList, const std::string &outputFileName);

        static void WriteFastaDatabase(std::vector<Protein*> &proteinList, const std::string &outputFileName, const std::string &delimeter);

    };
}
