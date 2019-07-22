#include "Protein.h"
#include "../Modifications/Modification.h"
#include "SequenceVariation.h"
#include "DisulfideBond.h"
#include "SpliceSite.h"
#include "ProteolysisProduct.h"
#include "DatabaseReference.h"
#include "../Modifications/ModificationLocalization.h"

#include "stringhelper.h"

//using namespace Proteomics::ProteolyticDigestion;

namespace Proteomics
{

    Protein::Protein(const std::string &sequence,
                     const std::string &accession,
                     const std::string &organism,
                     std::vector<std::tuple<std::string, std::string>> geneNames,
                     std::unordered_map<int, std::vector<Modification*>> oneBasedModifications,
                     std::vector<ProteolysisProduct*> proteolysisProducts,
                     const std::string &name,
                     const std::string &fullName,
                     bool isDecoy, bool isContaminant,
                     std::vector<DatabaseReference*> databaseReferences,
                     std::vector<SequenceVariation*> sequenceVariations,
                     std::vector<SequenceVariation*> appliedSequenceVariations,
                     const std::string &sampleNameForVariants,
                     std::vector<DisulfideBond*> disulfideBonds,
                     std::vector<SpliceSite*> spliceSites,
                     const std::string &databaseFilePath)
    {
        // Mandatory
        privateBaseSequence = sequence;
        privateNonVariantProtein = this;
        privateAccession = accession;

        privateName = name;
        privateOrganism = organism;
        privateFullName = fullName;
        privateIsDecoy = isDecoy;
        privateIsContaminant = isContaminant;
        privateDatabaseFilePath = databaseFilePath;
        privateSampleNameForVariants = sampleNameForVariants;

#ifdef ORIG
        privateGeneNames = geneNames ? geneNames : std::vector<std::tuple<std::string, std::string>>();
        privateProteolysisProducts = proteolysisProducts ? proteolysisProducts : std::vector<ProteolysisProduct*>();
        privateSequenceVariations = sequenceVariations ? sequenceVariations : std::vector<SequenceVariation*>();
        privateAppliedSequenceVariations = appliedSequenceVariations ? appliedSequenceVariations : std::vector<SequenceVariation*>();
        setOriginalNonVariantModifications(oneBasedModifications ? oneBasedModifications : std::unordered_map<int, std::vector<Modification*>>());
#endif
        // EG: in Theory, a reference can never have a null value in C++;
        privateGeneNames = geneNames;
        privateProteolysisProducts = proteolysisProducts;
        privateSequenceVariations = sequenceVariations;
        privateAppliedSequenceVariations = appliedSequenceVariations;
        setOriginalNonVariantModifications(oneBasedModifications);
        
        if (!oneBasedModifications.empty()) {
            setOneBasedPossibleLocalizedModifications(SelectValidOneBaseMods(oneBasedModifications));
        }
        else  {
            setOneBasedPossibleLocalizedModifications(std::unordered_map<int, std::vector<Modification*>>());
        }
        privateDatabaseReferences = databaseReferences ;
        privateDisulfideBonds = disulfideBonds;
        privateSpliceSites = spliceSites;
    }

    std::unordered_map<int, std::vector<Modification*>> Protein::getOneBasedPossibleLocalizedModifications() const
    {
        return privateOneBasedPossibleLocalizedModifications;
    }

    void Protein::setOneBasedPossibleLocalizedModifications(const std::unordered_map<int, std::vector<Modification*>> &value)
    {
        privateOneBasedPossibleLocalizedModifications = value;
    }

    std::vector<std::tuple<std::string, std::string>> Protein::getGeneNames() const
    {
        return privateGeneNames;
    }

    std::string Protein::getAccession() const
    {
        return privateAccession;
    }

    std::string Protein::getBaseSequence() const
    {
        return privateBaseSequence;
    }

    std::string Protein::getOrganism() const
    {
        return privateOrganism;
    }

    bool Protein::getIsDecoy() const
    {
        return privateIsDecoy;
    }

    std::vector<SequenceVariation*> Protein::getSequenceVariations() const
    {
        return privateSequenceVariations;
    }

    std::vector<DisulfideBond*> Protein::getDisulfideBonds() const
    {
        return privateDisulfideBonds;
    }

    std::vector<SpliceSite*> Protein::getSpliceSites() const
    {
        return privateSpliceSites;
    }

    std::vector<ProteolysisProduct*> Protein::getProteolysisProducts() const
    {
        return privateProteolysisProducts;
    }

    std::vector<DatabaseReference*> Protein::getDatabaseReferences() const
    {
        return privateDatabaseReferences;
    }

    std::string Protein::getDatabaseFilePath() const
    {
        return privateDatabaseFilePath;
    }

    Protein* Protein::getNonVariantProtein() const
    {
        return privateNonVariantProtein;
    }

    std::vector<SequenceVariation*> Protein::getAppliedSequenceVariations() const
    {
        return privateAppliedSequenceVariations;
    }

    std::string Protein::getSampleNameForVariants() const
    {
        return privateSampleNameForVariants;
    }

    int Protein::getLength() const
    {
        return privateBaseSequence.length();
    }

    std::string Protein::getFullDescription() const
    {
        return privateAccession + "|" + privateName + "|" + privateFullName;
    }

    std::string Protein::getName() const
    {
        return privateName;
    }

    std::string Protein::getFullName() const
    {
        return privateFullName;
    }

    bool Protein::getIsContaminant() const
    {
        return privateIsContaminant;
    }

    std::unordered_map<int, std::vector<Modification*>> Protein::getOriginalNonVariantModifications() const
    {
        return privateOriginalNonVariantModifications;
    }

    void Protein::setOriginalNonVariantModifications(std::unordered_map<int, std::vector<Modification*>> &value)
    {
        privateOriginalNonVariantModifications = value;
    }

#ifdef LATER
    char <missing_class_definition>::operator [](int zeroBasedIndex)
    {
        return BaseSequence[zeroBasedIndex];
    }
#endif

    std::string Protein::GetUniProtFastaHeader()
    {
#ifdef ORIG
        auto n = privateGeneNames->FirstOrDefault();
        std::string geneName = n == nullptr ? "" : n->Item2;
#endif
        std::tuple<std::string, std::string> n = privateGeneNames[0];
        std::string geneName = std::get<1>(n);

#ifdef ORIG
        return StringHelper::formatSimple("mz|{0}|{1} {2} OS={3} GN={4}", privateAccession, privateName,
                                   privateFullName, privateOrganism, geneName);
#endif
        std::string s = "mz|" + privateAccession + "|" + privateName + " " + privateFullName + " OS= " +
            privateOrganism + " GN=" +  geneName;
        return s;
    }

    std::string Protein::GetEnsemblFastaHeader()
    {
        return StringHelper::formatSimple("{0} {1}", privateAccession, privateFullName);
    }

    bool Protein::Equals(Protein *obj)
    {
#ifdef ORIG
        // C++ Note: this is Microsoft C++ extension not supported by g++
        return __super::Equals(obj);
        // Using the version from the current repository ( 07/21/2019) instead
        // of the previos verions. The C# code is as follows.
        // Protein otherProtein = (Protein)obj;
        // return otherProtein != null && otherProtein.Accession.Equals(Accession) &&
        // otherProtein.BaseSequence.Equals(BaseSequence);
#endif
        return obj != nullptr                           && 
            privateAccession    == obj->getAccession()  &&
            privateBaseSequence == obj->getBaseSequence() ;
    }

    int Protein::GetHashCode()
    {
#ifdef ORIG
        return __super::GetHashCode();
        // Using the version from the current repository (07/21/2019) instead
        // of the one used by the convertor. Original C# code is as follows.
        //  return this.BaseSequence.GetHashCode();
#endif
        return StringHelper::GetHashCode(privateBaseSequence);
    }
    
    std::vector<PeptideWithSetModifications*> Protein::Digest(DigestionParams *digestionParams,
                                                              std::vector<Modification*> &allKnownFixedModifications,
                                                              std::vector<Modification*> &variableModifications)
    {
        ProteinDigestion *digestion = new ProteinDigestion(digestionParams, allKnownFixedModifications,
                                                           variableModifications);

        //delete digestion;
        return digestionParams->getSearchModeType() == CleavageSpecificity::Semi ? digestion->SpeedySemiSpecificDigestion(this) : digestion->Digestion(this);
    }

    std::vector<Protein*> Protein::GetVariantProteins(int maxAllowedVariantsForCombinitorics, int minAlleleDepth)
    {
        return VariantApplication::ApplyVariants(this, privateSequenceVariations,
                                                 maxAllowedVariantsForCombinitorics,
                                                 minAlleleDepth);
    }

    void Protein::RestoreUnfilteredModifications()
    {
        privateOneBasedPossibleLocalizedModifications = privateOriginalNonVariantModifications;
    }

    std::unordered_map<int, std::vector<Modification*>> Protein::SelectValidOneBaseMods(std::unordered_map<int, std::vector<Modification*>> &dict)
    {
        std::unordered_map<int, std::vector<Modification*>> validModDictionary;
        for (auto entry =dict.begin(); entry != dict.end(); entry++ )
        {
            std::vector<Modification*> validMods;
            for (auto m : entry->second )
            {
                // mod must be valid mod and the motif of the mod must be present in the protein at the
                // specified location
                if (m->getValidModification() && ModificationLocalization::ModFits(m, privateBaseSequence, 0,
                                                                                   privateBaseSequence.length(),
                                                                                   entry->first))
                {
                    validMods.push_back(m);
                }
            }

            if (!validMods.empty())
            {
                if (validModDictionary.find(entry->first) != validModDictionary.end() )
                {
                    validModDictionary[entry->first].insert(validModDictionary[entry->first].end(),
                                                            validMods.begin(), validMods.end());
                }
                else
                {
                    validModDictionary.emplace(entry->first, validMods);
                }
            }
        }
        return validModDictionary;
    }

    std::string Protein::GetName(std::vector<SequenceVariation*> &appliedVariations, const std::string &name)
    {
        bool emptyVars = appliedVariations.empty() || appliedVariations.size() == 0;
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
