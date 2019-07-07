#pragma once

#include "InitiatorMethionineBehavior.h"
#include "CleavageSpecificity.h"
#include <string>
#include <vector>
#include <any>
#include "stringhelper.h"

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace Proteomics { namespace ProteolyticDigestion { class Protease; } }

using namespace Proteomics::Fragmentation;

namespace Proteomics
{
    namespace ProteolyticDigestion
    {
        class DigestionParams
        {
        private:
            int privateMaxMissedCleavages = 0;
            Proteomics::ProteolyticDigestion::InitiatorMethionineBehavior privateInitiatorMethionineBehavior = static_cast<Proteomics::ProteolyticDigestion::InitiatorMethionineBehavior>(0);
            int privateMinPeptideLength = 0;
            int privateMaxPeptideLength = 0;
            int privateMaxModificationIsoforms = 0;
            int privateMaxModsForPeptide = 0;
            Proteomics::ProteolyticDigestion::Protease *privateProtease;
            CleavageSpecificity privateSearchModeType = static_cast<CleavageSpecificity>(0);
            FragmentationTerminus privateFragmentationTerminus = static_cast<FragmentationTerminus>(0);
            Proteomics::ProteolyticDigestion::Protease *privateSpecificProtease;

            // this parameterless constructor needs to exist to read the toml.
            // if you can figure out a way to get rid of it, feel free...
        public:
            DigestionParams();

            DigestionParams(const std::string &protease = "trypsin", int maxMissedCleavages = 2, int minPeptideLength = 7, int maxPeptideLength = int::MaxValue, int maxModificationIsoforms = 1024, Proteomics::ProteolyticDigestion::InitiatorMethionineBehavior initiatorMethionineBehavior = InitiatorMethionineBehavior::Variable, int maxModsForPeptides = 2, CleavageSpecificity searchModeType = CleavageSpecificity::Full, FragmentationTerminus fragmentationTerminus = FragmentationTerminus::Both);

                int getMaxMissedCleavages() const;
                void setMaxMissedCleavages(int value);
                Proteomics::ProteolyticDigestion::InitiatorMethionineBehavior getInitiatorMethionineBehavior() const;
                void setInitiatorMethionineBehavior(Proteomics::ProteolyticDigestion::InitiatorMethionineBehavior value);
                int getMinPeptideLength() const;
                void setMinPeptideLength(int value);
                int getMaxPeptideLength() const;
                void setMaxPeptideLength(int value);
                int getMaxModificationIsoforms() const;
                void setMaxModificationIsoforms(int value);
                int getMaxModsForPeptide() const;
                void setMaxModsForPeptide(int value);
                Proteomics::ProteolyticDigestion::Protease *getProtease() const;
                void setProtease(Proteomics::ProteolyticDigestion::Protease *value);
                CleavageSpecificity getSearchModeType() const;
                void setSearchModeType(CleavageSpecificity value);
                FragmentationTerminus getFragmentationTerminus() const;
                void setFragmentationTerminus(FragmentationTerminus value);
                Proteomics::ProteolyticDigestion::Protease *getSpecificProtease() const;
                void setSpecificProtease(Proteomics::ProteolyticDigestion::Protease *value);

            bool Equals(std::any obj) override;

            int GetHashCode() override;

            std::string ToString() override;

            /// <summary>
            /// Creates a DigestionParams object from string. Used after deserializing a PeptideWithSetModifications
            /// </summary>
            static DigestionParams *FromString(const std::string &str);

        private:
            void RecordSpecificProtease();
        };
    }
}
