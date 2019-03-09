#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <tuple>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
//namespace Proteomics { class Modification; }
//namespace Proteomics { class SequenceVariation; }
//namespace Proteomics { class DisulfideBond; }
//namespace Proteomics { class ProteolysisProduct; }
//namespace Proteomics { class DatabaseReference; }
#include "Proteomics.h"
using namespace Proteomics;

namespace Proteomics {
    class Protein {
    private:
        std::unordered_map<int, std::vector<Modification*>> *privateOneBasedPossibleLocalizedModifications;
        std::vector<std::tuple<std::string, std::string>> *privateGeneNames;
        std::string privateAccession;
        std::string privateBaseSequence;
        bool privateIsDecoy = false;
        std::vector<SequenceVariation*> *privateSequenceVariations;
        std::vector<DisulfideBond*> *privateDisulfideBonds;
        std::vector<ProteolysisProduct*> *privateProteolysisProducts;
        std::vector<DatabaseReference*> *privateDatabaseReferences;
        std::string privateDatabaseFilePath;
        std::string privateName;
        std::string privateFullName;
        bool privateIsContaminant = false;

    public:
//        Protein(const std::string &sequence, const std::string &accession, std::vector<std::tuple<std::string, std::string>> &gene_names, std::unordered_map<int, std::vector<Modification*>> &oneBasedModifications, std::vector<ProteolysisProduct*> &proteolysisProducts, const std::string &name = "", const std::string &full_name = "", bool isDecoy = false, bool isContaminant = false, std::vector<DatabaseReference*> &databaseReferences, std::vector<SequenceVariation*> &sequenceVariations, std::vector<DisulfideBond*> &disulfideBonds, const std::string &databaseFilePath = "");
        Protein(const std::string &sequence, const std::string &accession, std::vector<std::tuple<std::string, std::string>> *gene_names, std::unordered_map<int, std::vector<Modification*>> *oneBasedModifications, std::vector<ProteolysisProduct*> *proteolysisProducts, const std::string &name = "", const std::string &full_name = "", bool isDecoy = false, bool isContaminant = false, std::vector<DatabaseReference*> *databaseReferences=nullptr, std::vector<SequenceVariation*> *sequenceVariations=nullptr, std::vector<DisulfideBond*> *disulfideBonds=nullptr, const std::string &databaseFilePath = "");

        std::unordered_map<int, std::vector<Modification*>> getOneBasedPossibleLocalizedModifications() const;

        /// <summary>
        /// The list of gene names consists of tuples, where Item1 is the type of gene name, and Item2 is the name. There may be many genes and names of a certain type produced when reading an XML protein database.
        /// </summary>
        std::vector<std::tuple<std::string, std::string>> getGeneNames() const;

        std::string getAccession() const;
        std::string getBaseSequence() const;
        bool getIsDecoy() const;
        std::vector<SequenceVariation*> getSequenceVariations() const;
        std::vector<DisulfideBond*> getDisulfideBonds() const;
        std::vector<ProteolysisProduct*> getProteolysisProducts() const;
        std::vector<DatabaseReference*> getDatabaseReferences() const;
        std::string getDatabaseFilePath() const;

        int getLength() const;

        std::string getFullDescription() const;

        std::string getName() const;

        std::string getFullName() const;

        bool getIsContaminant() const;


        char operator [](int zeroBasedIndex);

    };
}
