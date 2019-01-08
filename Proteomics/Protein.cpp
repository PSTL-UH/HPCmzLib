#include "Protein.h"
#include "Modification.h"
#include "SequenceVariation.h"
#include "DisulfideBond.h"
#include "ProteolysisProduct.h"
#include "DatabaseReference.h"


namespace Proteomics {

    Protein::Protein(const std::string &sequence, const std::string &accession, std::vector<std::tuple<std::string, std::string>> &gene_names, std::unordered_map<int, std::vector<Modification*>> &oneBasedModifications, std::vector<ProteolysisProduct*> &proteolysisProducts, const std::string &name, const std::string &full_name, bool isDecoy, bool isContaminant, std::vector<DatabaseReference*> &databaseReferences, std::vector<SequenceVariation*> &sequenceVariations, std::vector<DisulfideBond*> &disulfideBonds, const std::string &databaseFilePath) {
        // Mandatory
        BaseSequence = sequence;
        Accession = accession;

        Name = name;
        FullName = full_name;
        IsDecoy = isDecoy;
        IsContaminant = isContaminant;
        DatabaseFilePath = databaseFilePath;

        GeneNames = gene_names ? gene_names : std::vector<std::tuple<std::string, std::string>>();
        ProteolysisProducts = proteolysisProducts ? proteolysisProducts : std::vector<ProteolysisProduct*>();
        SequenceVariations = sequenceVariations ? sequenceVariations : std::vector<SequenceVariation*>();
        OneBasedPossibleLocalizedModifications = oneBasedModifications ? oneBasedModifications : std::unordered_map<int, std::vector<Modification*>>();
        DatabaseReferences = databaseReferences ? databaseReferences : std::vector<DatabaseReference*>();
        DisulfideBonds = disulfideBonds ? disulfideBonds : std::vector<DisulfideBond*>();
    }

    std::unordered_map<int, std::vector<Modification*>> Protein::getOneBasedPossibleLocalizedModifications() const {
        return privateOneBasedPossibleLocalizedModifications;
    }

    std::vector<std::tuple<std::string, std::string>> Protein::getGeneNames() const {
        return privateGeneNames;
    }

    std::string Protein::getAccession() const {
        return privateAccession;
    }

    std::string Protein::getBaseSequence() const {
        return privateBaseSequence;
    }

    bool Protein::getIsDecoy() const {
        return privateIsDecoy;
    }

    std::vector<SequenceVariation*> Protein::getSequenceVariations() const {
        return privateSequenceVariations;
    }

    std::vector<DisulfideBond*> Protein::getDisulfideBonds() const {
        return privateDisulfideBonds;
    }

    std::vector<ProteolysisProduct*> Protein::getProteolysisProducts() const {
        return privateProteolysisProducts;
    }

    std::vector<DatabaseReference*> Protein::getDatabaseReferences() const {
        return privateDatabaseReferences;
    }

    std::string Protein::getDatabaseFilePath() const {
        return privateDatabaseFilePath;
    }

    int Protein::getLength() const {
        return getBaseSequence().length();
    }

    std::string Protein::getFullDescription() const {
        return getAccession() + L"|" + getName() + L"|" + getFullName();
    }

    std::string Protein::getName() const {
        return privateName;
    }

    std::string Protein::getFullName() const {
        return privateFullName;
    }

    bool Protein::getIsContaminant() const {
        return privateIsContaminant;
    }

    char Protein::operator [](int zeroBasedIndex) {
        return getBaseSequence()[zeroBasedIndex];
    }
}
