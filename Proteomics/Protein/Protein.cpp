#include "Protein.h"
#include "../Modifications/Modification.h"
#include "SequenceVariation.h"
#include "DisulfideBond.h"
#include "SpliceSite.h"
#include "ProteolysisProduct.h"
#include "DatabaseReference.h"
#include "../Modifications/ModificationLocalization.h"

using namespace Proteomics::ProteolyticDigestion;

namespace Proteomics
{

    Protein::Protein(const std::string &sequence, const std::string &accession, const std::string &organism, std::vector<std::tuple<std::string, std::string>> &geneNames, std::unordered_map<int, std::vector<Modification*>> &oneBasedModifications, std::vector<ProteolysisProduct*> &proteolysisProducts, const std::string &name, const std::string &fullName, bool isDecoy, bool isContaminant, std::vector<DatabaseReference*> &databaseReferences, std::vector<SequenceVariation*> &sequenceVariations, std::vector<SequenceVariation*> &appliedSequenceVariations, const std::string &sampleNameForVariants, std::vector<DisulfideBond*> &disulfideBonds, std::vector<SpliceSite*> &spliceSites, const std::string &databaseFilePath)
    {
        // Mandatory
        BaseSequence = sequence;
        NonVariantProtein = this;
        Accession = accession;

        Name = name;
        Organism = organism;
        FullName = fullName;
        IsDecoy = isDecoy;
        IsContaminant = isContaminant;
        DatabaseFilePath = databaseFilePath;
        SampleNameForVariants = sampleNameForVariants;

        GeneNames = geneNames ? geneNames : std::vector<std::tuple<std::string, std::string>>();
        ProteolysisProducts = proteolysisProducts ? proteolysisProducts : std::vector<ProteolysisProduct*>();
        SequenceVariations = sequenceVariations ? sequenceVariations : std::vector<SequenceVariation*>();
        AppliedSequenceVariations = appliedSequenceVariations ? appliedSequenceVariations : std::vector<SequenceVariation*>();
        setOriginalNonVariantModifications(oneBasedModifications ? oneBasedModifications : std::unordered_map<int, std::vector<Modification*>>());
        if (!oneBasedModifications.empty())
        {
            setOneBasedPossibleLocalizedModifications(SelectValidOneBaseMods(oneBasedModifications));
        }
        else
        {
            setOneBasedPossibleLocalizedModifications(std::unordered_map<int, std::vector<Modification*>>());
        }
        DatabaseReferences = databaseReferences ? databaseReferences : std::vector<DatabaseReference*>();
        DisulfideBonds = disulfideBonds ? disulfideBonds : std::vector<DisulfideBond*>();
        SpliceSites = spliceSites ? spliceSites : std::vector<SpliceSite*>();
    }

    std::unordered_map<int, std::vector<Modification*>> <missing_class_definition>::getOneBasedPossibleLocalizedModifications() const
    {
        return privateOneBasedPossibleLocalizedModifications;
    }

    void <missing_class_definition>::setOneBasedPossibleLocalizedModifications(const std::unordered_map<int, std::vector<Modification*>> &value)
    {
        privateOneBasedPossibleLocalizedModifications = value;
    }

    std::vector<std::tuple<std::string, std::string>> <missing_class_definition>::getGeneNames() const
    {
        return privateGeneNames;
    }

    std::string <missing_class_definition>::getAccession() const
    {
        return privateAccession;
    }

    std::string <missing_class_definition>::getBaseSequence() const
    {
        return privateBaseSequence;
    }

    std::string <missing_class_definition>::getOrganism() const
    {
        return privateOrganism;
    }

    bool <missing_class_definition>::getIsDecoy() const
    {
        return privateIsDecoy;
    }

    std::vector<SequenceVariation*> <missing_class_definition>::getSequenceVariations() const
    {
        return privateSequenceVariations;
    }

    std::vector<DisulfideBond*> <missing_class_definition>::getDisulfideBonds() const
    {
        return privateDisulfideBonds;
    }

    std::vector<SpliceSite*> <missing_class_definition>::getSpliceSites() const
    {
        return privateSpliceSites;
    }

    std::vector<ProteolysisProduct*> <missing_class_definition>::getProteolysisProducts() const
    {
        return privateProteolysisProducts;
    }

    std::vector<DatabaseReference*> <missing_class_definition>::getDatabaseReferences() const
    {
        return privateDatabaseReferences;
    }

    std::string <missing_class_definition>::getDatabaseFilePath() const
    {
        return privateDatabaseFilePath;
    }

    Protein *<missing_class_definition>::getNonVariantProtein() const
    {
        return privateNonVariantProtein;
    }

    std::vector<SequenceVariation*> <missing_class_definition>::getAppliedSequenceVariations() const
    {
        return privateAppliedSequenceVariations;
    }

    std::string <missing_class_definition>::getSampleNameForVariants() const
    {
        return privateSampleNameForVariants;
    }

    int <missing_class_definition>::getLength() const
    {
        return BaseSequence->Length;
    }

    std::string <missing_class_definition>::getFullDescription() const
    {
        return Accession + "|" + Name + "|" + FullName;
    }

    std::string <missing_class_definition>::getName() const
    {
        return privateName;
    }

    std::string <missing_class_definition>::getFullName() const
    {
        return privateFullName;
    }

    bool <missing_class_definition>::getIsContaminant() const
    {
        return privateIsContaminant;
    }

    std::unordered_map<int, std::vector<Modification*>> <missing_class_definition>::getOriginalNonVariantModifications() const
    {
        return privateOriginalNonVariantModifications;
    }

    void <missing_class_definition>::setOriginalNonVariantModifications(const std::unordered_map<int, std::vector<Modification*>> &value)
    {
        privateOriginalNonVariantModifications = value;
    }

    char <missing_class_definition>::operator [](int zeroBasedIndex)
    {
        return BaseSequence[zeroBasedIndex];
    }

    public std::string <missing_class_definition>::GetUniProtFastaHeader()
    {
        auto n = GeneNames::FirstOrDefault();
        std::string geneName = n == nullptr ? "" : n->Item2;
        return std::string::Format("mz|{0}|{1} {2} OS={3} GN={4}", Accession, Name, FullName, Organism, geneName);
    }

    public std::string <missing_class_definition>::GetEnsemblFastaHeader()
    {
        return StringHelper::formatSimple("{0} {1}", Accession, FullName);
    }

    public bool <missing_class_definition>::Equals(std::any obj)
    {
        return __super::Equals(obj);
    }

    public int <missing_class_definition>::GetHashCode()
    {
        return __super::GetHashCode();
    }

    public std::vector<PeptideWithSetModifications*> <missing_class_definition>::Digest(DigestionParams *digestionParams, std::vector<Modification*> &allKnownFixedModifications, std::vector<Modification*> &variableModifications)
    {
        ProteinDigestion *digestion = new ProteinDigestion(digestionParams, allKnownFixedModifications, variableModifications);

        delete digestion;
        return digestionParams->getSearchModeType() == CleavageSpecificity::Semi ? digestion->SpeedySemiSpecificDigestion(this) : digestion->Digestion(this);
    }

    public std::vector<Protein*> <missing_class_definition>::GetVariantProteins(int maxAllowedVariantsForCombinitorics, int minAlleleDepth)
    {
        return VariantApplication::ApplyVariants(this, SequenceVariations, maxAllowedVariantsForCombinitorics, minAlleleDepth);
    }

    public void <missing_class_definition>::RestoreUnfilteredModifications()
    {
        OneBasedPossibleLocalizedModifications = OriginalNonVariantModifications;
    }

    private std::unordered_map<int, std::vector<Modification*>> <missing_class_definition>::SelectValidOneBaseMods(std::unordered_map<int, std::vector<Modification*>> &dict)
    {
        std::unordered_map<int, std::vector<Modification*>> validModDictionary;
        for (auto entry : dict)
        {
            std::vector<Modification*> validMods;
            for (auto m : entry.Value)
            {
                //mod must be valid mod and the motif of the mod must be present in the protein at the specified location
                if (m->getValidModification() && ModificationLocalization::ModFits(m, BaseSequence, 0, BaseSequence->Length, entry.first))
                {
                    validMods.push_back(m);
                }
            }

            if (validMods.Any())
            {
                if (validModDictionary.Keys->Contains(entry.first))
                {
                    validModDictionary[entry.first].insert(validModDictionary[entry.first].end(), validMods.begin(), validMods.end());
                }
                else
                {
                    validModDictionary.emplace(entry.first, validMods);
                }
            }
        }
        return validModDictionary;
    }

    private std::string <missing_class_definition>::GetName(std::vector<SequenceVariation*> &appliedVariations, const std::string &name)
    {
        bool emptyVars = appliedVariations.empty() || appliedVariations.size()() == 0;
        if (name == "" && emptyVars)
        {
            return "";
        }
        else
        {
            std::string variantTag = emptyVars ? "" : StringHelper::formatSimple(" variant:{0}", VariantApplication::CombineDescriptions(appliedVariations));
            return name + variantTag;
        }
    }
}
