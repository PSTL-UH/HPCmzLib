#pragma once

#include "VariantApplication.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <tuple>
#include "stringhelper.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Proteomics { class Modification; }
namespace Proteomics { class SequenceVariation; }
namespace Proteomics { class DisulfideBond; }
namespace Proteomics { class SpliceSite; }
namespace Proteomics { class ProteolysisProduct; }
namespace Proteomics { class DatabaseReference; }

using namespace Proteomics::ProteolyticDigestion;

namespace Proteomics
{
    class Protein
    {
    private:
        std::unordered_map<int, std::vector<Modification*>> privateOneBasedPossibleLocalizedModifications;
        std::vector<std::tuple<std::string, std::string>> privateGeneNames;
        std::string privateAccession;
        std::string privateBaseSequence;
        std::string privateOrganism;
        bool privateIsDecoy = false;
        std::vector<SequenceVariation*> privateSequenceVariations;
        std::vector<DisulfideBond*> privateDisulfideBonds;
        std::vector<SpliceSite*> privateSpliceSites;
        std::vector<ProteolysisProduct*> privateProteolysisProducts;
        std::vector<DatabaseReference*> privateDatabaseReferences;
        std::string privateDatabaseFilePath;
        Protein *privateNonVariantProtein;
        std::vector<SequenceVariation*> privateAppliedSequenceVariations;
        std::string privateSampleNameForVariants;
        std::string privateName;
        std::string privateFullName;
        bool privateIsContaminant = false;
        std::unordered_map<int, std::vector<Modification*>> privateOriginalNonVariantModifications;

        /// <summary>
        /// Protein. Filters out modifications that do not match their amino acid target site.
        /// </summary>
        /// <param name="sequence">Base sequence of the protein.</param>
        /// <param name="accession">Unique accession for the protein.</param>
        /// <param name="organism">Organism with this protein.</param>
        /// <param name="geneNames">List of gene names as tuple of (nameType, name), e.g. (primary, HLA-A)</param>
        /// <param name="oneBasedModifications">Modifications at positions along the sequence.</param>
        /// <param name="proteolysisProducts"></param>
        /// <param name="name"></param>
        /// <param name="fullName"></param>
        /// <param name="isDecoy"></param>
        /// <param name="isContaminant"></param>
        /// <param name="databaseReferences"></param>
        /// <param name="sequenceVariations"></param>
        /// <param name="disulfideBonds"></param>
        /// <param name="spliceSites"></param>
        /// <param name="databaseFilePath"></param>
    public:
        Protein(const std::string &sequence, const std::string &accession, const std::string &organism = "", std::vector<std::tuple<std::string, std::string>> &geneNames = std::vector<std::tuple<std::string, std::string>>(), std::unordered_map<int, std::vector<Modification*>> &oneBasedModifications = std::unordered_map<int, std::vector<Modification>>(), std::vector<ProteolysisProduct*> &proteolysisProducts = std::vector<ProteolysisProduct>(), const std::string &name = "", const std::string &fullName = "", bool isDecoy = false, bool isContaminant = false, std::vector<DatabaseReference*> &databaseReferences = std::vector<DatabaseReference>(), std::vector<SequenceVariation*> &sequenceVariations = std::vector<SequenceVariation>(), std::vector<SequenceVariation*> &appliedSequenceVariations = std::vector<SequenceVariation>(), const std::string &sampleNameForVariants = "", std::vector<DisulfideBond*> &disulfideBonds = std::vector<DisulfideBond>(), std::vector<SpliceSite*> &spliceSites = std::vector<SpliceSite>(), const std::string &databaseFilePath = "");

        /// <summary>
        /// Protein construction with applied variations
        /// </summary>
        /// <param name="variantBaseSequence"></param>
        /// <param name="protein"></param>
        /// <param name="appliedSequenceVariations"></param>
        /// <param name="applicableProteolysisProducts"></param>
        /// <param name="oneBasedModifications"></param>
        /// <param name="sampleNameForVariants"></param>
        Protein(std::string variantBaseSequence, Protein protein, std::vector<SequenceVariation*> appliedSequenceVariations, std::vector<ProteolysisProduct*> applicableProteolysisProducts, std::unordered_map<int, std::vector<Modification*>> oneBasedModifications, std::string sampleNameForVariants) : this(variantBaseSequence, VariantApplication::GetAccession(protein, appliedSequenceVariations), organism: protein::Organism, geneNames: std::vector<std::tuple<std::string, std::string>>(protein::GeneNames), oneBasedModifications: oneBasedModifications != nullptr ? oneBasedModifications::ToDictionary([&] (std::any x)
        {
        x::Key;
        }, [&] (std::any x)
        {
        x->Value;
    }) : std::unordered_map<int, std::vector<Modification*>>(), proteolysisProducts: std::vector<ProteolysisProduct*>((applicableProteolysisProducts != nullptr) ? applicableProteolysisProducts : std::vector<ProteolysisProduct*>()), name: GetName(appliedSequenceVariations, protein->Name), fullName: GetName(appliedSequenceVariations, protein->FullName), isDecoy: protein::IsDecoy, isContaminant: protein::IsContaminant, databaseReferences: std::vector<DatabaseReference*>(protein::DatabaseReferences), sequenceVariations: std::vector<SequenceVariation*>(protein::SequenceVariations), disulfideBonds: std::vector<DisulfideBond*>(protein::DisulfideBonds), spliceSites: std::vector<SpliceSite*>(protein::SpliceSites), databaseFilePath: protein::DatabaseFilePath){NonVariantProtein = protein::NonVariantProtein;
            setOriginalNonVariantModifications(getNonVariantProtein()->getOriginalNonVariantModifications());
            AppliedSequenceVariations = ((appliedSequenceVariations != nullptr) ? appliedSequenceVariations : std::vector<SequenceVariation*>())->ToList();
            SampleNameForVariants = sampleNameForVariants;
    };

        /// <summary>
        /// Modifications (values) located at one-based protein positions (keys)
        /// </summary>
//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        public IDictionary<int, List<Modification>> OneBasedPossibleLocalizedModifications
        {
            std::unordered_map<int, std::vector<Modification*>> get();
//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
            set
        }

        /// <summary>
        /// The list of gene names consists of tuples, where Item1 is the type of gene name, and Item2 is the name. There may be many genes and names of a certain type produced when reading an XML protein database.
        /// </summary>
//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        public IEnumerable<std::tuple<string, string>> GeneNames
        {
            std::vector<std::tuple<std::string, std::string>> get();
        }

        /// <summary>
        /// Unique accession for this protein.
        /// </summary>
//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        public string Accession
        {
            std::string get();
        }

        /// <summary>
        /// Base sequence, which may contain applied sequence variations.
        /// </summary>
//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        public string BaseSequence
        {
            std::string get();
        }

//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        public string Organism
        {
            std::string get();
        }
//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        public bool IsDecoy
        {
            bool get();
        }
//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        public IEnumerable<SequenceVariation> SequenceVariations
        {
            std::vector<SequenceVariation*> get();
        }
//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        public IEnumerable<DisulfideBond> DisulfideBonds
        {
            std::vector<DisulfideBond*> get();
        }
//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        public IEnumerable<SpliceSite> SpliceSites
        {
            std::vector<SpliceSite*> get();
        }
//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        public IEnumerable<ProteolysisProduct> ProteolysisProducts
        {
            std::vector<ProteolysisProduct*> get();
        }
//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        public IEnumerable<DatabaseReference> DatabaseReferences
        {
            std::vector<DatabaseReference*> get();
        }
//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        public string DatabaseFilePath
        {
            std::string get();
        }

        /// <summary>
        /// Protein before applying variations.
        /// </summary>
//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        public Protein NonVariantProtein
        {
            Protein *get();
        }

        /// <summary>
        /// Sequence variations that have been applied to the base sequence.
        /// </summary>
//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        public List<SequenceVariation> AppliedSequenceVariations
        {
            std::vector<SequenceVariation*> get();
        }

        /// <summary>
        /// Sample name from which applied variants came, e.g. tumor or normal.
        /// </summary>
//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        public string SampleNameForVariants
        {
            std::string get();
        }

//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        public int Length
        {
            int get();
        }

//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        public string FullDescription
        {
            std::string get();
        }

//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        public string Name
        {
            std::string get();
        }
//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        public string FullName
        {
            std::string get();
        }
//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        public bool IsContaminant
        {
            bool get();
        }
//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        internal IDictionary<int, List<Modification>> OriginalNonVariantModifications
        {
            std::unordered_map<int, std::vector<Modification*>> get();
//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
            set
        }

//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        public char this[int zeroBasedIndex]
        {
            char get(int zeroBasedIndex);
        }

        /// <summary>
        /// Formats a string for a UniProt fasta header. See https://www.uniprot.org/help/fasta-headers.
        /// Note that the db field isn't very applicable here, so mz is placed in to denote written by mzLib.
        /// </summary>
//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        public string GetUniProtFastaHeader()

        /// <summary>
        /// Formats a string for an ensembl header
        /// </summary>
//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        public string GetEnsemblFastaHeader()

        /// <summary>
        /// The protein object uses the default equals method for speed, 
        /// but note that two protein objects with the same information will not be equal by this method.
        /// </summary>
        /// <param name="obj"></param>
        /// <returns></returns>
//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        public override bool Equals(object obj)

        /// <summary>
        /// The protein object uses the default hash code method for speed, 
        /// but note that two protein objects with the same information will give two different hash codes.
        /// </summary>
        /// <returns></returns>
//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        public override int GetHashCode()

        /// <summary>
        /// Gets peptides for digestion of a protein
        /// </summary>
//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        public IEnumerable<PeptideWithSetModifications> Digest(DigestionParams digestionParams, IEnumerable<Modification> allKnownFixedModifications, List<Modification> variableModifications)

        /// <summary>
        /// Gets proteins with applied variants from this protein
        /// </summary>
//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        public List<Protein> GetVariantProteins(int maxAllowedVariantsForCombinitorics = 4, int minAlleleDepth = 1)

        /// <summary>
        /// Restore all modifications that were read in, including those that did not match their target amino acid.
        /// </summary>
//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        public void RestoreUnfilteredModifications()

        /// <summary>
        /// Filters modifications that do not match their target amino acid.
        /// </summary>
        /// <param name="dict"></param>
        /// <returns></returns>
//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        private IDictionary<int, List<Modification>> SelectValidOneBaseMods(IDictionary<int, List<Modification>> dict)

//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
        private static string GetName(IEnumerable<SequenceVariation> appliedVariations, string name)
}
}
