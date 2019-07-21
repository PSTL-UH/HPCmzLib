#pragma once

#include "InitiatorMethionineBehavior.h"
#include <vector>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
//namespace Proteomics { namespace ProteolyticDigestion { class Protease; } }
#include "Protease.h"
namespace Proteomics { namespace ProteolyticDigestion { class DigestionParams; } }

//namespace Proteomics { class Modification; }
#include "../Modifications/Modification.h"
namespace Proteomics { class Protein; }

//namespace Proteomics { namespace ProteolyticDigestion { class PeptideWithSetModifications; } }
#include "PeptideWithSetModifications.h"

#include "../Fragmentation/Fragmentation.h"
using namespace Proteomics::Fragmentation;

namespace Proteomics
{
    namespace ProteolyticDigestion
    {
        class ProteinDigestion
        {
        private:
            Proteomics::ProteolyticDigestion::Protease *privateProtease;
            int privateMaximumMissedCleavages = 0;
            Proteomics::ProteolyticDigestion::DigestionParams *privateDigestionParams;
            Proteomics::ProteolyticDigestion::InitiatorMethionineBehavior privateInitiatorMethionineBehavior = static_cast<Proteomics::ProteolyticDigestion::InitiatorMethionineBehavior>(0);
            int privateMinPeptideLength = 0;
            int privateMaxPeptideLength = 0;
            std::vector<Modification*> privateAllKnownFixedModifications;
            std::vector<Modification*> privateVariableModifications;

            /// <summary>
            /// Initializes digestion object
            /// </summary>
            /// <param name="digestionParams"></param>
            /// <param name="allKnownFixedModifications"></param>
            /// <param name="variableModifications"></param>
        public:
            ProteinDigestion(Proteomics::ProteolyticDigestion::DigestionParams *digestionParams, std::vector<Modification*> &allKnownFixedModifications, std::vector<Modification*> &variableModifications);

                Proteomics::ProteolyticDigestion::Protease *getProtease() const;
                void setProtease(Proteomics::ProteolyticDigestion::Protease *value);
                int getMaximumMissedCleavages() const;
                void setMaximumMissedCleavages(int value);
                Proteomics::ProteolyticDigestion::DigestionParams *getDigestionParams() const;
                void setDigestionParams(Proteomics::ProteolyticDigestion::DigestionParams *value);
                Proteomics::ProteolyticDigestion::InitiatorMethionineBehavior getInitiatorMethionineBehavior() const;
                void setInitiatorMethionineBehavior(Proteomics::ProteolyticDigestion::InitiatorMethionineBehavior value);
                int getMinPeptideLength() const;
                void setMinPeptideLength(int value);
                int getMaxPeptideLength() const;
                void setMaxPeptideLength(int value);
                std::vector<Modification*> getAllKnownFixedModifications() const;
                void setAllKnownFixedModifications(const std::vector<Modification*> &value);
                std::vector<Modification*> getVariableModifications() const;
                void setVariableModifications(const std::vector<Modification*> &value);

            /// <summary>
            /// Gets peptides for speedy semispecific digestion of a protein
            /// This generates specific peptides of maximum missed cleavages
            /// These peptides need to be digested post search to their actual sequences
            /// semi-specific search enters here...
            /// </summary>
            /// <param name="protein"></param>
            /// <returns></returns>
            std::vector<PeptideWithSetModifications*> SpeedySemiSpecificDigestion(Protein *protein); //We are only getting fully specific peptides of the maximum cleaved residues here

            /// <summary>
            /// Gets peptides for specific protease digestion of a protein
            /// </summary>
            /// <param name="protein"></param>
            /// <returns></returns>
            std::vector<PeptideWithSetModifications*> Digestion(Protein *protein);
        };
    }
}
