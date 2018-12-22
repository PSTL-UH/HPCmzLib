#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <tuple>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Proteomics { class Modification; }
namespace Proteomics { class SequenceVariation; }
namespace Proteomics { class DisulfideBond; }
namespace Proteomics { class ProteolysisProduct; }
namespace Proteomics { class DatabaseReference; }


namespace Proteomics {
    class Protein {
    private:
        std::unordered_map<int, std::vector<Modification*>> privateOneBasedPossibleLocalizedModifications;
        std::vector<std::tuple<std::wstring, std::wstring>> privateGeneNames;
        std::wstring privateAccession;
        std::wstring privateBaseSequence;
        bool privateIsDecoy = false;
        std::vector<SequenceVariation*> privateSequenceVariations;
        std::vector<DisulfideBond*> privateDisulfideBonds;
        std::vector<ProteolysisProduct*> privateProteolysisProducts;
        std::vector<DatabaseReference*> privateDatabaseReferences;
        std::wstring privateDatabaseFilePath;
        std::wstring privateName;
        std::wstring privateFullName;
        bool privateIsContaminant = false;

//        #region Public Constructors

    public:
        Protein(const std::wstring &sequence, const std::wstring &accession, std::vector<std::tuple<std::wstring, std::wstring>> &gene_names, std::unordered_map<int, std::vector<Modification*>> &oneBasedModifications, std::vector<ProteolysisProduct*> &proteolysisProducts, const std::wstring &name = L"", const std::wstring &full_name = L"", bool isDecoy = false, bool isContaminant = false, std::vector<DatabaseReference*> &databaseReferences, std::vector<SequenceVariation*> &sequenceVariations, std::vector<DisulfideBond*> &disulfideBonds, const std::wstring &databaseFilePath = L"");

//        #endregion Public Constructors

//        #region Public Properties

        std::unordered_map<int, std::vector<Modification*>> getOneBasedPossibleLocalizedModifications() const;

        /// <summary>
        /// The list of gene names consists of tuples, where Item1 is the type of gene name, and Item2 is the name. There may be many genes and names of a certain type produced when reading an XML protein database.
        /// </summary>
        std::vector<std::tuple<std::wstring, std::wstring>> getGeneNames() const;

        std::wstring getAccession() const;
        std::wstring getBaseSequence() const;
        bool getIsDecoy() const;
        std::vector<SequenceVariation*> getSequenceVariations() const;
        std::vector<DisulfideBond*> getDisulfideBonds() const;
        std::vector<ProteolysisProduct*> getProteolysisProducts() const;
        std::vector<DatabaseReference*> getDatabaseReferences() const;
        std::wstring getDatabaseFilePath() const;

        int getLength() const;

        std::wstring getFullDescription() const;

        std::wstring getName() const;

        std::wstring getFullName() const;

        bool getIsContaminant() const;

//        #endregion Public Properties

//        #region Public Indexers

        wchar_t operator [](int zeroBasedIndex);

//        #endregion Public Indexers
    };
}
