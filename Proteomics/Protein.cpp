#include "Protein.h"
#include "Modification.h"
#include "SequenceVariation.h"
#include "DisulfideBond.h"
#include "ProteolysisProduct.h"
#include "DatabaseReference.h"


namespace Proteomics {

    Protein::Protein(const std::string &sequence, const std::string &accession, std::vector<std::tuple<std::string, std::string>> *gene_names, std::unordered_map<int, std::vector<Modification*>> *oneBasedModifications, std::vector<ProteolysisProduct*> *proteolysisProducts, const std::string &name, const std::string &full_name, bool isDecoy, bool isContaminant, std::vector<DatabaseReference*> *databaseReferences, std::vector<SequenceVariation*> *sequenceVariations, std::vector<DisulfideBond*> *disulfideBonds, const std::string &databaseFilePath) {
        // Mandatory
        privateBaseSequence = sequence;
        privateAccession = accession;

        privateName = name;
        privateFullName = full_name;
        privateIsDecoy = isDecoy;
        privateIsContaminant = isContaminant;
        privateDatabaseFilePath = databaseFilePath;

        if ( gene_names != nullptr ) {
            privateGeneNames = gene_names;
        }
        else {
            privateGeneNames = new std::vector<std::tuple<std::string, std::string>>();
        }
        
        if ( proteolysisProducts != nullptr ) {
            privateProteolysisProducts = proteolysisProducts;
        }
        else {
            privateProteolysisProducts = new std::vector<ProteolysisProduct*>();
        }

        if ( sequenceVariations != nullptr ) {
            privateSequenceVariations =  sequenceVariations;
        }
        else {
            privateSequenceVariations = new std::vector<SequenceVariation*>();
        }

        if ( oneBasedModifications != nullptr ) {
            privateOneBasedPossibleLocalizedModifications =  oneBasedModifications;
        }
        else {
            privateOneBasedPossibleLocalizedModifications = new std::unordered_map<int, std::vector<Modification*>>();
        }

        if ( databaseReferences!=nullptr) {
            privateDatabaseReferences = databaseReferences;
        }
        else {
            privateDatabaseReferences = new std::vector<DatabaseReference*>();
        }

        if ( disulfideBonds!=nullptr) {
            privateDisulfideBonds =  disulfideBonds;
        }
        else {
            privateDisulfideBonds = new std::vector<DisulfideBond*>();
        }
    }

    std::unordered_map<int, std::vector<Modification*>> Protein::getOneBasedPossibleLocalizedModifications() const {
        return *privateOneBasedPossibleLocalizedModifications;
    }

    std::vector<std::tuple<std::string, std::string>> Protein::getGeneNames() const {
        return *privateGeneNames;
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
        return *privateSequenceVariations;
    }

    std::vector<DisulfideBond*> Protein::getDisulfideBonds() const {
        return *privateDisulfideBonds;
    }

    std::vector<ProteolysisProduct*> Protein::getProteolysisProducts() const {
        return *privateProteolysisProducts;
    }

    std::vector<DatabaseReference*> Protein::getDatabaseReferences() const {
        return *privateDatabaseReferences;
    }

    std::string Protein::getDatabaseFilePath() const {
        return privateDatabaseFilePath;
    }

    int Protein::getLength() const {
        return getBaseSequence().length();
    }

    std::string Protein::getFullDescription() const {
        return getAccession() + "|" + getName() + "|" + getFullName();
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
