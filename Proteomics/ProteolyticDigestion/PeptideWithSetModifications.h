#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <any>
#include <optional>
#include <limits>
#include <iostream>
#include <fstream>

#include "stringhelper.h"
#include "stringbuilder.h"
#include <stdio.h>
#include <stdlib.h>

#include "ProteolyticPeptide.h"
#include "CleavageSpecificity.h"
#include "../../MassSpectrometry/Enums/DissociationType.h"
#include "../Fragmentation/ProductType.h"

#include "../Modifications/Modification.h"
#include "DigestionParams.h"
namespace Proteomics { class Protein; }

#include "../../Chemistry/Chemistry.h"
using namespace Chemistry;

#include "../../MassSpectrometry/MassSpectrometry.h"
using namespace MassSpectrometry;

#include "../AminoAcidPolymer/AminoAcidPolymer.h"
using namespace Proteomics::AminoAcidPolymer;

#include "../Fragmentation/FragmentationTerminus.h"
using namespace Proteomics::Fragmentation;

#include "../Fragmentation/Product.h"

#define PepWithSetModsDefaultSize 512


namespace Proteomics
{
    namespace ProteolyticDigestion
    {
        class PeptideWithSetModifications : public ProteolyticPeptide
        {
        private:
            std::string privateFullSequence;

            public:
                virtual ~PeptideWithSetModifications()
                {
                    if ( _digestionParams != nullptr ) 
                        delete _digestionParams;
                }

                std::string getFullSequence() const;
                void setFullSequence(const std::string &value);
            const int NumFixedMods;

            /// <summary>
            /// Dictionary of modifications on the peptide. The N terminus is index 1.
            /// The key indicates which residue modification is on (with 1 being N terminus).
            /// </summary>
        private:
            //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
            //ORIGINAL LINE: [NonSerialized] private Dictionary<int, Modification> _allModsOneIsNterminus;
            std::unordered_map<int, Modification*> _allModsOneIsNterminus; //we currently only allow one mod per position

            std::optional<bool> _hasChemicalFormulas;
            std::string _sequenceWithChemicalFormulas;
            std::optional<double> _monoisotopicMass;
            Proteomics::ProteolyticDigestion::DigestionParams *_digestionParams=nullptr;
            static const double WaterMonoisotopicMass;
            std::string DigestionParamString; // used to get digestion param object after deserialization
            std::string ProteinAccession; // used to get protein object after deserialization

            /// <summary>
            /// Creates a PeptideWithSetModifications object from a protein. Used when a Protein is digested.
            /// </summary>
        public:
            PeptideWithSetModifications(Proteomics::Protein *protein,
                                        Proteomics::ProteolyticDigestion::DigestionParams *digestionParams,
                                        int oneBasedStartResidueInProtein, int oneBasedEndResidueInProtein,
                                        CleavageSpecificity cleavageSpecificity,
                                        const std::string &peptideDescription, int missedCleavages,
                                        std::unordered_map<int, Modification*> &allModsOneIsNterminus,
                                        int numFixedMods);

            /// <summary>
            /// Creates a PeptideWithSetModifications object from a sequence string.
            /// Useful for reading in MetaMorpheus search engine output into mzLib objects.
            /// </summary>
            PeptideWithSetModifications(const std::string &sequence, std::unordered_map<std::string, Modification*> &allKnownMods,
                                        int numFixedMods = 0,
                                        Proteomics::ProteolyticDigestion::DigestionParams *digestionParams = nullptr,
                                        Proteomics::Protein *p = nullptr,
                                        int oneBasedStartResidueInProtein = std::numeric_limits<int>::min(),
                                        int oneBasedEndResidueInProtein = std::numeric_limits<int>::min(),
                                        int missedCleavages = std::numeric_limits<int>::min(),
                                        CleavageSpecificity cleavageSpecificity = CleavageSpecificity::Full,
                                        const std::string &peptideDescription = "");

            Proteomics::ProteolyticDigestion::DigestionParams *getDigestionParams() const;

            std::unordered_map<int, Modification*> &getAllModsOneIsNterminus();

            int getNumMods() const;

            int getNumVariableMods() const;

            double getMonoisotopicMass();

            std::string getSequenceWithChemicalFormulas();

            std::string getDigestionParamString() const; 

            std::string getProteinAccession() const; 

            void setProteinAccession(std::string accession);
            
            /// <summary>
            /// Generates theoretical fragments for given dissociation type for this peptide
            /// </summary>
            std::vector<Product*> Fragment(DissociationType dissociationType, FragmentationTerminus fragmentationTerminus);

#ifdef ORIG
            virtual std::string EssentialSequence(IReadOnlyDictionary<std::string, int> *modstoWritePruned);
#endif
            virtual std::string EssentialSequence(std::unordered_map<std::string, int> *modstoWritePruned);

#ifdef ORIG
            //C# TO C++ CONVERTER TODO TASK: Methods returning tuples are not converted by C# to C++ Converter:
            // private IEnumerable<(ProductType, int)> GetProlineZIonIndicies()
            //  {
             //     for (int i = BaseSequence.IndexOf('P'); i > -1; i = BaseSequence.IndexOf('P', i + 1))
            //            {
            //                yield return (ProductType.zDot, BaseSequence.Length - i);
            //            }
            //        }
#endif
            std::vector<std::tuple<ProductType, int>> GetProlineZIonIndicies()
            {
                std::vector<std::tuple<ProductType, int>> v;
                size_t i = 0;
                while ( (i = _baseSequence.find ( 'P', i ))){
                    if ( i == std::string::npos ) {
                        break;
                    }
                    v.push_back(std::make_tuple(ProductType::zDot, _baseSequence.length() - i));
                    i++;
                };
                return v;
            }
            
            PeptideWithSetModifications *Localize(int j, double massToLocalize);

            std::string ToString();

            bool Equals(PeptideWithSetModifications* obj);

            int GetHashCode();

            /// <summary>
            /// This should be run after deserialization of a PeptideWithSetModifications, in order to set its Protein and
            /// Modification objects, which were not serialized
            /// </summary>
            void SetNonSerializedPeptideInfo(std::unordered_map<std::string, Modification*> &idToMod,
                                             std::unordered_map<std::string, Proteomics::Protein*> &accessionToProtein);


            /// <summary>
            /// Alternative version of the function above, used by MetaMorpheus CrosslinkSpectral match deserialization
            /// </summary>
            void SetNonSerializedPeptideInfo ( std::vector<Proteomics::Protein *> &proteinList );
            
        private:
            void GetDigestionParamsAfterDeserialization();

            void GetModsAfterDeserialization(std::unordered_map<std::string, Modification*> &idToMod, std::string &baseSequence);

            void GetProteinAfterDeserialization(std::unordered_map<std::string, Proteomics::Protein*> &idToProtein);

            void DetermineFullSequence();

            void UpdateCleavageSpecificity();

        public:

            /// <summary>
            /// Pack a PeptideWithSetModifications into a character buffer.
            /// Required for Communication Operations in HPCMetaMorpheus
            ///
            /// Arguments:
            /// buf :     INOUT buffer used for packing
            /// buf_size: IN size of the allocated buffer provided by the upper layer
            ///           OUT size of required buffer if not large enough (return value -1)
            ///               or number of bytes used for packgin (return value > 0)
            /// pep(Vec): IN (vector of) PetideWithSetModifications to pack
            ///
            /// Return value:
            ///   -1 : input buffer was not large enough. buf_size will contain the required number
            ///        of bytes in this case
            ///   >0 : packing successful, number of bytes used up.
            /// </summary>
            static int Pack (char *buf, size_t &size, PeptideWithSetModifications *pep );
            static int Pack (char *buf, size_t &size,
                             const std::vector<PeptideWithSetModifications *> &pVec );

            /// <summary>
            /// similar functionality to Pack, but write the result to file
            /// instead of returning a char buffer (for communication)
            /// </summary>
            static void Serialize (std::string &filename, std::vector<PeptideWithSetModifications *> &pVec );
            static void Serialize (std::string &filename, PeptideWithSetModifications* &pVec );
            
            /// <summary>
            /// Functionality used to reconstruct a PeptideWithSetModifications based on a
            /// packed buffer.
            ///
            /// Arguments
            /// ---------
            /// buf:         IN input character buffer
            /// buf_len:     IN size of input buffer
            /// len:         OUT number of bytes used for unpacking 'count' elements
            /// newpep(Vec): OUT (vector of) new MatchedFragmentIon(s) .
            /// count:       IN how many elements to unpack.
            ///              default : -1 (until end of buffer is reached)
            /// </summary>
            static void Unpack (char *buf, size_t buf_len, size_t &len, PeptideWithSetModifications** newpep );
            static void Unpack (char *buf, size_t buf_len, size_t &len,
                                std::vector<PeptideWithSetModifications *> &newpVec,
                                int count = -1);

            /// <sumary>
            /// this method is meant to be used internally by the previous two methods,
            /// avoiding another (expensive) memcpy of the strings by passing
            /// in a starting index from where to use the stringvec
            /// </summary>
            static void Unpack (std::vector<std::string> &strVec, int index, size_t &len, PeptideWithSetModifications** newpep );

            /// <summary>
            /// Functionality used to reconstruct a PeptideWithSetModifications based on a
            /// packed buffer in a file.
            /// Arguments same as above, just no need to control number of elements read or determine
            /// end of a buffer.
            /// </summary>
            static void Deserialize (std::string &filename, std::vector<PeptideWithSetModifications *> &pVec );
            static void Deserialize (std::string &filename, PeptideWithSetModifications* &pVec );

        };
    }
}
