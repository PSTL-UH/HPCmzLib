#pragma once

#include "ProteolyticPeptide.h"
#include "CleavageSpecificity.h"
#include "../../MassSpectrometry/Enums/DissociationType.h"
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <any>
#include <optional>
#include "stringhelper.h"
#include "stringbuilder.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Proteomics { class Modification; }
namespace Proteomics { namespace ProteolyticDigestion { class DigestionParams; } }
namespace Proteomics { class Protein; }

using namespace Chemistry;
using namespace MassSpectrometry;
using namespace Proteomics::AminoAcidPolymer;
using namespace Proteomics::Fragmentation;

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

//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [NonSerialized] private Nullable<bool> _hasChemicalFormulas;
            std::optional<bool> _hasChemicalFormulas;
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [NonSerialized] private string _sequenceWithChemicalFormulas;
            std::string _sequenceWithChemicalFormulas;
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [NonSerialized] private Nullable<double> _monoisotopicMass;
            std::optional<double> _monoisotopicMass;
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [NonSerialized] private DigestionParams _digestionParams;
            Proteomics::ProteolyticDigestion::DigestionParams *_digestionParams;
            static const double WaterMonoisotopicMass;
            const std::string DigestionParamString; // used to get digestion param object after deserialization
            const std::string ProteinAccession; // used to get protein object after deserialization

            /// <summary>
            /// Creates a PeptideWithSetModifications object from a protein. Used when a Protein is digested.
            /// </summary>
        public:
//C# TO C++ CONVERTER TODO TASK: There is no C++ equivalent to 'ToString':
            PeptideWithSetModifications(Proteomics::Protein *protein, Proteomics::ProteolyticDigestion::DigestionParams *digestionParams, int oneBasedStartResidueInProtein, int oneBasedEndResidueInProtein, CleavageSpecificity cleavageSpecificity, const std::string &peptideDescription, int missedCleavages, std::unordered_map<int, Modification*> &allModsOneIsNterminus, int numFixedMods);

            /// <summary>
            /// Creates a PeptideWithSetModifications object from a sequence string.
            /// Useful for reading in MetaMorpheus search engine output into mzLib objects.
            /// </summary>
            PeptideWithSetModifications(const std::string &sequence, std::unordered_map<std::string, Modification*> &allKnownMods, int numFixedMods = 0, Proteomics::ProteolyticDigestion::DigestionParams *digestionParams = nullptr, Proteomics::Protein *p = nullptr, int oneBasedStartResidueInProtein = int::MinValue, int oneBasedEndResidueInProtein = int::MinValue, int missedCleavages = int::MinValue, CleavageSpecificity cleavageSpecificity = CleavageSpecificity::Full, const std::string &peptideDescription = "");

            Proteomics::ProteolyticDigestion::DigestionParams *getDigestionParams() const;

            std::unordered_map<int, Modification*> getAllModsOneIsNterminus() const;

            int getNumMods() const;

            int getNumVariableMods() const;

            double getMonoisotopicMass() const;

            std::string getSequenceWithChemicalFormulas() const;

            /// <summary>
            /// Generates theoretical fragments for given dissociation type for this peptide
            /// </summary>
            std::vector<Product*> Fragment(DissociationType dissociationType, FragmentationTerminus fragmentationTerminus);

            virtual std::string EssentialSequence(IReadOnlyDictionary<std::string, int> *modstoWritePruned);

//C# TO C++ CONVERTER TODO TASK: Methods returning tuples are not converted by C# to C++ Converter:
//            private IEnumerable<(ProductType, int)> GetProlineZIonIndicies()
    //        {
    //            for (int i = BaseSequence.IndexOf('P'); i > -1; i = BaseSequence.IndexOf('P', i + 1))
    //            {
    //                yield return (ProductType.zDot, BaseSequence.Length - i);
    //            }
    //        }

            PeptideWithSetModifications *Localize(int j, double massToLocalize);

            std::string ToString() override;

            bool Equals(std::any obj) override;

            int GetHashCode() override;

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
        };
    }
}
