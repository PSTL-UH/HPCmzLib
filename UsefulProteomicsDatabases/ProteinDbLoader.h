#pragma once

#include "DecoyType.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <tuple>
#include "stringhelper.h"
#include "stringbuilder.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace UsefulProteomicsDatabases { class FastaHeaderFieldRegex; }
namespace Proteomics { class Modification; }
namespace Proteomics { class Protein; }

using namespace Proteomics;

namespace UsefulProteomicsDatabases
{
    class ProteinDbLoader final
    {
    public:
        static FastaHeaderFieldRegex *const UniprotAccessionRegex;
        static FastaHeaderFieldRegex *const UniprotFullNameRegex;
        static FastaHeaderFieldRegex *const UniprotNameRegex;
        static FastaHeaderFieldRegex *const UniprotGeneNameRegex;
        static FastaHeaderFieldRegex *const UniprotOrganismRegex;

        static FastaHeaderFieldRegex *const EnsemblAccessionRegex;
        static FastaHeaderFieldRegex *const EnsemblFullNameRegex;
        static FastaHeaderFieldRegex *const EnsemblGeneNameRegex;

        static std::unordered_map<std::string, std::vector<Modification*>> IdToPossibleMods;
        static std::unordered_map<std::string, Modification*> IdWithMotifToMod;

        /// <summary>
        /// Stores the last database file path.
        /// </summary>
    private:
        static std::string last_database_location;

        /// <summary>
        /// Stores the modification list read during LoadProteinXML
        /// </summary>
        static std::vector<Modification*> protein_xml_modlist_general;

        /// <summary>
        /// Load a mzLibProteinDb or UniProt XML file. Protein modifications may be specified before the protein entries (mzLibProteinDb format).
        /// If so, this modification list can be acquired with GetPtmListFromProteinXml after using this method.
        /// They may also be read in separately from a ptmlist text file, and then input as allKnownModifications.
        /// If protein modifications are specified both in the mzLibProteinDb XML file and in allKnownModifications, they are collapsed into a HashSet of Modifications before generating Protein entries.
        /// </summary>
    public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [SuppressMessage("Microsoft.Usage", "CA2202:Do not dispose objects multiple times")] public static List<Protein> LoadProteinXML(string proteinDbLocation, bool generateTargets, DecoyType decoyType, IEnumerable<Modification> allKnownModifications, bool isContaminant, IEnumerable<string> modTypesToExclude, out Dictionary<string, Modification> unknownModifications, int maxThreads = -1, int maxHeterozygousVariants = 4, int minAlleleDepth = 1)
        static std::vector<Protein*> LoadProteinXML(const std::string &proteinDbLocation, bool generateTargets, DecoyType decoyType, std::vector<Modification*> &allKnownModifications, bool isContaminant, std::vector<std::string> &modTypesToExclude, std::unordered_map<std::string, Modification*> &unknownModifications, int maxThreads = -1, int maxHeterozygousVariants = 4, int minAlleleDepth = 1);

        /// <summary>
        /// Get the modification entries specified in a mzLibProteinDb XML file (.xml or .xml.gz).
        /// </summary>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [SuppressMessage("Microsoft.Usage", "CA2202:Do not dispose objects multiple times")] public static List<Modification> GetPtmListFromProteinXml(string proteinDbLocation)
        static std::vector<Modification*> GetPtmListFromProteinXml(const std::string &proteinDbLocation);

        /// <summary>
        /// Load a protein fasta database, using regular expressions to get various aspects of the headers. The first regex capture group is used as each field.
        /// </summary>
        static std::vector<Protein*> LoadProteinFasta(const std::string &proteinDbLocation, bool generateTargets, DecoyType decoyType, bool isContaminant, FastaHeaderFieldRegex *accessionRegex, FastaHeaderFieldRegex *fullNameRegex, FastaHeaderFieldRegex *nameRegex, FastaHeaderFieldRegex *geneNameRegex, FastaHeaderFieldRegex *organismRegex, std::vector<std::string> &errors, int maxThreads = -1);

        /// <summary>
        /// Merge proteins that have the same accession, sequence, and contaminant designation.
        /// </summary>
        static std::vector<Protein*> MergeProteins(std::vector<Protein*> &mergeThese);

    private:
        static std::string ApplyRegex(FastaHeaderFieldRegex *regex, const std::string &line);

        static std::unordered_map<std::string, std::vector<Modification*>> GetModificationDict(std::vector<Modification*> &mods);

        static std::unordered_map<std::string, Modification*> GetModificationDictWithMotifs(std::vector<Modification*> &mods);
    };
}
