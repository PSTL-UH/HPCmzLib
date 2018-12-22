#include "Protein.h"
#include "Modification.h"
#include "SequenceVariation.h"
#include "DisulfideBond.h"
#include "ProteolysisProduct.h"
#include "DatabaseReference.h"


namespace Proteomics {

    Protein::Protein(const std::wstring &sequence, const std::wstring &accession, std::vector<std::tuple<std::wstring, std::wstring>> &gene_names, std::unordered_map<int, std::vector<Modification*>> &oneBasedModifications, std::vector<ProteolysisProduct*> &proteolysisProducts, const std::wstring &name, const std::wstring &full_name, bool isDecoy, bool isContaminant, std::vector<DatabaseReference*> &databaseReferences, std::vector<SequenceVariation*> &sequenceVariations, std::vector<DisulfideBond*> &disulfideBonds, const std::wstring &databaseFilePath) {
        // Mandatory
        BaseSequence = sequence;
        Accession = accession;

        Name = name;
        FullName = full_name;
        IsDecoy = isDecoy;
        IsContaminant = isContaminant;
        DatabaseFilePath = databaseFilePath;

        GeneNames = gene_names ? gene_names : std::vector<std::tuple<std::wstring, std::wstring>>();
        ProteolysisProducts = proteolysisProducts ? proteolysisProducts : std::vector<ProteolysisProduct*>();
        SequenceVariations = sequenceVariations ? sequenceVariations : std::vector<SequenceVariation*>();
        OneBasedPossibleLocalizedModifications = oneBasedModifications ? oneBasedModifications : std::unordered_map<int, std::vector<Modification*>>();
        DatabaseReferences = databaseReferences ? databaseReferences : std::vector<DatabaseReference*>();
        DisulfideBonds = disulfideBonds ? disulfideBonds : std::vector<DisulfideBond*>();
    }

    std::unordered_map<int, std::vector<Modification*>> Protein::getOneBasedPossibleLocalizedModifications() const {
        return privateOneBasedPossibleLocalizedModifications;
    }

    std::vector<std::tuple<std::wstring, std::wstring>> Protein::getGeneNames() const {
        return privateGeneNames;
    }

    std::wstring Protein::getAccession() const {
        return privateAccession;
    }

    std::wstring Protein::getBaseSequence() const {
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

    std::wstring Protein::getDatabaseFilePath() const {
        return privateDatabaseFilePath;
    }

    int Protein::getLength() const {
        return getBaseSequence().length();
    }

    std::wstring Protein::getFullDescription() const {
        return getAccession() + L"|" + getName() + L"|" + getFullName();
    }

    std::wstring Protein::getName() const {
        return privateName;
    }

    std::wstring Protein::getFullName() const {
        return privateFullName;
    }

    bool Protein::getIsContaminant() const {
        return privateIsContaminant;
    }

    wchar_t Protein::operator [](int zeroBasedIndex) {
        return getBaseSequence()[zeroBasedIndex];
    }
}
