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
#include "stringhelper.h"
#include "stringbuilder.h"


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

#include "cereal/cereal.hpp"

namespace Proteomics
{
    namespace ProteolyticDigestion
    {
        //C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
        //ORIGINAL LINE: [Serializable] public class PeptideWithSetModifications : ProteolyticPeptide
        class PeptideWithSetModifications : public ProteolyticPeptide
        {
        private:
            std::string privateFullSequence;

            public:
                virtual ~PeptideWithSetModifications()
                {
                    //delete _digestionParams;
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
            Proteomics::ProteolyticDigestion::DigestionParams *_digestionParams;
            static const double WaterMonoisotopicMass;
            std::string DigestionParamString; // used to get digestion param object after deserialization
            std::string ProteinAccession; // used to get protein object after deserialization

            /// <summary>
            /// Creates a PeptideWithSetModifications object from a protein. Used when a Protein is digested.
            /// </summary>
        public:
            PeptideWithSetModifications(Proteomics::Protein *protein, Proteomics::ProteolyticDigestion::DigestionParams *digestionParams, int oneBasedStartResidueInProtein, int oneBasedEndResidueInProtein, CleavageSpecificity cleavageSpecificity, const std::string &peptideDescription, int missedCleavages, std::unordered_map<int, Modification*> &allModsOneIsNterminus, int numFixedMods);

            /// <summary>
            /// Creates a PeptideWithSetModifications object from a sequence string.
            /// Useful for reading in MetaMorpheus search engine output into mzLib objects.
            /// </summary>
            PeptideWithSetModifications(const std::string &sequence, std::unordered_map<std::string, Modification*> &allKnownMods, int numFixedMods = 0, Proteomics::ProteolyticDigestion::DigestionParams *digestionParams = nullptr, Proteomics::Protein *p = nullptr, int oneBasedStartResidueInProtein = std::numeric_limits<int>::min(), int oneBasedEndResidueInProtein = std::numeric_limits<int>::min(), int missedCleavages = std::numeric_limits<int>::min(), CleavageSpecificity cleavageSpecificity = CleavageSpecificity::Full, const std::string &peptideDescription = "");

            Proteomics::ProteolyticDigestion::DigestionParams *getDigestionParams() const;

            std::unordered_map<int, Modification*> &getAllModsOneIsNterminus();

            int getNumMods() const;

            int getNumVariableMods() const;

            double getMonoisotopicMass();

            std::string getSequenceWithChemicalFormulas();

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
                };
                return v;
            }
            
            PeptideWithSetModifications *Localize(int j, double massToLocalize);

            std::string ToString();

            bool Equals(PeptideWithSetModifications* obj);

            int GetHashCode();

            /// <summary>
            /// This should be run after deserialization of a PeptideWithSetModifications, in order to set its Protein and Modification objects, which were not serialized
            /// </summary>
            void SetNonSerializedPeptideInfo(std::unordered_map<std::string, Modification*> &idToMod, std::unordered_map<std::string, Proteomics::Protein*> &accessionToProtein);


        private:
            void GetDigestionParamsAfterDeserialization();

            void GetModsAfterDeserialization(std::unordered_map<std::string, Modification*> &idToMod, std::string &baseSequence);

            void GetProteinAfterDeserialization(std::unordered_map<std::string, Proteomics::Protein*> &idToProtein);

            void DetermineFullSequence();

            void UpdateCleavageSpecificity();

        public:
            template <class Archive>
            void save( Archive & ar ) const
            {
                ar( cereal::make_nvp("privateFullSequence", privateFullSequence) );
                ar( cereal::make_nvp("sequenceWithChemicalFormulas", _sequenceWithChemicalFormulas) );
                if (_hasChemicalFormulas.has_value())
                    ar( cereal::make_nvp("hasChemicalFormulas", _hasChemicalFormulas) );
                if (_monoisotopicMass.has_value())
                    ar( cereal::make_nvp("monoisotopicMass", _monoisotopicMass) );
                ar( cereal::make_nvp("WaterMonoisotopicMass", WaterMonoisotopicMass) );
                ar( cereal::make_nvp("DigestionParamString", DigestionParamString) );
                ar( cereal::make_nvp("ProteinAccession", ProteinAccession) );
            }

            template <class Archive>
            static void load_and_construct( Archive & ar, cereal::construct<PeptideWithSetModifications> & construct )
            {
                std::string fullSequence;
                std::unordered_map<std::string, Modification*> allModsOneIsNterminus;
                ar( cereal::make_nvp("privateFullSequence", fullSequence) );

                // if (_hasChemicalFormulas.has_value())
                //     ar( cereal::make_nvp("hasChemicalFormulas", _hasChemicalFormulas) );
                // if (_monoisotopicMass.has_value())
                //     ar( cereal::make_nvp("monoisotopicMass", _monoisotopicMass) );
                // ar( cereal::make_nvp("WaterMonoisotopicMass", WaterMonoisotopicMass) );
                // ar( cereal::make_nvp("DigestionParamString", DigestionParamString) );
                // ar( cereal::make_nvp("ProteinAccession", ProteinAccession) );

                construct( fullSequence, allModsOneIsNterminus); // calls MyType( x )
            }
        };
    }
}
