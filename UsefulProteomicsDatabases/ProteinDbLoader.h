#pragma once

#include "DecoyType.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <tuple>
#include <optional>
#include "stringhelper.h"
#include "stringbuilder.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Proteomics { class Modification; }
namespace Proteomics { class Protein; }

using namespace Proteomics;

namespace UsefulProteomicsDatabases {
    class ProteinDbLoader final {
//        #region Public Fields

    public:
        static Regex *uniprot_accession_expression;

        static Regex *uniprot_fullName_expression;

        static Regex *uniprot_gene_expression;

        static Regex *ensembl_accession_expression;

        static Regex *ensembl_fullName_expression;

        static Regex *ensembl_gene_expression;

//        #endregion Public Fields

//        #region Private Fields

        /// <summary>
        /// Stores the last database file path.
        /// </summary>
    private:
        static std::wstring last_database_location;

        /// <summary>
        /// Stores the modification list read during LoadProteinXML
        /// </summary>
        static std::vector<Modification*> protein_xml_modlist;

//        #endregion Private Fields

//        #region Public Methods

        /// <summary>
        /// Load a mzLibProteinDb or UniProt XML file. Protein modifications may be specified before the protein entries (mzLibProteinDb format).
        /// If so, this modification list can be acquired with GetPtmListFromProteinXml after using this method.
        /// They may also be read in separately from a ptmlist text file, and then input as allKnownModifications.
        /// If protein modifications are specified both in the mzLibProteinDb XML file and in allKnownModifications, they are collapsed into a HashSet of Modifications before generating Protein entries.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="proteinDbLocation"></param>
        /// <param name="generateTargetProteins"></param>
        /// <param name="generateDecoyProteins"></param>
        /// <param name="allKnownModifications"></param>
        /// <param name="IsContaminant"></param>
        /// <param name="dbRefTypesToKeep"></param>
        /// <param name="modTypesToExclude"></param>
        /// <param name="unknownModifications"></param>
        /// <returns></returns>
    public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [SuppressMessage("Microsoft.Usage", "CA2202:Do not dispose objects multiple times")] public static List<Protein> LoadProteinXML(string proteinDbLocation, bool generateTargetProteins, DecoyType decoyType, IEnumerable<Modification> allKnownModifications, bool IsContaminant, IEnumerable<string> modTypesToExclude, out Dictionary<string, Modification> unknownModifications)
        static std::vector<Protein*> LoadProteinXML(const std::wstring &proteinDbLocation, bool generateTargetProteins, DecoyType decoyType, std::vector<Modification*> &allKnownModifications, bool IsContaminant, std::vector<std::wstring> &modTypesToExclude, std::unordered_map<std::wstring, Modification*> &unknownModifications);

        /// <summary>
        /// Get the modification entries specified in a mzLibProteinDb XML file (.xml or .xml.gz).
        /// </summary>
        /// <param name="proteinDbLocation"></param>
        /// <returns></returns>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in native C++:
//ORIGINAL LINE: [SuppressMessage("Microsoft.Usage", "CA2202:Do not dispose objects multiple times")] public static List<Modification> GetPtmListFromProteinXml(string proteinDbLocation)
        static std::vector<Modification*> GetPtmListFromProteinXml(const std::wstring &proteinDbLocation);

        /// <summary>
        /// Load a protein fasta database, using regular expressions to get various aspects of the headers. The first regex capture group is used as each field.
        /// </summary>
        /// <param name="proteinDbLocation"></param>
        /// <param name="onTheFlyDecoys"></param>
        /// <param name="IsContaminant"></param>
        /// <param name="accession_expression"></param>
        /// <param name="full_name_expression"></param>
        /// <param name="name_expression"></param>
        /// <param name="gene_expression"></param>
        /// <returns></returns>
        static std::vector<Protein*> LoadProteinFasta(const std::wstring &proteinDbLocation, bool originalTarget, DecoyType onTheFlyDecoys, bool IsContaminant, Regex *accession_expression, Regex *full_name_expression, Regex *name_expression, Regex *gene_expression);

        /// <summary>
        /// Merge proteins that have the same accession, sequence, and contaminant designation.
        /// </summary>
        /// <param name="merge_these"></param>
        /// <returns></returns>
        static std::vector<Protein*> Merge_proteins(std::vector<Protein*> &merge_these);

//        #endregion Public Methods

//        #region Private Methods

    private:
        static int GetOldShuffleIndex(int i, int numSlides, int sequenceLength, bool methioninePresent);

        static std::unordered_map<std::wstring, std::vector<Modification*>> GetModificationDict(std::vector<Modification*> &mods);

//        #endregion Private Methods
    };
}
